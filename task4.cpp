#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <windows.h>

using namespace std;

int countWords(const string& sentence) {
    stringstream ss(sentence);
    string word;
    int count = 0;

    while (ss >> word) {
        count++;
    }

    return count;
}

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile) {
        cout << "Помилка відкриття файлу input.txt" << endl;
        return 1;
    }

    vector<string> sentences;
    string line;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            sentences.push_back(line);
        }
    }

    inputFile.close();

    sort(sentences.begin(), sentences.end(),
        [](const string& a, const string& b) {
            return countWords(a) > countWords(b);
        });

    for (const string& sentence : sentences) {
        outputFile << sentence << endl;
    }

    outputFile.close();

    cout << "Готово! Результат записано в output.txt" << endl;

    return 0;
}
