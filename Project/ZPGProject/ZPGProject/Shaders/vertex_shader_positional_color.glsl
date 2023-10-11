#version 330

layout(location=0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 fragColor;

void main () {
    mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
    gl_Position = MVP * vec4(vp, 1.0);
    fragColor = modelMatrix * vec4(vp, 1.0);
};