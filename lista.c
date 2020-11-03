#include <stdlib.h>

#include "lista.h"

lista_t* lista_crear() {

    lista_t* lista = malloc(sizeof(lista_t));

    if (!lista)
        return NULL;

    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    lista->cantidad = 0;

    return lista;
}

int lista_insertar(lista_t* lista, void* elemento) {

    if (!lista)
        return -1;

    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (!nodo)
        return -1;

    nodo->elemento = elemento;
    nodo->siguiente = NULL;

    lista->nodo_fin->siguiente = nodo;
    lista->nodo_fin = nodo;
    lista->cantidad++;

    return 0;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {

    if (!lista)
        return 1;

    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (!nodo)
        return -1;

    nodo->elemento = elemento;
    nodo_t* nodo_aux = lista->nodo_inicio;
    size_t contador = 1;

    while (contador < posicion) {
        nodo_aux = nodo_aux->siguiente;
        contador++;
    }

    if (posicion == 0) {
        nodo->siguiente = nodo_aux;
        lista->nodo_inicio = nodo;
    } else {
        nodo->siguiente = nodo_aux->siguiente;
        nodo_aux->siguiente = nodo;
    }

    if (posicion == lista->cantidad)
        lista->nodo_fin = nodo;

    lista->cantidad++;

    return 0;
}

int lista_borrar(lista_t* lista) {
    if (!lista)
        return -1;

    if (lista_vacia(lista))
        return -1;

    nodo_t* nodo = lista->nodo_inicio;

    free(lista->nodo_fin);
    lista->cantidad--;

    if (lista_vacia(lista)) {
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        return 0;
    }

    size_t contador = 1;

    while (contador < lista->cantidad) {
        lista->nodo_fin = nodo->siguiente;
        contador ++;
    }

    lista->nodo_fin->siguiente = NULL;

    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {

    if (!lista)
        return -1;

    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

    if (!lista)
        return NULL;

    if (posicion < lista->cantidad)
        return NULL;

    nodo_t* nodo = lista->nodo_inicio;
    size_t contador = 0;

    while (contador < posicion) {
        nodo = nodo->siguiente;
        contador++;
    }

    return nodo->elemento;
}

void* lista_ultimo(lista_t* lista){
    if (!lista)
        return NULL;
    if (lista_vacia(lista))
        return NULL;
    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    if (!lista)
        return true;

    if (lista->cantidad == 0)
        return true;

    return false;
}

size_t lista_elementos(lista_t* lista) {
    if (!lista)
        return 0;
    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento) {
    if (!lista)
        return -1;

    nodo_t* nodo = malloc(sizeof(nodo_t));

    nodo->elemento = elemento;
    nodo->siguiente = lista->nodo_inicio;

    lista->nodo_inicio = nodo;
    return 0;
}

int lista_desapilar(lista_t* lista) {
    return 0;
}

void* lista_tope(lista_t* lista) {
    return NULL;
}

int lista_encolar(lista_t* lista, void* elemento) {
    return 0;
}

int lista_desencolar(lista_t* lista) {
    return 0;
}

void* lista_primero(lista_t* lista) {
    return NULL;
}

void lista_destruir(lista_t* lista) {
    if (!lista)
        return;

    if (lista->cantidad == 0) {
        free(lista);
        return;
    }

    lista_borrar(lista);
    lista_destruir(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
    return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
    return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador) {
    return true;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {
    return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador) {}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {
    return 0;
}
