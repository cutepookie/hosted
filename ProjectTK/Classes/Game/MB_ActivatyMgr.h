//
//  MB_ActivatyMgr.h
//  ProjectPM
//
//  Created by WenYong on 14-5-25.
//
//

#ifndef __ProjectMB__MB_ActivatyMgr__
#define __ProjectMB__MB_ActivatyMgr__

#include "Game.h"
class MB_NodeSubActivatyEntry;
class MB_ActivatyMgr
{
public:
    ~MB_ActivatyMgr();
    static MB_ActivatyMgr* getInstance();
    static void destroyInstance();
    void lockEntry(MB_NodeSubActivatyEntry* pEntry);
    void unlockEntry();
    void reset();
    
    void setScrollView(CCScrollView* pScrollview);
private:
    MB_ActivatyMgr();
    void updataContentOffset();
private:
    MB_NodeSubActivatyEntry*        m_pLockedEntry;
    static MB_ActivatyMgr*      m_pActivateInstance;
    
    CC_SYNTHESIZE(int, m_nLastLockedTag, LastLockedTag);
    CCScrollView* m_pScrollview;
};
#endif /* defined(__ProjectMB__MB_ActivatyMgr__) */
