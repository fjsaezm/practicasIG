// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Implementación de la clase 'MallaPLY'
// **
// *********************************************************************


#include <cassert>
#include <aux.hpp>
#include <tuplasg.hpp>
#include <file_ply_stl.hpp>
#include "MallaPLY.hpp"

using namespace std ;

// *****************************************************************************

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre(string("malla leída del archivo '") + nombre_arch + "'" );

   //  calcular_normales();
   std::vector<float> vertices_ply ; // coordenadas de vértices
   std::vector<int>   caras_ply ;    // índices de vértices de triángulos
   ply::read( nombre_arch.c_str(), vertices_ply, caras_ply );
   
   for (int i = 0; i + 2 < vertices_ply.size(); i += 3)
     vertices.push_back({vertices_ply[i], vertices_ply[i+1], vertices_ply[i+2]});

   for (int i = 0; i + 2 < caras_ply.size(); i+= 3)
     caras.push_back({caras_ply[i], caras_ply[i+1], caras_ply[i+2]});

   tam_ver = vertices_ply.size() / 3;
   tam_tri = caras_ply.size() / 3;



}

// *****************************************************************************
