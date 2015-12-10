#version 150
// The inputs will be fed by the vertex buffer objects
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

// This will be passed to the fragment shader
out vec2 fragTexCoord;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out float visibility;

// Matrices as program attributes
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 lightPosition[4];
uniform float useFakeLighting;

const float density = 0.0035;
const float gradient = 5;

void main() {
  // Copy the input to the fragment shader
  fragTexCoord = vec2(TexCoord);

  vec4 worldPosition = ModelMatrix * vec4(Position, 1.0);
  vec4 positionRelativeToCamera = ViewMatrix * worldPosition;

  // Calculate the final position on screen
  gl_Position = ProjectionMatrix * positionRelativeToCamera;

  vec3 actualNormal = Normal;

  if (useFakeLighting > 0.5) {
    actualNormal = vec3(0.0, 1.0, 0.0);
  }

  surfaceNormal = (ModelMatrix * vec4(actualNormal, 0.0)).xyz;

  for (int i = 0; i < 4; i++) {
    toLightVector[i] = lightPosition[i] - worldPosition.xyz;
  }

  toCameraVector = (inverse(ViewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

  float distance = length(positionRelativeToCamera.xyz);
  visibility = exp(-pow((distance * density), gradient));
  visibility = clamp(visibility, 0.0, 1.0);
}
