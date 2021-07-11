#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 color, glm::vec3 pos, float atten, float innerCut, float outerCut) : attenuation(atten), innerCutOff(innerCut), outerCutOff(outerCut){
    // Initializer list: Member initializer 'lightColor' does not name a non-static data member or base class
    lightColor = color;
    lightPosition = pos;
}

SpotLight::~SpotLight() {
    
}

void SpotLight::draw(GLuint shaderProgram, glm::mat4 C) {
    glm::vec3 newPos = glm::vec3(C * glm::vec4(lightPosition, 1.0));
    glUseProgram(shaderProgram);
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.lightCol"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.lightPos"), 1, glm::value_ptr(newPos));
    glUniform1f(glGetUniformLocation(shaderProgram, "light.attenuation"), attenuation);
    glUniform1f(glGetUniformLocation(shaderProgram, "light.innerCutOff"), glm::cos(glm::radians(innerCutOff)));
    glUniform1f(glGetUniformLocation(shaderProgram, "light.outerCutOff"), glm::cos(glm::radians(outerCutOff)));
    glUniform1i(glGetUniformLocation(shaderProgram, "lightSource"), 2);
    glUseProgram(0);
}
