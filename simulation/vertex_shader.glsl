
#version 430 core

in vec4 bColor;
in vec4 bPosition;
in vec2 bTextureCoord;
in vec4 bNormal;

uniform mat4 transform;
uniform mat4 m_transform;
uniform mat4 n_transform;

out vec4 vColor;
out vec2 vTextureCoord;
out vec4 wPosition;
out vec4 oPosition;
out vec4 wNormal;

void
main()
{
    oPosition = bPosition;
    wPosition = m_transform * bPosition;
    wNormal = n_transform * bNormal;
    vColor = bColor;
    vTextureCoord = bTextureCoord;
    gl_Position = transform * bPosition;
}
