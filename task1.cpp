#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <future>
#include <fstream>
#include <clocale>
#include <windows.h>

using namespace std;

void generateArray(vector<int>& arr, int n)
{
    arr.clear();

    for (int i = 0; i < n; i++)
    {
        arr.push_back(rand() % 100000);
    }
}

void printArray(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

vector<int> copyArray(vector<int> arr)
{
    vector<int> newArr;

    for (int i = 0; i < arr.size(); i++)
    {
        newArr.push_back(arr[i]);
    }

    return newArr;
}

void bubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(vector<int>& arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void shellSort(vector<int>& arr)
{
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j = j - gap;
            }

            arr[j] = temp;
        }
    }
}

int binarySearch(vector<int> arr, int key)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

double getBubbleTime(vector<int> arr)
{
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(end - start).count();
}

double getSelectionTime(vector<int> arr)
{
    auto start = chrono::high_resolution_clock::now();
    selectionSort(arr);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(end - start).count();
}

double getShellTime(vector<int> arr)
{
    auto start = chrono::high_resolution_clock::now();
    shellSort(arr);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(end - start).count();
}

void bubbleAsync(vector<int> arr)
{
    bubbleSort(arr);
}

void selectionAsync(vector<int> arr)
{
    selectionSort(arr);
}

void shellAsync(vector<int> arr)
{
    shellSort(arr);
}

double getSyncTime(vector<int> arr)
{
    vector<int> a1 = copyArray(arr);
    vector<int> a2 = copyArray(arr);
    vector<int> a3 = copyArray(arr);

    auto start = chrono::high_resolution_clock::now();

    bubbleSort(a1);
    selectionSort(a2);
    shellSort(a3);

    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(end - start).count();
}

double getAsyncTime(vector<int> arr)
{
    vector<int> a1 = copyArray(arr);
    vector<int> a2 = copyArray(arr);
    vector<int> a3 = copyArray(arr);

    auto start = chrono::high_resolution_clock::now();

    future<void> f1 = async(launch::async, bubbleAsync, a1);
    future<void> f2 = async(launch::async, selectionAsync, a2);
    future<void> f3 = async(launch::async, shellAsync, a3);

    f1.get();
    f2.get();
    f3.get();

    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(end - start).count();
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF-8");

    srand(time(0));

    int sizes[6] = { 8, 80, 1200, 4000, 25000, 100000 };
    int runs = 5;

    vector<int> arr;
    generateArray(arr, 20);

    cout << "Початковий масив:" << endl;
    printArray(arr);

    vector<int> sortedArr = copyArray(arr);
    shellSort(sortedArr);

    cout << endl;
    cout << "Відсортований масив (сортування Шелла):" << endl;
    printArray(sortedArr);

    int x;
    cout << endl;
    cout << "Введіть елемент для бінарного пошуку: ";
    cin >> x;

    int pos = binarySearch(sortedArr, x);

    if (pos != -1)
    {
        cout << "Елемент знайдено. Індекс = " << pos << endl;
    }
    else
    {
        cout << "Елемент не знайдено." << endl;
    }

    ofstream file("results.csv");
    file << "n,bubble,selection,shell,sync,async\n";

    cout << endl;
    cout << "Результати:" << endl;

    for (int i = 0; i < 6; i++)
    {
        int n = sizes[i];

        double bubbleSum = 0;
        double selectionSum = 0;
        double shellSum = 0;
        double syncSum = 0;
        double asyncSum = 0;

        for (int j = 0; j < runs; j++)
        {
            vector<int> testArr;
            generateArray(testArr, n);

            bubbleSum += getBubbleTime(testArr);
            selectionSum += getSelectionTime(testArr);
            shellSum += getShellTime(testArr);
            syncSum += getSyncTime(testArr);
            asyncSum += getAsyncTime(testArr);
        }

        double bubbleAvg = bubbleSum / runs;
        double selectionAvg = selectionSum / runs;
        double shellAvg = shellSum / runs;
        double syncAvg = syncSum / runs;
        double asyncAvg = asyncSum / runs;

        cout << "n = " << n << endl;
        cout << "Сортування бульбашкою: " << bubbleAvg << " мс" << endl;
        cout << "Сортування вибором: " << selectionAvg << " мс" << endl;
        cout << "Сортування Шелла: " << shellAvg << " мс" << endl;
        cout << "Синхронно: " << syncAvg << " мс" << endl;
        cout << "Асинхронно: " << asyncAvg << " мс" << endl;
        cout << endl;

        file << n << ","
            << bubbleAvg << ","
            << selectionAvg << ","
            << shellAvg << ","
            << syncAvg << ","
            << asyncAvg << "\n";
    }

    file.close();

    cout << "Дані записано у results.csv" << endl;

    return 0;
}
