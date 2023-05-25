/* AES-128 Software Implementation */
// Select Mode: CBC
// Key size in bits: 128
// Rounds: 10
// -> AES-192(192비트 암호키)는 12라운드, AES-256는 14개 라운드를 실행한다.

// Initialization Vector: encryptionIntVec
// Cipher Key: aesEncryptionKey

// CBC(Cipher Block Chaining)는 블록 암호화 operation mode 중 보안성이 제일 높은 암호화 방법으로 가장 널리 사용된다.
// 평문의 각 블록은 이전 암호문과 XOR을 통해 연산되고, 첫 번째 암호문에 대해서는 IV(Initialization Vector)가 암호문 대신 사용된다.
// IV는 제2의 키가 될 수 있다.
// - IV: A data block that some modes of operation require as an additional initial input.
// 암호문이 블록의 배수가 되기 때문에 복호화 후 평문을 얻기 위해 Padding을 해야 한다.
// 암호화가 병렬처리가 아닌 순차적으로 수행돼야 한다.
// 이전 블록의 암호문(결과값)이 다음 블록의 입력으로 사용되기 때문에 파이프라이닝 구성도 어려울 듯
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Bit left rotation for 8-bit data
#define ROL8(x, shamt) ((uint8_t) ((x) << (shamt)) | (x) >> (8 - (shamt)))
// Bit left rotation for 32-bit data
#define ROL32(x, shamt) ((uint32_t)((x) << (shamt)) | (x) >> (32 - (shamt)))
// Multiplication for mix columns
#define MUL2(x) (((x) & 0x80) ? (uint8_t)(((x) << 1) ^ 0x1b) : (uint8_t)((x) << 1))
#define MUL3(x) (MUL2(x) ^ (x))

#define BYTE_AT(x, pos) (((x) >> (pos) * 8) & 0xff)

static const uint8_t sbox[256] = {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Round Constant
// AES-128의 10개 라운드에 대해 g 함수에서 사용되는 라운드 상수
static const uint8_t rc[10] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b00011011,
    0b00110110
};

// 덧셈은 XOR로 처리한다.
// MSB가 1인 경우 곱셈(1시프트) 이후 0x1b와 XOR한다.
inline uint8_t mul2(uint8_t num) {
    return (num & 0x80) ? ((num << 1) ^ 0x1b) : (num << 1);
}

/* Global Variables */
/* State (4x4 matrix) */
// Total 16 bytes (128-bit)
// s00 s04 s08 s12
// s01 s05 s09 s13
// s02 s06 s10 s14
// s03 s07 s11 s15
// col0: { s[0][0], s[1][0], s[2][0], s[3][0] }
uint8_t state[4][4];

/* Cipher Key (128-bit) */
// k0, k1, ..., k15: 암호화 키를 1바이트씩 나눈 것
// key[0]: k00 k01 k02 k03
// key[1]: k04 k05 k06 k07
// key[2]: k08 k09 k10 k11
// key[3]: k12 k13 k14 k15
uint32_t key[4];

/* Initialization Vector (for CBC mode) */
//uint32_t iv[4];
uint8_t iv[16];

/* Functions */
inline uint32_t gfunc(uint32_t kword, int round);
inline void keyExpansion(int round);
inline void addRoundKey();
inline void subBytes();
inline void shiftRows();
inline void mulColumn(uint8_t *col, uint8_t *res);
inline void mixColumns();
void init(const char *ivec, const char *k);

void printState() {
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%02x ", state[i][j]);
        }
        printf("\n");
    }
}

// Key scheduling(key expansion): 각 라운드에 적용되는 key를 선택한다.
uint32_t gfunc(uint32_t kword, int round) {
    int i;
    uint32_t result = 0;
    // 1. 입력값(키)을 1바이트 단위로 left ratation 해준다.
    kword = ROL32(kword, 8);
    for (i = 0; i < 4; i++) {
        // 2. 1바이트 단위로 S-Box 연산을 해준다.
        result <<= 8;
        result |= sbox[BYTE_AT(kword, 3 - i)];
        // 3. 라운드 상수(rc)와 최상위 바이트를 XOR 해준다.
        if (i == 0)
            result ^= rc[round - 1]; // 배열 인덱스라 현재 라운드에서 1을 뺀 값을 넣어준다
    }
}

void keyExpansion(int round) {
    key[0] = key[0] ^ gfunc(key[3], round);
    key[1] = key[1] ^ key[0];
    key[2] = key[2] ^ key[1];
    key[3] = key[3] ^ key[2];
}

/* addRoundKey: state와 해당 라운드의 키를 XOR한다. */
void addRoundKey() {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            state[j][i] = state[j][i] ^ BYTE_AT(key[i], j);
        }
    }
}

/* subBytes: 입력된 바이트를 sbox에 있는 값으로 대체한다. */
void subBytes() {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            state[j][i] = sbox[state[j][i]];
    }
}

/* shiftRows: state의 각 행에 left rotate(바이트 단위)를 적용한다. */
void shiftRows() {
    uint8_t temp;
    temp = state[1][0];
    // row1
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
    // row2
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    // row3
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

/* mixColumns: state의 각 열에 행렬 곱셈을 적용한다. */
// 한 열에 행렬곱셈을 적용한다.
void mulColumn(uint8_t *col, uint8_t *res) {
    res[0] = MUL2(col[0]) ^ MUL3(col[1]) ^ col[2] ^ col[3];
    res[1] = col[0] ^ MUL2(col[1]) ^ MUL3(col[2]) ^ col[3];
    res[2] = col[0] ^ col[1] ^ MUL2(col[2]) ^ MUL3(col[3]);
    res[3] = MUL3(col[0]) ^ col[1] ^ col[2] ^ MUL2(col[3]);
}

// state의 col0에서 col3까지 반복적으로 행렬곱을 적용한다.
void mixColumns() {
    int i, j;
    uint8_t col[4], res[4];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            col[j] = state[j][i];
        mulColumn(col, res);
        for (j = 0; j < 4; j++)
            state[j][i] = res[j];
    }
}

// CBC mode encryption
void cipher(char *text, int len) {
    int idx = 0;
    int round = 0;
    int i, j;
    int blkCount = 0;
    uint8_t cipherText[16];

    while (idx < len) {
        // fetch: 16 바이트 평문을 state 행렬로 읽어들인다.
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (idx >= len)
                    state[j][i] = 0;
                else
                    state[j][i] = (uint8_t)text[idx];
                idx++;
            }
        }

        // CBC: 평문을 이전 128비트 블록의 암호문(blkCount >= 1) 또는 Initialization Vector(blkCount == 0)와 XOR한다
        if (blkCount == 0) { // XOR with IV
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    state[j][i] ^= iv[(i * 4) + j];
                }
            }
        }
        else { // XOR with previous ciphertext
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    state[j][i] ^= cipherText[(i * 4) + j];
                }
            }
        }

        /* Block cipher encryption */
        // pre-round transformation
        addRoundKey();
        round++;

        // 1-9 round
        for (; round < 10; round++) {
            keyExpansion(round);
            subBytes();
            shiftRows();
            addRoundKey();
        }

        // 10 round
        keyExpansion(round);
        subBytes();
        shiftRows();
        addRoundKey();

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                printf("%x", state[j][i]);
                cipherText[(i * 4) + j] = state[j][i];
            }
        }
        blkCount++;
        //init("encryptionIntVec", "aesEncryptionKey");
    }
    printf("\n");
}

void init(const char *ivec, const char *k) {
    int i, j;
    for (i = 0; i < 16; i++) {
        printf("%x", k[i]);
    }
    printf("\n");
    printf("Key: ");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            key[i] <<= 8;
            key[i] |= k[(i * 4) + j];
        }
        printf("%x ", key[i]);
    }
    printf("\n");
    memcpy(iv, ivec, 16);
    memset(state, 0, 16);
    printf("IV: ");
    for (i = 0; i < 16; i++) {
        printf("%x", iv[i]);
    }
    printf("\n");
}

int main(void) {
    char *text1 = "Hello DGIST Algorithm";
    // Initialization Vector: encryptionIntVec
    // Cipher Key: aesEncryptionKey
    init("encryptionIntVec", "aesEncryptionKey");
    cipher(text1, strlen(text1));

    uint32_t word1 = 0x11223344;
    int i;
    for (i = 0; i < 4; i++)
        printf("%02x ", BYTE_AT(key[0], i));
    return 0;
}
// 4d29041de9c537871ddebb0d5b0bcac06239fb6af0c224691efbc0c0f5fd83e1

/*
int main(void) {
    uint8_t data1 = 0x61;
    printf("%x -> %x\n", data1, ROL8(data1, 3));
    uint8_t col0[4] = { 0xd4, 0xbf, 0x5d, 0x30 };
    uint8_t col1[4] = { 0x48, 0x79, 0x43, 0x39 };
    uint8_t result0[4] = { 0, };
    uint8_t result1[4] = { 0, };

    int i;
    // result0[0] = MUL2(col0[0]) ^ MUL3(col0[1]) ^ col0[2] ^ col0[3];
    // result1[0] = MUL2(col1[0]) ^ MUL3(col1[1]) ^ col1[2] ^ col1[3];

    // printf("%02x\n", result0[0]);
    // printf("%02x\n", result1[0]);

    // printf("mul2(%02x): %02x\n", col0[0], MUL2(col0[0]));
    // printf("mul3(%02x): %02x\n", col0[1], MUL3(col0[1]));

    mulColumn(col0, result0);
    mulColumn(col1, result1);
    for (i = 0; i < 4; i++) {
        printf("%02x ", result0[i]);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf("%02x ", result1[i]);
    }
    printf("\n");

    return 0;
}
*/

// references
// https://m.blog.naver.com/errorsoft666/221535323710
// https://hipolarbear.tistory.com/36
// https://www.javainuse.com/aesgenerator
// https://raw.githubusercontent.com/michaelehab/AES-Verilog/main/NIST.FIPS.197.pdf
// https://blog.naver.com/PostView.naver?blogId=wnrjsxo&logNo=221711255389
