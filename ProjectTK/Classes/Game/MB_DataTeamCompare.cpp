
#include "MB_DataTeamCompare.h"


MB_DataTeamCompare::MB_DataTeamCompare()
{
    m_pTeamArray = CCArray::create();
    m_pTeamArray->retain();
}

MB_DataTeamCompare::~MB_DataTeamCompare()
{
    CC_SAFE_RELEASE(m_pTeamArray);
}

bool MB_DataTeamCompare::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU32(&m_uRoleID);
    
    char* roleName = recvPacket->ReadString();
    if (roleName != NULL) {
        m_sRoleName = roleName;
    }
    CC_SAFE_FREE(roleName);
    recvPacket->readU16(&m_uRoleLevel);
    recvPacket->readU64(&m_uRoleFightPower);
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    
    int16_t data16;
    for (int i = 0; i < count; ++i)
    {
        MB_PetData* petData = new MB_PetData();
        if (recvPacket->readU16(&data16))
        {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16))
        {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU16(&data16))
        {
            petData->setPetTypeID(data16);
        }
        m_pTeamArray->addObject(petData);
        petData->release();
    }
    return true;
}