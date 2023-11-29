#version 420
#define MAX_LIGHTS          100

struct LightStruct {
    vec3 position;
    vec3 direction;
	vec3 color;
    vec3 attenuation; // x = constant, y = linear, z = quadratic;
    float offset1;
    float lightType;
    float lightStrength;
    float cutoff;
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

uniform vec3 cameraPosition;

struct Material {
    vec3 r_a;
    vec3 r_d;
    vec3 r_s;
    vec3 objectColor;
};
uniform Material material;

layout(std140, binding = 0) uniform LightArray {
    float lightsCount;
    LightStruct lights[MAX_LIGHTS];
};

//
// helper methods
//

float degreesToFloat(float inputAngle) {
    return ((360 - inputAngle) / 180) -1;
}

vec3 vec4toVec3(vec4 inputVec) {
    return inputVec.xyz / inputVec.w;
}

float calculateAttenuation(LightStruct light) {
    // Define attenuation factors
    float constant = light.attenuation.x;
    float linear = light.attenuation.y;
    float quadratic = light.attenuation.z;

    float dist = length(light.position - vec4toVec3(ex_worldPosition));
    return clamp(1.0 / (constant + linear * dist + quadratic * dist * dist), 0.0, 1.0);
}

//
// main methods
//

vec3 ambientLight(LightStruct light) {
    vec3 ambient = material.r_a * light.color * 0.1;
    return material.objectColor * ambient;
}

vec3 pointLight(LightStruct light) {
    //generic calculations
    vec3 lightVector = normalize(light.position - ex_worldPosition.xyz/ex_worldPosition.w);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w);
    vec3 halfDir = normalize(lightVector + viewDir);
    vec3 normalVector = normalize(ex_worldNormal);
    float dotProduct = dot(lightVector, ex_worldNormal);
    float attenuation = calculateAttenuation(light);

    float specStrength = pow(max(dot(halfDir, normalVector), 0.0), light.lightStrength);
    // Check if the light is hitting the back side of the surface
    if (dotProduct < 0.0) {
        specStrength = 0.0;
    }

    //light partials calculations
    vec3 specular = vec3(specStrength) * material.r_s;

    vec3 diffuse = max(dotProduct, 0.0) * material.r_d;

    return (diffuse + specular) * material.objectColor * light.color * attenuation;
}

vec3 directionalLight(LightStruct light) {
    //generic calculations
    vec3 lightVector = normalize(light.direction);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w);
    vec3 halfDir = normalize(lightVector + viewDir);
    vec3 normalVector = normalize(ex_worldNormal);
    float dotProduct = dot(lightVector, ex_worldNormal);

    float specStrength = pow(max(dot(halfDir, normalVector), 0.0), light.lightStrength);
    // Check if the light is hitting the back side of the surface
    if (dotProduct < 0.0) {
        specStrength = 0.0;
    }

    //light partials calculations
    vec3 specular = vec3(specStrength) * material.r_s;

    vec3 diffuse = max(dotProduct, 0.0) * material.r_d;

    return (diffuse + specular) * material.objectColor * light.color;
}

vec3 spotlightLight(LightStruct light) {
    vec3 lightVector = normalize(light.position - vec4toVec3(ex_worldPosition));

    float theta = dot(lightVector, normalize(-light.direction));

    if (theta <= degreesToFloat(light.cutoff)) {
        return vec3(0.0, 0.0, 0.0);
    }

    float smoothFactor = 1 - smoothstep(degreesToFloat(light.cutoff - 8.01f), degreesToFloat(light.cutoff), theta);

    return pointLight(light) * smoothFactor;
}

void main(void) {
    vec3 outColor = vec3(0);
    for (int i = 0; i < lightsCount; i++){
        if (lights[i].lightType == 0){  // AMBIENT
            outColor += ambientLight(lights[i]);
        } else if (lights[i].lightType == 1){  // POINT
            outColor += pointLight(lights[i]);
        } else if (lights[i].lightType == 2){  // DIRECTIONAL
            outColor += directionalLight(lights[i]);
        } else if (lights[i].lightType == 3){  // SPOTLIGHT
            outColor += spotlightLight(lights[i]);
        }
    }
    out_Color = vec4(outColor, 1);
}
