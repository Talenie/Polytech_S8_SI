#include <iostream>
#include <shader.h> // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h> // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp> // OpenGL Mathematics : www.http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <GLFW_define.h>

using namespace glm;
using namespace std;

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f


void view_control(mat4& view_matrix, float dx) {
  // exemple de control clavier
  if(glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS) {
    // appliquer une transformation (dx) à la matrice view
  }

  // ...
}


int main() {
  cout << "Debut du programme..." << endl;

  //==================================================
  //============= Creation de la fenetre =============
  //==================================================

  // Initialisation de GLFW
  if(!glfwInit()) {
    cout << "Echec de l'initialisation de GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // OpenGL 2.1
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

  // Ouverture d'une fenêtre en 1024x768
  // et creation d'un contexte OpenGL
  if(!glfwOpenWindow(WIDTH,HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW)) {
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
  //================= Initialisation =================
  //==================================================
  
  cout << "Initialisations..." << endl;

  // Definition de la couleur du fond
  glClearColor(0.0f,0.0f,0.3f,0.0f);

  GLuint programID = LoadShaders("../shader/vertex.glsl","../shader/fragment.glsl");

  // Definition d'un tableau de vecteurs définissant la geometrie
  vec3 vertex[] = {
    vec3(-0.5, -0.5, -0.5),
    vec3( 0.5, -0.5, -0.5),
    vec3(-0.5,  0.5, -0.5),
    vec3(-0.5,  0.5, -0.5),
    vec3( 0.5, -0.5, -0.5),
    vec3( 0.5,  0.5, -0.5)
  };

  // Creation d'un VAO (c'est l'objet qu'on va manipuler)
  GLuint vaoID;
  glGenVertexArrays(1,&vaoID); 
  glBindVertexArray(vaoID); // rendre ce VAO actif
  
  // Creation d'un buffer (VBO) avec vboID pour identifiant
  GLuint vboID;
  glGenBuffers(1,&vboID); // créer le VBO associé aux sommets

  // Definition de vboID comme le buffer courant
  // et lie automatiquement ce VBO au VAO actif
  glBindBuffer(GL_ARRAY_BUFFER,vboID);
  
  // Copie des donnees sur la carte graphique (dans vboID)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW); 

  // Obtention de l'ID de l'attribut "vertex_position" dans programID
  GLuint vertexPositionID = glGetAttribLocation(programID, "in_position");
	  
  // On indique a OpenGL comment lire les donnees
  glEnableVertexAttribArray(vertexPositionID);
  glVertexAttribPointer(
       vertexPositionID,   // ID de l'attribut à configurer
       3,                  // nombre de composante par position (x, y, z)
       GL_FLOAT,           // type des composantes
       GL_FALSE,           // normalisation des composantes
       0,                  // decalage des composantes
       (void*)0            // offset des composantes
			);
  
  glBindVertexArray(0); // Désactiver le VAO
  
  //==================================================
  // ToDo : Creer les matrices de transformation
  //==================================================


  
  
  cout << "Debut de la boucle principale..." << endl;
  unsigned int i = 0;

  // Boucle de dessin
  do {
    
    // Nettoyage de la zone de dessin
    glClear( GL_COLOR_BUFFER_BIT );

    //==================================================
    // ToDo : Modifier les matrices de transformation
    //==================================================

    

    //==================================================
    //===================== Dessin =====================
    //==================================================
    glUseProgram(programID); // Definition de programID comme le shader courant

    //==================================================
    // ToDo : Transmettre les matrices au vertex shader
    //==================================================
    
    
    
    glBindVertexArray(vaoID); // On active le VAO

    // on dessine le contenu de tous les VBOs (buffers) associés à ce VAO
    glDrawArrays(GL_TRIANGLES, 0, 6); 
    
    glBindVertexArray(0); // On désactive le VAO  

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
  //============== Nettoyage la memoire ==============
  //==================================================
  glDeleteBuffers(1, &vboID);
  glDeleteBuffers(1, &vaoID);

  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}
