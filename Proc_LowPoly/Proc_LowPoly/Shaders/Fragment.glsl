
#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 pos;  
void main()
{
	
	vec3 ec_normal = normalize(cross(dFdx(pos), dFdy(pos)));
	vec3 light_dir=vec3(0.0,0.85,0.85);
	float d=dot(light_dir,ec_normal);
	vec4 Color = vec4(d,d,d,1.0);
    FragColor = vec4(ourColor, 1.0)*Color;
}