
//

#include "MB_ActionData.h"

MB_ActionData* MB_ActionData::s_pData = NULL ;

void MB_ActionData::initActions(){

    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/action/battle_action.xml");
    
    if (!g_sharedDoc)
    {
        return ;
    }
    
    xmlNodePtr root;
    
    root = xmlDocGetRootElement(g_sharedDoc);
        
    for (  xmlNodePtr child = root->xmlChildrenNode ; child != NULL  ; child = child->next ) {
        
        if (xmlStrcmp(child->name,BAD_CAST "action")) {
      
            continue;
        }
    
        MB_Action * action = (MB_Action *) malloc(sizeof(MB_Action));
        action->speffect = NULL;
        strcpy(action->actionFlipName,"");
        
        for (struct _xmlAttr * attXml = child->properties; attXml != NULL; attXml = attXml->next ) {
            
            if (!xmlStrcmp(attXml->name,BAD_CAST "actionID")) {
                
                char * value = (char*)xmlNodeGetContent(attXml->children);                
                int actionID = atoi(value);                
                action->actionID = actionID;                
                free(value);
                
            }
            else if (!xmlStrcmp(attXml->name,BAD_CAST "actionName")) {
                
                char * value = (char*)xmlNodeGetContent(attXml->children);
                strcpy(action->actionName,value);
                free(value);
                
            } else if (!xmlStrcmp(attXml->name,BAD_CAST "actionFlipName")) {
                
                char * value = (char*)xmlNodeGetContent(attXml->children);
                strcpy(action->actionFlipName,value);
                free(value);
                
            }else if (!xmlStrcmp(attXml->name,BAD_CAST "actionType")) {
                
                char * value = (char*)xmlNodeGetContent(attXml->children);                
                action->actionType = atoi(value);                
                free(value);
                
                
            } 
            else if (!xmlStrcmp(attXml->name,BAD_CAST "actionTime")) {
                
                char * value = (char*)xmlNodeGetContent(attXml->children);                
                action->actionTime = atof(value);                
                free(value);
                
            }
            else if (!xmlStrcmp(attXml->name,BAD_CAST "moveTime")) {

                char * value = (char*)xmlNodeGetContent(attXml->children);
                action->moveTime = atof(value);
                free(value);

            }
            else if (!xmlStrcmp(attXml->name,BAD_CAST "moveType")) {

                char * value = (char*)xmlNodeGetContent(attXml->children);
                action->moveType = atoi(value);
                free(value);

            }
            //action->actionTime *= 0.5;
//            if (action->moveTime > 0.00001)
//            {
//                action->moveTime = 0.1;
//            }

        }
        //CCLog("-------ActionID:%d moveType:%f-------\n",action->actionID,action->moveTime);
    
        MB_ActionEffect *moveeff = NULL;        
        for ( xmlNodePtr effectChild = child ->xmlChildrenNode; effectChild != NULL; effectChild = effectChild->next ) {
            
            if (xmlStrcmp(effectChild->name, BAD_CAST "speffect") && xmlStrcmp(effectChild->name, BAD_CAST "effect")) {
                
                continue;
            }
            if(xmlStrcmp(effectChild->name, BAD_CAST "speffect") == 0){
            
                
                MB_ActionEffect*  tempeeff = (MB_ActionEffect *) malloc(sizeof(MB_ActionEffect));
                tempeeff->flipType = 0;
                for (struct _xmlAttr * attXml = effectChild->properties; attXml != NULL; attXml = attXml->next ) {
                    
                    if (!xmlStrcmp(attXml->name,BAD_CAST "effectName")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        strcpy( tempeeff->effectName, value);
                        free(value);
                        
                    }
                    else if (!xmlStrcmp(attXml->name,BAD_CAST "effectTime")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->effectTime = atof(value);
                        free(value);
                        
                    }
                    else if (!xmlStrcmp(attXml->name,BAD_CAST "sound")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        strcpy(tempeeff->sound,value);
                        free(value);
                        
                    }
                    else if (!xmlStrcmp(attXml->name,BAD_CAST "ccbirate")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->effectType =  atoi(value);//特殊動画里面表示概率
                        free(value);
                        
                    }
                }
                action->speffect = tempeeff;
                
            }else {
            
            
                MB_ActionEffect*  tempeeff = (MB_ActionEffect *) malloc(sizeof(MB_ActionEffect));
                tempeeff->flipType = 0;
                tempeeff->next = NULL;
                
                for (struct _xmlAttr * attXml = effectChild->properties; attXml != NULL; attXml = attXml->next ) {
                    
                    if (!xmlStrcmp(attXml->name,BAD_CAST "effectName")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        strcpy( tempeeff->effectName, value);
                        free(value);
                        
                    }
                    else if (!xmlStrcmp(attXml->name,BAD_CAST "effectStartTime")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->effectStartTime = atof(value);
                        free(value);
                        
                    } else if (!xmlStrcmp(attXml->name,BAD_CAST "effectTime")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->effectTime = atof(value);
                        free(value);
                        
                    }
                    else if (!xmlStrcmp(attXml->name,BAD_CAST "effectType")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->effectType = atoi(value);
                        free(value);
                        
                    }else if (!xmlStrcmp(attXml->name,BAD_CAST "sound")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        strcpy(tempeeff->sound,value);
                        free(value);
                        
                    }else if (!xmlStrcmp(attXml->name,BAD_CAST "flipType")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->flipType = atoi(value);
                        free(value);
                    }
                    else if (!xmlStrcmp(attXml->name,BAD_CAST "actionturnmove")) {
                        
                        char * value = (char*)xmlNodeGetContent(attXml->children);
                        tempeeff->turnMove = atoi(value);
                        free(value);
                    }
                }
                
                if (moveeff == NULL) {
                    
                    action->effect  = moveeff = tempeeff;
                    
                }else{
                    
                    moveeff->next = tempeeff;                
                    moveeff = tempeeff;
                    
                }
            }
        }
        
        m_mapAction.insert(std::pair< uint8_t, MB_Action *>(action->actionID , action));

    }
     
    xmlFreeDoc(g_sharedDoc);
    
    return ;

}

MB_ActionData::MB_ActionData(){
  
}
MB_ActionData::~MB_ActionData(){

    std::map <uint8_t, MB_Action*>::iterator it = m_mapAction.begin();
    std::map <uint8_t, MB_Action*>::iterator end = m_mapAction.end();
    while (it!=end)
    {
        if (it->second)
        {
            if (it->second->effect)
            {
                free(it->second->effect);
                it->second->effect = NULL;
            }
            if (it->second->speffect)
            {
                free(it->second->speffect);
                it->second->speffect = NULL;
            }
            free(it->second);
            ++it;
        }
        
    }
    m_mapAction.clear();
}

MB_ActionData * MB_ActionData::getInstance(){
    
    if(s_pData == NULL ){
    
        s_pData =new MB_ActionData();
        s_pData->initActions();
        
    }
    return  s_pData;

}
void MB_ActionData::destroyInstance(){
    
    delete s_pData;
    
    s_pData = NULL;

}
MB_Action *MB_ActionData::getActionByID(uint8_t actionId){

    std::map<uint8_t, MB_Action *> ::iterator actionIterator = m_mapAction.find(actionId);
    if ( actionIterator != m_mapAction.end()) {
        return actionIterator->second;
    }
    else
    {
        if (actionId > 100)
        {
            MB_Action * action = (MB_Action *) malloc(sizeof(MB_Action));
            action->actionID = actionId;
			action->moveTime = 0;
			action->actionTime = 0;
			action->moveType = 0;
			action->actionType = 0;
            m_mapAction.insert(std::pair< uint8_t, MB_Action *>(actionId , action));
            action->effect = NULL;
            action->speffect = NULL;
            return action;
        }
        MB_LOG("ID:%d action not exist.", actionId);
        return  NULL;
    }
}

void MB_ActionData::testActionCcbFiles()
{
    MB_ResWindow* pWindow = new MB_ResWindow;
    std::map<uint8_t, MB_Action*>::iterator it = m_mapAction.begin();
    std::map<uint8_t, MB_Action*>::iterator end = m_mapAction.end();
    
    int i = 0;
    std::string root = "res/";
    while (it != end)
    {
        CCLOG("载入:%s",it->second->effect->effectName);
        if(NULL == pWindow->loadResource((root+it->second->effect->effectName).c_str()))
        {
            CCLOG("无法载入得动作:%s",it->second->effect->effectName);
            ++i;
        }
        ++it;
    }
    if (i!=0)
    {
        CCLOG("一共有%d个动作无法加载,成功%d",i,m_mapAction.size()-i);
    }
    else
    {
        CCLOG("动作检查无误");
    }
    delete pWindow;
}
