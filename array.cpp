#include "array.h"
#include <stdlib.h>
#include <stdio.h>

OrderedStringArray::OrderedStringArray() { init(); max = 20; }

void OrderedStringArray::init() { n = -1; }

// Muestra todos los elementos individuales del arreglo.
void OrderedStringArray::show()
{   // Recorre todo el arreglo.
    for (int i = 0; i < n; i++) // Hasta llegar a N.
        std::cout << A[i] << std::endl; // Imprime el elemento dentro del indice actual.
}

void OrderedStringArray::credits()
{
    printf("María Clara Isabel Jaime Benítez (Erick Amaury)\nMatrícula: 25420048\n");
    printf("Fernanda Tovar Osuna\n");
    printf("Jesús Emanuel\n");
}

void OrderedStringArray::salir() { exit(EXIT_SUCCESS); }
