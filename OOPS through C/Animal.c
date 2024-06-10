#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
// virtual table list of pointers for storing methods pointers and it is an interface

struct Animal_vtable
{
    typedef void (* Walk_Fun)(struct Animal *a_this);
    typedef struct Animal* (* Dtor_Fun)(struct Animal *a_this);
    Walk_Fun walk;
    Dtor_Fun dtor;
};
struct Animal
{
  struct Animal_vtable v_table;
  char *name;
};
struct Dog
{
   struct Animal_vtable v_table;
   char *name;
   char *type;
};
 void Animal_Walk(struct Animal *a_this)
 {
    printf("ANIMAL IS WALKING of name :%s",a_this->name);
 }
 struct Animal_Dtor(struct Animal *a_this)
 {
    printf("ANIMAL DTOR\n");
    return a_this;
 }

Animal* Animal_alloc()
{
    return (Animal *)malloc(sizeof(struct Animal));
}
Animal * new_Animal(struct Animal* a_this)
{
   a_this->v_table->walk=Animal_Walk;
   a_this->v_table->dtor=Animal_Dtor;
   a_this->name="ANanymous";
   return a_this;
}
void Animal_Free(Animal *a_this)
{
    free(a_this);
}
void Dog_Walk(struct Dog *a_this)
{
    printf("DOG %s is walking  of type %s",a_this->name,a_this->type);
}
Dog* Dog_Dtor(struct Dog *a_This){
    // Explicit call to parent destructor
    Animal_Dtor((Animal*)a_This);

    printf("dog::dtor\n");

    return a_This;
}
Dog * Dog_Alloc()
{
    return (Dog *)malloc(sizeof(struct Dog));
}
Dog * new_Dog(struct Animal* dog_this)
{
  Animal_New((Animal*)a_Dog);

    a_Dog->Type = "Dog type";
    a_Dog->v_table.Walk = (Animal_vtable::Walk_Fun) Dog_Walk;
    a_Dog->v_table.Dtor = (Animal_vtable::Dtor_Fun) Dog_Dtor;

    return a_Dog;
}
int main(int argc, char **argv){
    /*
      Base class:

        Animal *a_Animal = Animal_New(Animal_Alloc());
    */
    Animal *a_Animal = (Animal*)Dog_New(Dog_Alloc());

    a_Animal->v_table->Walk(a_Animal);

    Animal_Free(a_Animal);
    return EXIT_SUCCESS;
}