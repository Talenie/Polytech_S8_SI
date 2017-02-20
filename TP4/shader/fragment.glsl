// Version d'OpenGL
#version 330

out vec3 ambiant;
out vec3 diffus;
out vec3 speculaire;

out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main() {

  // Affectation de la couleur du fragment
  frag_color = vec4(ambiant+diffus+speculaire,1.0);;
}
