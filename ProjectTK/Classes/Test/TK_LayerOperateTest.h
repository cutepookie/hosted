//
//  TK_LayerOperateTest.h
//  ProjectTK
//
//  Created by lic on 13-4-3.
//
//

#ifndef ProjectTK_TK_TK_LayerOperateTest_h
#define ProjectTK_TK_TK_LayerOperateTest_h
#include "TK_LayerWindow.h"
#include "Game.h"
class TK_LayerOperateTestMainView:public TK_LayerWindow
{
public:
    virtual bool init (void);
protected:
    void clickPop(CCObject* psender);
    void clickPush(CCObject* psender);
    void clickReplace(CCObject* psender);


};

class TK_LayerOperateTestPage:public TK_LayerWindow
{
public:
    TK_LayerOperateTestPage(){i++;
    
        winID = i;
        CCLog("%d 号窗体 创建！",winID);
    }
    ~TK_LayerOperateTestPage()
    {
        CCLog("%d 号窗体 析构！",winID);
    }
    
    virtual bool init (void);
    
    CREATE_FUNC(TK_LayerOperateTestPage)
public:
    static int i;
    
    int winID;
protected:
    void clickClose(CCObject* psender);
    
};


#endif
