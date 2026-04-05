#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>

using namespace std;

struct IPAddress {
    unsigned char octet[4];
};

IPAddress parseIP(const string& ipStr) {
    IPAddress ip;
    stringstream ss(ipStr);
    string octetStr;
    int i = 0;
    while (getline(ss, octetStr, '.') && i < 4) {
        ip.octet[i++] = static_cast<unsigned char>(stoi(octetStr));
    }
    return ip;
}


void printDecimal(const IPAddress& ip) {
    for (int i = 0; i < 4; ++i) {
        cout << static_cast<int>(ip.octet[i]);
        if (i < 3) cout << ".";
    }
}


void printBinary(const IPAddress& ip) {
    for (int i = 0; i < 4; ++i) {
        cout << bitset<8>(ip.octet[i]);
        if (i < 3) cout << ".";
    }
}

// Поразрядное логическое И двух IP-адресов (покомпонентно)
IPAddress bitwiseAnd(const IPAddress& a, const IPAddress& b) {
    IPAddress result;
    for (int i = 0; i < 4; ++i) {
        result.octet[i] = a.octet[i] & b.octet[i];
    }
    return result;
}

// Сравнение двух IP-адресов на равенство
bool areEqual(const IPAddress& a, const IPAddress& b) {
    for (int i = 0; i < 4; ++i) {
        if (a.octet[i] != b.octet[i]) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru-RU");

    string strA = "192.168.22.1";
    string strB = "172.16.31.8";
    string strC = "255.255.255.0";

    IPAddress A = parseIP(strA);
    IPAddress B = parseIP(strB);
    IPAddress C = parseIP(strC);


    //  Преобразование числа A в двоичную систему счисления
    cout << "\n1. Число A = ";
    printDecimal(A);
    cout << "\n   Двоичное представление A: ";
    printBinary(A);
    cout << endl;

    //  Преобразование числа B в двоичную систему счисления
    cout << "\n2. Число B = ";
    printDecimal(B);
    cout << "\n   Двоичное представление B: ";
    printBinary(B);
    cout << endl;

    //  Преобразование числа C (маски) в двоичную систему счисления
    cout << "\n3. Число C (маска) = ";
    printDecimal(C);
    cout << "\n   Двоичное представление C: ";
    printBinary(C);
    cout << endl;

    //  Поразрядное умножение (AND) числа A на C и числа B на C
    IPAddress A_and_C = bitwiseAnd(A, C);
    IPAddress B_and_C = bitwiseAnd(B, C);

    cout << "\n4. Поразрядное умножение (логическое И):" << endl;
    cout << "   A & C = ";
    printDecimal(A_and_C);
    cout << "   (двоичное: ";
    printBinary(A_and_C);
    cout << ")" << endl;

    cout << "   B & C = ";
    printDecimal(B_and_C);
    cout << "   (двоичное: ";
    printBinary(B_and_C);
    cout << ")" << endl;

    //  Сравнение результатов поразрядного умножения
    bool equal = areEqual(A_and_C, B_and_C);
    cout << "\n5. Сравнение результатов A&C и B&C:" << endl;
    cout << "   Результаты равны? --> " << boolalpha << equal << endl;
    cout << "   Формат False & True: " << boolalpha << equal << endl;

    return 0;
}
