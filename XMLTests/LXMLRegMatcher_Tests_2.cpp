#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "./LXML/LXMLRegMatcher.h"
#include "./LXML/LXMLRegMatcher_TestOutlet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;  // => Light-XML-Parser

namespace LXMLTests {
	namespace b {
	LXMLRegMatcher_TestOutlet* _pHelper{ nullptr };
	}
	using namespace b;
	TEST_CLASS(LXMLRegMatcher_Tests_2) {
public:


	TEST_CLASS_INITIALIZE(SetUp_Class) {
		_pHelper = new LXMLRegMatcher_TestOutlet();
	}


	TEST_CLASS_CLEANUP(TearDown_Class) {
		delete _pHelper; _pHelper = nullptr;
	}
	
	TEST_METHOD(Detect_XML_Open_Tag_At_Begin_0) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "<xml abc='456'>";
		string pattern = openTagPattern;
		string expected_0 = "<xml abc='456'>";
		string expected_1 = "xml";
		string expected_2 = "abc='456'";
		string expected_3 = ">";

		// Act				
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)4);
		Assert::AreEqual(pCut->SimpleResults()[0], expected_0);
		Assert::AreEqual(pCut->SimpleResults()[1], expected_1);
		Assert::AreEqual(pCut->SimpleResults()[2], expected_2);
		Assert::AreEqual(pCut->SimpleResults()[3], expected_3);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Detect_XML_Open_Tag_At_Begin_1) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "<xml abc='456'/>";
		string pattern = openTagPattern;
		string expected_0 = "<xml abc='456'/>";
		string expected_1 = "xml";
		string expected_2 = "abc='456'";
		string expected_3 = "/>";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)4);
		Assert::AreEqual(pCut->SimpleResults()[0], expected_0);
		Assert::AreEqual(pCut->SimpleResults()[1], expected_1);
		Assert::AreEqual(pCut->SimpleResults()[2], expected_2);
		Assert::AreEqual(pCut->SimpleResults()[3], expected_3);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Detect_XML_Open_Tag_At_Begin_2) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "<xml>";
		string pattern = openTagPattern;
		string expected_0 = "<xml>";
		string expected_1 = "xml";
		string expected_2 = "";
		string expected_3 = ">";

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)4);
		Assert::AreEqual(pCut->SimpleResults()[0], expected_0);
		Assert::AreEqual(pCut->SimpleResults()[1], expected_1);
		Assert::AreEqual(pCut->SimpleResults()[2], expected_2);
		Assert::AreEqual(pCut->SimpleResults()[3], expected_3);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Detect_XML_Open_Tag_At_Begin_Fail_0) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "<xml abc='456'";
		string pattern = openTagPattern;

		// Act		
		bool actual = _pHelper->RegExer(pCut, pattern, text, 0, false, false, false);

		// Assert
		Assert::IsFalse(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Detect_XML_CloseTagWithValues) {
		// Arrange
		LXMLRegMatcher* pCut = new LXMLRegMatcher();
		string text = "99</xml>";
		string pattern = closeTagPatternAndValue;

		// Act		
		bool actual = pCut->RegExer_HaystackMatch_Changing(pattern, text);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->SimpleResults().size(), (size_t)3);

		// Trash
		delete pCut; pCut = nullptr;
	}


	};
}