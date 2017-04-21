// Version d'OpenGL
#version 330

in vec2 texcoord;

out vec4 frag_color;

uniform sampler2D texSampler;

void main() {
	//float nbdrag = 3.0;
	//vec2 coord = mod(texcoord,1./nbdrag)*nbdrag;
	vec2 coord = texcoord;
	
	vec2 pix_size = 1./textureSize(texSampler,0);
	
	
	vec4 sum = texture(texSampler,coord);
	float distance = sum.w;
	//float nb_pix = 2.0*distance;
	float nb_pix = 5.;
	
	/* Dans le cadre d'un flou en fonction de la distance */
	//if(distance > 1.) {
		for(float i = -nb_pix; i < nb_pix; i+=2.){
			for(float j = -nb_pix; j < nb_pix; j+=2.){
				sum += texture(texSampler,coord+vec2(i,j)*pix_size);
			}
		}
		
		float size = float(2*nb_pix+1);
		sum = sum/((size*size));
		//sum = sum/size; // on adapte la division en fonction du nombre de passages dans la fonction
	//}
	
	frag_color = sum;
	
	/*  Discontinuité de couleur
	vec4 diff_h = texture(texSampler,coord+vec2(1,0)*pix_size)-texture(texSampler,coord+vec2(-1,0)*pix_size);
	vec4 diff_v = texture(texSampler,coord+vec2(0,1)*pix_size)-texture(texSampler,coord+vec2(0,-1)*pix_size);
	
	frag_color = vec4(length(diff_h-diff_v));
	*/
	
	//frag_color = texture(texSampler,coord);
}
