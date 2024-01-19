//
//  MB_MailMsgFile.h
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#ifndef __ProjectMB__MB_MailMsgFile__
#define __ProjectMB__MB_MailMsgFile__


#include "MB_ClientData.h"
#include "cocos2d.h"
#include <sys/stat.h>
#include "MB_MailMsgFile.h"
#include "MB_RoleData.h"
#include "MB_MailMsgData.h"
#include <unistd.h>
USING_NS_CC;




template<class T>
class MB_SaveMsgFile:public CCObject
{
public:
    MB_SaveMsgFile()
    {
        m_nRoleID = 0;
        m_nTargetID = 0;
        m_pUserEmailArray = new CCArray();
    }
    
    virtual ~MB_SaveMsgFile()
    {
        CC_SAFE_RELEASE_NULL(m_pUserEmailArray);
    }
    
    static MB_SaveMsgFile<T>* create(uint32_t roleId,uint32_t targetId)
    {
        MB_SaveMsgFile<T>* ptr = new MB_SaveMsgFile<T>;
        if (ptr && ptr->init(roleId, targetId))
        {
            ptr->autorelease();
            return ptr;
        }
        CC_SAFE_RELEASE(ptr);
        return NULL;
    }
    virtual bool init(uint32_t roleId,uint32_t targetId)
    {
        m_nRoleID = roleId;
        m_nTargetID = targetId;
        char filename[400];
        sprintf(filename,"%sMsgCache/%d/%d.cb",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),m_nRoleID,m_nTargetID);
        MB_XmlFile* pFile = MB_XmlFile::create(filename);
        if (pFile)
        {
            CCArray* pArray = CCArray::create();
            m_pUserEmailArray->removeAllObjects();
            if(pFile->queryNodesByName("Msgs|Msg", pArray))
            {
                MB_XmlNode* pNode = NULL;
                MB_SaveMsgData* pData = NULL;
                CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
                {
                    pData = new T();
                    if (pData->init(pNode))
                    {
                        m_pUserEmailArray->addObject(pData);
                    }
                    pData->release();
                }
            }
            pArray->removeAllObjects();
            if(pFile->queryNodesByName("Msgs", pArray))
            {
                MB_XmlNode* pNode = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
                if (pNode)
                {
                    pNode->queryAttributeByName("name");
                }
            }
        }
        
        return true;
    }
    
    CCArray* getUserEmailArray(){return m_pUserEmailArray;};
    
    void saveFile(uint32_t roleId,uint32_t targetId)
    {
        char fileLocal[1024];
        char fileLocal2[1024];
        char filename[1024];
        sprintf(fileLocal,"%sMsgCache",CCFileUtils::sharedFileUtils()->getWritablePath().c_str());
        sprintf(fileLocal2,"%sMsgCache/%d",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),roleId);
        sprintf(filename,"%sMsgCache/%d/%d.cb",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),roleId,m_nTargetID);
        
        int ret = access(fileLocal, F_OK);
        if(ret != 0)
        {
            int ret3 = mkdir(fileLocal, S_IRWXU | S_IRWXG | S_IRWXO);
            if (ret3 != 0)
            {
                return;
            }
        }
        int ret2 = access(fileLocal2, F_OK);
        if(ret2 != 0)
        {
            int ret3 = mkdir(fileLocal2, S_IRWXU | S_IRWXG | S_IRWXO);
            if (ret3 != 0)
            {
                return;
            }
        }
        
        xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
        xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"Msgs");
        xmlDocSetRootElement(doc,root_node);
        xmlNewProp(root_node,BAD_CAST"name",BAD_CAST m_szName.c_str());
        for (int i = 0; i < m_pUserEmailArray->count(); i++)
        {
            xmlNodePtr node = xmlNewNode(NULL,BAD_CAST"Msg");
            ((MB_SaveMsgData*)(m_pUserEmailArray->objectAtIndex(i)))->saveEmail(node);
            xmlAddChild(root_node,node);
        }
        
        int size;
        xmlChar* buff = new xmlChar[800];
        xmlDocDumpMemory(doc,&buff,&size);
        
        MB_Aescypt::encrypt_xmlstream2file((char*)buff,size,filename);
    }
    
    uint32_t getTargetID(){return m_nTargetID;};
private:
    CCArray* m_pUserEmailArray;
    uint32_t m_nRoleID;
    uint32_t m_nTargetID;
    CC_SYNTHESIZE(std::string, m_szName, Name);
};

#endif /* defined(__ProjectMB__MB_MailMsgFile__) */
