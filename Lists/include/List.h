#ifndef LIST_H
#define LIST_H
#pragma once

#include "Node.h"
#include <iostream>
#include <string>

class List
{
private:
    Node* head; // P
    Node* tail; // F

    // Como la prioridad 1 siempre va al principio, esta función nos encuentra
    // exactamente dónde empiezan los nodos de prioridad 2 (los ordenados).
    Node* firstPriority2() const
    {
        Node* q = head;
        // Mientras q no sea nulo y su prioridad sea 1,
        // sigue avanzando hasta encontrar el primer nodo con prioridad 2
        while (q && q->Prioridad == 1) 
            q = q->Sig;
            
        return q;
    }

    // Si la fecha que buscamos está en la segunda mitad de la lista,
    // es más rápido empezar a buscar desde el final (tail) hacia atrás.
    bool startFromTail(const Date& d, Node* first) const
    { 
        return d.getYear() > (first->Info.getYear() + tail->Info.getYear()) / 2; 
    }

    // Búsqueda secuencial normalita, pero solo entre los nodos de prioridad 1
    // Al estar desordenados, tenemos que recorrer toda la lista.
    Node* searchPriority1(const Date& d) const
    {
        Node* q = head;
        // Nos movemos solo mientras estemos en el bloque de prioridad 1
        while (q && q->Prioridad == 1)
        {
            if (q->Info.equals(d)) return q;
            q = q->Sig;
        }
        return nullptr;
    }

    // Búsqueda optimizada para los de prioridad 2. Como están ordenados,
    // en cuanto nos pasamos de la fecha, dejamos de buscar.
    Node* searchPriority2(const Date& d) const
    {
        Node* first = firstPriority2();
        // Si no hay prioridad 2, o la fecha se sale de los límites, ni lo intentamos
        if (!first || d.isLess(first->Info) || tail->Info.isLess(d)) return nullptr;

        if (startFromTail(d, first))
        {
            // Va de atrás hacia adelante
            Node* q = tail;
            while (q && q->Prioridad == 2)
            {
                if (q->Info.equals(d)) return q;
                if (q->Info.isLess(d)) return nullptr; // Ya nos pasamos, no está
                q = q->Ant;
            }
        }
        else
        {
            // Vamos de adelante hacia atrás
            Node* q = first;
            while (q)
            {
                if (q->Info.equals(d)) return q;
                if (d.isLess(q->Info)) return nullptr; // Ya nos pasamos, no está
                q = q->Sig;
            }
        }
        return nullptr;
    }

    // Inserta respetando el orden cronológico (solo para prioridad 2)
    void insertPriority2(const Date& d)
    {
        Node* first = firstPriority2();
        
        // Aquí van los casos particulares: la lista está vacía, o va al puro inicio, o al puro final
        if (!first) { insertBack(d, 2); return; }
        if (d.isLess(first->Info)) { insertBefore(first, d, 2); return; }
        if (!d.isLess(tail->Info)) { insertBack(d, 2); return; }

        // Si no, buscamos el hueco en el que quepa
        if (startFromTail(d, first))
        {
            Node* q = tail;
            while (q && q->Prioridad == 2)
            {
                if (q->Info.isLess(d)) { insertAfter(q, d, 2); return; }
                q = q->Ant;
            }
        }
        else
        {
            Node* q = first;
            while (q)
            {
                if (!q->Info.isLess(d)) { insertBefore(q, d, 2); return; }
                q = q->Sig;
            }
        }
    }

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() { freeAll(); }
    
    void insertFront(const Date& v, int p)
    {
        Node* Q = new Node(v, p);
        Q->Sig = head;
        if (head) head->Ant = Q; else tail = Q; // Si la lista estaba vacía, Q también es el final
        head = Q;
    }

    void insertBack(const Date& v, int p)
    {
        Node* Q = new Node(v, p);
        Q->Ant = tail;
        if (tail) tail->Sig = Q; else head = Q; // Si estaba vacía, Q también es el inicio
        tail = Q;
    }

    void insertBefore(Node* R, const Date& v, int p)
    {
        if (!R) { insertFront(v, p); return; }
        Node* Q = new Node(v, p);
        Q->Ant = R->Ant;
        Q->Sig = R;

        // Conectamos el nodo de atrás con el nuevo Q
        if (R->Ant) R->Ant->Sig = Q; else head = Q;
        R->Ant = Q;
    }

    void insertAfter(Node* R, const Date& v, int p)
    {
        if (!R) { insertBack(v, p); return; }
        Node* Q = new Node(v, p);
        Q->Sig = R->Sig;
        Q->Ant = R;
        // Conectamos el nodo de adelante con el nuevo Q
        if (R->Sig) R->Sig->Ant = Q; else tail = Q;
        R->Sig = Q;
    }

    // Quita el primer nodo de la lista y lo devuelve
    Node* removeFront()
    {
        if (!head) return nullptr;
        Node* Q = head;
        if (head->Sig == nullptr)
        {
            head = nullptr; tail = nullptr; // Era el único nodo
        }
        else
        {
            head = head->Sig;
            head->Ant = nullptr; // El nuevo inicio ya no tiene a nadie atrás
        }
        Q->Sig = nullptr; // Lo desconectamos por completo
        return Q;
    }

    // Quita el último nodo de la lista y lo devuelve
    Node* removeBack()
    {
        if (!head) return nullptr;
        Node* Q = tail;
        if (head->Sig == nullptr)
        { head = nullptr; tail = nullptr; } // Era el único nodo
        else
        {
            tail = tail->Ant;
            tail->Sig = nullptr; // El nuevo final ya no tiene a nadie adelante
        }
        Q->Ant = nullptr;
        return Q;
    }

    // Lógica principal para insertar según prioridad
    void insert(const Date& d, int p)
    {
        if (p == 1)
        {
            // La prioridad 1 es una cola: siempre se mete al final de su bloque
            Node* first = firstPriority2();
            first ? insertBefore(first, d, 1) : insertBack(d, 1);
        }
        else insertPriority2(d); // La prioridad 2 se inserta ordenada por fecha
    }

    bool remove(const Date& d, int p)
    {
        if (p == 1)
        {
            // En P1 es FIFO: el que llegó primero sale primero (ignoramos la fecha)
            if (head && head->Prioridad == 1)
            {
                Node* temp = removeFront();
                delete temp;
                return true;
            }
            return false;
        }

        // En P2 buscamos la fecha exacta y desconectamos el nodo
        Node* n = searchPriority2(d);
        if (!n) return false;
        
        if (n->Ant) n->Ant->Sig = n->Sig; else head = n->Sig;
        if (n->Sig) n->Sig->Ant = n->Ant; else tail = n->Ant;
        delete n;
        return true;
    }

    Node* search(const Date& d, int p) const
    { return p == 1 ? searchPriority1(d) : searchPriority2(d); }

    void display() const
    {
        if (head == nullptr)
        {
            std::cout << "Lista vacia\n";
            return;
        }
        std::cout << "--- Contenido ---\n";
        // Vamos de inicio a final usando un auxiliar "T"
        Node* T = head;
        while (T != nullptr)
        {
            std::cout << T->toString() << "\n";
            T = T->Sig;
        }
        std::cout << "-----------------\n";
    }

    void displayReverse() const
    {
        if (tail == nullptr)
        {
            std::cout << "Lista vacia\n";
            return;
        }
        // Aquí usamos el puntero final "F" para ir hacia atrás
        Node* T = tail;
        while (T != nullptr)
        {
            std::cout << T->toString() << "\n";
            T = T->Ant;
        }
    }

    // Destruye todos los nodos para no dejar memoria colgada
    void freeAll()
    {
        Node* T = head;
        while (T != nullptr)
        {
            Node* Q = T->Sig; // Guardamos el siguiente antes de borrar
            delete T;
            T = Q;
        }
        head = tail = nullptr;
    }

    bool isEmpty() const { return head == nullptr; }
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
};

#endif // Final de LIST_H