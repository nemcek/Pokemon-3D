#version 150
// A texture is expected as program attribute
uniform sampler2D Texture;
uniform vec3 lightColor;
uniform vec3 skyColor;

// The vertex shader fill feed this input
in vec2 fragTexCoord;
in vec3 surfaceNormal;
in vec3 toLightVector;
in float visibility;

// The final color
out vec4 FragmentColor;

void main() {

  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitLight = normalize(toLightVector);

  float dotProd = dot(unitNormal, unitLight);
  float brightness = max(dotProd, 0.0);
  vec3 diffuse = brightness * lightColor;

  // Lookup the color in Texture on coordinates given by fragTexCoord
  FragmentColor = vec4(diffuse, 1.0) * texture(Texture, fragTexCoord);
  FragmentColor = mix(vec4(skyColor, 1.0), FragmentColor, visibility);
}
