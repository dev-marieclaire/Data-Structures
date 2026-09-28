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

int OrderedStringArray::eliminar(std::string v)
{
    // falta el buscar aquí

    int R = -1; // solo para que compile, pero hay que cambiarlo por el resultado de int R = buscar(v)
    
    if (R == -1) {
        return R;
    }

    for (int i = R; i < n; i++) {
        A[i] = A[i + 1];
    }
    
    n = n - 1; 

    return R;
}

int OrderedStringArray::modificar(std::string v)
{
    // R = Eliminar(v)
    int R = eliminar(v); 
    
    // Si R != -1
    if (R != -1) {
        std::string temp;
        
        std::cout << "Dame el nuevo valor: ";
        
        std::cin >> temp; 
        
        // Insertar(falta el insertat aquí)
        
    }

    return R;
}

void OrderedStringArray::salir() { exit(EXIT_SUCCESS); }
