#version 150
// The inputs will be fed by the vertex buffer objects
in vec2 Position;
in vec2 TexCoord;

// This will be passed to the fragment shader
out vec2 fragTexCoord;

uniform mat4 ModelMatrix;

void main() {
  // Copy the input to the fragment shader
  fragTexCoord = vec2((Position.x + 1.0) / 2.0, (Position.y + 1.0) / 2.0);

  // Calculate the final position on screen
  // Note the visible portion of the screen is in <-1,1> range for x and y coordinates
  gl_Position = ModelMatrix * vec4(Position, 0.0, 1.0);
}
