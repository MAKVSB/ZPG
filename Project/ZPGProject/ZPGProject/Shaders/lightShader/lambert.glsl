/**
 * @file lightShader/fragment.glsl
 *
 * @brief Lambert shader
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

void main(void){
    //temporary constants
    vec3 lightColor = vec3(1, 1, 1);
    vec3 lightPosition = vec3(0.0,0.0,0.0);
    vec3 objectColor = vec3(0.285, 0.647, 0.812);

    //attenuation
    // Define attenuation factors
    float constant = 1.0;
    float linear = 0.36;
    float quadratic = 0.256;

    float dist = length(lightPosition - ex_worldPosition.xyz / ex_worldPosition.w);
    float attenuation = 1.0 / (constant + linear * dist + quadratic * dist * dist);
    lightColor = lightColor * attenuation;

    //generic calculations
    vec3 lightVector = lightPosition - ex_worldPosition.xyz;

    float diff = max(dot(normalize(lightVector), normalize(ex_worldNormal)),0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambient = vec3(0.1) * lightColor;
    out_Color = vec4((ambient + diffuse) * objectColor, 1.0);
}

