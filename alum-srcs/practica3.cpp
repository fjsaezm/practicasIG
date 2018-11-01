

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practicas.hpp"
#include "practica3.hpp"
#include "grafo-escena.hpp"



using namespace std ;

static int objetoActivo3 = 0;
static const int numObjetos3 = 1;
static int parametroActivo = 0;
static bool animaciones = false;

static NodoGrafoEscenaParam* objetos3[numObjetos3] = {nullptr};


void P3_Inicializar(  )
{
   cout << "Creando objetos de la práctica 3 .... " << flush ;
   objetos3[objetoActivo3] = new Cuerpo();

   cout << "hecho." << endl << flush ;
}

// ---------------------------------------------------------------------
// Función invocada al pulsar una tecla con la práctica 1 activa:
// (si la tecla no se procesa en el 'main').
//
//  - devuelve 'true' si la tecla se usa en esta práctica para cambiar
//    entre el grado de libertad o incrementar/decrementar valores
//  - devuelve 'false' si la tecla no se usa en esta práctica (no ha
//    cambiado nada)

bool P3_FGE_PulsarTeclaCaracter( unsigned char tecla )
{
   bool res = false  ; // valor devuelto (true si se ha procesado tecla)

   switch ( toupper( tecla ) )
   {
      case 'O' :
        objetoActivo3 = (objetoActivo3+1)%numObjetos3;
        res = true;

         break ;

      case 'A' :
        animaciones = ! animaciones;
        cout << "Activo/Desactivo animaciones" << endl;
        if(animaciones)
          FijarFuncDesocupado(FGE_Desocupado);
        res = true;
         break ;

      case 'G' :
        parametroActivo = (++parametroActivo)%(objetos3[objetoActivo3]->numParametros());

         break ;

      case 'R' :
        for (int i = 0; i < objetos3[objetoActivo3]->numParametros(); ++i){
          objetos3[objetoActivo3]->leerPtrParametro(i)->reset();
        }

        animaciones = false;

        res = true;

         break ;

      case '>' :
        if(animaciones)
          objetos3[objetoActivo3]->leerPtrParametro(parametroActivo)->acelerar();
        else
          objetos3[objetoActivo3]->leerPtrParametro(parametroActivo)->incrementar();

        res = true;

         break ;

      case '<' :
        if(animaciones)
          objetos3[objetoActivo3]->leerPtrParametro(parametroActivo)->decelerar();
        else
          objetos3[objetoActivo3]->leerPtrParametro(parametroActivo)->decrementar();

        res = true;


         break ;
      default :
         break ;

   }
   return res ;
}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 3  para dibujar los objetos
// se debe de usar el modo de dibujo que hay en el parámetro 'cv'
// (se accede con 'cv.modoVisu')

void P3_DibujarObjetos( ContextoVis & cv )
{
  objetos3[objetoActivo3]->visualizarGL(cv);


}

//--------------------------------------------------------------------------

bool P3_FGE_Desocupado()
{
 
  if (!animaciones)
    return false;

  objetos3[objetoActivo3]->siguienteCuadro();
  redibujar_ventana = true;

  return true;

}
