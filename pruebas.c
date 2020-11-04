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

void probar_insertar_nodo() {
    lista_t* lista = lista_crear();

    int elemento_uno = 11, elemento_dos = 22;

    lista_insertar(lista, &elemento_uno);
    pa2m_afirmar(elemento_uno == *(int*)lista_ultimo(lista), "Se insertó correctamente un nodo");

    lista_insertar(lista, &elemento_dos);
    pa2m_afirmar(elemento_dos == *(int*)lista_ultimo(lista), "Se insertó correctamente un nodo al final");

    pa2m_afirmar(lista->nodo_inicio->siguiente == lista->nodo_fin, "Se colocaron correctamente");

    lista_destruir(lista);
}

int main() {

    pa2m_nuevo_grupo("Pruebas de creacion de lista");
    probar_creacion_lista();

    pa2m_nuevo_grupo("Pruebas de creacion de Nodos");
    probar_insertar_nodo();

    pa2m_mostrar_reporte();
}
