#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "./LXML/LXMLRegMatcher.h"
#include "./LXML/LXMLRegMatcher_TestOutlet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;  // => Light-XML-Parser

namespace LXMLTests {
	namespace a {
		LXMLRegMatcher_TestOutlet* _pHelper{ nullptr };
	}
	using namespace a;
	TEST_CLASS(LXMLRegMatcher_Tests_1) {
public:
	

	TEST_CLASS_INITIALIZE(SetUp_Class) {
		_pHelper = new LXMLRegMatcher_TestOutlet();
	}


	TEST_CLASS_CLEANUP(TearDown_Class) {
		delete _pHelper; _pHelper = nullptr;
	}

	TEST_METHOD(Instance) {
		// Arrange
		// Act
		LXMLRegMatcher* pCut = new LXMLRegMatcher();

		// Assert
		Assert::IsNotNull(pCut);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Hello_FullMatch) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "Hello";
		string pattern = "Hello";
		string expected = "Hello";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, true, false);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)1);
		Assert::AreEqual(pCut->SimpleResults()[0], expected);

		// Trash
		delete pCut; pCut = nullptr;
	}
	

	TEST_METHOD(SpaceBegin) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = " Hello";   // Space at the begin. Does not match! Intended
		string pattern = "Hello";
		string expected = "Hello";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, true, false);

		// Assert
		Assert::IsFalse(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(SpaceEnd) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "Hello ";   // Space at the end. Does not match! Intended
		string pattern = "Hello";
		string expected = "Hello";

		// Act				
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, true, false);

		// Assert
		Assert::IsFalse(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Haystacker_SpaceBegin) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = " Hello ";   // Element inside spaces.
		string pattern = "Hello";
		string expected = "Hello";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)1);
		Assert::AreEqual(pCut->SimpleResults()[0], expected);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Haystacker_Muststart_at_Pos_0_To_Pass) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "Hello xvsehsndb";
		string pattern = "^Hello";
		string expected = "Hello";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)1);
		Assert::AreEqual(pCut->SimpleResults()[0], expected);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Haystacker_Muststart_at_Pos_0_To_Fail) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = " Hello xvsehsndb";
		string pattern = "^Hello";
		string expected = "Hello";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsFalse(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Haystacker_Multiple_Hello) {
		// Finds the first occurance.

		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "HelloHelloHelloHelloHelloHelloHelloHello";
		string pattern = "Hello";
		string expected = "Hello";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsTrue(true);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)1);
		Assert::AreEqual(pCut->SimpleResults()[0], expected);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Haystacker_Cut_Match) {
		// Cut the first occurance
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "HelloAHelloBHello";
		string pattern = "Hello";
		string expected = "Hello";
		string expectedText = "AHelloBHello";

		// Act				
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, true);

		// Assert
		Assert::IsTrue(true);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)1);
		Assert::AreEqual(pCut->SimpleResults()[0], expected);
		Assert::AreEqual(text, expectedText);

		// Trash
		delete pCut; pCut = nullptr;
	}


	};
}