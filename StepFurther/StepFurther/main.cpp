#include "Include/glad/gl.h"
#include "Include/GLFW/glfw3.h"
#include <cstdio>
#include "scene.h"

#pragma comment (lib, "glfw3.lib") 

bool is_rotating_view = false;
Scene scene;
double xpos, ypos;

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		is_rotating_view = true;
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		is_rotating_view = false;
	}
}

static void CursorMoveCallback(GLFWwindow* window, double curr_xpos, double curr_ypos) {
		if (is_rotating_view) {
			fprintf(stdout, "moving......\n");
			scene.OnMouseMove(curr_xpos - xpos, curr_ypos - ypos);
		} 		
		xpos = curr_xpos;
		ypos = curr_ypos;
}

void ErrorCallback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} 
	if (action == GLFW_PRESS) {
		scene.OnKeyDown(key);
	} else if (action == GLFW_RELEASE) {
		scene.OnKeyUp(key);
	}
}

int main(void) {
	int default_viewport_width = 1200;
	int default_viewport_height = 800;
	GLFWwindow* window;

	glfwSetErrorCallback(ErrorCallback);
	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(default_viewport_width, default_viewport_height, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorMoveCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0) {
		printf("Failed to initialize OpenGL context\n");
		return -1;
	}
	scene.SetViewPortSize(default_viewport_width * 1.0f, default_viewport_height * 1.0f);

	scene.Init();

	// Successfully loaded OpenGL
	printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	// #############################
	//POINT original_pos;

	// #############################

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// do something...
		scene.UpdateScene();
		scene.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

