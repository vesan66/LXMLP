#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "LXML/LXMLTagAnalyser.h"
#include "LXML/LXMLTagAnalyser_TestOutlet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;

namespace LXMLTests
{	
	LXMLTagAnalyser_TestOutlet* _pHelper{ nullptr }; 

	TEST_CLASS(LXMLTagAnalyser_Tests_2) {
public:


	TEST_CLASS_INITIALIZE(SetUp_Class) {
		// https://docs.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#test_classes
		// https://social.msdn.microsoft.com/Forums/vstudio/en-US/ed56ba06-bc9c-464c-9ca1-d23872f35eb6/using-testclassinitialize-with-cppunittestframework?forum=vcgeneral
		_pHelper = new LXMLTagAnalyser_TestOutlet();
	}


	TEST_CLASS_CLEANUP(TearDown_Class) {
		delete _pHelper; _pHelper = nullptr;
	}


	TEST_METHOD(GoodInput_EndTag_01) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "abcd</xml>";
		string keyTag = "xml";

		string ex_tag = keyTag;
		string ex_value = "abcd";
		_pHelper->SetKeyTag(pCut, keyTag);

		// Act		
		bool actual = pCut->GetNextClosingForThisAndValueBefore(text);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->KeyTag(), keyTag);
		Assert::AreEqual(pCut->ValueStr(), ex_value);
		bool tagIsClosed = pCut->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(tagIsClosed);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(GoodInput_EndTag_02) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "ABCD</xml>";
		string keyTag = "xml";

		string ex_tag = keyTag;
		string ex_value = "ABCD";
		_pHelper->SetKeyTag(pCut, keyTag);

		// Act		
		bool actual = pCut->GetNextClosingForThisAndValueBefore(text);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->KeyTag(), keyTag);
		Assert::AreEqual(pCut->ValueStr(), ex_value);
		bool tagIsClosed = pCut->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(tagIsClosed);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(GoodButEmptyInput_EndTag) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "</xml>";
		string keyTag = "xml";

		string ex_tag = keyTag;
		string ex_value = "";
		_pHelper->SetKeyTag(pCut, keyTag);

		// Act		
		bool actual = pCut->GetNextClosingForThisAndValueBefore(text);

		// Assert
		Assert::IsTrue(actual);
		Assert::AreEqual(pCut->KeyTag(), keyTag);
		Assert::AreEqual(pCut->ValueStr(), ex_value);
		bool tagIsClosed = pCut->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(tagIsClosed);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Bad_Input_EndTag_1) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml>";
		string keyTag = "xml";

		string ex_tag = keyTag;
		string ex_value = "";
		_pHelper->SetKeyTag(pCut, keyTag);

		// Act		
		bool actual = pCut->GetNextClosingForThisAndValueBefore(text);

		// Assert
		Assert::IsFalse(actual);
		Assert::AreEqual(pCut->KeyTag(), keyTag);
		Assert::AreEqual(pCut->ValueStr(), (TValueStr)"");
		bool tagIsClosed = pCut->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsFalse(tagIsClosed);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Bad_Input_EndTag_2) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "sfx dgdfg dfbmldbkneinv";
		string keyTag = "xml";

		string ex_tag = keyTag;
		string ex_value = "";
		_pHelper->SetKeyTag(pCut, keyTag);

		// Act		
		bool actual = pCut->GetNextClosingForThisAndValueBefore(text);

		// Assert
		Assert::IsFalse(actual);
		Assert::AreEqual(pCut->KeyTag(), keyTag);
		Assert::AreEqual(pCut->ValueStr(), (TValueStr)"");
		bool tagIsClosed = pCut->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsFalse(tagIsClosed);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Good_CheckIfNextIsOpenTag) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<xml fdsdf='df'>";

		// Act		
		bool actual = pCut->CheckIfNextIsAnyOpenTag(text);

		// Assert
		Assert::IsTrue(actual);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Bad_CheckIfNextIsOpenTag) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "</xml>";

		// Act		
		bool actual = pCut->CheckIfNextIsAnyOpenTag(text);

		// Assert
		Assert::IsFalse(actual);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Read_XML_Head) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>";

		// Act		
		bool actual = pCut->GetXMLHead(text);

		// Assert
		Assert::IsTrue(actual);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Understand_Namspaces) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<LXML dataversion='1.0' lxmlversion='1.5' xmlns='https://your-namespace.com'/>";
		string expected_0 = "<LXML dataversion='1.0' lxmlversion='1.5' xmlns='https://your-namespace.com'/>";
		string expected_1 = "LXML";
		string ex_key_0 = "dataversion";
		string ex_val_0 = "1.0";
		string ex_key_1 = "lxmlversion";
		string ex_val_1 = "1.5";
		string ex_key_2 = "xmlns";
		string ex_val_2 = "https://your-namespace.com";


		// Act		
		bool actual = pCut->ExplodeOpenTag(text);

		// Assert
		Assert::IsTrue(actual);
		bool isEmptyNode = pCut->IsEmptyNode() == TIsEmptyNode::eTrue;
		Assert::IsTrue(isEmptyNode);
		Assert::AreEqual(pCut->KeyTag(), expected_1);
		TAttributes items = pCut->Attributes();
		Assert::AreEqual(items.size(), (size_t)3);
		Assert::AreEqual(items[ex_key_0], ex_val_0);
		Assert::AreEqual(items[ex_key_1], ex_val_1);
		Assert::AreEqual(items[ex_key_2], ex_val_2);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(Understand_Namspaces_2) {
		// Arrange
		LXMLTagAnalyser* pCut = new LXMLTagAnalyser();
		string text = "<LXML dataversion='1.0' lxmlversion='1.5' xmlns='https://your-namespace.com'/>";

		// Act		
		bool actual = pCut->CheckIfNextIsAnyOpenTag(text);

		// Assert
		Assert::IsTrue(actual);

		// Trash
		delete pCut; pCut = nullptr;
	}

	};
}