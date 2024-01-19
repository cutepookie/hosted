//
//  MB_LayerCommand.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_LayerCommand__
#define __ProjectMB__MB_LayerCommand__

#include "MB_ResWindow.h"

class MB_LayerCommand:public MB_ResWindow,
public CCBMemberVariableAssigner
{
public:
    MB_LayerCommand();
    virtual ~MB_LayerCommand();
    virtual bool init();
    
    virtual bool onAssignCCBMemberVariable (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    CREATE_FUNC(MB_LayerCommand);
    bool showNodeFunctions(bool b)
    {
        bool bOld = m_pNodeFunctions->isVisible();
        m_pNodeFunctions->setVisible(b);
        return bOld;
    }
    void setSelectedSprPos(int index);
    CCNode* rootNode;
protected:
    virtual bool initFunctions();
    void updateAddSign(float dt);
private:

    CCNode* m_pNodeHome;
    CCNode* m_pNodeFriend;
    CCNode* m_pNodeFormation;
    CCNode* m_pNodeCallCrad;
    CCNode* m_pNodeRoom;
    CCNode* m_pNodeItem;
    CCNode* m_pSelectedSpr;
    CCNode* m_pNodeFunctions;
};

#endif /* defined(__ProjectMB__MB_LayerCommand__) */
