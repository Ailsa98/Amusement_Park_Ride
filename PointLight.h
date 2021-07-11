#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Light.h"

class PointLight : public Light {
private:
    float attenuation;
    
    /*
    glm::vec3 attenuation;
    // float constant;
    // float linear;
    // float quadratic;
     */
    
public:
    PointLight(glm::vec3 color, glm::vec3 pos, float atten);
    ~PointLight();

    void draw(GLuint shaderProgram, glm::mat4 C);
};

#endif
