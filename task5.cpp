#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>


using namespace std;

struct Abiturient {
    string prizvyshche;
    string imya;
    string telefon;
    float seredniyBal;
    string pilga;
};


void addAbiturient() {
    ofstream file("abiturients.txt", ios::app);

    Abiturient a;

    cout << "\nВведіть прізвище: ";
    cin >> a.prizvyshche;

    cout << "Введіть ім'я: ";
    cin >> a.imya;

    cout << "Введіть телефон: ";
    cin >> a.telefon;

    cout << "Введіть середній бал ЗНО: ";
    cin >> a.seredniyBal;

    cout << "Чи є пільга? (так/ні): ";
    cin >> a.pilga;

    file << a.prizvyshche << " "
        << a.imya << " "
        << a.telefon << " "
        << a.seredniyBal << " "
        << a.pilga << endl;

    file.close();

    cout << "\nАбітурієнта додано!\n";
}


void showAll() {
    ifstream file("abiturients.txt");

    Abiturient a;

    cout << "\n--- Список усіх абітурієнтів ---\n";

    while (file >> a.prizvyshche >> a.imya >> a.telefon >> a.seredniyBal >> a.pilga) {
        cout << "Прізвище: " << a.prizvyshche << endl;
        cout << "Ім'я: " << a.imya << endl;
        cout << "Телефон: " << a.telefon << endl;
        cout << "Середній бал ЗНО: " << a.seredniyBal << endl;
        cout << "Пільга: " << a.pilga << endl;
        cout << "--------------------------\n";
    }

    file.close();
}

void showPilga() {
    ifstream file("abiturients.txt");

    Abiturient a;
    bool found = false;

    cout << "\n--- Абітурієнти з пільгою ---\n";

    while (file >> a.prizvyshche >> a.imya >> a.telefon >> a.seredniyBal >> a.pilga) {
        if (a.pilga == "так") {
            cout << "Прізвище: " << a.prizvyshche << endl;
            cout << "Ім'я: " << a.imya << endl;
            cout << "Телефон: " << a.telefon << endl;
            cout << "Середній бал ЗНО: " << a.seredniyBal << endl;
            cout << "Пільга: " << a.pilga << endl;
            cout << "--------------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Абітурієнтів з пільгою не знайдено.\n";
    }

    file.close();
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Додати абітурієнта\n";
        cout << "2. Показати всіх абітурієнтів\n";
        cout << "3. Показати абітурієнтів з пільгою\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addAbiturient();
            break;
        case 2:
            showAll();
            break;
        case 3:
            showPilga();
            break;
        case 0:
            cout << "Програма завершена.\n";
            break;
        default:
            cout << "Невірний вибір!\n";
        }

    } while (choice != 0);

    return 0;
}
