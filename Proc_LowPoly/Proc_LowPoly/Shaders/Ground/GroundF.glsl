
#version 330 core
out vec4 FragColor;  
in vec3 ourColorG;
in vec3 posG;  
in vec3 NormalG;
void main()
{
	//My own flat shading with calculated normals from geometry shader
	vec3 LightPos = vec3(0.0,50.0,0.0);
	vec3 Lightdir = normalize(LightPos-posG);
	//Dot product between normal an light direction
	float intensity = max(0.1,dot(Lightdir, NormalG));


	FragColor = vec4(intensity*ourColorG,1.0);



	

	//Fake flat shading without knowing the normals. Took it from https://www.opengl.org/discussion_boards/showthread.php/190731-help-with-flat-shading
	/*vec3 ec_normal = normalize(cross(dFdx(posG), dFdy(posG)));
	vec3 light_dir=vec3(0.0,0.85,0.85);
	float d=dot(light_dir,ec_normal);
	vec4 Color = vec4(d,d,d,1.0);
    FragColor = vec4(ourColorG, 1.0)*Color;*/
}