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

