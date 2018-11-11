//OOT第2次作业-18101223769-黎豪
#include "fighter.h"

int main(void)
{
    fighter * objs[2];
    objs[0] = new fighter("Harry");
    Warrior Stallone("Stallone", objs[0]);
    objs[1] = &Stallone;
    printf("\n== Test the class famliy ==\n");
    for(int i=0; i<2; i++)
    {
        objs[i] -> outTitle();
        printf("---- %d ----\n", i+1);
        objs[i] -> hello();
    }
    delete objs[0];
    return 0;
}
