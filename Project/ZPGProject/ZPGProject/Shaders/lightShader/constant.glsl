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

struct Material {
    vec3 r_a;
    vec3 r_d;
    vec3 r_s;
    vec3 objectColor;
};
uniform Material material;

void main(void){
    out_Color = vec4(material.objectColor, 1.0);
}

