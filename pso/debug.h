#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define DEBUG(...)      std::cerr << "DEBUG: " << (__VA_ARGS__) << std::endl;
#define IFDEBUG(x)      x;

#endif // DEBUG_H
