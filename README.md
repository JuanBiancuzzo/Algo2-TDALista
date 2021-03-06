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

Esta función se fija si el nodo en el que estamos parado es valido, porque si es valido significa que podría avanzar al siguiente nodo.

#### Avanzar 

Comprobamos si tiene siguiente con al funcion lista_iterador_tiene_siguiente, si tiene avanzamos la corriente del iterador. En el caso de que terminemos en null devolvemos false, sino true.

#### Elemento actual

Comprobamos si estamos en un nodo valido, diferente a null, y devolvemos el elemento del nodo.

### Iterador interno

En este caso solo tenemos una sola función que es lista_con_cada_elemento, y lo primero que hacemos es verificar que la lista y la función que se pasa por parametro sean validos ya que sino no vamos a poder hacer nada.

Lo que se hace principalmente es recorrer la lista y en cada nodo usar la función que se nos pasa por parametro con el elemento del nodo actual, y después devolvemos la cantidad de nodos que recorrimos.

## Conceptos teóricos

### Listas

Se puede entender a una lista como un conjunto de elementos vinculados de forma lineal. Si lo vemos con un ejemplo puede quedar más claro, supongamos que tenemos que comprar varias cosas pero son tantas que va a ser mejor anotarlas, entonces uno saca una hoja para anotar y pone como primer cosa a coprar "pan", abajo de ese pone "agua", y así sigue poniendo las cosas que tiene que comprar. Ahora esto es una lista, las cosas que va a comprar son los elementos de la lista, y el hecho de que cada elemento este abajo de otro elemento haciendo una linea hacia abajo, mustra que estan vinculados de forma lineal.

Ahora hablando de las operaciones que tiene una lista, porque no se puede definir una lista sin sus operaciones. Que son la creación de la lista, que su análogo al ejemplo de antes sería sacar una hoja para anotar; si esta vacia la lista, que sería fijarse si no hay elementos; insertar en la lista, que sería agregar un objeto que se quiere comprar a cualquier parte de la lista; eliminar en la lista, que sería borrar un objeto; ver elemento, que sería leer que objeto pusiste en la lista; destruir la lista, que sería tirar la hoja a la basura (o reciclar) porque ya no la vas a usar.

En nuestro ejemplo de la lista de compra sería un ejemplo de una lista doblemente enlazada porque uno puede ir de un objeto de compra hacia arriba o abajo para ver otro objeto de compra. Pero esto no es la única forma de tener una lista, existen la lista simplemente enlazadas donde solamente podes ver el siguiente elemento en la lista. Hay que enteder que aunque el ejemplo de la lista de compra es bastante parecido a como es una lista, en una lista solo podes ver un elemento a la vez y el hecho de que sea simple o doblemente enlazada implica como uno se puede mover en esa lista, es decir, si es simplemente enlazada solo se puede avanzar pero en la doblemente enlazada podes avanzar o retroceder.

### Pilas y colas

Al igual que la lista, la pila y la cola son un conjunto de elemento vinculados de forma lineal, pero cada uno tiene una caracteristica fundamental.

Para la pila esta en la prioridad que se le da al tope de la pila, porque cuando se inserta un elemento se pone en el tope, si uno saca un elemento lo saca del tope, si quiere ver el elemento se ve el elemento del tope. Esta prioridad permite que si uno tiene que guardar elementos donde el último que entra tiene la mayor importancia. Un ejemplo de esto es por ejemplo si uno esta estudiando y esta leyendo un libro de matemática, y empieza a hablar de transformaciones lineales pero ese tema no lo sabes entonces dejas el libro y abris un libro donde explican las transformaciones lineales, pero ahora hablan de espacios vectoriales, entonces apilas el libro encima del anterior, y buscas un libro que expliquen espacios vectoriales. Por suerte se entiende todo lo que decia el libro entonces guardas el libro de espacios vectoriales en la biblioteca, y agarras el libro de transformaciones lineales, gracias a lo que leiste ahora podes entender ese libro y al terminar guardas el libro en la biblioteca. Por último, terminas de leer el último libro y lo guardas en la biblioteca. El libro que tenías en tus manos era el tope, y dejar los libros a un costado era el resto de la pila.
Con ese ejemplo se puede ver la importancia que se le da al tope en una pila que es su caracteristica fundamental.

Para la cola la caracteristica fundamental es el manejo de la prioridad, la prioridad siempre esta en el primero que llego, y lo último que llega es lo menos importante. Un ejemplo es la fila del supermercado donde el primero en llegar es el primero en ser atendido y el último tiene que esperar su turno. Esto se también en las operaciones de la cola, donde al insertar es al final de la cola, pero cuando uno quiere ver el valor de un elemento, se ve el valor del primer elemento.

### Iteradores

La funcionalidad de un iteradores es recorrer una lista, pila o cola, de forma independiente a la estructura que esta recorriendo. Esto hace que pueda ver el estado de toda la estructura sin tener que navegarla ya sea porque no es tan práctico como lo es en una lista, o directamente imposible por las operaciones de la estructura como la pila y cola.
    
#### Diferencia entre interno y externo

La funcionalidad es la misma por eso son iteradores, pero interno se refiere que tiene acceso a la estructura interna de la lista, pila o cola, que le da la ventaja que puede ser más directo en su forma de moverse en la estructura misma. Mientras que el iterador externo esta limitado a usar las mismas herramientas que usaria el usuario al interactuar con la lista, pila o cola.

Esto hace que los iteradores internos sean menos complejos algoritmicamente que los iteradores externos, suponiendo que estan hechos de la forma más eficiente. Pero la desventaja que tiene un iterador interno sobre el externo, es que el interno tiene que vernír con la estructura, mientras que el externo no esta limitado a ese caso, haciendo que el externo aunque más complejo algoritmicamente más probable de usarse por el hecho que el mismo usuario puede crealo para esa situación.

