// Version d'OpenGL
#version 330

/* 
pour le shading de Phong non flat
*/
in vec3 in_normale;
in vec3 lumiere;

/* Flat shading */
/*
flat in vec3 in_normale;
flat in vec3 lumiere;
*/

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;


out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main() {
  vec3 normale = normalize(in_normale);
  float ra,rd,rs;
  ra = 0.3;
  rd = 0.8;
  rs = 1.0;
  
  vec3 la,ld,ls;
    
  la = vec3(1.0,1.0,0.2);
  ld = vec3(1.0,0.8,0.2);
  ls = vec3(1.0,1.0,1.0);
  
  
  int s = 16;
  
  vec3 e = normalize((inverse(ViewMatrix * ModelMatrix) * vec4(0,0,1.0,0)).xyz);
  
  vec3 l,r;
   
  // Lumière venant de la caméra
  l = normalize(-e);
  //l = lumiere;
  r = normalize(reflect(l, normale));
  
  vec3 ambiant = ra*la;
  vec3 diffus = rd*ld*max(-dot(normale,l),0);
  vec3 speculaire = rs*ls*pow(max(dot(e,r),0),s);


  // Affectation de la couleur du fragment
  vec3 my_color = ambiant + diffus + speculaire;

	/**
	 Gestion du toon-shading
	*/
	float levels = 5;
	// Calcul de l’intensité de couleur en chaque sommet
	float intensity = (my_color.x+my_color.y+my_color.z)/3.0;
	// Application d’une nuance en fonction des niveaux de couleur et de l’intensité précédemment calculée
	float shade = ceil(intensity * levels)/levels;
	// Application de la nuance à la couleur initiale
	my_color = my_color * shade;

  frag_color = vec4(my_color,1.0);

  
}
