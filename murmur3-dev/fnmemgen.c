// fn_mem_read generator
// programmed by euntae-bae
//function Bit#(32) fn_mem_read(Bit#(64) addr);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <message_in_file>\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(argv[1], "rt");
    if (!fp) {
        printf("E: failed to open file \"%s\"\n", argv[1]);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    uint64_t msglen = ftell(fp) - 1;
    rewind(fp);

    char *msg = (char*)malloc(msglen + 1);
    memset(msg, 0, msglen + 1);
    size_t nread = fread(msg, 1, msglen, fp);

    //printf("nread: %lu, msglen: %lu\n", nread, msglen);
    //printf("msg: %s\n", msg);

    char *ptr = msg;
    int rembyte = msglen;
    int addr = 0;
    int i;

    printf("function Bit#(32) fn_mem_read(Bit#(64) addr);\n");
    printf("\treturn case (addr)\n");

    while (rembyte > 0) {
        printf("\t\t'h%016x: return 'h", addr);
        for (i = 0; i < 4; i++) {
            if (rembyte > 0)
                printf("%02x", *ptr++);
            else
                printf("%02x", 0);
            rembyte--;
        }
        printf(";\n");
        addr += 4;
    }
    printf("\t\tdefault: return 0;\n");
    printf("\tendcase;\n");
    printf("endfunction\n");
    free(msg);

    return 0;
}