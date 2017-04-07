#include <iostream>
#include <vector>
#include <string>
#include <shader.h> // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h>    // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW_define.h>
#include <Mesh.h>
#include <QGLWidget>

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

using namespace glm;
using namespace std;

void view_control(mat4& view_matrix, float dx);

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
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Ouverture d'une fenêtre en 1024x768
  // et creation d'un contexte OpenGL
  if(!glfwOpenWindow(WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW)) {
    cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Definition du titre de la fenêtre
  glfwSetWindowTitle( "Polytech RICM 4 - TP8" );

  // Autorise GLFW a recevoir les appuis de touche
  glfwEnable( GLFW_STICKY_KEYS );

  // Initialisation de  GLEW
  glewExperimental = GL_TRUE;
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
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //-------------------------------------------------
  // Chargemement et compilation des shaders 
  GLuint programID1 = LoadShaders( "../shader/first-pass.vert", "../shader/first-pass.frag" );
  GLuint programID2 = LoadShaders( "../shader/second-pass.vert", "../shader/second-pass.frag" );

   //-------------------------------------------------
  // Initialisation du maillage
  string file_name("../models/dragon.off");
  cout << "chargement de '" << file_name << "'..." << endl;
  Mesh m(file_name.c_str());
  m.normalize();
  m.colorize();
  cout << "...fini. " << m.nb_vertices << " sommets, " << m.nb_faces << " triangles." << endl;
  
  // Creation d'un VAO pour l'objet (c'est l'objet qui encapsule les VBOs et qu'on va manipuler)
  GLuint vaoObjID;
  glGenVertexArrays(1,&vaoObjID); 
  glBindVertexArray(vaoObjID); // rendre ce VAO actif
    
  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(vec3), m.vertices.data(), GL_STATIC_DRAW);
  GLuint vertexPositionID = glGetAttribLocation(programID1, "in_position");
  glVertexAttribPointer(vertexPositionID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  glEnableVertexAttribArray(vertexPositionID);

  GLuint colorBufferID;
  glGenBuffers(1, &colorBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  glBufferData(GL_ARRAY_BUFFER, m.colors.size() * sizeof(vec3), m.colors.data(), GL_STATIC_DRAW);
  GLuint vertexColorID = glGetAttribLocation(programID1, "in_color");
  glVertexAttribPointer(vertexColorID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  glEnableVertexAttribArray(vertexColorID);

  GLuint normalBufferID;
  glGenBuffers(1, &normalBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
  glBufferData(GL_ARRAY_BUFFER, m.normals.size() * sizeof(vec3), m.normals.data(), GL_STATIC_DRAW);
  GLuint vertexNormalID = glGetAttribLocation(programID1, "in_normal");
  glVertexAttribPointer(vertexNormalID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  glEnableVertexAttribArray(vertexNormalID);

  GLuint indiceBufferID;
  glGenBuffers(1, &indiceBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.faces.size() * sizeof(uint),
  	       m.faces.data(), GL_STATIC_DRAW);


  // Creation d'un VAO pour le carre sur lequel on va plaquer la texture ou on a dessine  
  vec3 vertices[] = {vec3(-1.0, -1.0, 0.0),
		     vec3(-1.0,  1.0, 0.0),
		     vec3( 1.0, -1.0, 0.0),
		     vec3( 1.0,  1.0, 0.0)};

  unsigned int indices[] = {0, 2, 3, 0, 3, 1};

  GLuint vaoQuadID;
  glGenVertexArrays(1,&vaoQuadID); 
  glBindVertexArray(vaoQuadID);
  
  GLuint vertexQuadBufferID;
  glGenBuffers(1, &vertexQuadBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexQuadBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  GLuint vertexQuadPositionID = glGetAttribLocation(programID2, "in_position");
  glVertexAttribPointer(vertexQuadPositionID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  glEnableVertexAttribArray(vertexQuadPositionID);

  GLuint indiceQuadBufferID;
  glGenBuffers(1, &indiceQuadBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceQuadBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

  glBindVertexArray(0); // Désactiver le VAO

  //==================================================
  // Initialisation de 2 textures vides (une pour les couleurs, une pour faire le test de profondeur)
  //==================================================
  GLuint textureDepthID;
  glGenTextures(1, &textureDepthID);
  glBindTexture(GL_TEXTURE_2D,textureDepthID);
  glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,WIDTH,HEIGHT,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  GLuint textureColorID;
  glGenTextures(1, &textureColorID);
  glBindTexture(GL_TEXTURE_2D,textureColorID);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,WIDTH,HEIGHT,0,GL_RGBA,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  //==================================================
  // Creation du FBO (FrameBuffer Object)
  //==================================================
  GLuint fboID;
  glGenFramebuffers(1,&fboID); // on génère un FBO
  glBindFramebuffer(GL_FRAMEBUFFER,fboID); // on l'active (les opérations suivantes s'appliqueront dessus)
  glBindTexture(GL_TEXTURE_2D,textureColorID); // on active la texture de couleur
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,textureColorID,0); // on l'attache au FBO (sur l'unité COLOR_ATTACHEMENT0)
  glBindTexture(GL_TEXTURE_2D,textureDepthID); // on active la texture de profondeur 
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,textureDepthID,0); // on l'attache aussi au FBO (sans cette texture OpenGL ne pourrait plus faire le test de profondeur)
  glBindFramebuffer(GL_FRAMEBUFFER,0); // on désactive le FBO
  


  //==================================================
  // Matrices et adresses de variables 
  //==================================================
  mat4 projection_matrix = perspective(45.0f, WIDTH / HEIGHT, 0.1f, 100.0f);
  mat4 view_matrix = lookAt(vec3(0.0, 0.0, 2), vec3(0.0), vec3(0.0, 1.0, 0.0));
  mat4 model_matrix = scale(mat4(1.0f), vec3(0.5));
  
  GLuint PmatrixID = glGetUniformLocation(programID1, "ProjectionMatrix");
  GLuint VmatrixID = glGetUniformLocation(programID1, "ViewMatrix");
  GLuint MmatrixID = glGetUniformLocation(programID1, "ModelMatrix");
  GLuint texSamplerID = glGetUniformLocation(programID2, "texSampler");


  //==================================================
  //=========== Debut des choses serieuses ===========
  //==================================================

  cout << "Debut de la boucle principale..." << endl;

  double init_time = glfwGetTime();
  double prec_time = init_time;
  double cur_time = init_time;
  double speed = 0.5;
    
  char title[100];
  // Boucle de dessin
  do{
    // Nettoyage de la zone de dessin (couleurs+profondeurs)
    int w,h;
    glfwGetWindowSize(&w,&h);
    glViewport(0,0,w,h);

    //==================================================
    //============= Calcul du Point de Vue =============
    //==================================================
      
    prec_time = cur_time;
    cur_time = glfwGetTime() - init_time;
    double delta_time = cur_time - prec_time;
    sprintf(title,"Polytech RICM 4 - TP8 - %2.0f FPS",1.0/ delta_time);
    glfwSetWindowTitle(title);

    view_control(view_matrix, speed * delta_time);

    //==================================================
    //===================== Dessin =====================
    //==================================================

    // ***** premiere passe : dessin de l'objet dans la texture textureColorID ****** 
    glEnable(GL_DEPTH_TEST); // test de profondeur (important pour dessiner en 3D)
    glBindFramebuffer(GL_FRAMEBUFFER,fboID); // a partir d'ici, on dessine dans les textures attachées au FBO
    glDrawBuffer(GL_COLOR_ATTACHMENT0); // en particulier dans la texture attaché au COLOR_ATTACHEMENT0
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // on efface les textures (couleur+profondeur)
    glUseProgram(programID1); // premier shader actif 

    // Transmission des matrices au vertex shader
    glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, value_ptr(projection_matrix));
    glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, value_ptr(view_matrix));
    glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, value_ptr(model_matrix));

    // dessin de l'objet
    glBindVertexArray(vaoObjID);
    glDrawElements(GL_TRIANGLES,m.faces.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    // ***** seconde passe : dessin d'un carré sur lequel on plaque la texture ***** 
    glDisable(GL_DEPTH_TEST); // plus besoins du test de profondeur (on dessine juste un carré plaqué sur l'écran)
    glBindFramebuffer(GL_FRAMEBUFFER,0); // a partir d'ici, on dessine sur l'écran
    glClear(GL_COLOR_BUFFER_BIT); // on efface la couleur
    glUseProgram(programID2); // second shader actif 

    // transmission de la texture (il s'agit de la texture dans laquelle on vient de dessiner l'objet)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureColorID);
    glUniform1i(texSamplerID,0);

    // dessin du carre plaque sur l'ecran
    glBindVertexArray(vaoQuadID);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    // Echange des zones de dessin buffers
    glfwSwapBuffers();
      
    cout << "Temps ecoule (s) : " << cur_time << "\r";
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
    
  // Liberation des buffers
  glDeleteBuffers(1, &vaoObjID);
  glDeleteBuffers(1, &vaoQuadID);
  glDeleteBuffers(1, &vertexBufferID);
  glDeleteBuffers(1, &normalBufferID);
  glDeleteBuffers(1, &indiceBufferID);
  glDeleteBuffers(1, &vertexQuadBufferID);
  glDeleteBuffers(1, &indiceQuadBufferID);
  glDeleteFramebuffers(1,&fboID);
  glDeleteTextures(1,&textureColorID);
  glDeleteTextures(1,&textureDepthID);

  cout << "Fin du programme..." << endl;
    
    
  return EXIT_SUCCESS;
}

void view_control(mat4& view_matrix, float dx) {
  if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS) {
    vec4 axis = vec4(1.0, 0.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, dx * 180.0f, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS) {
    vec4 axis = vec4(1.0, 0.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, -dx * 180.0f, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, dx * 180.0f, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, -dx * 180.0f, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_PAGEUP ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, dx * 180.0f, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_PAGEDOWN ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, -dx * 180.0f, vec3(axis));
  }
  
  if (glfwGetKey( GLFW_KEY_Z ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_S ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_Q) == GLFW_PRESS) {
    vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_D ) == GLFW_PRESS) {
    vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_A ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey( GLFW_KEY_E ) == GLFW_PRESS) {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }
}

