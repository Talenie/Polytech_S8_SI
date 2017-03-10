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
  
  
  float intensity = (diffus.x+diffus.y+diffus.z)/3.0;
  float niveaux = 12.0;
  
  for(float i=niveaux; i>0.0; i--) {
  	if(intensity <= 1/i) {
  		my_color.x = my_color.x/i;
  		my_color.y = my_color.y/i;
  		my_color.z = my_color.z/i;
  	}
  }
/*
  if(intensity > 0.8) {
  	my_color = vec3(1.0,1.0,1.0);
  } else if(intensity > 0.2) {
  	my_color = vec3(0.5,0.5,0.5);
  } else {
  	my_color = vec3(0.0,0.0,0.0);
  }
*/

  frag_color = vec4(my_color,1.0);

  
}
