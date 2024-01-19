
#include "MB_TutorialMgr.h"
#include "MB_FunctionMgr.h"
#include "MB_ServerRewardData.h"
#include <algorithm>
#include "MB_LayerChapterWnd.h"
#include "MB_AbsolvedInterface.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_FunctionModule.h"
#include "MB_LayerAbsolvedPage.h"
USING_NS_CC;
USING_NS_CC_EXT;


MB_TutorialMgr* s_pTutorialMgr = NULL;

MB_TutorialMgr::MB_TutorialMgr()
{
    m_bSkipTutorial = false;
    m_pData = new CCArray();
    m_pTemplete = new CCArray();
    m_nCurPart = 0;
    m_nMaxPart = 0;
    m_nMaxID = 0;
    m_bHasTutorialDilog = false;
    initTemplete();
    
    SOCKET_MSG_REGIST(SC_ROLE_SET_GUIDE_STATE, MB_TutorialMgr);
    SOCKET_MSG_REGIST(SC_ROLE_GET_GUIDE_STATE, MB_TutorialMgr);
}

MB_TutorialMgr::~MB_TutorialMgr()
{
    CC_SAFE_RELEASE_NULL(m_pData);
    CC_SAFE_RELEASE_NULL(m_pTemplete);
    
    SOCKET_MSG_UNREGIST(SC_ROLE_GET_GUIDE_STATE);
    SOCKET_MSG_UNREGIST(SC_ROLE_SET_GUIDE_STATE);
}

MB_TutorialMgr* MB_TutorialMgr::getInstance()
{
    if (s_pTutorialMgr == NULL) {
        s_pTutorialMgr = new MB_TutorialMgr();
    }
    return s_pTutorialMgr;
}

void MB_TutorialMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pTutorialMgr);
    s_pTutorialMgr = NULL;
}


bool MB_TutorialMgr::initTemplete()
{
    MB_XmlFile* pXml = MB_XmlFile::create("config/tutorial/tutorial.xml");
//    MB_XmlFile* pXml = MB_XmlFile::create("/Users/chenhongkun/Desktop/Project/trunk/gdwork/config/tutorial/tutorial.xml");
    if (pXml == NULL)return false;
    
    CCArray* pArray = CCArray::create();
    if(!pXml->queryNodesByName("tutorials|tutorial", pArray))
    {
        return false;
    }
    
    m_pTemplete->removeAllObjects();
    MB_XmlNode* pTemp = NULL;

    int id = 0;
    CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
    {
        MB_TutorialTemplete* pdata = new MB_TutorialTemplete;
        pdata->setID(++id);
        if (pdata->init(pTemp))
        {
            MB_TutorialTemplete* preTemp = getTempleteByID(pdata->getID() - 1);
            if(preTemp)
            {
                
                preTemp->setCellIndex(pdata->getCellIndex());
//                if(preTemp->getCellIndex() != 0)
//                {
//                    CCLOG("%d %d %d %d",preTemp->getID(), preTemp->getPart(),preTemp->getTagID(),preTemp->getCellIndex());
//                }
                
//                preTemp->setGataOpenSkip(pdata->getGataOpenSkip());
                preTemp->setFunId(pdata->getFunId());
            }

            if(m_nMaxID < pdata->getID())m_nMaxID = pdata->getID();
            if(m_nMaxPart < pdata->getPart())m_nMaxPart = pdata->getPart();

            if(std::find(m_LevelUpGoHomeLevels.begin(), m_LevelUpGoHomeLevels.end(),
                         pdata->getRoleLevel()) ==  m_LevelUpGoHomeLevels.end())
            {
                m_LevelUpGoHomeLevels.push_back(pdata->getRoleLevel());
            }
            
            m_pTemplete->addObject(pdata);
        }
        CC_SAFE_RELEASE_NULL(pdata);
    }
    return true;
}

bool MB_TutorialMgr::getRoleLevelUpGoHome()
{
    if(MB_TutorialMgr::getInstance()->getSkipTutorial())return false;
    
    for (int i = 0; i<m_LevelUpGoHomeLevels.size(); ++i)
    {
        if(m_LevelUpGoHomeLevels[i] == MB_RoleData::getInstance()->getLevel())
        {
            return true;
        }
    }
    return false;
}

int MB_TutorialMgr::GataOpenSkip()
{
    MB_TutorialTemplete* pCur = getTempleteByID(m_curID);
    if(pCur && pCur->getGataOpenSkip())
    {
        if(dynamic_cast<MB_LayerChapterWnd*>(CCFunctionInterface::getCurrentFunctionWnd())||dynamic_cast<MB_LayerAbsolvedPage*>(CCFunctionInterface::getCurrentFunctionWnd()))
        {
            return pCur->getGataOpenSkip();
        }
    }
    
    return 0;
}

bool MB_TutorialTemplete::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)return false;
    
//    m_nID = pNode->queryAttributeByName("id")->intValue();
    m_nPart = pNode->queryAttributeByName("part")->intValue();
    m_nType = pNode->queryAttributeByName("type")->intValue();
    m_nTagID = pNode->queryAttributeByName("tagid")->intValue();
    m_nRoleLevel = pNode->queryAttributeByName("rolelevel")->intValue();
    m_strText = pNode->queryAttributeByName("text")->getCString();
    m_nSoundID = pNode->queryAttributeByName("sound")->intValue();
    
    m_bCompleteNode = pNode->queryAttributeByName("comp")->intValue();
    m_nCellIndex = pNode->queryAttributeByName("cellIndex")->intValue();
    m_bGataOpenSkip = pNode->queryAttributeByName("gataOpenSkip")->intValue();
    m_Gohome = pNode->queryAttributeByName("gohome")->intValue();
    m_nFunId= pNode->queryAttributeByName("funid")->intValue();

    return true;
}

void MB_TutorialMgr::SetModelDilogState(std::string key,bool value)
{
    m_ModelDilogMap[key] = value;
}

bool MB_TutorialMgr::HasModelDilog()
{
    std::map<std::string,bool>::iterator it = m_ModelDilogMap.begin();
    for (; it!=m_ModelDilogMap.end(); ++it)
    {
        if(it->second)
        {
            return true;
        }
    }
    return false;
}

int MB_TutorialMgr::getCellIndex()
{
    MB_TutorialTemplete* pCur = getTempleteByID(m_curID - 1);
    if(pCur && pCur->getCellIndex()!=0)
    {
        return pCur->getCellIndex()-1;
    }
    return 0;
}

NSGameFunction::FunctionType MB_TutorialMgr::getFunID()
{
    MB_TutorialTemplete* pCur = getTempleteByID(m_curID - 1);
    if(pCur && pCur->getFunId() != 0)
    {
        return (NSGameFunction::FunctionType)pCur->getFunId();
    }
    return (NSGameFunction::FunctionType)0;
}

bool MB_TutorialMgr::initData()
{
    m_curID = -1;
    m_pData->removeAllObjects();
    
    bool bMakeCurID = false;
    for (int i = 0; i < m_pTemplete->count(); ++i)
    {
        MB_TutorialTemplete* templete = (MB_TutorialTemplete*)m_pTemplete->objectAtIndex(i);
        MB_TutorialData* data = new MB_TutorialData();
        data->setTypeID(templete->getID());
        data->setIsPassed(false);
        
        //当前阶段第一个节点
        if(!bMakeCurID && templete->getPart() == (m_nCurPart+1))
        {
            bMakeCurID = true;
            int idTemp = templete->getID() - 1;
            if(m_curID < idTemp)m_curID = idTemp;
        }
        
        m_pData->addObject(data);
        data->release();
    }
    
    if(m_curID == -1)
    {
        m_curID = m_nMaxID;
        m_nCurPart = m_nMaxPart;
        m_bSkipTutorial = true;
    }
    
    for (int i = 0; i < m_pData->count(); i++)
    {
        MB_TutorialData* data = (MB_TutorialData*)m_pData->objectAtIndex(i);
        MB_TutorialTemplete* templete = getTempleteByID(data->getTypeID());
        
        if (templete == NULL)
        {
            MB_LOG("not find tutorial id:%d",data->getTypeID());
            return true;
        }
        
        data->setIsPassed(templete->getID() <= m_curID);
    }
    return true;
}

bool MB_TutorialMgr::getCompletePveGoHome()
{
    MB_TutorialTemplete* pTemp = getTempleteByID(m_curID - 1);
    if(pTemp && pTemp->getGohome() && !m_bSkipTutorial)
    {
        return true;
    }
    return false;
}


bool MB_TutorialMgr::isPassed(int typeID)
{
    for (int i = 0; i < m_pData->count(); ++i)
    {
        MB_TutorialData* data = (MB_TutorialData*)m_pData->objectAtIndex(i);
        if (data->getTypeID() == typeID)
        {
            return data->getIsPassed();
        }
    }
    return true;
}

void MB_TutorialMgr::skipTutorial()
{
    TutorialForcedTrigpetComplete
    m_bSkipTutorial = true;
    for (int i = 0; i < m_pData->count(); ++i)
    {
        MB_TutorialData* data = (MB_TutorialData*)m_pData->objectAtIndex(i);
        data->setIsPassed(true);
    }
    m_curID = m_nMaxPart;
    sendrole_set_guide_state(m_curID);
    sendrole_log_guide_state(m_nMaxID);
}


void MB_TutorialMgr::trigpetComplete()
{
    for (int i = 0; i < m_pData->count(); ++i)
    {
        MB_TutorialData* data = (MB_TutorialData*)m_pData->objectAtIndex(i);
        if (data->getTypeID() == m_curID)
        {
            data->setIsPassed(true);
            MB_TutorialTemplete* templete = getTempleteByID(m_curID);
            sendrole_log_guide_state(templete->getID());
            if (templete->getIsCompleteNode())
            {
                sendrole_set_guide_state(templete->getPart());
            }
            CCNode* pNode = CCDirector::sharedDirector()->getRunningScene();
            if(pNode)
            {
                pNode->removeChildByTag(templete->getTagID());
            }
            m_bHasTutorialDilog = false;
            global_tutorialNode = NULL;
            char buff[100] = {0};

            sprintf(buff, "引导完成:%d %d",m_nCurPart,templete->getTagID());
            MB_LOG("%s",buff);
            m_nCurPart = m_nCurPart < templete->getPart()?templete->getPart():m_nCurPart;
            ++m_curID;
            
            m_bSkipTutorial = m_curID>=m_nMaxID;
            return;
        }
    }
    
//    MB_LOG("can't find tutorial typeid:%d", m_curID);
}

bool MB_TutorialMgr::canTrigpetByTypeID(int typeID)
{
    if(HasModelDilog())
    {
        MB_TutorialTemplete* templete = getTempleteByID(m_curID);
        if(templete)
        {
            CCNode* pNode = CCDirector::sharedDirector()->getRunningScene();
            if(pNode)
            {
                if(pNode->getChildByTag(templete->getTagID()))
                {
                    pNode->removeChildByTag(templete->getTagID());
                }
            }
        }
        
        m_bHasTutorialDilog = false;
        return false;
    }
    
    if(getHasTutorialDilog())return false;
    
    //已经引导过的id
    if (isPassed(typeID)) {
        return false;
    }
    
    MB_TutorialTemplete* templete = getTempleteByID(typeID);
    //不存在此模板
    if (templete == NULL) {
        MB_LOG("unkown tutorial id:%d", typeID);
        return false;
    }
    
    //前置引导是否完成
    if (isPassed(templete->getID() - 1) == false)
    {
        return false;
    }

    
    //等级是否满足条件
    if (templete->getRoleLevel() > MB_RoleData::getInstance()->getLevel())
    {
        return false;
    }
    
    m_curID = typeID;
    
    char buff[100] = {0};
    sprintf(buff, "开始引导:%d %d",m_nCurPart,templete->getTagID());
    MB_LOG("%s",buff);
    
    return true;
}


bool MB_TutorialMgr::canTrigpetByTagID(int tagID)
{
    MB_TutorialTemplete* templete = NULL;
    for (int i = 0; i < m_pTemplete->count(); ++i)
    {
        templete = (MB_TutorialTemplete*)m_pTemplete->objectAtIndex(i);
        if (templete->getTagID() == tagID)
        {
            if (canTrigpetByTypeID(templete->getID()))
            {
                return true;
            }
        }
    }
    
    return false;
}

MB_TutorialTemplete* MB_TutorialMgr::getTempleteByID(int typeID)
{
    MB_TutorialTemplete* templete = NULL;
    for (int i = 0; i < m_pTemplete->count(); ++i)
    {
        templete = dynamic_cast<MB_TutorialTemplete*>(m_pTemplete->objectAtIndex(i));
        if (templete && templete->getID() == typeID)
        {
            return templete;
        }
    }
    return NULL;
}


void MB_TutorialMgr::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_ROLE_SET_GUIDE_STATE:
            recvrole_set_guide_state(recvPacket);
            break;
        case SC_ROLE_GET_GUIDE_STATE:
            recvrole_get_guide_state(recvPacket);
            break;
            
        default:
            break;
    }
}

bool MB_TutorialMgr::sendrole_get_guide_state()
{
    SOCKET_REQUEST_START(CS_ROLE_GET_GUIDE_STATE);
    SOCKET_REQUEST_END(SC_ROLE_GET_GUIDE_STATE, MB_TutorialMgr::onMsgRecv);
    return true;
}

bool MB_TutorialMgr::recvrole_get_guide_state(MB_MsgBuffer *recvPacket)
{
    uint16_t data16 = 0;//新手引导阶段ID
    if (recvPacket->readU16(&data16))
    {
        if(MB_RoleData::getInstance()->getLevel() > 1 && data16 == 0)
        {
            data16 = m_curID = m_nMaxID;
            m_nCurPart = m_nMaxPart;
            m_bSkipTutorial = true;
        }
        
        setCurPart(data16);

        initData();
        return true;
    }
    return false;
}

bool MB_TutorialMgr::sendrole_set_guide_state(uint16_t status)
{
    SOCKET_REQUEST_START(CS_ROLE_SET_GUIDE_STATE);
    packet->writeU16(status);
    SOCKET_REQUEST_END(SC_ROLE_SET_GUIDE_STATE, MB_TutorialMgr::onMsgRecv);
    return true;
}

bool MB_TutorialMgr::sendrole_log_guide_state(uint16_t id)
{
    SOCKET_REQUEST_START(CS_ROLE_LOG_GUIDE_STATE);
    packet->writeU16(id);
    SOCKET_REQUEST_END(CS_ROLE_LOG_GUIDE_STATE, MB_TutorialMgr::onMsgRecv);
    return true;
}

bool MB_TutorialMgr::recvrole_set_guide_state(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    if (recvPacket->readU8(&result))
    {
        if (result == 1)
        {
            return true;
        }
        else
        {
            MB_LOG("tutorial status errcode:%d", result);
        }
    }
    
    return true;
}
