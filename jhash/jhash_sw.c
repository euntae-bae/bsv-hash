#include <stdio.h>
#include <string.h>

unsigned int jhash(void *key, int len) {
	unsigned char *p = (unsigned char*)key;
	unsigned int h = 8388617;   // 초기값

	for (int i = 0; i < len; i++)
	{
		h = ( (h << 1 | h >> 30) & 0x7fffffff ) ^ p[i];
        printf("[%02d] h=%d, p[%d]=%d\n", i, h, i, p[i]);
	}
	return h;
}

int main(int argc, char const *argv[])
{
	int arr[] = { 12, 0, 23, 43, 230, 2 };
    char msg[] = "Hello World";

	printf("%#x\n", jhash(arr, 3));
    printf("%#x\n", jhash(msg, strlen(msg)));

	return 0;
}