#version 430 core

out vec4 fColor;

in vec2 vTextureCoord;
in vec4 wPosition;
in vec4 oPosition;
in vec4 wNormal;
in vec4 vColor;

uniform sampler2D sampler;
uniform samplerCube samplerC;
uniform int surface_effect;
uniform vec3 camera_position;
uniform vec4 diffuse_color;
// light
uniform vec4 ambient_light;
uniform vec4 specular_light;
uniform vec4 diffuse_light;
uniform vec4 light_position;

// material
uniform vec4 ambient_color;
uniform vec4 specular_color;
uniform float specular_shininess;
uniform float specular_strength;

void main()
{
    vec4 materialColor;   
    if(surface_effect == 0) {
        materialColor = diffuse_color * texture(sampler, vTextureCoord);
    } else if(surface_effect == 1) {
        materialColor = texture(sampler, vTextureCoord);
    } else if(surface_effect == 2) {
        materialColor = diffuse_color;
    } else if(surface_effect == 3){
        materialColor = diffuse_color * vColor;
    }else if(surface_effect == 4) {
        materialColor = texture(samplerC, oPosition.xyz);
    } else if(surface_effect == 5){
        vec3 rfl = reflect(wPosition.xyz-camera_position, normalize(wNormal.xyz));
        materialColor = texture(samplerC, rfl) * vec4(.9);
    }else {
        materialColor = vColor;
    }
    vec3 light_direction = wPosition.xyz - light_position.xyz;
    vec3 vnn = normalize(wNormal.xyz);
    float diffuse_factor = max(0.0, dot(vnn, -normalize(light_direction)));
    vec3 half_vector = normalize(normalize(-light_direction) - normalize(wPosition.xyz-camera_position.xyz));
    float specular_factor = max(0.0, dot(vnn, half_vector));
    if (diffuse_factor == 0.0) specular_factor = 0.0;
    else specular_factor = pow(specular_factor, specular_shininess) * specular_strength;
    vec4 ambient_component = materialColor * ambient_light;
    vec4 diffuse_component = diffuse_factor * materialColor * diffuse_light;
    vec4 specular_component = specular_factor * specular_color * specular_light;
    vec4 total = ambient_component + diffuse_component + specular_component;

    fColor = vec4(total.rgb, 1.0);
}
