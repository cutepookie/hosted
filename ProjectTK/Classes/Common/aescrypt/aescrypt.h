/*
 * aescrypt.h
 *
 * Copyright (C) 2007, 2008, 2009
 *
 * This software is licensed as "freeware."  Permission to distribute
 * this software in source and binary forms is hereby granted without a
 * fee.  THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * THE AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DAMAGES RESULTING FROM
 * THE USE OF THIS SOFTWARE, EITHER DIRECTLY OR INDIRECTLY, INCLUDING,
 * BUT NOT LIMITED TO, LOSS OF DATA OR DATA BEING RENDERED INACCURATE.
 *
 */

#ifndef __AESCRYPT_H__
#define __AESCRYPT_H__

#include "platform/CCPlatformMacros.h"
#include "aes.h"
#include "sha256.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char aes[3];
    unsigned char version;
    unsigned char last_block_size;
} aescrypt_hdr;

typedef unsigned char sha256_t[32];

static unsigned char aeskey[258] = "N8cuLeZy7GHJ98B3IiNcRTakXm0scThv6ZT90JeL27Hu377oZKeGlbQ2Bwgsn2vbFDdsP2B60z38jSfj9yQwEje4Uhs5nehmEx59CIAjqRoCjUW1L2FAcsaifWPks7KDzl51eduqOIdM0lKzpUbyEo6q0lhMwA6yt7cOyR6O567zi4afoVgSSXAl1gbErvTaruguonipojiezheduandaimajiuzhengmingzhegeyouxiyijinghenhuolehaha";

CC_DLL int encrypt_stream(FILE *infp, FILE *outfp, unsigned char* passwd, int passlen);
CC_DLL int decrypt_stream(FILE *infp, FILE *outfp, unsigned char* passwd, int passlen);
CC_DLL char * decrypt_streamTobuffer(FILE *infp, unsigned char* passwd, int passlen);
#ifdef __cplusplus
}
#endif

#endif // __AESCRYPT_H__
