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

in vec2 ex_texturePosition;
uniform sampler2D textureUnitID;

void main(void){
    out_Color = texture(textureUnitID, ex_texturePosition);
}
