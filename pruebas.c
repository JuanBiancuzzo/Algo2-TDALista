#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pa2mm.h"

#define ERROR -1
#define EXITO 0

void insertar_n_elementos(lista_t* lista, void* elemento, size_t n) {
    for (size_t i = 0; i < n; i++)
        lista_insertar(lista, elemento);
}

void probar_creacion_lista () {
    lista_t* lista = NULL;

    pa2m_afirmar((lista = lista_crear()) != NULL,
                 "Se pudo crear la lista");
    pa2m_afirmar(lista->nodo_inicio == NULL && lista->nodo_fin == NULL && lista->cantidad == 0,
                 "Se inicializó correctamente la lista");

    lista_destruir(lista);
}

void probar_insertar_nodo () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    pa2m_afirmar(lista_insertar(NULL, &elemento_uno) == ERROR,
                 "Detecta que la lista es invalida");

    lista_insertar(lista, &elemento_uno);
    lista_insertar(lista, &elemento_dos);

    pa2m_afirmar(elemento_dos == *(int*)lista_ultimo(lista),
                 "Se insertó correctamente un nodo al final");
    pa2m_afirmar(lista->nodo_inicio->siguiente == lista->nodo_fin,
                 "Se colocaron correctamente");


    lista_destruir(lista);
}

void probar_insertar_en_posicion_nodo () {
     lista_t* lista = lista_crear();
     int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

     pa2m_afirmar(lista_insertar_en_posicion(NULL, &elemento_uno, 1) == ERROR,
                  "Detecta que la lista es invalida");

     lista_insertar_en_posicion(lista, &elemento_uno, 1);
     pa2m_afirmar(lista->nodo_inicio->elemento == lista->nodo_fin->elemento,
                  "Detecta que la lista esta vacia");

     insertar_n_elementos(lista, &elemento_uno, 2);

     lista_insertar_en_posicion(lista, &elemento_dos, 1);
     pa2m_afirmar(elemento_dos == *(int*)lista->nodo_inicio->siguiente->elemento,
                  "Colocado en la posicion correcta");

     lista_insertar_en_posicion(lista, &elemento_tres, 9);
     pa2m_afirmar(elemento_tres == *(int*)lista->nodo_fin->elemento,
                  "Colocado al final aunque la posición no exista");

     lista_destruir(lista);
}

void probar_apilar_nodo () {
     lista_t* lista = lista_crear();
     int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

     pa2m_afirmar(lista_apilar(NULL, &elemento_uno) == ERROR,
                  "Detecta que la lista es invalida");

     lista_apilar(lista, &elemento_dos);
     pa2m_afirmar(lista->nodo_inicio == lista->nodo_fin && lista->nodo_fin != NULL
                  && *(int*)lista->nodo_inicio->elemento == elemento_dos,
                  "Apila correctamente un elemento en lista vacia");

     insertar_n_elementos(lista, &elemento_uno, 3);

     lista_apilar(lista, &elemento_tres);
     pa2m_afirmar(*(int*)lista->nodo_inicio->elemento == elemento_tres,
                  "Apila correctamente un elemento al comienzo de la lista");

     lista_destruir(lista);
}

void probar_encolar_nodo () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

    pa2m_afirmar(lista_encolar(NULL, &elemento_uno) == ERROR,
                 "Detecta que la lista es invalida");

    lista_encolar(lista, &elemento_dos);
    pa2m_afirmar(lista->nodo_inicio == lista->nodo_fin && lista->nodo_fin != NULL
                 && *(int*)lista->nodo_inicio->elemento == elemento_dos,
                 "Encola correctamente un elemento en lista vacia");

    insertar_n_elementos(lista, &elemento_uno, 3);

    lista_encolar(lista, &elemento_tres);
    pa2m_afirmar(*(int*)lista->nodo_fin->elemento == elemento_tres,
                 "Encola correctamente un elemento al final de la lista");

    lista_destruir(lista);
}

void probar_elemento_en_posicion_mostrar () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

    pa2m_afirmar(lista_elemento_en_posicion(NULL, 4) == NULL,
                 "Detecta que la lista es invalida");

    pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == NULL,
                 "Detecta que la lista esta vacia");

    lista_insertar(lista, &elemento_uno); // posicion 0
    lista_insertar(lista, &elemento_dos); // posicion 1
    lista_insertar(lista, &elemento_tres);// posicion 2

    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 0) == elemento_uno,
                 "Devuelve correctamente el primer elemento");

    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 2) == elemento_tres,
                 "Devuelve correctamente el ultimo elemento");

    pa2m_afirmar(lista_elemento_en_posicion(lista, 9) == NULL,
                 "Detecta que la posicion es invalida");

    lista_destruir(lista);
}

void probar_ultimo_mostrar () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    pa2m_afirmar(lista_ultimo(NULL) == NULL,
                 "Detecta que la lista es invalida");

    pa2m_afirmar(lista_ultimo(lista) == NULL,
                 "Detecta que la lista esta vacia");

    lista_insertar(lista, &elemento_uno);

    pa2m_afirmar(*(int*)lista_ultimo(lista) == elemento_uno,
                 "Devuelve correctamente el ultimo elemento, cuando es el único");

    lista_insertar(lista, &elemento_uno);
    lista_insertar(lista, &elemento_dos);

    pa2m_afirmar(*(int*)lista_ultimo(lista) == elemento_dos,
                 "Devuelve correctamente el ultimo elemento, cuando hay más de uno");

    lista_destruir(lista);
}

void probar_tope_mostrar () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    pa2m_afirmar(lista_tope(NULL) == NULL,
                 "Detecta que la lista es invalida");

    pa2m_afirmar(lista_tope(lista) == NULL,
                 "Detecta que la lista esta vacia");

    lista_apilar(lista, &elemento_uno);

    pa2m_afirmar(*(int*)lista_tope(lista) == elemento_uno,
                 "Devuelve correctamente el primer elemento, cuando es el único");

    lista_apilar(lista, &elemento_uno);
    lista_apilar(lista, &elemento_dos);

    pa2m_afirmar(*(int*)lista_tope(lista) == elemento_dos,
                 "Devuelve correctamente el primer elemento, cuando hay más de uno");

    lista_destruir(lista);
}

void probar_primero_mostar () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    pa2m_afirmar(lista_primero(NULL) == NULL,
                 "Detecta que la lista es invalida");

    pa2m_afirmar(lista_primero(lista) == NULL,
                 "Detecta que la lista esta vacia");

    lista_apilar(lista, &elemento_uno);

    pa2m_afirmar(*(int*)lista_primero(lista) == elemento_uno,
                 "Devuelve correctamente el primer elemento, cuando es el único");

    lista_apilar(lista, &elemento_uno);
    lista_apilar(lista, &elemento_dos);

    pa2m_afirmar(*(int*)lista_primero(lista) == elemento_dos,
                 "Devuelve correctamente el primer elemento, cuando hay más de uno");

    lista_destruir(lista);
}

void probar_borrar_de_posicion_nodo () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

    pa2m_afirmar(lista_borrar_de_posicion(NULL, 2) == ERROR,
                  "Detecta que la lista es invalida");

    pa2m_afirmar(lista_borrar_de_posicion(lista, 2) == ERROR,
                  "Detecta que la lista esta vacia");

    lista_insertar(lista, &elemento_uno); // posicion 0
    lista_insertar(lista, &elemento_dos); // posicion 1
    lista_insertar(lista, &elemento_tres);// posicion 2

    lista_borrar_de_posicion(lista, 1);
    pa2m_afirmar(lista->nodo_inicio->siguiente == lista->nodo_fin,
                 "Eliminó correctamente el nodo en una posicion especifica");

    lista_borrar_de_posicion(lista, 8);
    pa2m_afirmar(lista->nodo_inicio == lista->nodo_fin && *(int*)lista->nodo_inicio->elemento == elemento_uno,
                 "Eliminó correctamente el nodo en una posicion inexistente");

    lista_borrar_de_posicion(lista, 0);
    pa2m_afirmar(lista_vacia(lista) && lista->nodo_inicio == NULL && lista->nodo_fin == NULL,
                 "Eliminó correctamente el ultimo nodo");

    lista_destruir(lista);
}

int main() {

    pa2m_nuevo_grupo("Pruebas de creacion de lista");
    probar_creacion_lista();


    pa2m_nuevo_grupo("Pruebas de creacion de Nodos");
    printf(" * Probar lista_insertar:\n");
    probar_insertar_nodo();
    printf("\n * Probar lista_insertar_en_posicion:\n");
    probar_insertar_en_posicion_nodo();
    printf("\n * Probar lista_apilar:\n");
    probar_apilar_nodo();
    printf("\n * Probar lista_encolar:\n");
    probar_encolar_nodo();

    pa2m_nuevo_grupo("Pruebas de mostrar elementos");
    printf(" * Probar lista_elemento_en_posicoion:\n");
    probar_elemento_en_posicion_mostrar();
    printf("\n * Probar lista_ultimo:\n");
    probar_ultimo_mostrar();
    printf("\n * Probar lista_tope:\n");
    probar_tope_mostrar();
    printf("\n * Probar lista_primero:\n");
    probar_primero_mostar();

    pa2m_nuevo_grupo("Pruebas de borrar de Nodos");
    printf(" * Probar lista_borrar_de_posicion:\n");
    probar_borrar_de_posicion_nodo();
    // printf("\n * Probar lista_desapilar:\n");
    // printf("\n * Probar lista_desencolar:\n");

    pa2m_mostrar_reporte();
}
