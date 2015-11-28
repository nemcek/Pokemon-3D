#version 150
// A texture is expected as program attribute
uniform sampler2D Texture;
uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float reflectivity;
uniform float shineDamper;
uniform vec3 skyColor;

// The vertex shader fill feed this input
in vec2 fragTexCoord;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

// The final color
out vec4 FragmentColor;

void main() {

  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitToCameraVector = normalize(toCameraVector);

  vec3 totalDiffuse = vec3(0.0);
  vec3 totalSpecular = vec3(0.0);

  for (int i = 0; i < 4; i++) {

    // distance from light
    float distance = length(toLightVector[i]);
    float attenuationFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);

    // normalized vector pointing to light
    vec3 unitLight = normalize(toLightVector[i]);

    // dot product and brightness of light calculation
    float dotProd = dot(unitNormal, unitLight);
    float brightness = max(dotProd, 0.0);

    // direction of light (from light)
    vec3 lightDirection = -unitLight;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(reflectedLightDirection, unitToCameraVector);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);

    // sum
    totalDiffuse = totalDiffuse +  (brightness * lightColor[i]) / attenuationFactor;
    totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColor[i]) / attenuationFactor;
  }

  totalDiffuse = max(totalDiffuse, 0.2);

  // Lookup the color in Texture on coordinates given by fragTexCoord
  FragmentColor = vec4(totalDiffuse, 1.0) * texture(Texture, fragTexCoord) + vec4(totalSpecular, 1.0);
  FragmentColor = mix(vec4(skyColor, 1.0), FragmentColor, visibility);
}
