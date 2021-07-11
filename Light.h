#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Node.h"

class Light : public Node {
protected:
    glm::vec3 lightColor;
    glm::vec3 lightPosition;
    
public:
    ~Light(){};

    virtual void draw(GLuint shaderProgram, glm::mat4 C) = 0;
    virtual void update(glm::mat4 C) { lightPosition = glm::vec3(C * glm::vec4(lightPosition, 1.0)); };
    void rotate(float rotAngle, glm::vec3 rotAxis) {
        lightPosition = glm::vec3(glm::rotate(glm::mat4(1.0), rotAngle, rotAxis) * glm::vec4(lightPosition, 1.0));
    };
    virtual glm::vec3 getPos(){ return lightPosition; };
    virtual void setPos(glm::vec3 pos){ lightPosition = pos; };
};

#endif
