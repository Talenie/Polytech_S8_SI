// Version d'OpenGL
#version 330

in vec3 vert_color;
in vec3 vert_normal;
in vec3 light_dir;
in vec3 view_dir;
in float depth;

out vec4 frag_color;

uniform sampler2D texSampler;

// Fonction appellee pour chaque fragment
void main() {
  vec3 normal = normalize(vert_normal);
  
  float d = max(dot(-light_dir, normal),0.);
  float s = pow(max(dot(reflect(-light_dir,normal),view_dir),0.),5.);
  vec3 c = mix(vec3(0.5,0.6,0.9),vec3(0.7,0.6,0.3),smoothstep(0.4,0.6,vert_color.x));
  vec3 color = c*d+vec3(0.5)*s;
  
  frag_color = vec4(color, depth);
}
