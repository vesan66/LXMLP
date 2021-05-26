#include "pch.h"
#include "CppUnitTest.h"
#include "./LXMLObjectMapper/LXMLObject.h"
#include "Configuration.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LXMLP;  // => Light-XML-Parser

namespace LXMLObjectTests
{
	TEST_CLASS(LXMLObject_Tests_1) {
public:

	TEST_METHOD(EmptyObject) {
		// Arrange		
		string expected = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><LXML dataversion='1.0' lxmlversion='1.0' xmlns='https://your-namespace.com'><ROOT classname='configuration' type='object'><A type='integer'>22</A><B encoded='binhex' type='string'>44617320697374206461206472696E6E652E</B><C type='double'>3.330000</C><D type='bool'>true</D><ampcont type='keyedcontainer'><dreik classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>13</number></dreik><einsk classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>11</number></einsk><zweik classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>12</number></zweik></ampcont><pS1 classname='subsub' type='object'><BKey encoded='binhex' type='string'>45696E65204F72616E676521</BKey></pS1><stringIntMap type='simplekeyedcontainer'><Banane type='integer'>5</Banane><Hallo type='integer'>2</Hallo><Schokolade type='integer'>4</Schokolade></stringIntMap><stringvector type='simplecontainer'><ITEM encoded='binhex' type='string'>526F6D</ITEM><ITEM encoded='binhex' type='string'>4E697A7A61</ITEM><ITEM encoded='binhex' type='string'>4265726C696E</ITEM></stringvector><vectcont type='container'><ITEM classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>22</number></ITEM><ITEM classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>23</number></ITEM></vectcont></ROOT></LXML>";
		Configuration* pCut = new Configuration();

		// Act
		string actual = pCut->GetXMLNode();

		// Assert
		Assert::IsNotNull(pCut);
		Assert::AreEqual(actual, expected);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(GetObjectFromXML) {
		// Arrange		
		string input = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><LXML dataversion='1.0' lxmlversion='1.0' xmlns='https://your-namespace.com'><ROOT classname='configuration' type='object'><A type='integer'>22</A><B encoded='binhex' type='string'>44617320697374206461206472696E6E652E</B><C type='double'>3.330000</C><D type='bool'>true</D><ampcont type='keyedcontainer'><dreik classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>13</number></dreik><einsk classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>11</number></einsk><zweik classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>12</number></zweik></ampcont><pS1 classname='subsub' type='object'><BKey encoded='binhex' type='string'>45696E65204F72616E676521</BKey></pS1><stringIntMap type='simplekeyedcontainer'><Banane type='integer'>5</Banane><Hallo type='integer'>2</Hallo><Schokolade type='integer'>4</Schokolade></stringIntMap><stringvector type='simplecontainer'><ITEM encoded='binhex' type='string'>526F6D</ITEM><ITEM encoded='binhex' type='string'>4E697A7A61</ITEM><ITEM encoded='binhex' type='string'>4265726C696E</ITEM></stringvector><vectcont type='container'><ITEM classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>22</number></ITEM><ITEM classname='contitem' type='object'><keyofstring encoded='binhex' type='string'>45696E65204F72616E676521</keyofstring><number type='integer'>23</number></ITEM></vectcont></ROOT></LXML>";
		Configuration* pCut = new Configuration(false);

		// Act
		bool actual = pCut->LoadObjectFromSourceText(input);

		// Assert
		Assert::IsNotNull(pCut);
		Assert::AreEqual(actual, true);

		// Trash
		delete pCut; pCut = nullptr;
	}


	TEST_METHOD(New_Not_Initialized) {
		// Arrange		
		string expected = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><LXML dataversion='1.0' lxmlversion='1.0' xmlns='https://your-namespace.com'><ROOT classname='configuration' type='object'><A type='integer'>0</A><B encoded='binhex' type='string'>44617320697374206461206472696E6E652E</B><C type='double'>0.000000</C><D type='bool'>false</D></ROOT></LXML>";
		Configuration* pCut = new Configuration(false);
		pCut->LoadObjectFromSourceText("", true);

		// Act
		string actual = pCut->GetXMLNode();

		// Assert
		Assert::IsNotNull(pCut);
		Assert::AreEqual(actual, expected);

		// Trash
		delete pCut; pCut = nullptr;
	}

	};
}
