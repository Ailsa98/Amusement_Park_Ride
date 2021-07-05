#ifndef _NODE_H_
#define _NODE_H_

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Node {
    
public:
    virtual ~Node(){};
    virtual void draw(GLuint shaderProgram, glm::mat4 C) = 0;
    virtual void update(glm::mat4 C) = 0;
};


#endif
