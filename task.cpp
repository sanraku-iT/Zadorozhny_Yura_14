#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <locale.h>

using namespace std;

int** createMatrix(int n)
{
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }
    return a;
}

void deleteMatrix(int** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] a[i];
    }
    delete[] a;
}

void fillMatrix(int** a, int n, int variant)
{
    int minValue = -10 - variant;
    int maxValue = 10 + variant;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = minValue + rand() % (maxValue - minValue + 1);
        }
    }
}

void printMatrix(int** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
}

bool isSector5(int i, int j)
{
    return i <= j;
}

bool isSector2(int i, int j, int n)
{
    return (j <= i && j <= n - 1 - i);
}

void findMinPositiveInSector5(int** a, int n)
{
    bool found = false;
    int minPositive = 0;
    int row = -1;
    int col = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isSector5(i, j) && a[i][j] > 0)
            {
                if (!found || a[i][j] < minPositive)
                {
                    minPositive = a[i][j];
                    row = i;
                    col = j;
                    found = true;
                }
            }
        }
    }

    if (found)
    {
        cout << "\nУ секторі *5 найменший додатний елемент: " << minPositive << endl;
        cout << "Його позиція: рядок " << row + 1 << ", стовпець " << col + 1 << endl;
    }
    else
    {
        cout << "\nУ секторі *5 додатних елементів немає." << endl;
    }
}

double averageOfNegativeElements(int** a, int n, bool& hasNegative)
{
    int sum = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] < 0)
            {
                sum += a[i][j];
                count++;
            }
        }
    }

    if (count == 0)
    {
        hasNegative = false;
        return 0;
    }

    hasNegative = true;
    return (double)sum / count;
}

int countSector2Elements(int** a, int n)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isSector2(i, j, n))
            {
                count++;
            }
        }
    }

    return count;
}

void replaceSector2(int** a, int n, int value)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isSector2(i, j, n))
            {
                a[i][j] = value;
            }
        }
    }
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    srand((unsigned)time(0));

    const int variant = 14;
    int n;
    cout << "Введіть розмір квадратної матриці n: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Помилка! Розмір матриці має бути більше 0." << endl;
        return 0;
    }

    int** matrix = createMatrix(n);

    fillMatrix(matrix, n, variant);

    cout << "\nПочаткова матриця:" << endl;
    printMatrix(matrix, n);

    findMinPositiveInSector5(matrix, n);

    int sector2Count = countSector2Elements(matrix, n);
    cout << "\nКількість елементів у секторі *2: " << sector2Count << endl;

    bool hasNegative;
    double avgNegative = averageOfNegativeElements(matrix, n, hasNegative);

    if (!hasNegative)
    {
        cout << "У матриці немає від'ємних елементів, тому заміна не виконується." << endl;
    }
    else
    {
        cout << "Середнє арифметичне від'ємних елементів матриці: " << avgNegative << endl;

        int newValue = (int)avgNegative;
        replaceSector2(matrix, n, newValue);

        cout << "\nМатриця після заміни елементів сектору *2:" << endl;
        printMatrix(matrix, n);
    }

    deleteMatrix(matrix, n);

    return 0;
}
