// Version d'OpenGL
#version 330

// Donnees d'entree
layout(location=0) in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

// Donnees de sortie
out vec4 my_color;
out vec4 my_position;
out vec4 my_normale;
out vec4 my_prof;

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Fonction appellee pour chaque sommet
void main()
{
	// Affectation de la position du sommet
	// gl_Position est definit par defaut dans GLSL
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
	
	float z = -(ViewMatrix * ModelMatrix * vec4(in_position, 1.0)).z -1.5;
	
	my_color = vec4(in_color, 1.0);
    my_position = vec4(in_position, 1.0);
	my_normale = vec4(in_normal, 1.0);
	my_prof = vec4(z,z,z, 1.0);
}
