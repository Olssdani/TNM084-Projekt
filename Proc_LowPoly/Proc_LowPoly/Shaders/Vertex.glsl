#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
  
out vec3 ourColor; // output a color to the fragment shader
out vec3 pos;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
 
	pos = (view * vec4(aPos, 1.0)).xyz;
    if(aPos.y >20.0)
    {
    	 ourColor = vec3(1.0, 1.0,1.0); 
    }else{
    	ourColor = vec3(0.0, 1.0,0.0); 
    }
   // set ourColor to the input color we got from the vertex data
}  