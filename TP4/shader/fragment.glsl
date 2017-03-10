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
  
  // Toon shading
  float choix = 5;
  float x,y,z;
  
  for(float i = 1; i <= choix; i++){
	if(my_color.x < i/choix && my_color.x >= (i-1)/choix) x = (i-1)/choix;
	if(my_color.y < i/choix && my_color.y >= (i-1)/choix) y = (i-1)/choix;
	if(my_color.z < i/choix && my_color.z >= (i-1)/choix) z = (i-1)/choix;
  }
  
  frag_color = vec4(x,y,z,1.0);
  
}
