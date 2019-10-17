varying out vec4 color;
varying out vec4 P;
varying out vec3 N;
varying out vec4 V;


void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Calc position and normal, light direction and view direction
	P = gl_ModelViewMatrix*gl_Vertex;
	N = normalize(gl_NormalMatrix * gl_Normal);
	V = gl_Vertex;
	

	

	//color = phongIllumination(P, N);
}

