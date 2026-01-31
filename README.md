# Suma Paralela de Arreglos con OpenMP

Proyecto de práctica para la materia de Cómputo en la Nube del Tecnológico de Monterrey (A01797412).

## Descripción

Este programa implementa la **suma paralela de dos arreglos** utilizando OpenMP. Dado dos arreglos `A` y `B` de tamaño `N`, calcula un arreglo resultado `R` donde `R[i] = A[i] + B[i]` distribuyendo el trabajo entre múltiples hilos de ejecución.

## Características

- Paralelización con **OpenMP** usando `#pragma omp parallel for`
- Configuración flexible del tamaño del arreglo y número de hilos
- Generador de números aleatorios reproducible (semilla fija)
- Validación automática de resultados
- Medición del tiempo de ejecución

## Requisitos

- Compilador C++ con soporte para OpenMP (Visual Studio, g++, clang++)
- Visual Studio 2019 o superior (incluye archivos de proyecto `.vcxproj`)

## Compilación

### Visual Studio
Abrir `solucion-paralela.sln` y compilar el proyecto.

### Linux/macOS con g++
```bash
g++ -fopenmp -O2 -o solucion_paralela ConsoleApplication1/SolucionParalela.cpp
```

## Uso

Al ejecutar el programa, se solicitan dos parámetros:

1. **Tamaño del arreglo (N)**: Cantidad de elementos en cada arreglo
2. **Número de hilos**: Cantidad de hilos a usar (0 = automático según CPU)

### Ejemplo de ejecución

```
Tamano del arreglo N (ej. 1000): 1000000
Numero de hilos (0 = automatico): 4

--- Muestra de verificacion ---
A (primeros 10): 38, 17, 90, 58, 23, 79, 55, 99, 71, 59
B (primeros 10): 27, 67, 48, 18, 100, 28, 30, 76, 18, 65
R (primeros 10): 65, 84, 138, 76, 123, 107, 85, 175, 89, 124
Validacion (primeros 20): OK

--- Info de ejecucion ---
N = 1000000
Hilos usados = 4
Tiempo (s) = 0.002345
```

## Estructura del Proyecto

```
├── ConsoleApplication1/
│   └── SolucionParalela.cpp    # Código fuente principal
├── solucion-paralela.sln       # Solución de Visual Studio
└── README.md
```

## Funcionamiento Interno

1. Lee los parámetros de entrada del usuario
2. Inicializa arreglos `A` y `B` con valores aleatorios (0-100)
3. Ejecuta la suma en paralelo con scheduling estático
4. Mide el tiempo de ejecución usando `omp_get_wtime()`
5. Valida los primeros 20 elementos del resultado
6. Muestra estadísticas de la ejecución
