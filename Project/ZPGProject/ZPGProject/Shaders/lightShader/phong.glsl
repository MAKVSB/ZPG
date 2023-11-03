/**
 * @file lightShader/fragment.glsl
 *
 * @brief Phong shader
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#version 420
#define MAX_LIGHTS          10

struct LightStruct {
    vec3 position;
    vec3 direction;
	vec3 color;
    vec3 attenuation;
    float lightType;
    float lightStrength;
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

uniform vec3 cameraPosition;

layout(std140, binding = 1) uniform Material {
    vec3 r_a;
    vec3 r_d;
    vec3 r_s;
};

layout(std140, binding = 0) uniform LightArray {
    LightStruct lights[MAX_LIGHTS];
};

void main(void) {
    //temporary constants
    vec3 lightColor = lights[0].color;
    vec3 lightPosition = lights[0].position;
    vec3 objectColor = vec3(0.285, 0.647, 0.812);

    //attenuation
    // Define attenuation factors
    float constant = lights[0].attenuation.x;
    float linear = lights[0].attenuation.y;
    float quadratic = lights[0].attenuation.z;

    float dist = length(lightPosition - ex_worldPosition.xyz / ex_worldPosition.w);
    float attenuation = clamp(1.0 / (constant + linear * dist + quadratic * dist * dist), 0.0, 1.0);

    //generic calculations
    vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz/ex_worldPosition.w);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w);
    vec3 reflectDir = reflect(-lightVector, ex_worldNormal);
    float dotProduct = dot(lightVector, ex_worldNormal);

    float specStrength = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // Check if the light is hitting the back side of the surface
    if (dotProduct < 0.0) {
        specStrength = 0.0;
    }
    vec3 specular = vec3(specStrength) * r_s * lightColor * attenuation;

    float diff = max(dotProduct, 0.0);
    vec3 diffuse = max(dotProduct, 0.0) * r_d * lightColor * attenuation;

    vec3 ambient = vec3(0.1) * r_a * lightColor;

    out_Color = vec4((ambient + diffuse + specular) * objectColor, 1.0);
}
