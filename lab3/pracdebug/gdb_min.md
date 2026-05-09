# Pruebas rápidas con GDB

## Compilar con depuración

Primero, compilar ambos programas con `-g`:

```bash
gcc -g fib.c -o fib
gcc -g test.c -o test
```

## Tutorial rápido (`test`)

Para comprobar lo básico de `gdb`:

```bash
gdb ./test
(gdb) break main
(gdb) run
(gdb) next
(gdb) print x
(gdb) next
(gdb) print x
```

## Ejercicio 2 (`fib`)

Comprobación inicial:

```bash
./fib 10
```

Depuración paso a paso desde el `while`:

```bash
gdb ./fib
(gdb) set args 10
(gdb) break fib.c:23
(gdb) run
(gdb) display fn
(gdb) display fn_1
(gdb) next
```

### Primer término > 100000

Con watchpoint:

```bash
gdb ./fib
(gdb) set args 100
(gdb) break fib.c:23
(gdb) run
(gdb) watch fn if fn > 100000
(gdb) continue
(gdb) print i
(gdb) print fn
```

Resultado que me salió:
- `fn = 121393`
- `i = 26` (posición 27 en la serie)

### Primer negativo (overflow)

También con watchpoint:

```bash
gdb ./fib
(gdb) set args 100
(gdb) break fib.c:23
(gdb) run
(gdb) watch fn if fn < 0
(gdb) continue
(gdb) print i
(gdb) print fn
```

Resultado que me salió:
- `fn = -1323752223`
- `i = 47`
- Causa: overflow de `int`
