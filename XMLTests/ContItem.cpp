#include "pch.h"
#include "ContItem.h"


string ContItem::ClassNameXML() const {
    return ContItem::ClassName();
}


string ContItem::ClassName() {
    return "contitem";
}