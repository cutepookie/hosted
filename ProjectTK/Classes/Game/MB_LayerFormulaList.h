//
//  MB_LayerFormulaList.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#ifndef __ProjectMB__MB_LayerFormulaList__
#define __ProjectMB__MB_LayerFormulaList__

#include "Game.h"

class MB_LayerFormulaList:public MB_ResWindow
{
public:

    MB_LayerFormulaList();

    virtual ~MB_LayerFormulaList();

    static MB_LayerFormulaList* create(const CCSize& sz);

    virtual bool init(const CCSize& sz);

    virtual void onResetWnd();
    
    virtual void resetList();

    static bool sortFormulaArray(const CCArray* pArray,std::vector<MB_ItemData*>& result);

protected:
    static bool sortFunction(MB_ItemData* first,MB_ItemData* second);
private:
    CC_SYNTHESIZE_READONLY(uint32_t, m_nCount, Count);
    CCSize          m_szListSize;
    
    CCLayer*        m_pListLayer;
};

#endif /* defined(__ProjectMB__MB_LayerFormulaList__) */
