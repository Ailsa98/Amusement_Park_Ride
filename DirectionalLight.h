#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "Light.h"

class DirectionalLight : public Light {
    
public:
    DirectionalLight(glm::vec3 color, glm::vec3 dir);
    ~DirectionalLight();

    void draw(GLuint shader, glm::mat4 C);
};

#endif
