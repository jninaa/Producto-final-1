#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;
using namespace std:chrono;

// Estructura para registrar los contadores de métricas
struct Metricas {
    unsigned long long comparaciones = 0;
    unsigned long long intercambios = 0;
    size_t profundidad_max_recursion = 0;
};

// -------------------------------------------------------------
// 1. INSERTION SORT (Inserción Directa - Iterativo)
// -------------------------------------------------------------
void insertionSort(vector<int>& arr, Metricas& m) {
    m.comparaciones = 0;
    m.intercambios = 0;
    m.profundidad_max_recursion = 0;
    
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int clave = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            m.comparaciones++;
            if (arr[j] > clave) {
                arr[j + 1] = arr[j];
                m.intercambios++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = clave;
    }
}

// -------------------------------------------------------------
// 2. MERGE SORT (Mezcla - Recursivo)
// -------------------------------------------------------------
void merge(vector<int>& arr, int izq, int medio, int der, Metricas& m) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[izq + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2) {
        m.comparaciones++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        m.intercambios++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++; m.intercambios++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++; m.intercambios++;
    }
}

void mergeSortHelper(vector<int>& arr, int izq, int der, Metricas& m, size_t prof_actual) {
    if (prof_actual > m.profundidad_max_recursion) {
        m.profundidad_max_recursion = prof_actual;
    }

    if (izq < der) {
        int medio = izq + (der - izq) / 2;
        mergeSortHelper(arr, izq, medio, m, prof_actual + 1);
        mergeSortHelper(arr, medio + 1, der, m, prof_actual + 1);
        merge(arr, izq, medio, der, m);
    }
}

void mergeSort(vector<int>& arr, Metricas& m) {
    m.comparaciones = 0;
    m.intercambios = 0;
    m.profundidad_max_recursion = 0;
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1, m, 1);
    }
}

// -------------------------------------------------------------
// Generación de Patrones de Datos
// -------------------------------------------------------------
vector<int> generarPatron(int n, string patron, mt19937& rng) {
    vector<int> vec(n);
    if (patron == "aleatorio") {
        uniform_int_distribution<int> dist(1, 1000000);
        for (int i = 0; i < n; ++i) vec[i] = dist(rng);
    } else if (patron == "ascendente") {
        for (int i = 0; i < n; ++i) vec[i] = i;
    } else if (patron == "descendente") {
        for (int i = 0; i < n; ++i) vec[i] = n - i;
    } else if (patron == "casi_ordenado") {
        for (int i = 0; i < n; ++i) vec[i] = i;
        int perm = max(1, (int)(n * 0.05));
        uniform_int_distribution<int> dist(0, n - 1);
        for (int i = 0; i < perm; ++i) swap(vec[dist(rng)], vec[dist(rng)]);
    } else if (patron == "duplicados") {
        uniform_int_distribution<int> dist(1, 15);
        for (int i = 0; i < n; ++i) vec[i] = dist(rng);
    }
    return vec;
}

// -------------------------------------------------------------
// Función Principal
// -------------------------------------------------------------
int main() {
    cout << "=== INICIANDO BENCHMARK DE ALGORITMOS DE ORDENAMIENTO ===" << endl;

    ofstream csv("../results/resultados_benchmark.csv");
    if (!csv.is_open()) {
        csv.open("resultados_benchmark.csv");
    }

    csv << "algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,profundidad_recursion\n";

    vector<int> tamanos = {1000, 10000};
    vector<string> patrones = {"aleatorio", "ascendente", "descendente", "casi_ordenado", "duplicados"};
    int repeticiones = 10;
    
    mt19937 rng(2026);

    for (int n : tamanos) {
        cout << "\n[SECCION] Procesando tamano n = " << n << endl;

        for (string patron : patrones) {
            cout << " -> Evaluando patron: " << patron << "..." << endl;

            for (int r = 0; r < repeticiones; ++r) {
                vector<int> datos_base = generarPatron(n, patron, rng);

                // Benchmark Insertion Sort
                {
                    vector<int> datos = datos_base;
                    Metricas m;
                    auto inicio = steady_clock::now();
                    insertionSort(datos, m);
                    auto fin = steady_clock::now();
                    double tiempo = duration<double, milli>(fin - inicio).count();

                    csv << "InsertionSort," << n << "," << patron << "," << r << "," 
                        << tiempo << "," << m.comparaciones << "," << m.intercambios << "," 
                        << m.profundidad_max_recursion << "\n";
                }

                // Benchmark Merge Sort
                {
                    vector<int> datos = datos_base;
                    Metricas m;
                    auto inicio = steady_clock::now();
                    mergeSort(datos, m);
                    auto fin = steady_clock::now();
                    double tiempo = duration<double, milli>(fin - inicio).count();

                    csv << "MergeSort," << n << "," << patron << "," << r << "," 
                        << tiempo << "," << m.comparaciones << "," << m.intercambios << "," 
                        << m.profundidad_max_recursion << "\n";
                }
            }
        }
    }

    csv.close();
    cout << "\n=== BENCHMARK FINALIZADO EXITOSAMENTE ===" << endl;
    cout << "Resultados guardados en el archivo CSV." << endl;
    
    return 0;
}
