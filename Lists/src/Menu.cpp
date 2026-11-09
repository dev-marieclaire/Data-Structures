#include "Menu.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <cstddef>

Menu::Menu() {}

void Menu::clearScreen() const
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Menu::pressEnter() const
{
    std::cout << "\nPresione ENTER para continuar...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool Menu::promptYesNo(const std::string& q) const
{
    while(true)
    {
        std::cout << q << " (s/n)\n>> ";
        std::string s;
        std::getline(std::cin, s);
        if (s == "s" || s == "S" || s == "si" || s == "Si" || s == "SI") return true;
        if (s == "n" || s == "N" || s == "no" || s == "No" || s == "NO") return false;
        std::cout << "Respuesta invalida, use s o n.\n";
    }
}

int Menu::promptInt(const std::string& prompt, int min, int max) const
{
    while(true)
    {
        if (!prompt.empty()) std::cout << prompt << " (" << min << "-" << max << ")\n";
        std::cout << ">> ";
        std::string s;
        std::getline(std::cin, s);
        try
        {
            std::size_t pos = 0;
            int v = std::stoi(s, &pos);
            if (pos == s.size() && v >= min && v <= max) return v;
        } catch (...) {}
        std::cout << "Entrada invalida. Intente de nuevo.\n";
    }
}

Date Menu::promptDate(const std::string& prompt) const
{
    while(true)
    {
        std::cout << prompt << " (dd/MM/yyyy)\n>> ";
        std::string s;
        std::getline(std::cin, s);

        std::istringstream iss(s);
        int day, month, year;
        char s1, s2, extra;

        if (!(iss >> day >> s1 >> month >> s2 >> year)
            || s1 != '/'
            || s2 != '/')
        {
            std::cout << "Formato invalido, use dd/MM/yyyy.\n";
            continue;
        }

        if (iss >> extra) { std::cout << "Caracteres extra al final.\n"; continue; }
        if (day < 0 || day > 255
            || month < 0 || month > 255
            || year < 0 || year > 65535
        )
        {
            std::cout << "Valores fuera de rango.\n";
            continue;
        }

        try
        {
            return Date(static_cast<uint8_t>(day),
                        static_cast<uint8_t>(month),
                        static_cast<uint16_t>(year));
        }
        catch (const std::invalid_argument& e)
        { std::cout << e.what() << ". Intente de nuevo.\n"; }
    }
}

int Menu::promptPriority() const
{
    std::cout << "Prioridad: 1 = COLA (sin orden), 2 = ORDENADA (cronologica)\n";
    return promptInt("Elija prioridad", 1, 2);
}

// Opciones

void Menu::Initialize()
{
    list.freeAll();
    std::cout << "\n>> Lista borrada y memoria liberada.\n";
    pressEnter();
}

void Menu::Display()
{
    if (list.EsVacia())
    {
        std::cout << "\n>> La lista esta vacia.\n";
        pressEnter();
        return;
    }

    std::cout << "\n  1) Ascendente  (P -> F)\n" << "  2) Descendente (F -> P)\n";

    int opt = promptInt("Elija orden", 1, 2);
    
    if (opt == 1) list.Mostrar();
    else list.MostrarReversa();
    
    pressEnter();
}

void Menu::Search()
{
    // Si no hay nada, no tiene sentido pedir prioridad ni fecha.
    if (list.isEmpty())
    {
        std::cout << "\n>> La lista esta vacia. No hay nada que buscar.\n";
        pressEnter();
        return;
    }

    int p = promptPriority();
    Date d = promptDate("Fecha a buscar");
    
    Node* n = list.search(d, p);
    if (n) 
        std::cout << "\n>> ENCONTRADA: " << n->toString() << "\n";
    else   
        std::cout << "\n>> NO se encontro la fecha con prioridad " << p << ".\n";
    
    pressEnter();
}

void Menu::Insert()
{
    int p = promptPriority();
    Date d = promptDate("Fecha a insertar");
    list.insert(d, p);
    std::cout << "\n>> Insertada: " << d.toString()
              << " (prioridad " << p << ")\n";
    pressEnter();
}

void Menu::Remove()
{
    // Si la lista está vacía, ni siquiera preguntamos si quiere continuar,
    // simplemente le decimos que no se puede.
    if (list.isEmpty())
    {
        std::cout << "\n>> La lista esta vacia. No hay nada que eliminar.\n";
        pressEnter();
        return;
    }

    int p = promptPriority();

    if (p == 1)
    {
        // Para la prioridad 1, el que está al inicio es el que entró primero (FIFO)
        Node* h = list.getHead();
        if (h && h->Prioridad == 1)
        {
            std::cout << "\n>> Eliminando (FIFO P1): " << h->toString() << "\n";
            list.removeFront();
        }
        else
        {
            std::cout << "\n>> No hay nodos de prioridad 1 para eliminar.\n";
        }
    }
    else
    {
        // Para la prioridad 2, el usuario debe decirnos qué fecha quiere borrar
        Date d = promptDate("Fecha a eliminar");
        std::cout << (list.remove(d, 2)
            ? "\n>> Eliminada: " + d.toString()
            : "\n>> NO se encontro la fecha con prioridad 2.") << "\n";
    }
    pressEnter();
}

void Menu::Modify()
{
    // Misma lógica: si está vacía, ni preguntamos nada más.
    if (list.isEmpty())
    {
        std::cout << "\n>> La lista esta vacia. No hay nada que modificar.\n";
        pressEnter();
        return;
    }

    int p = promptPriority();
    Date oldDate = promptDate("Fecha a modificar");

    Node* n = list.search(oldDate, p);
    if (!n) 
    {
        std::cout << "\n>> NO se pudo localizar la fecha. Operacion cancelada.\n";
        pressEnter();
        return;
    }

    Date newDate = promptDate("Nueva fecha");

    if (p == 1)
    {
        // Reemplazo "in place", conserva la posicion
        n->Info = newDate; 
        std::cout << "\n>> Modificada (en la misma posicion): " << newDate.toString() << "\n";
    }
    else
    {
        // Eliminar + insertar para conservar el orden
        list.remove(oldDate, 2);
        list.insert(newDate, 2);
        std::cout << "\n>> Modificada y reordenada: " << newDate.toString() << "\n";
    }
    pressEnter();
}

void Menu::show()
{
    for (int option = -1; option != 0; )
    {
        clearScreen();
        std::cout << "Estructura de Datos, Unidad II: Listas Doblemente Enlazadas.\n";
        std::cout << "0) Salir\n"
                  << "1) Inicializar / Borrar Lista\n"
                  << "2) Mostrar Lista\n"
                  << "3) Buscar\n"
                  << "4) Insertar\n"
                  << "5) Eliminar\n"
                  << "6) Modificar\n"
                  << "7) Créditos.\n";

        option = promptInt("", 0, 7);
        switch (option)
        {
            case 1: Initialize(); break;
            case 2: Display();    break;
            case 3: Search();     break;
            case 4: Insert();     break;
            case 5: Remove();     break;
            case 6: Modify();     break;
            case 7: Credits();    break;
        }
    }
}
