# Sistemas Operativos - Práctica 1, Lab 3 - Depuración con gdb

## Tareas a realizar

1. Tutorial.
 
Este directorio contiene un programa sencillo en C en el archivo `test.c`con el
que se ilustra el video introductorio a `gdb` descrito en el enunciado de la
práctica. El alumno debe utilizarlo para seguir los pasos indicados en el video
y aprender el uso del depurador.

2. Trabajo propio

En segundo lugar, el alumno debe practicar con el depurador utilizando el
programa expuesto en el enunciado de la práctica en el apéndice dedicado a
`gdb`, que es capaz de calcular los primeros elementos de la serie de
Fibonacci, aceptando como parámetro cuantos términos se desean mostrar. Debe
crearse un archivo fuente en este directorio copiando dicho programa, y este
debe ser compilado y se debe ejecutar sin problemas.

	$ ./fib 10 
	0, 1, 1, 2, 3, 5, 8, 13, 21, 34

A continuación, el alumno ejecutará el programa paso a paso con gdb. Debe
tenerse en cuenta que los parámetros del programa no se pasan al invocar a `gdb`,
sino que se inicia gdb cargando el programa y después se especifican con el
comando `set args`, por ejemplo:

	(gdb) set args 10
    
o bien se ejecuta el programa con el comando `run` especificando los
argumentos:

	(gdb) run 10
    
El comando `start` inicia la ejecución con los argumentos especificados por
`set args` o por el último `run`.

- Establezca un punto de ruptura en la linea que contiene el `while`, para no
  tener que ejecutar el programa paso a paso hasta ese punto. Ejecute entonces
  el programa.
- Visualice las variables `fn` y `fn_1` para comprender el funcionamiento del
  programa mientras lo ejecuta paso a paso.
- Averigüe utilizando un watchpoint en qué posición de la serie aparece el
	primer término mayor que 100.000. Utilice para ello como argumento un número
	de elementos de la serie suficientemente alto.
- Averigüe en qué momento de la secuencia el programa falla, ya que empieza a
  generar números negativos. ¿Por qué puede ser que esté ocurriendo esto?
- Ejecute el programa hasta el final, y observe en qué momento durante la
  ejecución aparece por pantalla la serie de términos.
