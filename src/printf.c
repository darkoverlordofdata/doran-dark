#include <stdio.h> 
#include <stdarg.h>
#include <math.h> 
#include <dark/Foundation.h>


char* convert(unsigned int, int);       //Convert integer number into octal, hex, etc.



__attribute__((__format__ (__printf__, 1, 2)))                          \
char* DSsprintf(const char* format, ...) 
{
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = DSvsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return "";
    char* str = DSCalloc((len+1), sizeof(char));
    len = DSvsnprintf(str, len+1, format, args2);
    va_end(args2);
    return str;
}

void DSvfprintf(FILE* stream, const char* format, va_list _args) 
{
    va_list args1;
    va_list args2;
    
    va_copy(args1, _args);
    va_copy(args2, _args);  

    int len = DSvsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    char* str = DSCalloc((len+1), sizeof(char));
    len = DSvsnprintf(str, len+1, format, args2);
    va_end(args2);
    fputs(str, stream);
    return;
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


int DSvsnprintf(char* str, size_t n, const char* format, va_list _args)  
{
    char *traverse; 
    char result[40];
    unsigned int i; 
    double f;
    char *s;
    char *cvt;
    char *dst = str;
    DSObject* object;
    bool canWrite = (str != nullptr);
    int length = 0;
    int l;

    //Module 1: Initializing printf's arguments 
    va_list arg; 
    va_copy(arg, _args);
    
    for(traverse = format; *traverse != '\0'; traverse++) 
    { 

        while( *traverse != '%' ) 
        { 
            if (*traverse == '\0') return length;
            if (canWrite) *dst++ = *traverse;
            traverse++; 
            length++;
        } 
        
        traverse++; 
        
        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        if (canWrite) *dst++ = i;
                        length++;
                        break; 
                        
            case 'f' : f = va_arg(arg,double);
                        // printf("double value = %f\n", f);
                        sprintf(result, "%f", f);
                        l = strlen(result);
                        if (canWrite) dst = strncpy(dst, result, l) + 1;
                        length += l;
                        break;

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            if (canWrite) *dst++ = '-';
                            length++;
                        } 
                        cvt = convert(i,10);
                        l = strlen(cvt);
                        if (canWrite) dst = strncpy(dst, cvt, l) + l;
                        length += l;
                        break; 
                        
            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        cvt = convert(i,8);
                        l = strlen(cvt);
                        if (canWrite) dst = strncpy(dst, cvt, l) + l;
                        length += l;
                        break; 
                        
            case 's': s = va_arg(arg,char *);       //Fetch string
                        l = strlen(s);
                        if (canWrite) dst = strncpy(dst, s, l) + l;
                        length += l;
                        break; 
                        
            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        cvt = convert(i,16);
                        l = strlen(cvt);
                        if (canWrite) dst = strncpy(dst, cvt, l) + l;
                        length += l;
                        break; 

            case '$': i = va_arg(arg,DSObject *);   // Fetch DaRKSTEP object
                        object = (DSObject*)i;
                        l = strlen(ToString(object));
                        if (canWrite) dst = strncpy(dst, ToString(object), l) + l;
                        length += l;
                        break;
        }   
    } 
    
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
}

