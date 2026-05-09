# Esqueletos de Código para Examen de SO

Documento corto para memorizar patrones de código de examen en papel.

## 1. `fork` básico

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(-1);
    }

    if (pid == 0) {
        printf("Hijo: pid=%d\n", getpid());
        exit(0);
    } else {
        printf("Padre: pid=%d, hijo=%d\n", getpid(), pid);
    }

    return 0;
}
```

## 2. `fork` + `wait`

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(-1);
    }

    if (pid == 0) {
        printf("Hijo ejecutando\n");
        exit(7);
    } else {
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Codigo de salida: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
```

## 3. `fork` + `execve`

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(-1);
    }

    if (pid == 0) {
        char *argv[] = {"./prog", "arg1", NULL};
        char *envp[] = {NULL};

        execve("./prog", argv, envp);
        perror("execve");
        exit(-1);
    } else {
        wait(&status);
    }

    return 0;
}
```

## 4. Crear varios hijos en bucle

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int i;
    int n = 3;
    pid_t pid;

    for (i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(-1);
        }

        if (pid == 0) {
            printf("Soy el hijo %d con pid %d\n", i, getpid());
            exit(0);
        }
    }

    for (i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
```

## 5. `pthread_create` + `pthread_join`

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    int *p = (int *)arg;
    printf("Hilo con valor %d\n", *p);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t th;
    int x = 5;

    pthread_create(&th, NULL, thread_func, &x);
    pthread_join(th, NULL);

    return 0;
}
```

## 6. Mutex básico

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *arg) {
    int i;

    for (i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t th1, th2;

    pthread_create(&th1, NULL, thread_func, NULL);
    pthread_create(&th2, NULL, thread_func, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Counter = %ld\n", counter);
    return 0;
}
```

## 7. Memoria compartida POSIX + `mmap`

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

struct data {
    int x;
    int y;
};

int main(void) {
    int fd;
    struct data *p;

    fd = shm_open("/mi_shm", O_CREAT | O_RDWR, 0600);
    if (fd == -1) {
        perror("shm_open");
        exit(-1);
    }

    ftruncate(fd, sizeof(struct data));

    p = mmap(NULL, sizeof(struct data),
             PROT_READ | PROT_WRITE,
             MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    p->x = 1;
    p->y = 2;

    munmap(p, sizeof(struct data));
    close(fd);
    shm_unlink("/mi_shm");

    return 0;
}
```

## 8. Pipe anónimo

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pid_t pid;
    int x = 123;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(-1);
    }

    if (pid == 0) {
        close(fd[1]);
        read(fd[0], &x, sizeof(int));
        close(fd[0]);
        printf("Hijo recibe %d\n", x);
        exit(0);
    } else {
        close(fd[0]);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
```

## 9. FIFO

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int fd;
    int x = 10;

    mkfifo("mi_fifo", 0666);

    fd = open("mi_fifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }

    write(fd, &x, sizeof(int));
    close(fd);

    unlink("mi_fifo");
    return 0;
}
```

## 10. Productor-consumidor con semáforos

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int item = 0;

    while (1) {
        item++;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        printf("Consumido %d\n", item);
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

## Qué memorizar de verdad

No hace falta aprender cada programa entero. Aprende estas piezas:

### `fork`

```c
pid = fork();
if (pid < 0) { perror("fork"); exit(-1); }
if (pid == 0) { /* hijo */ }
else { /* padre */ }
```

### `wait`

```c
wait(&status);
if (WIFEXITED(status)) { WEXITSTATUS(status); }
```

### hilo

```c
pthread_create(&th, NULL, func, arg);
pthread_join(th, NULL);
```

### mutex

```c
pthread_mutex_lock(&mutex);
/* seccion critica */
pthread_mutex_unlock(&mutex);
```

### shared memory

```c
fd = shm_open(...);
ftruncate(fd, ...);
p = mmap(..., MAP_SHARED, ...);
```

### pipe

```c
pipe(fd);
fd[0]; /* lectura */
fd[1]; /* escritura */
```

## Ejercicio de mutex

Enunciado típico:

“Crear un programa con 2 hilos. Cada hilo incrementa una variable global `counter` 1.000.000 de veces. Proteger correctamente la sección crítica con un mutex y mostrar el valor final.”

### Solución

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NITER 1000000

long counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *incrementer(void *arg) {
    int i;

    for (i = 0; i < NITER; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t th1, th2;

    if (pthread_create(&th1, NULL, incrementer, NULL) != 0) {
        perror("pthread_create");
        exit(-1);
    }

    if (pthread_create(&th2, NULL, incrementer, NULL) != 0) {
        perror("pthread_create");
        exit(-1);
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Valor final de counter: %ld\n", counter);

    return 0;
}
```

## Qué te pueden pedir explicar aquí

- Sin mutex hay condición de carrera.
- `counter++` no es atómico.
- La sección crítica es la actualización de `counter`.
- `pthread_join` asegura que el `main` espere a que terminen los hilos.
- El resultado esperado es `2000000`.

## Qué suele hacer suspender en papel

- olvidar `#include <pthread.h>`
- poner mal la firma `void *func(void *arg)`
- olvidar `pthread_join`
- hacer `lock` y olvidar `unlock`
- proteger mal la sección crítica
- pensar que `counter++` es seguro sin mutex

