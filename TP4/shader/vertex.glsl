// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

// Donnees de sortie
out vec4 my_color;

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
  ra = 0.2;
  rd = 0.4;
  rs = 0.4;
  
  vec3 la,ld,ls;
  
  la = vec3(0,1.0,1.0);
  ld = vec3(0.1,0.1,1.0);
  ls = vec3(1.0,1.0,1.0);
  
  vec3 l,r;
  l = normalize(vec3(1.0,1.0,0));
  r = normalize(reflect(l, normale));
  
  int s = 4;
  
  vec3 e = normalize((inverse(ViewMatrix * ModelMatrix) * vec4(0,0,1.0,0)).xyz);
  
  vec3 Lf = ra*la + rd*ld*max(-dot(normale,l),0) + rs*ls*pow(max(dot(e,r),0),s);
  

  my_color = vec4(Lf,1.0);
}
