#version 330 core
// This is a sample fragment shader.

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 lightPos;
    vec3 lightCol;
    float attenuation;
    // vec3 attenuation;
};

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 fragNormal;
in vec3 fragPos;

uniform PointLight light;
uniform Material material;
uniform vec3 viewPos;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main() {
    vec3 objColor;
    
    // Ambient
    vec3 ambient = light.lightCol * material.ambient;

    // Diffuse
    vec3 lightDir = normalize(light.lightPos - fragPos);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * light.lightCol;

    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.lightCol * (spec * material.specular);

    // Attenuation
    float dist = length(light.lightPos - fragPos);
    /*
    float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * distance +
                               light.attenuation.z * (distance * distance));
     */
    float attenuation = 1.0f / light.attenuation / dist;

    objColor = attenuation * (ambient + diffuse + specular);

    // Use the color passed in. An alpha of 1.0f means it is not transparent.
    fragColor = vec4(objColor, 1.0f);
}
