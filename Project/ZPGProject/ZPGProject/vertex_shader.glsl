#version 330

layout(location=0) in vec4 vp;
layout(location=1) in vec4 color; 
out vec4 fragColor;

void main () {
     gl_Position = vp;
     fragColor = color;
};