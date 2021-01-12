#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char* reverse_string(char* param_1)
{
    char* return_val = strdup(param_1);
    int length = strlen(param_1); 
    for (int i = 0; i < (length / 2); i++)
    {
        char storage = param_1[i];
        return_val[i] = param_1[length - i - 1];
        return_val[length - i - 1] = storage;
    }
    return return_val;
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
    int length = 12;
    int i = 0;
    if (base == 'd')
    {
        if (num < 0) //this is to catch negative numbers.
        {
            num = num * -1;
            neg = 1;
        }
        mod = 10;
        str = malloc(sizeof(char) * length); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.   
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
    }
    else if (base == 'o')
    {
        mod = 8;
        str = malloc(sizeof(char) * length); //The greatest value of int is 2,147,483,647. If that value is negative, then we'll need a string that is 11 characters long to hold it.      
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = remainder + '0';
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = num + '0';
    }
    else if (base == 'u')
    {
        mod = 10;
        str = malloc(sizeof(char) * length);
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = remainder + '0';
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = num + '0';
    }
    else if (base == 'x' || base == 'X')
    {
        mod = 16;
        str = malloc(sizeof(char) * length);
        while (num >= mod)
        {
            remainder = num % mod;
            str[i] = hex_to_char(remainder, base);
            i++;
            num = (num - remainder) / mod;
        }
        str[i] = hex_to_char(num, base);
    }
    str = reverse_string(str); //Reverses the string to provide a clean output.
    str = realloc(str, i + 1);
    return str;
}

int insert(char c, va_list args) //This function determines how to add the next item in args to a string
{
    char *val; 
    int i = 0; //this is used to iterate but will also store the number of characters written.
    if (c == 'd' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
    {
        int num = va_arg(args, int);
        val = num_to_str(num, c);
        while (val[i] != '\0')
        {
            write(1, &val[i], 1);
            i++;
        }
    }
    else if (c == 'c')
    {
        val = malloc(sizeof(char));
        *val = va_arg(args, int);
        write(1, val, 1);
        i++;
    }
    else if (c == 's')
    {
        char* val = va_arg(args, char*);
        if (val == NULL)
        {
            val = "(null)";
            while (val[i] != '\0')
            {
                write(1, &val[i], 1);
                i++;
            }
        }
        else
        {
            while (val[i] != '\0')
            {
                write(1, &val[i], 1);
                i++;
            }
        }
    }
    else if (c == 'p')
    {
        //This if statement is very similar to the num_to_str function. I didn't copy that here because num_to_str takes ints, not long ints
        unsigned long int mod = 16;
        int remainder;
        unsigned long int num = va_arg(args, unsigned long int); //in a 64 bit system, a void pointer can have a size of 8 bytes, therefore we use a long int to store the value.
        val = malloc(sizeof(char) * 21); //The greatest value of long int is 4,294,967,295. If that value is negative, then we'll need a string that is 11 characters long to hold it.
        while (num >= mod)
        {
            remainder = num % mod;
            val[i] = hex_to_char(remainder, 'x');
            i++;
            num = (num - remainder) / mod;
        }
        val[i] = hex_to_char(num, 'x');
        val[i + 1] = 'x';
        val[i + 2] = '0';
        val = reverse_string(val); //Reverses the string to provide a clean output.
        i = 0;  //reset i to 0 to write all the characters
        while (val[i] != '\0')
        {
            write(1, &val[i], 1);
            i++;
        }
    }
    return(i);
}

int my_printf(char *format, ...)
{
    va_list args;
    va_start(args, format);  
    char *str = strdup(format);
    int char_written = 0; //this is a count of all the characters written.
    int i = 0;
    while (str[i] != '\0')
    {
        if(str[i] == '%') //if we see a modifier, look at the next character to see what to do.
        {
            i++;
            char_written = char_written + insert(str[i], args); //the insert function will take the character and insert whatever is next in the args list
        }
        else
        {
            write(1, &str[i], 1);
            char_written++;
        }
        i++;
    }    
    va_end(args);
    free(str);
    return char_written;
}

int main()
{
    char* p = "alkhje;lkh";
    int x = my_printf("NULL STRING %p!\n", p);
    int y = printf("NULL STRING %p!\n", p);
    printf("x = %d", x);
    printf("y = %d", y);
    return 0;
}