#include <iostream>
#include <shader.hpp> // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h> // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp> // OpenGL Mathematics : www.http://glm.g-truc.net/0.9.5/index.html

using namespace glm;
using namespace std;

int main() {
  cout << "Debut du programme..." << endl;

  // Initialisation de GLFW
  if(!glfwInit()) {
    cout << "Echec de l'initialisation de GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2); // OpenGL 2.1
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

  // Ouverture d'une fenêtre en 1024x768
  // et creation d'un contexte OpenGL
  if(!glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW)) {
    cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Definition du titre de la fenêtre
  glfwSetWindowTitle( "Polytech RICM 4 - TP1" );

  // Autorise GLFW a recevoir les appuis de touche
  glfwEnable(GLFW_STICKY_KEYS);

  // Initialisation de  GLEW
  if(glewInit() != GLEW_OK) {
    cout << "Echec de l'initialisation de GLEW" << endl;
    exit(EXIT_FAILURE);
  }

  // Verification des donnees du contexte OpenGL
  const GLubyte* renderer = glGetString (GL_RENDERER);
  cout << "Carte Graphique : " << renderer << endl;

  const GLubyte* version = glGetString (GL_VERSION);
  cout << "Driver OpenGL : " << version << endl;



  //==================================================
  // ToDo : Initialiser
  //==================================================

  cout << "Initialisations..." << endl;

  // Definition de la couleur du fond
  glClearColor(0.8f,0.8f,0.8f,0.0f);

  // Récupération des shaders
  GLuint programID = LoadShaders("../shader/vertex.glsl","../shader/fragment.glsl");
  glUseProgram(programID);

	// Def d'un tableau de vecteur
	vec3 vertex[3] ;
	vertex[0] = vec3(-0.5f,0.5f,0.0f);
	vertex[1] = vec3(0.5f,0.5f,0.0f);
	vertex[2] = vec3(0.0f,-0.5f,0.0f);
	
	// recup ID de l'argument vertex_position
	GLuint vertexPositionID = glGetAttribLocation( programID, "vertex_position");
	
	// Creer VAO et recup Id
	GLuint vaoID;
	glGenVertexArrays(1,&vaoID); // Allocation memoire dan le GPU
	
	// Definit comme objet courant
	glBindVertexArray(vaoID);
	
	// Creer VBO et recup ID
	GLuint vboID;
	glGenBuffers(1,&vboID);
	
	//definit comme buffer courant et lie automatiquement le VBO au VBA courant
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	
	// Copie de donnees vers le VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex),vertex, GL_STATIC_DRAW) ;
	
	// On indique a OpenGL comment lire les données
	glEnableVertexAttribArray(vertexPositionID);
	glVertexAttribPointer(
		vertexPositionID,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	
	glBindVertexArray(0); //desactive VAO
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	
	
	
  cout << "Debut de la boucle principale..." << endl;
  unsigned int i = 0;
    
  
  // Boucle de dessin
  do {
    // Nettoyage de la zone de dessin
	glClear( GL_COLOR_BUFFER_BIT );
	  
	//~ //==================================================
	//~ // ToDo : Dessiner
	//~ //==================================================
	//~ glBegin(GL_TRIANGLES);
	//~ glColor3f(0.1f,0.1f,0.8f);
	//~ glVertex3f(-0.5f,0.5f,0.0f);
	//~ glColor3f(0.8f,0.1f,0.1f);
	//~ glVertex3f(0.5f,0.5f,0.0f);
	//~ glColor3f(0.1f,0.8f,0.1f);
	//~ glVertex3f(0.0f,-0.5f,0.0f);
	//~ glEnd();
	
	
	glBindVertexArray(vaoID) ; // On a c t i v e l e VAO
	// on d e s s i n e l e contenu de t o u s l e s VBOs ( b u f f e r s ) a s s o c i e s a c e VAO
	glDrawArrays(GL_TRIANGLES,0,3);
	glBindVertexArray(0); // On d e s a c t i v e l e VAO
	  
	// Echange des zones de dessin buffers
	glfwSwapBuffers();
	
    cout << "Compteur : " << i++ << "\r";
    cout.flush();

  } // Execution de la boucle...
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
	 glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

  cout << endl;

  // Ferme GLFW et OpenGL
  glfwTerminate();



  //==================================================
  // ToDo : Nettoyer la memoire
  //==================================================
  glDeleteBuffers(1,&vboID);
  glDeleteBuffers(1,&vaoID);




  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}

