#include "prx.h"
#include "prxtype2.h"
#include "prxtype8.h"
#include "crypt.h"

#include <stddef.h>
#include <string.h>

const uint8_t g_0x0E000000_seed[0x90] = { 0xDE, 0x57, 0xB7, 0x77, 0x17, 0xDD, 0x62, 0xEE, 0x7B, 0x78, 0x03, 0x5D, 0x44, 0x86, 0xCA, 0x59, 0x20, 0x8D, 0xF6, 0x93, 0x28, 0x93, 0x81, 0x21, 0x71, 0x4E, 0xA7, 0x86, 0xCA, 0x82, 0x24, 0x1B, 0x58, 0xAE, 0x74, 0x5F, 0x6C, 0x01, 0x8D, 0x56, 0x32, 0x88, 0x4D, 0x9A, 0x72, 0x43, 0xA2, 0x2E, 0x84, 0xF4, 0x0C, 0x82, 0xB9, 0x06, 0xFC, 0xFC, 0x6A, 0xFB, 0x5B, 0x8A, 0xD7, 0x9C, 0x9F, 0xBF, 0x01, 0x0D, 0x85, 0x15, 0xBA, 0x5F, 0xED, 0x39, 0x93, 0x83, 0xC3, 0x4C, 0xAF, 0xDE, 0x3A, 0xED, 0xBF, 0x68, 0xA7, 0x1A, 0x77, 0x8A, 0xBD, 0x89, 0x65, 0x41, 0x56, 0x46, 0xD9, 0xDB, 0x33, 0x73, 0x81, 0x6C, 0xE8, 0x62, 0x96, 0x9B, 0x29, 0x03, 0x5A, 0xAE, 0xAF, 0x73, 0x20, 0x53, 0xA0, 0x40, 0xE8, 0x4B, 0x66, 0x10, 0x99, 0x6A, 0xB7, 0xE5, 0x70, 0xDD, 0xE0, 0x29, 0x28, 0x24, 0x60, 0xEA, 0x30, 0xAE, 0x42, 0x20, 0x32, 0x8D, 0x6F, 0x94, 0x71, 0x5F, 0x9E, 0xA2, 0xD5, 0x7F, 0x0C, 0x7C };
const uint8_t g_0xD82310F0_seed[0x10] = { 0x9D, 0x09, 0xFD, 0x20, 0xF3, 0x8F, 0x10, 0x69, 0x0D, 0xB2, 0x6F, 0x00, 0xCC, 0xC5, 0x51, 0x2E };
const uint8_t g_0xD8231EF0_seed[0x10] = { 0x4F, 0x44, 0x5C, 0x62, 0xB3, 0x53, 0xC4, 0x30, 0xFC, 0x3A, 0xA4, 0x5B, 0xEC, 0xFE, 0x51, 0xEA };
const uint8_t g_0xD82328F0_seed[0x10] = { 0x5D, 0xAA, 0x72, 0xF2, 0x26, 0x60, 0x4D, 0x1C, 0xE7, 0x2D, 0xC8, 0xA3, 0x2F, 0x79, 0xC5, 0x54 };

const PrxMetaType g_prx_metatypes[] = {
    { 
        .tag = 0x0E000000, // PSAR
        .keyid = 0x51,
        .type = PRX_TYPE_8,
        .seed = g_0x0E000000_seed
    },
    { 
        .tag = 0xD82310F0, // PSAR 02G
        .keyid = 0x51,
        .type = PRX_TYPE_2,
        .seed = g_0xD82310F0_seed,
    },
    { 
        .tag = 0xD8231EF0, // PSAR 03/04/07/09G
        .keyid = 0x51,
        .type = PRX_TYPE_2,
        .seed = g_0xD8231EF0_seed,
    },
    { 
        .tag = 0xD82328F0, // PSAR 05G
        .keyid = 0x51,
        .type = PRX_TYPE_2,
        .seed = g_0xD82328F0_seed,
    }
};

#define NUM_PRX_METATYPES   (sizeof(g_prx_metatypes)/sizeof(g_prx_metatypes[0]))

PrxDecryptResult prx_decrypt(void *data, size_t *out_length)
{
    PSP_Header header;
    memcpy(&header, data, sizeof(header));

    *out_length = header.comp_size;

    for (size_t i = 0; i < NUM_PRX_METATYPES; ++i) {
        if (header.tag == g_prx_metatypes[i].tag) {
            switch (g_prx_metatypes[i].type) {
                case PRX_TYPE_2:
                    return prx2_decrypt((unsigned char *)data, &g_prx_metatypes[i]);
                case PRX_TYPE_8:
                    return prx8_decrypt((unsigned char *)data, &g_prx_metatypes[i]);
            }
        }
    }

    return PRX_DECRYPT_ERR_UNSUPPORTED;
}