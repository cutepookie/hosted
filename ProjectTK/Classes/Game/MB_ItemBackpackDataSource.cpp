//
//  MB_ItemBackpackDataSource.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#include "MB_ItemBackpackDataSource.h"
#include "MB_ItemData.h"
#include "MB_LayerPicDeploy.h"
#include "MB_LayerBackpack.h"
MB_ItemBackpackDataSource::MB_ItemBackpackDataSource()
{
	isAllRun = true;
	m_pItemArray = NULL;
	m_szCell = CCSize(640, 140);
}

MB_ItemBackpackDataSource::~MB_ItemBackpackDataSource()
{

}

CCSize MB_ItemBackpackDataSource::tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
    if (allCellCount-1==idx) {
        return m_szCell+CCSize(0,LASTCELLADDHEIGHT);
    }
    return m_szCell;
};

CCTableViewCell* MB_ItemBackpackDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell *cell = table->dequeueCell();
	if (cell == NULL)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
	}
	else
	{
		cell->removeAllChildren();
	}
	CCLayer* layer = CCLayer::create();
	layer->setContentSize(m_szCell);

	for (int i = idx*PERLINEITEM; i < (idx + 1)*PERLINEITEM && i < m_pItemArray->count(); i++)
	{
		MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemArray->objectAtIndex(i));
		if (itemData == NULL)
		{
			return cell;
		}
		MB_NodeItem* nodeIcon = MB_NodeItem::create(itemData->getItemUID());
        if (allCellCount-1==idx) {
            nodeIcon->setPosition(ccp(m_szCell.width/PERLINEITEM*(i%PERLINEITEM)*0.93f + 74, m_szCell.height/2+15+LASTCELLADDHEIGHT));
        }else
        {
            nodeIcon->setPosition(ccp(m_szCell.width/PERLINEITEM*(i%PERLINEITEM)*0.93f + 74, m_szCell.height/2+15));
        }
		layer->addChild(nodeIcon);
	}
	cell->addChild(layer);
	bool isContains = false;
	for (int i = 0; i<isRunedIdx.size(); i++) {
		if (isRunedIdx[i] == idx) {
			isContains = true;
			break;
		}
	}

	if (isAllRun || !isContains)
	{
		if (isAllRun&&idx>7) {
            return cell;
        }
        isRunedIdx.push_back(idx);
        if (global_layerBackpack!=NULL&&global_layerBackpack->isAnimation) {
            if (isAllRun) {
                NSGameHelper::runMoveAndOptAction(layer, idx*actionSpanTime, actionMoveTime, true, true);
            }
            else
            {
                NSGameHelper::runMoveAndOptAction(layer, 0, actionMoveTime, true, true);
            }
        }
    }
    return cell;
}

unsigned int MB_ItemBackpackDataSource::numberOfCellsInTableView(CCTableView *table)
{
	if (m_pItemArray == NULL) {
		m_pItemArray = MB_ItemMgr::getInstance()->getOtherArray();
        allCellCount =m_pItemArray->count()/PERLINEITEM + ((m_pItemArray->count()%PERLINEITEM) == 0? 0:1);
    }
    return allCellCount;
}
