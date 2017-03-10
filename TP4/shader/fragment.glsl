// Version d'OpenGL
#version 330

/* pour le shading de Phong non flat
*/
in vec3 ambiant;
in vec3 diffus;
in vec3 speculaire;

/* Flat shading 
flat in vec3 ambiant;
flat in vec3 diffus;
flat in vec3 speculaire;
*/

out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main() {

  // Affectation de la couleur du fragment
  vec3 my_color = ambiant + diffus + speculaire;
  
	/*
  if(diffus.x	 > 0.04) {
  	my_color = vec3(1.0,1.0,1.0);
  } else {
  	my_color = vec3(0.0,0.0,0.0);
  }
  */
  
  frag_color = vec4(my_color,1.0);

  
}
