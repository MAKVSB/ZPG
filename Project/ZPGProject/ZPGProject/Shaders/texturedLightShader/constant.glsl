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
uniform vec2 textureScaler;
uniform int textureSet;

void main(void) {
    if (textureSet == 0){
        out_Color = vec4(material.objectColor, 1.0);
        return;
    }
    out_Color = texture(textureUnitID, ex_texturePosition * textureScaler);
}
