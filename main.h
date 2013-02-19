#ifndef OZ7FOX_MAIN
#define OZ7FOX_MAIN
#include "key.h"

/**
 * @file main.h
 * @brief Header file for main
 * 
 * For documentation of its functions, see the documentation of \c{main.c}
 */
ticks_t sendFoxID(uint8_t fox_number);
ticks_t sendCallsign();
void initPorts();

#endif /* OZ7FOX_MAIN */
