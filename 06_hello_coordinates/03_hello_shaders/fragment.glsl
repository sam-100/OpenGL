#version 330 core
in vec3 outColor;

out vec4 FragColor;

uniform float colorFactor;

void main() {
    FragColor = vec4(outColor.x*colorFactor, outColor.y*colorFactor, outColor.z*colorFactor, 1.0f);
}