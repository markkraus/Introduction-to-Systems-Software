#include <stdio.h>

// Includes the header file 'size.h'
#include "size.h"

int main(void){

    

    // Print the sizes of structs
    printf("The size of struct A is %lu\n", sizeof(A));
    printf("The size of struct B is %lu\n", sizeof(B));
    printf("The size of struct C is %lu\n", sizeof(C));

    return 0;
}

// printf("The size of struct A is %lu\n", sizeof(object1.int_byte_sizeA) + sizeof(object1.long_byte_sizeA) + sizeof(object1.char_byte_sizeA));
// printf("The size of struct B is %lu\n", sizeof(object2.long_byte_sizeB) + sizeof(object2.int_byte_sizeB) + sizeof(object2.char_byte_sizeB));
// printf("The size of struct C is %lu\n", sizeof(object3.long_byte_sizeC) + sizeof(object3.int_byte_sizeC) + sizeof(object3.charC_byte_sizeA) + sizeof(object3.charC_byte_sizeB) + sizeof(object3.charC_byte_sizeC) + sizeof(object3.charC_byte_sizeD));
