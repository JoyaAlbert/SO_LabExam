## Ejercicios básicos con la _shell_

A continuación se presentan unos ejercicios básicos de manejo de la línea de órdenes, que van incrementándose en dificultad, y que deberán realizarse con los datos contenidos en el repositorio proporcionado. 

Los primeros ejercicios se dan con sus respuestas, a modo de ejemplo sobre cómo deben responderse el resto de ejercicios.

1. Abra una consola y, desde el directorio donde haya clonado el repositorio, cambie el directorio de trabajo a `lab2`.
    
    
		cd ~/labssoo24-username/lab2
    
2. Crée un directorio que se llame `pruebas`. Cambie su directorio de trabajo a este directorio. Muestre el nuevo directorio de trabajo.


		mkdir pruebas 
		cd pruebas 
		pwd 
        
		/home/ubuntu/labssoo24-username/lab2/pruebas
    
3. Obtenga desde aquí, empleando una trayectoria relativa, el listado del directorio `lab2` del repositorio.


		ls ..
        
		test.tgz  
		README.md
    
4. Descomprima los contenidos del archivo `test.tgz` desde el directorio de trabajo actual, empleando el comando `tar -xzf trayectoria_relativa_de_test.tgz`. Después, liste el contenido del directorio actual.


		tar -xzf ../test.tgz 
		ls 
        
		Chapter01.txt  Chapter05.txt Chapter09.txt  Chapter13.txt  Chapter17.txt 
		Chapter02.txt  Chapter06.txt Chapter10.txt  Chapter14.txt  Chapter18.txt 
		Chapter03.txt  Chapter07.txt Chapter11.txt  Chapter15.txt  Chapter19.txt 
		Chapter04.txt  Chapter08.txt Chapter12.txt  Chapter16.txt
    
5. Como puede observar, se trata de los 19 capítulos de un libro (en realidad, un fragmento de cada uno), en formato texto plano. Liste los contenidos del directorio en formato largo, mostrando la lista de archivos ordenada por tamaño del archivo en bytes, de mayor a menor. (Consulte la página del manual para encontrar la opción requerida).

```bash
ls -lS
total 76
-rw-r--r--. 1 albertojoya albertojoya 1381 feb 25  2021 Chapter03.txt
-rw-r--r--. 1 albertojoya albertojoya 1254 feb 25  2021 Chapter05.txt
-rw-r--r--. 1 albertojoya albertojoya 1238 feb 25  2021 Chapter13.txt
-rw-r--r--. 1 albertojoya albertojoya 1237 feb 25  2021 Chapter09.txt
-rw-r--r--. 1 albertojoya albertojoya 1087 feb 25  2021 Chapter07.txt
-rw-r--r--. 1 albertojoya albertojoya 1065 feb 25  2021 Chapter04.txt
-rw-r--r--. 1 albertojoya albertojoya 1026 feb 25  2021 Chapter02.txt
-rw-r--r--. 1 albertojoya albertojoya  989 feb 25  2021 Chapter11.txt
-rw-r--r--. 1 albertojoya albertojoya  985 feb 25  2021 Chapter18.txt
-rw-r--r--. 1 albertojoya albertojoya  904 feb 25  2021 Chapter08.txt
-rw-r--r--. 1 albertojoya albertojoya  894 feb 25  2021 Chapter12.txt
-rw-r--r--. 1 albertojoya albertojoya  856 feb 25  2021 Chapter14.txt
-rw-r--r--. 1 albertojoya albertojoya  772 feb 25  2021 Chapter06.txt
-rw-r--r--. 1 albertojoya albertojoya  700 feb 25  2021 Chapter01.txt
-rw-r--r--. 1 albertojoya albertojoya  663 feb 25  2021 Chapter10.txt
-rw-r--r--. 1 albertojoya albertojoya  659 feb 25  2021 Chapter15.txt
-rw-r--r--. 1 albertojoya albertojoya  604 feb 25  2021 Chapter19.txt
-rw-r--r--. 1 albertojoya albertojoya  527 feb 25  2021 Chapter17.txt
-rw-r--r--. 1 albertojoya albertojoya  458 feb 25  2021 Chapter16.txt
```

5. Liste los contenidos del directorio en formato largo, mostrando la lista de archivos ordenada por tamaño del archivo en bytes **de menor a mayor**. (Consulte la página del manual para encontrar la opción requerida).

```bash
ls -lSr
total 76
-rw-r--r--. 1 albertojoya albertojoya  458 feb 25  2021 Chapter16.txt
-rw-r--r--. 1 albertojoya albertojoya  527 feb 25  2021 Chapter17.txt
-rw-r--r--. 1 albertojoya albertojoya  604 feb 25  2021 Chapter19.txt
-rw-r--r--. 1 albertojoya albertojoya  659 feb 25  2021 Chapter15.txt
-rw-r--r--. 1 albertojoya albertojoya  663 feb 25  2021 Chapter10.txt
-rw-r--r--. 1 albertojoya albertojoya  700 feb 25  2021 Chapter01.txt
-rw-r--r--. 1 albertojoya albertojoya  772 feb 25  2021 Chapter06.txt
-rw-r--r--. 1 albertojoya albertojoya  856 feb 25  2021 Chapter14.txt
-rw-r--r--. 1 albertojoya albertojoya  894 feb 25  2021 Chapter12.txt
-rw-r--r--. 1 albertojoya albertojoya  904 feb 25  2021 Chapter08.txt
-rw-r--r--. 1 albertojoya albertojoya  985 feb 25  2021 Chapter18.txt
-rw-r--r--. 1 albertojoya albertojoya  989 feb 25  2021 Chapter11.txt
-rw-r--r--. 1 albertojoya albertojoya 1026 feb 25  2021 Chapter02.txt
-rw-r--r--. 1 albertojoya albertojoya 1065 feb 25  2021 Chapter04.txt
-rw-r--r--. 1 albertojoya albertojoya 1087 feb 25  2021 Chapter07.txt
-rw-r--r--. 1 albertojoya albertojoya 1237 feb 25  2021 Chapter09.txt
-rw-r--r--. 1 albertojoya albertojoya 1238 feb 25  2021 Chapter13.txt
-rw-r--r--. 1 albertojoya albertojoya 1254 feb 25  2021 Chapter05.txt
-rw-r--r--. 1 albertojoya albertojoya 1381 feb 25  2021 Chapter03.txt
```

6. Liste los contenidos del directorio, mostrando la lista de archivos ordenada por fecha de última modificación, mostrando **primero el más antiguo**. (Consulte la página del manual para encontrar la opción requerida).

```bash
ls -ltr
total 76
-rw-r--r--. 1 albertojoya albertojoya  700 feb 25  2021 Chapter01.txt
-rw-r--r--. 1 albertojoya albertojoya 1026 feb 25  2021 Chapter02.txt
-rw-r--r--. 1 albertojoya albertojoya 1381 feb 25  2021 Chapter03.txt
-rw-r--r--. 1 albertojoya albertojoya 1065 feb 25  2021 Chapter04.txt
-rw-r--r--. 1 albertojoya albertojoya 1254 feb 25  2021 Chapter05.txt
-rw-r--r--. 1 albertojoya albertojoya  772 feb 25  2021 Chapter06.txt
-rw-r--r--. 1 albertojoya albertojoya 1087 feb 25  2021 Chapter07.txt
-rw-r--r--. 1 albertojoya albertojoya  904 feb 25  2021 Chapter08.txt
-rw-r--r--. 1 albertojoya albertojoya 1237 feb 25  2021 Chapter09.txt
-rw-r--r--. 1 albertojoya albertojoya  663 feb 25  2021 Chapter10.txt
-rw-r--r--. 1 albertojoya albertojoya  989 feb 25  2021 Chapter11.txt
-rw-r--r--. 1 albertojoya albertojoya  894 feb 25  2021 Chapter12.txt
-rw-r--r--. 1 albertojoya albertojoya 1238 feb 25  2021 Chapter13.txt
-rw-r--r--. 1 albertojoya albertojoya  856 feb 25  2021 Chapter14.txt
-rw-r--r--. 1 albertojoya albertojoya  659 feb 25  2021 Chapter15.txt
-rw-r--r--. 1 albertojoya albertojoya  458 feb 25  2021 Chapter16.txt
-rw-r--r--. 1 albertojoya albertojoya  527 feb 25  2021 Chapter17.txt
-rw-r--r--. 1 albertojoya albertojoya  985 feb 25  2021 Chapter18.txt
-rw-r--r--. 1 albertojoya albertojoya  604 feb 25  2021 Chapter19.txt
```

7. Cree tres directorios llamados `part1`, `part2` y `part3`. Copie, con un solo comando y sin cambiar de directorio de trabajo, los capítulos del 1 al 7 en el directorio `part1`.

```bash
mkdir part1 part2 part3 && cp Chapter0[1-7].txt part1/
```

9. Cambie el directorio de trabajo a `part2` y copie en él, con un solo comando y sin cambiar de directorio de trabajo, los capítulos del 8 al 14.

```bash
cd part2 && cp ../Chapter08.txt . && cp ../Chapter09.txt . && cp ../Chapter1[0-4].txt .
```

10. Sin cambiar de directorio de trabajo (es decir, permaneciendo en `part2`) copie con un solo comando los capítulos del 15 al 19 en el directorio `part3`.

```bash
cp ../Chapter1[5-9].txt ../part3/
```


11. Vuelva a cambiar el directorio de trabajo al directorio `pruebas` y liste los contenidos del directorio en formato largo, haciendo que se visualice tras el nombre de cada directorio el caracter `/`.

```bash
cd .. && ls -lF
total 88
-rw-r--r--. 1 albertojoya albertojoya  1381 feb 25  2021 Chapter03.txt
-rw-r--r--. 1 albertojoya albertojoya  1254 feb 25  2021 Chapter05.txt
-rw-r--r--. 1 albertojoya albertojoya  1238 feb 25  2021 Chapter13.txt
...
drwxr-xr-x. 2 albertojoya albertojoya  4096 feb 24 20:17 part1/
drwxr-xr-x. 2 albertojoya albertojoya  4096 feb 24 20:17 part2/
drwxr-xr-x. 2 albertojoya albertojoya  4096 feb 24 20:17 part3/
```

12. Sin cambiar de directorio de trabajo, cree un directorio llamado `backup` en su directorio de conexión y mueva allí todos los archivos de texto del directorio de trabajo.

```bash
mkdir -p ~/backup && mv *.txt ~/backup
```

13. Muestre por pantalla, con un solo comando y sin cambiar el directorio de trabajo, los contenidos de los 3 primeros capítulos contenidos en el directorio `part1`.

```bash
cat part1/Chapter0[1-3].txt
--- Capítulo 1 ---
En un agujero en el suelo, vivía un hobbit. No un agujero húmedo, sucio...
...
--- Capítulo 2 ---
Bilbo se levantó de un salto, y poniéndose la bata entró en el comedor...
...
--- Capítulo 3 ---
vadearon un río por un lugar ancho y poco profundo, resonante de piedras...
```

14. Sin cambiar de directorio de trabajo y con una única orden, genere un archivo en el directorio de trabajo llamado `thehobbit.txt` que contenga el texto de todos los capítulos almacenados en el directorio `part1`.

```bash
cat part1/*.txt > thehobbit.txt
```

15. Sin cambiar de directorio de trabajo y con una única orden, añada al archivo anterior los capítulos almacenados en los directorios `part2` y `part3`. Bonus points si lo hace pasándole a `cat` una única trayectoria.

```bash
cat part[23]/*.txt >> thehobbit.txt
```

16. Sin cambiar de directorio y con una única orden, genere un archivo `thehobbit.bak` con los contenidos de todos los capítulos contenidos en el directorio `backup`creado anteriormente en el directorio de conexión. Compare este archivo con el archivo `thehobbit.txt` empleando el comando `diff`, y haciendo que si ambos son iguales este comando lo indique por pantalla.

```bash
cat ~/backup/*.txt > thehobbit.bak && diff -s thehobbit.txt thehobbit.bak
Los archivos thehobbit.txt y thehobbit.bak son idénticos
```

   
17. Averigüe en cuantas lineas aparece la palabra "hobbit" en el archivo `thehobbit.txt`.

```bash
grep -c "hobbit" thehobbit.txt
7
```

18. Sin cambiar de directorio, averigüe cuantas veces aparece el nombre "Smaug" en los capítulos contenidos en cada uno de los directorios `part1`, `part2`y `part3`. No hace falta que sea con un único comando. A continuación, averigüe con un único comando el total de veces que aparece este nombre entre los tres directorios.

```bash
grep -r "Smaug" part[123] | wc -l
4
```

19. Sin cambiar de directorio y con una única orden, averigüe en qué capítulo de los contenidos en los directorios `part1`, `part2`y `part3` aparece el nombre "Balin". ¿Sería capaz de conseguir que la respuesta por pantalla fuese únicamente la trayectoria relativa del archivo?

```bash
grep -l "Balin" part[123]/*.txt
part1/Chapter03.txt
```

20. Borre el archivo `thehobbit.bak`. Borre los directorios `part1`, `part2` y `part3` junto con sus contenidos, empleando la orden `rm` (consulte la página del manual). Mueva todos los archivos almacenados en la carpeta `backup` que creó en el directorio de conexión al directorio de trabajo. Borre, sin cambiar el directorio de trabajo, el mencionado directorio `backup`.

```bash
rm thehobbit.bak && rm -rf part1 part2 part3 && mv ~/backup/*.txt . && rmdir ~/backup
```

21. Obtenga un archivo llamado "bigger.txt" que contenga la lista de los 8 capítulos de mayor tamaño del directorio en formato largo.

```bash
ls -lS | head -n 9 | tail -n 8 > bigger.txt
cat bigger.txt
-rw-r--r--. 1 albertojoya albertojoya 17299 feb 24 20:16 thehobbit.txt
-rw-r--r--. 1 albertojoya albertojoya  1381 feb 25  2021 Chapter03.txt
-rw-r--r--. 1 albertojoya albertojoya  1254 feb 25  2021 Chapter05.txt
-rw-r--r--. 1 albertojoya albertojoya  1238 feb 25  2021 Chapter13.txt
-rw-r--r--. 1 albertojoya albertojoya  1237 feb 25  2021 Chapter09.txt
-rw-r--r--. 1 albertojoya albertojoya  1087 feb 25  2021 Chapter07.txt
-rw-r--r--. 1 albertojoya albertojoya  1065 feb 25  2021 Chapter04.txt
-rw-r--r--. 1 albertojoya albertojoya  1026 feb 25  2021 Chapter02.txt
```

22. Obtenga un archivo llamado "smaller.txt" que contenga la lista de los 4 capítulos de menor tamaño del directorio en formato normal, ordenados por número de capítulo. No utilice el modificador `-r` de `ls` para esta tarea.

```bash
ls Chapter* | sort -V | head -n 4 > smaller.txt
cat smaller.txt
Chapter01.txt
Chapter02.txt
Chapter03.txt
Chapter04.txt
```

23. El programa `uniq` sirve para eliminar lineas duplicadas (siempre que sean consecutivas), y puede emplearse como filtro. Consulte la página del manual para más información. Sabiendo esto, elabore un comando empleando filtros que obtenga en cuántos de los 19 capítulos aparece la palabra "Bilbo".

```bash
grep "Bilbo" Chapter* | cut -d: -f1 | uniq | wc -l
12
```
