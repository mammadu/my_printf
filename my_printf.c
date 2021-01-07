/*
Printf

Goals:
* Take a string and print it to standard output.
* If any modifiers are given I have to replace the modifier with the proper element at the location of the modifier
* I need to be able to account for an unknown amount of modifiers

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
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void insert(char c, va_list args) //This function determines how to add the next item in args to a string
{
    if (c == 'd')
    {
        // char* str = (char*)malloc(sizeof(char) * 11);
        // itoa(va_arg(args,int), str, 10); //itoa isn't a standard function in stdlib.h, I'll have to develop my own function
        // int i = 0;
        // while (str[i] != '\0')
        // {
        //     write(1, &str[i], 1);
        //     i++;
        // }
        // free(str);
    }
    else if (c == 'o')
    {

    }
    else if (c == 'u')
    {
        
    }
    else if (c == 'x')
    {
        
    }
    else if (c == 'c')
    {
        char val = va_arg(args, int);
        write(1, &val, 1);
    }
    else if (c == 's')
    {
        char* val = va_arg(args, char*);
        int i = 0;
        while (val[i] != '\0')
        {
            write(1, &val[i], 1);
            i++;
        }
    }
    else if (c == 'p')
    {
        
    }
}


int my_printf(char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    int i = 0;
    while (format[i] != '\0')
    {
        if(format[i] == '%') //if we see a modifier, look at the next character to see what to do.
        {
            i++;
            insert(format[i], args); //the insert function will take the character and insert whatever is next in the args list
        }
        else
        {
            write(1, &format[i], 1);
        }
        i++;
    }
    va_end(args);
    return strlen(format);
}

int main()
{
    char *str = "fuck everything";
    printf("printf: hello world\n");
    my_printf("my_printf: hello world %s", str);
    return 0;
}