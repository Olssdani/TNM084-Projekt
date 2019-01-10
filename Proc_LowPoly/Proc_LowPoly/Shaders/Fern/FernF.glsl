
#version 330 core
out vec4 FragColor;  
in vec3 posG;  
in vec3 NormalG;
void main()
{
	//My own flat shading with calculated normals from geometry shader
	vec3 LightPos = vec3(0.0,50.0,0.0);
	vec3 Lightdir = normalize(LightPos-posG);
	//Dot product between normal an light direction
	float intensity = max(0.2,dot(Lightdir, NormalG));


	FragColor = vec4(intensity*vec3(0.0,1.0,0.0),1.0);


}