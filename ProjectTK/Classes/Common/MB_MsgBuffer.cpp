

#include "MB_MsgBuffer.h"

#include <cassert>
#include <cstring>

/**
 * Equality operator
 **/
bool operator==(const MB_MsgBuffer& lhs, const MB_MsgBuffer& rhs)
{
    return (lhs.GetLength() == rhs.GetLength()) &&
    (memcmp(lhs.GetData(), rhs.GetData(), lhs.GetLength()) == 0);
}

/**
 * Append data to the end of the buffer
 **/
bool MB_MsgBuffer::Write(const void* data, uint32_t len)
{
    assert(data != 0);
    assert(len > 0);
    
    uint16_t dataLen = HTON_I16(len);
   
    // resize to new length
    uint32_t oldSize = (uint32_t)m_buf.size();
    m_buf.resize(oldSize + len + 2);
    // copy directly into the vector's memory
    memcpy(&m_buf[oldSize], &dataLen, 2);
    memcpy(&m_buf[oldSize + 2], data, len);
    return true;
}

bool MB_MsgBuffer::WriteBegin()
{
    uint16_t data = 1;
    uint32_t len = 2;
    
    // resize to new length
    uint32_t oldSize = (uint32_t)m_buf.size();
    m_buf.resize(oldSize + len);
    // copy directly into the vector's memory
    memcpy(&m_buf[oldSize], &data, len);
    return true;
}

bool MB_MsgBuffer::WriteEnd()
{
    uint16_t data = HTON_I16(m_buf.size());
    uint32_t len = 2;
    
    // copy directly into the vector's memory
    memcpy(&m_buf[0], &data, len);
    return true;
}

bool MB_MsgBuffer::writeU8(u_char data)
{
    uint32_t len = 1;
    
    // resize to new length
    uint32_t oldSize = (uint32_t)m_buf.size();
    m_buf.resize(oldSize + len);
    // copy directly into the vector's memory
    memcpy(&m_buf[oldSize], &data, len);
    return true;
}

bool MB_MsgBuffer::writeU16(uint16_t data)
{
    data = HTON_I16(data);
    uint32_t len = 2;
    
    // resize to new length
    uint32_t oldSize = (uint32_t)m_buf.size();
    m_buf.resize(oldSize + len);
    // copy directly into the vector's memory
    memcpy(&m_buf[oldSize], &data, len);
    return true;
}

bool MB_MsgBuffer::writeU32(uint32_t data)
{
    data = HTON_I32(data);
    uint32_t len = 4;
    
    // resize to new length
    uint32_t oldSize = (uint32_t)m_buf.size();
    m_buf.resize(oldSize + len);
    // copy directly into the vector's memory
    memcpy(&m_buf[oldSize], &data, len);
    return true;
}

bool MB_MsgBuffer::WriteUINT64(uint64_t data)
{
    data = HTON_I64(data);
    uint32_t len = 8;
    
    // resize to new length
    uint32_t oldSize = (uint32_t)m_buf.size();
    m_buf.resize(oldSize + len);
    // copy directly into the vector's memory
    memcpy(&m_buf[oldSize], &data, len);
    return true;
}

/**
 * Read bytes from the current read position
 **/
bool MB_MsgBuffer::Read(void* dataOut, uint32_t len)
{
    assert(dataOut != 0);
    assert(len > 0);
    
    // not enough to read?
    if( len > (m_buf.size() - m_readOffset) )
        return false;
    // copy, advance read head
    memcpy(dataOut, &m_buf[m_readOffset], len);
    m_readOffset += len;
    return true;
}

char* MB_MsgBuffer::ReadString()
{
    //assert(dataOut == 0);
    
    uint16_t len = 0;
    readU16(&len);
    
    if( len == 0 || len > (m_buf.size() - m_readOffset) )
        return NULL;
    char* dataOut = (char*)malloc(sizeof(char)*(len+1));
    memset(dataOut, 0, sizeof(char)*(len+1));
    // copy, advance read head
    memcpy(dataOut, &m_buf[m_readOffset], len);
    m_readOffset += len;
    
    return dataOut;
}

bool MB_MsgBuffer::readU8(void* dataOut)
{
    assert(dataOut != 0);
    uint32_t len = 1;
    
    // not enough to read?
    if( len > (m_buf.size() - m_readOffset) )
        return false;
    // copy, advance read head
    memcpy(dataOut, &m_buf[m_readOffset], len);
    m_readOffset += len;
    return true;
}

bool MB_MsgBuffer::readU16(void* dataOut)
{
    assert(dataOut != 0);
    uint32_t len = 2;
    
    // not enough to read?
    if( len > (m_buf.size() - m_readOffset) )
        return false;
    // copy, advance read head
    memcpy(dataOut, &m_buf[m_readOffset], len);
    m_readOffset += len;
    uint16_t* data = (uint16_t*)(dataOut);
    *data = NTOH_I16(*data);
    return true;
}

bool MB_MsgBuffer::readU32(void* dataOut)
{
    assert(dataOut != 0);
    uint32_t len = 4;
    
    // not enough to read?
    if( len > (m_buf.size() - m_readOffset) )
        return false;
    // copy, advance read head
    memcpy(dataOut, &m_buf[m_readOffset], len);
    m_readOffset += len;
    uint32_t* data = (uint32_t*)dataOut;
    *data = NTOH_I32(*data);
    return true;
}

bool MB_MsgBuffer::readU64(void* dataOut)
{
    assert(dataOut != 0);
    uint32_t len = 8;
    
    // not enough to read?
    if( len > (m_buf.size() - m_readOffset) )
        return false;
    // copy, advance read head
    memcpy(dataOut, &m_buf[m_readOffset], len);
    m_readOffset += len;
    uint64_t* data = (uint64_t*)dataOut;
    *data = NTOH_I64(*data);
    return true;
}

void MB_MsgBuffer::skip(uint16_t len)
{
    assert(len + m_readOffset < m_buf.size());
    
    m_readOffset += len;
}

void MB_MsgBuffer::skipU8()
{
    assert(1 + m_readOffset < m_buf.size());
    
    m_readOffset += 1;
}

void MB_MsgBuffer::skipU16()
{
    assert(2 + m_readOffset < m_buf.size());
    
    m_readOffset += 2;
}

void MB_MsgBuffer::skipU32()
{
    assert(4 + m_readOffset < m_buf.size());
    
    m_readOffset += 4;
}

void MB_MsgBuffer::skipU64()
{
    assert(8 + m_readOffset < m_buf.size());
    
    m_readOffset += 8;
}

/**
 * Serialization
 **/
//SERIALIZE_DEFINE_PUT(KMB_MsgBuffer, obj, serializer)
//{
//    // store size and bytes, but not read offset
//    DWORD len = obj.GetLength();
//    return serializer.Put(len) &&
//    ((len == 0) || ( serializer.Put( obj.m_bCompress ) && serializer.PutRaw(obj.GetData(), len) ));
//}
//
//SERIALIZE_DEFINE_GET(KMB_MsgBuffer, obj, serializer)
//{
//    // clear existing contents
//    obj.Clear();
//    // read size
//    DWORD len;
//    if( !serializer.Get(len) )
//    {
//        return false;
//    }
//    
//    if( len == 0 )
//    {
//        return true;
//    }
//    
//    if( len > serializer.GetReadLength() )
//    {
//        return false;
//    }
//    
//    // resize and read data
//    obj.m_buf.resize(len);
//    return serializer.Get( obj.m_bCompress ) && serializer.GetRaw(&obj.m_buf[0], len);
//}

//#include "zlib/zlib.h"
//
//bool KMB_MsgBuffer::Compress()
//{
//    if( m_bCompress ) return true;
//
//    std::vector<UCHAR> vecBuff;
//    DWORD dwSize = compressBound( GetLength() );
//    vecBuff.resize( dwSize );
//    
//    // compress data.
//    DWORD dwOriginSize = GetLength();
//    int nRet = compress2( &vecBuff[0], &dwSize, (UCHAR*)GetData(), GetLength(), 1 );
//    if( nRet != Z_OK )
//        return false;
//    
//    vecBuff.resize( dwSize );   // trim extra buffer space
//    
//    Clear();
//    Write( &dwOriginSize, sizeof( dwOriginSize) );
//    Write( (void*)&vecBuff[0], vecBuff.size() );
//    
//    m_bCompress = true;
//    return true;
//}
//
//bool KMB_MsgBuffer::UnCompress()
//{
//    if( !m_bCompress ) return true;
//    
//    DWORD dwOriginSize;
//    DWORD dwRetSize;
//    
//    m_readOffset = 0;
//    
//    Read( &dwOriginSize, sizeof( dwOriginSize ) );
//    
//    dwRetSize = dwOriginSize;
//    
//    std::vector<UCHAR> vecDecompBuff;
//    vecDecompBuff.resize( dwOriginSize );
//    
//    int nRet = uncompress( &vecDecompBuff[0], &dwRetSize, (UCHAR*)&m_buf[m_readOffset], m_buf.size() - sizeof( dwOriginSize ) );
//    if( nRet != Z_OK || dwRetSize != dwOriginSize )
//        return false;
//    
//    Clear();
//    Write( (void*)(&vecDecompBuff[0]), dwOriginSize );
//    
//    m_bCompress = false;
//    
//    return true;
//}

