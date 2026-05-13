#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Функция проверки, является ли число полным квадратом
bool isPerfectSquare(long long x) {
    if (x < 0) return false;
    long long root = static_cast<long long>(sqrt(x));
    return (root * root == x);
}

// Функция проверки, является ли целое число числом Фибоначчи
bool isFibonacci(int n) {
    long long n2 = static_cast<long long>(n) * n;
    long long val1 = 5 * n2 + 4;
    long long val2 = 5 * n2 - 4;
    return isPerfectSquare(val1) || isPerfectSquare(val2);
}

// Фильтрация вектора: возвращает новый вектор, содержащий только числа Фибоначчи
vector<int> filterFibonacci(const vector<int>& src) {
    vector<int> result;
    for (int num : src) {
        if (isFibonacci(num)) {
            result.push_back(num);
        }
    }
    return result;
}

// Вывод вектора в консоль
void printVector(const string& title, const vector<int>& vec) {
    cout << title << " (размер " << vec.size() << "): ";
    if (vec.empty()) {
        cout << "(пусто)";
    }
    else {
        for (size_t i = 0; i < vec.size(); ++i) {
            cout << vec[i];
            if (i != vec.size() - 1) cout << ", ";
        }
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); // для корректного отображения кириллицы

    cout << "============================================================" << endl;
    cout << "Лабораторная работа №11 (вариант 22)" << endl;
    cout << "Задание: выделить из вектора числа Фибоначчи." << endl;
    cout << "============================================================" << endl;

    int n;
    cout << "Введите количество элементов вектора: ";
    cin >> n;

    if (n <= 0) {
        cout << "Некорректный размер вектора!" << endl;
        return 1;
    }

    vector<int> original;
    cout << "Введите " << n << " целых чисел через пробел: ";
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        original.push_back(val);
    }

    // Вывод исходного вектора
    printVector("Исходный вектор", original);

    // Формирование нового вектора из чисел Фибоначчи
    vector<int> fibVector = filterFibonacci(original);

    // Вывод результата
    if (fibVector.empty()) {
        cout << "\nВ исходном векторе нет чисел Фибоначчи. Новый вектор не создан." << endl;
    }
    else {
        cout << "\nИсходный вектор СОДЕРЖИТ числа Фибоначчи." << endl;
        printVector("Новый вектор (только числа Фибоначчи)", fibVector);
    }

    // Дополнительная проверка для наглядности (по желанию)
    cout << "\nПримечание: числа Фибоначчи в диапазоне int: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ..." << endl;

    return 0;
}
