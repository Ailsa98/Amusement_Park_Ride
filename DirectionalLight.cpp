#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 dir) {
    lightColor = color;
    lightPosition = dir;
}

DirectionalLight::~DirectionalLight() {
    
}

void DirectionalLight::draw(GLuint shader, glm::mat4 C) {
    glm::vec3 newDir = glm::vec3(C * glm::vec4(lightPosition, 1.0));
    glUseProgram(shader);
    glUniform3fv(glGetUniformLocation(shader, "light.lightCol"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shader, "light.lightPos"), 1, glm::value_ptr(newDir));
    glUniform1i(glGetUniformLocation(shader, "lightSource"), 1);
    glUseProgram(0);
}
