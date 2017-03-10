// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

// Donnees de sortie
/* pour le shading de phong non flat
*/
out vec3 ambiant;
out vec3 diffus;
out vec3 speculaire;

/* Flat shading
flat out vec3 ambiant;
flat out vec3 diffus;
flat out vec3 speculaire;
 */
 
// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Fonction appellee pour chaque sommet
void main() {
  // Affectation de la position du sommet
  // gl_Position est definit par defaut dan GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
  
  vec3 normale = (transpose(inverse(ModelMatrix)) * vec4(in_normal,0.0)).xyz;
  
  float ra,rd,rs;
  ra = 0.3;
  rd = 0.9;
  rs = 1.0;
  
  vec3 la,ld,ls;
  
  la = in_color;
  ld = in_color;
  
  //la = vec3(1.0,0.6,0.2);
  //ld = vec3(1.0,1.0,0.1);
  ls = vec3(1.0,1.0,1.0);
  
  
  int s = 16;
  
  vec3 e = normalize((inverse(ViewMatrix * ModelMatrix) * vec4(0,0,1.0,0)).xyz);
  
  vec3 l,r;
   
  // Lumière venant de la caméra
  l = normalize(-e);
  r = normalize(reflect(l, normale));
  
  ambiant = ra*la;
  diffus = rd*ld*max(-dot(normale,l),0);
  speculaire = rs*ls*pow(max(dot(e,r),0),s);
}
