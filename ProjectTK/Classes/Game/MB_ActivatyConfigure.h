//
//  MB_ActivatyConfigure.h
//  ProjectPM
//
//  Created by chk on 14-4-30.
//
//

#ifndef __ProjectMB__MB_ActivatyConfigure__
#define __ProjectMB__MB_ActivatyConfigure__

#include "cocos2d.h"
#include <map>
USING_NS_CC;

class MB_XmlNode;

/*<function type="101" name="任務" openlable="name_renwu.png" closelable="name_close.png" level="10"  enable="btn_index_00.png" disable="btn_index_01.png" activateccbi="res/gui_tutorial_lv10.ccbi" />*/
class MB_ActivatyItem:public CCObject
{
public:
    static MB_ActivatyItem* create(MB_XmlNode* pNode);
    bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nActivatyType, ActivatyType);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nLevel, NeedLevel);
    CC_SYNTHESIZE_READONLY(std::string, m_szActivatyName, ActivatyName);
    CC_SYNTHESIZE_READONLY(std::string, m_szActivateCcbi, ActivateCcbi);
};

class MB_ActivatyConfigure
{
public:
    virtual ~MB_ActivatyConfigure();
    static MB_ActivatyConfigure* getInstance();
    static void destroyInstance();
    MB_ActivatyItem* queryActivatyItemByType(uint16_t nType);
    void loadResource2SpriteCache();
protected:
    virtual bool init();
    bool addActivaty(MB_XmlNode* pNode);
private:
    MB_ActivatyConfigure();
    std::string         m_pResource;
    static MB_ActivatyConfigure* m_pSingletonInstance;
    CCArray*            m_pContainer;
};
#endif /* defined(__ProjectMB__MB_ActivatyConfigure__) */
