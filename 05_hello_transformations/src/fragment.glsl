#version 330 core
in vec4 outColor;
in vec2 TexCord;

out vec4 fragColor;

uniform float colorFactor;
uniform sampler2D texContainer;
uniform sampler2D texFace;

void main() {
    fragColor = mix(texture(texContainer, TexCord), texture(texFace, TexCord), 0.3);
}
