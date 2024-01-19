
#ifndef __ProjectMB__MB_NodeServerInfo__
#define __ProjectMB__MB_NodeServerInfo__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class MB_NodeServerInfo : public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    
    MB_NodeServerInfo();
    ~MB_NodeServerInfo();
    bool init(const char* strServerZone, const char* strServerName, int serverStatus,unsigned int sid);

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual const CCSize& getNodeSize()const{return m_ContentSize;}
    void onZoneNodeClick(CCObject* pSender);
private:
    CCSize      m_ContentSize;
    std::string m_strServerZone;
    std::string m_strServerName;
    int         m_uServerStatus;
    unsigned int m_nServerID;
    
};

#endif /* defined(__ProjectMB__MB_NodeServerInfo__) */
