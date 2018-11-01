

#include "aux.hpp"
#include "matrices-tr.hpp"
#include "shaders.hpp"
#include "grafo-escena.hpp"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
  glMatrixMode (GL_MODELVIEW);
  glPushMatrix ();

  for (unsigned i = 0; i < entradas.size(); i++)
    switch (entradas[i].tipo) {
    case TipoEntNGE::objeto:
      entradas[i].objeto->visualizarGL (cv);
      break;
    case TipoEntNGE::transformacion:
      glMatrixMode (GL_MODELVIEW);
      glMultMatrixf (*(entradas[i].matriz));
      break;
    default:
      std::cout << "Tipo no conocido" << std::endl;
    }

  glMatrixMode (GL_MODELVIEW);
  glPopMatrix();
}
// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{
  ponerNombre("Nombre");

}
// -----------------------------------------------------------------------------

void NodoGrafoEscena::fijarColorNodo( const Tupla3f & nuevo_color )
{
   // COMPLETAR: práctica 3: asignarle un color plano al nodo, distinto del padre
   // ........

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
  entradas.push_back(entrada);
  return entradas.size()-1;

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   
  assert(entradas[indice].tipo == TipoEntNGE::transformacion);

  return entradas[indice].matriz;

}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // ........

}

// *****************************************************************************
// Nodo del grafo de escena, con una lista añadida de parámetros
// *****************************************************************************


// -----------------------------------------------------------------------------
// devuelve el numero de grados de libertad
int NodoGrafoEscenaParam::numParametros()
{
  return parametros.size();

}
// -----------------------------------------------------------------------------

// devuelve un puntero al i-ésimo grado de libertad
Parametro * NodoGrafoEscenaParam::leerPtrParametro( unsigned i )
{
  return &parametros[i];
}
// -----------------------------------------------------------------------------

void NodoGrafoEscenaParam::siguienteCuadro()
{
  
  for (auto& param: parametros)
    param.siguiente_cuadro();
}

// -----------------------------------------------------------------------------

// My items

Cuerpo::Cuerpo(){
  Cilindro* p1 = new Cilindro(100,25,0.1,1, true,true);
  Cilindro* body = new Cilindro(100,25,0.35,1,true,true);
  Cilindro* p2 = new Cilindro(100,25,0.1,1, true,true);
  Cilindro* a1 = new Cilindro(100,25,0.1,1,true,true);
  Cilindro* a2 = new Cilindro(100,25,0.1,1,true,true);
  Cono* cuello = new Cono(100,50,0.35,0.2,true,true);
  Esfera* c = new Esfera(100,50,0.35,true,true);
  //  int prueba1 =agregar( MAT_Traslacion(0,1,0));


  agregar(p1);
  agregar(MAT_Traslacion(0.5,0,0));
  agregar(p2);
  //Uso el - para centrar el tronco
  agregar(MAT_Traslacion(-0.25,1,0));
  agregar(body);
  //Subo la cabeza
  agregar(MAT_Traslacion(0,1,0));
  agregar(cuello);
  agregar(MAT_Traslacion(0,0.25,0));
  agregar(c);

  //Bajo para los brazos
  agregar(MAT_Traslacion(0,-0.25,0));

  // Inclinación brazos
  
  int a = agregar(MAT_Rotacion(150,1,0,0));
  //Brazo de un lado
  agregar(MAT_Traslacion(-0.35,0,0));
  agregar(a1);
  //Brazo del otro lado
  agregar(MAT_Traslacion(0.7,0,0));
  agregar(a2);

  Parametro param1(
               "Rotacion del brazo",
               leerPtrMatriz(a),
               [=] (float v) {return MAT_Rotacion(v,1,0,0);},
               true,
               150.0,
               30.0,
               0.5
               );
  /*Parametro param2(
                   "Rotacion del brazo otro sentido",
                   leerPtrMatriz(a),
                   [=] (float v) {return MAT_Rotacion(v,0,1,0);},
                   true,
                   150.0,
                   30.0,
                   0.5
                   );*/
  parametros.push_back(param1);
  // parametros.push_back(param2);


  /*
  Matriz4f* ptr_mat = leerPtrMatriz(prueba1);
 

  Parametro p2(
               "Movimientorandom2",
               ptr_mat, //Ptrmatriz
               [=] (float v) {return MAT_Traslacion(-1,0,0);},
               true, //Acotado
               45.0, //Valor inicial
               60.0, //Semiamplitud
               4.0 //Frecuencia
               );
    parametros.push_back(p1);
    parametros.push_back(p2);*/
}
