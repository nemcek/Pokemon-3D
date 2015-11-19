#version 150
// A texture is expected as program attribute
uniform sampler2D Texture;
uniform vec3 lightColor;
uniform float reflectivity;
uniform float shineDamper;
uniform vec3 skyColor;

// The vertex shader fill feed this input
in vec2 fragTexCoord;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

// The final color
out vec4 FragmentColor;

void main() {

  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitLight = normalize(toLightVector);

  float dotProd = dot(unitNormal, unitLight);
  float brightness = max(dotProd, 0.0);
  vec3 diffuse = brightness * lightColor;

  vec3 unitToCameraVector = normalize(toCameraVector);
  vec3 lightDirection = -unitLight;
  vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

  float specularFactor = dot(reflectedLightDirection, unitToCameraVector);
  specularFactor = max(specularFactor, 0.0);
  float dampedFactor = pow(specularFactor, shineDamper);

  vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

  // Lookup the color in Texture on coordinates given by fragTexCoord
  FragmentColor = vec4(diffuse, 1.0) * texture(Texture, fragTexCoord) + vec4(finalSpecular, 1.0);
  FragmentColor = mix(vec4(skyColor, 1.0), FragmentColor, visibility);
}
