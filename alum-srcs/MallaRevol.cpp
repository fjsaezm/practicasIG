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

// *****************************************************************************


void MallaRevol::crearMallaRevol( const std::vector<Tupla3f> & perfil_original, const unsigned nperfiles, const bool crear_tapas, const bool cerrar_malla) {


}
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
   nvper = vertices_ply.size() / 3;

   // calcular la tabla de normales
   calcular_normales();


}

// *****************************************************************************
