#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "globals_globals.h"
#include "LXMLObjectMapper/LXMLObject.h"

using namespace std;
using namespace LXMLObjects;

class SubSub : public LXMLObject {
public:
	inline explicit SubSub() : LXMLObject() { SHOWC; };
	inline virtual ~SubSub() override { SHOWD; };

	virtual string ClassNameXML() const override;
	static string ClassName();

protected:

	inline virtual bool FillObjectFromSource(LXMLElement* pLXML) override {
		bool wasDefault = false;

		// Read a string.
		this->_b = this->GetStringFromSource_Or_Default(pLXML, k_b, _default_b, wasDefault);
		return true;
	}

	inline virtual bool FillSourceFromObject(LXMLElement* pLXML) override {

		this->AddStringNode(pLXML, k_b, "Eine Orange!");

		return true;
	}


public:
	int _a = 3;
	string _b = "";
	double _c = 99.60;
public: //private:
	string k_a = "AKey";
	string k_b = "BKey";
	string k_c = "CKey";

	string _default_b = "Toastbrot";
};
