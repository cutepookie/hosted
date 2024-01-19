//
//  TK_LayerOperateTest.cpp
//  ProjectTK
//
//  Created by lic on 13-4-3.
//
//

#include "TK_LayerOperateTest.h"
 int TK_LayerOperateTestPage::i = 0;

bool TK_LayerOperateTestMainView::init(void)
{
    CCMenu* m_pMenu;
    CCMenuItemFont* m_pPop;
    CCMenuItemFont* m_pPush_Back;
    CCMenuItemFont* m_pReplace;
    
    m_pPop = CCMenuItemFont::create("POP",this,menu_selector(TK_LayerOperateTestMainView::clickPop));
    
    m_pPush_Back = CCMenuItemFont::create("PUSH_BACK",this,menu_selector(TK_LayerOperateTestMainView::clickPush));
    m_pPush_Back->setPositionY(60);
    
    m_pReplace = CCMenuItemFont::create("REPLACE",this,menu_selector(TK_LayerOperateTestMainView::clickReplace));
    m_pReplace->setPositionY(120);
    
    m_pMenu = CCMenu::create(m_pPop,m_pPush_Back,m_pReplace,NULL);
    m_pMenu->setPosition(80,200);
    addChild(m_pMenu);
    return true;
}

void TK_LayerOperateTestMainView::clickPop(CCObject* psender)
{
    popLayer();
}
void TK_LayerOperateTestMainView::clickPush(CCObject* psender)
{
    pushLayer(TK_LayerOperateTestPage::create());
}

void TK_LayerOperateTestMainView::clickReplace(CCObject* psender)
{
    replaceLayer(TK_LayerOperateTestPage::create());
}


bool TK_LayerOperateTestPage::init (void)
{
    char temp[32];
    sprintf(temp,"%d 号窗体！！！！",winID);
    CCLabelTTF* plabel = CCLabelTTF::create(temp,"Marker Felt",12);
    addChild(plabel);
    
    CCMenu* m_pMenu;
    CCMenuItemFont* m_pPop;

    m_pPop = CCMenuItemFont::create("POP_ME",this,menu_selector(TK_LayerOperateTestPage::clickClose));
    //m_pPush_Back->setPositionY(60);
    
    m_pMenu = CCMenu::create(m_pPop,NULL);
    m_pMenu->setPosition(50,100);
    addChild(m_pMenu);
    
    setPosition(ccp(200 + rand()%100,100+rand()%100));
    
    return true;
}

void TK_LayerOperateTestPage::clickClose(CCObject* psender)
{
    popMe();
}
