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
    vec3 objectColor = vec3(0.285, 0.647, 0.812);

    vec3 ambient = vec3(0.5) * lightColor;
    out_Color = vec4(ambient * objectColor, 1.0);
}

