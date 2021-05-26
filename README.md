# LXMLP
Light XML Parser.

This is a simple XML-Parser and Object-to-xml-to-file mapper.

## What is it used for?
You may use this bunch of files, if you want to store some more sophisticated configurations of your software.

If you want to avoid dependencies to larger frameworks.

## What can by stored?
- Bool, Int, Double, String
- Sub objects
- Containers of objects
- Containers of simple types

### How to use it.
Take a look a the Unittest-Helper-Classes like LXMLP/XMLTests/Configuration.h and LXMLP/XMLTests/Configuration.cpp.
Short: Inherit from 'LXMLObject' and override the needed methods like:
 - FillObjectFromSource(LXMLElement* pLXML)
 - FillSourceFromObject(LXMLElement* pLXML)
 - inline virtual string ClassNameXML() const override { return ContItem::ClassName(); }
 
and implement this:
  - inline string ClassName() { return "THE_NAME_OF_YOUR_CLASS_IN_XML"; }
  
## Things to improve
Today the string values are only converted to Hex to avoid any escaping-circus. Maybe better to use Base64. But a valid char there is a '/', which means: there might be inteferences with the surrounding xml.

## License
MIT - License

