#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "globals_globals.h"
#include "LXMLObjectMapper/LXMLObject.h"
#include "SubSub.h"
#include "ContItem.h"
#include <functional>

using namespace std;
using namespace LXMLObjects;

class Configuration : public LXMLObject {
public:

	inline explicit Configuration() : Configuration(true) {
	};

	inline explicit Configuration(const bool& init) : LXMLObject() {
		SHOWC;
		if (init) {
			SetValues();
		}
	};

	inline virtual ~Configuration() {
		SHOWD;
		if (_pS1 != nullptr) { delete _pS1; _pS1 = nullptr; }
		if (_pVectStringCont != nullptr) { delete _pVectStringCont; _pVectStringCont = nullptr; }
		if (_pMapSimplenCont != nullptr) { delete _pMapSimplenCont; _pMapSimplenCont = nullptr; }

		if (_pVectCont != nullptr) {

			while (!_pVectCont->empty()) {
				auto item = _pVectCont->front();
				delete item;
				_pVectCont->erase(_pVectCont->begin());
			}
			_pVectCont->clear();
			delete _pVectCont; _pVectCont = nullptr;
		}


		if (_pMapCont != nullptr) {
			for (auto item : *_pMapCont) {
				auto elem = item.second;
				delete elem;
			}
			_pMapCont->clear();
			delete _pMapCont; _pMapCont = nullptr;
		}

	};

	virtual string ClassNameXML() const override;
	static string ClassName();

protected:
	inline virtual bool FillObjectFromSource(LXMLElement* pLXML) override {

		bool wasDefault = false;

		LXMLElement::ELXMLErrors err = pLXML->StateFromLoad();
		SHOWOMessage(std::to_string((int)err));

		// Read a string.
		this->_b = this->GetStringFromSource_Or_Default(pLXML, k_b, _default_b, wasDefault);

		// Read a bool.
		this->_d = this->GetBoolFromSource_Or_Default(pLXML, k_d, _default_d, wasDefault);

		// Read a int.
		this->_a = this->GetIntFromSource_Or_Default(pLXML, k_a, _default_a, wasDefault);

		// Read a Double;
		this->_c = this->GetDoubleFromSource_Or_Default(pLXML, k_c, _default_c, wasDefault);


		function<LXMLObject* ()> creator = [this]()->LXMLObject* {
			if (_pS1 != nullptr) { delete _pS1; _pS1 = nullptr; }
			_pS1 = new SubSub();
			return _pS1;  };
		if (this->GetObjectFromSource(pLXML, k_pS1, SubSub::ClassName(), creator)) {
			if (_pS1 != nullptr) {
				SHOWOMessage(_pS1->_b);
			}
		}


		function<LXMLObject* ()> creator_for_container_item = [this]()->LXMLObject* {
			ContItem* pItem = new ContItem();
			return pItem;  };
		function<bool(LXMLObject*)> append_function = [this](LXMLObject* pItem)->bool {
			if (this->_pVectCont == nullptr) { _pVectCont = new vector<ContItem*>; }
			if (pItem != nullptr) {
				ContItem* pElem = static_cast<ContItem*>(pItem);
				_pVectCont->push_back(pElem);
				return true;
			}
			return false;  };
		if (this->GetContainerFromSource(pLXML, k_VectorContainer, creator_for_container_item, append_function)) {
			if (_pS1 != nullptr) {
				SHOWOMessage(_pS1->_b);
			}
		}


		function<LXMLObject* ()> creator_for_keyedcontainer_item = [this]()->LXMLObject* {
			ContItem* pItem = new ContItem();
			return pItem;  };
		function<bool(LXMLObject*, const string& key)> keyedappend_function = [this](LXMLObject* pItem, const string& key)->bool {
			if (this->_pMapCont == nullptr) { _pMapCont = new map<string, ContItem*>; }
			if ((pItem != nullptr) && (!key.empty())) {
				ContItem* pElem = static_cast<ContItem*>(pItem);
				_pMapCont->insert({ key, pElem });
				return true;
			}
			return false;  };
		if (this->GetKeyedContainerFromSource(pLXML, k_MapContainer, creator_for_keyedcontainer_item, keyedappend_function)) {
			if (_pS1 != nullptr) {
				SHOWOMessage(_pS1->_b);
			}
		}


		function<bool(LXMLElement*, const string& key)> simplekeyedappend_function = [this](LXMLElement* pItem, const string& key)->bool {
			if (this->_pMapSimplenCont == nullptr) { _pMapSimplenCont = new map<string, int>; }
			if ((pItem != nullptr) && (!key.empty())) {
				int value = stoi(pItem->ValueStr());
				_pMapSimplenCont->insert({ key, value });
				return true;
			}
			return false;  };
		if (this->GetSimpleKeyedContainerFromSource(pLXML, k_MapStringIntContainer, simplekeyedappend_function)) {
			if (_pS1 != nullptr) {
				SHOWOMessage(_pS1->_b);
			}
		}


		function<bool(LXMLElement*)> simpleappend_function = [this](LXMLElement* pItem)->bool {
			if (this->_pVectStringCont == nullptr) { _pVectStringCont = new vector<string>; }
			if (pItem != nullptr) {
				bool wasDefault = false;
				string value = this->GetDecodedValueString(pItem, "NaN", wasDefault);
				_pVectStringCont->push_back(value);
				return true;
			}
			return false;  };
		if (this->GetSimpleContainerFromSource(pLXML, k_VectorStringContainer, simpleappend_function)) {
			if (_pS1 != nullptr) {
				SHOWOMessage(_pS1->_b);
			}
		}


		return true;
	}


	inline virtual bool FillSourceFromObject(LXMLElement* pLXML) override {

		this->AddIntegerNode(pLXML, k_a, _a);
		this->AddStringNode(pLXML, k_b, "Das ist da drinne.");
		this->AddDoubleNode(pLXML, k_c, _c);
		this->AddBoolNode(pLXML, k_d, _d);

		this->AddObjectNode(pLXML, k_pS1, _pS1);
		this->AddContainerNode<vector<ContItem*>>(pLXML, k_VectorContainer, _pVectCont);
		this->AddKeyedContainerNode<map<string, ContItem*>>(pLXML, k_MapContainer, _pMapCont);

		this->AddContainerNodeSimpleTypes<vector<string>>(pLXML, k_VectorStringContainer, kAttr_Type_Value_string, _pVectStringCont);

		this->AddKeyedContainerNodeSimpleTypes<map<string, int>>(pLXML, k_MapStringIntContainer, kAttr_Type_Value_integer, _pMapSimplenCont);

		return true;
	}


	inline void SetValues() {
		this->_a = 22;
		this->_b = "Gnu";
		this->_c = 3.33;
		this->_d = true;
		this->_pS1 = new SubSub();
		this->_pVectCont = new vector<ContItem*>;
		this->_pMapCont = new map<string, ContItem*>;
		this->_pVectStringCont = new vector<string>;
		this->_pMapSimplenCont = new map<string, int>;

		ContItem* pCI;
		pCI = new ContItem(22);
		_pVectCont->push_back(pCI);
		pCI = new ContItem(23);
		_pVectCont->push_back(pCI);


		ContItem* pMI;
		pMI = new ContItem(11);
		_pMapCont->insert({ "einsk", pMI });
		pMI = new ContItem(12);
		_pMapCont->insert({ "zweik", pMI });
		pMI = new ContItem(13);
		_pMapCont->insert({ "dreik", pMI });

		_pVectStringCont->push_back({ "Rom" });
		_pVectStringCont->push_back({ "Nizza" });
		_pVectStringCont->push_back({ "Berlin" });


		_pMapSimplenCont->insert({ "Hallo", 2 });
		_pMapSimplenCont->insert({ "Schokolade", 4 });
		_pMapSimplenCont->insert({ "Banane", 5 });

	}


public: // private:
	int _a = 0;
	string _b = "";
	double _c = 0.00;
	bool   _d = false;
	SubSub* _pS1{};

	vector<ContItem*>* _pVectCont{};
	vector<string>* _pVectStringCont{};
	map<string, ContItem*>* _pMapCont{};
	map<string, int>* _pMapSimplenCont{};
public: // private:

	string k_a = "A";
	string k_b = "B";
	string k_c = "C";
	string k_d = "D";
	string k_pS1 = "pS1";

	string k_VectorContainer = "vectcont";
	string k_MapContainer = "ampcont";
	string k_VectorStringContainer = "stringvector";
	string k_MapStringIntContainer = "stringIntMap";

	int _default_a = 6;
	string _default_b = "hallo";
	double _default_c = 5.50;
	bool _default_d = true;
};

