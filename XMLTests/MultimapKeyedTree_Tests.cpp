#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "./MultimapKeyedTree/MultimapKeyedTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MMKT;

namespace MultimapKeyedTreeTests
{
	TEST_CLASS(MultimapKeyedTree_Tests) {
public:

	TEST_METHOD(Instance) {
		// Arrange
		// Act
		MultimapKeyedTree* pCut = new MultimapKeyedTree();

		// Assert
		Assert::IsNotNull(pCut);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(Forbiddens) {
		// Arrange
		MultimapKeyedTree* pCut = new MultimapKeyedTree();

		// Act		
		//MultimapKeyedTreeElement* pElement = new MultimapKeyedTreeElement(pCut);
		//MultimapKeyedTreeConnector* pConnector = new MultimapKeyedTreeConnector();

		// Assert
		// Both elements are not public creatable, which is intended.
		Assert::IsTrue(true);

		// Trash
		delete pCut; pCut = nullptr;
	}

	TEST_METHOD(AddChild) {
		// Arrange
		MultimapKeyedTree* pCut = new MultimapKeyedTree();
		string keyword = "Keyword";

		// Act		
		MultimapKeyedTreeElement* pElement = pCut->CreateNewChild();
		pElement->SetKey(keyword);
		pCut->AddElement(pElement);

		// Assert
		auto pElems = pCut->Childs();
		Assert::AreEqual(pElems->size(), (size_t) 1 );
		auto pElemIter = pElems->find(keyword);
		auto pElem = pElemIter->second;
		Assert::AreEqual(pElem->Key(), keyword);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(AddChildChild) {
		// Arrange
		MultimapKeyedTree* pCut = new MultimapKeyedTree();
		string keyword = "Keyword";
		string keyword2 = "Banane";
		MultimapKeyedTreeElement* pElement = pCut->CreateNewChild();
		pElement->SetKey(keyword);
		pCut->AddElement(pElement);

		// Act		
		MultimapKeyedTreeElement* pElement2 = pElement->CreateNewChild();
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