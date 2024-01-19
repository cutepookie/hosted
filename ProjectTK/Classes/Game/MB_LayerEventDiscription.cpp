

#include "MB_LayerEventDiscription.h"
#include "MB_ActivatyMainLayer.h"
MB_LayerEventDiscription::MB_LayerEventDiscription(){
    
    m_pTimeCount = NULL;
    m_pDiscription = NULL;
    m_pDetail = NULL ;
    SOCKET_MSG_REGIST(SC_ACTIVITY_RECORD_UPDATE, MB_LayerEventDiscription);
}
MB_LayerEventDiscription::~MB_LayerEventDiscription(){
    
    CC_SAFE_RELEASE(m_pTimeCount);
    CC_SAFE_RELEASE(m_pDiscription);
    CC_SAFE_RELEASE(m_pDetail);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_RECORD_UPDATE);
}
bool MB_LayerEventDiscription::init(){
    
    if(MB_ResWindow::init() == false){
        
        return false;
    }    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/activity_node_des.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    m_pDiscription->setHorizontalAlignment(kCCTextAlignmentCenter);
    return true;
}
MB_LayerEventDiscription * MB_LayerEventDiscription::create(){
    
    MB_LayerEventDiscription *ptr = new MB_LayerEventDiscription();
    if(ptr && ptr->init()){
        
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_LayerEventDiscription::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_LayerEventDiscription::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
  
    return NULL;
}
bool MB_LayerEventDiscription::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTimeCount", CCLabelTTF *, m_pTimeCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDiscription", CCLabelTTF *, m_pDiscription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDetail", CCLabelTTF *, m_pDetail);
    return false;
}
void  MB_LayerEventDiscription::tickTime(float dt){
    
    int timelift = m_nCloseTime -MB_ClientSocket::getInstance()->getServerTime();
    char databuf[50];
    sprintf(databuf,"%d天%02d时%02d分%02d秒",timelift/(3600*24),timelift%(3600*24)/3600,timelift%3600/60,timelift%3600%60);
    m_pTimeCount->setString(databuf);
    if(timelift <= 0){
        
        CCObject * object = MB_MoneyEevntMgr::getInstance()->getEventDataByActivityID(m_nActivyId);
        if(object)
        {
            MB_MoneyEevntMgr::getInstance()->getEventList()->removeObject(object);
            MB_MoneyEevntMgr::getInstance()->sethasChange(true);
            MB_TARGET_PARENT(MB_ActivatyMainLayer, pEvent);
            if( pEvent){
                pEvent->dirty();
            }
        }
        unschedule(schedule_selector(MB_LayerEventDiscription::tickTime));
    }
}

void MB_LayerEventDiscription::setClostTime(int closeTime){
    
    m_nCloseTime  = closeTime;
    if (m_nCloseTime > 0) {
        
        tickTime(0);
        schedule(schedule_selector(MB_LayerEventDiscription::tickTime),1);
    
    }else{
    
        m_pTimeCount->setString("永久");
        
    }
}
void MB_LayerEventDiscription::setDiscription(const char * discription){
    
    if(discription && m_pDiscription)m_pDiscription->setString(discription);
}
void MB_LayerEventDiscription::setActivyID(int activyid){
    
    m_nActivyId = activyid ;
    
}
void MB_LayerEventDiscription::setNomCount(int type, int count){
    
    m_pDetail->setVisible(true);
    if(type == 4){
    
        char databuf[100];
        m_pDetail->setVisible(true);
        sprintf(databuf, "活动期间，已经累计充值%d天",count);
        m_pDetail->setString(databuf);
        
    }else if(type == 2){
        
        char databuf[100];
        m_pDetail->setVisible(true);
        sprintf(databuf, "活动期间，已经累计充值%d元",count);
        m_pDetail->setString(databuf);
   
    }else if(type == 6){
        
        char databuf[100];
        m_pDetail->setVisible(true);
        sprintf(databuf, "活动期间，已经累计消费%d宝石",count);
        m_pDetail->setString(databuf);
    }else
    {
        m_pDetail->setVisible(false);
    }
}
void MB_LayerEventDiscription::onMsgRecv(CCNode* node, SocketResponse* response){
    
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
        case SC_ACTIVITY_RECORD_UPDATE:
        {
            
            if(m_pDetail->isVisible()){
                
                MB_MoneyEevntData * data = MB_MoneyEevntMgr::getInstance()->getEventDataByActivityID(m_nActivyId );
                
                if(data->getType() == 4){
                    
                    char databuf[100];
                    m_pDetail->setVisible(true);
                    sprintf(databuf, "活动期间，已经累计充值%d天",data->getTypeValue());
                    m_pDetail->setString(databuf);
                    
                }else if(data->getType()  == 2){
                  
                    char databuf[100];
                    m_pDetail->setVisible(true);
                    sprintf(databuf, "活动期间，已经累计充值%d元",data->getTypeValue());
                    m_pDetail->setString(databuf);
                }
            }
        
        
        }
            break;
        default:
            break;
    }
}
