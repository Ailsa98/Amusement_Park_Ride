#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Node.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Material.h"

class Geometry : public Node {
private:
	std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;
    std::vector<glm::ivec2> uvs;
    bool hasTexture = false;
    
    // color
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    
    glm::mat4 model;
    glm::mat4 newModel;
    
    GLfloat minX = std::numeric_limits<GLfloat>::max();
    GLfloat maxX = std::numeric_limits<GLfloat>::min();
    GLfloat minY = std::numeric_limits<GLfloat>::max();
    GLfloat maxY = std::numeric_limits<GLfloat>::min();
    GLfloat minZ = std::numeric_limits<GLfloat>::max();
    GLfloat maxZ = std::numeric_limits<GLfloat>::min();
    glm::vec3 center;
    
    GLfloat maxDist = std::numeric_limits<GLfloat>::min();

	GLuint VAO, VBO1, VBO2, EBO;


public:
    Geometry(){ return; };
	Geometry(std::string objFilename);
	~Geometry();
	
    void draw(GLuint shaderProgram, glm::mat4 C);
    void update(glm::mat4 C);
    void setColor(Material*& color);
};


#endif
