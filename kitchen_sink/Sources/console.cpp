#include "pch.h"
#include "..\Headers\console.h"
#include "..\Headers\typedefs.h"
#include <iostream>

//-------------------------------------------------------------------------------------------
// Uses std::cout to print the input string to the console for debugging purposes
//-------------------------------------------------------------------------------------------
void CONSOLE::print_to_console( string print_string /*= ""*/ )
{
	std::cout << print_string << std::endl;
}
