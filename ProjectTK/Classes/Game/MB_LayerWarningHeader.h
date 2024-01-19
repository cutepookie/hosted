

#ifndef __ProjectMB__MB_LayerWarningHeader__
#define __ProjectMB__MB_LayerWarningHeader__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
#define MESSAGE_MAX 50

class MB_MessageSpItem:public CCObject {

    public:
    
    MB_MessageSpItem(){
    
    }
    ~MB_MessageSpItem(){
    
    }    
    CC_SYNTHESIZE(uint8_t, m_nRewardType, RewardType);
    CC_SYNTHESIZE(uint16_t, m_nRewardValue, RewardValue);
    CC_SYNTHESIZE(uint32_t, m_nRewardNum, RewardNum);
    CC_SYNTHESIZE(uint8_t, m_nRewardRank, RewardRank);
    CC_SYNTHESIZE(uint32_t, m_nRewardLevel, RewardLevel);
};
class MB_HeadMessage:public CCObject{

    private :
    
    std::string  m_strString;
    std::string  m_strRoleName;
    CCArray *    m_pArray;

    public :
    
    MB_HeadMessage(){
    
        m_pArray = new CCArray();
    }
    ~MB_HeadMessage(){
    
        CC_SAFE_DELETE(m_pArray);
    }
    CC_SYNTHESIZE(int, m_nType, Type);
    CC_SYNTHESIZE(int, m_nMessageID, MessageID);
    void setString(const char *str){
        
        m_strString = str;
    }
    const char *getString(){

        return  m_strString.c_str();
    }
    void setRoleName(const char *str){
        
        m_strRoleName = str;
    }
    const char *getRoleName(){
        
        return  m_strRoleName.c_str();
    }
    CCArray *getArray(){

        return  m_pArray;
    }
    
};
class MB_LayerWarningHeader : public CCLayer
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCNodeLoaderListener
{
    
    CCLabelTTF* m_pHeaderInfo;
    float m_nHeaderLeft;
    static MB_LayerWarningHeader *m_pSharedLayer;
    ccColor3B m_pColor;
    CCNode *m_pNode;
    float m_nMessageLength;
    CCScrollView *m_pScoller;
    CCNode *m_pScollerNode;
        CCNode *m_pBgNode;
    CCArray *m_pStringCache;
    MB_HeadMessage *m_pNowShowMessage;

    
public:
    MB_LayerWarningHeader();
    ~MB_LayerWarningHeader();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MB_LayerWarningHeader, create);
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    void onCommitClicked(CCObject* pSender);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    CCObject *getStringBuffer(MB_MsgBuffer* pbuffer);
    CCLabelTTF *getLabel(CCObject *obj);
    bool recvmeesage_bc_id2(MB_MsgBuffer *recvpacket,MB_HeadMessage *message);
    void goShowMessage(MB_HeadMessage *message);
    void onPopItem();
    void setHeaderString(const char *);    
    bool recvmessage_pet_upLevel(MB_HeadMessage *message);
    bool recvmeesage_bc_id(MB_HeadMessage *message);
    bool recvmeesage_bc_id2(MB_HeadMessage *message);
    bool recvmessage_item_uprank(MB_HeadMessage *message);
    bool recvmessage_best_card(MB_HeadMessage *message);
    bool recvbattle_broadcaset_get_item(MB_HeadMessage *message);
    
//    bool recvmessage_pet_upLevel(MB_MsgBuffer *recvpacket);
//    bool recvmeesage_bc_id(MB_MsgBuffer *recvpacket);
//    bool recvmeesage_bc_id2(MB_MsgBuffer *recvpacket);
//    bool recvmessage_item_uprank(MB_MsgBuffer *recvpacket);
//    bool recvmessage_best_card(MB_MsgBuffer* pbuffer);
//    CCLabelTTF *getLabel(MB_MsgBuffer* pbuffer);
    void getMessageByID(short messgeId,char *strBuf);
    static  MB_LayerWarningHeader *getSharedLayerWarningHeader();
    void onMoevMessageOver(CCNode *);
    void onStartMessageMove(CCLabelTTF *);
    void convertDataToCard(sCallGeneralCard *pcard, kmCardType type, uint32_t value);
};

class MB_LayerWarningHeaderLoader:public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MB_LayerWarningHeaderLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MB_LayerWarningHeader);
};

#endif /* defined(__ProjectMB__MB_LayerWarningHeader__) */
