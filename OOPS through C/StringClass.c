#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
// defining string class
struct StringClass
{
   char* (*get)(const void* self);
   void (*set)(const void* self,char * val);
   int (*len)(const void* self);
   char value[256];
};
typedef struct StringClass * String;
// default methods
   char* getString(const void * self);
   void setString(const void* self,char * val);
   int length(const void* self);
   String new_String();
    void freeString(void* self);
// making constructor
// Immutable classes inheretence
struct ImmutableString
{
   String base;
   // set is inherited from the base string class
   char* (* get)(const void* self);
   int (*len)(const void* self);
};
typedef struct ImmutableString* ImString;
// contrustor
ImString new_ImString(char * string)
{
   ImString str=(ImString) malloc(sizeof(struct ImmutableString));
   str->base=new_String();
   str->get=str->base->get;
   str->len=str->base->len;
   str->base->set(str,string);
   return str;
}
int main()
{
    String str=new_String();
    str->set(str,"HELLO");
      printf("String : %s\n", str->get(str));
    str->set(str,"modified string ");
      printf("String modified : %s\n", str->get(str));
    printf("String Length: %d\n%s", str->len(str),str);
    ImString str2=new_ImString("HI I AM NEW");
    printf("\nNES STR IMMUTABLE :  %s",str2->get(str2));
    printf("\nNEw sTR len IMMUTABLE %d",str2->len(str2));
   //  str2->set(str2,"HII modified immutable");
   //  printf("\nNES STR IMMUTABLE modified :  %s",str2->get(str2));
    freeString(str);
    freeString(str2);
   //  printf("\nNEw sTR len IMMUTABLE %d",str2->len(str2));
    return EXIT_SUCCESS;
}
char* getString(const void * self)
{
   return (char*)((String)self)->value;
}

void setString(const void* self_obj,char* val)
{
   strcpy(((String)self_obj)->value, val);
}

int length(const void* self_obj)
{
   return strlen(((String)self_obj)->value);
}
String new_String()
{
   String str = (String) malloc(sizeof(struct StringClass));
   // assigning address to every method for pointers
   str->get = &getString;
   str->set = &setString;
   str->len = &length;
   str->set(str, "");
   return str;
}
void freeString(void* self_obj)
{
   free(self_obj);
}