#include <stdio.h>
#include <string.h>
#include "jhash.h"

// Hello HELLO World
// 48 65 6C 6C 6F 20 48 45 4C 4C 4F 20 57 6F 72 6C 64
int main(void)
{
    uint8_t key[] = "Hello HELLO World";
    uint32_t hash = 0;

    hash = jhash(key);
    printf("hash: %08x\n", hash); // hash: 769d8e63

    return 0;
}
