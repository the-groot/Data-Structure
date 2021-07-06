
#include <stdio.h>
#include <stdlib.h>

/* book style */

/*
typedef struct listNode* listPointer;
typedef struct {
    char data[4];
    listPointer link;
} listNode;

*/

typedef struct {
    char data[4];
    struct listNode *link;
} listNode;



void callbyvalue(listNode *first);
void callbyreference(listNode **first);

/* book style */

// void callbyvalue(listPointer first);
// void callbyreference(listPointer *first);


void main()
{
    
    listNode *first = NULL;

    printf("[MAIN]\n");
    printf("        addr(first) = %p, val(first) = %p\n\n", &first, first);

    callbyvalue(first);

    printf("[MAIN]\n");
    printf("        addr(first) = %p, val(first) = %p\n\n", &first, first);
    

    callbyreference(&first);

    printf("[MAIN]\n");
    printf("        addr(first) = %p, val(first) = %p\n\n", &first, first);

    free(first);
}

void callbyvalue(listNode *first)
{
    first++;
    printf("[@CBV\n");
    printf("        sizeof(*first) = %ld\n", sizeof(*first));
    printf("        addr(first) = %p, val(first) = %p\n\n", &first, first);


}

void callbyreference(listNode **first)
{
    listNode *temp = (listNode*)malloc(sizeof(listNode));
    *first = temp;
    printf("[@CBR]\n");
    printf("        addr(first) \t= %p\n", &first);
    printf("        val(first) \t= %p\n", first);
    printf("        val(*first) \t= %p\n", *first);
    printf("        val(temp) \t= %p\n", temp);
}
