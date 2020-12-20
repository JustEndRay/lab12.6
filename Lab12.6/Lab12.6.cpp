#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <string>

using namespace std;


typedef string Info;
struct Elem
{
    Elem* link;
    Info info;
    Info info2;
};

void Read_File(Elem*& first, Elem*& last);
void Print(Elem* L);
void Sort_Action(Elem*& L);
void Enqueue(Elem*& first, Elem*& last, Info value);
Info Dequeue(Elem*& first, Elem*& last);
void Insert(Elem*& L, Info value, Info p);
int Count(Elem* L);
void Remove(Elem*& L);

int main()
{
    srand((unsigned)time(NULL));

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* first = NULL,
        * last = NULL;

    int action;

    do
    {
        cout << endl << endl;
        cout << "Виберіть дію: " << endl;
        cout << "1 - Побудувати чергу" << endl;
        cout << "2 - Надрукувати чергу" << endl;
        cout << "3 - Сортувати" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> action;
        switch (action)
        {
        case 1:
            Read_File(first, last);
            break;
        case 2:
            cout << "Черга: "; Print(first);
            break;
        case 3:
            Sort_Action(first);
            break;
        case 0:
            exit(1);
        }
    } while (action != 0);

    return 0;
}

void Read_File(Elem*& first, Elem*& last)
{
    ifstream f("F.txt", ios::in);

    if (!f.is_open())
    {
        cout << "Помилка!Файл не відкрито." << endl;
        exit(1);
    }
    string line;
    while (!f.eof())
    {
        getline(f, line);
        Enqueue(first, last, line);
    }
}
void Print(Elem* L)
{
    while (L != NULL)
    {
        cout << L->info<<" (Впадково присвоєне число="<< L->info2 << ") ";
        L = L->link;
    }
}
void Insert(Elem*& L, Info value, Info p)
{
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->info2 = p;
    if (L != NULL)
    {
        Elem* T = L;
        while (T->link != L)
            T = T->link;

        T->link = tmp;
    }
    else
        L = tmp;

    tmp->link = L;
}
void Sort_Action(Elem*& L)
{
    int size = Count(L);

    for (int i = 0; i < size - 1; i++)
    {
        Info value = L->info2;

        Insert(L, (L, i, size)); //добавлення у кінець списку зворотних елементів
    }

    for (int j = 0; j < size - 1; j++)
    {
        Remove(L);//видалення лишніх елементів

    }
}
int Count(Elem* L)
{
    if (L == NULL)
        return 0;

    Elem* first = L;
    int k = 1;
    while (L->link != first)
    {
        k++;
        L = L->link;
    }
    return k;
}
void Remove(Elem*& L)
{
    Elem* T = L;
    while (T->link != L)
        T = T->link;

    Info value = L->info;

    if (T != L)
    {
        Elem* tmp = L->link;
        delete L;

        L = tmp;
        T->link = L;
    }
}
void Enqueue(Elem*& first, Elem*& last, Info value)
{
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = NULL;
    char v[2];
    int digit = rand() % 7;
    v[0] = digit + '0';
    v[1] = 0;
    tmp->info2=v;
    if (last != NULL)
        last->link = tmp;
    last = tmp;
    if (first == NULL)
        first = tmp;
}
Info Dequeue(Elem*& first, Elem*& last)
{
    Elem* tmp = first->link;
    Info value = first->info;
    delete first;
    first = tmp;
    if (first == NULL)
        last = NULL;
    return value;
}