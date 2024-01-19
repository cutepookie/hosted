
#ifndef __ProjectMB__MB_DataTeamCompare__
#define __ProjectMB__MB_DataTeamCompare__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_DataTeamCompare: public CCObject
{
public:
    MB_DataTeamCompare();
    ~MB_DataTeamCompare();
    
    CC_SYNTHESIZE(uint32_t, m_uRoleID, RoleID);
    CC_SYNTHESIZE(uint16_t, m_uRoleLevel, RoleLevel);
    CC_SYNTHESIZE(uint64_t, m_uRoleFightPower, RoleFightPower);
    
    void setRoleName(const char* roleName) { m_sRoleName = roleName;}
    const char* getRoleName() { return m_sRoleName.c_str();}
    CCArray* getTeamArray() { return m_pTeamArray;}
    
    bool read(MB_MsgBuffer* recvPacket);
private:
    std::string m_sRoleName;
    CCArray* m_pTeamArray;
};


#endif /* defined(__ProjectMB__MB_DataTeamCompare__) */
