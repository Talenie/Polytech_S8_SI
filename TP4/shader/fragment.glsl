// Version d'OpenGL
#version 330

/* pour le shading de Phong non flat
*/
in vec3 in_normale;
in vec3 lumiere;

/* Flat shading 
flat in vec3 normale;
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
  rd = 0.9;
  rs = 1.0;
  
  vec3 la,ld,ls;
    
  la = vec3(1.0,0.6,0.2);
  ld = vec3(1.0,1.0,0.1);
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
