#include "pe3.h"

pe3* program; 

void reshape(GLFWwindow* window, int width, int height)
{
    program->reshape(width, height);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	program->keyboard(key, scancode, action, mods);
}

void display(void)
{
    program->display();
}

void update(void)
{
	program->update();
}

int main(int argc, char** argv)
{
    //Initialize GLFW
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(500, 500, "PE3", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


    //Load OpenGL extensions!
	glewExperimental = GL_TRUE;
	glewInit();

    //Initialize our program
	program = new pe3(argc, argv);

	glfwSetWindowSizeCallback(window, reshape);
	glfwSetKeyCallback(window, keyboard);

	while (!glfwWindowShouldClose(window))
	{
		// Call to the update function; should always be before rendering.
		update();

		// Call the render function.
		display();

		// Swaps the back buffer to the front buffer
		// Remember, you're rendering to the back buffer, then once rendering is complete, you're moving the back buffer to the front so it can be displayed.
		glfwSwapBuffers(window);

		// Checks to see if any events are pending and then processes them.
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;

}
