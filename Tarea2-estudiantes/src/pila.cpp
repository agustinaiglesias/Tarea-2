/* 5463192 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"
#include "../include/cadena.h"
#include "../include/producto.h"

struct _rep_pila {
  TCadena pila;
  nat cantidad;
};

/*
  Devuelve una TPila vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TPila crearPila() {
  TPila nueva = new _rep_pila;
  nueva -> pila = crearCadena();
  nueva -> cantidad = 0;
  return nueva;
 }

/*
  Libera la memoria asignada a 'p' si la pila no contiene elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'p'.
 */
void liberarPila(TPila p) {
  if (p -> cantidad == 0){
    delete p;
    p = NULL;
  }
}

/*
  Devuelve la cantidad de elementos de 'p'.
  El tiempo de ejecución debe ser O(1).
 */
nat cantidadEnPila(TPila p) {
  if (p!=NULL){
    return p -> cantidad;
  }else{
    return 0;
  }
}

/*
  Apila 'dato' en 'p' y devuelve 'p' con el dato apilado.
  El tiempo de ejecución debe ser O(1).
 */
TPila apilar(Producto dato, TPila p) {
  p -> pila = insertarAlInicio(p -> pila, dato);
  p -> cantidad = p -> cantidad + 1;
  return p;
 }

/*
  Devuelve el elemento más nuevo en 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
Producto cima(TPila p) {
  return datoCadena(p -> pila);
}

/*
  Remueve de 'p' su elemento más nuevo.
  Devuelve 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TPila desapilar(TPila p) {
   removerPrimero(p -> pila); //OJO no es void
  p -> cantidad = p -> cantidad -1 ;
  //liberarProducto(aBorrar);
  return p;
}
