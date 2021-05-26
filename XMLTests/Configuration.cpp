#include "pch.h"
#include "Configuration.h"

string Configuration::ClassNameXML() const {
	return Configuration::ClassName();
}


string Configuration::ClassName() {
	return "configuration";
}