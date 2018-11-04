#include <cassert>
#include <cmath>
#include "Parametro.hpp"
#include "Objeto3D.hpp"

// -----------------------------------------------------------------------------

// crear grado de libertad no acotado

Parametro::Parametro(
   const std::string &  p_descripcion,
   Matriz4f *           p_ptr_mat,
   TFuncionCMF          p_fun_calculo_matriz,
   bool                 p_acotado,
   float                p_c,
   float                p_s,
   float                p_f
)
  :descripcion(p_descripcion),
   ptr_mat(p_ptr_mat),
   fun_calculo_matriz(p_fun_calculo_matriz),
   acotado(p_acotado),
   c(p_c),
   s(p_s),
   f(p_f)

{
  velocidad = 0.1;
  valor_normal = 0.0;
}
// -----------------------------------------------------------------------------

void Parametro::actualizar_matriz(){
  *ptr_mat = fun_calculo_matriz(leer_valor_actual());
}


void Parametro::siguiente_cuadro()
{
  valor_normal += velocidad;

  //actualizamos matriz
  actualizar_matriz();

}
// -----------------------------------------------------------------------------

void Parametro::reset()
{
  valor_normal = 0.0;
  velocidad = 0.1;
  //Actualizamos matriz
  actualizar_matriz();

}
// -----------------------------------------------------------------------------
void Parametro::incrementar()
{
  valor_normal += valor_incremento;
  //Actualizamos matriz
  actualizar_matriz();

}
// -----------------------------------------------------------------------------

void Parametro::decrementar()
{
  valor_normal -= valor_incremento;
  //actualizamos matriz
  actualizar_matriz();

}
// -----------------------------------------------------------------------------
void Parametro::acelerar()
{
  velocidad +=valor_incremento_aceleracion;

}
// -----------------------------------------------------------------------------
void Parametro::decelerar()
{
  velocidad -= valor_incremento_aceleracion;
  if(velocidad < 0.0) velocidad = 0.0;

}
// -----------------------------------------------------------------------------

float Parametro::leer_valor_actual()
{
  float valor = 0;
  if(!acotado)
    valor = c+s*valor_normal;
  else
   valor  = c+s*sin(2*M_PI*f*valor_normal);

  return valor;


}

// -----------------------------------------------------------------------------
float Parametro::leer_velocidad_actual()
{
  return velocidad;
}
// -----------------------------------------------------------------------------

std::string Parametro::leer_descripcion()
{
  return descripcion;

}
// -----------------------------------------------------------------------------
