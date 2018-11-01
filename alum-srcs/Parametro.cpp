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

{
  descripcion = p_descripcion;
  ptr_mat = p_ptr_mat;
  fun_calculo_matriz = p_fun_calculo_matriz;
  acotado = p_acotado;
  c = p_c;
  s = p_s;
  f = p_f;
  valor_normal = 0;
  velocidad = 0;

}
// -----------------------------------------------------------------------------



void Parametro::siguiente_cuadro()
{
  valor_normal += velocidad;

  //actualizamos matriz
  *ptr_mat = fun_calculo_matriz(leer_valor_actual());

}
// -----------------------------------------------------------------------------

void Parametro::reset()
{
  valor_normal = 0;
  velocidad = 0;
  //Actualizamos matriz
  *ptr_mat = fun_calculo_matriz(leer_valor_actual());

}
// -----------------------------------------------------------------------------
void Parametro::incrementar()
{
  valor_normal += valor_incremento;
  //Actualizamos matriz
  *ptr_mat = fun_calculo_matriz(leer_valor_actual());

}
// -----------------------------------------------------------------------------

void Parametro::decrementar()
{
  valor_normal -= valor_incremento;
  //actualizamos matriz
  *ptr_mat = fun_calculo_matriz(leer_valor_actual());

}
// -----------------------------------------------------------------------------
void Parametro::acelerar()
{
  velocidad +=valor_incremento_aceleracion;

}
// -----------------------------------------------------------------------------
void Parametro::decelerar()
{
  velocidad = velocidad - valor_incremento_aceleracion < 0 ? 0 : velocidad - valor_incremento_aceleracion;

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
