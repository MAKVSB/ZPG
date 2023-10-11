#version 330

in vec4 fragColor;
out vec4 frag_colour;

void main () {
     frag_colour = (fragColor/2)+0.5f;
}