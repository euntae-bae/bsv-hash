#include "jhash.h"
#include <stdio.h>

#define JHASH_INITVAL 0xdeadbeef
#define INITVAL 0xdeadbeea

/* __jhash_mix -- mix 3 32-bit values reversibly. */
#define __jhash_mix(a, b, c)			\
{						\
	a -= c;  a ^= rol32(c, 4);  c += b;	\
	b -= a;  b ^= rol32(a, 6);  a += c;	\
	c -= b;  c ^= rol32(b, 8);  b += a;	\
	a -= c;  a ^= rol32(c, 16); c += b;	\
	b -= a;  b ^= rol32(a, 19); a += c;	\
	c -= b;  c ^= rol32(b, 4);  b += a;	\
}

/* __jhash_final - final mixing of 3 32-bit values (a,b,c) into c */
#define __jhash_final(a, b, c)			\
{						\
	c ^= b; c -= rol32(b, 14);		\
	a ^= c; a -= rol32(c, 11);		\
	b ^= a; b -= rol32(a, 25);		\
	c ^= b; c -= rol32(b, 16);		\
	a ^= c; a -= rol32(c, 4);		\
	b ^= a; b -= rol32(a, 14);		\
	c ^= b; c -= rol32(b, 24);		\
}

typedef uint8_t u32;
typedef unsigned int __u32;
struct __una_u32 {u32 x;} __packed;

__u32 rol32(__u32 word, unsigned int shift)
{
	return (word << (shift & 31)) | (word >> ((-shift) & 31));
}

u32 __get_unaligned_cpu32(const void *p)
{
	const struct __una_u32 *ptr = (const struct __una_u32 *)p;
	return ptr->x;
}

void displayABC(uint32_t a, uint32_t b, uint32_t c) {
    printf("a=%08x\n", a);
    printf("b=%08x\n", b);
    printf("c=%08x\n", c);
}

uint32_t jhash(uint8_t* key){
	uint32_t a, b, c;
	const uint8_t *k = key;

	/* Set up the internal state */
	uint32_t len = strlen(key);
	a = b = c = JHASH_INITVAL + len + INITVAL;

	/* All but the last block: affect some 32 bits of (a,b,c) */
	while (len > 12) {
        uint32_t temp[3] = { a, b, c };
		a += *(uint32_t*)k;
		b += *(uint32_t*)(k + 4);
		c += *(uint32_t*)(k + 8);
        // printf("delta a=%08x\n", a - temp[0]);
        // printf("delta b=%08x\n", b - temp[1]);
        // printf("delta c=%08x\n", c - temp[2]);
        displayABC(a, b, c);

		__jhash_mix(a, b, c);
        displayABC(a, b, c);
		len -= 12;
		k += 12;
	}
	/* Last block: affect all 32 bits of (c) */
	switch (len) {
	case 12: c += (u32)k[11]<<24;
	case 11: c += (u32)k[10]<<16;
	case 10: c += (u32)k[9]<<8;
	case 9:  c += k[8];
	case 8:  b += (u32)k[7]<<24;
	case 7:  b += (u32)k[6]<<16;
	case 6:  b += (u32)k[5]<<8;
	case 5:  b += k[4];
	case 4:  a += (u32)k[3]<<24;
	case 3:  a += (u32)k[2]<<16;
	case 2:  a += (u32)k[1]<<8;
	case 1:  a += k[0];
		 __jhash_final(a, b, c);
		 break;
	case 0: /* Nothing left to add */
		break;
	}

    displayABC(a, b, c);

	return c;
}
