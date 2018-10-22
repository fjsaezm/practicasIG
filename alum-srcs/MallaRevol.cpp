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

  double ang = cerrar_malla ? 360.0 / (double) nperfiles : 360.0 / (double) nperfiles - 1;

  //Matriz de giro de ángulo ang.
  Matriz4f giro = MAT_Rotacion(ang, 0, 1, 0);

  vector<Tupla3f> aux = perfil_original;
  //Insertamos los primeros vértices
  vertices.insert(vertices.end(), aux.begin(),aux.end());
  unsigned i,j;

  for( i = 0; i < nperfiles - 1; i++){

    vector<Tupla3f> rotado;
    //Rotate and save in a 2nd auxiliar vector
    for(auto vert : aux)
      rotado.push_back(giro * vert);
    //Add verts to the MAIN vector
    vertices.insert(vertices.end(), rotado.begin(), rotado.end());
    //The auxiliar vector is the rotated one, so we want to rotate the rotated
    aux = rotado;

    // Add faces
    for (j = 0; j < nvp - 1; j++) {
      int k1 = i * nvp + j;
      int k2 = i * nvp + j + 1;
      int k3 = (i+1) * nvp + j + 1;
      int k4 = (i+1) * nvp + j;

      caras.push_back({k4, k2, k3});
      caras.push_back({k4, k1, k2});
    }
  }


   if (cerrar_malla) {
    // Añadir caras (i = nper - 1)
    for (j = 0; j < nvp - 1; j++) {
      int k1 = i * nvp + j;
      int k2 = i * nvp + j + 1;
      int k3 = j + 1; // ((i+1) % nper) * nvp + j + 1
      int k4 = j; // ((i+1) % nper) * nvp + j

      caras.push_back({k4, k2, k3});
      caras.push_back({k4, k1, k2});
    }
  }

  // Crear tapas
  if (crear_tapas) {

    // Cara inferior
    auto primer_ver = vertices[0];
    if (primer_ver(X) != 0) {
      vertices.push_back({0.0, primer_ver(Y), 0.0});
      tam_ver++;

      for (i = 0; i + nvp < tam_ver; i += nvp)
        caras.push_back({i, tam_ver - 1, (i + nvp) % (tam_ver - 1)});
    }

    // Cara superior
    auto ult_ver = vertices[tam_ver - 2];
    if (ult_ver(X) != 0) {
      vertices.push_back({0.0, ult_ver(Y), 0.0});
      tam_ver++;

      for (i = nvp - 1; i + nvp < tam_ver; i += nvp)
        caras.push_back({i, tam_ver - 1, i + nvp});

      // Última cara (i = nper * nvp - 1)
      caras.push_back({i, tam_ver - 1, nvp - 1});
    }
  }

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
