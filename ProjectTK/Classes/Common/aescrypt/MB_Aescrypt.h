//
//  MB_Aescypt.h
//  encrypt_file
//
//  Created by wenyong on 14-8-30.
//  Copyright (c) 2014年 wenyong. All rights reserved.
//

#ifndef __encrypt_file__MB_Aescypt__
#define __encrypt_file__MB_Aescypt__

#include <string>
#include <vector>
#include <stdio.h>

class MB_Aescypt
{
public:
    ~MB_Aescypt();
    bool encrypt_file(const char* pSrc, const char* pDest);
    bool decrypt_file(const char* pSrc, const char* pDest);
    
    static int encrypt_xmlstream2file(char* pdata,int size,const char* outfp);
    static int encrypt_stream(const char *infile, const char *outfile);
    static unsigned char * decrypt_stream(FILE *infp,unsigned long *length);

    static int encrypt_stream(FILE *infp, FILE *outfp);
    static unsigned char * decrypt_stream(char *buf,unsigned long *length);
    static int decrypt_stream(const char *infile, const char *outfile);
    static int decrypt_stream(FILE *infp,FILE *outfp);
};

#endif /* defined(__encrypt_file__MB_Aescypt__) */
