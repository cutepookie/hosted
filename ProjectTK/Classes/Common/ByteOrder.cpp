
#include "ByteOrder.h"

#define TEMP_SWAP(a,b,tmp) tmp = a; a = b; b = tmp

/**
 * Returns physically converted 16-bit intepet
 **/
uint16_t ByteOrder::SwapInt16(uint16_t x)
{
    // get the individual bytes
    u_char b0 = static_cast<u_char>(x & 0xFF);
    u_char b1 = static_cast<u_char>((x >> 8) & 0xFF);
    // put them back in reverse order
    return static_cast<uint16_t>((b0 << 8) | b1);
}

/**
 * Returns physically converted 32-bit intepet
 **/
uint32_t ByteOrder::SwapInt32(uint32_t x)
{
    // get the individual bytes
    u_char b0 = static_cast<u_char>(x & 0xFF);
    u_char b1 = static_cast<u_char>((x >> 8) & 0xFF);
    u_char b2 = static_cast<u_char>((x >> 16) & 0xFF);
    u_char b3 = static_cast<u_char>((x >> 24) & 0xFF);
    // put them back in reverse order
    return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}


/**
 * Returns physically converted 64-bit intepet
 **/
uint64_t ByteOrder::SwapInt64(uint64_t x)
{
    // use union hack
    union
    {
        uint64_t val;
        u_char bytes[8];
    } u;
    u.val = x;
    // 0 1 2 3 4 5 6 7 -> 7 6 5 4 3 2 1 0
    u_char tmp;
    TEMP_SWAP(u.bytes[0], u.bytes[7], tmp);
    TEMP_SWAP(u.bytes[1], u.bytes[6], tmp);
    TEMP_SWAP(u.bytes[2], u.bytes[5], tmp);
    TEMP_SWAP(u.bytes[3], u.bytes[4], tmp);
    return u.val;
}


/**
 * Returns physically converted 32-bit float
 **/
float ByteOrder::SwapFloat32(float x)
{
    // use union hack
    union
    {
        float val;
        u_char bytes[4];
    } u;
    u.val = x;
    // 0 1 2 3 -> 3 2 1 0
    u_char tmp;
    TEMP_SWAP(u.bytes[0], u.bytes[3], tmp);
    TEMP_SWAP(u.bytes[1], u.bytes[2], tmp);
    return u.val;
}

/**
 * Returns physically converted 64-bit float
 **/
double ByteOrder::SwapFloat64(double x)
{
    // use union hack
    union
    {
        double val;
        u_char bytes[8];
    } u;
    u.val = x;
    // 0 1 2 3 4 5 6 7 -> 7 6 5 4 3 2 1 0
    u_char tmp;
    TEMP_SWAP(u.bytes[0], u.bytes[7], tmp);
    TEMP_SWAP(u.bytes[1], u.bytes[6], tmp);
    TEMP_SWAP(u.bytes[2], u.bytes[5], tmp);
    TEMP_SWAP(u.bytes[3], u.bytes[4], tmp);
    return u.val;
}
