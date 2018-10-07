

#include <aux.hpp>
#include <tuplasg.hpp>
#include "MallaInd.hpp"   // declaración de 'ContextoVis'



// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre("malla indexada, anónima");

}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;

}
// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcular_normales()
{
   // COMPLETAR: en la práctica 2: calculo de las normales de la malla
   // .......


}


// -----------------------------------------------------------------------------

void MallaInd::visualizarDE_MI( ContextoVis & cv )
{
   // use vertex array
   glEnableClientState( GL_VERTEX_ARRAY );

   // pointer to coordinates
   glVertexPointer( 3, GL_FLOAT, 0 , vertices.data() );

   // draw: primitive type, nº index, index type, triangle table
   glDrawElements( GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, caras.data());

   //disable use vertex array
   glDisableClientState( GL_VERTEX_ARRAY );

   // VERSION CON BEGIN-END.
  //   glBegin (GL_TRIANGLES);
  //   for ( int i = 0; i < tabla_caras.size(); i++)
  //     for ( int j = 0; j < 3; j++)
  //       {
  //         unsigned ind_ver = tabla_caras[i][j];
  //         glVertex3fv (tabla_vertices[ind_ver]);
  //       }

  //  glEnd();


}

GLuint crearVBO( GLuint tipo, GLuint tamanio, GLvoid* puntero){
  assert ( tipo == GL_ARRAY_BUFFER || tipo == GL_ELEMENT_ARRAY_BUFFER);
 GLuint id_vbo;
 glGenBuffers ( 1, &id_vbo ); // Crear nuevo VBO con identificador en id_vbo
 glBindBuffer ( tipo, id_vbo ); //Activar el VBO usando su identificador
 glBufferData ( tipo , tamanio, puntero, GL_STATIC_DRAW ); // Transferencia RAM -> GPU

 glBindBuffer ( tipo, 0) ; // Desactivar VBO

 return id_vbo;
}

void MallaInd::crearVBOs(){

  tam_ver = sizeof(float)*3*vertices.size();
  tam_tri = sizeof(unsigned)*3*caras.size();

  id_vbo_ver = crearVBO( GL_ARRAY_BUFFER, tam_ver, vertices.data());
  id_vbo_tri = crearVBO( GL_ELEMENT_ARRAY_BUFFER, tam_tri, caras.data());
}

// ----------------------------------------------------------------------------
void MallaInd::visualizarDE_VBOs( ContextoVis & cv )
{
   crearVBOs();

   //Activate VBO
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver);
   //Select format
   glVertexPointer( 3, GL_FLOAT, 0,0);
   // Deactivate VBO
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   // Activate VA.
   glEnableClientState(GL_VERTEX_ARRAY);

   //visualize
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
   glDrawElements( GL_TRIANGLES, caras.size()*3L, GL_UNSIGNED_INT, NULL);
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);

   // Deactivate vertex array
   glDisableClientState( GL_VERTEX_ARRAY );

}

// -----------------------------------------------------------------------------

void MallaInd::visualizarGL( ContextoVis & cv )
{
  GLenum mode;

 switch(cv.modoVis){
 case modoSolido:
   mode = GL_FILL;
   break;
 case modoPuntos:
   mode = GL_POINT;
   break;
 case modoAlambre:
 default:
   mode = GL_LINE;
 }

 glPolygonMode (GL_FRONT_AND_BACK, mode);

if(cv.usarVBOs)
  visualizarDE_VBOs(cv);
else
  visualizarDE_MI(cv);



}
// *****************************************************************************

// *****************************************************************************

Cubo::Cubo(Tupla3f origen, float lado)
:  MallaInd( "malla cubo" )
{
  float origenx = origen[0],
      origeny = origen[1],
      origenz = origen[2];

    Tupla3f cero = origen;
    Tupla3f uno = {origenx + lado, origeny, origenz};
    Tupla3f dos = {origenx + lado, origeny,origenz + lado};
    Tupla3f tres = {origenx, origeny, origenz + lado};
    Tupla3f cuatro = {origenx, origeny + lado, origenz};
    Tupla3f cinco = {origenx + lado, origeny + lado, origenz};
    Tupla3f seis = {origenx + lado,origeny + lado, origenz + lado};
    Tupla3f siete = {origenx, origeny + lado, origenz + lado};
    vertices = {cero, uno, dos, tres, cuatro, cinco, seis, siete};
    caras = {
                   {0,1,2} ,{0,2,3},
                   {0,1,4}, {1,4,5},
                   {0,3,7}, {0,4,7},
                   {2,1,5}, {2,5,6},
                   {2,3,7}, {2,7,6},
                   {4,5,6}, {4,6,7}
    };
}
// *****************************************************************************

Tetraedro::Tetraedro()
:  MallaInd( "malla tetraedro")
{

  // De lado 1 y altura 1
  float origen = 0.0;
  float lado = 1.0;
  float altura = 1.0;

  Tupla3f cero = {origen, origen, origen};
  Tupla3f uno = {lado, origen , origen};
  Tupla3f dos = {origen, origen, lado};
  Tupla3f tres = {origen, altura, origen};
  vertices = {cero, uno, dos, tres};
  caras = {{0,1,2},{0,1,3},{1,2,3},{0,2,3}};
}
// *****************************************************************************
