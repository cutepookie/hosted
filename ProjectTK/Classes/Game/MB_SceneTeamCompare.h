

#ifndef __ProjectMB__MB_SceneTeamCompare__
#define __ProjectMB__MB_SceneTeamCompare__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_DataTeamCompare;

class MB_NodeTeamCompare_Old: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeTeamCompare_Old();
    ~MB_NodeTeamCompare_Old();
    CC_SYNTHESIZE(int, m_nRoleID, RoleID);
    static MB_NodeTeamCompare_Old* create(MB_PetData* petData, CCPoint pos,bool bIs3v3Match = false);
    virtual bool init(MB_PetData* petData, CCPoint pos,bool bIs3v3Match = false);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onDel2Clicked(CCObject *);
    virtual void onDel1Clicked(CCObject *);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void onPetTeamDataDtl(MB_MsgBuffer* recvPacket);
private:
    bool m_bIs3v3Match;
    std::string m_sPetName;
    uint16_t    m_nPetType;
    ccColor3B   m_Color;
    
    CCNode*     m_pNodeIcon;


};


class MB_SceneTeamCompare_Old : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_SceneTeamCompare_Old();
    ~MB_SceneTeamCompare_Old();
    
    static CCScene* scene(MB_DataTeamCompare* data,bool bIs3v3Match = false);
    static MB_SceneTeamCompare_Old* create(MB_DataTeamCompare* data,bool bIs3v3Match = false);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(MB_DataTeamCompare* data,bool bIs3v3Match = false);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual void onTeamClicked(CCObject* pSender);
    virtual void onBackClicked(CCObject* pSender);
    CC_SYNTHESIZE(MB_DataTeamCompare*,m_pData,Data);
protected:
    bool m_bIsEnemy;
    int m_uPetIndex;
    CCNode* m_pOur_pos;
    CCNode* m_pEnemy_pos;
    bool m_bIsPopScene;
    
    CCLabelTTF* m_pRoleName;
    CCLabelBMFont*     m_pNodeOtherLv;
    CCLabelBMFont*     m_pNodeSelfLv;
};




//class MB_NodeTeamCompare:public MB_NodeTeamCompare_Old
//{
//public:
//    MB_NodeTeamCompare():m_IsWorldKing(true){}
//    void onDel1Clicked(CCObject *);
//    void onMsgRecv(CCNode* node, SocketResponse* response);
//    static MB_NodeTeamCompare* create(MB_PetData* petData, CCPoint pos,bool isWorldKing = true);
//    
//    CC_SYNTHESIZE(bool, m_IsWorldKing, IsWorldKing);
//};
class MB_SceneTeamCompare:public MB_SceneTeamCompare_Old
{
public:
    MB_SceneTeamCompare();
    ~MB_SceneTeamCompare();
    static MB_SceneTeamCompare* create(MB_DataTeamCompare* data0,MB_DataTeamCompare* data1);
    static CCScene* scene(MB_DataTeamCompare* data0,MB_DataTeamCompare* data1);
    
    static CCScene* scene(MB_DataTeamCompare* data);
    static MB_SceneTeamCompare* create(MB_DataTeamCompare* data);
    virtual bool init(MB_DataTeamCompare* data);
    virtual bool init(MB_DataTeamCompare* data,MB_DataTeamCompare* data1);
    CC_SYNTHESIZE(MB_DataTeamCompare*,m_pDataSefCp,DataSefCp);
};

#endif /* defined(__ProjectMB__MB_SceneTeamCompare__) */
