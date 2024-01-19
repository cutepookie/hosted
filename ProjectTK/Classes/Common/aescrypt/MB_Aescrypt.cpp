//
//  MB_Aescypt.cpp
//  encrypt_file
//
//  Created by wenyong on 14-8-30.
//  Copyright (c) 2014年 wenyong. All rights reserved.
//


#include "MB_Aescrypt.h"
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

#define FileCodeKey 20
#define FileCodePrivateKey 14
#define HashKey1    0xf0
#define HashKey2    0x0f

static std::vector<std::string>  file_container;

MB_Aescypt::~MB_Aescypt()
{
    file_container.clear();
}
int MB_Aescypt::encrypt_stream(FILE *infp, FILE *outfp){
    
    while (!feof(infp))
    {
        char c = fgetc(infp);
        c =  c^FileCodeKey^FileCodePrivateKey;
        char change = ((c << 4)&HashKey1) + ((c>>4)&HashKey2);
        change = change^FileCodePrivateKey;
        fputc(change, outfp);
    }
    fclose(infp);
    fclose(outfp);
    return 1;
}
unsigned char * MB_Aescypt::decrypt_stream(FILE *infp,unsigned long *length){
    
    fseek(infp, 0, SEEK_END);
    *length  = ftell(infp);
    unsigned char *outbuffer = new unsigned char[*length];
    int index = 0;
    fseek(infp,0,SEEK_SET);
    while (!feof(infp))
    {
        char c = fgetc(infp);
        c = c ^ FileCodePrivateKey;
        char change = ((c << 4)&HashKey1) + ((c>>4)&HashKey2);
        change = change^FileCodeKey^FileCodePrivateKey;
        outbuffer[index] = change;
        if( change == EOF)
        {
            outbuffer[index] = '\0';
            index++;
            break;
        }
        index++;
    }
    fclose(infp);
    return outbuffer;
}
unsigned char * MB_Aescypt::decrypt_stream(char *buf,unsigned long *length){
    
    unsigned char *outbuffer = new unsigned char[*length];
    int index = 0;
    while (index < *length) {
        
        char c = buf[index];
        c = c ^ FileCodePrivateKey;
        char change = ((c << 4)&HashKey1) + ((c>>4)&HashKey2);
        change = change^FileCodeKey^FileCodePrivateKey;
        outbuffer[index] = change;
        if( change == EOF){
            
            outbuffer[index] = '\0';
            index++;
            break;
        }
        index++;
        
        
    }
    return outbuffer;
}
int MB_Aescypt::encrypt_stream(const char *infile, const char *outfile){
    
    FILE * fp = fopen(infile, "r");
    
    if(fp){
        
        FILE * op = fopen(outfile, "w");
        if(op){
            
            encrypt_stream(fp, op);
            return 1;
            
        }else {
            
            fclose(op);
            fclose(fp);
            return -1;
        }
    }else{
        
        fclose(fp);
        return -1;
    }
    return  -1;
    
}
int MB_Aescypt::decrypt_stream(const char *infile, const char *outfile){
    
    FILE * fp = fopen(infile, "r");
    
    if(fp){
        
        FILE * op = fopen(outfile, "w");
        if(op){
            
            decrypt_stream(fp, op);
            return 1;
            
        }else {
            
            fclose(op);
            fclose(fp);
            return -1;
        }
    }else{
        
        fclose(fp);
        return -1;
    }
    return  -1;
}
int MB_Aescypt::decrypt_stream(FILE *infp,FILE *outfp){
    
    while (!feof(infp)) {
        
        char c = fgetc(infp);
        c = c ^ FileCodePrivateKey;
        char change = ((c << 4)&HashKey1) + ((c>>4)&HashKey2);
        change = change^FileCodeKey^FileCodePrivateKey;
        if( change == EOF){
            
            break;
        }
        fputc(change, outfp);
        
    }
    fclose(outfp);
    fclose(infp);
    return 1;
}

int MB_Aescypt::encrypt_xmlstream2file(char* pdata,int size,const char* outfile)
{
    if (pdata == NULL || size ==0 || outfile==NULL)
    {
        return -1;
    }
    
    int sz = 0;
    char change = 0;
    char c = 0;
    
    FILE* outfp = fopen(outfile,"w");
    if(outfp)
    {
        while (pdata[sz]!='\0')
        {
            c = pdata[sz];
            c =  c^FileCodeKey^FileCodePrivateKey;
            change = ((c << 4)&HashKey1) + ((c>>4)&HashKey2);
            change = change ^ FileCodePrivateKey;
            fputc(change, outfp);
            sz++;
        }
        fclose(outfp);
        return 1;
    }
    return -1;
}

bool MB_Aescypt::encrypt_file(const char* pSrc, const char* pDest)
{
    if(encrypt_stream(pSrc,pDest)==-1)
    {
        std::cout<<"fail to encrypt:"<<pSrc<<std::endl;
        return false;
    }
    
    std::cout<<pSrc<<"-->>"<<pDest<<std::endl;
    return true;
}
bool MB_Aescypt::decrypt_file(const char* pSrc, const char* pDest)
{
    if(decrypt_stream(pSrc,pDest)==-1)
    {
        std::cout<<"fail to decrypt:"<<pSrc<<std::endl;
        return false;
    }
    
    std::cout<<pSrc<<"-->>"<<pDest<<std::endl;
    return true;
}
