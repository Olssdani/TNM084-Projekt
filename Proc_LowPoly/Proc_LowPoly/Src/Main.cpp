#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "Camera/Camera.h"
#include "Models/Ground.h"
#include "Models/Water.h"
#include "L-System\L_System2D.h"
#include "Models\Fern.h"
#include "Utilities.h"
#include "L-System\L_System3D.h"
#include "Models\Tree.h"
//#include <vld.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_Ground(GLFWwindow *window, Ground &ground);
void process_Water(GLFWwindow *window, Water &water);
double displayFPS(GLFWwindow *window);

void updateTime();

// settings
unsigned int SCR_WIDTH = 900;
unsigned int SCR_HEIGHT = 900;
unsigned int MAP = 150;
Camera camera(glm::vec3(0.0f, 50.0f, 10.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{	
	//Set random time
	srand(time(NULL));
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	// glfw window creation
	// --------------------
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(primary);
	GLFWwindow* window;
	if (mode != NULL)
	{
		window = glfwCreateWindow(mode->width, mode->height, "Low Poly World", primary, NULL);
	}
	else {
		window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "Low Poly World", NULL, NULL);
	}

	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	printf("GL vendor:       %s\n", glGetString(GL_VENDOR));
	printf("GL renderer:     %s\n", glGetString(GL_RENDERER));
	printf("GL version:      %s\n", glGetString(GL_VERSION));
	printf("Desktop size:    %d x %d pixels\n", mode->width, mode->height);

	//Objects
	int groundSize = 150;
	Ground ground(groundSize, 50);
	Water water(groundSize,100);
	std::vector<Fern> ferns(1);
	ground.RenderHeight(MAP, MAP);
	//for (int i = 0; i < ferns.size(); i++)
	//{
	//	float x = groundSize * ((float)rand() / RAND_MAX);
	//	float y = groundSize * ((float)rand() / RAND_MAX);
	//	ferns[i].SetTranslation(glm::vec3(x, ground.data[(int)x*(int)y]*ground.max, y));

	//	float r =360*((float)rand() / RAND_MAX);
	//	ferns[i].SetRotation(glm::vec3(0.0, 1.0, 0.0), D2R * r);

	//	float s = 0.05 + 0.2*((float)rand() / RAND_MAX);
	//	ferns[i].SetScale(glm::vec3(s, s, s));
	//	
	//}
	//Fern fern;
	std::vector<Tree> trees(20);
	float min =1.0f;
	float max = 0.0f;
	for (int i = 0; i < trees.size(); i++)
	{
		float x = (groundSize * ((float)rand() / RAND_MAX));
		float y = (groundSize * ((float)rand() / RAND_MAX));
		float Tree_Placement = pow((float)rand() / RAND_MAX,2);
		float Place_noise = (noise3(x / groundSize, y / groundSize, 0.5)+1.0)*0.5;
		if (min > Place_noise)
		{
			min = Place_noise;
		}
		if (max < Place_noise)
		{
			max = Place_noise;
		}

		
		if ( Place_noise <0.2 || Tree_Placement >Place_noise )
		{
			i--;
		}
		else {

			trees[i].SetTranslation(glm::vec3(x, ground.data[(int)x*(int)y] * ground.max, y));
			trees[i].x = x;
			trees[i].y = y;
			float r = 360 * ((float)rand() / RAND_MAX);
			trees[i].SetRotation(glm::vec3(0.0, 1.0, 0.0), D2R * r);

			float s = 0.2 + 0.3*((float)rand() / RAND_MAX);
			trees[i].SetScale(glm::vec3(s, s, s));
		}

		//std::cout << i << std::endl;
	}

	std::cout << "Max: " << max << " Min: " << min << std::endl;
	
	
	Tree tree(8, 1.0);



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// render loop
	// -----------
	
	while (!glfwWindowShouldClose(window))
	{
		//Update delta time
		updateTime();
		
		//Get input
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			process_Ground(window, ground);
			for (int i = 0; i < trees.size(); i++)
			{
				trees[i].SetTranslation(glm::vec3(trees[i].x, ground.data[(int)trees[i].x *(int)trees[i].y] * ground.max, trees[i].y));
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			process_Water(window, water);
		}
		else
		{
			processInput(window);
		}


	
		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			ground.UpdateShader();
			water.UpdateShader();
			for (int i = 0; i < ferns.size(); i++)
			{

				ferns[i].UpdateShader();
			}
			for (int i = 0; i < trees.size(); i++)
			{

				trees[i].UpdateShader();
			}
			tree.UpdateShader();
			std::cout << "New Shader loaded" << std::endl;
		}	
		
		
		// rende//r
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Get the current projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		//Get the current view matrix;
		glm::mat4 view = camera.View();
		//ground.Render(projection, view);
		//water.Render(projection, view);
		for (int i = 0; i < ferns.size(); i++)
		{
			ferns[i].Render(projection, view);
		}
		for (int i = 0; i < trees.size(); i++)
		{
			//trees[i].Render(projection, view);

		}
		
		
		//Show fps
		displayFPS(window);
		//std::cout << SCR_HEIGHT << " " << SCR_WIDTH << std::endl;
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void process_Ground(GLFWwindow *window, Ground &ground)
{
	
	//Big Noise
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		ground.SetMountainNoise(glm::vec3(0.01, 0.0, 0.0));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ground.SetMountainNoise(glm::vec3(-0.01, 0.0, 0.0));
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ground.SetMountainNoise(glm::vec3(0.0, 0.01, 0.0));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ground.SetMountainNoise(glm::vec3(0.0, -0.01, 0.0));

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		ground.SetMountainNoise(glm::vec3(0.0, 0.0, 0.01));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		ground.SetMountainNoise(glm::vec3(0.0, 0.0, -0.01));

	//Small Noise
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ground.SetGroundNoise(glm::vec3(0.01, 0.0, 0.0));
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		ground.SetGroundNoise(glm::vec3(-0.01, 0.0, 0.0));

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		ground.SetGroundNoise(glm::vec3(0.0, 0.01, 0.0));
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		ground.SetGroundNoise(glm::vec3(0.0, -0.01, 0.0));

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		ground.SetGroundNoise(glm::vec3(0.0, 0.0, 0.01));
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		ground.SetGroundNoise(glm::vec3(0.0, 0.0, -0.01));
		//Height
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		ground.SetGroundHeight(glm::vec2(0.2, 0.0));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ground.SetGroundHeight(glm::vec2(-0.2, 0.0));
	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ground.SetGroundHeight(glm::vec2(0.0, 0.2));
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ground.SetGroundHeight(glm::vec2(0.0, -0.2));
		

	//Small height
	if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
		ground.SetSmallHeight(0.2f);
	if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
		ground.SetSmallHeight(-0.2f);
	ground.RenderHeight(MAP, MAP);
	
}


void process_Water(GLFWwindow *window, Water &water)
{

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		water.WaterHeight(0.1f);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		water.WaterHeight(-0.1f);

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	SCR_HEIGHT = height;
	SCR_WIDTH = width;
	glViewport(0, 0, width, height);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.RIGHT, deltaTime);

	//Water height



	//Toggle wireframe or solid
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void updateTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
double displayFPS(GLFWwindow *window) {

	static double t0 = 0.0;
	static int frames = 0;
	double fps = 0.0;
	double frametime = 0.0;
	static char titlestring[200];

	double t;

	// Get current time
	t = glfwGetTime();  // Gets number of seconds since glfwInit()
						// If one second has passed, or if this is the very first frame
	if ((t - t0) > 1.0 || frames == 0)
	{
		fps = (double)frames / (t - t0);
		if (frames > 0) frametime = 1000.0 * (t - t0) / frames;
		sprintf(titlestring, "TNM046, %.2f ms/frame (%.1f FPS)", frametime, fps);
		glfwSetWindowTitle(window, titlestring);
		// printf("Speed: %.1f FPS\n", fps);
		t0 = t;
		frames = 0;
	}
	frames++;
	return fps;
}
