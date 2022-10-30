/* 5463192 */

/*
  Módulo de implementación de 'ColProductos'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/producto.h"
#include "../include/pila.h"
#include "../include/utils.h"
#include "../include/colProductos.h"

// Representación de 'ColProductos'.
// Declaración del tipo 'TColProductos'
struct rep_colproductos{
  Producto prod;
  rep_colproductos *izq, *der;
};

/*
  Devuelve un 'ColProductos' vacío (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TColProductos crearColProductos(){
  TColProductos nuevo =NULL;
  /*nuevo -> prod = crearProducto();
  nuevo -> izq = NULL;
  nuevo -> der = NULL;*/
  return nuevo;

}


/*
  Libera la memoria asociada a 'colProd' pero no la de sus productos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'colProd'.
 */
void liberarColProductos(TColProductos colProd){
  if (colProd != NULL){
      liberarColProductos(colProd->izq);
      liberarColProductos(colProd->der);
      //liberarProducto(colProd -> prod);
      delete colProd;
      colProd = NULL;
  }
}

/*
Devuelve true si existe un Producto con identificador 'idProd'.
En caso contrario devuelve false.
El tiempo de ejecución debe ser O(log(n)).
*/
bool existeProductoEnColProductos(nat idProd, TColProductos colProd){
  bool res = false;
  if (colProd != NULL){
    if( obtenerIdentificadorDeProducto(colProd -> prod) == idProd){
      res = true;
    }
    else{
      if(idProd < obtenerIdentificadorDeProducto(colProd -> prod)){
       if(colProd -> izq != NULL){
         res = existeProductoEnColProductos(idProd, colProd -> izq);
       }

      }
      if (idProd > obtenerIdentificadorDeProducto(colProd -> prod)){
        if(colProd -> der != NULL){
          res = existeProductoEnColProductos(idProd, colProd -> der);
        }
      }
    }
  }
  return res;
 }

/*
  Devuelve el Producto cuyo componente natural es 'idProd'.
  Si 'idProd' no pertenece a 'colProd', devuelve NULL.
  El tiempo de ejecución debe ser O(log(n)).
 */
Producto buscarProductoEnColProductos(nat idProd, TColProductos colProd){
  if(existeProductoEnColProductos(idProd, colProd)){
    Producto res;
    if(obtenerIdentificadorDeProducto(colProd -> prod) == idProd){
      res = colProd -> prod;
    }else{
      if(idProd < obtenerIdentificadorDeProducto(colProd -> prod)){
        res = buscarProductoEnColProductos(idProd, colProd -> izq);
      }
      if(idProd > obtenerIdentificadorDeProducto(colProd -> prod)){
      res = buscarProductoEnColProductos(idProd, colProd -> der);
      }
    }
    return res;
  }else{
    return NULL;
  }
}

/*
  Inserta 'dato' en 'colProd'.
  Precondición: !existeProductoEnColProductos()
  El tiempo de ejecución debe ser O(log(n))
 */
TColProductos insertarEnColProductos(Producto dato, TColProductos colProd){
  if (colProd == NULL){
    colProd = new rep_colproductos;
    colProd -> prod = dato;
    colProd -> izq = NULL;
    colProd -> der = NULL;
  }else{
    if (obtenerIdentificadorDeProducto(dato) < obtenerIdentificadorDeProducto(colProd -> prod)){
      colProd -> izq = insertarEnColProductos(dato, colProd -> izq);
    }
    if (obtenerIdentificadorDeProducto(dato) > obtenerIdentificadorDeProducto(colProd -> prod)){
      colProd -> der = insertarEnColProductos(dato, colProd -> der);
    }
  }
  return colProd;
}

/* Función auxiliar que devuelve el mayor identificador de los productos del árbol.
Precondición: el árbol no es vacío.
*/
nat maxProd(TColProductos colProd){
  nat res;
  if(colProd -> der == NULL){
    res = obtenerIdentificadorDeProducto(colProd -> prod);
  }
  else{
    res = maxProd(colProd -> der);
  }
  return res;
}

/* Procedimiento auxiliar que remueve de 'colProd' el elemento con el mayor identificador. */
void removerMaxcolProd(TColProductos &colProd){
  if( colProd != NULL){
    if( colProd -> der == NULL){
      TColProductos aux = colProd;
      colProd = colProd -> izq;
      delete aux;
      aux = NULL;
    }
    else{
      removerMaxcolProd(colProd -> der);
    }
  }
}









/*
  Remueve de 'colProd' el elemento con identificador idProd.
  Devuelve 'colProd'.
  Precondición: existeProductoEnColProductos()
  El tiempo de ejecución debe ser O(log(n))
 */
TColProductos removerDeColProductos(nat idProd, TColProductos colProd){
  if(obtenerIdentificadorDeProducto(colProd -> prod) == idProd){
    if(colProd -> izq != NULL){
      colProd -> prod = buscarProductoEnColProductos(maxProd(colProd -> izq), colProd);
      removerMaxcolProd(colProd -> izq);
    }
    else{
      TColProductos aux = colProd;
      colProd = colProd -> der;
      //liberarProducto(aux -> prod);
      delete aux;
      aux = NULL;
    }
  }
  else{
    if(obtenerIdentificadorDeProducto(colProd -> prod) > idProd){
      colProd -> izq = removerDeColProductos(idProd, colProd -> izq);
    }
    if(obtenerIdentificadorDeProducto(colProd -> prod) < idProd){
      colProd -> der = removerDeColProductos(idProd, colProd -> der);
    }
  }
  return colProd;










/*  if (idProd == obtenerIdentificadorDeProducto(colProd -> prod)){
      if (colProd -> izq == NULL && colProd -> der == NULL){ //CASO raíz es una hoja
      liberarProducto(colProd -> prod);
      delete colProd;
      colProd = NULL;
      }else{
          TColProductos borrar = colProd;
          if(colProd -> der != NULL){
            TColProductos aux = colProd -> der;
            while(aux -> izq != NULL){
              aux = aux -> izq;
            }
            aux -> izq = colProd -> izq;
            colProd = colProd -> der;
            liberarProducto(borrar -> prod);
            delete borrar;
            borrar = NULL;
          }
          else{ //der null
            colProd = colProd -> izq;
            liberarProducto(borrar->prod);
            delete borrar;
            borrar = NULL;
          }
      }
    }else{
      if (idProd < obtenerIdentificadorDeProducto(colProd -> prod)){
        colProd = removerDeColProductos(idProd, colProd -> izq);
      }
      if (idProd > obtenerIdentificadorDeProducto(colProd -> prod)){
        colProd = removerDeColProductos(idProd, colProd -> der);
      }
    }
    return colProd;*/
 }

/* Función auxiliar */

void colProdAPilaAux(TColProductos colProd, TPila &pila){
    if( colProd != NULL){
      if (colProd -> izq == NULL && colProd -> der == NULL){
        pila = apilar(colProd -> prod, pila);
      }
      else{
        if( colProd ->izq != NULL){
          colProdAPilaAux(colProd -> izq, pila);
        }
        pila = apilar(colProd -> prod, pila);
        if( colProd -> der != NULL){
          colProdAPilaAux(colProd -> der, pila);
        }
     }
   }
}









/*
  Devuelve una pila con los elementos de la colección ordenados por identificador
  de menor a mayor.
*/

TPila colProdAPila(TColProductos colProd){

  TPila res = crearPila();
  colProdAPilaAux(colProd, res);
  return res;
}
