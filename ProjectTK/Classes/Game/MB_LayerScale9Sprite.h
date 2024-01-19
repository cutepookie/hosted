//
//  MB_LayerScale9Sprite.h
//  ProjectPM
//
//  Created by WenYong on 14-5-6.
//
//

#ifndef __ProjectMB__MB_LayerScale9Sprite__
#define __ProjectMB__MB_LayerScale9Sprite__

#include "MB_ResWindow.h"

class MB_LayerScale9SpriteTest:public MB_ResWindow,
public CCBMemberVariableAssigner
{
public:
    MB_LayerScale9SpriteTest();
    ~MB_LayerScale9SpriteTest();
    CREATE_FUNC(MB_LayerScale9SpriteTest);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onResetWnd();
private:
    CCScale9Sprite*     m_pSprite0;
    CCScale9Sprite*     m_pSprite1;
};
#endif /* defined(__ProjectMB__MB_LayerScale9Sprite__) */
