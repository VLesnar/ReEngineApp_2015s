#include "pe3.h"

using namespace std;
float dist = 1;
double theta = 1;
double phi = 1;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,  0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//Constructor
pe3::pe3(int argc, char** argv)
{
	init();
	//This program was written with milliseconds
	//in mind, whereas glfwGetTime returns the time
	//in seconds, so we multiply it with 1000.
	lastFrame = glfwGetTime() * 1000;
}

//This is our main update loop
void pe3::update(void)
{
	//Current frame's time, in milliseconds
	currentFrame = glfwGetTime() * 1000;

	//The time between our current and last frame
	float deltaF = currentFrame - lastFrame;

	//Time carried over from the previous frame:
	//timeStepsToProcess < dT
	//...
	timeStepsToProcess += deltaF;
	//...is now: 
	//timeStepsToProcess > dT

	//We're using a constant dT (60 fps).
	//If, after we're done processing our 
	//time steps, we have any time left
	//over, that carries over to the next frame.
	while (timeStepsToProcess >= deltaT)
	{

		timeStepsToProcess -= deltaT;

		if (simulationActive)
			for (int i = 0; i < NUM_BALLS; i++) 
			{

				//Update the ball's velocity
				balls[i].pos.x += balls[i].vx;
				balls[i].pos.y += balls[i].vy;
				balls[i].pos.z += balls[i].vz;

				//Attempt at wall collisions
				glm::vec4 posi = glm::vec4(balls[i].pos, 1);  //need to create a vec4 to conform with multiplication by a mat4
				posi = modelMatrix*posi; //this transforms from global coordinates into the local coordinates of the box, despite appearing to do just the opposite
				balls[i].pos.x = posi.x;
				balls[i].pos.y = posi.y;
				balls[i].pos.z = posi.z;

				//now the same needs to be done to the ball's velocity vector
				glm::vec4 veloc = glm::vec4(balls[i].vx, balls[i].vy, balls[i].vz, 1);
				veloc = modelMatrix*veloc;
				balls[i].vx = veloc.x;
				balls[i].vy = veloc.y;
				balls[i].vz = veloc.z;
				
				
				//Actual collisions
				if (balls[i].pos.x < -STAGE_WIDTH / 2. + balls[i].radius)
				{
					balls[i].pos.x = -STAGE_WIDTH / 2. + balls[i].radius;
					balls[i].vx *= -1;
				}
				else if (balls[i].pos.x > STAGE_WIDTH / 2. - balls[i].radius)
				{
					balls[i].pos.x = STAGE_WIDTH / 2. - balls[i].radius;
					balls[i].vx *= -1;
				}

				if (balls[i].pos.y < -STAGE_HEIGHT / 2. + balls[i].radius)
				{
					balls[i].pos.y = -STAGE_HEIGHT / 2. + balls[i].radius;
					balls[i].vy *= -1;
				}
				else if (balls[i].pos.y > STAGE_HEIGHT / 2. - balls[i].radius)
				{
					balls[i].pos.y = STAGE_HEIGHT / 2. - balls[i].radius;
					balls[i].vy *= -1;
				}

				if (balls[i].pos.z < -STAGE_DEPTH / 2. + balls[i].radius)
				{
					balls[i].pos.z = -STAGE_DEPTH / 2. + balls[i].radius;
					balls[i].vz *= -1;
				}
				else if (balls[i].pos.z > STAGE_DEPTH / 2. - balls[i].radius)
				{
					balls[i].pos.z = STAGE_DEPTH / 2. - balls[i].radius;
					balls[i].vz *= -1;
				}

				//Checks for collisions with other balls
				for (int j = 0; j < NUM_BALLS; j++)
				{
					if (i != j)
					{
						float touchDistance = balls[i].radius + balls[j].radius;
						if ((balls[i].pos.x - balls[j].pos.x) <= touchDistance && (balls[i].pos.y - balls[j].pos.y) <= touchDistance && (balls[i].pos.z - balls[j].pos.z) <= touchDistance)
						{
							balls[i].isColliding = 1;
							balls[j].isColliding = 1;
						}
						else
						{
							balls[i].isColliding = 0;
							balls[j].isColliding = 0;
						}
					}
				}

				//after the collisions between ball and the six sides of the box are handled, transform back to global coordinates using glm::transpose(modelMatrix) 
				posi = glm::transpose(modelMatrix)*glm::vec4(balls[i].pos, 1);
				balls[i].pos.x = posi.x;
				balls[i].pos.y = posi.y;
				balls[i].pos.z = posi.z;

				veloc = glm::transpose(modelMatrix)*glm::vec4(balls[i].vx, balls[i].vy, balls[i].vz, 1);
				balls[i].vx = veloc.x;
				balls[i].vy = veloc.y;
				balls[i].vz = veloc.z;


			}

	}

	lastFrame = currentFrame;

	//x = d  sin(θ)sin(φ), y = d cos(φ),  z = d cos(θ)sin(φ)   where  0 < d,   0 ≤ θ ≤ 2π,  0 < φ < π   (the restrictions on d and φ are intentional)
	viewMatrix = glm::lookAt(glm::vec3(dist*sin(theta)*sin(phi), dist*cos(phi), dist*cos(theta)*sin(phi)), cameraFront, cameraUp);
	
	
}

void pe3::init(void)
{
	glClearColor(0.4f, 0.4f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	//The cube's initial orientation
	//(an identity matrix)
	modelMatrix = glm::mat4();

	//Lets load our .obj!
	//Our vertices will be in sphere[0].mesh.positions
	//Our indices will be in sphere[0].mesh.indices
	std::string error = tinyobj::LoadObj(sphere, "sphere.obj");
	if (error.size() > 0)
		printf("Error: %s", error.c_str());

	//Laying pipes like a plumber
	//(Initialize rendering pipeline)
	initPipeline();
	
	//x = d  sin(θ)sin(φ), y = d cos(φ),  z = d cos(θ)sin(φ)   where  0 < d,   0 ≤ θ ≤ 2π,  0 < φ < π   (the restrictions on d and φ are intentional)

	//Initialize the view matrix
	viewMatrix = glm::mat4();
	viewMatrix = glm::lookAt(glm::vec3(dist*sin(theta)*sin(phi), dist*cos(phi), dist*cos(theta)*sin(phi)), cameraFront, cameraUp);
	//viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f));
	//viewMatrix = glm::translate(viewMatrix, cameraTrans);



	//Prepare our perspective matrix
	//This is our FOV
	float angle = 45.0f;
	//Aspect ratio = Screen Width/ Screen Height
	float imageAspectRatio = 500.0f / 500.0f;
	float n = 0.1f;//near
	float f = 100.0f;//far

	//Actually create the perspective matrix using the previously calculated values
	projMatrix = glm::perspective(angle, imageAspectRatio, n, f);

	/*
	Load our initial model, perspective, and view matrices onto the GPU:

	(Uniform variables are variables on the GPU that are set by the user
	from outside the gpu. This is data you're free to "upload"to the GPU
	whenever you wish.)

	The "locations" correspond to actual locations on the GPU where your
	variable will live. In the case of this example, we're specifically
	stating that we will be loading matrices onto the GPU (evidenced by
	the Matrix4fv part of glUniformMatrix4fv, signifying that we're loading
	a 4x4 matrix comprising of floats). The 1 is the amount of matrices we're
	loading into the variable, and the following boolean controls whether
	the matrix is transposed or not.
	*/
	glUniformMatrix4fv(projLocation, 1, false, glm::value_ptr(projMatrix) );
	glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(modelMatrix) );
	glUniformMatrix4fv(viewLocation, 1, false, glm::value_ptr(viewMatrix) );

	float random;

	srand(time(0));

	//Here we create the balls that are to be jumping around in our cube
	//We use random values for their starting speeds and sizes
	for (int i = 0; i < NUM_BALLS; i++) 
	{

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].pos.x = random*STAGE_WIDTH / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].pos.y = random*STAGE_HEIGHT / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].pos.z = random*STAGE_DEPTH / 2.;

		random = ((rand() / (GLfloat)RAND_MAX));

		balls[i].radius = random * 2;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].vx = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].vy = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].vz = MAX_SPEED*random;

		balls[i].isColliding = 0;

	}

}

void pe3::initPipeline(void)
{
	//Our OpenGL "program"
	//stores and links our compiled
	//shaders.
	program = glCreateProgram();

	//Set up our shaders!
	//Vertex shaders deal with the 
	//vertices of every object
	initShader(GL_VERTEX_SHADER, "vertex.glsl", program);

	//Fragment shaders deal with
	//the colours of each pixel
	initShader(GL_FRAGMENT_SHADER, "fragment.glsl", program);

	//Linking the program
	//creates executables
	//for our two shaders.
	//Also initializes all
	//uniform variables'
	//locations
	glLinkProgram(program);

	//Initialize our buffers
	//We will be using buffers to send our vertex information
	//(from our loaded .obj file, which is stored in vertex<> shapes
	initBuffers();

	//We need to get the location for our matrix variables after
	//the program has been linked.
	projLocation = glGetUniformLocation(program, "proj");//The perspective (projection) matrix
	modelLocation = glGetUniformLocation(program, "model");//The model matrix (the teapot)
	viewLocation = glGetUniformLocation(program, "view");//The view matrix (the camera)
	boolLocation = glGetUniformLocation(program, "collision");//The bool controlling the sphere's colour

	glUseProgram(program);

}

void pe3::initBuffers()
{
	//If anything in this section needs further explaining,
	//feel free to consult the comments in the previous example's
	//initBuffers() function

	vertexAttribLocation = glGetAttribLocation(program, "vertex_in");
	checkGLErrors("Query vertex attribute location");

	//Cube First
	//VAO
	glGenVertexArrays(1, &cubeVAOLocation);
	glBindVertexArray(cubeVAOLocation);
	/* -- Everything after this point will be recorded into our cube's VAO -- */

	//Set up the index buffer for our cube
	glGenBuffers(1, &cubeIBOLocation);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBOLocation);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(GLuint), &cubeIndices[0], GL_STATIC_DRAW);

	//Set up the vertex buffer for our cube
	glGenBuffers(1, &cubeVBOLocation);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOLocation);
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), &cube[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(vertexAttribLocation, 3, GL_FLOAT, 0, 0, 0);
	//Enable our VAO for reading, our last step for this VAO!
	glEnableVertexAttribArray(vertexAttribLocation);
	checkGLErrors("Cube buffers");

	//Now lets do the same for the sphere!
	//Notice how it gets its own VAO? Check out display()
	//to see how we're using it.
	glGenVertexArrays(1, &sphereVAOLocation);
	glBindVertexArray(sphereVAOLocation);
	/* -- Everything after this point will be  recorded into our sphere's VAO -- */
	glGenBuffers(1, &sphereIBOLocation);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBOLocation);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere[0].mesh.indices.size() * sizeof(GLuint), &sphere[0].mesh.indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &sphereVBOLocation);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBOLocation);
	glBufferData(GL_ARRAY_BUFFER, sphere[0].mesh.positions.size() * 3 * sizeof(float), &sphere[0].mesh.positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribLocation, 3, GL_FLOAT, 0, 0, 0);
	//Enable VAO for reading
	glEnableVertexAttribArray(vertexAttribLocation);
	checkGLErrors("Sphere buffers");

	//If anything in this section confused you, look here for further information:
	// http://www.opengl.org/wiki/Vertex_Array_Object

	//Lets clean up after ourselves...
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(program);
	checkGLErrors("Use program");

}

//In our current version of OpenGL (3.3 for this demo) we have to
//manually query for gl errors. In versions 4.3 and above, however,
//it's possible to add this function as a callback for whenever
//an error occurs. For more info see: https://www.opengl.org/wiki/Debug_Output
bool pe3::checkGLErrors(const char* description)
{
	GLenum error = glGetError();
	bool hadError = false;

	while(error != GL_NO_ERROR)
	{
		printf("[ERROR]@[%s]: %s\n", description, gluErrorString(error));
		error = glGetError();
		hadError = true;
	}

	return hadError;
}

bool pe3::initShader(GLenum type, std::string file, GLuint program)
{
    //Lets create a shader object on the GPU
	GLuint shader = glCreateShader( type );
	checkGLErrors("initShader: created shader");

	std::string source;

	if(!readFile(file, &source))
	{
		printf("ERROR: Could not read file %s", file.c_str());
	}

    //The string containing our shader's text
	GLchar const *shader_source = source.c_str();

    //Lets set it so that the shader stored at the location
    //entitled "shader" will be 
	glShaderSource( shader, 1, &shader_source, NULL );
	checkGLErrors("initShader: set shader source");
	

	glCompileShader( shader );
	checkGLErrors("initShader: compiled shader");

	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &shaderCompiled ); 
	if( shaderCompiled != GL_TRUE ) 
	{ 
		printf( "ERROR: Unable to compile shader %d!\n\nSource:\n%s\n", shader, source.c_str() );
		int infoLength = 0;
		int maxL = infoLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxL);
		char* infoLog = new char[maxL];

		glGetProgramInfoLog(program, maxL, &infoLength, infoLog);
		//if (infoLength > 0)
			printf("GLPROGRAMIV:%s\n", infoLog);

		glDeleteShader( shader );
		shader = 0;
	}

	glAttachShader( program, shader );
	checkGLErrors("initShader: attached shader");

	return true;
}

//Just a generic function for reading a file!
bool pe3::readFile(std::string filename, std::string* target)
{

	std::ifstream shaderSource(filename.c_str());

	target->assign( ( std::istreambuf_iterator< char >( shaderSource ) ), std::istreambuf_iterator< char >() );
	if(target->length() > 0)
		return true;

	return false;

}

void pe3::display(void)
{
	//Clears the color and depth buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int i = 0;

	//Load the view matrix onto the shader 
	glUniformMatrix4fv(viewLocation, 1, false, value_ptr(viewMatrix));

	//Load the model matrix for the cube
	glUniformMatrix4fv(modelLocation, 1, false, value_ptr(modelMatrix));
	glUniform1i(boolLocation, 0);

	//Cube
	//Look ma, no buffers!
	//(Since we set up a Vertex Array Object when setting up our buffers, all we 
	//have to do is load the vertex array to have access to the buffers' "state"
	//which we previously setup. See initBuffers() for more)
	glBindVertexArray(cubeVAOLocation);
	glDrawElements(GL_LINE_STRIP, elements, GL_UNSIGNED_INT, NULL);

	//Sphere
	glBindVertexArray(sphereVAOLocation);

	glLineWidth(.5);
	//Each ball has its own position in the world,
	//so we're using a unique matrix for each ball.
	glm::mat4 ballMatrix;

	for (i = 0; i < NUM_BALLS; i++)
	{
		//Reset the matrix to the identity matrix
		ballMatrix = glm::mat4();

		//Translate it
		ballMatrix = glm::translate(ballMatrix, balls[i].pos);
		
		//Scale it (since a ball's default radius is 1, we can just
		//treat its radius as its scale!)
		ballMatrix = glm::scale(ballMatrix, glm::vec3(balls[i].radius));

		//Send it to the GPU
		glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(ballMatrix));

		//Update the colour boolean
		if (balls[i].isColliding == 0)
			glUniform1i(boolLocation, 0);
		else
			glUniform1i(boolLocation, 1);

		//Draw the ball
		glDrawElements(GL_LINES, sphere[0].mesh.indices.size(), GL_UNSIGNED_INT, NULL);
	}

	glBindVertexArray(0);
	glFlush();

 }


void pe3::reshape (int w, int h)
{
	//Prepare our perspective matrix
	//This is our FOV
	float angle = 45.0f;
	//Aspect ratio = Screen Width/ Screen Height
	float imageAspectRatio = (float)w / (float)h;
	float n = 0.1f;//near
	float f = 100.0f;//far

	//Actually create the perspective matrix using the previously calculated values
	projMatrix = glm::perspective(angle, imageAspectRatio, n, f);
	glUniformMatrix4fv(projLocation, 1, false, glm::value_ptr(projMatrix));
	glViewport(0, 0, w, h);
 }



void pe3::keyboard(int key, int scancode, int action, int mods)
{
	GLfloat cameraSpeed = 0.05f;
	//Sanity check
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
		return;

	if (mods == GLFW_MOD_SHIFT)
		caps = !caps;

	switch (key) {
				

		case GLFW_KEY_G:
			{	
				/* change roll, i.e. rotate about the object's local z axis */
				glm::vec3 axis(0.0f, 0.0f, 1.0f);
				if (!caps)
					modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), axis);
				else
					modelMatrix = glm::rotate(modelMatrix, glm::radians(-1.0f), axis);
			}
			break;
	
		case GLFW_KEY_B:
			
			{
				/*  change pitch, i.e. rotate about the object's local x axis   */
				glm::vec3 axis(1.0f, 0.0f, 0.0f);
				if (!caps)
					modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), axis);
				else
					modelMatrix = glm::rotate(modelMatrix, glm::radians(-1.0f), axis);
			}
			break;
					
		case GLFW_KEY_A:
			{
				/*  change pitch, i.e. rotate about the object's local y axis   */
				glm::vec3 axis(0.0f, 1.0f, 0.0f);
				if (!caps)
					modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), axis);
				else
					modelMatrix = glm::rotate(modelMatrix, glm::radians(-1.0f), axis);
			}
			break;

		case GLFW_KEY_R:
		
		    /* reset the object's orientation to align with global coordinates */
			modelMatrix = glm::mat4();
			viewMatrix = glm::mat4();
			viewMatrix = glm::translate(viewMatrix, cameraTrans);

			break;

		case GLFW_KEY_I:
				dist += 1;
				break;
		case GLFW_KEY_K:
				dist -= 1;
				if (dist < 0)
				{
					dist = 0;
				}
				break;
		case GLFW_KEY_J:
				phi -= .1;
				if (phi < 0)
				{
					phi = 0;
				}
				break;
		case GLFW_KEY_L:
				phi += .1;
			if (glm::radians(phi) > glm::radians(3.14))
			{
				phi = 3.14;
			}
				break;
		case GLFW_KEY_U:
			theta -= .1;
			if (theta < 0)
			{
				theta = 0;
			}
			break;
		case GLFW_KEY_O:
			theta += .1;
			if (glm::radians(theta) > glm::radians(3.14 * 2))
			{
				theta = 3.14 * 2;
			}
			break;

		case GLFW_KEY_CAPS_LOCK:
			caps = !caps;
			break;
		
		case GLFW_KEY_SPACE:
			simulationActive = !simulationActive;
			break;

		default:
			break;
	}

	if (mods == GLFW_MOD_SHIFT)
		caps = !caps;

}


pe3::~pe3(void)
{
	glDeleteProgram(program);

	for (int i = 0; i < shaders.size(); i++)
		glDeleteShader(shaders[i]);
}


