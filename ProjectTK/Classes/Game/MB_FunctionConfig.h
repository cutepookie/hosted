//
//  MB_FunctionConfig.h
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#ifndef __ProjectMB__MB_FunctionConfig__
#define __ProjectMB__MB_FunctionConfig__

#include "MB_ClientData.h"

class MB_XmlNode;

/*<function type="101" name="任務" openlable="name_renwu.png" closelable="name_close.png" level="10"  enable="btn_index_00.png" disable="btn_index_01.png" activateccbi="res/gui_tutorial_lv10.ccbi" />*/
class MB_FunctionItem:public MB_ClientData
{
public:
    static MB_FunctionItem* create(MB_XmlNode* pNode);
    virtual bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nFunctionType, FunctionType);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nLevel, NeedLevel);
    CC_SYNTHESIZE_READONLY(std::string, m_szFunctionName, FunctionName);
    CC_SYNTHESIZE_READONLY(std::string, m_szEnableFile, EnableFile);
    CC_SYNTHESIZE_READONLY(std::string, m_szDisableFile, DisableFile);
    CC_SYNTHESIZE_READONLY(std::string, m_szActivateCcbi, ActivateCcbi);
    CC_SYNTHESIZE_READONLY(std::string, m_szNameEnable, NameEnable);
    CC_SYNTHESIZE_READONLY(std::string, m_szNameDisable, NameDisable);
    CC_SYNTHESIZE_READONLY(std::string, m_szDes, Des);
};

class MB_ActivatyRestrict:public MB_ClientData
{
public:
    static MB_ActivatyRestrict* create(MB_XmlNode* pNode);
    virtual bool init(MB_XmlNode* pNode);
    bool isActivated();
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nRestrictRoleLevel, RestrictRoleLevel);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nRestrictVipLevel, RestrictVipLevel);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nType, Type);
};

class MB_FunctionConfigure
{
public:
    virtual ~MB_FunctionConfigure();
    static MB_FunctionConfigure* getInstance();
    static void destroyInstance();
    MB_FunctionItem* queryFunctionItemByType(uint16_t nType);
    MB_ActivatyRestrict* queryActivatRestrictItemByType(uint16_t nType);
    bool getIsRoleOutOfRestrict(uint16_t nType);
    void loadResource2SpriteCache();
    void removeResourceFromCache();
    int getFunctionLimitLevel(int type);
protected:
    virtual bool init();
    virtual bool addPage(MB_XmlNode* pNode);
private:
    MB_FunctionConfigure();
    std::string         m_pResource;
    static MB_FunctionConfigure* m_pSingletonInstance;
    CCArray*            m_pContainer;
    CCArray*            m_pRestrictItems;
};

#endif /* defined(__ProjectMB__MB_FunctionConfig__) */
