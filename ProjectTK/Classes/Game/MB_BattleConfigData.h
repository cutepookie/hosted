//
//  MB_BattleConfigData.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-13.
//
//

#ifndef __ProjectMB__MB_BattleConfigData__
#define __ProjectMB__MB_BattleConfigData__

#include "../Common/GameLib/UnityXml/MB_XmlItems.h"

class MB_BattleConfigData
{
public:
    static MB_BattleConfigData* getInstance();
    static void destroyInstance();
    bool getColorBySpiritValue(ccColor3B* pColor,int nSpirit);
private:
    static MB_BattleConfigData*     m_pSingletonInstance;
    bool init();
    MB_BattleConfigData();
    ~MB_BattleConfigData();
    ccColor3B*        m_pData;
    unsigned int      m_nCount;
};

#endif /* defined(__ProjectMB__MB_BattleConfigData__) */

