#version 430


layout(triangles) in;

layout(line_strip, max_vertices = 18) out;

uniform mat4 MVP;



in mat3 tbnMatrix[];



out vec3 vertcolor;

void main()
{
float len = 0.3;

  int i;
  for(i=0; i < 3; i++)
  {
    vec3 P = gl_in[i].gl_Position.xyz;

        
  

    //Normal
    vertcolor = vec3(0,1,0);

    gl_Position = MVP * vec4(P, 1.0);
    
    EmitVertex();
    
    gl_Position = MVP * vec4(P + tbnMatrix[i][2] * len, 1.0);
    vertcolor = vec3(0,1,0);

    EmitVertex();
  
EndPrimitive();  

      //Tanget
    vertcolor = vec3(0,0,1);

    gl_Position = MVP * vec4(P, 1.0);
    
    EmitVertex();
    
    gl_Position = MVP * vec4(P + tbnMatrix[i][0] * len, 1.0);
    vertcolor = vec3(0,0,1);

    EmitVertex();

    
EndPrimitive();

      //Bitanget
    vertcolor = vec3(1,0,0);

    gl_Position = MVP * vec4(P, 1.0);
    
    EmitVertex();
    
    gl_Position = MVP * vec4(P + tbnMatrix[i][1] * len, 1.0);
    vertcolor = vec3(1,0,0);

    EmitVertex();
    


EndPrimitive();


  }
}