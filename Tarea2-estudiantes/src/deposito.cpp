/* 5463192 */

/*
  Módulo de definición de 'Deposito'.

  Los elementos de tipo 'Deposito' son punteros a una estructura (que debe
  definirse en deposito.cpp).

  Laboratorio de Programación 2 2do semestre 2022.
  InCo-FIng-UDELAR
 */

#include "../include/deposito.h"
#include "../include/fecha.h"
#include "../include/colProductos.h"
#include "../include/pila.h"
#include "../include/producto.h"

// Representación de 'Deposito'.
// Se debe definir en deposito.cpp.
// struct _rep_deposito;
// Declaración del tipo 'Deposito'.
struct _rep_deposito{
	TColProductos productos;
};

/* Operaciones de deposito */

/*
  Devuelve un 'deposito' vacío, sin productos.
*/
TDeposito crearDeposito() {
	TDeposito nuevo = new _rep_deposito;
	nuevo -> productos = crearColProductos();
	return nuevo; }

/*
  Libera la memoria reservada por 'deposito' y de todos sus elementos.
 */
void liberarDeposito(TDeposito deposito) {
	TPila aux = colProdAPila(deposito ->  productos);
	while (cantidadEnPila(aux) != 0) {
		Producto aLiberar = cima(aux);
		liberarProducto(aLiberar);
		aux = desapilar(aux);
	}
	liberarColProductos(deposito -> productos);
	liberarPila(aux);
	delete deposito;
	deposito = NULL;
}

/*
  Devuelve las unidades del producto con identificador 'identificador'
  en el deposito 'deposito'. O(log(n))
 */
nat obtenerCantidadUnidades(TDeposito deposito, int identificador){
	Producto aux= buscarProductoEnColProductos(identificador ,deposito -> productos);
	return obtenerCantidad(aux);
 }

/*
  Agrega un producto al depósito con el identificador y el nombre que se pasan como parametros. O(log(n))
  Pre: !existeProducto().
 */
void agregarProducto(TDeposito deposito, nat identificador, char* nombre){
	Producto AInsertar = crearProducto(identificador, nombre);
	deposito -> productos = insertarEnColProductos(AInsertar, deposito -> productos);
}

/*
  Devuelve true si existe un producto con identificador 'identificador'. O(log(n))
*/
bool existeProducto(TDeposito deposito, nat identificador){
	if( deposito != NULL){
		return existeProductoEnColProductos(identificador, deposito -> productos);
	}else{
		return false;
	}
}

/*
  Quita del depósito todas las unidades que tengan fecha de vencimiento anterior
  o igual a la fecha pasada como parámetro.
*/
void quitarVencidosDeposito(TDeposito deposito, TFecha fecha){
	TPila aux = colProdAPila(deposito -> productos);
	while( cantidadEnPila(aux) != 0){
		quitarVencidos(cima(aux), fecha);
		aux = desapilar(aux);
	}
	liberarPila(aux);
}

/*
  Agrega cantidad unidades con fecha de vencimiento fVenc al producto de identificador
  'identificador'.
  Pre: existeProducto().
*/
void agregarUnidades(TDeposito deposito, nat identificador, nat cantidad, TFecha fVenc){
	Producto aux = buscarProductoEnColProductos(identificador, deposito -> productos);
	agregarUnidades(aux, cantidad, fVenc);
}

/*
    Quita cantidad elementos al producto con identificador 'identificador'.
    Se quitan los elementos con fecha de vencimiento más próxima.
    Pueden existir productos con cantidad 0 pero no con cantidad menor a cero.
    Pre: existeProducto() && obtenerCantidadUnidades() >= cantidad.
*/
void quitarUnidades(TDeposito deposito, nat identificador, nat cantidad){
	Producto aux = buscarProductoEnColProductos(identificador, deposito -> productos);
	quitarUnidades(aux, cantidad);
}

/*
    Si el producto existe, entonces lo elimina. También se deben eliminar todas
    las unidades del producto.
*/
void eliminarProducto(TDeposito deposito, nat identificador){
	if (existeProducto(deposito, identificador)){
		Producto eliminar = buscarProductoEnColProductos(identificador, deposito -> productos);
		deposito -> productos = removerDeColProductos(identificador, deposito -> productos);
		liberarProducto(eliminar);

	}
}

/*
  Se debe imprimir el resumen del depósito de la forma que está aclarada en
  el archivo de especificación gestionDeposito.h
*/
void imprimirResumenDeposito(TDeposito deposito) {
	if (deposito != NULL){
		TPila dep = colProdAPila(deposito -> productos);
		while( cantidadEnPila(dep) != 0){
			Producto aImprimir = cima(dep);
			imprimirProducto(aImprimir);
			dep = desapilar(dep);
		}
		liberarPila(dep);
	}

}

/*
  Imprime los datos del producto en el formato específicado en la letra. O(log(n))
  Pre: existeProducto()
 */
void imprimirProducto(TDeposito deposito, int identificador){
	Producto imprimir = buscarProductoEnColProductos(identificador, deposito -> productos);
	imprimirProducto(imprimir);
}
