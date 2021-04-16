#pragma once
#include "..\Headers\typedefs.h"

//-------------------------------------------------------------------------------------------
// CONSOLE is a tiny class so that I dont have to include <iostream> everywhere
// when I want to test something by printing to the console
//-------------------------------------------------------------------------------------------
class CONSOLE
{
public:
	static void print_to_console(string print_string = "");
};