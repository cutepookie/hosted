//
//  MB_NodePetTeam.h
//  ProjectMB
//
//  Created by yuanwugang on 14-9-24.
//
//

#ifndef __ProjectMB__MB_NodePetTeam__
#define __ProjectMB__MB_NodePetTeam__

#include "MB_ResWindow.h"
#include "MB_LocalProto.h"
class MB_PetData;
class MB_NodePetTeam:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePetTeam();
    virtual ~MB_NodePetTeam();
    static MB_NodePetTeam* create(uint64_t uid);
    virtual bool init(uint64_t uid);
    
    static MB_NodePetTeam* create(MB_PetData* pData);
    virtual bool init(MB_PetData* pData);
    
    virtual void onResetWnd(void);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
//    static const  CCSize & getSize();
    
    void setShowInfo(bool bShow);
public:
        CCScale9Sprite*  m_pSpriteBG2;
    
protected:
//    void onDetailClicked(CCObject* pSender);
protected:
    CCSprite*       m_pSpriteFrame;
    CCSprite*       m_pSpriteCard;
    CCLabelTTF*     m_pTTFName;
    CCLabelTTF*     m_pTTFLv;
    CCSprite*       m_pStar[MAX_GER_STAR];
    CCPoint         starPt[7];
    CCNode*         m_pNodeInfo;
    CCSprite*       m_pSpriteBG1;

    MB_PetData* m_pData;
    uint64_t m_nUID;
};


#endif /* defined(__ProjectMB__MB_NodePetTeam__) */
