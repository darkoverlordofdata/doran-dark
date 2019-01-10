#include <dark/Foundation.h>
#include <stdio.h> 
#include <stdarg.h>                      

char* convert(unsigned int, int);       //Convert integer number into octal, hex, etc.

void DSvfprintf(FILE* stream, char* format, va_list _args) 
{ 
    char *traverse; 
    unsigned int i; 
    char *s; 
    DSObject* object;

    //Module 1: Initializing printf's arguments 
    va_list arg; 
    va_copy(arg, _args);
    
    for(traverse = format; *traverse != '\0'; traverse++) 
    { 

        while( *traverse != '%' ) 
        { 
            if (*traverse == '\0') return;
            fputc(*traverse, stream);
            traverse++; 
        } 
        
        traverse++; 
        
        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        fputc(i, stream);
                        break; 
                        
            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            fputc('-', stream); 
                        } 
                        fputs(convert(i,10), stream);
                        break; 
                        
            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        fputs(convert(i,8), stream);
                        break; 
                        
            case 's': s = va_arg(arg,char *);       //Fetch string
                        fputs(s, stream); 
                        break; 
                        
            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        fputs(convert(i,16), stream);
                        break; 

            case '$': i = va_arg(arg,DSObject *);   // Fetch DaRKSTEP object
                        object = (DSObject*)i;
                        fputs(ToString(object), stream);
                        break;
        }   
    } 
    
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 
    
    ptr = &buffer[49]; 
    *ptr = '\0'; 
    
    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 
    
    return(ptr); 
}