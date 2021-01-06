/*
Printf

Goals:
* Take a string and print it to standard output.
* If any modifiers are given I have to replace the modifier with the proper element at the location of the modifier
* I need to be able to account for an variable amount of modifiers (look into stdarg for this)

I think I can just use the write function for basic strings. The difficulty will be in dealing with the different format modifiers.
I'll probably have to take the different formats and convert them to character strings then insert that into the final string

I have to account for the following modifiers
%d: decimal 
%o: unsigned octal
%u: unsigned decimal
%x: unsigned hexadecimal
%c: character
%s: pointer to array of characters
%p: void pointer argument printed in hexadecimal

I'll have to make sure the arguments match the specifier type
I'll have to make sure the arguments are processed in the correct order
*/

#include <stdarg.h>

int printf(char* string,)