
#include "Hex.h"
#include <stdexcept>
#include <cctype>
#include <algorithm>

Hex::Hex()
{
    capacity = MAX_SIZE;
    count = 1;

    for (int i = 0; i < MAX_SIZE; i++)
        digits[i] = 0;
}

Hex::Hex(const string& value)
{
    capacity = static_cast<int>(value.length());

    if (capacity < 1 || capacity > MAX_SIZE)
        throw invalid_argument("Incorrect hexadecimal number length");

    for (int i = 0; i < MAX_SIZE; i++)
        digits[i] = 0;

    count = capacity;

    for (int i = 0; i < count; i++)
    {
        char c = value[value.length() - 1 - i];

        if (c >= '0' && c <= '9')
            digits[i] = c - '0';
        else if (c >= 'A' && c <= 'F')
            digits[i] = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            digits[i] = c - 'a' + 10;
        else
            throw invalid_argument("Invalid hexadecimal digit");
    }

    Normalize();
}

Hex::Hex(int capacity, const string& value)
{
    if (capacity < 1 || capacity > MAX_SIZE ||
        value.empty() || value.length() > static_cast<size_t>(capacity))
        throw invalid_argument("Incorrect size or value");

    this->capacity = capacity;

    for (int i = 0; i < MAX_SIZE; i++)
        digits[i] = 0;

    count = static_cast<int>(value.length());

    for (int i = 0; i < count; i++)
    {
        char c = value[value.length() - 1 - i];

        if (c >= '0' && c <= '9')
            digits[i] = c - '0';
        else if (c >= 'A' && c <= 'F')
            digits[i] = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            digits[i] = c - 'a' + 10;
        else
            throw invalid_argument("Invalid hexadecimal digit");
    }

    Normalize();
}

Hex::Hex(const Hex& other)
{
    capacity = other.capacity;
    count = other.count;

    for (int i = 0; i < MAX_SIZE; i++)
        digits[i] = other.digits[i];
}

int Hex::size() const
{
    return capacity;
}

int Hex::getCount() const
{
    return count;
}

unsigned char Hex::getDigit(int index) const
{
    if (index < 0 || index >= capacity)
        throw out_of_range("Incorrect digit index");

    return digits[index];
}

bool Hex::setSize(int value)
{
    if (value < 1 || value > MAX_SIZE || value < count)
        return false;

    capacity = value;
    return true;
}

bool Hex::setDigit(int index, unsigned char value)
{
    if (index < 0 || index >= capacity || value > 15)
        return false;

    digits[index] = value;

    if (index >= count && value != 0)
        count = index + 1;

    Normalize();
    return true;
}

void Hex::Normalize()
{
    while (count > 1 && digits[count - 1] == 0)
        count--;

    if (count == 0)
        count = 1;
}

Hex& Hex::operator=(const Hex& other)
{
    if (this != &other)
    {
        capacity = other.capacity;
        count = other.count;

        for (int i = 0; i < MAX_SIZE; i++)
            digits[i] = other.digits[i];
    }

    return *this;
}

unsigned char Hex::operator[](int index) const
{
    if (index < 0 || index >= count)
        throw out_of_range("Incorrect digit index");

    return digits[index];
}

Hex::operator string() const
{
    string result;

    for (int i = count - 1; i >= 0; i--)
    {
        if (digits[i] < 10)
            result += char('0' + digits[i]);
        else
            result += char('A' + digits[i] - 10);
    }

    return result;
}

istream& operator>>(istream& in, Hex& value)
{
    string text;
    in >> text;

    if (!in)
        return in;

    try
    {
        Hex temp(value.capacity, text);
        value = temp;
    }
    catch (const exception&)
    {
        in.setstate(ios::failbit);
    }

    return in;
}

ostream& operator<<(ostream& out, const Hex& value)
{
    out << static_cast<string>(value);
    return out;
}

bool operator==(const Hex& a, const Hex& b)
{
    if (a.count != b.count)
        return false;

    for (int i = 0; i < a.count; i++)
        if (a.digits[i] != b.digits[i])
            return false;

    return true;
}

bool operator!=(const Hex& a, const Hex& b)
{
    return !(a == b);
}

bool operator<(const Hex& a, const Hex& b)
{
    if (a.count != b.count)
        return a.count < b.count;

    for (int i = a.count - 1; i >= 0; i--)
    {
        if (a.digits[i] != b.digits[i])
            return a.digits[i] < b.digits[i];
    }

    return false;
}

bool operator>(const Hex& a, const Hex& b)
{
    return b < a;
}

bool operator<=(const Hex& a, const Hex& b)
{
    return !(a > b);
}

bool operator>=(const Hex& a, const Hex& b)
{
    return !(a < b);
}

void Hex::SubtractInPlace(const Hex& other)
{
    int borrow = 0;

    for (int i = 0; i < count; i++)
    {
        int value = digits[i] - borrow;

        if (i < other.count)
            value -= other.digits[i];

        if (value < 0)
        {
            value += 16;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        digits[i] = static_cast<unsigned char>(value);
    }

    Normalize();
}

Hex operator+(const Hex& a, const Hex& b)
{
    Hex result;
    int carry = 0;

    result.count = max(a.count, b.count);

    for (int i = 0; i < result.count; i++)
    {
        int value = carry;

        if (i < a.count)
            value += a.digits[i];

        if (i < b.count)
            value += b.digits[i];

        result.digits[i] = static_cast<unsigned char>(value % 16);
        carry = value / 16;
    }

    if (carry != 0)
    {
        if (result.count == Hex::MAX_SIZE)
            throw overflow_error("Hexadecimal result is too large");

        result.digits[result.count++] = static_cast<unsigned char>(carry);
    }

    result.Normalize();
    return result;
}

Hex operator-(const Hex& a, const Hex& b)
{
    if (a < b)
        throw underflow_error("Unsigned hexadecimal subtraction is negative");

    Hex result(a);
    result.SubtractInPlace(b);
    return result;
}

Hex operator*(const Hex& a, const Hex& b)
{
    Hex result;

    for (int i = 0; i < a.count; i++)
    {
        int carry = 0;

        for (int j = 0; j < b.count; j++)
        {
            int position = i + j;

            if (position >= Hex::MAX_SIZE)
                throw overflow_error("Hexadecimal result is too large");

            int value = result.digits[position]
                + a.digits[i] * b.digits[j] + carry;

            result.digits[position] = static_cast<unsigned char>(value % 16);
            carry = value / 16;
        }

        int position = i + b.count;

        while (carry > 0)
        {
            if (position >= Hex::MAX_SIZE)
                throw overflow_error("Hexadecimal result is too large");

            int value = result.digits[position] + carry;
            result.digits[position] = static_cast<unsigned char>(value % 16);
            carry = value / 16;
            position++;
        }
    }

    result.count = Hex::MAX_SIZE;
    result.Normalize();
    return result;
}

void Hex::MultiplyBy16AndAdd(unsigned char digit)
{
    if (count >= MAX_SIZE)
        throw overflow_error("Hexadecimal result is too large");

    for (int i = count; i > 0; i--)
        digits[i] = digits[i - 1];

    digits[0] = digit;
    count++;

    Normalize();
}

Hex operator/(const Hex& a, const Hex& b)
{
    Hex zero("0");

    if (b == zero)
        throw domain_error("Division by zero");

    Hex quotient;
    Hex remainder;
    quotient.count = a.count;

    for (int i = 0; i < Hex::MAX_SIZE; i++)
        quotient.digits[i] = 0;

    for (int i = a.count - 1; i >= 0; i--)
    {
        remainder.MultiplyBy16AndAdd(a.digits[i]);

        unsigned char qdigit = 0;

        while (!(remainder < b))
        {
            remainder.SubtractInPlace(b);
            qdigit++;
        }

        quotient.digits[i] = qdigit;
    }

    quotient.Normalize();
    return quotient;
}

Hex operator%(const Hex& a, const Hex& b)
{
    Hex zero("0");

    if (b == zero)
        throw domain_error("Division by zero");

    Hex quotient = a / b;
    return a - quotient * b;
}

