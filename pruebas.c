#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pa2mm.h"

#define ERROR -1
#define EXITO 0

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

     lista_insertar(lista, &elemento_uno);
     lista_insertar(lista, &elemento_uno);

     lista_insertar_en_posicion(lista, &elemento_dos, 1);
     pa2m_afirmar(elemento_dos == *(int*)lista->nodo_inicio->siguiente->elemento,
                  "Colocado en la posicion correcta");

     lista_insertar_en_posicion(lista, &elemento_tres, 9);
     pa2m_afirmar(elemento_tres == *(int*)lista->nodo_fin->elemento,
                  "Colocado al final aunque la posición no exista");

     lista_destruir(lista);
}

void probar_borrar_de_posicion_nodo () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

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
    printf("\tProbar lista_insertar:\n");
    probar_insertar_nodo();
    printf("\n\tProbar lista_insertar_en_posicion:\n");
    probar_insertar_en_posicion_nodo();
    printf("\n\tProbar lista_borrar_de_posicion:\n");
    probar_borrar_de_posicion_nodo();

    pa2m_mostrar_reporte();
}
