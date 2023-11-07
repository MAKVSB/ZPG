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

uniform vec3 cameraPosition;

out vec4 ex_worldPosition;

void main () {
    ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0));
};