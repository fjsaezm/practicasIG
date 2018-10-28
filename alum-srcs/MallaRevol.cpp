// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include <aux.hpp>
#include <tuplasg.hpp>
#include <file_ply_stl.hpp>
#include <matrices-tr.hpp>
#include "MallaRevol.hpp"
#include <vector>

using namespace std ;

// ****************************************************************************


MallaRevol::MallaRevol() : MallaInd() {}


void MallaRevol::crearMallaRevol( const std::vector<Tupla3f> & perfil_original, const unsigned nperfiles, const bool crear_tapas, const bool cerrar_malla) {

  int nper = cerrar_malla ? nperfiles : nperfiles-1 ;
  double ang = 360.0 / (nper);
  nvp = perfil_original.size();

  //Matriz de giro de ángulo ang.
  Matriz4f giro = MAT_Rotacion(ang, 0, 1, 0);

  vector<Tupla3f> aux = perfil_original;
  //Insertamos los primeros vértices
  vertices.insert(vertices.end(), aux.begin(),aux.end());
  unsigned i,j;

  // Inicializacion de los vertices
  for (int i = 0; i < nperfiles; i++)
    for ( unsigned j = 0; j < nvp; j++)
      {
        Matriz4f matriz_giro = MAT_Rotacion((float)i*ang, 0 , 1 , 0);
        vertices.push_back(matriz_giro*perfil_original[j]);
      }
  //Add faces
  for ( int i = 0; i < nperfiles - 1; i++)
    for ( unsigned j = 0; j < nvp-1; j++)
      {
        caras.push_back({ i*nvp + j, (i+1)*nvp+j+1 , (i+1)*nvp+j});
        caras.push_back({ i*nvp + j, i*nvp + j+1, (i+1)*nvp + j+1});
      }

  if (cerrar_malla){
     for (unsigned j = 0; j < nvp-1; j++)
       {
         caras.push_back({ (nper - 1)*nvp + j, j+1, j});
         caras.push_back ({ (nper - 1)*nvp + j, (nper - 1)*nvp + j+1, j+1});
       }
   }
   // Crear tapas
   if (crear_tapas){

     std::cout << "Crear tapas." << endl;

     vertices.push_back({0, perfil_original[0][1], 0});
     vertices.push_back({0, perfil_original[nvp-1][1], 0});


     std::cout << "Creados vertices de tapas: " << vertices[vertices.size()-2] << " y " << vertices[vertices.size()-1]<< endl;

     // Se crean las caras de las tapas.
     for (int i = 0 ; i < nperfiles - 1; i++ )
       {
         caras.push_back( {i*nvp, vertices.size()-2, (i+1)*nvp} );
         caras.push_back( {(i+1)*nvp - 1, vertices.size()-1, (i+2)*nvp -1} );
       }

     // Si se ha cerrado la malla hay caras adicionales.
     if (cerrar_malla)
       {
       caras.push_back ( { nvp*(nper - 1), vertices.size()-2 , 0 } );
       caras.push_back ( { nvp*(nper - 1) + nvp - 1, vertices.size()-1, nvp - 1});
       }
   }

   tam_ver = vertices.size();
   tam_tri = caras.size();



 

}


//To initialize from a Original Tupla3f profile
void MallaRevol::inicializarMallaRevol(std::vector<Tupla3f> & perfil_original,  unsigned nPerfiles, unsigned numVertPerfil,bool crearTapas, bool cerrarMalla)
{
  nper = nPerfiles;
  nvp = numVertPerfil;
  tam_ver = nper * nvp; // vértices totales

  // Construir vértices y caras
  crearMallaRevol(perfil_original,nper, crearTapas, cerrarMalla);

  calcular_normales();
}




//From a PLY File
MallaRevol::MallaRevol( const std::string & nombre_arch,
                        const unsigned nperfiles,
                        const bool     crear_tapas,
                        const bool     cerrar_malla  )
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));

   std::vector<float> vertices_ply ; // coordenadas de vértices original
   ply::read_vertices(nombre_arch.c_str(), vertices_ply);

   std::vector<Tupla3f> perfilOriginal;

   //Get the original profile from a PLY file
   for (int i = 0; i + 2 < vertices_ply.size(); i += 3)
     perfilOriginal.push_back({vertices_ply[i], vertices_ply[i+1], vertices_ply[i+2]});

   nper = nperfiles;
   nvp = vertices_ply.size() / 3;

   crearMallaRevol(perfilOriginal, nper,crear_tapas,cerrar_malla );

   // calcular la tabla de normales
   calcular_normales();

}

// *****************************************************************************


Cilindro::Cilindro(unsigned numVertPerfil, unsigned nPerfiles, float r, float a, bool crearTapas, bool cerrarMalla)
{
  radio = r;
  altura = a;
  vector<Tupla3f> perfilOriginal(numVertPerfil);

  std::cout<< "Creo el cilindro!" << std::endl;
  for(int i = 0; i < numVertPerfil; i++){
    float alturaAct = a * ((float(i)/numVertPerfil-1));
    perfilOriginal[i] = {r, alturaAct , 0.0 };
  }
  std::cout<< "Voy a revolusionarme" << std::endl;
  inicializarMallaRevol(perfilOriginal,nPerfiles,numVertPerfil, crearTapas,cerrarMalla);
}

Cono::Cono(unsigned numVertPerfil, unsigned nPerfiles, float r, float a, bool crearTapas, bool cerrarMalla)
{
  radio = r;
  altura = a;
  vector<Tupla3f> perfilOriginal(numVertPerfil);

  std::cout<< "Creo el cono!" << std::endl;
  for(int i = 0; i < numVertPerfil; i++){
    //Función de un cono
    float x = (1-float(i) / (numVertPerfil-1)) *r;
    perfilOriginal[i] = {x,(-a/r)*x+a, 0.0};
  }
  inicializarMallaRevol(perfilOriginal,nPerfiles,numVertPerfil, crearTapas,cerrarMalla);
}

Esfera::Esfera(unsigned numVertPerfil,unsigned nPerfiles,float r, bool crearTapas, bool cerrarMalla)
{
  radio = r;
  vector<Tupla3f> perfilOriginal(numVertPerfil);

  std::cout<< "Creo la esfera!"<<std::endl;
  for(int i = 0; i < numVertPerfil; i++){
    float y = r* (-1 + (float)2*i / (numVertPerfil-1));
    perfilOriginal[i] = {sqrt(r*r-y*y),y,0.0};
  }
  inicializarMallaRevol(perfilOriginal,nPerfiles,numVertPerfil, crearTapas,cerrarMalla);
}
