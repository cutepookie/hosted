//
//  MB_LayerPerfectRaceRule.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#include "MB_LayerPerfectRaceRule.h"
#include "MB_FunctionMgr.h"
#include "../Common/RichText.h"

MB_LayerPerfectRaceRule::MB_LayerPerfectRaceRule()
{
    m_pNodeRule = NULL;
    m_pRichBox = NULL;
}

MB_LayerPerfectRaceRule::~MB_LayerPerfectRaceRule()
{
    CC_SAFE_RELEASE_NULL(m_pNodeRule);
    CC_SAFE_RELEASE_NULL(m_pRichBox);
}

bool MB_LayerPerfectRaceRule::init()
{
    CCNode* pNode = loadResource("res/monsterrace_layer_rule.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
//        NSGameHelper::adjustScrollNode(m_pNodeRule);
        pScrollView = CCScrollView::create(m_pNodeRule->getContentSize());
        pScrollView->setDirection(kCCScrollViewDirectionVertical);
        CC_SAFE_RELEASE_NULL(m_pRichBox);
        m_pRichBox = RichText::create("",24,CCSizeMake(m_pNodeRule->getContentSize().width, 0));
        m_pRichBox->retain();
        pScrollView->setContainer(m_pRichBox);
        onResetWnd();
        m_pNodeRule->addChild(pScrollView);
        
        return true;
    }
    
    return false;
}

void MB_LayerPerfectRaceRule::onResetWnd()
{
    setRuleString(getRuleString().c_str());
    pScrollView->setContentSize(m_pRichBox->getContentSize());
    pScrollView->setContentOffset(ccp(0,m_pNodeRule->getContentSize().height - m_pRichBox->getContentSize().height));
}

bool MB_LayerPerfectRaceRule::onAssignCCBMemberVariable(CCObject* pTarget,
                                                        const char* pMemberVariableName,
                                                        CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_rule",CCNode*, m_pNodeRule);
    return false;
}

SEL_MenuHandler MB_LayerPerfectRaceRule::onResolveCCBCCMenuItemSelector(CCObject * pTarget,
                                                                        const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPerfectRaceRule::onBackClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerPerfectRaceRule::onResolveCCBCCControlSelector(CCObject * pTarget,
                                                   const char* pSelectorName)
{
    
    return NULL;
}

//static void convertToRbfString(std::string& str)
//{
//    for (int i = 0; i<str.length(); ++i)
//    {
//        if (str[i] == '{')
//        {
//            str[i] = '<';
//        }
//        else if(str[i] == '}')
//        {
//            str[i] = '>';
//        }
//    }
//}
const std::string& MB_LayerPerfectRaceRule::getRuleString()
{
    if (m_szRule.empty())
    {
        MB_XmlFile* pFile = MB_XmlFile::create("config/monster_game.xml");
        if (pFile)
        {
            CCArray* pArray = CCArray::create();
            if(pFile->queryNodesByName("help", pArray))
            {
                MB_XmlNode* pNode = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
                if (pNode)
                {
                    m_szRule = pNode->queryAttributeByName("des")->getCString();
                }
            }
        }
//        convertToRbfString(m_szRule);
    }
    return m_szRule;
}

void MB_LayerPerfectRaceRule::setRuleString(const char* pString)
{
    if (m_pRichBox && pString)
    {
        m_pRichBox->setAnchorPoint(ccp(0,0));
        m_pRichBox->setString(pString);
    }
}

void MB_LayerPerfectRaceRule::onBackClicked(CCObject* pSender)
{
    popWindow();
}

std::string MB_LayerPerfectRaceRule::m_szRule = "";
