

#ifndef __ProjectMB__MB_MsgBuffer__
#define __ProjectMB__MB_MsgBuffer__


#include "ByteOrder.h"
#include "cocos2d.h"

class MB_MsgBuffer
{
public:
    MB_MsgBuffer();
    MB_MsgBuffer(const std::vector<char>& buff);
    MB_MsgBuffer(const MB_MsgBuffer& other);
    
    ~MB_MsgBuffer();
    
    const MB_MsgBuffer& operator=(const MB_MsgBuffer& other);
    
    bool Write(const void* data, uint32_t len);
    bool writeU8(u_char data);
    bool writeU16(uint16_t data);
    bool writeU32(uint32_t data);
    bool WriteUINT64(uint64_t data);
    bool WriteBegin();
    bool WriteEnd();
    
    bool Read(void* dataOut, uint32_t len);
    char* ReadString();
    bool readU8(void* dataOut);
    bool readU16(void* dataOut);
    bool readU32(void* dataOut);
    bool readU64(void* dataOut);
    
    void skipU8();
    void skipU16();
    void skipU32();
    void skipU64();
    void skip(uint16_t len);
    
    const void* GetData() const;
    uint32_t GetLength() const;
    void Clear();
    void Reset();
    uint32_t GetReadLength() const;
    
    const std::vector<char>& GetBuffer() const { return m_buf; }
    
    void Swap(MB_MsgBuffer& other);
    
    //bool Compress();
    //bool UnCompress();
    
private:
    bool                  m_bCompress;
    std::vector<char>     m_buf;          // buffer
    uint32_t                 m_readOffset;   // "read head" offset from m_buf[0]
    
};

// equality operator
bool operator==(const MB_MsgBuffer& lhs, const MB_MsgBuffer& rhs);

inline MB_MsgBuffer::MB_MsgBuffer()
: m_readOffset(0), m_bCompress(false)
{
}

inline MB_MsgBuffer::MB_MsgBuffer(const std::vector<char>& buff)
: m_buf(buff)
, m_readOffset(0)
, m_bCompress(false)
{
}

inline MB_MsgBuffer::MB_MsgBuffer(const MB_MsgBuffer& other)
: m_buf(other.m_buf),
m_readOffset(other.m_readOffset),
m_bCompress( other.m_bCompress )
{
}

inline MB_MsgBuffer::~MB_MsgBuffer()
{
}

inline const MB_MsgBuffer& MB_MsgBuffer::operator=(const MB_MsgBuffer& other)
{
    // check self-assignment
    if( this != &other )
    {
        m_buf = other.m_buf;
        m_readOffset = other.m_readOffset;
        m_bCompress = other.m_bCompress;
    }
    return *this;
}

inline void MB_MsgBuffer::Swap(MB_MsgBuffer& other)
{
    m_buf.swap(other.m_buf);
    uint32_t tmp = m_readOffset;
    m_readOffset = other.m_readOffset;
    other.m_readOffset = tmp;
    std::swap( m_bCompress, other.m_bCompress );
    
}

inline const void* MB_MsgBuffer::GetData() const
{
    return m_buf.empty() ? 0 : &m_buf[0];
}

inline uint32_t MB_MsgBuffer::GetLength() const
{
    return (uint32_t)m_buf.size();
}

inline void MB_MsgBuffer::Clear()
{
    m_bCompress = false;
    m_buf.clear();
    m_readOffset = 0;
}

inline void MB_MsgBuffer::Reset()
{
    m_readOffset = 0;
}

inline uint32_t MB_MsgBuffer::GetReadLength() const
{
    return (uint32_t)(m_buf.size() - m_readOffset);
}

#endif /* defined(__ProjectMB__MB_MsgBuffer__) */
