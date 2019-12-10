#include "window.h"
#include "Include/glad/gl.h"
#include "Include/GLFW/glfw3.h"
//#define IMGUI_DISABLE_INCLUDE_IMCONFIG_H
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"
#define NOMINMAX
#include "gui/imgui_filedialog.h"
#include <algorithm>
#include <iostream>


using namespace zjl;

GLFWwindow* window; 
bool my_tool_active;

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		is_rotating_view = true;
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		is_rotating_view = false;
	}
}

void WindowSizeCallback(GLFWwindow* window, int width, int height) {
	scene.SetViewPortSize(width - toolset_region_width, height);
	current_viewport_height = height;
	current_viewport_width = width;
}

void CursorMoveCallback(GLFWwindow* window, double curr_xpos, double curr_ypos) {
	if (is_rotating_view) {
		// fprintf(stdout, "moving......\n");
		scene.OnMouseMove(curr_xpos - xpos, curr_ypos - ypos);
	} 		
	xpos = curr_xpos;
	ypos = curr_ypos;
}

void ErrorCallback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} 
	if (action == GLFW_PRESS) {
		scene.OnKeyDown(key);
	} else if (action == GLFW_RELEASE) {
		scene.OnKeyUp(key);
	}
}

static bool InitImGui(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImFontConfig config;
	config.OversampleH = 5;
	config.OversampleV = 5;
	ImFont* font = io.Fonts->AddFontFromFileTTF("ProggyClean.ttf",
		13.0f, &config);

	ImGui::SetNextWindowPos(ImVec2(default_viewport_width - toolset_region_width, 0));
	ImGui::SetNextWindowSize(ImVec2(toolset_region_width, default_viewport_height));
	// New IMGUI frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();
	return true;
}

static void DrawGuiComponents() {
	// ....
	int current_item = 1;
	const char* items[] = { "abc", "def", "ffff", "0000", "????" };
	bool tt1;
	bool tt2;
	bool tt3;

	// New IMGUI frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(current_viewport_width - toolset_region_width, 0));
	ImGui::SetNextWindowSize(ImVec2(std::max(1.0f, toolset_region_width * 1.0f - 1), current_viewport_height));
	ImGui::Begin("GUI", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open", "Ctrl+O")) { 
				/* Do stuff */ 

				//FILE* fp = fopen("trimesh.vert", "r");
				//std::cout << "##########################" << std::endl;
				//std::cout << "current dir: " << GetCurrentWorkingDir() << std::endl;
				//if (fp == nullptr) {
				//	std::cout << "cannot find trimesh.vert............." << std::endl;
				//} else {
				//	std::cout << "succeed in finding trimesh.vert............." << std::endl;
				//}
				auto file_str = ImGui::file_dialog_open();
				SetCurrentWorkingDir(current_working_directory);
				//fp = fopen("trimesh.vert", "r");
				//std::cout << "##########################" << std::endl;
				//std::cout << "current dir: " << GetCurrentWorkingDir() << std::endl;
				//if (fp == nullptr) {
				//	std::cout << "cannot find trimesh.vert............." << std::endl;
				//} else {
				//	std::cout << "succeed in finding trimesh.vert............." << std::endl;
				//}
				scene.LoadModel(file_str);
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	//ImGuiWindowFlags_;
	ImGui::BeginChild(ImGui::GetID("GUIddd"), ImVec2(toolset_region_width - 1.0, 80), ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar);
	ImGui::Checkbox("hell1", &tt1);
	ImGui::Checkbox("hell2", &tt2);
	ImGui::Checkbox("hell3", &tt3);
	ImGui::Checkbox("hell4", &tt3);
	ImGui::Checkbox("hell5", &tt3);
	ImGui::Checkbox("hell6", &tt3);
	ImGui::EndChild();
	//ImGui::ListBoxHeader("ModelName");
	//ImGui::ListBox("Models", &current_item, items, 5);
	//ImGui::ListBoxFooter();
	ImGui::Checkbox("BoundingBox", &scene.GetOption().show_bbox_); 
	ImGui::LabelText("FrameTime", "%.3f s", frame_time);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

int zjl::ShowWindow() {
	glfwSetErrorCallback(ErrorCallback);
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_SAMPLES, 4);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(default_viewport_width, default_viewport_height, "Hello", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorMoveCallback);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0) {
		printf("Failed to initialize OpenGL context\n");
		return -1;
	}
	// Successfully loaded OpenGL
	printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	scene.SetViewPortSize(default_viewport_width * 1.0f - toolset_region_width, default_viewport_height * 1.0f);
	scene.Init();
	current_working_directory = GetCurrentWorkingDir();

	if (!InitImGui(window)) {
		printf("Failed to initialize ImGUI\n");
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// do something...
		scene.UpdateScene();
		scene.Draw();
		frame_time = scene.GetDeltaTime();

		glEnable(GL_SCISSOR_TEST);
		glScissor(current_viewport_width - toolset_region_width, 0, toolset_region_width, current_viewport_height);
		glClearColor(0.9f, 0.9f, 0.9f, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
		glClear(GL_COLOR_BUFFER_BIT );
		glDisable(GL_SCISSOR_TEST);

		DrawGuiComponents();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
