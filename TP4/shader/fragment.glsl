// Version d'OpenGL
#version 330

in vec3 ambiant;
in vec3 diffus;
in vec3 speculaire;

out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main() {

  // Affectation de la couleur du fragment
  vec3 my_color = ambiant + diffus + speculaire;
  frag_color = vec4(my_color,1.0);;
}
