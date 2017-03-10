// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

// Donnees de sortie
/* pour le shading de phong non flat
*/
out vec3 in_normale;
out vec3 lumiere;

/* Flat shading
flat out vec3 normale;
flat out vec3 lumiere;
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
  
  in_normale = (transpose(inverse(ModelMatrix)) * vec4(in_normal,0.0)).xyz;
  lumiere = vec3(0.0,1.0,0.5);
}
