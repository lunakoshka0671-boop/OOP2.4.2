
#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP2.4.2/Hex.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HexUnitTests
{
    TEST_CLASS(HexTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            Hex h;
            Assert::IsTrue(static_cast<string>(h) == "0");
            Assert::AreEqual(100, h.size());
            Assert::AreEqual(1, h.getCount());
        }

        TEST_METHOD(TestStringConstructor)
        {
            Hex h("2A5");
            Assert::IsTrue(static_cast<string>(h) == "2A5");
            Assert::AreEqual(3, h.getCount());
        }

        TEST_METHOD(TestCapacityConstructor)
        {
            Hex h(10, "1F");
            Assert::AreEqual(10, h.size());
            Assert::IsTrue(static_cast<string>(h) == "1F");
        }

        TEST_METHOD(TestCopyConstructor)
        {
            Hex h1("ABC");
            Hex h2(h1);

            Assert::IsTrue(h1 == h2);
        }

        TEST_METHOD(TestAssignment)
        {
            Hex h1("123");
            Hex h2("F");

            h2 = h1;

            Assert::IsTrue(h1 == h2);
        }

        TEST_METHOD(TestIndexOperator)
        {
            Hex h("2A5");

            Assert::AreEqual(5, static_cast<int>(h[0]));
            Assert::AreEqual(10, static_cast<int>(h[1]));
            Assert::AreEqual(2, static_cast<int>(h[2]));
        }

        TEST_METHOD(TestSetDigit)
        {
            Hex h("123");

            Assert::IsTrue(h.setDigit(0, 15));
            Assert::IsTrue(static_cast<string>(h) == "12F");

            Assert::IsFalse(h.setDigit(0, 16));
            Assert::IsFalse(h.setDigit(-1, 1));
        }

        TEST_METHOD(TestAddition)
        {
            Hex a("2A");
            Hex b("5");

            Assert::IsTrue(static_cast<string>(a + b) == "2F");
        }

        TEST_METHOD(TestAdditionWithCarry)
        {
            Hex a("F");
            Hex b("1");

            Assert::IsTrue(static_cast<string>(a + b) == "10");
        }

        TEST_METHOD(TestSubtraction)
        {
            Hex a("2A");
            Hex b("5");

            Assert::IsTrue(static_cast<string>(a - b) == "25");
        }

        TEST_METHOD(TestMultiplication)
        {
            Hex a("2A");
            Hex b("5");

            Assert::IsTrue(static_cast<string>(a * b) == "D2");
        }

        TEST_METHOD(TestDivision)
        {
            Hex a("2A");
            Hex b("5");

            Assert::IsTrue(static_cast<string>(a / b) == "8");
        }

        TEST_METHOD(TestRemainder)
        {
            Hex a("2A");
            Hex b("5");

            Assert::IsTrue(static_cast<string>(a % b) == "2");
        }

        TEST_METHOD(TestComparison)
        {
            Hex a("A");
            Hex b("B");
            Hex c("A");

            Assert::IsTrue(a < b);
            Assert::IsTrue(b > a);
            Assert::IsTrue(a == c);
            Assert::IsTrue(a != b);
            Assert::IsTrue(a <= c);
            Assert::IsTrue(b >= a);
        }

        TEST_METHOD(TestSubtractionUnderflow)
        {
            Hex a("5");
            Hex b("A");

            bool exceptionThrown = false;

            try
            {
                Hex result = a - b;
            }
            catch (const underflow_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(TestDivisionByZero)
        {
            Hex a("10");
            Hex b("0");

            bool exceptionThrown = false;

            try
            {
                Hex result = a / b;
            }
            catch (const domain_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }
    };
}
