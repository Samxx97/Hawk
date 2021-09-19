#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoords;

uniform mat4 u_VP;
uniform mat4 u_Transform;
out vec2 v_TextureCoords;

void main()
{	
	v_TextureCoords = a_TextureCoords;
	gl_Position = u_VP * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

uniform vec4 u_Color;
in vec2 v_TextureCoords;
uniform sampler2D u_Texture;

void main()
{	
	
	gl_FragColor = texture(u_Texture, v_TextureCoords);

}