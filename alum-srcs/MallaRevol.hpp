// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Declaraciones de la clase MallaRevol
// **
// *********************************************************************

#ifndef IG_MALLAREVOL_HPP
#define IG_MALLAREVOL_HPP

#include <vector>          // usar std::vector
#include <string>

#include "MallaInd.hpp"   // declaración de 'Objeto3D'
// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos

class MallaRevol : public MallaInd
{
private:

  unsigned
  nper , // numero de perfiles
    nvp  ; // numero de vertices por perfil

public:
  // crea una malla de revolucion
  MallaRevol();

  MallaRevol( const std::string & nombre_arch,
              const unsigned nperfiles,
              const bool     crear_tapas,
              const bool     cerrar_malla ) ;

  void inicializarMallaRevol(std::vector<Tupla3f> & perfil_original,
                             unsigned nPerfiles,
                             unsigned numVertPerfil,
                             bool crearTapas,
                             bool cerrarMalla );

  void crearMallaRevol( const std::vector<Tupla3f> & perfil_original,
                        const unsigned nperfiles,
                        const bool crear_tapas,
                        const bool cerrar_malla ) ;


} ;

// Clases cilindro, cono, Esfera

class Cilindro : public MallaRevol
{
protected:
  float radio;
  float altura;

public:
  Cilindro(unsigned numVertPerfil, unsigned nPerfiles, float r, float a, bool crearTapas, bool cerrarMalla);
};

class Cono : public MallaRevol
{
protected:
  float radio;
  float altura;
public:
  Cono(unsigned numVertPerfil, unsigned nPerfiles, float r, float a, bool crearTapas, bool cerrarMalla);
};

class Esfera : public MallaRevol
{
protected:
  float radio;
public:
  Esfera( unsigned numVertPerfil, unsigned nPerfiles, float r, bool crearTapas, bool cerrarMalla);
};

#endif
