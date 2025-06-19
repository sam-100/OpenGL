#version 330 core
in vec4 outColor;
in vec2 TexCord;

out vec4 FragColor;

uniform float colorFactor;
uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, TexCord);
}
