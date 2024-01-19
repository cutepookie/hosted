//
//  MB_SuitTemplate.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#ifndef __ProjectMB__MB_SuitTemplate__
#define __ProjectMB__MB_SuitTemplate__

#include "Game.h"


/*
 <set id="10001" name="青铜套装" group="10207,10208,10209,10210,10211,10212">
    <activate needAmount="2">
        <attr type="1" value="100" />
        <attr type="2" value="100" />
        <attr type="3" value="100" />
    </activate>
 </set>
 */
class MB_SuitActivateData;
class MB_SuitTemplate:public CCObject
{
public:
    enum ESuitPartType
    {
        kPartWeapon     = 0,    // 武器
        kPartHeadWare   = 1,    // 头饰
        kPartArmor      = 2,    // 战甲
        kPartWing       = 3,    // 翅膀
        kPartRuneStore  = 4,    // 符石
        kPartToterm     = 5,    // 图腾
        kPartCount,
    };

    MB_SuitTemplate();

    ~MB_SuitTemplate();

    virtual bool init(MB_XmlNode* pNode);

    static MB_SuitTemplate* create(MB_XmlNode* pNode);

    const char* getSuitName()const;

    uint16_t getPartItemIdByType(int nType)const;

    const uint16_t* getParts()const;

    bool getActivateOptionsByPartCount(CCArray* pOptions,int nCount);

    MB_SuitActivateData* QueryActivateOptionByPartCount(int nCount);

    bool isItemInThisSuit(uint16_t nItemId)const;

    CCNode* createActivateAttrPanelByCount(uint16_t nCount,const CCSize& sz)const;
    CCArray* getActivateOptions(){return m_pActivateOptions;}
    
    uint8_t getSuitStar();
private:
    CC_SYNTHESIZE_READONLY(int, m_nId, Id);

    CC_SYNTHESIZE_READONLY(uint16_t, m_nGroupCount, GroupCount);

    std::string     m_szSuitName;

    uint16_t        m_nParts[6];

    CCArray*        m_pActivateOptions;
};

#endif /* defined(__ProjectMB__MB_SuitTemplate__) */
