
#ifndef ProjectMB_MB_DescriptionCommon_h
#define ProjectMB_MB_DescriptionCommon_h
#include "cocos2d.h"
#include "MB_DescriptionCommonUnit.h"

typedef std::map<uint16_t,sDesCommon*>  desCommonMap;
typedef desCommonMap::iterator          desCommonMap_It;

class MB_DescriptionCommon:public cocos2d::CCObject
{
public:
    
                    MB_DescriptionCommon  (void);
    virtual        ~MB_DescriptionCommon  (void);
public:
    virtual void    load                  (std::string file);
    
public:
    sDesCommon*     getDesCommon          (uint16_t key);
    bool            contains              (uint16_t key);
    
private:
    desCommonMap    m_desCommonMap;
private:
    bool            m_isInit;
};


#endif
