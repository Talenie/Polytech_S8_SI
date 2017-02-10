// Version d'OpenGL
#version 330

in vec4 my_color;
in vec4 my_position;
in vec4 my_normale;
in vec4 my_prof;
uniform int viewport;

out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main()
{
  // Affectation de la couleur du fragment
  switch(viewport){
	  case 0 :
		frag_color = vec4(my_color.rgb ,1.0);
		break;
	  case 1 :
		frag_color = vec4(my_position.rgb ,1.0);
		break;
	  case 2 :
		frag_color = vec4(my_normale.rgb ,1.0);
		break;
	  case 3 :
		frag_color = vec4(my_prof.rgb ,1.0);
	  default :
	  break;
  }
}
