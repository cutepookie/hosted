//
//  MB_ActivatyMgr.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-25.
//
//

#include "MB_ActivatyMgr.h"
#include "MB_NodeSubActivatyEntry.h"

MB_ActivatyMgr* MB_ActivatyMgr::m_pActivateInstance = NULL;

MB_ActivatyMgr* MB_ActivatyMgr::getInstance()
{
    if (m_pActivateInstance==NULL)
    {
        m_pActivateInstance = new MB_ActivatyMgr;
    }
    
    return m_pActivateInstance;
}

void MB_ActivatyMgr::setScrollView(CCScrollView* pScrollview)
{
    m_pScrollview = pScrollview;
}

void MB_ActivatyMgr::destroyInstance()
{
    CC_SAFE_DELETE(m_pActivateInstance);
}

void MB_ActivatyMgr::lockEntry(MB_NodeSubActivatyEntry* pEntry)
{
    if (pEntry == NULL)
    {
        return;
    }
    
    unlockEntry();
    
    if (pEntry->retainCount()!=0)
    {
        CC_SAFE_RELEASE_NULL(m_pLockedEntry);
        CC_SAFE_RETAIN(pEntry);
        m_pLockedEntry = pEntry;
        pEntry->setSelect(true);
        m_nLastLockedTag = pEntry->getTag();
        
        updataContentOffset();
    }
}

void MB_ActivatyMgr::updataContentOffset()
{
    

    
    
//    if(m_pScrollview && m_pLockedEntry)
//    {
//        CCSize viewSize = m_pScrollview->getViewSize();
//        CCSize conSize = m_pScrollview->getContentSize();
//        
//        float fx = m_pLockedEntry->getPositionX();
//        if(viewSize.width < conSize.width)
//        {
//            if(fx > viewSize.width/2 && fx < conSize.width - viewSize.width/2)
//            {
//                CCPoint pt = m_pScrollview->getContentOffset();
//                pt.x =  viewSize.width/2 - fx;
//                m_pScrollview->setContentOffsetInDuration(pt,.5);
//            }
//            else if(fx > conSize.width - viewSize.width/2)
//            {
//                CCPoint pt = m_pScrollview->getContentOffset();
//                pt.x =  viewSize.width - conSize.width;
//                m_pScrollview->setContentOffsetInDuration(pt,.5);
//            }
//            else
//            {
//                CCPoint pt = m_pScrollview->getContentOffset();
//                pt.x =  0;
//                m_pScrollview->setContentOffsetInDuration(pt,.5);
//            }
//        }
//    }
}

void MB_ActivatyMgr::unlockEntry()
{
    if (m_pLockedEntry)//if(m_pLockedEntry)m_pLockedEntry->release();
    {
        m_pLockedEntry->setSelect(false);
        CC_SAFE_RELEASE_NULL(m_pLockedEntry);
    }
}

void MB_ActivatyMgr::reset()
{
    unlockEntry();
}
MB_ActivatyMgr::MB_ActivatyMgr()
{
    m_pLockedEntry = NULL;
    m_nLastLockedTag = -1;
    m_pScrollview = NULL;
}
MB_ActivatyMgr::~MB_ActivatyMgr()
{
    unlockEntry();
    CC_SAFE_RELEASE_NULL(m_pLockedEntry);
}