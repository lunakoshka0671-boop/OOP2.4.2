
#pragma once

#include <iostream>
#include <string>

using namespace std;

class Hex
{
private:
    static const int MAX_SIZE = 100;

    unsigned char digits[MAX_SIZE];
    int capacity;   // Максимальна місткість об'єкта
    int count;  // Фактична кількість цифр

    void Normalize();
    void SubtractInPlace(const Hex& other);
    void MultiplyBy16AndAdd(unsigned char digit);

public:
    Hex();
    explicit Hex(const string& value);
    Hex(int size, const string& value);
    Hex(const Hex& other);
    

    int getSize() const;
    int getCount() const;
    unsigned char getDigit(int index) const;

    bool setSize(int value);
    bool setDigit(int index, unsigned char value);

    int size() const;

    Hex& operator=(const Hex& other);
    unsigned char operator[](int index) const;

    operator string() const;

    friend istream& operator>>(istream& in, Hex& value);
    friend ostream& operator<<(ostream& out, const Hex& value);

    friend Hex operator+(const Hex& a, const Hex& b);
    friend Hex operator-(const Hex& a, const Hex& b);
    friend Hex operator*(const Hex& a, const Hex& b);
    friend Hex operator/(const Hex& a, const Hex& b);
    friend Hex operator%(const Hex& a, const Hex& b);

    friend bool operator==(const Hex& a, const Hex& b);
    friend bool operator!=(const Hex& a, const Hex& b);
    friend bool operator<(const Hex& a, const Hex& b);
    friend bool operator>(const Hex& a, const Hex& b);
    friend bool operator<=(const Hex& a, const Hex& b);
    friend bool operator>=(const Hex& a, const Hex& b);
};


