#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "./LXML/LXML.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;  // => Light-XML-Parser

namespace LXMLTests
{
	TEST_CLASS(LXML_Tests_2) {
public:

	TEST_METHOD(Instances) {
		// Arrange
		
		LXML* pRoot = new LXML();

		LXMLElement* pBranch = pRoot->CreateNewChild("BRANCH");
		pRoot->AddElement(pBranch);
		
		pBranch->AddElement(pBranch->CreateNewChild("Quickleaf"));

		// Act
		LXMLElement* pLeaf = pBranch->CreateNewChild("LEAF");		
		bool actual = pBranch->AddElement(pLeaf);

		// Assert
		Assert::IsNotNull(pRoot);
		size_t count = 0;
		bool isTrue = false;
		count = pBranch->Childs()->size();
		isTrue = count == 2;
		Assert::IsTrue(isTrue);

		count = pRoot->Childs()->size();
		isTrue = count == 1;
		Assert::IsTrue(isTrue);

		Assert::IsTrue(actual); // At the end, to check all other stuff.

		// Trash
		delete pRoot; pRoot = nullptr;
	}


	TEST_METHOD(Add_Element_On_Wrong_Places) {
		// Arrange
		LXML* pRoot = new LXML();

		LXMLElement* pBranch = pRoot->CreateNewChild("BRANCH");
		pRoot->AddElement(pBranch);

		pBranch->AddElement(pBranch->CreateNewChild("Quickleaf"));
		
		// Act
		LXMLElement* pLeaf = pRoot->CreateNewChild("LEAF");
		bool actual = pBranch->AddElement(pLeaf);

		// Assert
		
		Assert::IsNotNull(pRoot);
		size_t count = pBranch->Childs()->size();
		bool isTrue = count == 1;
		Assert::IsTrue(isTrue);

		count = pRoot->Childs()->size();
		isTrue = count == 1;
		Assert::IsTrue(isTrue);

		Assert::IsFalse(actual); // At the end, to check all other stuff.

		// Trash
		delete pRoot; pRoot = nullptr;
	}


	TEST_METHOD(Sanitize) {
		// Arrange
		const string testString	= "hallo\nwelt";
		const string expected = "hallowelt";
		LXML* pRoot = new LXML();

		// Act		
		string actual = pRoot->Sanitize(testString);

		// Assert
		Assert::AreEqual(actual, expected);
		Assert::AreNotEqual(actual, testString);

		// Trash
		delete pRoot; pRoot = nullptr;
	}


	TEST_METHOD(OneFlatElement) {
		// Arrange
		const string testString = "<xml hallo='a'/>";
		string keytag = "xml";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);		
		Assert::IsTrue(pElement->ChangingText().empty());

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eFalse;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}

	TEST_METHOD(OneFlatElement_W_closing) {
		// Arrange
		const string testString = "<xml hallo='a'></xml>";
		string keytag = "xml";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		Assert::IsTrue(pElement->ChangingText().empty());

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eFalse;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}

	TEST_METHOD(OneFlatElement_W_closing_and_Value) {
		// Arrange
		const string testString = "<xml hallo='a'>99</xml>";
		string keytag = "xml";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		Assert::IsTrue(pElement->ChangingText().empty());

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eFalse;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "99";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}


	TEST_METHOD(OneFlatElement_W_One_Sub) {
		// Arrange
		const string testString = "<xml hallo='a'><sub welt='ball'>22</sub></xml>";
		string keytag = "xml";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		Assert::IsTrue(pElement->ChangingText().empty());

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}

	TEST_METHOD(OneFlatElement_W_Two_Subs) {
		// Arrange
		const string testString = "<xml hallo='a'><sub welt='ball'>22</sub><sub welt='apfel'>3</sub></xml>";
		string keytag = "xml";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		Assert::IsTrue(pElement->ChangingText().empty());

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}

	TEST_METHOD(OneFlatElement_W_Two_Subs_all_subs) {
		// Arrange
		const string testString = "<sub hallo='a'><sub welt='ball'>22</sub><sub welt='apfel'>3</sub></sub>";
		string keytag = "sub";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);
		pElement->SetDontCreateXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		Assert::IsTrue(pElement->ChangingText().empty());

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		string generatedXML = pElement->GetXMLNode();
		isTrue = generatedXML == testString;
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}

	TEST_METHOD(OneFlatElement_W_Two_Subs_on_Top_Will_only_take_one) {
		// Arrange
		const string testString = "<sub hallo='a'>11</sub><sub welt='ball'>22</sub>";
		string resultAfterParse = "<sub welt='ball'>22</sub>";
		string keytag = "sub";
		LXML* pElement = new LXML();
		bool isTrue = false;
		pElement->SetIgnoreMissingXMLHead(true);

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		bool theRest = pElement->ChangingText() == resultAfterParse;
		Assert::IsTrue(theRest);

		isTrue = (string)pElement->Key() == keytag;
		Assert::IsTrue(isTrue);

		isTrue = pElement->HasChild() == THasChild::eTrue;
		Assert::IsFalse(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		isTrue = pElement->ValueStr() == "11";
		Assert::IsTrue(isTrue);

		isTrue = pElement->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pElement->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		// Trash
		delete pElement; pElement = nullptr;
	}

	TEST_METHOD(XML_Head_1) {
		// Arrange
		const string testString = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><sub hallo='a'>11</sub>";
		string resultAfterParse = "";
		string keytag = "sub";
		LXML* pElement = new LXML();
		bool isTrue = false;

		// Act		
		bool actual = pElement->Parse(testString);

		// Assert
		Assert::AreEqual(actual, true);
		bool theRest = pElement->ChangingText() == resultAfterParse;
		Assert::IsTrue(theRest);

		isTrue = pElement->HasChild() == THasChild::eFalse;
		Assert::IsTrue(isTrue);

		isTrue = pElement->TagIsClosed() == TTagIsClosed::eTrue;
		Assert::IsTrue(isTrue);

		auto iter = pElement->Childs()->find(keytag);
		isTrue = iter != pElement->Childs()->end();
		Assert::IsTrue(isTrue);
		LXMLElement* pChild = static_cast<LXMLElement*>(iter->second);

		isTrue = pChild->ValueStr() == "11";
		Assert::IsTrue(isTrue);

		isTrue = pChild->Attributes()->size() == 1;
		Assert::IsTrue(isTrue);
		string a = pChild->Attributes()->at("hallo");
		isTrue = a == "a";
		Assert::IsTrue(isTrue);

		string generatedXML = pElement->GetXMLNode();
		isTrue = generatedXML == testString;
		Assert::IsTrue(isTrue);


		// Trash
		delete pElement; pElement = nullptr;
	}

	};
}