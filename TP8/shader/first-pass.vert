// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
in vec3 in_normal;
in vec3 in_color;

// Donnees de sortie
out vec3 vert_color;
out vec3 vert_normal;

out vec3 light_dir;
out vec3 view_dir;
out float depth;

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Fonction appellee pour chaque sommet
void main() {
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
  
  vert_normal = (transpose(inverse(ViewMatrix*ModelMatrix)) * vec4(in_normal, 0.0)).xyz;
  light_dir = vec3(0.0, 0.0, -1.0);  
  view_dir = vec3(0.,0.,-1.);
  depth = length((ViewMatrix * ModelMatrix * vec4(in_position, 1.0)).xyz);
  vert_color = in_color;
}
