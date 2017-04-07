// Version d'OpenGL
#version 330

in vec2 vert_texCoord;
in vec3 vert_normal;
in vec3 light_dir;
in vec3 view_dir;

out vec4 frag_color;

uniform sampler2D texSampler;

// Fonction appellee pour chaque fragment
void main() {
  vec3 normale = texture( texSampler, vert_texCoord).xyz;
  
  float ra,rd,rs;
  ra = 0.3;
  rd = 1.0;
  rs = 0.6;
  
  
  vec3 la,ld,ls;
    
  la = texture( texSampler, vert_texCoord).xyz;
  ld = texture( texSampler, vert_texCoord).xyz;
  ls = vec3(1.0,1.0,1.0);
  
  
  int s = 16;
    
  vec3 r = normalize(reflect(light_dir, normale));
  
  vec3 ambiant = ra*la;
  vec3 diffus = rd*ld*max(-dot(normale,light_dir),0);
  vec3 speculaire = rs*ls*pow(max(dot(view_dir,r),0),s);


  // Affectation de la couleur du fragment
  vec3 my_color = ambiant + diffus + speculaire;
  
  frag_color = vec4(my_color, 1.0);
  
  // TODO: récupérer la couleur correspondant à ce fragment dans la texture
  //frag_color = texture( texSampler, vert_texCoord);
}
