#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pa2mm.h"

void probar_creacion_lista() {
    lista_t* lista = NULL;

    pa2m_afirmar((lista = lista_crear()) != NULL, "Se pudo crear la lista");
    pa2m_afirmar(lista->nodo_inicio == NULL && lista->nodo_fin == NULL && lista->cantidad == 0, "Se inicializó correctamente la lista");

    lista_destruir(lista);
}

void probar_creacion_nodo() {
    lista_t* lista = lista_crear();


    lista_destruir(lista);
}

int main() {

    pa2m_nuevo_grupo("Pruebas de creacion de lista");
    probar_creacion_lista();
    probar_creacion_nodo();

    pa2m_mostrar_reporte();
}
