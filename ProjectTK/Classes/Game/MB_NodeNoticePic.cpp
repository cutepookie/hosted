//
//  MB_NodeNoticePic.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-1-21.
//
//

#include "MB_NodeNoticePic.h"
#include "MB_FunctionModule.h"

MB_NodeNoticePic::MB_NodeNoticePic()
{
    m_pSpritePic = NULL;
}
MB_NodeNoticePic::~MB_NodeNoticePic()
{
    CC_SAFE_RELEASE_NULL(m_pSpritePic);
}


bool MB_NodeNoticePic::init()
{
    CCNode* node = MB_ResWindow::loadResource("res/message_node_newpicture");
    if (node)
    {
        this->addChild(node);
        this->setContentSize(m_pSpritePic->getContentSize());
        return true;
    }
    return false;
}
bool MB_NodeNoticePic::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpritePic", CCSprite*,m_pSpritePic);
    return false;
}

bool MB_NodeNoticePic::setPic(int picID)
{
    if (picID == 0)
    {
        return false;
    }
    //TODODO 公告图
//    char file[128];
//    sprintf(file,"bg/tmzz_banner_zhaohuan_char.png",picID);

    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage("bg/tmzz_banner_zhaohuan_char.png");
    if(textrue != NULL)
    {
        CCSpriteFrame * frame  = CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        if (frame)
        {
            m_pSpritePic->setDisplayFrame(frame);
            return true;
        }
    }
    return false;
}
