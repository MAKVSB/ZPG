#version 330

layout(location=0) in vec4 vp;
out vec4 fragColor;

void main () {
     gl_Position = vp;
     fragColor = vp;
};