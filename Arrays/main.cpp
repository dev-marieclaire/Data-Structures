#include "array.h"

int main()
{
    OrderedStringArray array;

    char option;

    do
    {
        std::cout << "0) Salir.\n" << "1) Mostrar.\n" << "2) Buscar.\n" << "3) Insertar.\n" << "4) Eliminar.\n" << "5) Modificar.\n" << "6) Créditos\n";
        std::cout << "Ingrese una opcion:\n>> ";
        std::cin >> option;

        switch(option)
        {
            case '0':
                array.salir();
                break;
            case '1':
                array.show();
                break;
            case '2':
                array.search("");
                break;
            case '3':
                array.insert("");
                break;
            case '4':
                array.eliminar("");
                break;
            case '5':
                array.modificar("");
                break;
            case '6':
                array.credits();
                break;
            default:
                std::cout << "Opción inválida, vuelva a intentar." << std::endl;
                break;
        }
    } while(option != '0');

    array.credits();
    array.salir();
}
