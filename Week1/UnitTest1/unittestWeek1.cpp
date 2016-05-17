#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Week1/Ex1.h"
#include "../Week1/Ex2.h"
#include "../Week1/Ex3.h"
#include "../Week1/Ex5.h"
#include "../Week1/Ex6.h"
#include "../Week1/Ex8.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Week1
{		
	TEST_CLASS(Ex1)
	{
	public:
		//Test method for digitNumber function
		TEST_METHOD(TestDigitNumberFunction)
		{
			Assert::AreEqual(3, digitNumber(100));
			Assert::AreEqual(3, digitNumber(-100));
			Assert::AreEqual(1, digitNumber(0));
		}
		//Test method for descendingOrder function
		TEST_METHOD(TestDescendingOrderFunction)
		{
			Assert::AreEqual(951, descendingOrder(195));
			Assert::AreEqual(-951, descendingOrder(-195));
			Assert::AreEqual(0, descendingOrder(0));
		}
	};

	TEST_CLASS(Ex2)
	{
	public:
		//Test Method for returning upper case characters number of a string
		TEST_METHOD(TestUppercaseCharatersNumber)
		{
			Assert::AreEqual(4, (int)uppercaseCharatersNumber("fasfAFFD"));
			Assert::AreEqual(8, (int)uppercaseCharatersNumber("fasfAFFD/////  sssdfAAAA"));
			Assert::AreEqual(0, (int)uppercaseCharatersNumber("dfasdfasdfasdfas  d"));
		}
		//Test Method for returning lower case characters number of a string
		TEST_METHOD(TestLowercaseCharatersNumber)
		{
			Assert::AreEqual(4, (int)lowercaseCharatersNumber("fasfAFFD"));
			Assert::AreEqual(9, (int)lowercaseCharatersNumber("fasfAFFD/////  sssdfAAAA"));
			Assert::AreEqual(0, (int)lowercaseCharatersNumber("JDHGJHDHJD"));
		}
	};

	TEST_CLASS(Ex3)
	{
	public:
		TEST_METHOD(TestTaxiCostFunction)
		{
			Assert::AreEqual((float) 10000, taxiCost(0.75));
			Assert::AreEqual((float) 11875, taxiCost(1.25));
			Assert::AreEqual((float) 491000, taxiCost(63));
		}
	};

	TEST_CLASS(Ex5)
	{
	public:
		TEST_METHOD(TestIsLeapYearFunction)
		{
			Assert::AreEqual(true, isLeapYear(2016));
			Assert::AreEqual(false, isLeapYear(2015));
			Assert::AreEqual(true, isLeapYear(2012));
		}

		TEST_METHOD(TestIsValidDayFunction)
		{
			Assert::AreEqual(true, isValidDay(29, 2, 2016));
			Assert::AreEqual(false, isValidDay(29, 2, 2014));
			Assert::AreEqual(true, isValidDay(29, 2, 2012));
		}
	};

	TEST_CLASS(Ex8)
	{
	public:
		TEST_METHOD(TestReverseStringFunction)
		{
			string testString = "asdfghj";
			Assert::AreEqual(testString, reverseString("jhgfdsa"));
		}
	};

	TEST_CLASS(Ex6)
	{
	public:
		TEST_METHOD(TestTrimFunction)
		{
			string testString = "fsdfa d";
			Assert::AreEqual(testString, trim("   fsdfa d     "));
		}

		TEST_METHOD(TestRemoveRedundantFunction)
		{
			string testString = "today is a good day, I'm good too.";
			Assert::AreEqual(testString, removeRedundant("today is a good day,,,,, I'm good too......"));
		}

		TEST_METHOD(TestNormalizeStringFunction)
		{
			string testString = "today is a good day, I'm good too";
			Assert::AreEqual(testString, normalizeString(trim("   today   is a   good day   ,  ,  ,    I'm good too")));
		}
	};
}