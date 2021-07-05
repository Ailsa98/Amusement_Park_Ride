#include "Camera.h"

Camera::Camera(glm::vec3 eye, glm::vec3 look, glm::vec3 up) : eyePos(eye), lookAtPoint(look), upVector(up){
    view = glm::lookAt(eyePos, lookAtPoint, upVector);
    newEyePos = eyePos;
    newLookPos = lookAtPoint;
    newView = view;
}

Camera::~Camera() {
    
}

void Camera::draw(GLuint shaderProgram, glm::mat4 C) {
    newEyePos = glm::vec3(C * glm::vec4(eyePos, 1));
    newLookPos = glm::vec3(C * glm::vec4(lookAtPoint, 1));
    newView = glm::lookAt(newEyePos, newLookPos, glm::vec3(0, 1, 0));
    /*
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, false, glm::value_ptr(newView));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(newEyePos));
    glUseProgram(refShader);
    glUniformMatrix4fv(glGetUniformLocation(refShader, "view"), 1, false, glm::value_ptr(newView));
    glUniform3fv(glGetUniformLocation(refShader, "viewPos"), 1, glm::value_ptr(newEyePos));
    glUseProgram(0);
     */
}
