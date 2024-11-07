#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab12\Source.cpp"
#include <fstream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestRead)
		{
			std::ofstream testFile("testGraph.txt");
			testFile << "4 5\n1 2 10\n1 3 20\n2 3 30\n3 4 10\n2 4 50\n";
			testFile.close();

			bool result = read("testGraph.txt");

			Assert::IsTrue(result);
			Assert::AreEqual(distances[0][1], 10u);
			Assert::AreEqual(distances[1][3], 50u);
			Assert::AreEqual(parent[1][3], 1);
		}

		TEST_METHOD(TestDjikstra)
		{
			std::ofstream testFile("testGraph.txt");
			testFile << "3 3\n1 2 5\n2 3 10\n1 3 15\n";
			testFile.close();

			read("testGraph.txt");

			djikstra(0);

			Assert::AreEqual(distances[0][0], 0u);
			Assert::AreEqual(distances[0][1], 5u);
			Assert::AreEqual(distances[0][2], 15u);
		}

	};
}
