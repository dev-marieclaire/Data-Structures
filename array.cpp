#include "array.h"
#include <stdlib.h>
#include <stdio.h>
#include <cctype>

// María - Compara alfabéticamente dos Strings, ignorando mayúsculas/minúsculas.
// Retorna 1 si x > y, -1 si x < y, 0 si son iguales.
int is_greater(std::string x, std::string y)
{
    std::string aux_x, aux_y;

    for (unsigned char c : x)
        aux_x += static_cast<char>(std::toupper(c));

    for (unsigned char c : y)
        aux_y += static_cast<char>(std::toupper(c));

    if (aux_x == aux_y) return 0;

    size_t i = 0;
    while (i < aux_x.size() && i < aux_y.size())
    {
        if (aux_x[i] > aux_y[i]) return 1;
        if (aux_x[i] < aux_y[i]) return -1;
        ++i;
    }

    // Si una cadena es prefijo de la otra, la más corta es menor.
    return (aux_x.size() < aux_y.size()) ? -1 : 1;
}

OrderedStringArray::OrderedStringArray()
{
    init();
    max = sizeof(A) / sizeof(std::string);
}

void OrderedStringArray::init() { n = -1; }

void OrderedStringArray::show()
{
    std::cout << "Tamaño del arreglo: " << max << std::endl;
    std::cout << "Elementos guardados: " << n + 1 << std::endl;

    for (int i = 0; i <= n; i++)
        std::cout << A[i] << std::endl;
}

int OrderedStringArray::search(std::string v)
{
    if (v.empty())
    {
        std::cout << "Valor a buscar: ";
        std::cin >> v;
    }

    for (int i = 0; i <= n; i++)
    {
        if (is_greater(A[i], v) == 0)
            return i;
    }

    return -1;
}

void OrderedStringArray::insert(std::string v)
{
    if (v.empty())
    {
        std::cout << "Valor a insertar: ";
        std::cin >> v;
    }

    if (n == max - 1)
    {
        std::cout << "Arreglo lleno" << std::endl;
        return;
    }

    int i = n; // último índice ocupado

    // Desplaza a la derecha mientras el elemento actual sea mayor que v.
    while (i >= 0 && is_greater(A[i], v) > 0)
    {
        A[i + 1] = A[i];
        i -= 1;
    }

    A[i + 1] = v;
    n += 1;
}

int OrderedStringArray::eliminar(std::string v)
{
    if (v.empty())
    {
        std::cout << "Valor a eliminar: ";
        std::cin >> v;
    }

    int R = search(v);

    if (R >= 0)
    {
        // Primero desplaza los elementos a la izquierda.
        for (int i = R; i < n; i++)
        {
            A[i] = A[i + 1];
        }

        // Luego reduce el tamaño lógico.
        n -= 1;
    }

    return R;
}

int OrderedStringArray::modificar(std::string v)
{
    if (v.empty())
    {
        std::cout << "Valor a modificar: ";
        std::cin >> v;
    }

    int R = eliminar(v);

    if (R > -1)
    {
        std::string temp;
        std::cout << "Dame el nuevo valor: ";
        std::cin >> temp;

        insert(temp);
    }

    return R;
}

void OrderedStringArray::credits()
{
    printf("María Clara Isabel Jaime Benítez (Erick Amaury)\nMatrícula: 25420048\n");
    printf("Fernanda Tovar Osuna\nMatrícula: 25420199\n");
    printf("Jesús Emanuel\n");
}

void OrderedStringArray::salir() { exit(EXIT_SUCCESS); }
