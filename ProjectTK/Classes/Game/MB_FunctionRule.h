//
//  MB_FunctionRule.h
//  ProjectPM
//
//  Created by WenYong on 14-7-26.
//
//

#ifndef __ProjectMB__MB_FunctionRule__
#define __ProjectMB__MB_FunctionRule__

#include "MB_ClientData.h"
class RichText;
using namespace cocos2d;

/*
 <Rules level="25">
    <Rule functionType="" richText="1" content=""/>
 </Rules>
 */
class MB_RuleData : public MB_ClientData
{
public:
    MB_RuleData()
    {
        m_nType = 0;
        m_bRichText = false;
    }
    virtual bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(int, m_nType, Type);
    CC_SYNTHESIZE_READONLY(bool, m_bRichText, RichText);
    CC_SYNTHESIZE_READONLY(std::string, m_pszContent, Content);
};

class MB_FunctionRule:public CCObject
{
public:
    static MB_FunctionRule* getInstance();
    static void destroyInstance();
    ~MB_FunctionRule();
    const MB_RuleData* getRuleByType(int nType);
    CCNode* craeteRuleNodeByType(int nType,const CCSize& sz);

protected:
    
    MB_FunctionRule();
    bool readConfig();
private:
    static MB_FunctionRule* m_pInstance;
    CCArray*                m_pRules;
};

#endif /* defined(__ProjectMB__MB_FunctionRule__) */
