#include <iostream>
#include <windows.h>
using namespace std;

int ScalarProduct(int x[], int y[], int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += x[i] * y[i];
    }

    return sum;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const int n = 5;

    int a[n] = { 1, 0, 3, 2, -1 };
    int b[n] = { 2, 3, 0, 1, 4 };
    int c[n] = { 1, 2, 0, 0, 1 };

    int ab = ScalarProduct(a, b, n);
    int ac = ScalarProduct(a, c, n);
    int bc = ScalarProduct(b, c, n);

    cout << "Скалярний добуток векторів a і b = " << ab << endl;
    cout << "Скалярний добуток векторів a і c = " << ac << endl;
    cout << "Скалярний добуток векторів b і c = " << bc << endl;
    cout << endl;

    if (ab == 0)
    {
        cout << "Вектори a і b ортогональні." << endl;
    }
    else
    {
        cout << "Вектори a і b не ортогональні." << endl;
    }

    if (ac == 0)
    {
        cout << "Вектори a і c ортогональні." << endl;
    }
    else
    {
        cout << "Вектори a і c не ортогональні." << endl;
    }

    if (bc == 0)
    {
        cout << "Вектори b і c ортогональні." << endl;
    }
    else
    {
        cout << "Вектори b і c не ортогональні." << endl;
    }

    return 0;
}
