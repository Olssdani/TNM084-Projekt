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

//Function declaration
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
//Camera
Camera camera(glm::vec3(0.0f, 50.0f, 10.0f));

//Mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// time
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{	
	//Set random time
	srand(time(NULL));

	// initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window and get the monitor size
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(primary);
	GLFWwindow* window;
	
	//Goes into fullscreen if the the mode variable isn't null
	if (mode == NULL)
	{
		window = glfwCreateWindow(mode->width, mode->height, "Low Poly World", primary, NULL);
		SCR_WIDTH = mode->width;
		SCR_HEIGHT = mode->height;
	}
	else {
		window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "Low Poly World", NULL, NULL);
	}

	
	//Check if a window is created
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	//Set window and callback functions.
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	
	// Disable the mouse and capture it
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//Print out information about GPU
	printf("GL vendor:       %s\n", glGetString(GL_VENDOR));
	printf("GL renderer:     %s\n", glGetString(GL_RENDERER));
	printf("GL version:      %s\n", glGetString(GL_VERSION));
	printf("Desktop size:    %d x %d pixels\n", mode->width, mode->height);

	//Objects
	//Set size of ground
	int groundSize = 150;
	//Water and ground
	Ground ground(groundSize, 150);
	
	Water water(groundSize,200);
	//Render out a height map (Works but not as it supposed to)
	ground.RenderHeight(MAP, MAP);
	
	/*
	Initialize the grass  
	*/
	std::vector<Fern> grass(50);
	//Loop over all the grass models and place them out
	for (int i = 0; i < grass.size(); i++)
	{
		//Random a position
		float x = groundSize * ((float)rand() / RAND_MAX);
		float y = groundSize * ((float)rand() / RAND_MAX);
		grass[i].SetTranslation(glm::vec3(x, ground.data[(int)x*(int)y]*ground.max, y));

		//Random a rotation
		float r =360*((float)rand() / RAND_MAX);
		grass[i].SetRotation(glm::vec3(0.0, 1.0, 0.0), D2R * r);

		//Random a scale
		float s = 0.05 + 0.1*((float)rand() / RAND_MAX);
		grass[i].SetScale(glm::vec3(s, s, s));
		
	}
	/*
	Initialize the trees
	*/

	std::vector<Tree> trees;
	trees.resize(50);

	//Loop over and place out trees
	for (int i = 0; i < trees.size(); i++)
	{
		//Random a position
		float x = (groundSize * ((float)rand() / RAND_MAX));
		float y = (groundSize * ((float)rand() / RAND_MAX));
		//Get a random nummer to check against the noise
		float Tree_Value = pow((float)rand() / RAND_MAX,2);
		//Get the noise value in the position
		float Noise_Value = (noise3(x / groundSize, y / groundSize, 0.5)+1.0)*0.5;
	
		//If the Tree value is higher than the noise value try a new position.
		//Noise_Value must be over 0.2 because of the brute force nature of the 
		//algoritm a threeshold must be sett otherwise the desired output isn't optained.
		if (Noise_Value <0.2 || Tree_Value >Noise_Value)
		{
			i--;
		}
		else {
			//Set the tree to the postion then rotate and scale it.
			trees[i].SetTranslation(glm::vec3(x, ground.data[(int)x*(int)y] * ground.max, y));
			trees[i].x = x;
			trees[i].y = y;
			//rotation
			float r = 360 * ((float)rand() / RAND_MAX);
			trees[i].SetRotation(glm::vec3(0.0, 1.0, 0.0), D2R * r);
			//Scale
			float s = 0.2 + 0.3*((float)rand() / RAND_MAX);
			trees[i].SetScale(glm::vec3(s, s, s));
		}
	}


	//Enable some opengl things
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	/*
		Render loop
	*/
	while (!glfwWindowShouldClose(window))
	{
		//Update delta time
		updateTime();
		
		/*
			Get Input
		*/
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			//Gte input for ground
			process_Ground(window, ground);
			//Update trees position
			/*for (int i = 0; i < trees.size(); i++)
			{
				trees[i].SetTranslation(glm::vec3(trees[i].x, (ground.data[(int)trees[i].x *(int)trees[i].y]*200.0f)-100.0f, trees[i].y));
			}*/
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			//Get input for water
			process_Water(window, water);
		}
		else
		{
			//Get rest of the inputs
			processInput(window);
		}


		//Update shaders
		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			ground.UpdateShader();
			water.UpdateShader();
			for (int i = 0; i < grass.size(); i++)
			{
				grass[i].UpdateShader();
			}
			for (int i = 0; i < trees.size(); i++)
			{
				trees[i].UpdateShader();
			}
			std::cout << "New Shader loaded" << std::endl;
		}	
		
		
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Get the current projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		//Get the current view matrix;
		glm::mat4 view = camera.View();
		ground.Render(projection, view);
		water.Render(projection, view);
		for (int i = 0; i < grass.size(); i++)
		{
			grass[i].Render(projection, view);
		}
		for (int i = 0; i < trees.size(); i++)
		{
			trees[i].Render(projection, view);
		}
		
		
		//Show fps
		displayFPS(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
//Get all inputs for ground
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

//Get all inputs for water
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
	//Close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Move camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.RIGHT, deltaTime);


	//Toggle wireframe or solid
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


//Get mouse movement
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

//scroll input
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

//Get delta time
void updateTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
//Display framrate
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
