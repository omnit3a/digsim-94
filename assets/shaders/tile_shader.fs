#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

out vec4 finalColor;

void main() {
    vec4 texel = texture(texture0, fragTexCoord);

    if (texel.rgb == vec3(1.0f, 0.0f, 1.0f))
    {
    finalColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    else
    {
    finalColor = vec4(texel.rgb, 1.0f);
    }
}