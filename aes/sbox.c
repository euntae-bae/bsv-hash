// #include <stdio.h>
// #include <stdint.h>

// // <<< is a left bitwise circular shift
// #define ROTL8(x, shift) \
//     ((uint8_t)((x) << (shift)) | ((x) >> (8 - (shift))))

// #define getBit(x, loc) (((x) >> (loc)) & 1)

// uint8_t calc_sbox_forward(uint8_t b) {
//     uint8_t matTrans[64] = {
//         1, 0, 0, 0, 1, 1, 1, 1,
//         1, 1, 0, 0, 0, 1, 1, 1,
//         1, 1, 1, 0, 0, 0, 1, 1,
//         1, 1, 1, 1, 0, 0, 0, 1,
//         1, 1, 1, 1, 1, 0, 0, 0,
//         0, 1, 1, 1, 1, 1, 0, 0,
//         0, 0, 1, 1, 1, 1, 1, 0,
//         0, 0, 0, 1, 1, 1, 1, 1
//     };

//     uint8_t s[8] = { 0, };
//     uint8_t bin[8] = { 0, };
//     uint8_t c[8] = { 1, 1, 0, 0, 0, 1, 1, 0 };
//     uint8_t sout = 0;
//     int i, j;
//     //uint8_t carry = 0;

//     //printf("%03u: ", b);
//     for (i = 0; i < 8; i++) {
//         bin[7 - i] = getBit(b, (uint8_t)(7 - i));
//         //printf("%u ", bin[7 - i]);
//     }
//     //printf("\n");

//     for (i = 0; i < 8; i++) {
//         for (j = 0; j < 8; j++) {
//             //uint8_t sbit = (matTrans[i * 8 + j] * bin[j]) ? 1 : 0;
//             //s[i] ^= sbit;
//             s[i] ^= matTrans[i * 8 + j] * bin[j];
//             s[i] &= 1;
//         }
//         //carry = s[i] & c[i];
//         s[i] ^= c[i];
//     }

//     for (i = 7; i >= 0; i--) {
//         sout |= s[i];
//         sout <<= 1;
//     }
//     return sout;
// }


// // uint8_t calc_sbox_forward(uint8_t b) {
// //     uint8_t s = b ^ ROTL8(b, 1) ^  ROTL8(b, 2) ^  ROTL8(b, 3) ^  ROTL8(b, 4) ^ 0x63;
// //     return s;
// // }

// void initialize_aes_sbox(uint8_t *sbox) {
//     uint8_t i, j;
//     for (i = 0; i < 16; i++) {
//         for (j = 0; j < 16; j++) {
//             uint8_t idx = i * 16 + j;
//             sbox[idx] = calc_sbox_forward(idx);
//             printf("%02x ", sbox[idx]);
//         }
//         printf("\n");
//     }

//     printf("sbox[0x11]=%02x\n", sbox[0x11]);
// }

// int main(void) {
//     uint8_t sbox[256] = { 0, };
//     initialize_aes_sbox(sbox);

//     return 0;
// }

#include <stdio.h>
#include <stdint.h>

#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))

void initialize_aes_sbox(uint8_t *sbox) {
	uint8_t p = 1, q = 1;
	
	/* loop invariant: p * q == 1 in the Galois field */
	do {
		/* multiply p by 3 */
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

		/* divide q by 3 (equals multiplication by 0xf6) */
		q ^= q << 1;
		q ^= q << 2;
		q ^= q << 4;
		q ^= q & 0x80 ? 0x09 : 0;

		/* compute the affine transformation */
		uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

		sbox[p] = xformed ^ 0x63;
	} while (p != 1);

	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
}

int main(void) {
    uint8_t sbox[256];
    int i, j;
    initialize_aes_sbox(sbox);

    for (i = 0; i <= 0x0f; i++) {
        for (j = 0; j <= 0x0f; j++) {
            int idx = (i << 8) | j;
            printf("%02x ", sbox[idx]);
        }
        printf("\n");
    }
    return 0;
}

/*
function generate(p){
    //let irreducible_poly = "1 + x + x**3 + x**4 + x**8";
    try{
        p = parseInt(eval(irreducible_poly.replace(/x/g, '10')), 2);
    } catch(err){
        console.log('Irreducible Polynomial invalid');
        return;
    }

    // Calculate Multiplicative Inverse
    let t = new Uint32Array(256);
    for (let i = 0, x = 1; i < 256; i ++) {
        t[i] = x;
        x ^= (x << 1) ^ ((x >>> 7) * p);
    }

    // Generate Sbox with Affine transformation
    let Sbox = new Uint32Array(256);
    Sbox[0] = 0x63;
    for (let i = 0; i < 255; i ++) {
        let x = t[255 - i];
        x |= x << 8;
        x ^= (x >> 4) ^ (x >> 5) ^ (x >> 6) ^ (x >> 7);
        Sbox[t[i]] = (x ^ 0x63) & 0xFF;
    }

    return Sbox;
}
*/