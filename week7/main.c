#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// int main()
// {
//     int arr_index = 1;
//     int arr[6] = {0, 0, 0, 0, 0};
//     while (arr_index != 0)
//     {
//         printf("enter 5 numberS (0 = stoppen):   ");
//         scanf("%d", &arr_index);
//         printf("\n");
//         arr[0] = arr_index;
//         if (arr_index != 0)
//         {
//             for (int i = 0; i < 5; i++)
//             {
//                 arr[5 - i] = arr[4 - i];
//             }  
//         }

//     }
//         for (int i = 1; i < 6; i++)
//         {
//             printf("place %d has value: %d\n", i, arr[6 - i]);
//         }
    

//     return 0;
// }

//===========================================================================================================

char *create_concatenated_cstring(char *source1, char *source2); 
void destroy_cstring(char **gluedstring);



int strlen(char *s) 
{ 
    int n = 0; 
    for (n = 0; *s != '\0'; s++, n++); 
    return n; 
}
int main() 
{ 
    char *string1 = "Common sense is genius "; 
    char *string2 = "dressed in its working clothes."; 
    char *together = create_concatenated_cstring(string1, string2); 
    printf("Aan elkaar geplakt vormen de strings de volgende " \ 
    "quote:\n\n\"%s\"\n\n", together); 
    destroy_cstring(&together); 
    if (NULL == together)
    printf("De string was inderdaad vernietigd!\n");
    return 0;
}

char *create_concatenated_cstring(char *source1, char *source2){

    int length = strlen(source1) + strlen(source2);
    char *new_arr = (char *)malloc((length+1)*sizeof(char));
    if (new_arr == NULL){
       puts("Memory allocation error.");
       return 1;
   }


}

void destroy_cstring(char **gluedstring){



}