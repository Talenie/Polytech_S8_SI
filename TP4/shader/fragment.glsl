// Version d'OpenGL
#version 330

flat in vec3 ambiant;
flat in vec3 diffus;
flat in vec3 speculaire;

out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main() {

  // Affectation de la couleur du fragment
  vec3 my_color = ambiant + diffus + speculaire;
  frag_color = vec4(my_color,1.0);;
}
