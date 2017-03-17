// Version d'OpenGL
#version 330

in vec2 coords;

out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main() {
  // Affichage de la coordonnee du fragment/pixel
  frag_color = vec4(coords,0.5,1.0);
}
