#include <stdio.h> 
#include <stdarg.h>
#include <math.h> 
#include <dark/Foundation.h>


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

int DSvsnprintf(char* str, size_t n, const char* format, va_list _args)  
{
    char *iter; 
    char result[40];
    char spec[40];
    int i;
    int l;
    int c;
    char *s;
    DSObject* object;
    char *dst = str;
    bool canWrite = (str != nullptr);
    int length = 0;
    char* types = "diuoxXfFeEgGaAcspn$";
    char* types1 ="_&^#@";
    va_list arg; 
    va_copy(arg, _args);
    
    for (iter = format; *iter != '\0'; iter++) { 

        while ( *iter != '%' ) { 
            if (*iter == '\0') return length;
            if (canWrite) *dst++ = *iter;
            iter++; 
            length++;
        } 
        iter++; 
        // while not in types...

        switch (*iter) { 
        default:
            Appendc(spec, *iter);
            break;
        case 'c' :  //Fetch char argument
            i = va_arg(arg,int);    
            if (canWrite) *dst++ = i;
            length++;
            break; 
                    
        case 'f' : 
        case 'F' : 
        case 'e' : 
        case 'E' : 
        case 'g' : 
        case 'G' : 
        case 'a' : 
        case 'A' : 
            l = sprintf(result, "%f", va_arg(arg,double));
            if (canWrite) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'u':
            l = sprintf(result, "%d", va_arg(arg,unsigned int));
            if (canWrite) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'd': //Fetch Decimal argument
        case 'i': //Fetch Integer argument
            l = sprintf(result, "%d", va_arg(arg,int));
            if (canWrite) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'o': //Fetch Octal representation
            l = sprintf(result, "%o", va_arg(arg,unsigned int));
            if (canWrite) dst = strncpy(dst, result, l) + l;
            length += l;
            break;
                    
        case 's': //Fetch string
            s = va_arg(arg,char *);       
            l = strlen(s);
            if (canWrite) dst = strncpy(dst, s, l) + l;
            length += l;
            break; 
                    
        case 'x': //Fetch Hexadecimal representation
        case 'X': //Fetch Hexadecimal representation
            l = sprintf(result, "%0x", va_arg(arg,unsigned int));
            if (canWrite) dst = strncpy(dst, result, l) + 1;
            length += l;
            break;

        case '$': // Fetch DaRKSTEP object
            object = va_arg(arg,DSObject *);   
            l = strlen(ToString(object));
            if (canWrite) dst = strncpy(dst, ToString(object), l) + l;
            length += l;
            break;
        }   
    } 
    va_end(arg); 
}

