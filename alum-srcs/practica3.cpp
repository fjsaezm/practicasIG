// *********************************************************************
// **
// ** Informática Gráfica, curso 2018-19
// ** Práctica 2  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practicas.hpp"
#include "practica3.hpp"

using namespace std ;


static bool animaciones = false;
static int gradoLibertadActivo = 0;
static const int numObjetos3 = 1;
static int  objetoActivo3 = 0;
NodoGrafoEscenaParam* objetos3[numObjetos3] = {nullptr};



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
        objetoActivo3 = (objetoActivo3 + 1) % numObjetos3 ;
        res = true;

         break ;

      case 'A' :
        animaciones = !animaciones;
        if(animaciones)
          FijarFuncDesocupado(FGE_Desocupado);

        res = true;

         break ;

      case 'G' :
        if ( objetos3[objetoActivo3] != nullptr ) {
          p3_grado_libertad_activo = (p3_grado_libertad_activo + 1) %
            objetos3[objetoActivo3]->numParametros();
          cout << " nuevo grado de libertad activo '"
               << objetos3[objetoActivo3]->leerPtrParametro(p3_grado_libertad_activo)->leer_descripcion()
               << "'" << endl;
          res = true;
        }

         break ;

      case 'R' :
        animaciones = false;
        if (objetos3[objetoActivo3] != nullptr)
          for (unsigned i = 0; i < objetos3[objetoActivo3]->numParametros(); i++)
            objetos3[objetoActivo3]->leerPtrParametro(i)->reset();
        cout << "Reset." << endl;
        res = true;

         break ;

      case '>' :
        if (objetos3[objetoActivo3] != nullptr) {
          auto param_activo = objetos3[objetoActivo3]->leerPtrParametro(p3_grado_libertad_activo);

          if (animaciones) {
            param_activo->acelerar();
            cout << "práctica 3: el grado de libertad activo es " << p3_grado_libertad_activo
                 << ", con velocidad " << param_activo->leer_velocidad_actual() << endl;
          }

          else {
            param_activo->incrementar();
            cout << "práctica 3: el grado de libertad activo es " << p3_grado_libertad_activo
                 << ", con valor " << param_activo->leer_valor_actual() << endl;
          }

          res = true;
        }

         break ;

      case '<' :
        if (objetos3[objetoActivo3] != nullptr) {
          auto param_activo = objetos3[objetoActivo3]->leerPtrParametro(p3_grado_libertad_activo);

          if (animaciones) {
            param_activo->decelerar();
            cout << "práctica 3: el grado de libertad activo es " << p3_grado_libertad_activo
                 << ", con velocidad " << param_activo->leer_velocidad_actual() << endl;
          }

          else {
            param_activo->decrementar();
            cout << "práctica 3: el grado de libertad activo es " << p3_grado_libertad_activo
                 << ", con valor " << param_activo->leer_valor_actual() << endl;
          }

          res = true;
        }


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

 if (objetos3[objetoActivo3] != nullptr)
   objetos3[objetoActivo3]->siguienteCuadro();

 redibujar_ventana = true;

 return true;

}
