/*
  Módulo de definición de 'TPila'.

  Los elementos de tipo TPila son pilas de elementos de tipo TInfo.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "utils.h"
#include "producto.h"

// Representación de 'TPila'.
// Se debe definir en pila.cpp.
// struct _rep_pila;
// Declaración del tipo 'TPila'
typedef struct _rep_pila *TPila;

/*
  Devuelve una TPila vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TPila crearPila();

/*
  Libera la memoria asignada a 'p' si la pila no contiene elementos.
  El tiempo de ejecución debe ser O(1).
 */
void liberarPila(TPila p);

/*
  Devuelve la cantidad de elementos de 'p'.
  El tiempo de ejecución debe ser O(1).
 */
nat cantidadEnPila(TPila p);

/*
  Apila 'dato' en 'p' y devuelve 'p' con el dato apilado.
  El tiempo de ejecución debe ser O(1).
 */
TPila apilar(Producto dato, TPila p);

/*
  Devuelve el elemento más nuevo en 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
Producto cima(TPila p);

/*
  Remueve de 'p' su elemento más nuevo.
  Devuelve 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TPila desapilar(TPila p);

#endif
