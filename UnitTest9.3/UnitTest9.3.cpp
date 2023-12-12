#include "pch.h"
#include "CppUnitTest.h"
#include "..\ap_9.3\9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            int size = 3;
            Note* array = new Note[size];
            array[0] = { "Doe", "John", "123456789", {10, 3, 1990} };
            array[1] = { "Smith", "Jane", "987654321", {15, 5, 1985} };
            array[2] = { "Johnson", "Bob", "555666777", {20, 3, 1995} };

            sortArrayByBirthDates(array, size);


            Note expected_result[3] = {
                { "Smith", "Jane", "987654321", {15, 5, 1985} },
                { "Doe", "John", "123456789", {10, 3, 1990} },
                { "Johnson", "Bob", "555666777", {20, 3, 1995} }
            };


            for (int i = 0; i < size; ++i) {
                Assert::AreEqual(expected_result[i].lastName, array[i].lastName);
                Assert::AreEqual(expected_result[i].firstName, array[i].firstName);
                Assert::AreEqual(expected_result[i].phoneNumber, array[i].phoneNumber);
                Assert::AreEqual(expected_result[i].birthDate[0], array[i].birthDate[0]);
                Assert::AreEqual(expected_result[i].birthDate[1], array[i].birthDate[1]);
                Assert::AreEqual(expected_result[i].birthDate[2], array[i].birthDate[2]);
            }


            delete[] array;

		}
	};
}
