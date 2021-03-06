


#ifndef GRAFO_ESCENA_HPP
#define GRAFO_ESCENA_HPP

//#include <obj-gra.hpp>
//#include <materiales.hpp>

#include "matrices-tr.hpp"
#include "materiales.hpp"
#include "Objeto3D.hpp"
#include "MallaInd.hpp"
#include "MallaRevol.hpp"

// *********************************************************************
// declaración adelantada de estructura para un nodo del grafo de escena

class NodoGrafoEscena ;
class NodoGrafoEscenaParam;

// *********************************************************************
// tipo enumerado con los tipos de entradas del nodo del grafo de escena

enum class TipoEntNGE { objeto, transformacion, material, noInicializado } ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

struct EntradaNGE
{
   TipoEntNGE tipo ;   // objeto, transformacion, material
   union
   {  Objeto3D * objeto ;  // ptr. a un objeto (no propietario)
      Matriz4f * matriz ;  // ptr. a matriz 4x4 transf. (propietario)
      Material * material ; // ptr. a material (no propietario)
   } ;
   // constructores (uno por tipo)
   EntradaNGE( Objeto3D * pObjeto ) ;      // (copia solo puntero)
   EntradaNGE( const Matriz4f & pMatriz ); // (crea copia en el heap)
   EntradaNGE( Material * pMaterial ) ;    // (copia solo puntero)
   ~EntradaNGE() ;
} ;

// *********************************************************************
// Nodo del grafo de escena: es un objeto 3D parametrizado, que contiene una lista de entradas

class NodoGrafoEscena : public Objeto3D
{
   protected:
  std::vector<EntradaNGE> entradas;

   public:

   NodoGrafoEscena() ;

   // visualiza usando OpenGL
   virtual void visualizarGL( ContextoVis & cv ) ;
   void fijarColorNodo( const Tupla3f & nuevo_color ) ;

   // calcular y obtener la caja englobante
   //virtual CajaEngf cajaEnglobante() ;

   // añadir una entrada al final, hace copia de la entrada
   // devuelve indice de la entrada dentro del vector de entradas
   unsigned agregar( const EntradaNGE & entrada );

   // construir una entrada y añadirla (al final)
   unsigned agregar( Objeto3D * pObjeto ); // objeto (copia solo puntero)
   unsigned agregar( const Matriz4f & pMatriz ); // matriz (copia objeto)
   unsigned agregar( Material * pMaterial ); // material (copia solo puntero)

   // devuelve el puntero a la matriz en la i-ésima entrada
   Matriz4f * leerPtrMatriz( unsigned iEnt );

   // método para buscar un objeto con un identificador
   virtual bool buscarObjeto( const int ident_busc, const Matriz4f & mmodelado,
                    Objeto3D ** objeto, Tupla3f & centro_wc )  ;

   // si 'centro_calculado' es 'false', recalcula el centro usando los centros
   // de los hijos (el punto medio de la caja englobante de los centros de hijos)
   virtual void calcularCentroOC() ;

} ;

// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos que tienen además un vector de
// parámetros

class NodoGrafoEscenaParam : public NodoGrafoEscena
{
   protected:
  std::vector<Parametro> parametros;


   public:
      // devuelve el número de parámetros
      int numParametros();

      // devuelve un puntero al i-ésimo parámetro (i < numParametros())
      Parametro * leerPtrParametro( unsigned i ) ;

      // actualiza el objeto para ir al siguiente cuadro,
      // se usa cuando están activadas las animaciones, una vez antes de cada frame
      void siguienteCuadro();
} ;

#endif // GRAFO_ESCENA_HPP

// *********************************************************************


class Cuerpo : public NodoGrafoEscenaParam{
public:
  Cuerpo();
};

class Brazo : public NodoGrafoEscenaParam{
protected:
  int puntMatriz;
public:
  Brazo();
  Matriz4f* getMat();

};

class Cabeza : public NodoGrafoEscenaParam{
protected:
  int puntMatriz;
public:
  Cabeza();
  Matriz4f* getMat();
};

class Pierna : public NodoGrafoEscenaParam{
protected:
  int puntMatriz;
public:
  Pierna();
  Matriz4f* getMat();
};

class Bateria : public NodoGrafoEscenaParam{
protected:
  Matriz4f* puntMatrizPlatillo;
public:
  Bateria();
  Matriz4f* getMatrizPlatillo();


};

class Tambor : public NodoGrafoEscenaParam{
 public:
  Tambor(float altura);
};

class Platillo : public NodoGrafoEscenaParam{
 protected:
  Matriz4f* matrizMetal;
 public:
  Platillo(float altura);
  Matriz4f* getPuntMatriz();
};

class MetalCono : public NodoGrafoEscenaParam{
protected:
  int puntMatriz;
public:
  MetalCono();
  Matriz4f* getPuntMatriz();
};
