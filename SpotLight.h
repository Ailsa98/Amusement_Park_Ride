#ifndef _SPOT_LIGHT_H_
#define _SPOT_LIGHT_H_

#include "Light.h"

class SpotLight : public Light {
private:
    float innerCutOff;
    float outerCutOff;
    float attenuation;
    
public:
    SpotLight(glm::vec3 color, glm::vec3 pos, float atten, float innerCut, float outerCut);
    ~SpotLight();

    void draw(GLuint shaderProgram, glm::mat4 C);
};

#endif
