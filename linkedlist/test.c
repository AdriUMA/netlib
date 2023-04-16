#include "addressList.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char const *argv[]){
    AddressList al;

    createList(&al);
    deleteList(&al);

    removeAddress(&al, "dawd");

    createList(&al);
    insertAddress(&al,"uno");
    insertAddress(&al,"dos");
    insertAddress(&al,"tres");

    printf("Valor: %s \n", al->address);
    printf("Valor: %s \n", al->next->address);
    printf("Valor: %s \n", al->next->next->address);

    removeAddress(&al, "uno");

    printf("Valor: %s \n", al->address);
    printf("Valor: %s \n", al->next->address);
    printf("Valor: %s \n", al->next->next->address);
}
