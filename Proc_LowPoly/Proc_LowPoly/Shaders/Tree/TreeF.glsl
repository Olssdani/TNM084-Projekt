
#version 330 core
out vec4 FragColor;  
in vec3 ourColorG;
in vec3 posG;  
in vec3 NormalG;

void main()
{
	//My own flat shading with calculated normals from geometry shader
	vec3 LightPos = vec3(10.0,50.0,10.0);
	vec3 Lightdir = normalize(LightPos-posG);
	//Dot product between normal an light direction
	float intensity = max(0.2,dot(Lightdir, NormalG));


	FragColor = vec4(intensity *ourColorG,1.0);


}