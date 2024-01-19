//


#include "MB_MailData.h"
#include "MB_ItemData.h"
#include "MB_petData.h"
#include "MB_MailMainView.h"
#include "MB_GameInfoEnum.h"
#include "MB_RuleFightInterface.h"
#include "MB_SceneGame.h"
MB_MailData* s_pMailData = NULL;

MB_MailData::MB_MailData()
{
    for (int i = 0; i<kmMailsTable_Num; ++i){
        m_mailsTable[i] = new MB_MailsOperator();
        initData[i] = false;
        

    }
    
    SOCKET_MSG_REGIST(SC_MAIL_INFO,MB_MailData);
    SOCKET_MSG_REGIST(SC_MAIL_DRAW_REWARD,MB_MailData);
    SOCKET_MSG_REGIST(SC_MAIL_DELETE,MB_MailData);
    SOCKET_MSG_REGIST(SC_MAIL_NEW,MB_MailData);
    SOCKET_MSG_REGIST(SC_MAIL_UNREAD_NUM,MB_MailData);
//    SOCKET_MSG_REGIST(SC_MAIL_MORE,MB_MailData);
    SOCKET_MSG_REGIST(SC_HIST_GET_LIST,MB_MailData);
    SOCKET_MSG_REGIST(SC_HIST_MORE,MB_MailData);
    SOCKET_MSG_REGIST(SC_HIST_REPLAY,MB_MailData);
    SOCKET_MSG_REGIST(SC_HIST_UNREADNUM,MB_MailData);
//    SOCKET_MSG_REGIST(SC_MAIL_AGREE_FRIEND, MB_MailData);
    SOCKET_MSG_REGIST(SC_FRIEND_REMOVE_REQUEST, MB_MailData);
    
    
}

MB_MailData::~MB_MailData()
{
    SOCKET_MSG_UNREGIST(SC_MAIL_INFO);
    SOCKET_MSG_UNREGIST(SC_MAIL_DRAW_REWARD);
    SOCKET_MSG_UNREGIST(SC_MAIL_DELETE);
    SOCKET_MSG_UNREGIST(SC_MAIL_NEW);
    SOCKET_MSG_UNREGIST(SC_MAIL_UNREAD_NUM);
//    SOCKET_MSG_UNREGIST(SC_MAIL_MORE);
    SOCKET_MSG_UNREGIST(SC_HIST_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_HIST_MORE);
    SOCKET_MSG_UNREGIST(SC_HIST_REPLAY);
    SOCKET_MSG_UNREGIST(SC_HIST_UNREADNUM);
//    SOCKET_MSG_UNREGIST(SC_MAIL_AGREE_FRIEND);
    SOCKET_MSG_UNREGIST(SC_FRIEND_REMOVE_REQUEST);
    
    
    for (int i = 0; i<kmMailsTable_Num; ++i)
        CC_SAFE_RELEASE(m_mailsTable[i]);
}

MB_MailData* MB_MailData::getInstance()
{
    if (s_pMailData == NULL) {
        s_pMailData = new MB_MailData();
    }
    return s_pMailData;
}
void MB_MailData::destroyInstance()
{
    CC_SAFE_RELEASE(s_pMailData);
    s_pMailData = NULL;
}


void MB_MailData::onMsgRecv(cocos2d::CCNode *node, cocos2d::extension::SocketResponse *response)
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
    
    switch (Msg)
    {
    case SC_MAIL_INFO:
        recvmail_info(recvPacket);
        break;
    case SC_MAIL_DRAW_REWARD:
        recvmail_draw_reward(recvPacket);
        break;
    case SC_MAIL_DELETE:
        recvmail_delete(recvPacket);
        break;
    case SC_MAIL_NEW:
        recvmail_new(recvPacket);
        break;
    case SC_MAIL_UNREAD_NUM:
        recvmail_unread_num(recvPacket);
        break;
//    case SC_MAIL_MORE:
//        recvmail_more(recvPacket);
//        break;
    case SC_HIST_GET_LIST:
        recvhist_get_list(recvPacket);
        break;
    case SC_HIST_MORE:
        recvhist_more(recvPacket);
        break;
    case SC_HIST_REPLAY:
        recvhist_replay(recvPacket);
        break;
    case SC_HIST_UNREADNUM:
        recvhist_unreadNum(recvPacket);
        break;
//    case SC_MAIL_AGREE_FRIEND:
//        recvmail_agree_friend(recvPacket);
//        break;
    case SC_FRIEND_REMOVE_REQUEST:
        recvfriend_remove_request(recvPacket);
        break;
    default:
        break;
    };
}


int MB_MailData::queryMailTotalUnRead(void)
{
    int total = 0;
    for (int i = 0; i<kmMailsTable_Num; ++i)
        total += ((m_mailsTable[i]->getUnReadCount()));
    return total;
}

int MB_MailData::queryMailUnRead(kmMailsTable table)
{
    return (m_mailsTable[(int)table-1]->getUnReadCount());
}

void MB_MailData::removeMail(int64_t uid)
{
    for (int i = 0; i<kmMailsTable_Num; ++i)
        m_mailsTable[i]->remove(uid);
}

sMailCell* MB_MailData::queryMail(int64_t uid)
{
    sMailCell* ret = NULL;
    for (int i = 0; i<kmMailsTable_Num; ++i)
    {
        ret = m_mailsTable[i]->query(uid);
        if (ret)
        break;
    }
    return ret;
}

std::string MB_MailData::convertToRbfString(std::string str)
{
    return str;
}
std::string MB_MailData::queryMailTitle(int64_t uid)
{
    sMailCell* ret = queryMail(uid);
    return  GET_CONFIG_VALUE("email_description.xml",
                             ret->mailTemplateID ,
                             "title");
}
std::string MB_MailData::queryMailRbfContent(int64_t uid)
{
    std::string str = "";
    std::string temp;
    char tempChar[512];
    sMailCell* ret = queryMail(uid);
    
    if (ret)
    {
        str = ret->mailTemplateID != 0? \
              convertToRbfString(GET_CONFIG_VALUE("email_description.xml",
                               ret->mailTemplateID ,
                               "des")): \
              ret->content;
        
        str = ret->paramList.calculateNewRbfStrByOldRbfStr(str);
        if(kmMailType_PresonMail == ret->mailType)
        {
            temp = "[color=ff0000]" + ret->senderName + "[/color]";
            temp += "/n[color=ffffff]"+str  + "[/color]";
            str  = temp;
        }
        
        if (ret->mailType == kmMailType_Pvp)
        {
            if (ret->mailTemplateID == 80) //挑战胜利
            {
                sprintf(tempChar,str.c_str(),
                        ret->senderName.c_str(),ret->arg,ret->addRepu);
            }
            else if (ret->mailTemplateID == 16) //挑战失败

            {
                sprintf(tempChar,str.c_str(),
                        ret->senderName.c_str(),ret->addRepu);
            }
            else
            {
                sprintf(tempChar,str.c_str(),
                        ret->senderName.c_str(),ret->arg);
            }

            str = tempChar;
        }
        else if(ret->mailType == kmMailType_TreasureRob)
        {
            sprintf(tempChar,str.c_str(),
                    ret->senderName.c_str(),
                    ItemMgr->getItemNameByTid(ret->arg).c_str());
            str = tempChar;
        }
        
        KeyValue_It it;
        it = ret->mailReward.ItemRewards.begin();
        while (it != ret->mailReward.ItemRewards.end())
        {
            str += ItemMgr->getItemNameByTid(it->first);
            str += ":";
            sprintf(tempChar, "%d",it->second);
            str += tempChar;
            str += ";";
            it++;
        }
        
        it = ret->mailReward.PetRewards.begin();
        while (it != ret->mailReward.PetRewards.end())
        {
            MB_PetTemplate* pgt;
            pgt = MB_PetMgr::getInstance()->getPetTemplateByID(it->first);
            str += pgt?pgt->getPetName():"";
            str += ":";
            sprintf(tempChar, "%d",it->second);
            str += tempChar;
            str += ";";
            it++;
        }
    }
    return str;
}

kmMailsTable MB_MailData::queryMailTabel(int64_t uid)
{
    kmMailsTable ret = kmMailsTable_Preson;
    for (int i = 0; i<kmMailsTable_Num; ++i)
    {
        if(m_mailsTable[i]->query(uid))
        {
            ret = (kmMailsTable)(i+1);
            break;
        }
    }
    return ret;
}

MailList& MB_MailData::getMails(kmMailsTable table)
{
    return m_mailsTable[(int)table-1]->getMails();
}

//请求分页邮件列表
void MB_MailData::sendmail_info(kmMailsTable table)
{
    
    if (queryMailUnRead(table) >0 || initData[table-1] == false)
    {
        initData[table-1] = true;
        MailList& mailist = m_mailsTable[(int)table - 1]->getMails();
        SOCKET_REQUEST_START(CS_MAIL_INFO);
        packet->writeU8((unsigned char)table);
        packet->WriteUINT64(mailist.size()>0?mailist[0]->mailUID:0);
        SOCKET_REQUEST_END(SC_MAIL_INFO, MB_ItemMgr::onMsgRecv);
        PopupPauseMsgBox
    }
}


void MB_MailData::recvmail_info(MB_MsgBuffer* recvPacket)
{
    ClosePauseMsgBox
    uint8_t     data8;
    uint16_t    data16;
    recvPacket->readU8(&data8);
    if (1 == data8)
    {
        recvPacket->readU8(&data8);
        kmMailsTable table = (kmMailsTable)data8;
        CCAssert(table>0&&table<=kmMailsTable_Num, "table error！！！");
        bool isRemoveData;
        recvPacket->readU8(&data8);
        isRemoveData =  (data8 == 1);
        if (isRemoveData){
            
            m_mailsTable[(int)table-1]->removeAll();
        }

        m_mailsTable[(int)table-1]->insert(recvPacket);
        
        recvPacket->readU16(&data16);
        for(int i = 0;i<data16&&i<kmMailsTable_Num;++i)
        {
            recvPacket->readU8(&data8);
            m_mailsTable[i]->setUnReadCout(data8);
        }
     
    }
    else
    {
        switch (data8) {
            case 1:
                MB_Message::sharedMB_Message()->showMessage("成功");
                break;
            case 2:
                MB_Message::sharedMB_Message()->showMessage("类型错误");
                break;
            case 3:
                MB_Message::sharedMB_Message()->showMessage("没有最新的邮件");
                break;
            default:
                break;
        }
    }
}

//领取奖励邮件
void MB_MailData::sendmail_draw_reward(int64_t uid)
{
    SOCKET_REQUEST_START(CS_MAIL_DRAW_REWARD);
    packet->WriteUINT64(uid);
    m_currentMailUID = uid;
    SOCKET_REQUEST_END(SC_MAIL_DRAW_REWARD, MB_ItemMgr::onMsgRecv);
    PopupPauseMsgBox
}

void MB_MailData::recvmail_draw_reward(MB_MsgBuffer* recvPacket)
{
    ClosePauseMsgBox
    uint8_t     data8;
    recvPacket->readU8(&data8);
    MB_Message::sharedMB_Message()->removeALLMessage();
    if(data8  != 1 )
    {
        switch (data8)
        {
            case 1:
                MB_Message::sharedMB_Message()->showMessage("领取成功");
                break;
            case 2:
                MB_Message::sharedMB_Message()->showMessage("领取失败-该邮件不存在、或者已被领过了");
                break;
                
            default:
                break;
        }
    }
    removeMail(m_currentMailUID);

   
}

//删除邮件
void MB_MailData::sendmail_delete(int64_t uid)
{
    SOCKET_REQUEST_START(CS_MAIL_DELETE);
    packet->WriteUINT64(uid);
    packet->writeU8(queryMailTabel(uid));
    m_currentMailUID = uid;
    SOCKET_REQUEST_END(SC_MAIL_DELETE, MB_ItemMgr::onMsgRecv);
    PopupPauseMsgBox
}

void MB_MailData::recvmail_delete(MB_MsgBuffer* recvPacket)
{
    ClosePauseMsgBox
    uint8_t     data8;
    recvPacket->readU8(&data8);

    switch (data8) {
        case 1:
            MB_Message::sharedMB_Message()->showMessage("删除成功");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("删除失败-该邮件不存在");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("删除失败-该邮件不能删除");
            break;
            
        default:
            break;
    }
    removeMail(m_currentMailUID);
}

//写邮件
void MB_MailData::sendmail_new(sNewMail& newMailInfo)
{
    SOCKET_REQUEST_START(CS_MAIL_NEW);
    packet->writeU32(newMailInfo.targetID);
    //name
    if(newMailInfo.targetName == "")
    {
        packet->writeU16(0);
    }
    else
    {
        //packet->writeU16(newMailInfo.targetName.size());
        packet->Write(newMailInfo.targetName.c_str(),newMailInfo.targetName.size());
    }
    
    //content
    if(newMailInfo.content == "")
    {
        packet->writeU16(0);
    }
    else
    {
        //packet->writeU16(newMailInfo.content.size());
        packet->Write(newMailInfo.content.c_str(),newMailInfo.content.size());
    }
    SOCKET_REQUEST_END(SC_MAIL_NEW, MB_ItemMgr::onMsgRecv);
    PopupPauseMsgBox
}

void MB_MailData::recvmail_new(MB_MsgBuffer* recvPacket)
{
    
    ClosePauseMsgBox
    uint8_t     data8;
    recvPacket->readU8(&data8);
    SHOW_WND_TIPLite("send_mail_result.xml", data8);
    removeMail(m_currentMailUID);

}

//系统好友加入请求
void MB_MailData::sendmail_agree_friend(int64_t uid)
{
  
    SOCKET_REQUEST_START(CS_MAIL_AGREE_FRIEND);
    packet->WriteUINT64(uid);
    m_currentMailUID = uid;
    SOCKET_REQUEST_END(SC_MAIL_AGREE_FRIEND,MB_MailData::onMsgRecv);
    PopupPauseMsgBox
}

//void MB_MailData::recvmail_agree_friend(MB_MsgBuffer* recvPacket)
//{
//    ClosePauseMsgBox
//    uint8_t data8;
//    recvPacket->readU8(&data8);
//    SHOW_WND_TIPLite("mail_agree_friend_result.xml", data8);
//    removeMail(m_currentMailUID);
//}

//拒绝加好友请求成功 
void MB_MailData::recvfriend_remove_request(MB_MsgBuffer* recvPacket)
{
    ClosePauseMsgBox
    MB_Message::sharedMB_Message()->showMessage("拒绝成功");
    removeMail(m_currentMailUID);
}


//请求未读邮件个数
void MB_MailData::sendmail_unread_num(void)
{
    SOCKET_REQUEST_START(CS_MAIL_UNREAD_NUM);
    SOCKET_REQUEST_END(SC_MAIL_UNREAD_NUM, MB_ItemMgr::onMsgRecv);
}

void MB_MailData::recvmail_unread_num(MB_MsgBuffer* recvPacket)
{
    uint16_t data16;
    uint8_t  data8;
    recvPacket->readU16(&data16);
    for(int i = 0;i<data16&&i<kmMailsTable_Num;++i)
    {
        recvPacket->readU8(&data8);
        m_mailsTable[i]->setUnReadCout(data8);
    }
    
}

void MB_MailData::sendhist_get_list(kmMailsTable table)
{
    if (queryMailUnRead(table)>0 || initData[table-1] == false)
    {
        initData[table-1] = true;
//        MailList& mailist = m_mailsTable[(int)table - 1]->getMails();
        SOCKET_REQUEST_START(CS_HIST_GET_LIST);
        packet->writeU8((unsigned char)table);
//        packet->WriteUINT64(mailist.size()>0?mailist[0]->mailUID:0);
        SOCKET_REQUEST_END(SC_HIST_GET_LIST, MB_ItemMgr::onMsgRecv);
        PopupPauseMsgBox
    }
}

void MB_MailData::recvhist_get_list(MB_MsgBuffer *recvPacket)
{
    ClosePauseMsgBox
    uint8_t     data8;
    uint16_t    data16;

    recvPacket->readU8(&data8);
    kmMailsTable table = (kmMailsTable)data8;
    CCAssert(table>0&&table<=kmMailsTable_Num, "table error！！！");
    bool isRemoveData;
    recvPacket->readU8(&data8);
    isRemoveData = (bool)data8;
    if (isRemoveData)
        m_mailsTable[(int)table-1]->removeAll();
    
    m_mailsTable[(int)table-1]->insertHist(recvPacket);
    
    recvPacket->readU16(&data16);
    m_mailsTable[(int)table-1]->setUnReadCout(0);
  
}

void MB_MailData::sendhist_more(kmMailsTable table)
{
    CCAssert(table>0&&table<=kmMailsTable_Num, "table error！！！");
    MailList& mailist = m_mailsTable[(int)table - 1]->getMails();
    
    if (mailist.size()>0)
    {
        SOCKET_REQUEST_START(CS_HIST_MORE);
        packet->WriteUINT64(mailist[mailist.size()-1]->mailUID);
        packet->writeU8((unsigned char)table);
        SOCKET_REQUEST_END(SC_HIST_MORE, MB_ItemMgr::onMsgRecv);
        PopupPauseMsgBox
    }
}

void MB_MailData::recvhist_more(MB_MsgBuffer *recvPacket)
{
    ClosePauseMsgBox
    uint8_t data8;
    uint16_t data16;
    recvPacket->readU8(&data8);

    kmMailsTable table = (kmMailsTable)data8;
    CCAssert(table>0&&table<=kmMailsTable_Num, "table error！！！");
    
    m_mailsTable[(int)table-1]->insertHist(recvPacket);
    recvPacket->readU16(&data16);
    m_mailsTable[(int)table-1]->setUnReadCout(data16);
 
}

void MB_MailData::sendhist_replay(kmMailsTable table,uint64_t uid)
{

    m_nReplayID = uid;
    m_nTable = table;
    SOCKET_REQUEST_START(CS_HIST_REPLAY);
    packet->WriteUINT64(uid);
    packet->writeU8((unsigned char)table);
    SOCKET_REQUEST_END(SC_HIST_REPLAY, MB_ItemMgr::onMsgRecv);
    m_currentMailUID = uid;
    PopupPauseMsgBox
}

void MB_MailData::recvhist_replay(MB_MsgBuffer *recvPacket)
{
    ClosePauseMsgBox
    uint8_t data8;
    recvPacket->readU8(&data8);
    if (data8 == 1)
    {
        uint16_t data16;
        recvPacket->readU16(&data16);
        if (data16 > 0)
        {
            MB_NetStructFight fight;
            recvfight* fightresult = fight.recvfight_request(recvPacket);
            fightresult->type = kFightResultTypeReplay;
            
            const char* attackName;
            const char* defenceName;
            
            if(MailMgr->queryMail(m_currentMailUID))
            {
                if (hisType_IsSbAttack(MailMgr->queryMail(m_currentMailUID)->hisType) == 0x01)
                {
                    attackName = MB_RoleData::getInstance()->getName();
                    defenceName = MailMgr->queryMail(m_currentMailUID)->senderName.c_str();
                }
                else
                {
                    attackName = MailMgr->queryMail(m_currentMailUID)->senderName.c_str();
                    defenceName = MB_RoleData::getInstance()->getName();
                }
                CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,attackName,defenceName,m_nReplayID,m_nTable,kReplayTypePvp));
            }
            else
            {
                QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface);
                Hist* pHist = pInterface->getRuleInfo()->queryRuleFighterByUID(pInterface->getFightReplayUID());
                if(pHist)
                {
                    attackName = pHist->getName().c_str();
                    defenceName = MB_RoleData::getInstance()->getName();
                    m_nReplayID = pHist->getHistUID();
                    m_nTable = kmMailsTable_RuleFight;
                    CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,attackName,defenceName,m_nReplayID,m_nTable,kReplayTypeRuleFight));
                }
                QUERY_FUNCTION_END;
            }
        }
    }
    else
    {
    
        MB_Message::sharedMB_Message()->showMessage( "该战报已过期, 需要刷新页面" );
        
    }
    m_currentMailUID = 0;
}

void MB_MailData::recvhist_unreadNum(MB_MsgBuffer *recvPacket)
{
    ClosePauseMsgBox
    uint8_t data8;
    uint16_t data16;
    recvPacket->readU8(&data8);

    kmMailsTable table = (kmMailsTable)data8;
    CCAssert(table>0&&table<=kmMailsTable_Num, "table error！！！");

    recvPacket->readU16(&data16);
    m_mailsTable[(int)table-1]->setUnReadCout(data16);
  
}
