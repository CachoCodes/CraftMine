#version 330 core
#extension GL_ARB_bindless_texture : require

out vec4 FragColor;

in vec2 TexCoord;

/*
uniform int Type;
uniform vec3 water_tone;
uniform vec3 natural_tone;
*/
uniform sampler2D Texture;

void main(){
    FragColor = texture(Texture, TexCoord);
}