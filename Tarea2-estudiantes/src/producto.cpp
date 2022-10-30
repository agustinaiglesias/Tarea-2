/* 5463192 */

/*
  Módulo de implementacion de 'Producto'.

  Los elementos de tipo 'Producto' son punteros a una estructura (que debe
  definirse en producto.cpp).

  Laboratorio de Programación 2 2do semestre 2022.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/fecha.h"
#include "../include/producto.h"
#include "../include/lista.h"
#include "../include/vencimiento.h"

// Representación de 'Producto'.
// Se debe definir en producto.cpp.
// struct _rep_producto;
// Declaración del tipo 'Producto'.
struct _rep_producto{
	nat id;
	char* nombre;
	nat cantidadUnidades;
	TLista unidades;
};

/* Operaciones de producto */

/*
  Devuelve un 'producto'.
 */
Producto crearProducto(nat identificadorDeProducto, char* nombre){
	Producto nuevo = new _rep_producto;
  nuevo -> id =  identificadorDeProducto;
  nuevo -> nombre = copiarCadenaChar(nombre);
  nuevo -> cantidadUnidades = 0;
  nuevo -> unidades = crearLista();
  return nuevo;
 }

/*
  Libera la memoria reservada por 'producto'.
 */
void liberarProducto(Producto producto){
	delete[] (producto -> nombre);
  liberarLista(producto -> unidades);
  delete producto;
  producto = NULL;
}

/*
  Devuelve la cantidad de unidades 'producto'.
 */
nat obtenerCantidad(Producto producto){ return producto -> cantidadUnidades; }

/*
  Devuelve el identificador de producto de 'producto'.
 */
nat obtenerIdentificadorDeProducto(Producto producto){
		return producto -> id;
}

/*
    Agrega cantidad elementos a la unidad.
    Pre: cantidad y f_venc deben ser mayores a cero.
 */
void agregarUnidades(Producto producto, nat cantidad, TFecha f_venc){
	producto -> unidades = agregarAListaOrdenado(producto -> unidades, f_venc, cantidad);
	producto -> cantidadUnidades = producto -> cantidadUnidades + cantidad;
}

/*
    Quita cantidad elementos al producto con menor fecha de vencimiento.
    Pre: cantidad debe ser mayor a cero.
 */
void quitarUnidades(Producto producto, nat cantidad){
	producto -> unidades = quitarDeLista(producto -> unidades, cantidad);
	producto -> cantidadUnidades = producto -> cantidadUnidades - cantidad;
}

/*
    Quita todas las unidades de productos cuya fecha de vencimiento es menor a
    la fecha actual.
 */
void quitarVencidos(Producto producto, TFecha fecha){
	while (producto -> unidades != NULL && (compararFechas(obtenerFVencimiento(obtenerMasViejo(producto -> unidades)), fecha) == -1
	|| compararFechas(obtenerFVencimiento(obtenerMasViejo(producto -> unidades)), fecha) == 0)){
		Vencimiento ven = obtenerMasViejo(producto -> unidades);
		producto -> cantidadUnidades = producto -> cantidadUnidades - obtenerCantidad(ven);
		producto -> unidades = quitarMasViejo(producto -> unidades);
		liberarVencimiento(ven);
	}
}

/*
  Imprime los datos del producto en el formato específicado en gestionDeposito.
 */
void imprimirProducto(Producto producto){
  printf("Información del producto %d - %s\n", producto->id, producto->nombre);
  printf("Total de unidades: %d\n", producto->cantidadUnidades);
  imprimirInfoLista(producto->unidades);
}
