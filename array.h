#pragma once

#include <iostream>
#include <string>

// Orden: Alfabético.
// Soportará tanto mayúsculas como minúscilas, desde la A a la Z
// Las mayúsculas no afectarán a la búsqueda (usar un método UPPERCASE).
// Sin embargo, los datos se tienen que guardar tal y como se escriben.
// El arreglo debe iniciar vacío.
// PD de María: Para probar los algoritmos, podemos realizar inserciones de datos.

class OrderedStringArray
{
    private:
        std::string A[20]; // Administrará un arreglo ordenado de hasta 20 palabras
        int n; // Indica cuántos elementos están contenidos en el arreglo.
        int max; // Indica el tamaño máximo del arreglo. N no puede ser mayor a MAX.
    public:
        /* Aquí irán los métodos. */
        OrderedStringArray();

        // Inicializar / Borrar arreglo - María
        void init();
        // Mostrar arreglo - María
        void show();

        // Buscar - Fer
        // Insertar - Fer

        // Eliminar - Jesús
        // Modificar - Jesús

        // Créditos - María
        void credits();
        // Salir - María
        void salir();
};
