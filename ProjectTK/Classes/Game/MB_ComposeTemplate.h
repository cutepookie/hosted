//
//  MB_ComposeTemplate.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#ifndef __ProjectMB__MB_ComposeTemplate__
#define __ProjectMB__MB_ComposeTemplate__

#include "Game.h"

#define MAX_MATERIAL    5

/*<Compose id="",coin="10000000",type="",material="",target="" />*/
enum ComposeType
{
    kComposeCard = 1,
    kComposeItem = 2,
    kComposeUnknow,
};

class MB_ComposeMgr;

class MB_ComposeTemplate:public CCObject
{
public:
    friend class MB_ComposeMgr;
    virtual ~MB_ComposeTemplate();
    const uint16_t* getMaterialsArray()const;
protected:
    MB_ComposeTemplate();
    static MB_ComposeTemplate* create(MB_XmlNode* pNode);
    virtual bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nComposeID, ComposeID);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nComposeType, ComposeType);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTartgetID, TargetID);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nMaterialCount, MaterialCount);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nCostCoin, CostCoin);
    uint16_t                                    m_pMaterialArray[MAX_MATERIAL];
};

#endif /* defined(__ProjectMB__MB_ComposeTemplate__) */
