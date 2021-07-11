#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <vector>

#include "main.h"
#include "shader.h"
#include "Skybox.h"
#include "Transform.h"
#include "Geometry.h"
#include "Sphere.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Camera.h"

class Window {
public:
	// Window Properties
	static int width;
	static int height;
	static const char* windowTitle;

	// Objects to Render
    static Skybox* skybox;
    static Sphere* sphere;
    static Geometry * torus;
    static Geometry * plane;
    static std::vector<Geometry*> horses;
    static std::vector<Geometry*> birds;
    static std::vector<Geometry*> cylinders;
    
    // Transforms
    static Transform * world;
    static Transform * orbit;
    static std::vector<Transform*> horseMoves;
    static std::vector<Transform*> cylinSyses;
    static std::vector<Transform*> birdOrbits;
    
    // Movement
    static float x;
    static bool toggle1;
    static bool toggle2;
    static bool toggle3;
    static bool roToggle;
    
    // Trackball
    //static bool leftPress;
    static glm::vec3 prevPos;
    
    // Color
    static Material * pearl;
    static Material * obsidian;
    static Material * jade;
    static Material * bronze;
    static Material * emerald;
    static Material * ruby;
    static Material * turquoise;
    static Material * brass;
    static Material * chrome;
    static Material * copper;
    static Material * gold;
    static Material * silver;
    
    // Light
    static PointLight * ptLight;
    static DirectionalLight * dirLight;
    static SpotLight * spotLight;
    
    // Projection matrix:
    static glm::mat4 projection;
    
    // Camera
    static std::vector<Camera*> cameras;
    static std::vector<Transform*> camCtrls;
    
    // Filepath
    static std::string directory;
    
	// Shader Program ID
	static GLuint phongShader;
    static GLuint basicShader;
    static GLuint skyboxShader;
    static GLuint refShader;

	// Constructors and Destructors
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();

	// Window functions
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);

	// Draw and Update functions
	static void idleCallback();
	static void displayCallback(GLFWwindow*);

	// Callbacks
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static glm::vec3 trackBallMapping(GLFWwindow* window, double xPos, double yPos);
    static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
