#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

// Estructura para registrar los contadores de métricas
struct Metricas {
    unsigned long long comparaciones = 0;
    unsigned long long intercambios = 0;
    size_t profundidad_max_recursion = 0;
};

// -------------------------------------------------------------
// 1. INSERTION SORT (Implementado)
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
// 2. MERGE SORT (Pendiente de completar)
// -------------------------------------------------------------
void merge(vector<int>& arr, int izq, int medio, int der, Metricas& m) {
    // TODO: Implementar la función de mezcla contando comparaciones e intercambios
}

void mergeSortHelper(vector<int>& arr, int izq, int der, Metricas& m, size_t prof_actual) {
    // TODO: Implementar la división recursiva y medir la profundidad de recursión
}

void mergeSort(vector<int>& arr, Metricas& m) {
    // TODO: Llamar al helper e inicializar las métricas
}

// -------------------------------------------------------------
// Generación de patrones de datos (Implementado)
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
// Función Principal (Estructura base)
// -------------------------------------------------------------
int main() {
    // Ajustado únicamente a n = 1000 y n = 10000
    vector<int> tamanos = {1000, 10000};
    vector<string> patrones = {"aleatorio", "ascendente", "descendente", "casi_ordenado", "duplicados"};
    int repeticiones = 10;
    
    mt19937 rng(2026);

    cout << "--- AVANCE DEL BENCHMARK ---" << endl;

    for (int n : tamanos) {
        for (string patron : patrones) {
            cout << "Ejecutando pruebas para n=" << n << ", patron=" << patron << "..." << endl;
            
            for (int r = 0; r < repeticiones; ++r) {
                vector<int> datos_base = generarPatron(n, patron, rng);

                // Prueba de Insertion Sort
                vector<int> datos_ins = datos_base;
                Metricas m_ins;
                auto inicio = chrono::steady_clock::now();
                insertionSort(datos_ins, m_ins);
                auto fin = chrono::steady_clock::now();
                double tiempo_ins = chrono::duration<double, milli>(fin - inicio).count();

                // TODO: Ejecutar Merge Sort cuando la función esté completa
                // TODO: Escribir los resultados en el archivo CSV (results/resultados_benchmark.csv)
            }
        }
    }

    return 0;
}
