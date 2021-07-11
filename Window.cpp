#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";

// Objects to Render
Skybox * Window::skybox;
Sphere * Window::sphere;
Geometry * Window::torus;
Geometry * Window::plane;
std::vector<Geometry*> Window::horses = std::vector<Geometry*>(4);
std::vector<Geometry*> Window::birds = std::vector<Geometry*>(4);
std::vector<Geometry*> Window::cylinders = std::vector<Geometry*>(4);

Transform * Window::world;
Transform * Window::orbit;
 
std::vector<Transform*> Window::horseMoves = std::vector<Transform*>(4);
std::vector<Transform*> Window::cylinSyses = std::vector<Transform*>(4);
std::vector<Transform*> Window::birdOrbits = std::vector<Transform*>(4);

// Movement
float Window::x = 0;
bool Window::toggle1 = true;
bool Window::toggle2 = true;
bool Window::toggle3 = true;
bool Window::roToggle = false;

// Trackball
//bool Window::leftPress = false;
bool leftPress = false;
glm::vec3 Window::prevPos;

// Default filepath
std::string Window::directory = "/Users/ailsafan/Desktop/demo/demo2/obj/";

// Light
PointLight * Window::ptLight;
DirectionalLight * Window::dirLight;
SpotLight * Window::spotLight;
Light * currLight;

// Colors
Material * Window::emerald = new Material(glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568),
                           glm::vec3(0.633, 0.727811, 0.633), 0.6);
Material * Window::jade = new Material(glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63),
                        glm::vec3(0.316228, 0.316228, 0.316228), 0.1);
Material * Window::obsidian = new Material(glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525),
                            glm::vec3(0.332741, 0.328634, 0.346435), 0.3);
Material * Window::pearl = new Material(glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829),
                         glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
Material * Window::ruby = new Material(glm::vec3(0.1745, 0.01175, 0.01175), glm::vec3(0.61424, 0.04136, 0.04136),
                        glm::vec3(0.727811, 0.626959, 0.626959), 0.6);
Material * Window::turquoise = new Material(glm::vec3(0.1, 0.18725, 0.1745), glm::vec3(0.396, 0.74151, 0.69102),
                             glm::vec3(0.297254, 0.30829, 0.306678), 0.1);
Material * Window::brass = new Material(glm::vec3(0.329412, 0.223529, 0.027451), glm::vec3(0.780392, 0.568627, 0.113725),
                        glm::vec3(0.992157, 0.941176, 0.807843), 0.21794872);
Material * Window::bronze = new Material(glm::vec3(0.2125, 0.1275, 0.054), glm::vec3(0.714, 0.4284, 0.18144),
                          glm::vec3(0.393548, 0.271906, 0.166721), 0.2);
Material * Window::chrome = new Material(glm::vec3(0.25), glm::vec3(0.4), glm::vec3(0.774597), 0.6);
Material * Window::copper = new Material(glm::vec3(0.19125, 0.0735, 0.0225), glm::vec3(0.7038, 0.27048, 0.0828),
                          glm::vec3(0.256777, 0.137622, 0.086014), 0.1);
Material * Window::gold = new Material(glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648),
                        glm::vec3(0.628281, 0.555802, 0.366065), 0.4);
Material * Window::silver = new Material(glm::vec3(0.19225), glm::vec3(0.50754), glm::vec3(0.508273), 0.4);

// Cameras
Camera * currCam;
std::vector<Camera*> Window::cameras = std::vector<Camera*>(4);
std::vector<Transform*> Window::camCtrls = std::vector<Transform*>(4);

// Projection matrix:
glm::mat4 Window::projection;

// Shader Program ID
GLuint Window::phongShader;
GLuint Window::skyboxShader;
GLuint Window::basicShader;
GLuint Window::refShader;

bool Window::initializeProgram() {
    // Create a shader program with a vertex shader and a fragment shader.
    phongShader = LoadShaders("shaders/phongShader.vert", "shaders/phongShader.frag");
    skyboxShader = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
    //basicShader = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    refShader = LoadShaders("shaders/reflection.vert", "shaders/reflection.frag");

    // Check the shader program.
    if (!phongShader) {
        std::cerr << "Failed to initialize phong shader program" << std::endl;
        return false;
    }
    if (!skyboxShader) {
        std::cerr << "Failed to initialize skybox shader program" << std::endl;
        return false;
    }
    /*
    if (!basicShader) {
        std::cerr << "Failed to initialize basic shader program" << std::endl;
        return false;
    }
     */
    if (!refShader) {
        std::cerr << "Failed to initialize environment shader program" << std::endl;
        return false;
    }
    
    return true;
}

bool Window::initializeObjects() {    
    // Initialize lights
    ptLight = new PointLight(glm::vec3(1.f), glm::vec3(50, 0, 0), 0.04);
    dirLight = new DirectionalLight(glm::vec3(1.f), glm::vec3(-100, 100, 0));
    spotLight = new SpotLight(glm::vec3(1.f), glm::vec3(20, 0, 0), 0.01, 25.f, 30.f);
    currLight = spotLight;
    
    // Initialize cameras
    cameras[0] = new Camera(glm::vec3(200, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    cameras[1] = new Camera(glm::vec3(0, 75, 0), glm::vec3(-10, 75, 0), glm::vec3(0, 1, 0));
    cameras[2] = new Camera(glm::vec3(0, 20, 0), glm::vec3(-10, 20, 0), glm::vec3(0, 1, 0));
    cameras[3] = new Camera(glm::vec3(35, 5, 10), glm::vec3(0, 5, 10), glm::vec3(0, 1, 0));
    
    for (int i = 0; i < 4; ++i) {
        cameras[i]->setRefShader(refShader);
    }
    currCam = cameras[0];
    
    // Create the skybox
    skybox = new Skybox(1024.f);
    
    // Create objects
    sphere = new Sphere();
    sphere->setTexture(skybox->getTexture());
    sphere->setShader(refShader);
    
    torus = new Geometry(directory + "torus_lr.obj");
    
    for (int i = 0; i < 4; ++i) {
        horses[i] = new Geometry(directory + "horse.obj");
        birds[i] = new Geometry(directory + "bird2.obj");
        cylinders[i] = new Geometry(directory + "cylinder1.obj");
    }
    
    plane = new Geometry(directory + "cube1.obj");
    
    // Create transforms
    glm::mat4 model = glm::mat4(1);
    world = new Transform(model);
    orbit = new Transform(model);

    // Level 3 : birds
    model = glm::mat4(1);
    for (int i = 0; i < 4; ++i) {
        birdOrbits[i] = new Transform(model);
        birdOrbits[i]->addChild(birds[i]);
    }
    
    // Level 2 : birds and horses
    model = glm::translate(glm::mat4(1), glm::vec3(40.0f, 0.0f, 0.0f));
    cylinSyses[0] = new Transform(model);
    
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, -40.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
    cylinSyses[1] = new Transform(model);
    
    model = glm::translate(glm::mat4(1), glm::vec3(-40.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
    cylinSyses[2] = new Transform(model);
    
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 40.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    cylinSyses[3] = new Transform(model);

    model = glm::mat4(1);
    horseMoves[0] = new Transform(model);
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, -15.0f, 0.0f));
    horseMoves[1] = new Transform(model);
    model = glm::mat4(1);
    horseMoves[2] = new Transform(model);
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, 15.0f, 0.0f));
    horseMoves[3] = new Transform(model);
    
    for (int i = 0; i < 4; ++i) {
        horseMoves[i]->addChild(horses[i]);
        horseMoves[i]->addChild(birdOrbits[i]);
        cylinSyses[i]->addChild(horseMoves[i]);
        cylinSyses[i]->addChild(cylinders[i]);
    }
    
    // Level 1 : the orbit
    orbit->addChild(torus);
    orbit->addChild(plane);
    orbit->addChild(sphere);
    //orbit->addChild(ptLight);
    
    for (int i = 0; i < 4; ++i) {
        orbit->addChild(cylinSyses[i]);
    }
    
    // Cameras
    model = glm::mat4(1);
    camCtrls[0] = new Transform(model);
    camCtrls[1] = new Transform(model);
    model = glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camCtrls[2] = new Transform(model);
    model = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camCtrls[3] = new Transform(model);
    
    for (int i = 0; i < 4; ++i) {
        camCtrls[i]->addChild(cameras[i]);
    }
    
    world->addChild(orbit);
    world->addChild(camCtrls[0]);
    
    orbit->addChild(camCtrls[1]);
    
    horseMoves[0]->addChild(camCtrls[2]);
    
    birdOrbits[0]->addChild(camCtrls[3]);
    
    // Set colors for objects
    torus->setColor(pearl);

    for (int i = 0; i < 4; ++i) {
        //horses[i]->setColor(pearl);
        cylinders[i]->setColor(silver);
        birds[i]->setColor(obsidian);
    }

    horses[0]->setColor(turquoise);
    horses[1]->setColor(ruby);
    horses[2]->setColor(brass);
    horses[3]->setColor(bronze);
    
    plane->setColor(pearl);
    
    // Set initial models for objects
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, 48.0f, 0.0f));
    torus->update(glm::scale(model, glm::vec3(40, 15, 40)));
    
    model = glm::scale(glm::mat4(1), glm::vec3(2, 45, 2));
    for (int i = 0; i < 4; ++i) cylinders[i]->update(model);
    
    model = glm::scale(glm::mat4(1), glm::vec3(0.15));
    for (int i = 0; i < 4; ++i) horses[i]->update(model);
    
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, 5.0f, 30.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2));
    for (int i = 0; i < 4; ++i) birds[i]->update(model);
    birds[1]->update(glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    birds[2]->update(glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    birds[3]->update(glm::rotate(glm::mat4(1), glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, -45.0f, 0.0f));
    plane->update(glm::scale(model, glm::vec3(120, 1, 120)));
    
    model = glm::translate(glm::mat4(1), glm::vec3(0.0f, 55.0f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    sphere->update(glm::scale(model, glm::vec3(20)));
    
    return true;
}

void Window::cleanUp() {
    // Deallcoate the objects.
    delete world;

    // Delete the shader program.
    glDeleteProgram(phongShader);
    glDeleteProgram(skyboxShader);
    //glDeleteProgram(basicShader);
    glDeleteProgram(refShader);
}

GLFWwindow* Window::createWindow(int width, int height) {
    // Initialize GLFW.
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    // 4x antialiasing.
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    // Apple implements its own version of OpenGL and requires special treatments
    // to make it uses modern OpenGL.

    // Ensure that minimum OpenGL version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable forward compatibility and allow a modern OpenGL context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the GLFW window.
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

    // Check if the window could not be created.
    if (!window) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the context of the window.
    glfwMakeContextCurrent(window);

#ifndef __APPLE__
    // On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

    // Initialize GLEW.
    if (glewInit()) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return NULL;
    }
#endif
    
    // Set swap interval to 1.
    glfwSwapInterval(0);
    
    // Call the resize callback to make sure things get drawn immediately.
    Window::resizeCallback(window, width, height);
    
    return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height) {
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size.
    glViewport(0, 0, width, height);

    // Set the projection matrix.
    Window::projection = glm::perspective(glm::radians(60.0),
                                double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback() {
    if (toggle1) {
        orbit->update(glm::rotate(glm::mat4(1), glm::radians(-0.1f), glm::vec3(0, 1, 0)));
    }
    
    if (toggle2) {
        x += 0.01;
        float t1 = 0.15 * cos(x);
        float t2 = 0.15 * sin(x);
        horseMoves[0]->update(glm::translate(glm::mat4(1), glm::vec3(0, t1, 0)));
        horseMoves[1]->update(glm::translate(glm::mat4(1), glm::vec3(0, t2, 0)));
        horseMoves[2]->update(glm::translate(glm::mat4(1), glm::vec3(0, -t1, 0)));
        horseMoves[3]->update(glm::translate(glm::mat4(1), glm::vec3(0, -t2, 0)));
    }
    
    if (toggle3) {
        for (int i = 0; i < 4; ++i) {
            birdOrbits[i]->update(glm::rotate(glm::mat4(1), glm::radians(0.5f), glm::vec3(0, 1, 0)));
        }
    }
}

void Window::displayCallback(GLFWwindow* window) {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the objects
    skybox->draw(currCam->newView, projection, skyboxShader);
    currLight->draw(phongShader, glm::mat4(1));
    
    glUseProgram(phongShader);
    glUniformMatrix4fv(glGetUniformLocation(phongShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(phongShader, "view"), 1, GL_FALSE, glm::value_ptr(currCam->newView));
    glUniform3fv(glGetUniformLocation(phongShader, "viewPos"), 1, glm::value_ptr(currCam->newEyePos));

    glUseProgram(refShader);
    glUniformMatrix4fv(glGetUniformLocation(refShader, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(refShader, "view"), 1, false, glm::value_ptr(currCam->newView));
    glUniform3fv(glGetUniformLocation(refShader, "viewPos"), 1, glm::value_ptr(currCam->newEyePos));
    
    world->draw(phongShader, glm::mat4(1));
    
    glUseProgram(0);

    // Gets events, including input such as keyboard and mouse or window resizing
    glfwPollEvents();

    // Swap buffers.
    glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    const float cameraSpeed = 5.f;
    // Check for a key press.
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
                
                // Animation control
            case GLFW_KEY_1:
                toggle1 = !toggle1;
                break;
                
            case GLFW_KEY_2:
                toggle2 = !toggle2;
                break;
                
            case GLFW_KEY_3:
                toggle3 = !toggle3;
                break;
                
            case GLFW_KEY_RIGHT_ALT:
                roToggle = !roToggle;
                break;
                
            // Camera control    
            case GLFW_KEY_F1:
                currCam = cameras[0];
                break;
            
            case GLFW_KEY_F2:
                currCam = cameras[1];
                break;
                
            case GLFW_KEY_F3:
                currCam = cameras[2];
                break;
                
            case GLFW_KEY_F4:
                currCam = cameras[3];
                break;
                
            default:
                break;
        }
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        glm::mat4 model;
        switch (key) {
                // Camera movement
                // Move / Rotate up
            case GLFW_KEY_UP:
                if (!roToggle) {
                    currCam->setEyePos(currCam->getEyePos() + glm::vec3(0, cameraSpeed, 0));
                    currCam->setLookPos(currCam->getLookPos() + glm::vec3(0, cameraSpeed, 0));
                } else {
                    currCam->setEyePos(currCam->getEyePos() + glm::vec3(0, cameraSpeed, 0));
                }
                break;
                
                // Move / Rotate down
            case GLFW_KEY_DOWN:
                if (!roToggle) {
                    currCam->setEyePos(currCam->getEyePos() - glm::vec3(0, cameraSpeed, 0));
                    currCam->setLookPos(currCam->getLookPos() - glm::vec3(0, cameraSpeed, 0));
                } else {
                    currCam->setEyePos(currCam->getEyePos() - glm::vec3(0, cameraSpeed, 0));
                }
                break;
                
                // Move / Rotate left
            case GLFW_KEY_LEFT:
                if (!roToggle) {
                    currCam->setEyePos(currCam->getEyePos() + glm::vec3(0, 0, cameraSpeed));
                    currCam->setLookPos(currCam->getLookPos() + glm::vec3(0, 0, cameraSpeed));
                } else {
                    glm::vec3 eye = currCam->getEyePos();
                    model = glm::rotate(glm::mat4(1), glm::radians(cameraSpeed), currCam->getUpVec());
                    currCam->setLookPos(eye + glm::vec3(model * glm::vec4(currCam->getLookPos() - eye, 0)));
                }
                break;
                
                // Move / Rotate right
            case GLFW_KEY_RIGHT:
                if (!roToggle) {
                    currCam->setEyePos(currCam->getEyePos() - glm::vec3(0, 0, cameraSpeed));
                    currCam->setLookPos(currCam->getLookPos() - glm::vec3(0, 0, cameraSpeed));
                } else {
                    glm::vec3 eye = currCam->getEyePos();
                    model = glm::rotate(glm::mat4(1), glm::radians(-cameraSpeed), currCam->getUpVec());
                    currCam->setLookPos(eye + glm::vec3(model * glm::vec4(currCam->getLookPos() - eye, 0)));
                }
                break;
                
                // Move in
            case GLFW_KEY_COMMA:
                currCam->setEyePos(currCam->getEyePos() - glm::vec3(cameraSpeed, 0, 0));
                currCam->setLookPos(currCam->getLookPos() - glm::vec3(cameraSpeed, 0, 0));
                break;
                
                // Move out
            case GLFW_KEY_PERIOD:
                currCam->setEyePos(currCam->getEyePos() + glm::vec3(cameraSpeed, 0, 0));
                currCam->setLookPos(currCam->getLookPos() + glm::vec3(cameraSpeed, 0, 0));
                break;
                
            case GLFW_KEY_P:
                currLight = ptLight;
                break;
                
            case GLFW_KEY_D:
                currLight = dirLight;
                break;
                
            case GLFW_KEY_S:
                currLight = spotLight;
                break;
                
            default:
                break;
        }
    }
}

/**
 * Detect the left-button of the mouse being depressed.
 * Keep track of the last known mouse position (mapped to the hemi-sphere).
 */
void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        leftPress = true;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        // Map the mouse position to a logical sphere location.
        prevPos = trackBallMapping(window, x, y);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftPress = false;
    }
}

/**
 * Treat the mouse position as the projection of a point on the hemi-sphere down to the image plane (along the z-axis),
 * and determine that point on the hemi-sphere.
 */
glm::vec3 Window::trackBallMapping(GLFWwindow* window, double xPos, double yPos) {
    // Mapping
    glm::vec3 v;
    // !!! currWidth != Window::width
    int currWidth, currHeight;
    glfwGetWindowSize(window, &currWidth, &currHeight);
    v.x = (2.0 * xPos - currWidth) / currWidth;
    v.y = (currHeight - 2.0 * yPos) / currHeight;
    v.z = 0.0;
    float d = glm::length(v);
    d = (d < 1.0) ? d : 1.0;
    v.z = sqrtf(1.001 - d * d);
    glm::normalize(v); // Still need to normalize, since we only capped d, not v.
    return v;
}
 
/**
 * Detect the mouse movements and update the display.
 */
void Window::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
    if (leftPress) {
        // Detect the mouse movement
        glm::vec3 currPos = trackBallMapping(window, xPos, yPos); // Map the mouse position to a logical
        glm::vec3 direction = currPos - prevPos;
        float velocity = glm::length(direction);
        // If little movement - do nothing.
        if(velocity > 0.0001) {
            // Determine the great circle connecting the old and the current mouse-hemi-sphere point.
            // Calculate the normal to this plane. This will be the axis about which to rotate.
            glm::vec3 rotAxis = glm::cross(prevPos, currPos);
            float rotAngle = velocity * 2;
            //ptBall->rotateObj(rotAngle, rotAxis);
            currLight->rotate(rotAngle, rotAxis);
        }
        prevPos = currPos;
    }
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    glm::vec3 trans;
    GLfloat multiLt = 1 + 0.1 * yoffset;
    glm::vec3 pos = currLight->getPos();
    trans = glm::vec3(glm::scale(glm::mat4(1), glm::vec3(multiLt)) * glm::vec4(pos, 1.0));
    //ptBall->translate(trans);
    currLight->setPos(trans);
    //ptBall->scale(multiObj);
}
