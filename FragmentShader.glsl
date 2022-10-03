#version 330

uniform vec3 triangleColor;
in vec4 vColor;
out vec4 color;

void main(){
	color = vColor;
}