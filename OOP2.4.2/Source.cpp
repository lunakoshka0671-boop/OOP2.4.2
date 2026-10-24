
#include <iostream>
#include <string>
#include <stdexcept>
#include "Hex.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    try
    {
        // 1. Створення об'єктів різними конструкторами
        Hex h1;
        Hex h2("2A5");
        Hex h3(10, "1F");
        Hex h4(h2);

        cout << "h1 (default): " << h1 << endl;
        cout << "h2 (string): " << h2 << endl;
        cout << "h3 (capacity 10): " << h3 << endl;
        cout << "h4 (copy): " << h4 << endl;

        // 2. Методи доступу
        cout << "\nCapacity h3: " << h3.size() << endl;
        cout << "Digit count h3: " << h3.getCount() << endl;
        cout << "Digit at index 0 of h2: "
            << static_cast<int>(h2[0]) << endl;

        // 3. Зміна цифри через метод із перевіркою
        Hex h5("123");
        h5.setDigit(0, 15);
        cout << "\nh5 after setDigit: " << h5 << endl;

        // 4. Присвоєння
        Hex h6;
        h6 = h3;
        cout << "h6 after assignment: " << h6 << endl;

        // 5. Введення з клавіатури
        Hex inputNumber;
        cout << "\nEnter a hexadecimal number: ";

        if (cin >> inputNumber)
            cout << "You entered: " << inputNumber << endl;
        else
        {
            cout << "Invalid hexadecimal number!" << endl;
            return 1;
        }

        // 6. Арифметичні операції
        Hex a("2A");
        Hex b("5");

        cout << "\na = " << a << endl;
        cout << "b = " << b << endl;
        cout << "a + b = " << a + b << endl;
        cout << "a - b = " << a - b << endl;
        cout << "a * b = " << a * b << endl;
        cout << "a / b = " << a / b << endl;
        cout << "a % b = " << a % b << endl;

        // 7. Порівняння
        cout << boolalpha;
        cout << "\na == b: " << (a == b) << endl;
        cout << "a != b: " << (a != b) << endl;
        cout << "a < b: " << (a < b) << endl;
        cout << "a > b: " << (a > b) << endl;
        cout << "a <= b: " << (a <= b) << endl;
        cout << "a >= b: " << (a >= b) << endl;

        // 8. Перетворення у string
        string text = static_cast<string>(a);
        cout << "\nString representation: " << text << endl;

        // 9. Масив об'єктів
        Hex numbers[3] = {
            Hex("A"),
            Hex("10"),
            Hex("FF")
        };

        cout << "\nArray of Hex objects:\n";

        for (int i = 0; i < 3; i++)
            cout << "numbers[" << i << "] = "
            << numbers[i] << endl;

        // 10. Розмір класу
        cout << "\nSize of Hex without packing: "
            << sizeof(Hex) << " bytes" << endl;

        cout << "Size of Hex with pack(1) layout: "
            << sizeof(unsigned char) * 100
            + sizeof(int) * 2
            << " bytes" << endl;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
