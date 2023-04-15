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

    printf("Valor: %s \n", al->address);

    removeAddress(&al, "uno");

    printf("Valor: %s \n", al->address);
}
