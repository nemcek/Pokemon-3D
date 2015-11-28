#version 150
// A texture is expected as program attribute
uniform sampler2D BackgroundTexture;
uniform sampler2D RTexture;
uniform sampler2D GTexture;
uniform sampler2D BTexture;
uniform sampler2D BlendMap;

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

  vec4 blendMapColor = texture(BlendMap, fragTexCoord);

  float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
  vec2 tiledCoords = fragTexCoord * 80.0;
  vec4 backgroundTextureColor = texture(BackgroundTexture, tiledCoords) * backTextureAmount;
  vec4 rTextureColor = texture(RTexture, tiledCoords) * blendMapColor.r;
  vec4 gTextureColor = texture(GTexture, tiledCoords) * blendMapColor.g;
  vec4 bTextureColor = texture(BTexture, tiledCoords) * blendMapColor.b;

  vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;

  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitToCameraVector = normalize(toCameraVector);

  vec3 totalDiffuse = vec3(0.0);
  vec3 totalSpecular = vec3(0.0);

  for (int i = 0; i < 4; i++) {
    float distance = length(toLightVector[i]);
    float attenuationFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);

    vec3 unitLight = normalize(toLightVector[i]);

    float dotProd = dot(unitNormal, unitLight);
    float brightness = max(dotProd, 0.0);

    vec3 lightDirection = -unitLight;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(reflectedLightDirection, unitToCameraVector);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);

    totalDiffuse = totalDiffuse +  (brightness * lightColor[i]) / attenuationFactor;
    totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColor[i]) / attenuationFactor;
  }

  totalDiffuse = max(totalDiffuse, 0.2);

  // Lookup the color in Texture on coordinates given by fragTexCoord
  FragmentColor = vec4(totalDiffuse, 1.0) * totalColor + vec4(totalSpecular, 1.0);
  FragmentColor = mix(vec4(skyColor, 1.0), FragmentColor, visibility);
}