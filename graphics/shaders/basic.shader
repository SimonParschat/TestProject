#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normalScale;

out vec2 v_Texcoord;
out vec3 v_NormalScale;


uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

void main()
{
    v_NormalScale = normalScale;
    v_Texcoord =  texcoord;
    gl_Position = projectionMat * viewMat * modelMat * position;
}


#shader fragment
#version 330 core 

layout(location = 0) out vec4 ColorOut;
in vec2 v_Texcoord;
in vec3 v_NormalScale;

uniform sampler2D ourTexture;

vec3 grassColor = vec3(0.1,0.7,0.2);
uniform vec3 u_LightDirection;

void main()
{
    //vec4 tex = texture(ourTexture, TexCoord);
    //ColorOut = vec4( grassColor * dot( u_LightDirection, v_NormalScale ), 1.0 );
    ColorOut = texture(ourTexture, v_Texcoord);
}
