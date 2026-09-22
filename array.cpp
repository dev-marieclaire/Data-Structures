#include "array.h"
#include <stdlib.h>
#include <stdio.h>

OrderedStringArray::OrderedStringArray() { init(); max = 19; }

OrderedStringArray::init() { n = -1; }

OrderedStringArray::show()
{
    for (int i = 0; i < n; i++)
        printf("%s", A[i]);
}

OrderedStringArray::credits()
{
    printf("María Clara Isabel Jaime Benítez (Erick Amaury)\nMatrícula: 25420048");
    printf("Fernanda Tovar Osuna");
    printf("Jesús Emanuel");
}

OrderedStringArray::salir() { exit(EXIT_SUCCESS); }
