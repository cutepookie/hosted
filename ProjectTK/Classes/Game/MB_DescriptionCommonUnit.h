
#ifndef ProjectMB_MB_DescriptionCommonUnit_h
#define ProjectMB_MB_DescriptionCommonUnit_h

#include "cocos2d.h"

class DescriptionCommonUnit
{
public:
    DescriptionCommonUnit   (){m_value = "";}
public:
    void                    insertPair (std::string key ,std::string value);
    bool                    contains   (std::string key);
    DescriptionCommonUnit&  queryValue (std::string key);
    
    //transform
    int                     toInt      (void);
    std::string             toString   (void);
    bool                    toBoolean  (void);
    
private:
    std::string                         m_value;
    std::map<std::string, std::string>  m_KeyValueMap;
};

typedef DescriptionCommonUnit sDesCommon;

#endif
