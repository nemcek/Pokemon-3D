#version 150

in vec3 fragTexCoord;

out vec4 FragmentColor;

uniform samplerCube CubeMap;
uniform vec3 fogColor;

const float lowerLimit = 0.0;
const float upperLimit = 30.0;

void main() {
    vec4 finalColor = texture(CubeMap, fragTexCoord);

    float factor = (fragTexCoord.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);

    FragmentColor = mix(vec4(fogColor, 1.0), finalColor, factor);
//    FragmentColor = texture(CubeMap, fragTexCoord);
}