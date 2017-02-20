// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

// Donnees de sortie
flat out vec3 ambiant;
flat out vec3 diffus;
flat out vec3 speculaire;

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
  ra = 0.1;
  rd = 0.5;
  rs = 1.0;
  
  vec3 la,ld,ls;
  
  la = vec3(0,0.2,1.0);
  ld = vec3(0.1,0.1,1.0);
  ls = vec3(1.0,1.0,1.0);
  
  vec3 l,r;
  l = normalize(vec3(0.5,1.0,0.5));
  r = normalize(reflect(l, normale));
  
  int s = 16;
  
  vec3 e = normalize((inverse(ViewMatrix * ModelMatrix) * vec4(0,0,1.0,0)).xyz);
    
  ambiant = ra*la;
  diffus = rd*ld*max(-dot(normale,l),0);
  speculaire = rs*ls*pow(max(dot(e,r),0),s);
}
