# TDA Lista

Este tipo de dato abstracto es una lista con las operaciones de lista, como las administrativas (crear y destruir) e instartar, insertar en una posicion, eliminar, eliminar en una posicion y mostar el elemento en una posicion.

A su vez tenemos operaciones para que se comporte como una pila, teniendo las operaciones de apilar, desapilar y tope. También para que se comporte como una cola, teniendo las operaciones de encolar, desencolar y primero.

## Compilación y ejecucion

### Compilar
    
Para poder ejecutarlo primero tenemos que compilarlo, esto lo hacemos con la siguiente linea
``` bash
gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -std=c99 -O0 *.c -o lista_se 
```
De esta manera todos los archivos .c se compilan con este TDA. También esta con la ayuda del makefile se puede compilar con la linea
``` bash
make build
```
    
### Ejecutar

Para ejecutarlo vamos a usar valgrind, esto lo hacemos con la siguiente linea
``` bash
valgrind --leak-check==full --track-origins=yes --show-reachable=yes ./lista_se
```
También con makefile podemos hacer lo mismo con la linea
``` bash
make valgrind
```

## Detalles de la implementación

### Funciones crear

En este TDA tenenemos la creación de la lista y del iterador externo, ambas funcionan de forma muy parecida. Primero lo que se hace es revisar los parametros, en el caso del iterador, revisar que la lista que se pasa sea valida. Ahora sabiendo que los parametros pasados son validos se reserva memoría en el heap la cual verificamos que sea valido el puntero, para inicializar la lista o el iterador con los valores correspondientes.

### Funciones de inserción

En las 4 funciones, insertar, apilar, encolar y insertar en posición, lo primero que se hace es revisar que la lista que se pasa como parametro sea valido, ya que si la lista no es valida no podremos avanzar.

#### Insertar

Necesitamos colocar el nodo al final de la lista entonces nos aprovechamos del puntero al último nodo, asignamos el siguiente del último nodo al nodo que queremos insertar, y el nodo que queremos insertar su siguiente es null. La única excepción es cuando la lista esta vacia donde el nodo a insertar es el nodo inicio y fin de la lista.

Usé el puntero al último nodo en vez de recorrer la lista porque la complejidad de usar el puntero sería de O(1) en comparación a O(n) al recorrer la lista, con la única ventaja de no tener la excepción de la lista vacia.

#### Apilar y encolar

En ambos casos utilizo los punteros que tiene la lista para posicionarme correctamente. En el caso de apilar queremos insertar un nodo al principio de la lista, entonces el siguiente del nodo que quiero insertar tiene que ser el primer elemento de la lista, haciendo que el nodo que insertamos es el primer nodo de la lista, por lo que apilamos ese nodo. En el caso de encolar queremos insertar un nodo al final de la lista, entonces el siguiente del último nodo tiene que ser el nodo que queremos insertar, haciendo que el nodo que insertamos sea el último nodo en la lista, por lo que apilamos ese nodo.

#### Insertar en posición

Como su nombre lo indica se necesita insertar un nodo en la posición que se especifique, vamos a usar como ayuda las funciones de apilar y encolar. Usamos apilar cuando se quiera insertar al principio de la lista, y usamos encolar cuando se quiera insertar al final de la lista. En los casos donde la posición no sea el primero ni el último, recorremos la lista hasta la posición anterior al lugar donde vamos a insertar, que facilitar la comprención llamaremos nod auxiliar. El siguiente del nodo que vamos a insertar tiene que ser el siguiente del nodo auxiliar y el siguiente del nodo auxiliar tiene que ser el nodo que queremos insertar, haciendo que se haya insertado en la posición que queríamos.

Elegí utilizar las funciones apilar y encolar ya que la complejidad usandolas o no era O(n) ya que en ambos casos tendré que recorrer la lista. Además usandolas me da la ventaja de no tener que preocuparme por los casos de insertarlo al principio o al final, que agregarían complejidad a la lectura del código ya que estos casos, especialmente el insertar al pricipio, son dificiles de trabajar cuando se tiene que recorrer la lista.

### Funciones mostrar elemento

En las 4 funciones, lista_tope, lista_ultimo, lista_primero y lista_elemento_en_posicion, lo primero que se hace es revisar que la lista que se pasa como parametro sea valido, ya que si la lista no es valida no podremos mostrar nada.

#### Tope, último y primero

En los tres casos utilizamos un puntero que es parte de la lista, para el lista_tope y lista_primero utilizamos el puntero al primer nodo y devolviendo su elemento, y para lista_ultimo usamos el puntero al último nodo y devolviendo su elemento.

En el caso de la función lista_ultimo tenía la posibilidad de recorrer toda la lista, o usar el puntero, y elegí usar el puntero porque no solo su complejidad es O(1) sino que también ayuda a la lectura de la función.

#### Elemento en posición

A diferencia de las otras 3 funciones, en esta tenemos que recorrer la lista para llegar a la posición que se quiera mostar. En este caso no es necesario utilizar las funciones de lista_primero y lista_ultimo, como análogo a lo que hicimos en insertar en posicion, porque no en este caso no hay diferencia en buscar la primera, última o alguna posición en el medio.

### Funciones borrar

En las 4 funciones, lista_borrar, lista_desapilar, lista_desencolar y lista_borrar_de_posicion, lo primero que se hace es revisar que la lista que se pasa como paramentro sea valido y que no esté vacia, ya que si la lista no es valida no podremos eliminar nada.

#### Borrar

El objetivo de la función es eliminar el último nodo, lamentablemente no podemos usar el puntero al último nodo, entonces recorremos la lista hasta el anteúltimo, liberamos el último y usamos el anteúltimo como último. La única excepción para esta función es cuando la lista esta vacia, en ese caso se libera el único nodo que hay y los punteros al primero y al último son null.

#### Desapilar y desencolar

Ambas funciones hacen lo mismo, sacar el primer nodo de la pila o cola, respectivamente, entonces la explicación es la misma para ambos. Usando el puntero al primer nodo, podemos liberarlo y luego el segundo nodo se convierte en primer nodo. 

#### Borrar en posición

En la función lista_borrar_de_posicion hacemos algo muy parecido a la función lista_insertar_en_posicion donde si la posición a borrar es primer nodo, usamos lista_desapilar, si la posición a borrar termina en el último nodo, usamos lista_borrar. Para los casos intermedio recorremos la lista hasta el anterior al que queremos borrar, liberamos el nodo a borrar, y unimos el nodo anterior con el nodo siguiente.

En este caso, al igual que la función lista_insertar_en_posicion, decidí usar lista_borrar y lista_desapilar ya que la complejidad sigue siendo O(n) usandolas, y facilita la lectura del código.

### Iterador externo

En las 3 funciones, lista_iterador_tiene_siguiente, lista_iterador_avanzar y lista_iterador_elemento_actual, se verifica que el iterador es valido ya que si este no lo es no podremos hacer nada.

#### Tiene siguiente

Esta función se fija si la posición en la que esta no es null, porque si no es null significa que podría avanzar al siguiente nodo.

#### Avanzar 

Comprobamos si tiene siguiente con al funcion lista_iterador_tiene_siguiente, si tiene avanzamos la corriente del iterador. En el caso de que terminemos en null devolvemos false, sino true.

#### Elemento actual

Comprobamos si estamos en un nodo valido, diferente a null, y devolvemos el elemento del nodo.

### Iterador interno

En este caso solo tenemos una sola función que es lista_con_cada_elemento, y lo primero que hacemos es verificar que la lista y la función que se pasa por parametro sean validos ya que sino no vamos a poder hacer nada.

Lo que se hace principalmente es recorrer la lista y en cada nodo usar la función que se nos pasa por parametro con el elemento del nodo actual, y después devolvemos la cantidad de nodos que recorrimos.

## Conceptos teóricos

### Listas

### Pilas y colas

### Iteradores
    
#### Diferencia entre interno y externo

