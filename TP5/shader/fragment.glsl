// Version d'OpenGL
#version 330

in vec2 coords;
uniform float time;

out vec4 frag_color;


vec2 mult(in vec2 a, in vec2 b){
	vec2 res;
	res.x = a.x*b.x - a.y*b.y;
	res.y = a.x*b.y + a.y*b.x;
	return res;
}

// Calcule la puissance p d'un nombre complexe
vec2 pow(in vec2 c, in int p) {
	vec2 res = c;
	for( int i = 1; i < p; i++){
		res = mult(res,c);
	}
	return res;
}


// Calcule la couleur à  partir d'un entier.
vec4 colormap(in float n){
	float r,g,b;
	r = 1-n;
	g = 1-n;
	b = cos(n);
	return vec4(r,g,b,1.0);
}

float mandelbrot(in vec2 c, in int N){
	float S = 1000.;
	int div = 10;
	vec2 z = vec2(0.0);
	
	if(int(mod(time/div,2))==1){
		z = vec2(mod(time/div,1),1-mod(time/div,1));
	} else {
		z = vec2(1-mod(time/div,1),mod(time/div,1));
	}
	
	for(int i = 0; i < N; ++i){
		z = pow(z,5) + c;
		if(length(z) > S){
			return float(i)/float(N-1);
		}
	}
	return 1.0;
}

// Fonction appellee pour chaque fragment
void main() {
  // Affichage de la coordonnee du fragment/pixel
  
  float n = mandelbrot(coords,30);
  frag_color = colormap(n);
  
  
}
