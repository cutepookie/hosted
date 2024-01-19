//
//  MB_LayerServerContainer.cpp
//  ProjectMB
//
//  Created by wenyong on 14-8-28.
//
//

#include "MB_LayerServerContainer.h"
#include "MB_FunctionModule.h"
#include "MB_NodeServerItem.h"

MB_LayerServerContainer* MB_LayerServerContainer::create(uint16_t begin, uint16_t end)
{
    MB_LayerServerContainer* pInstance = new MB_LayerServerContainer;
    if (pInstance && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->resetRange(begin, end);
        return pInstance;
    }
    
    return NULL;
}

void MB_LayerServerContainer::resetRange(uint16_t begin, uint16_t end)
{
    int total = end - begin;
    
    removeAllChildren(); // aways remove all children
    
    if (total<0 || begin < 1)
    {
        return;
    }
    
    CCSize sz = MB_NodeServerItem::getWndSize();
    
    CCSize content_size = CCSizeMake(0, 0);
    
    int number = ((total%2) == 0) ? (total/2) : ((total/2)+1);
    
    content_size.height = sz.height * number;
    content_size.width = sz.width * 2;
    
    setContentSize(content_size);
    
    int server_count = MB_ServerList::getInstance()->getServerListCount();
    ServerList* pList = MB_ServerList::getInstance()->getServerList();
    if (pList == NULL)
    {
        return;
    }
    
    CCNode* pNode = NULL;
    
    float y = content_size.height;
    float x = 0;
    
    int index = 0;
    
    for (uint16_t i=begin; (i<=end)&&(i<=server_count); ++i)
    {
        pNode = MB_NodeServerItem::create(pList[i-1].serverID, pList[i-1].name.c_str(),pList[i-1].serverStatus);
        if (pNode)
        {
            addChild(pNode);
            
            if (index%2==0)
            {
                y -= sz.height;
                x = 0;
            }
            else
            {
                x = sz.width;
            }
            pNode->setPosition(x,y);
            ++index;
        }
    }
}