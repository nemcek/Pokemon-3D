#version 150

in vec3 Position;
in vec3 TexCoord;

out vec3 fragTexCoord;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

void main() {
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Position, 1.0);
    fragTexCoord = TexCoord;
}