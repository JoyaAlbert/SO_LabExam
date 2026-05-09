# Chuleta Extensa de Laboratorios de Sistemas Operativos

Documento de repaso basado en los laboratorios de este repositorio. Está orientado a examen: qué se ha visto, qué hace cada llamada, cómo se relacionan los conceptos y qué errores suelen preguntar.

## 0. Mapa rápido de laboratorios

- `lab1`: compilación básica en C y ejecución.
- `lab2`: shell, rutas, ficheros, filtros, redirecciones y comodines.
- `lab3`: `make`, compilación separada, enlazado, depuración con `gdb`, ensamblador.
- `lab4`: procesos, `fork`, `wait`, `execve`, estado de salida.
- `lab5`: procesos cooperando en paralelo, reparto de trabajo, terminación de hijos, `kill`.
- `lab6`: hilos POSIX, `pthread_create`, `pthread_join`, exclusión mutua con mutex.
- `lab7`: señales, `signal`/`sigaction`, `alarm`, interrupciones asíncronas.
- `lab8`: memoria compartida POSIX con `shm_open` + `mmap`, semáforos en memoria compartida.
- `lab9`: productor-consumidor, buffer circular, busy waiting frente a semáforos `empty/full/mutex`.
- `lab10`: E/S de bajo nivel, ficheros binarios, `open/read/write/lseek/fstat`, `mmap`.
- `lab11`: pipes anónimos, comunicación padre-hijos o entre procesos relacionados.
- `lab12`: FIFOs (`mkfifo`), comunicación entre ejecutables independientes con `execve`.

## 1. Ideas globales que debes dominar

En SO siempre te van a mezclar estas cuatro preguntas:

1. Quién ejecuta: un proceso o un hilo.
2. Qué memoria comparten.
3. Cómo se sincronizan.
4. Cómo se comunican.

Regla mental:

- Procesos: espacio de memoria separado.
- Hilos: comparten memoria del proceso.
- Pipes/FIFOs: comunican por flujo de bytes.
- Memoria compartida: comunican compartiendo datos directamente.
- Semáforos/mutex: no transportan datos; coordinan acceso.
- Señales: notifican eventos, no valen para pasar estructuras complejas.

## 2. Lab 1: compilación básica

## Qué se vio

- Programa `hello.c`.
- Compilación simple con `cc hello.c -o hello`.
- Ejecución con `./hello`.

## Qué debes saber

- El compilador traduce C a binario ejecutable.
- `-o` fija el nombre del ejecutable.
- `./programa` ejecuta el binario del directorio actual.

## Preguntas típicas

- Diferencia entre código fuente y ejecutable.
- Por qué `./hello` y no solo `hello`.
  Porque el directorio actual no suele estar en `PATH`.

## 3. Lab 2: shell, ficheros y filtros

## Comandos base

- Navegación: `pwd`, `cd`, `ls`
- Creación y borrado: `mkdir`, `cp`, `mv`, `rm`, `rmdir`
- Visualización: `cat`, `less`
- Búsqueda: `grep`
- Comparación: `diff`
- Compresión: `tar -xzf`
- Conteo: `wc`
- Ordenación: `sort`

## Cosas importantes

- Rutas absolutas: empiezan por `/`
- Rutas relativas: dependen del directorio actual
- Comodines:
  - `*`: cualquier secuencia
  - `?`: un carácter
  - `[1-3]`: rango
- Redirecciones:
  - `>` sobrescribe
  - `>>` añade al final
- Pipes:
  - `cmd1 | cmd2`
  - la salida estándar de `cmd1` entra por la entrada estándar de `cmd2`

## Ejemplos típicos

```bash
ls -lS
ls -ltr
cat part[23]/*.txt >> thehobbit.txt
grep -c "hobbit" thehobbit.txt
grep -l "Balin" part[123]/*.txt
grep -r "Smaug" part[123] | wc -l
```

## Trampas típicas

- `uniq` solo elimina duplicados consecutivos.
- `grep -c` cuenta líneas, no ocurrencias individuales.
- `rm -r` borra recursivamente; cuidado con directorios.
- `mv` cambia nombre o mueve, según el destino.

## 4. Lab 3: compilación separada, `make` y `gdb`

## Compilación separada

Flujo:

1. Cada `.c` se compila a `.o`
2. El enlazador junta los `.o`
3. Se resuelven símbolos entre módulos

Ejemplo conceptual:

```bash
gcc -c hello.c
gcc -c imprime_es.c
gcc hello.o imprime_es.o -o hello
```

## `make`

## Para qué sirve

- Automatiza compilación.
- Recompila solo lo necesario.
- Usa dependencias entre archivos.

## Estructura mental

```make
objetivo: dependencias
	comando
```

## Qué suele preguntar el examen

- Qué recompila `make` si cambias un `.h`
  Recompila los `.c` que dependan de ese `.h`.
- Diferencia entre compilar y enlazar.
- Qué es una regla `.PHONY`.

## `gdb`

## Comandos clave

- `break` o `b`: poner breakpoint
- `run`: ejecutar
- `next`: siguiente línea sin entrar en funciones
- `step`: entra en la función
- `continue`: continuar
- `print x`: ver variable
- `watch x`: parar cuando cambie `x`
- `backtrace`: pila de llamadas
- `set args ...`: argumentos del programa

## Lo importante del lab

- Seguir ejecución paso a paso.
- Entender por qué una variable cambia.
- Detectar overflow en Fibonacci.

## Pregunta clásica

Por qué Fibonacci acaba dando negativos:

- Porque `int` tiene rango finito.
- Hay overflow aritmético.
- En C con enteros con signo, el overflow es problemático y el resultado deja de representar la secuencia correcta.

## 5. Lab 4: procesos, `fork`, `wait`, `execve`

## Modelo mental

`fork()` duplica el proceso actual.

Después de `fork` hay dos procesos ejecutando casi el mismo código:

- padre: `fork()` devuelve PID del hijo
- hijo: `fork()` devuelve `0`
- error: devuelve `-1`

## Esquema típico

```c
pid_t pid = fork();
if (pid < 0) {
    perror("fork");
    exit(-1);
}
if (pid == 0) {
    /* código del hijo */
    exit(0);
} else {
    /* código del padre */
    wait(NULL);
}
```

## `wait`

- Bloquea hasta que termina un hijo.
- Devuelve el PID del hijo terminado.
- Guarda información de terminación en `status`.

Macros:

- `WIFEXITED(status)`: terminó con `exit` o `return`
- `WEXITSTATUS(status)`: código de salida
- `WIFSIGNALED(status)`: terminó por señal

## `execve`

- Sustituye la imagen del proceso actual por otro programa.
- Si `execve` funciona, no vuelve.
- Si vuelve, hubo error.

Patrón:

```c
if (fork() == 0) {
    execve("./prog", argv, envp);
    perror("execve");
    exit(-1);
}
wait(NULL);
```

## Qué no cambia con `execve`

- El PID del proceso.
- Algunos descriptores de fichero abiertos, salvo que se marquen para cerrar.

## Qué sí cambia

- Código, datos, pila, programa cargado.

## Lo visto en `race.c`

- Se crean varios hijos con `fork`.
- Cada hijo ejecuta `player()`.
- El padre usa `wait` varias veces.
- Se mide tiempo con `gettimeofday`.
- Se clasifica a cada hijo según su finalización.

## Trampas típicas

- No cerrar con `exit` en el hijo cuando corresponde.
- Hacer `fork` dentro de bucles y no controlar quién sigue bifurcando.
- Creer que padre e hijo comparten variables normales después de `fork`.
  No: cada uno tiene su copia.

## 6. Lab 5: multiproceso, reparto de trabajo, terminación coordinada

## Qué se vio

- Un problema de minería dividido entre varios procesos.
- Reparto del espacio de búsqueda.
- Lanzamiento de hijos.
- Uso de `execve` para que cada hijo ejecute el minero.
- El padre espera resultados y mata a los restantes si uno encuentra solución.

## Ideas importantes

- Paralelismo por procesos.
- División del rango de trabajo.
- Supervisión del padre.
- Terminación temprana con `kill(SIGTERM)`.

## Patrón general

1. Dividir el trabajo.
2. Crear N hijos.
3. Cada hijo ejecuta una versión trabajadora.
4. El padre hace `wait`.
5. Si uno resuelve:
   termina al resto.

## Cuándo usar procesos aquí

- Aislamiento fuerte.
- Ejecuciones independientes.
- Fácil reaprovechar programa ya existente con `execve`.

## Riesgos típicos

- Repartir mal rangos y dejar huecos o solapes.
- No tratar bien fallos de `fork`.
- No distinguir entre:
  - “no encontré solución”
  - “hubo error”
  - “me mató una señal”

## 7. Lab 6: hilos POSIX y mutex

## Concepto central

Los hilos comparten:

- variables globales
- heap
- descriptores de fichero

Cada hilo tiene:

- su pila
- sus registros
- su contador de programa

## API básica

```c
pthread_t th;
pthread_create(&th, NULL, funcion_hilo, arg);
pthread_join(th, NULL);
```

La función del hilo tiene forma:

```c
void *func(void *arg)
```

## Carrera crítica

Si varios hilos leen y escriben la misma variable sin protección, hay condición de carrera.

Ejemplo conceptual:

```c
counter++;
```

No es atómico.

Realmente implica leer, modificar y escribir. Dos hilos pueden pisarse.

## Mutex

Sirve para exclusión mutua.

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&mutex);
/* sección crítica */
pthread_mutex_unlock(&mutex);
pthread_mutex_destroy(&mutex);
```

## Lo visto en integración multihilo

- Reparto de intervalos entre hilos.
- Cada hilo calcula una suma parcial.
- Un mutex protege la acumulación en el resultado global.
- Después se hace `join` de todos.

## Cosas que suelen preguntar

- Diferencia entre concurrencia y paralelismo.
- Diferencia entre proceso e hilo.
- Qué comparten los hilos.
- Qué pasa si olvidas `join`.
- Qué pasa si olvidas liberar el mutex.

## Errores típicos

- Pasar a todos los hilos la misma dirección de una variable que cambia en el bucle.
- Proteger demasiado código con mutex y perder paralelismo.
- Acceder a variables compartidas sin sincronización.

## 8. Lab 7: señales

## Qué es una señal

Mecanismo asíncrono por el que el sistema o un proceso notifica un evento a otro proceso.

## Señales importantes

- `SIGINT`: Ctrl+C
- `SIGTERM`: petición estándar de terminación
- `SIGKILL`: terminación forzada, no capturable
- `SIGALRM`: alarma tras `alarm()`
- `SIGUSR1`, `SIGUSR2`: señales de usuario

## Instalación de manejadores

Forma simple:

```c
signal(SIGINT, handler);
```

Forma robusta:

```c
struct sigaction a;
a.sa_handler = handler;
sigemptyset(&a.sa_mask);
a.sa_flags = 0;
sigaction(SIGINT, &a, NULL);
```

Con información adicional:

```c
a.sa_sigaction = handler3;
a.sa_flags = SA_SIGINFO;
```

## Lo visto en el lab

- Mostrar estado del minero con `SIGUSR1`.
- Usar `SIGINT` para pedir estado y confirmar salida.
- Temporización con `alarm(2)`.
- Cancelar petición con `SIGALRM`.

## Idea clave

Las señales interrumpen la ejecución en un punto impredecible.

Por eso, en un handler:

- no conviene hacer lógica compleja
- no conviene asumir estado consistente

## Trampas típicas de examen

- `SIGKILL` y `SIGSTOP` no pueden capturarse ni ignorarse.
- Una señal no “espera” a que el programa esté listo.
- Un handler puede ejecutarse entre dos instrucciones críticas.
- No todo es seguro dentro de un handler.

## Pregunta muy típica

Diferencia entre `signal` y `sigaction`:

- `sigaction` es la interfaz moderna y más controlable.
- permite máscaras, flags y recibir `siginfo_t`.

## 9. Lab 8: memoria compartida POSIX

## Objetivo

Compartir datos entre procesos sin copiar por pipe.

## Secuencia típica

1. `shm_open`
2. `ftruncate`
3. `mmap`
4. acceso a la zona compartida
5. opcionalmente `munmap`, `close`, `shm_unlink`

## Ejemplo mental

```c
int fd = shm_open("/miobj", O_CREAT | O_RDWR, 0600);
ftruncate(fd, sizeof(struct data));
struct data *p = mmap(NULL, sizeof(struct data),
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
```

## Puntos clave

- `shm_open` crea o abre un objeto de memoria compartida.
- `ftruncate` fija su tamaño.
- `mmap` lo mapea al espacio de direcciones del proceso.
- `MAP_SHARED` hace visibles los cambios a otros procesos que mapearon lo mismo.

## Lo visto en `tickets`

- Se inicializa una estructura compartida con:
  - tickets disponibles
  - tickets vendidos
  - precio
  - caja total
- Varios procesos venden entradas.
- Se usa un semáforo dentro de la estructura para proteger la sección crítica.

## Semáforos en memoria compartida

```c
sem_init(&t->sem, 1, 1);
```

El segundo parámetro `pshared = 1` indica que el semáforo es compartido entre procesos.

## Errores típicos

- Olvidar `ftruncate` antes de `mmap`.
- Usar `MAP_PRIVATE` en vez de `MAP_SHARED`.
- Inicializar el semáforo con `pshared = 0` cuando lo compartirán procesos.
- Acceder concurrentemente sin proteger la estructura compartida.

## 10. Lab 9: productor-consumidor

## Problema

Un productor genera elementos y un consumidor los retira. Hay que coordinar:

- exclusión mutua
- huecos disponibles
- elementos disponibles

## Primera versión: busy waiting

En `prodcons` se ve una solución con espera activa:

- entrar en bucle
- comprobar condición
- si no se cumple, repetir

Problema:

- desperdicia CPU
- mala escalabilidad

## Segunda versión: semáforos `empty/full/mutex`

Patrón clásico:

- `mutex`: protege la sección crítica
- `empty`: número de huecos libres
- `full`: número de elementos listos

Inicialización habitual:

```c
sem_init(&mutex, 1, 1);
sem_init(&empty, 1, BUFFER_SIZE);
sem_init(&full, 1, 0);
```

## Productor

```c
sem_wait(&empty);
sem_wait(&mutex);
/* insertar */
sem_post(&mutex);
sem_post(&full);
```

## Consumidor

```c
sem_wait(&full);
sem_wait(&mutex);
/* extraer */
sem_post(&mutex);
sem_post(&empty);
```

## Buffer circular

Variables típicas:

- `in`: próxima posición de inserción
- `out`: próxima posición de extracción
- `count`: cuántos elementos hay

Actualización:

```c
in = (in + 1) % BUFFER_SIZE;
out = (out + 1) % BUFFER_SIZE;
```

## Lo que te pueden preguntar

- Por qué `empty` empieza en `BUFFER_SIZE`.
- Por qué `full` empieza en `0`.
- Por qué hace falta `mutex` además de `empty/full`.
  Porque `empty/full` controlan cantidad; `mutex` protege la sección crítica.

## 11. Lab 10: ficheros binarios y `mmap`

## E/S de bajo nivel

Llamadas clave:

- `open`
- `read`
- `write`
- `lseek`
- `close`
- `fstat`

## Diferencia con stdio

- Bajo nivel: descriptores de fichero, llamadas del sistema.
- `stdio`: `FILE *`, buffering de biblioteca C.

## `lseek`

Reposiciona el offset del fichero:

```c
lseek(fd, 0, SEEK_SET);
lseek(fd, 0, SEEK_END);
lseek(fd, -sizeof(x), SEEK_CUR);
```

## `fstat`

Permite obtener tamaño y metadatos del fichero:

```c
struct stat s;
fstat(fd, &s);
```

## `mmap` sobre ficheros

En vez de leer y escribir manualmente, mapeas el fichero en memoria:

```c
pe = mmap(NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
```

Entonces puedes tratar el fichero como un array en memoria.

## Lo visto en `gradesort_mmap`

- `fstat` obtiene tamaño.
- `mmap` mapea el fichero.
- Se calcula `nelem = s.st_size / sizeof(struct evaluation)`.
- Se ordena como si fuese un array normal.
- `munmap` libera el mapeo.

## Ventajas de `mmap`

- código más simple para acceso aleatorio
- el SO gestiona la paginación
- puede ser mucho más rápido

## Inconvenientes

- cuidado con tamaños y alineación
- acceso fuera de rango puede fallar grave
- no sustituye toda la lógica de sincronización si varios procesos escriben

## Comparación típica

- `read/write`: control explícito del flujo de E/S
- `mmap`: acceso directo tipo memoria

## 12. Lab 11: pipes anónimos

## Qué son

Canales unidireccionales de bytes entre procesos relacionados.

```c
int fd[2];
pipe(fd);
```

- `fd[0]`: lectura
- `fd[1]`: escritura

## Uso correcto

Cada proceso debe cerrar los extremos que no usa.

Esto es muy importante porque:

- evita fugas de descriptores
- permite que `read` vea EOF cuando toca

## Patrón básico

```c
pipe(fd);
if (fork() == 0) {
    close(fd[1]);
    read(fd[0], ...);
    close(fd[0]);
    exit(0);
} else {
    close(fd[0]);
    write(fd[1], ...);
    close(fd[1]);
    wait(NULL);
}
```

## Lo visto en `picalc_pipes`

Arquitectura:

- `dispatcher`: reparte trabajos
- `workers`: calculan parciales
- `gatherer`: recoge resultados

Dos pipes:

- uno de trabajo
- uno de resultados

## Ideas clave

- varios hijos heredan los descriptores tras `fork`
- si no cierras el lado de escritura correcto, el lector puede bloquearse esperando más datos
- `read` devuelve `0` al llegar EOF

## Preguntas típicas

- Por qué cerrar descriptores no usados.
- Si un pipe es bidireccional.
  No: conceptualmente es unidireccional.
- Si sirve entre procesos no emparentados.
  En general se usa entre relacionados; para no relacionados suele preferirse FIFO o sockets.

## 13. Lab 12: FIFOs

## Qué son

Pipes con nombre en el sistema de ficheros.

Se crean con:

```c
mkfifo("myfifo", 0666);
```

Se abren con `open` como si fuesen un fichero.

## Diferencia con pipe anónimo

- pipe anónimo:
  - no tiene nombre en el sistema de ficheros
  - se crea con `pipe`
  - típico entre procesos relacionados
- FIFO:
  - sí tiene nombre
  - se crea con `mkfifo`
  - puede usarse entre procesos independientes

## Lo visto en `picalc_fifos`

- Se crean dos FIFOs: una para trabajo y otra para resultados.
- Luego se lanzan procesos con `fork` + `execve`:
  - `dispatcher`
  - `workers`
  - `gatherer`
- Los ejecutables se comunican abriendo las FIFOs por nombre.
- Al final se hace `unlink` de las FIFOs.

## Detalles importantes

- Abrir una FIFO para escritura puede bloquear hasta que haya lector.
- Abrir una FIFO para lectura puede bloquear hasta que haya escritor.
- Por eso importa el orden de creación y lanzamiento de procesos.

## Trampas típicas

- Confundir `unlink` con cerrar descriptor.
- No borrar la FIFO al terminar y dejar basura en el sistema.
- Creer que la FIFO almacena registros; en realidad transmite bytes.

## 14. Comparativas esenciales

## `fork` vs `pthread_create`

- `fork` crea proceso nuevo.
- `pthread_create` crea hilo dentro del mismo proceso.
- Tras `fork`, memoria separada.
- Entre hilos, memoria compartida.
- Crear hilos suele ser más ligero.
- Procesos aíslan mejor fallos.

## `execve` vs llamada a función

- llamar a una función mantiene el mismo programa
- `execve` reemplaza el programa entero del proceso

## Pipe vs FIFO vs memoria compartida

- Pipe:
  - simple
  - flujo de bytes
  - ideal para procesos relacionados
- FIFO:
  - como pipe pero con nombre
  - útil entre programas separados
- Memoria compartida:
  - muy eficiente para grandes datos
  - necesita sincronización adicional

## Mutex vs semáforo

- mutex:
  - exclusión mutua
  - normalmente 1 recurso crítico
- semáforo:
  - contador
  - puede representar varios recursos o eventos

## Busy waiting vs bloqueo

- busy waiting:
  - consume CPU mientras espera
- bloqueo con semáforos:
  - el proceso/hilo duerme hasta que puede continuar

## `read/write` vs `mmap`

- `read/write`: acceso explícito por llamadas
- `mmap`: acceso por memoria

## 15. Llamadas y patrones que conviene memorizar

## Manejo de errores

```c
if (algo == -1) {
    perror("algo");
    exit(-1);
}
```

## `fork`

```c
pid_t pid = fork();
if (pid < 0) { perror("fork"); exit(-1); }
if (pid == 0) { /* hijo */ exit(0); }
/* padre */
```

## `wait`

```c
int status;
pid_t p = wait(&status);
if (WIFEXITED(status)) {
    int code = WEXITSTATUS(status);
}
```

## `execve`

```c
char *argv[] = {"./prog", "arg1", NULL};
char *envp[] = {NULL};
execve("./prog", argv, envp);
perror("execve");
exit(-1);
```

## Hilos

```c
pthread_t th;
pthread_create(&th, NULL, func, arg);
pthread_join(th, NULL);
```

## Mutex

```c
pthread_mutex_lock(&m);
/* sección crítica */
pthread_mutex_unlock(&m);
```

## Señales

```c
signal(SIGINT, handler);
alarm(2);
```

## Memoria compartida

```c
fd = shm_open("/obj", O_CREAT | O_RDWR, 0600);
ftruncate(fd, size);
p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
```

## Pipe

```c
pipe(fd);
read(fd[0], &x, sizeof(x));
write(fd[1], &x, sizeof(x));
```

## FIFO

```c
mkfifo("fifo", 0666);
fd = open("fifo", O_RDONLY);
```

## `mmap` de fichero

```c
fstat(fd, &s);
p = mmap(NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
munmap(p, s.st_size);
```

## 16. Errores típicos de examen

- Confundir PID de padre con PID de hijo tras `fork`.
- Usar variables normales para comunicar procesos tras `fork`.
- No cerrar descriptores de pipes/FIFOs.
- Olvidar que `execve` solo vuelve si falla.
- Acceder a memoria compartida sin sincronizar.
- Usar `sem_init(..., 0, ...)` para procesos distintos.
- Pensar que `counter++` es atómico.
- No distinguir proceso terminado por `exit` de proceso terminado por señal.
- No recalcular el número de elementos de un fichero binario con `sizeof`.
- Creer que `grep -c` cuenta apariciones en vez de líneas.
- Olvidar que `uniq` requiere líneas consecutivas.
- No hacer `munmap` o no limpiar con `unlink`/`shm_unlink` cuando procede.

## 17. Preguntas cortas de examen con respuesta

## ¿Qué devuelve `fork`?

- `-1` en error
- `0` en el hijo
- PID del hijo en el padre

## ¿Qué hace `wait`?

Bloquea al padre hasta que termina un hijo y recupera su estado.

## ¿Qué hace `execve`?

Reemplaza el programa actual por otro ejecutable.

## ¿Padre e hijo comparten memoria tras `fork`?

No de forma normal; cada uno tiene su copia del espacio de direcciones.

## ¿Los hilos comparten variables globales?

Sí.

## ¿Para qué sirve un mutex?

Para garantizar exclusión mutua en una sección crítica.

## ¿Para qué sirve `SIGUSR1`?

Es una señal definida para uso de la aplicación.

## ¿Qué diferencia hay entre `pipe` y `mkfifo`?

`pipe` crea un canal anónimo; `mkfifo` crea un canal con nombre en el sistema de ficheros.

## ¿Qué ventaja tiene `mmap`?

Permite tratar un fichero como memoria y puede reducir sobrecoste de E/S explícita.

## ¿Qué hace `ftruncate` en memoria compartida?

Fija el tamaño del objeto compartido.

## 18. Mini guía de decisión

Si el examen pregunta “qué mecanismo usarías”, piensa así:

- Quiero lanzar otro programa y aislarlo:
  `fork` + `execve`
- Quiero paralelismo dentro del mismo proceso:
  `pthread_create`
- Quiero que procesos emparentados se pasen flujo simple:
  `pipe`
- Quiero comunicación por nombre entre programas distintos:
  `mkfifo`
- Quiero compartir grandes datos entre procesos:
  `shm_open` + `mmap`
- Quiero proteger una sección crítica:
  mutex o semáforo binario
- Quiero modelar recursos disponibles o eventos:
  semáforo contador
- Quiero reaccionar a eventos asíncronos:
  señales

## 19. Cómo estudiar esto en modo examen

Orden recomendado:

1. `lab4`, `lab6`, `lab7`
   procesos, hilos y señales son núcleo duro.
2. `lab8`, `lab9`
   sincronización y memoria compartida.
3. `lab11`, `lab12`
   IPC por pipes y FIFOs.
4. `lab10`
   E/S y `mmap`.
5. `lab2`, `lab3`
   shell, `make`, `gdb`, que también suelen entrar.

## 20. Resumen final en una página mental

- `fork`: clona proceso.
- `execve`: sustituye programa.
- `wait`: recoge terminación de hijos.
- `pthread_create`: crea hilo.
- mutex: protege sección crítica.
- señal: evento asíncrono.
- `shm_open` + `mmap`: memoria compartida entre procesos.
- `sem_init(pshared=1)`: semáforo compartido entre procesos.
- `pipe`: canal anónimo.
- `mkfifo`: canal con nombre.
- `open/read/write/lseek`: E/S de bajo nivel.
- `fstat`: tamaño y metadatos.
- `mmap`: fichero como memoria.
- productor-consumidor:
  `empty`, `full`, `mutex`.

## 21. Repositorio usado como base

Esta chuleta se ha construido a partir de los laboratorios presentes en:

- `lab1`
- `lab2`
- `lab3`
- `lab4`
- `lab5`
- `lab6`
- `lab7`
- `lab8`
- `lab9`
- `lab10`
- `lab11`
- `lab12`

