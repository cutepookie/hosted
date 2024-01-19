
#ifndef __ProjectMB__ByteOrder__
#define __ProjectMB__ByteOrder__

#include "stdint.h"
#include "sys/types.h"

namespace ByteOrder
{
    uint16_t  SwapInt16(uint16_t x);
    uint32_t  SwapInt32(uint32_t x);
    uint64_t SwapInt64(uint64_t x);
    float  SwapFloat32(float x);
    double SwapFloat64(double x);
}

// byteorder definitions
#define BYTEORDER_BIG       'B'
#define BYTEORDER_LITTLE    'L'

// win32 byte order
#define BYTEORDER_HOST      BYTEORDER_LITTLE
//#define BYTEORDER_NET       BYTEORDER_LITTLE
#define BYTEORDER_NET       BYTEORDER_BIG


#if( BYTEORDER_HOST == BYTEORDER_NET )
#   define HTON_I16(x) (x)
#   define HTON_I32(x) (x)
#   define HTON_I64(x) (x)
#   define HTON_F32(x) (x)
#   define HTON_F64(x) (x)
#else
#   define HTON_I16(x) (ByteOrder::SwapInt16(static_cast<uint16_t>(x)))
#   define HTON_I32(x) (ByteOrder::SwapInt32(static_cast<uint32_t>(x)))
#   define HTON_I64(x) (ByteOrder::SwapInt64(static_cast<uint64_t>(x)))
#   define HTON_F32(x) (ByteOrder::SwapFloat32(x))
#   define HTON_F64(x) (ByteOrder::SwapFloat64(x))
#endif

#define NTOH_I16(x) HTON_I16(x)
#define NTOH_I32(x) HTON_I32(x)
#define NTOH_I64(x) HTON_I64(x)
#define NTOH_F32(x) HTON_F32(x)
#define NTOH_F64(x) HTON_F64(x)

#endif /* defined(__ProjectMB__ByteOrder__) */
