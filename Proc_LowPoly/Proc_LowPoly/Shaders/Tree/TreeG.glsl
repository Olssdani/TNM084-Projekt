#version 150
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 pos[3];
in vec3 ourColor[3];
out vec3 ourColorG;
out vec3 posG;
out vec3 NormalG;
void main()
{
	//Find the edges on the triangle
	vec3 LV = pos[1]-pos[0];
	vec3 RV = pos[2]-pos[0];

	//Take the cross product between the edges to find the normal
	vec3 Normal = normalize(cross(LV,RV));

	//Send to the fragment shader
	for(int i = 0; i < gl_in.length(); i++)
	{
	 	gl_Position = gl_in[i].gl_Position;
	 	ourColorG = ourColor[i];
	 	NormalG = Normal;
	 	posG = pos[i];
	 	EmitVertex();
	}
	EndPrimitive();
}