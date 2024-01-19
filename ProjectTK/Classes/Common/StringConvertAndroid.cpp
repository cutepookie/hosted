////
////  StringConvert.cpp
////  ProjectTK
////
////  Created by lic  on 13-5-20.
////
////
//
//#include "StringConvert.h"
//#include "cocos2d.h"
//#include "iconv.h"
//std::wstring StringConvert::s2ws(std::string s)
//{
//    int maxLength = s.length();
//    wchar_t wStr[maxLength];
//    wmemset(wStr, 0, maxLength);
//    int charLength = 0;
//    int i = 0,j = 0;
//    uint8_t* srcStr = (uint8_t*)s.c_str();
//    while (maxLength > 0)
//    {
//        charLength = UTF8_To_UCS4(&srcStr[j], &wStr[i++]);
//        j = j+charLength;
//        if (i >= maxLength || j > maxLength) {
//            break;
//        }
//        maxLength = maxLength - charLength;
//    }
//    std::wstring val(wStr);
//    return val;
//}
//
//std::string  StringConvert::ws2s(std::wstring wstr)
//{
//    std::string s = "";
//    for (int i = 0; i < wstr.length(); ++i)
//    {
//        char temp[8];
//        int  len;
//        memset(temp, 0, sizeof(temp));
//        ConvertUTF32ToUTF8(wstr[i], temp, &len);
//        s += temp;
//    }
//    return s;
//}
//
//
//void StringConvert::ConvertUTF32ToUTF8(unsigned long input, char* output, int* length )
//{
//    const unsigned long BYTE_MASK = 0xBF;
//    const unsigned long BYTE_MARK = 0x80;
//    const unsigned long FIRST_BYTE_MARK[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
//    
//    if (input < 0x80) {
//        *length = 1;
//    }
//    else if ( input < 0x800 ) {
//        *length = 2;
//    }
//    else if ( input < 0x10000 ) {
//        *length = 3;
//    }
//    else if ( input < 0x200000 ) {
//        *length = 4;
//    }
//    else {
//        *length = 0;    // This code won't covert this correctly anyway.
//        return;
//    }
//    
//    output += *length;
//    
//    // Scary scary fall throughs.
//    switch (*length) {
//        case 4:
//            --output;
//            *output = (char)((input | BYTE_MARK) & BYTE_MASK);
//            input >>= 6;
//        case 3:
//            --output;
//            *output = (char)((input | BYTE_MARK) & BYTE_MASK);
//            input >>= 6;
//        case 2:
//            --output;
//            *output = (char)((input | BYTE_MARK) & BYTE_MASK);
//            input >>= 6;
//        case 1:
//            --output;
//            *output = (char)(input | FIRST_BYTE_MARK[*length]);
//        default:
//            break;
//    }
//}
//
//
//// 轉換UTF8编碼到UCS4编碼
//int StringConvert::UTF8_To_UCS4( uint8_t* pbUTF8, wchar_t* dwUCS4 )
//{
//    int     i, iLen;
//    uint8_t    b;
//    
//    if( pbUTF8 == NULL )
//    {   // 參數錯誤
//        return 0;
//    }
//    
//    b = *pbUTF8++;
//    
//    if( b < 0x80 )
//    {
//        *dwUCS4 = b;
//        return 1;
//    }
//    
//    if( b < 0xC0 || b > 0xFD )
//    {   // 非法UTF8
//        return 0;
//    }
//    
//    if( b < 0xE0 )
//    {
//        *dwUCS4 = b & 0x1F;
//        iLen = 2;
//    }
//    else if( b < 0xF0 )
//    {
//        *dwUCS4 = b & 0x0F;
//        iLen = 3;
//    }
//    else if( b < 0xF8 )
//    {
//        *dwUCS4 = b & 7;
//        iLen = 4;
//    }
//    else if( b < 0xFC )
//    {
//        *dwUCS4 = b & 3;
//        iLen = 5;
//    }
//    else
//    {
//        *dwUCS4 = b & 1;
//        iLen = 6;
//    }
//    
//    for( i = 1; i < iLen; i++ )
//    {
//        b = *pbUTF8++;
//        if( b < 0x80 || b > 0xBF )
//        {   // 非法UTF8
//            break;
//        }
//        
//        *dwUCS4 = ((*dwUCS4) << 6) + (b & 0x3F);
//    }
//    
//    if( i < iLen )
//    {   // 非法UTF8
//        return 0;
//    }
//    else
//    {
//        return iLen;
//    }
//}
//
//
