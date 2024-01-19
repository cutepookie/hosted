
#ifndef __ProjectMB__MB_LayerEventUnit__
#define __ProjectMB__MB_LayerEventUnit__

#include "Game.h"
#include "MB_NodeItem.h"
class MB_LayerEventUnit:public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
private:
    int  m_nType;
    CCLabelBMFont *m_pCancollect;
    CCLabelTTF *m_pMutilCollect;
    CCLabelTTF *m_pMoney[4];
    CCNode *m_pIcon[4];
    CCMenuItemImage *m_pCollectBt;
    int m_nActitvyID;
    int m_nUnitID;
    CCNode *m_pNodeSize;
public :
    MB_LayerEventUnit();
    ~MB_LayerEventUnit();
    virtual bool init(int type);
    static  MB_LayerEventUnit * create(int type);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onClickCollect(CCObject *);
    CCSize getUnitSize();
    void setActivityAndUnit(int activity, int ID);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool sendactivity_draw(uint16_t activityID,uint16_t drawID);
    bool recvactivity_draw(MB_MsgBuffer* recvPacket);
    bool addIcon(int16_t TypeId, int num,int *index,int level ,int rank ,bool isPet = false);
};

#endif /* defined(__ProjectMB__MB_LayerEventUnit__) */
