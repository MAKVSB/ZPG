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

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

out vec4 ex_worldPosition;
out vec3 ex_texturePosition;

void main () {
    mat4 modelMatrix = mat4(1);
    modelMatrix[3][0] = cameraPosition.x;
    modelMatrix[3][1] = cameraPosition.y;
    modelMatrix[3][2] = cameraPosition.z;
    ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0));
    ex_texturePosition = in_Position;
};