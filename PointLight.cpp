#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, glm::vec3 pos, float atten) : attenuation(atten) {
    // Initializer list: Member initializer 'lightColor' does not name a non-static data member or base class
    lightColor = color;
    lightPosition = pos;
}

PointLight::~PointLight() {
    
}

void PointLight::draw(GLuint shaderProgram, glm::mat4 C) {
    glm::vec3 newPos = glm::vec3(C * glm::vec4(lightPosition, 1.0));
    glUseProgram(shaderProgram);
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.lightCol"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.lightPos"), 1, glm::value_ptr(newPos));
    glUniform1f(glGetUniformLocation(shaderProgram, "light.attenuation"), attenuation);
    glUniform1i(glGetUniformLocation(shaderProgram, "lightSource"), 0);
    glUseProgram(0);
}
