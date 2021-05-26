#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "LXML/LXMLTagAnalyser.h"
#include "LXML/LXMLTagAnalyser_TestOutlet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;

namespace LXMLTests
{
	TEST_CLASS(LXMLTagAnalyser_Tests_1) {
public:

	TEST_METHOD(Instance) {
		// Arrange
	
		// Act		
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();

		// Assert
		Assert::IsNotNull(pCut);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(GoodInput_Two_Attributes) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		LXMLTagAnalyser_TestOutlet* pHelper = new LXMLTagAnalyser_TestOutlet();

		string text = "abc='456' def='wert'";
		string ex_key_0 = "abc";
		string ex_val_0 = "456";
		string ex_key_1 = "def";
		string ex_val_1 = "wert";

		// Act		
		bool actual = pHelper->ExplodeAttributes(pCut, text);

		// Assert
		Assert::IsTrue(actual);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t) 2);
		Assert::AreEqual(items[ex_key_0], ex_val_0);
		Assert::AreEqual(items[ex_key_1], ex_val_1);

		// Trash
		delete pCut; pCut = nullptr;
		delete pHelper; pHelper = nullptr;

	}

	TEST_METHOD(GoodInput_One_Attributes) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		LXMLTagAnalyser_TestOutlet* pHelper = new LXMLTagAnalyser_TestOutlet();
		string text = "abc='456'";
		string ex_key_0 = "abc";
		string ex_val_0 = "456";

		// Act		
		bool actual = pHelper->ExplodeAttributes(pCut, text);

		// Assert
		Assert::IsTrue(actual);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t) 1);
		Assert::AreEqual(items[ex_key_0], ex_val_0);

		// Trash
		delete pCut; pCut = nullptr;
		delete pHelper; pHelper = nullptr;
	}
	
	TEST_METHOD(GoodInput_No_Attributes) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		LXMLTagAnalyser_TestOutlet* pHelper = new LXMLTagAnalyser_TestOutlet();
		string text = "";

		// Act		
		bool actual = pHelper->ExplodeAttributes(pCut, text);

		// Assert
		Assert::IsTrue(actual);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
		delete pHelper; pHelper = nullptr;
	}

	TEST_METHOD(GoodInput_Illegal_Attributes_0) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		LXMLTagAnalyser_TestOutlet* pHelper = new LXMLTagAnalyser_TestOutlet();
		string text = "abc='456";

		// Act		
		bool actual = pHelper->ExplodeAttributes(pCut, text);

		// Assert
		Assert::IsFalse(actual);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
		delete pHelper; pHelper = nullptr;
	}

	TEST_METHOD(GoodInput_Illegal_Attributes_1) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		LXMLTagAnalyser_TestOutlet* pHelper = new LXMLTagAnalyser_TestOutlet();
		string text = "abc'456'";

		// Act		
		bool actual = pHelper->ExplodeAttributes(pCut, text);

		// Assert
		Assert::IsFalse(actual);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
		delete pHelper; pHelper = nullptr;
	}

	TEST_METHOD(GoodInput_Illegal_Attributes_2) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		LXMLTagAnalyser_TestOutlet* pHelper = new LXMLTagAnalyser_TestOutlet();
		string text = " abc='456'";

		// Act		
		bool actual = pHelper->ExplodeAttributes(pCut, text);

		// Assert
		Assert::IsFalse(actual);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
		delete pHelper; pHelper = nullptr;
	}

	TEST_METHOD(Explode_Tag_Empty) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml abc='456'/>";
		string expected_0 = "<xml abc='456'/>";
		string expected_1 = "xml";
		string ex_key_0 = "abc";
		string ex_val_0 = "456";

		// Act		
		bool actual = pCut->ExplodeOpenTag(text);

		// Assert
		Assert::IsTrue(actual);
		bool isEmptyNode = pCut->IsEmptyNode() == TIsEmptyNode::eTrue;
		Assert::IsTrue(isEmptyNode);
		Assert::AreEqual(pCut->KeyTag(), expected_1);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)1);
		Assert::AreEqual(items[ex_key_0], ex_val_0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Explode_Tag_Not_Empty) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml abc='456'/>";
		string expected_0 = "<xml abc='456'/>";
		string expected_1 = "xml";
		string ex_key_0 = "abc";
		string ex_val_0 = "456";

		// Act		
		bool actual = pCut->ExplodeOpenTag(text);

		// Assert
		Assert::IsTrue(actual);
		bool isEmptyNode = pCut->IsEmptyNode() == TIsEmptyNode::eTrue;
		Assert::IsTrue(isEmptyNode);
		Assert::AreEqual(pCut->KeyTag(), expected_1);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)1);
		Assert::AreEqual(items[ex_key_0], ex_val_0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Explode_Tag_No_Attributes_Empty) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml/>";
		TKeyTagStr expected_1 = "xml";

		// Act		
		bool actual = pCut->ExplodeOpenTag(text);

		// Assert
		Assert::IsTrue(actual);
		bool isEmptyNode = pCut->IsEmptyNode() == TIsEmptyNode::eTrue;
		Assert::IsTrue(isEmptyNode);
		Assert::AreEqual(pCut->KeyTag(), expected_1);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Explode_Tag_No_Attributes_Not_Empty) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml>";
		string expected_1 = "xml";

		// Act		
		bool actual = pCut->ExplodeOpenTag(text);

		// Assert
		Assert::IsTrue(actual);
		bool isEmptyNode = pCut->IsEmptyNode() == TIsEmptyNode::eTrue;
		Assert::IsFalse(isEmptyNode);
		Assert::AreEqual(pCut->KeyTag(), expected_1);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Explode_Tag_MustFail) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml abc='4abc='456'56'/>";

		// Act		
		bool actual = pCut->ExplodeOpenTag(text);

		// Assert
		Assert::IsFalse(actual);
		bool isEmptyNode = pCut->IsEmptyNode() == TIsEmptyNode::eUndefined;
		Assert::IsTrue(isEmptyNode);
		Assert::AreEqual(pCut->KeyTag(), TKeyTagStr(""));
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)0);

		// Trash
		delete pCut; pCut = nullptr;
	}
	};
}