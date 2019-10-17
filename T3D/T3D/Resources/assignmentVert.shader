varying out vec4 color;
varying out vec4 P;
varying out vec3 N;


void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Calc position and normal, light direction and view direction
	P = gl_ModelViewMatrix * gl_Vertex;
	N = normalize(gl_NormalMatrix * gl_Normal);
	
	if (gl_Position.z > 0.0) {
		color = (1, 1, 1, 1);
	}


	

	//color = phongIllumination(P, N);
}

