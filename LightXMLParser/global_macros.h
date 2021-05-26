#pragma once
#include <iostream>

#ifdef WIN32
//do some stuff for windows
#elif __APPLE__
//do some stuff for Apple
#elif __linux__
//do stuff for Linux
#endif

using namespace std;


#define _SHOWDESTRUCTORS true
#define _SHOWCONSTRUCTORS true
#define _SHOWOTHERS false




#if _SHOWDESTRUCTORS == true
#define SHOWD cout<< __FUNCTION__ << " $$$" << endl;
#else
#define SHOWD
#endif


#if _SHOWCONSTRUCTORS == true
#define SHOWC cout<< __FUNCTION__ << " ###" << endl;
#else
#define SHOWC
#endif


#if _SHOWOTHERS == true
#define SHOWO cout<< __FUNCTION__ << endl;
#else
#define SHOWO
#endif

#if _SHOWOTHERS == true
#define SHOWOMessage(message) cout<< __FUNCTION__ << ": " << message << endl;
#else
#define SHOWOMessage(message)
#endif