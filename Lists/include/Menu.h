#ifndef MENU_H
#define MENU_H
#pragma once

#include "List.h"
#include <string>

class Menu
{
private:
    List list;

    // Entrada y salida
    void clearScreen() const;
    void pressEnter() const;
    int  promptInt(const std::string& prompt, int min, int max) const;
    Date promptDate(const std::string& prompt) const;
    int  promptPriority() const;
    bool promptYesNo(const std::string& question) const;

    // Opciones del menu
    void Initialize();
    void Display();
    void Search();
    void Insert();
    void Remove();
    void Modify();
    void Credits();

public:
    Menu();
    void show();
};

#endif // Final de MENU_H
