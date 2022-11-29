#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

/* for litte-endian CPUs*/
// key가 입력이다. hash 값과 구분할 것
static inline uint32_t murmur_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;            // multiply by c1
    k = (k << 15) | (k >> 17);  // ROL15
    k *= 0x1b873593;            // multiply by c2
    return k;
}
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
	uint32_t h = seed;  // 해시값은 맨 처음에 seed로 초기화
    uint32_t k;
    /* Read in groups of 4. */
    // key(메시지)를 4바이트(32비트) 단위로 읽는다
    for (size_t i = len >> 2; i; i--) {
        // Here is a source of differing results across endiannesses.
        // A swap here has no effects on hash properties though.
        memcpy(&k, key, sizeof(uint32_t));
            printf("%02x %02x %02x %02x\t\t--> %08x\n", *key, *(key + 1), *(key + 2), *(key + 3), k);
        key += sizeof(uint32_t);    // 포인터가 다음 4바이트를 가리키도록 더한다 (key는 바이트 배열이므로 4바이트인 4를 더해준다)
        h ^= murmur_32_scramble(k); // 해시값과 scramble된 key 값을 XOR
            printf("scramble(%08x)\t--> %08x\n", k, murmur_32_scramble(k));
        h = (h << 13) | (h >> 19);  // ROL13
        h = h * 5 + 0xe6546b64;     // m(=5)배 하고, n(=0xe6546b64)와 더해준다.
            printf("h=%08x\n", h);
    }   // 다음에 읽은 4바이트 메시지에 대해 반복한다

    /* Read the rest. */
    // 4바이트로 나누어 떨어지지 않는 메시지 처리
    k = 0;
    for (size_t i = len & 3; i; i--) {
        k <<= 8;
        k |= key[i - 1];    // 리틀엔디안이므로 뒤에서부터 읽어온다.
    }
    printf("k=%08x\n", k);
    // A swap is *not* necessary here because the preceding loop already
    // places the low bytes in the low places according to whatever endianness
    // we use. Swaps only apply when the memory is copied in a chunk.
    h ^= murmur_32_scramble(k);
    // 나머지 바이트들은 ROL13, (hash x m) + n 해주지 않음

    /* Finalize. */
    printf("finalize =======\n");
	h ^= len;
    printf("h=%08x\n", h);
	h ^= h >> 16;
    printf("h=%08x\n", h);
	h *= 0x85ebca6b;
    printf("h=%08x\n", h);
	h ^= h >> 13;
    printf("h=%08x\n", h);
	h *= 0xc2b2ae35;
    printf("h=%08x\n", h);
	h ^= h >> 16;
    printf("h=%08x\n", h);
    printf("================\n");
	return h;
}

void displayHexMsg(const uint8_t *msg, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
        printf("%02x ", msg[i]);
    printf("\n");
}

int main(void) {
    srand(time(NULL));
    //uint32_t s = rand();
    uint32_t s = 1429907438;
    uint8_t key[] = "Hello World";
    size_t len = strlen(key);
    printf("msg: "); displayHexMsg(key, len);
    printf("seed: %u\n", s);
    printf("len: %lu\n\n", len);
    clock_t startTime = clock();
    printf("\n%s --> %x\n", key, murmur3_32(key, len, s));
    clock_t endTime = clock();
    printf("elapsed time (ms): %lf\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}