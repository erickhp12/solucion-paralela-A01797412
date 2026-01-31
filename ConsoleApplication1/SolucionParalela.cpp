#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <omp.h>

void print_sample(const std::vector<int>& v, const std::string& name, int k = 10) {
    std::cout << name << " (primeros " << k << "): ";
    for (int i = 0; i < (int)v.size() && i < k; ++i) {
        std::cout << v[i] << (i + 1 < k && i + 1 < (int)v.size() ? ", " : "");
    }
    std::cout << "\n";
}

int main() {
    int N = 1000;
    int num_threads = 0;

    std::cout << "Tamano del arreglo N (ej. 1000): ";
    if (!(std::cin >> N) || N <= 0) {
        std::cout << "Entrada invalida. Usando N=1000.\n";
        N = 1000;
        std::cin.clear();
        std::cin.ignore(100000, '\n');
    }

    std::cout << "Numero de hilos (0 = automatico): ";
    if (!(std::cin >> num_threads) || num_threads < 0) {
        std::cout << "Entrada invalida. Usando automatico.\n";
        num_threads = 0;
        std::cin.clear();
        std::cin.ignore(100000, '\n');
    }

    if (num_threads > 0) {
        omp_set_num_threads(num_threads);
    }

    std::vector<int> A(N), B(N), R(N);

    // RNG reproducible (misma salida en cada corrida)
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 100);

    for (int i = 0; i < N; ++i) {
        A[i] = dist(rng);
        B[i] = dist(rng);
    }

    double t0 = omp_get_wtime();

#pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i) {
        R[i] = A[i] + B[i];
    }

    double t1 = omp_get_wtime();

    std::cout << "\n--- Muestra de verificacion ---\n";
    print_sample(A, "A");
    print_sample(B, "B");
    print_sample(R, "R");

    bool ok = true;
    for (int i = 0; i < N && i < 20; ++i) {
        if (R[i] != A[i] + B[i]) {
            ok = false;
            break;
        }
    }
    std::cout << "Validacion (primeros 20): " << (ok ? "OK" : "FALLO") << "\n";

    int used_threads = 1;
#pragma omp parallel
    {
#pragma omp single
        used_threads = omp_get_num_threads();
    }

    std::cout << "\n--- Info de ejecucion ---\n";
    std::cout << "N = " << N << "\n";
    std::cout << "Hilos usados = " << used_threads << "\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Tiempo (s) = " << (t1 - t0) << "\n";

    return 0;
}
