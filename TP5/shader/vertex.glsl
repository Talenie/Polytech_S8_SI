// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
uniform float p0x;
uniform float p0y;
uniform float p1x;
uniform float p1y;

out vec2 coords;

// Fonction appellee pour chaque sommet
void main() {
  gl_Position = vec4(in_position, 1.0);
  
  coords = vec2((in_position.x-p0x)/(p1x-p0x),(in_position.y-p1y)/(p0y-p1y)); // remap [-1,1] to [0,1]
}
