// Version d'OpenGL
#version 120

attribute vec3 vertex_position;

// Fonction appelée pour chaque sommet
void main(){
	gl_Position = vec4(vertex_position,1.);
}
