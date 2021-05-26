#include "pch.h"
#include "CppUnitTest.h"
#include "./LXML/LXML.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;  // => Light-XML-Parser

namespace LXMLTests
{
	TEST_CLASS(LXML_Tests_1)
	{
	public:
		
		TEST_METHOD(Instance) {
			// Arrange
			// Act
			LXML* pCut = new LXML();

			// Assert
			Assert::IsNotNull(pCut);

			// Trash
			delete pCut; pCut = nullptr;
		}

		TEST_METHOD(Forbiddens) {
			// Arrange
			LXML* pCut = new LXML();

			// Act		
			//LXMLElement* pElement = new LXMLElement(pCut);
			//LXMLConnector* pConnector = new LXMLConnector();

			// Assert
			// Both elements are not public creatable, which is intended.
			Assert::IsTrue(true);

			// Trash
			delete pCut; pCut = nullptr;
		}

		TEST_METHOD(AddChild) {
			// Arrange
			LXML* pCut = new LXML();
			string keyword = "Keyword";

			// Act		
			LXMLElement* pElement = pCut->CreateNewChild();
			pElement->SetKey(keyword);
			pCut->AddElement(pElement);

			// Assert
			auto pElems = pCut->Childs();
			Assert::AreEqual(pElems->size(), (size_t)1);
			auto pElemIter = pElems->find(keyword);
			auto pElem = pElemIter->second;
			Assert::AreEqual(pElem->Key(), keyword);

			// Trash
			delete pCut; pCut = nullptr;
		}

		TEST_METHOD(AddChildChild) {
			// Arrange
			LXML* pCut = new LXML();
			string keyword = "Keyword";
			string keyword2 = "Banane";
			LXMLElement* pElement = pCut->CreateNewChild();
			pElement->SetKey(keyword);
			pCut->AddElement(pElement);

			// Act		
			LXMLElement* pElement2 = pElement->CreateNewChild();
			pElement2->SetKey(keyword2);
			pElement->AddElement(pElement2);

			// Assert
			auto pElems = pCut->Childs();
			Assert::AreEqual(pElems->size(), (size_t)1);
			auto pElemIter = pElems->find(keyword);
			auto pElem = pElemIter->second;
			Assert::AreEqual(pElem->Key(), keyword);

			auto pElems2 = pElem->Childs();
			Assert::AreEqual(pElems2->size(), (size_t)1);
			auto pElem2Iter = pElems2->find(keyword2);
			auto pElem2 = pElem2Iter->second;
			Assert::AreEqual(pElem2->Key(), keyword2);

			// Trash
			delete pCut; pCut = nullptr;
		}
	};
}
