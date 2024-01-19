//
//  MB_EquipmentSuitsMgr.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#ifndef __ProjectMB__MB_EquipmentSuitsMgr__
#define __ProjectMB__MB_EquipmentSuitsMgr__

#include "Game.h"

class MB_SuitTemplate;

class MB_SuitEquipmentMgr:public CCObject
{
public:
    virtual ~MB_SuitEquipmentMgr();

    static MB_SuitEquipmentMgr* getInstance();

    static void destroyInstance();

    MB_SuitTemplate* getSuitTemplateBy(int nSuitId)const;
    
protected:

    virtual bool init();

private:
    MB_SuitEquipmentMgr();

    static MB_SuitEquipmentMgr* m_pSingletonInstance;

    CCArray*            m_pSuitsTemplate;
};

#endif /* defined(__ProjectMB__MB_EquipmentSuitsMgr__) */
