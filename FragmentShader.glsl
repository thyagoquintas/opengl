#version 330

uniform vec3 triangleColor;
uniform sampler2D theTexture;
in vec4 vColor;
in vec2 TexCord;
out vec4 color;

void main(){
	color = texture(theTexture, TexCord);
}