#pragma once

#include "globals_globals.h"
#include "LXMLObjectMapper/LXMLObject.h"

using namespace std;
using namespace LXMLObjects;

class ContItem : public LXMLObject {
public:
	inline explicit ContItem() : ContItem(0) {};
	inline explicit ContItem(const int& number) : LXMLObject(), _number{ number } { SHOWC; };
	inline virtual ~ContItem() override { SHOWD; };

	virtual string ClassNameXML() const override;
	static string ClassName();

protected:

	inline virtual bool FillObjectFromSource(LXMLElement* pLXML) override {
		bool wasDefault = false;

		// Read a string.
		this->_b = this->GetStringFromSource_Or_Default(pLXML, k_b, _default_b, wasDefault);
		this->_number = this->GetIntFromSource_Or_Default(pLXML, k_number, -1, wasDefault);
		return true;
	}

	inline virtual bool FillSourceFromObject(LXMLElement* pLXML) override {

		this->AddStringNode(pLXML, k_b, "Eine Orange!");
		this->AddIntegerNode(pLXML, k_number, _number);
		return true;
	}


public:
	string _b = "";
	int _number = 0;
private:
	string k_b = "keyofstring";
	string k_number = "number";


	string _default_b = "Toastbrot";
};

