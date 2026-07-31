#include "File1.h"
#include "Static.h"
#include <iostream>

void FileOneFunction()
{
	++variable;
	std::cout 
		<< "File1, variable: "
		<< variable
		<< "\n";
}