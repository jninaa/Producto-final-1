# Comparación de Algoritmos de Ordenamiento: Insertion Sort vs Merge Sort

Este proyecto realiza un analisis comparativo y empirico entre dos algoritmos de ordenamiento interno: **Insertion Sort** (Insercion directa, cuadratico) y **Merge Sort** (Mezcla, logaritmico). El objetivo es evaluar su rendimiento en funcion del tamaño de los datos y su disposicion inicial (patrones de orden).

---

## Estructura del Repositorio

```text
.
|-- README.md              # Documentacion principal del proyecto
|-- .gitignore             # Archivos omitidos por Git
|-- docs/                  # Documentos del proyecto
|   |-- manuscrito.pdf     # Articulo cientifico en formato COMTEL / APA 7
|   |-- diapositiva.pdf    # Presentacion para la sustentacion
|-- include/               # Archivos de cabecera (interfaces comunes)
|-- src/
|   |-- main.cpp           # Codigo fuente del benchmark en C++
|-- data/                  # Archivos de datos o instancias de entrada
|-- results/
    |-- resultados_benchmark.csv  # Resultados de los experimentos

   
    Metodologia Experimental
1. Algoritmos Evaluados

    Insertion Sort: Algoritmo iterativo in-situ. Su complejidad espacial es O(1) y su complejidad temporal varia entre O(n) (mejor caso) y O(n^2) (peor y promedio caso).

    Merge Sort: Algoritmo recursivo basado en divide y venceras. Su complejidad temporal es O(n log n) en todos los casos, con una complejidad espacial auxiliar de O(n) y profundidad de recursion de O(log n).

Ambos algoritmos conservan el orden relativo de elementos iguales (son estables).
2. Escenarios y Patrones de Entrada

Se evaluaron tres tamaños de entrada: n = 1,000, 10,000 y 100,000. Para cada tamaño, se generaron 5 patrones de datos:

    Aleatorio: Valores enteros distribuidos uniformemente.

    Ascendente: Arreglo previamente ordenado.

    Descendente: Arreglo totalmente invertido (peor caso para Inserción).

    Casi Ordenado: Arreglo con un 5% de elementos permutados.

    Duplicados: Datos en un rango reducido de valores para forzar repeticiones.

3. Métricas Registradas

    Tiempo de ejecucion en milisegundos (chrono::steady_clock).

    Numero de comparaciones de elementos.

    Numero de intercambios o movimientos de datos.

    Profundidad maxima de recursion (para Merge Sort).

Se realizaron 50 repeticiones independientes por cada combinacion probada, usando el generador std::mt19937 con semilla fija (2026) para garantizar reproducibilidad.
Requisitos y Compilacion
Requisitos Previos

    Compilador de C++ compatible con el estandar C++17 (g++, clang++ o MSVC).

    Git Bash o terminal del sistema operativo.

Instrucciones de Compilacion y Ejecucion

    Clonar el repositorio:
    Bash

    git clone [https://github.com/tu-usuario/nombre-repositorio.git](https://github.com/tu-usuario/nombre-repositorio.git)
    cd nombre-repositorio
    (En este caso git clone https://github.com/jninaa/Producto-final-1)
    (cd Producto-final-1)

    Compilar el programa principal con optimizacion -O2:
    Bash

    g++ -O2 -std=c++17 src/main.cpp -o benchmark

    Ejecutar el benchmark:
    
    Bash

    ./benchmark

Al finalizar la ejecucion, se generara el archivo results/resultados_benchmark.csv con los datos crudos recolectados.

Entorno de Pruebas

    Procesador: Intel CPU

    Memoria RAM: 12 GB

    Sistema Operativo: Windows 11

    Compilador: g++ (GCC) C++17

    Semilla de Aleatoriedad: 2026

Autor

    Jose Alonso Nina Arocutipa

    Universidad Nacional Jorge Basadre Grohmann

    Escuela Profesional de Ingenieria en Informatica y Sistemas

