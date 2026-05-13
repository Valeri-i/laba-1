#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Функция для вывода списка на экран
void printList(const list<int>& lst, const string& title) {
    cout << title << ": ";
    if (lst.empty()) {
        cout << "(пустой список)";
    } else {
        for (int val : lst) {
            cout << val << " ";
        }
    }
    cout << endl;
}

// Функция проверки, является ли элемент локальным минимумом
// Для элемента по итератору it в списке lst (необходимы соседи)
bool isLocalMinimum(list<int>::const_iterator it, const list<int>& lst) {
    // Если список пуст или элемент один, то он не считается локальным минимумом
    if (lst.size() <= 1) return false;

    // Определяем соседей
    auto prevIt = it;
    auto nextIt = it;
    bool hasPrev = (it != lst.begin());      // есть предыдущий элемент?
    bool hasNext = (nextIt != --lst.end());  // есть следующий элемент?
    if (hasNext) ++nextIt;                   // перемещаем на следующий

    // Если есть оба соседа
    if (hasPrev && hasNext) {
        auto prevVal = *(--prevIt);   // предыдущий элемент
        auto curVal = *it;
        auto nextVal = *nextIt;
        return (curVal < prevVal && curVal < nextVal);
    }
    // Только следующий сосед (первый элемент)
    else if (!hasPrev && hasNext) {
        return (*it < *nextIt);
    }
    // Только предыдущий сосед (последний элемент)
    else if (hasPrev && !hasNext) {
        auto prevVal = *(--prevIt);
        return (*it < prevVal);
    }
    // Нет соседей (один элемент) – не минимум
    return false;
}

// Функция удаления всех локальных минимумов из списка
void removeLocalMinimums(list<int>& lst) {
    if (lst.size() <= 1) return;  // Один элемент или пустой список – удалять нечего

    auto it = lst.begin();
    while (it != lst.end()) {
        // Проверяем, является ли текущий элемент локальным минимумом
        if (isLocalMinimum(it, lst)) {
            // erase возвращает итератор на следующий элемент
            it = lst.erase(it);
        } else {
            ++it;
        }
    }
}

// Заполнение списка случайными целыми числами
void fillRandom(list<int>& lst, int size, int minVal, int maxVal) {
    lst.clear();
    for (int i = 0; i < size; ++i) {
        int val = minVal + rand() % (maxVal - minVal + 1);
        lst.push_back(val);
    }
}

// Ручной ввод элементов списка
void fillManual(list<int>& lst, int size) {
    lst.clear();
    cout << "Введите " << size << " целых чисел через пробел: ";
    for (int i = 0; i < size; ++i) {
        int val;
        cin >> val;
        lst.push_back(val);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");  // для русских символов в консоли (Windows)
    srand(static_cast<unsigned>(time(nullptr))); // инициализация ГСЧ

    cout << "==================================================" << endl;
    cout << "Лабораторная работа №10 (вариант 22)" << endl;
    cout << "Задание: найти и удалить все локальные минимумы в списке." << endl;
    cout << "==================================================" << endl;

    int choice;
    cout << "Выберите способ заполнения списка:\n";
    cout << "1 - Случайными числами\n";
    cout << "2 - Ввод с клавиатуры\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    int size;
    cout << "Введите количество элементов списка: ";
    cin >> size;
    if (size <= 0) {
        cout << "Некорректный размер списка!" << endl;
        return 1;
    }

    list<int> myList;

    if (choice == 1) {
        int minVal, maxVal;
        cout << "Введите минимальное и максимальное значение (через пробел): ";
        cin >> minVal >> maxVal;
        if (minVal >= maxVal) {
            cout << "Некорректный диапазон!" << endl;
            return 1;
        }
        fillRandom(myList, size, minVal, maxVal);
    } else {
        fillManual(myList, size);
    }

    // Вывод исходного списка
    printList(myList, "Исходный список");

    // Удаление локальных минимумов
    removeLocalMinimums(myList);

    // Вывод изменённого списка
    printList(myList, "Список после удаления локальных минимумов");

    // Дополнительное пояснение
    cout << "\nПримечание: локальным минимумом считается элемент, который меньше обоих своих соседей.\n";
    cout << "Для первого элемента — меньше следующего, для последнего — меньше предыдущего.\n";
    cout << "Элементы, равные соседям, не считаются локальными минимумами.\n";

    return 0;
}
