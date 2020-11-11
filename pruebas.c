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

void probar_insertar_invalido() {
    int elemento = 11;

    pa2m_afirmar(lista_insertar(NULL, &elemento) == ERROR,
                 "Detecta que la lista es invalida\n");

}

void probar_insertar_lista_vacia () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    pa2m_afirmar(lista_insertar(lista, &elemento) == EXITO,
                 "Mensaje de exito al insertar en una lista vacia");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio == lista->nodo_fin,
                 "La estructura de la lista se actualiza de forma correcta");

    pa2m_afirmar(!lista->nodo_inicio->siguiente && elemento == *(int*)lista->nodo_inicio->elemento,
                 "Inserta correctamente un elemento con la lista vacia\n");


    lista_destruir(lista);
}

void probar_insertar_lista_con_nodos () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    nodo_t* nodo = calloc(1, sizeof(nodo_t));
    if (!nodo) {
        lista_destruir(lista);
        return;
    }

    lista->nodo_inicio = nodo;
    lista->nodo_fin = nodo;
    lista->cantidad = 1;

    pa2m_afirmar(lista_insertar(lista, &elemento) == EXITO,
                 "Mensaje de exito al insertar un elemento con una lista no vacia");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio != lista->nodo_fin,
                 "La estructura de la lista se actualiza de forma correcta");

    pa2m_afirmar(elemento == *(int*)lista->nodo_fin->elemento,
                 "Se inserta correctamente el elemento al final\n");


    lista_destruir(lista);
}

void probar_insertar_varios_nodos_en_lista_vacia () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    pa2m_afirmar(lista_insertar(lista, &elemento_uno) == EXITO && lista_insertar(lista, &elemento_dos) == EXITO,
                 "Mensaje de exito al insertar varios elementos");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio != lista->nodo_fin,
                 "La estructura de la lista se actualizó de forma correcta");

    pa2m_afirmar(elemento_uno == *(int*)lista->nodo_inicio->elemento && lista->nodo_inicio->siguiente == lista->nodo_fin,
                 "Se inserta correctamente el primer elemento");

    pa2m_afirmar(elemento_dos == *(int*)lista->nodo_fin->elemento && !lista->nodo_fin->siguiente,
                 "Se inserta correctamente el segundo elemento");

    lista_destruir(lista);
}

void probar_insertar_nodo () {

    probar_insertar_invalido();
    probar_insertar_lista_vacia();
    probar_insertar_lista_con_nodos();
    probar_insertar_varios_nodos_en_lista_vacia();

}

void probar_insertar_en_posicion_lista_invalida () {
    int elemento = 11;

    pa2m_afirmar(lista_insertar_en_posicion(NULL, &elemento, 1) == ERROR,
                 "Detecta correctamente una lista invalida\n");

}

void probar_insertar_en_posicion_lista_vacia () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento, 0) == EXITO,
                 "Mensaje de exito al insertar en una lista vacia");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio == lista->nodo_fin,
                 "La estructura de la lista se actualizó de forma correcta")

    pa2m_afirmar(elemento == *(int*)lista->nodo_inicio->elemento,
                 "Se insertó correctamente el nodo\n");

    lista_destruir(lista);
}

void probar_insertar_en_posicion_en_extremos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;

    insertar_n_elementos(lista, &elemento_uno, 5);

    pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_dos, 0) == EXITO,
                 "Mensaje de exito al insertar al principio de la lista");

    pa2m_afirmar(elemento_dos == *(int*)lista->nodo_inicio->elemento,
                 "Se inserta correctamente el elemento al principio");

    pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_tres, 6) == EXITO,
                 "Mensaje de extio al insertar al final de la lista");

    pa2m_afirmar(elemento_tres == *(int*)lista->nodo_fin->elemento,
                 "Se inserta correctamente el elemento al final\n")

    lista_destruir(lista);
}

void probar_insertar_en_posicion_afuera_de_la_lista () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    insertar_n_elementos(lista, &elemento_uno, 5);

    pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_dos, 10) == EXITO,
                 "Mensaje de exito al insertar en posicion mayor a la cantidad de la lista");

    pa2m_afirmar(elemento_dos == *(int*)lista->nodo_fin->elemento,
                 "Se insertó correctamente en la ultima posicion");

    lista_destruir(lista);
}

void probar_insertar_en_posicion_nodo () {

    probar_insertar_en_posicion_lista_invalida();
    probar_insertar_en_posicion_lista_vacia();
    probar_insertar_en_posicion_en_extremos();
    probar_insertar_en_posicion_afuera_de_la_lista();

}

void probar_apilar_lista_invalida () {
    int elemento = 11;

    pa2m_afirmar(lista_apilar(NULL, &elemento) == ERROR,
                 "Detecta que la pila es invalida\n");
}

void probar_apilar_lista_vacia () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    pa2m_afirmar(lista_apilar(lista, &elemento) == EXITO,
                 "Mensaje de exito al apilar en una pila vacia");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio == lista->nodo_fin,
                 "La estructura de la lista se actualiza correctamente");

    pa2m_afirmar(elemento == *(int*)lista->nodo_inicio->elemento,
                 "Se apiló correctamente el elemento en la pila\n")

    lista_destruir(lista);
}

void probar_apilar_lista_con_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    insertar_n_elementos(lista, &elemento_uno, 5);

    pa2m_afirmar(lista_apilar(lista, &elemento_dos) == EXITO,
                 "Mensaje de exito al apilar en una pila con varios nodos");

    pa2m_afirmar(elemento_dos == *(int*)lista->nodo_inicio->elemento,
                 "Se apiló correctamente el elemento en la pila con varios nodos\n");

    lista_destruir(lista);
}

void probar_apilar_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, mensaje_uno, elemento_dos = 22, mensaje_dos, elemento_tres = 33, mensaje_tres;
    bool posicion_uno, posicion_dos, posicion_tres;

    mensaje_uno = lista_apilar(lista, &elemento_uno);
    mensaje_dos = lista_apilar(lista, &elemento_dos);
    mensaje_tres = lista_apilar(lista, &elemento_tres);

    pa2m_afirmar(mensaje_uno == EXITO && mensaje_dos == EXITO && mensaje_tres == EXITO,
                 "Mensaje de exito al apilar tres elementos");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio != lista->nodo_fin,
                 "La estructura de la pila se actualizó correctamente");

    posicion_uno = elemento_uno == *(int*)lista->nodo_fin->elemento;
    posicion_dos = elemento_dos == *(int*)lista->nodo_inicio->siguiente->elemento;
    posicion_tres = elemento_tres == *(int*)lista->nodo_inicio->elemento;

    pa2m_afirmar(posicion_uno && posicion_dos && posicion_tres,
                 "Se apiló correctamente los tres elementos en la pila\n");

    lista_destruir(lista);
}

void probar_apilar_nodo () {

    probar_apilar_lista_invalida();
    probar_apilar_lista_vacia();
    probar_apilar_lista_con_nodos();
    probar_apilar_varios_nodos();

}

void probar_encolar_lista_invalida () {
    int elemento = 11;

    pa2m_afirmar(lista_encolar(NULL, &elemento) == ERROR,
                 "Detecta que la cola es invalida\n");
}

void probar_encolar_lista_vacia () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    pa2m_afirmar(lista_encolar(lista, &elemento) == EXITO,
                 "Mensaje de exito al encolar en cola vacia");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio == lista->nodo_fin,
                 "Se actualiza la cola correctamente");

    pa2m_afirmar(elemento == *(int*)lista->nodo_fin->elemento,
                 "Se encoló correctamente el elemento en cola vacia\n");

    lista_destruir(lista);
}

void probar_encolar_lista_con_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    insertar_n_elementos(lista, &elemento_uno, 5);

    pa2m_afirmar(lista_encolar(lista, &elemento_dos) == EXITO,
                 "Mensaje de exito al encolar en cola con varios nodos");

    pa2m_afirmar(elemento_dos == *(int*)lista->nodo_fin->elemento,
                "Se encoló correctamente el elemtno en cola con varios nodos\n");

    lista_destruir(lista);
}

void probar_encolar_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, mensaje_uno, elemento_dos = 22, mensaje_dos, elemento_tres = 33, mensaje_tres;
    bool posicion_uno, posicion_dos, posicion_tres;

    mensaje_uno = lista_encolar(lista, &elemento_uno);
    mensaje_dos = lista_encolar(lista, &elemento_dos);
    mensaje_tres = lista_encolar(lista, &elemento_tres);

    pa2m_afirmar(mensaje_uno == EXITO && mensaje_dos == EXITO && mensaje_tres == EXITO,
                 "Mensaje de exito al encolar los tres elementos en la cola");

    pa2m_afirmar(lista->nodo_inicio && lista->nodo_fin && lista->nodo_inicio != lista->nodo_fin,
                 "Se actualiza la cola correctamente");

    posicion_uno = elemento_uno == *(int*)lista->nodo_inicio->elemento;
    posicion_dos = elemento_dos == *(int*)lista->nodo_inicio->siguiente->elemento;
    posicion_tres = elemento_tres == *(int*)lista->nodo_fin->elemento;

    pa2m_afirmar(posicion_uno && posicion_dos && posicion_tres,
                 "Se encoló correctamente los tres elementos en la cola\n");

    lista_destruir(lista);
}

void probar_encolar_nodo () {

    probar_encolar_lista_invalida();
    probar_encolar_lista_vacia();
    probar_encolar_lista_con_nodos();
    probar_encolar_varios_nodos();

}

void probar_elemento_en_posicion_valores_invalidos () {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL,
                 "Detecta correctamente que la lista es invalida");

    pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == NULL,
                 "Detecta correctamente que la posicion es invalida\n");

    lista_destruir(lista);
}

void probar_elemento_en_posicion_lista_con_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(elemento == *(int*)lista_elemento_en_posicion(lista, 0),
                 "Encuentra la posición correcta en la lista de un nodo\n");

    lista_destruir(lista);
}

void probar_elemento_en_posicion_lista_con_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22, elemento_tres = 33;
    bool posicion_uno, posicion_dos, posicion_tres;

    lista_encolar(lista, &elemento_uno);
    lista_encolar(lista, &elemento_dos);
    lista_encolar(lista, &elemento_tres);

    posicion_uno = elemento_uno == *(int*)lista_elemento_en_posicion(lista, 0);
    posicion_dos = elemento_dos == *(int*)lista_elemento_en_posicion(lista, 1);
    posicion_tres = elemento_tres == *(int*)lista_elemento_en_posicion(lista, 2);

    pa2m_afirmar(posicion_uno && posicion_dos && posicion_tres,
                 "Encuentra las tres posiciones correctas en la lista con varios nodos\n");

    lista_destruir(lista);
}

void probar_elemento_en_posicion_mostrar () {

    probar_elemento_en_posicion_valores_invalidos();
    probar_elemento_en_posicion_lista_con_un_nodo();
    probar_elemento_en_posicion_lista_con_varios_nodos();

}

void probar_ultimo_lista_invalida_vacia () {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_ultimo(NULL) == NULL,
                 "Detecta correctamente una lista invalida");

    pa2m_afirmar(lista_ultimo(lista) == NULL,
                 "Detecta correctamente una lista vacia\n");

    lista_destruir(lista);
}

void probar_ultimo_lista_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(elemento == *(int*)lista_ultimo(lista),
                 "Encuentra el último elemento en lista de un nodo\n");

    lista_destruir(lista);
}

void probar_ultimo_lista_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    insertar_n_elementos(lista, &elemento_uno, 5);

    lista_encolar(lista, &elemento_dos);

    pa2m_afirmar(elemento_dos == *(int*)lista_ultimo(lista),
                 "Encuentra el último elemento en lista con varios nodos\n");

    lista_destruir(lista);
}

void probar_ultimo_mostrar () {

    probar_ultimo_lista_invalida_vacia();
    probar_ultimo_lista_un_nodo();
    probar_ultimo_lista_varios_nodos();

}

void probar_tope_lista_invalida_vacia () {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_tope(NULL) == NULL,
                 "Detecta correctamente que la pila invalida");

    pa2m_afirmar(lista_tope(lista) == NULL,
                 "Detecta correctamente que la pila esta vacia\n");

    lista_destruir(lista);
}

void probar_tope_lista_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(elemento == *(int*)lista_tope(lista),
                 "Encuentra el elemento del tope en una pila con un nodo\n");

    lista_destruir(lista);
}

void probar_tope_lista_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    lista_apilar(lista, &elemento_uno);
    lista_apilar(lista, &elemento_dos);

    pa2m_afirmar(elemento_dos == *(int*)lista_tope(lista),
                 "Encuentra el elemento del tope en una pila con varios nodos\n");

    lista_destruir(lista);
}

void probar_tope_mostrar () {

    probar_tope_lista_invalida_vacia();
    probar_tope_lista_un_nodo();
    probar_tope_lista_varios_nodos();

}

void probar_primero_lista_invalida_vacia () {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_primero(NULL) == NULL,
                 "Detecta correctamente que la cola invalida");

    pa2m_afirmar(lista_primero(lista) == NULL,
                 "Detecta correctamente que la cola esta vacia\n");

    lista_destruir(lista);
}

void probar_primero_lista_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(elemento == *(int*)lista_primero(lista),
                 "Encuentra el elemento del primero en una cola con un nodo\n");

    lista_destruir(lista);
}

void probar_primero_lista_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    lista_encolar(lista, &elemento_uno);
    lista_encolar(lista, &elemento_dos);

    pa2m_afirmar(elemento_uno == *(int*)lista_primero(lista),
                 "Encuentra el elemento del primero en una cola con varios nodos\n");

    lista_destruir(lista);
}

void probar_primero_mostar () {

    probar_primero_lista_invalida_vacia();
    probar_primero_lista_un_nodo();
    probar_primero_lista_varios_nodos();

}

void probar_borrar_de_posicion_valores_invalidos () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    pa2m_afirmar(lista_borrar_de_posicion(NULL, 1) == ERROR,
                 "Detecta correctamente que la lista es invalida");

    pa2m_afirmar(lista_borrar_de_posicion(lista, 1) == ERROR,
                 "Detecta correctamente que la lista esta vacia");

    lista_insertar(lista, &elemento);

    pa2m_afirmar(lista_borrar_de_posicion(lista, 5) == EXITO,
                 "Mensaje de exito al intentar eliminar una posicion invalida");

    pa2m_afirmar(!lista->nodo_inicio && !lista->nodo_fin && lista_vacia(lista),
                 "La estructura de la lista se actualizó correctamente eliminando el ultimó nodo\n");

    lista_destruir(lista);
}

void probar_borrar_de_posicion_lista_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == EXITO,
                 "Mensaje de exito al borrar nodo de una lista con un solo nodo");

    pa2m_afirmar(!lista->nodo_inicio && !lista->nodo_fin && lista_vacia(lista),
                 "La estructura de la lista se actualizó correctamente eliminando el nodo\n");

    lista_destruir(lista);
}

void probar_borrar_de_posicion_lista_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;
    bool eliminado = true;

    insertar_n_elementos(lista, &elemento_uno, 5);
    lista_insertar_en_posicion(lista, &elemento_dos, 3);

    pa2m_afirmar(lista_borrar_de_posicion(lista, 3) == EXITO,
                 "Mensaje de exito al borrar nodo de una lista con varios nodos");

    for (size_t i = 0; i < lista_elementos(lista); i++) {
        if (elemento_dos == *(int*)lista_elemento_en_posicion(lista, i))
            eliminado = false;
    }

    pa2m_afirmar(eliminado,
                 "Se elimina correctamente el nodo de una lista con varios nodos\n");

    lista_destruir(lista);
}

void probar_borrar_de_posicion_nodo () {

    probar_borrar_de_posicion_valores_invalidos();
    probar_borrar_de_posicion_lista_un_nodo();
    probar_borrar_de_posicion_lista_varios_nodos();

}

void probar_desapilar_lista_invalida () {

    pa2m_afirmar(lista_desapilar(NULL) == ERROR,
                 "Detecta correctamente que la pila es invalida\n");

}

void probar_desapilar_lista_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(lista_desapilar(lista) == EXITO,
                 "Mensaje de exito al borrar un nodo en una pila de un nodo");

    pa2m_afirmar(!lista->nodo_inicio && !lista->nodo_fin && lista_vacia(lista),
                 "Se eliminó correctamente el nodo\n");

    lista_destruir(lista);
}

void probar_desapilar_lista_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;
    bool eliminado = true;

    insertar_n_elementos(lista, &elemento_uno, 5);
    lista_apilar(lista, &elemento_dos);

    pa2m_afirmar(lista_desapilar(lista) == EXITO,
                 "Mensaje de exito al borrar un nodo en una pila con varios nodos");

    for (size_t i = 0; i < lista_elementos(lista); i++) {
        if (elemento_dos == *(int*)lista_elemento_en_posicion(lista, i))
            eliminado = false;
    }

    pa2m_afirmar(eliminado,
                 "Se eliminó correctamente el nodo\n");

    lista_destruir(lista);
}

void probar_desapilar_nodo () {

    probar_desapilar_lista_invalida();
    probar_desapilar_lista_un_nodo();
    probar_desapilar_lista_varios_nodos();

}

void probar_desencolar_lista_invalida () {

    pa2m_afirmar(lista_desencolar(NULL) == ERROR,
                 "Detecta correctamente que la cola es invalida\n");

}

void probar_desencolar_lista_un_nodo () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    pa2m_afirmar(lista_desencolar(lista) == EXITO,
                 "Mensaje de exito al borrar un nodo en una cola de un nodo");

    pa2m_afirmar(!lista->nodo_inicio && !lista->nodo_fin && lista_vacia(lista),
                 "Se eliminó correctamente el nodo\n");

    lista_destruir(lista);
}

void probar_desencolar_lista_varios_nodos () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;
    bool eliminado = true;

    insertar_n_elementos(lista, &elemento_uno, 5);
    lista_apilar(lista, &elemento_dos);

    pa2m_afirmar(lista_desencolar(lista) == EXITO,
                 "Mensaje de exito al borrar un nodo en una cola con varios nodos");

    for (size_t i = 0; i < lista_elementos(lista); i++) {
        if (elemento_dos == *(int*)lista_elemento_en_posicion(lista, i))
            eliminado = false;
    }

    pa2m_afirmar(eliminado,
                 "Se eliminó correctamente el nodo\n");

    lista_destruir(lista);
}

void probar_desencolar_nodo () {

    probar_desencolar_lista_invalida();
    probar_desencolar_lista_un_nodo();
    probar_desencolar_lista_varios_nodos();

}

void probar_iterador_lista_invalida () {

    pa2m_afirmar(lista_iterador_crear(NULL) == NULL,
                 "Detecta correctamente que se le pasa una lista invalida\n");

}

void probar_iterador_inicializado () {
    lista_t* lista = lista_crear();
    int elemento = 11;

    lista_insertar(lista, &elemento);

    lista_iterador_t* iterador = lista_iterador_crear(lista);

    pa2m_afirmar(iterador->lista == lista && elemento == *(int*)iterador->corriente->elemento,
                 "Se inicializa correctamente el iterador de una lista\n");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void probar_iterador_crear () {

    probar_iterador_lista_invalida();
    probar_iterador_inicializado();

}

void probar_iterador_tiene_siguiente () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    lista_insertar(lista, &elemento_uno);
    lista_insertar(lista, &elemento_dos);

    lista_iterador_t* iterador = lista_iterador_crear(lista);

    pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false,
                 "Detecta un iterador invalido");

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true,
                 "Detecta correctamente que tiene siguiente");

    iterador->corriente = lista->nodo_inicio->siguiente;

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false,
                 "Detecta correctamente que no tiene siguiente");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void probar_iterador_avanzar () {
    lista_t* lista = lista_crear();
    int elemento_uno = 11, elemento_dos = 22;

    lista_insertar(lista, &elemento_uno);
    lista_insertar(lista, &elemento_dos);

    lista_iterador_t* iterador = lista_iterador_crear(lista);

    pa2m_afirmar(lista_iterador_avanzar(NULL) == false,
                 "Detecta correctamente que el iterador es invalido");

    pa2m_afirmar(lista_iterador_avanzar(iterador) == true && *(int*)iterador->corriente->elemento == elemento_dos,
                 "Se mueve correctamente a la siguiente posicion");

    pa2m_afirmar(lista_iterador_avanzar(iterador) == false,
                 "No se mueve cuando no hay siguiente posición");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

bool puedo_seguir_uno (void* elemento, void* contexto) {
    return true;
}

bool puedo_seguir_dos (void* elemento, void* contexto) {
    (*(int*)contexto)++;

    if (*(int*) contexto == 5)
        return false;
    return true;
}

void probar_iterador_con_cada_elemento () {
    lista_t* lista = lista_crear();
    int elemento = 11, contador = 0;
    size_t cantidad = 5;

    bool (*funcion_uno) (void*, void*) = puedo_seguir_uno;
    bool (*funcion_dos) (void*, void*) = puedo_seguir_dos;

    pa2m_afirmar(lista_con_cada_elemento(NULL, funcion_uno, NULL) == 0,
                 "Detecta correctamente que la lista es invalida");

    pa2m_afirmar(lista_con_cada_elemento(lista, funcion_uno, NULL) == 0,
                 "Detecta correctamente que la lista esta vacia");

    insertar_n_elementos(lista, &elemento, cantidad);

    pa2m_afirmar(lista_con_cada_elemento(lista, NULL, NULL) == 0,
                 "Detecta correctamente que la funcion es invalida");

    pa2m_afirmar(lista_con_cada_elemento(lista, funcion_uno, NULL) == cantidad,
                 "Detecta correctamente que la lista tiene 5 elementos");

    insertar_n_elementos(lista, &elemento, cantidad);
    cantidad += 5;

    pa2m_afirmar(lista_con_cada_elemento(lista, funcion_uno, NULL) == cantidad,
                 "Detecta correctamente que la lista tiene 10 elementos");


    pa2m_afirmar(lista_con_cada_elemento(lista, funcion_dos, &contador) == 5,
                 "Detecta correctamente que la funcion_dos le pide que se detenga")

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
    printf("\n * Probar lista_desapilar:\n");
    probar_desapilar_nodo();
    printf("\n * Probar lista_desencolar:\n");
    probar_desencolar_nodo();

    pa2m_nuevo_grupo("Pruebas de iteradores");
    printf(" * Probar iterador_crear (iterador externo):\n");
    probar_iterador_crear();
    printf("\n * Probar iterador_tiene_siguiente (iterador externo):\n");
    probar_iterador_tiene_siguiente();
    printf("\n * Probar iterador_avanzar (iterador externo):\n");
    probar_iterador_avanzar();
    printf("\n * Probar iterador_con_cada_elemento (iterador interno):\n");
    probar_iterador_con_cada_elemento();

    pa2m_mostrar_reporte();
}
