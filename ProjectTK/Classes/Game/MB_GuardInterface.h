//
//  MB_GuardInterface.h
//  ProjectMB
//
//  Created by yuanwugang on 15-3-3.
//
//

#ifndef __ProjectMB__MB_GuardInterface__
#define __ProjectMB__MB_GuardInterface__

#include "MB_FunctionModule.h"
#include "MB_TeamData.h"

class MB_PetGuardData;
class MB_MsgBuffer;
class MB_PetGuardRule;
class MB_GuardInterface : CCObject
{
public:
    MB_GuardInterface();
    ~MB_GuardInterface();
    
    static MB_GuardInterface* getInstance();
    static void destroyInstance();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    void send_PetGuardInfo();
    void recv_PetGuardInfo(MB_MsgBuffer* pRecv);
    void send_PetGuardSet(uint64_t uid,uint8_t pos);
    void recv_PetGuardSet(MB_MsgBuffer* pRecv);
    void send_PetGuardRefresh(uint8_t pos,bool* list);
    void recv_PetGuardRefresh(MB_MsgBuffer* pRecv);
    
    MB_PetGuardData* getPetGuardDataByPos(uint8_t pos);
    MB_PetGuardData* getPetGuardDataByUid(uint64_t uid);
    //检查是否守護精靈
    bool checkIsGuardPos(uint8_t pos);
    bool checkIsGuardPet(uint64_t uid);
    bool checkIsGuardPetType(uint16_t tid);
    uint8_t getRankByValAndType(uint32_t val,uint8_t type);
    uint32_t getCostByLockNum(int num);
protected:
    MB_PetGuardData* m_pData[MEMBER_NUM];
    MB_PetGuardRule* m_pRule;
    static  MB_GuardInterface* m_pInstance;
    CC_SYNTHESIZE(uint8_t,m_uCurPos,CurPos);
};
#endif /* defined(__ProjectMB__MB_GuardInterface__) */
