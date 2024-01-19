
#ifndef ProjectMB_MB_DescriptionCommonTable_h
#define ProjectMB_MB_DescriptionCommonTable_h
#include "MB_DescriptionCommon.h"
USING_NS_CC;

//singleton
class MB_DescriptionCommonTable:public CCObject
{
public:
    typedef std::map<std::string,MB_DescriptionCommon*> desTable;
    typedef desTable::iterator                          desTable_It;
    
public:
             MB_DescriptionCommonTable();
    virtual ~MB_DescriptionCommonTable();

public:
    static MB_DescriptionCommonTable& getInstance()
    {
        static MB_DescriptionCommonTable instance;
        return instance;
    }
public:
    sDesCommon*  getDesCommon   (std::string file,uint16_t key);

protected:
    void         loadConfig     (std::string file);
    void         loadDesCommon  (std::string file);
    
private:
    desTable     m_desTable;
};

#define DesTable  MB_DescriptionCommonTable::getInstance()

#endif
