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



char* reverse_string(char* param_1)
{
    int length = strlen(param_1);
    for (int i = 0; i < length / 2; i++)
    {
        char storage = param_1[i];
        param_1[i] = param_1[length - i - 1];
        param_1[length - i - 1] = storage;
    }
    return param_1;
}

char hex_to_char (int num, char base)
{
    char return_val;
    if (num == 15)
    {
        if (base == 'X')
        {
            return_val = 'F';
        }
        else if (base == 'x')
        {
            return_val = 'f';
        }
        
    }
    else if (num == 14)
    {
        if (base == 'X')
        {
            return_val = 'E';
        }
        else if (base == 'x')
        {
            return_val = 'e';
        }
    }
    else if (num == 13)
    {
        if (base == 'X')
        {
            return_val = 'D';
        }
        else if (base == 'x')
        {
            return_val = 'd';
        }
    }
    else if (num == 12)
    {
        if (base == 'X')
        {
            return_val = 'C';
        }
        else if (base == 'x')
        {
            return_val = 'c';
        }
    }
    else if (num == 11)
    {
        if (base == 'X')
        {
            return_val = 'B';
        }
        else if (base == 'x')
        {
            return_val = 'b';
        }
    }
    else if (num == 10)
    {
        if (base == 'X')
        {
            return_val = 'A';
        }
        else if (base == 'x')
        {
            return_val = 'a';
        }
    }
    else
    {
        return_val = num + '0';
    }
    return return_val;
}

char *num_to_str(int num, char base)
{
    int mod; //This is used to do operations in the specific base.
    int neg = 0; //this identifies if a number is negative. 1 means the number is negative, 0 means the number is non-negative.
    int remainder;
    char *str;
    if (base == 'd')
    {
        if (num < 0) //this is to catch negative numbers.
        {
            num = num * -1;
            neg = 1;
        }
        mod = 10;
        str = malloc(sizeof(char) * 11); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.
        int i = 0;        
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = remainder + '0';
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = num + '0';
        if (neg == 1) //Adds a '-' to the string for negative numbers
        {
            i++;
            str[i] = '-';
        }
        str = reverse_string(str); //Reverses the string to provide a clean output.
    }
    else if (base == 'o')
    {
        mod = 8;
        str = malloc(sizeof(char) * 11); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.
        int i = 0;        
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = remainder + '0';
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = num + '0';
        str = reverse_string(str); //Reverses the string to provide a clean output.
    }
    else if (base == 'u')
    {
        mod = 10;
        str = malloc(sizeof(char) * 11); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.
        int i = 0;        
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = remainder + '0';
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = num + '0';
        str = reverse_string(str); //Reverses the string to provide a clean output.
    }
    else if (base == 'x' || base == 'X')
    {
        mod = 16;
        str = malloc(sizeof(char) * 11); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.
        int i = 0;        
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = hex_to_char(remainder, base);
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = hex_to_char(num, base);
        str = reverse_string(str); //Reverses the string to provide a clean output.
    }
    return str;
}

void insert(char c, va_list args) //This function determines how to add the next item in args to a string
{
    if (c == 'd' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
    {
        int num = va_arg(args, int);
        char *val = num_to_str(num, c);
        int i = 0;
        while (val[i] != '\0')
        {
            write(1, &val[i], 1);
            i++;
        }
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
        //This if statement is very similar to the num_to_str function. I didn't copy that here because num_to_str takes ints, not long ints
        unsigned long int mod = 16;
        int remainder;
        unsigned long int num = va_arg(args, unsigned long int); //in a 64 bit system, a void pointer can have a size of 8 bytes, therefore we use a long int to store the value.
        char *str = malloc(sizeof(char) * 20); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.
        int i = 0;        
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = hex_to_char(remainder, 'x');
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = hex_to_char(num, 'x');
        str[i + 1] = 'x';
        str[i + 2] = '0';
        str = reverse_string(str); //Reverses the string to provide a clean output.
        i = 0;  //reset i to 0 to write all the characters
        while (str[i] != '\0')
        {
            write(1, &str[i], 1);
            i++;
        }
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
    int num = 0xFA123;
    void *p = &num;
    printf("printf: %p\n", p);
    my_printf("my_printf: %p\n", p);
    return 0;
}