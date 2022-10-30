/* 5463192 */

/*
  Módulo de definición de 'TLista'.

  Los elementos de tipo TLista son Listas de elementos de tipo TFecha.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/lista.h"
#include "../include/vencimiento.h"
#include "../include/fecha.h"

// Representación de 'TLista'.
// Se debe definir en Lista.cpp.
// Declaración del tipo 'TLista'
struct _rep_lista{
  _rep_lista* sig;
  Vencimiento ven;
};

// Que sentido tiene esta funcion?
/*
  Devuelve una TLista vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TLista crearLista(){
  TLista lista = NULL;
  return lista;  }

/*
  Libera la memoria asignada a la TLista 'p' y la de todos sus elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de la TLista
  'p'.
 */
void liberarLista(TLista p){
    TLista aux = p;
    while(p != NULL){
      liberarVencimiento(p -> ven);
      aux = p->sig;
      delete p;
      p = aux;
  }
}

/*
  Devuelve true si la TLista 'p' es vacia.
  El tiempo de ejecución debe ser O(1).
 */
bool esVaciaLista(TLista p){
  if (p == NULL){
  return true;
  }
  else return false;
 }

/*
  Devuelve 'p' con un nuevo vencimiento insertado en caso de que no exista la fecha
  en la lista. Si ya existe un vencimiento con f_venc se le aumenta cantidad a dicho elemento.
  En caso de crear un nuevo vencimiento, la fecha utilizada al crearlo no debe
  compartir memoria con 'f_venc' que se pasa por parámetro.
  El tiempo de ejecución debe ser O(n).
 */
TLista agregarAListaOrdenado(TLista p, TFecha f_venc, nat cantidad){
  if (p == NULL){
    TLista nuevo = new _rep_lista;
    nuevo -> ven = crearVencimiento(f_venc, cantidad);
    nuevo -> sig = NULL;
    p = nuevo;
  } else {
      TLista iter = p;
      while(iter-> sig != NULL && compararFechas(f_venc, obtenerFVencimiento(iter -> ven)) == 1){
        iter = iter -> sig;
      }
      if(compararFechas(f_venc, obtenerFVencimiento(iter -> ven)) == 1){
        TLista nuevo = new _rep_lista;
        nuevo -> ven = crearVencimiento(f_venc, cantidad);
        nuevo -> sig = NULL;
        iter -> sig = nuevo;
      }
      if(compararFechas(f_venc, obtenerFVencimiento(iter -> ven)) == 0){
        agregarUnidades(iter->ven, cantidad);
      }
      if(compararFechas(f_venc, obtenerFVencimiento(iter -> ven)) == -1){
        TLista nuevo = new _rep_lista;
        *nuevo = *iter;
        iter -> ven = crearVencimiento(f_venc, cantidad);
        iter -> sig = nuevo;
      }
  }
  return p;
 }

/*
  Devuelve el elemento en 'p' con menor fecha de vencimiento de la lista.
  Precondición: cantidadEnLista(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
Vencimiento obtenerMasViejo(TLista p){   return p -> ven; }

/*
	Quita de la lista 'p' al elemento con la menor fecha de vencimiento.
	Pre: la lista tiene al menos un elemento.
*/
TLista quitarMasViejo(TLista p){
  TLista aux = p;
   p = p->sig;
   //liberarVencimiento(aux->ven);
   delete aux;
   aux = NULL;
   return p;
 }

/*
Elimina 'cantidad' de unidades de la lista de vencimientos.
Las unidades se eliminan según la fecha de vencimiento de menor a mayor fecha.
Si 'cantidad' es mayor que la cantidad de unidades sumadas que hay en la lista,
entonces se deben eliminar todos los elementos de la lista.
*/
TLista quitarDeLista(TLista p, nat cantidad){
  while(p != NULL && cantidad > 0){
    while(cantidad > 0 && obtenerCantidad(p->ven) > 0){
      quitarUnidades(p->ven, 1);
      cantidad = cantidad -1;
    }
    if (obtenerCantidad(p->ven) == 0){
      TLista aux = p;
      p = p -> sig;
      liberarVencimiento(aux -> ven);
      delete aux;
      aux = NULL;
    }
  }
  return p;
 }

/*
    Imprime información de la lista en el formato siguiente:
	%Fecha vencimiento% -> %cantidad unidades%
	%Fecha vencimiento% -> %cantidad unidades%
	%Fecha vencimiento% -> %cantidad unidades%
*/
void imprimirInfoLista(TLista p){
  while (p!= NULL){
    if(p->ven != NULL){
     imprimirVencimiento(p->ven);
     p = p->sig;
   }
 }
}
