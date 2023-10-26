#include <stdio.h>
#include <stdlib.h> // for malloc()


typedef struct _listitem
{
    void *data;
    struct _listitem *next;
} Listitem;




typedef struct
{
    Listitem *head, *tail;


} List;


void list_init(List *theList);
void list_add_to_tail(void *data, List *theList);
void list_print(List *theList);
void list_free(List *theList);



int main()
{
    char *a = "Rome", *b = "Seattle", *c = "Toronto", *d = "Zurich", *s = "hi";
    // Adres a staat op STACK en wijst naar ‘R’ in read-only! Opvragen met a[0], a[1], etc. !
    // Let op: a dus 4 bytes breed (want adres), NIET strlen(“Rome”) breed (5 bytes)!!
    // Vraag: Hoe forceer je gaten in de volgordelijkheid van de listitems als alles nu
    // evengoed achter elkaar wordt gezet in het geheugen ??
    
    List myList;
    list_init(&myList);
    list_add_to_tail((void *)a, &myList);
    list_add_to_tail((void *)b, &myList);
    list_add_to_tail((void *)c, &myList);
    list_add_to_tail((void *)d, &myList);
    list_add_to_tail((void *)s, &myList);
    list_print(&myList);
    list_free(&myList);
    return 0;
}


void list_init(List *theList)
{
    theList->head = NULL; // points to nothing
    theList->tail = NULL; // points to nothing
}


void list_add_to_tail(void *data, List *theList)
{
    // 1. Maak een nieuwe Listitem aan met malloc()
    Listitem *newtail = (Listitem *)malloc(sizeof(Listitem));
    // 2. Zet ‘data’ in de Listitem en verwijs met next naar NULL (wordt immers de nwe tail)
    newtail->data = data;
    newtail->next = NULL;
    // 3. Als de lijst leeg is:
    if (theList->head == NULL && theList->tail == NULL)
    {
        theList->head = newtail;    // > Laat zowel de head- als de tail-pointer naar het nieuwe item wijzen
        theList->tail = newtail;

    }else{// Als de lijst niet leeg is:

        theList->tail->next = newtail;    // > De ‘next’-pointer v.h. huidige laatste item moet naar het nieuwe laatste
        theList->tail = newtail; // item gaan wijzen
                                 // > De tail-pointer moet vervolgens ook naar het nieuwe laatste item gaan wijzen
}
    }
    


void list_print(List *theList)
{
    // Als de lijst wel leeg is:
    if (theList->head == NULL && theList->tail == NULL){


        printf("lijst is leeg") ;   
        return;    // > Zolang de langsloop-variabele niet NULL is


    }
    
    
    // > Laat een ‘langsloop’-variabele wijzen naar de head van de list
    Listitem *i = theList->head;
    // - Print het huidige data-item
    // - Laat de langsloop-variabele wijzen naar het item waar de ‘next’-pointer
    while (i != NULL)

    {
        printf("%s ", (char *)i->data);
        i = i->next;

    }
    
    // van het huidige item naar wijst
    // Als de lijst wel leeg is:
    // > Print “de lijst is leeg!”
}



void list_free(List *theList)
{
    Listitem *current, *next;
    current = theList->head;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    list_init(theList); // list is empty, so head and tail should point to NULL
}
