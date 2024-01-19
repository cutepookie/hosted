//
//  MB_ComposeMgr.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#ifndef __ProjectMB__MB_ComposeMgr__
#define __ProjectMB__MB_ComposeMgr__

#include "Game.h"

/*
 <Composes>
 <Compose id="",type="",material="",target="" />
 <Compose id="",type="",material="",target="" />
 </Composes>
 */

class MB_ComposeTemplate;


class MB_ComposeMgr:public CCObject
{
public:

    virtual ~MB_ComposeMgr();

    static MB_ComposeMgr* getInstance();

    static void destroyInstance();

    MB_ComposeTemplate* getComposeTemplateByID(uint16_t nID);

    void sendcombine_do(uint8_t nCombineType,uint16_t nComposeID,uint8_t nComposeType,uint64_t* pUidList,uint16_t nCount);

    void onMsgRecv(CCNode* node, SocketResponse* response);

    uint64_t getRandomCombine(int nStar,int nType);

protected:
    void recvcombine_fail(MB_MsgBuffer* pbuff);

    void recvcombine_pet(MB_MsgBuffer* pbuff);

    void recvcombine_equip(MB_MsgBuffer* pbuff);

    virtual bool init();
private:
    MB_ComposeMgr();
    static MB_ComposeMgr* m_pSingletonInstance;

    std::map<uint16_t,MB_ComposeTemplate*>  m_pComposeContainer;
    std::map<uint16_t,uint64_t>             m_RandomConbineCosts;
};

#endif /* defined(__ProjectMB__MB_ComposeMgr__) */
