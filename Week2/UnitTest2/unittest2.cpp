#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Week2/Ex1.h"
#include "../Week2/Ex2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(Ex1)
	{
	public:
		
		TEST_METHOD(TestBracketFilter)
		{
			vector<int> open, close;
			string input = "(())";
			bracketFilter(open, close, input);
			vector<int> openTest = { 0, 1 };
			vector<int> closeTest = { 2, 3 };
			Assert::AreEqual(1, (int)(open == openTest));
			Assert::AreEqual(1, (int)(close == closeTest));
		}

		TEST_METHOD(TestAdditionBracket)
		{
			vector<int> open, close;
			string input = ")(";
			bracketFilter(open, close, input);

			vector<int> act = { 0, 3 };
			vector<int> test = additionBrackets(open, close);
			Assert::AreEqual(1, (int)(act == test));
		}

		TEST_METHOD(TestFixBracketString)
		{
			string test = "()()";
			Assert::AreEqual(test, fixBracketString(")("));
		}
	};

	TEST_CLASS(Ex2)
	{
	public:
		TEST_METHOD(TestSearchWord)
		{
			string a = "hung "
			Assert::AreEqual(1, )
		}
		
		TEST_METHOD(TestReplaceWord)
		{

		}
	};
}