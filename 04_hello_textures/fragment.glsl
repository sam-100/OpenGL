#version 330 core
in vec4 outColor;

out vec4 FragColor;

uniform float colorFactor;

void main() {
    FragColor = vec4(outColor.rgb*colorFactor, 1.0f);
}
