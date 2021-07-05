#include "Geometry.h"

Geometry::Geometry(std::string objFilename) {
    std::ifstream objFile(objFilename); // The obj file we are reading.
    
    std::vector<glm::vec3> pointsTemp;
    std::vector<glm::vec3> pointsNormalTemp;
    std::vector<glm::vec2> uvsTemp;
    std::vector<glm::ivec3> facesTemp;
    std::vector<glm::ivec3> facesNormalTemp;
    std::vector<glm::ivec3> facesUVTemp;
    
    // Check whether the file can be opened.
    if (objFile.is_open()) {
        std::string line; // A line in the file.
        // Read lines from the file.
        while (std::getline(objFile, line)) {
            // Turn the line into a string stream for processing.
            std::stringstream ss;
            ss << line;
            // Read the first word of the line.
            std::string label;
            ss >> label;
            // If the line is about vertex (starting with a "v").
            if (label == "v") {
                // Read the later three float numbers and use them as the // coordinates.
                glm::vec3 point;
                ss >> point.x >> point.y >> point.z;
                // Process the point. For example, you can save it to a.
                pointsTemp.push_back(point);
            }
            
            // 'vn' lines to load normals
            if (label == "vn") {
                glm::vec3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                pointsNormalTemp.push_back(normal);
            }
            
            // 'vt' lines to load texture vertices
            else if (label == "vt") {
                hasTexture = true;
                glm::vec3 uv;
                ss >> uv.x >> uv.y;
                uvsTemp.push_back(uv);
                //std::cout << "VT!!! " << objFilename << endl;
            }
            
            
            // 'f' lines to load triangles
            if (label == "f") {
                glm::ivec3 face;
                glm::ivec3 faceUV;
                glm::ivec3 faceNormal;
                
                std::string extra;
                
                char delimiter;
                
                // Load for v1//vn1 v2//vn2 v3//vn3
                if (!hasTexture) {
                    ss >> face.x >> delimiter >> delimiter >> faceNormal.x;
                    ss >> face.y >> delimiter >> delimiter >> faceNormal.y;
                    ss >> face.z >> delimiter >> delimiter >> faceNormal.z;
                    
                    face.x--;
                    face.y--;
                    face.z--;
                    faceNormal.x--;
                    faceNormal.y--;
                    faceNormal.z--;
                    facesTemp.push_back(face);
                    facesNormalTemp.push_back(faceNormal);
                    
                    ss >> extra;
                    
                    // Load for quads
                    if (extra != ""){
                        std::stringstream s;
                        s << extra;
                        glm::ivec3 face2;
                        glm::ivec3 faceNormal2;
                        s >> face2.z >> delimiter >> delimiter >> faceNormal2.z;
                        
                        face2.x = face.x;
                        face2.y = face.z;
                        
                        faceNormal2.x = faceNormal.x;
                        faceNormal2.y = faceNormal.z;
                        
                        face2.z--;
                        faceNormal2.z--;
                        
                        facesTemp.push_back(face2);
                        facesNormalTemp.push_back(faceNormal2);
                    }
                }
                else {
                    //std::cout << "has Texture" << endl;
                    ss >> face.x >> delimiter >> faceUV.x >> delimiter >> faceNormal.x;
                    ss >> face.y >> delimiter >> faceUV.y >> delimiter >> faceNormal.y;
                    ss >> face.z >> delimiter >> faceUV.z >> delimiter >> faceNormal.z;
                    
                    // Change index from 1~n to 0~n-1
                    face.x--;
                    face.y--;
                    face.z--;
                    faceUV.x--;
                    faceUV.y--;
                    faceUV.z--;
                    faceNormal.x--;
                    faceNormal.y--;
                    faceNormal.z--;
                    facesTemp.push_back(face);
                    facesUVTemp.push_back(faceUV);
                    facesNormalTemp.push_back(faceNormal);
                    
                    ss >> extra;
                    
                    // Load for quads v4/uv4/vn4
                    if (extra != "") {
                        std::stringstream s;
                        s << extra;
                        glm::ivec3 face2;
                        glm::ivec3 faceUV2;
                        glm::ivec3 faceNormal2;
                        s >> face2.z >> delimiter >> faceUV2.z >> delimiter >> faceNormal2.z;
                        
                        face2.x = face.x;
                        face2.y = face.z;
                        
                        faceUV2.x = faceUV.x;
                        faceUV2.y = faceUV.z;
                        
                        faceNormal2.x = faceNormal.x;
                        faceNormal2.y = faceNormal.z;
                        
                        face2.z--;
                        faceUV2.z--;
                        faceNormal2.z--;
                        
                        facesTemp.push_back(face2);
                        facesUVTemp.push_back(faceUV2);
                        facesNormalTemp.push_back(faceNormal2);
                    }
                }
            }
        }
    }
    else {
        std::cerr << "Can't open the file " << objFilename << std::endl;
    }
    objFile.close();
    
    
    /*
     * Section 4, you will need to normalize the object to fit in the
     * screen.
     */
    for (int i = 0; i < facesTemp.size(); i++) {
        glm::ivec3 tempFace;
        points.push_back(pointsTemp[facesTemp[i].x]);
        points.push_back(pointsTemp[facesTemp[i].y]);
        points.push_back(pointsTemp[facesTemp[i].z]);
        
        if (hasTexture) {
            uvs.push_back(uvsTemp[facesUVTemp[i].x]);
            uvs.push_back(uvsTemp[facesUVTemp[i].y]);
            uvs.push_back(uvsTemp[facesUVTemp[i].z]);
        }
        
        normals.push_back(pointsNormalTemp[facesNormalTemp[i].x]);
        normals.push_back(pointsNormalTemp[facesNormalTemp[i].y]);
        normals.push_back(pointsNormalTemp[facesNormalTemp[i].z]);
        
        tempFace.x = 3 * i;
        tempFace.y = 3 * i + 1;
        tempFace.z = 3 * i + 2;
        
        faces.push_back(tempFace);
    }
    
    // Find max and min points
    for (int i = 0; i < points.size(); i++){
        if (points[i].x > maxX)
            maxX = points[i].x;
        if (points[i].x < minX)
            minX = points[i].x;
        if (points[i].y > maxY)
            maxY = points[i].y;
        if (points[i].y < minY)
            minY = points[i].y;
        if (points[i].z > maxZ)
            maxZ = points[i].z;
        if (points[i].z < minZ)
            minZ = points[i].z;
    }
    
    // Find center
    GLfloat centerX = (GLfloat)(minX + maxX) / 2.0f;
    GLfloat centerY = (GLfloat)(minY + maxY) / 2.0f;
    GLfloat centerZ = (GLfloat)(minZ + maxZ) / 2.0f;
    center = glm::vec3(centerX, centerY, centerZ);
    
    // Set new coordinates
    for (int i = 0; i < points.size(); i++) {
        GLfloat newX = points[i].x - center.x;
        GLfloat newY = points[i].y - center.y;
        GLfloat newZ = points[i].z - center.z;
        points[i] = glm::vec3(newX, newY, newZ);
    }
    
    // Find maximum distance from the center
    for (int i = 0; i < points.size(); i++) {
        GLfloat dist = sqrt(pow(points[i].x, 2) + pow(points[i].y, 2) + pow(points[i].z, 2));
        if (dist > maxDist){
            maxDist = dist;
        }
    }
    
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    
    // Generate a Vertex Array (VAO), Vertex Buffer Object (VBO) and Element Buffer Object (EBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);
    
    // Bind VAO
    glBindVertexArray(VAO);
    
    // Bind VBO to the bound VAO, and store the point data
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    
    // Enable Vertex Attribute 0 to pass point data through to the shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * faces.size(), faces.data(), GL_STATIC_DRAW);
    
    // Bind VBO2, and store the normal data
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
    
    // Enable Vertex Attribute 1 to pass point data through to the shader
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Unbind the VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Geometry::~Geometry() {
    // Delete the VBO, VAO and EBO.
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Geometry::draw(GLuint shaderProgram, glm::mat4 C) {
    // Actiavte the shader program
    glUseProgram(shaderProgram);
    
    newModel = C * model;
    
    // Get the shader variable locations and send the uniform data to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(newModel));
    glUniform3fv(glGetUniformLocation(shaderProgram, "material.ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shaderProgram, "material.diffuse"), 1, glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shaderProgram, "material.specular"), 1, glm::value_ptr(specular));
    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), shininess);
    
    // Bind the VAO
    glBindVertexArray(VAO);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Draw the faces
    glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
    
    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}

void Geometry::update(glm::mat4 C) {
    model = C * model;
}

void Geometry::setColor(Material*& color) {
    ambient = color->ambient;
    diffuse = color->diffuse;
    specular = color->specular;
    shininess = color->shininess;
}
