/**
 * @file lightShader/vertex.glsl
 *
 * @brief Lambert shader
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;

void main () {
    ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
    mat4 normalMatrix = modelMatrix; //temporary
    ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * in_Normal);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
};