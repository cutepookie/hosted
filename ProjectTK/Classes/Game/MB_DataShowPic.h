

#ifndef __ProjectMB__MB_DataShowPic__
#define __ProjectMB__MB_DataShowPic__

#include "Game.h"
#include "MB_CommonType.h"

USING_NS_CC;

#define SHAPE_1 1
#define SHAPE_2 2
#define SHAPE_3 3
#define SHAPE_BASE  10000000
class MB_DataShowPic :public CCObject
{
private:
    
    //本地读取數据
    CCArray *m_pClientMB_PetTemplateArray;
    CCArray *m_pClientEquipTempleteArray;
    CCArray *m_pClientTreasureTempleteArray;
    
    //伺服器接受的數据
    CCArray *m_pServerMB_PetTemplateArray;
    CCArray *m_pServerEquipTempleteArray;
    CCArray *m_pServerTreasureTempleteArray;
    
    bool initMB_PetTemplate();
    bool initEquipTemplete();
    bool initTreasureTemplete();
    
    
public:
    
    MB_DataShowPic();
    ~MB_DataShowPic();
    
    /** Return the shared instance **/
    static MB_DataShowPic *getInstance();
    
    /** Relase the shared instance **/
    static void destroyInstance();
    
    //图鉴协议
    bool sendgather_get_list(uint8_t type);
    bool recvgather_get_list(MB_MsgBuffer* recvPacket);
    bool recvgather_new(MB_MsgBuffer* recvPacket);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    
    CCArray* getClientMB_PetTemplateArray(){return m_pClientMB_PetTemplateArray;};
    CCArray* getClientEquipTempleteArray(){return m_pClientEquipTempleteArray;};
    CCArray* getClientTreasureTempleteArray(){return m_pClientTreasureTempleteArray;};
    void getClientMB_PetTemplateArrayByStar(CCArray* array,int star);
    void getClientEquipTempleteArrayByStar(CCArray* array,int star);
    
    
    CCArray* getServerMB_PetTemplateArray(){return m_pServerMB_PetTemplateArray;};
    CCArray* getServerEquipTempleteArray(){return m_pServerEquipTempleteArray;};
    CCArray* getServerTreasureTempleteArray(){return m_pServerTreasureTempleteArray;};
    
};

class MB_PicShow: public CCObject
{
public:
    MB_PicShow(){m_Shape = 1;m_bActivata = true;m_bIsNew = false;};
    CC_SYNTHESIZE(uint16_t, m_uID, ID);
    //添加形态 yuanwugang
    CC_SYNTHESIZE(uint16_t,m_Shape,Shape);
    CC_SYNTHESIZE(bool,m_bActivata,Activata);
    CC_SYNTHESIZE(bool,m_bIsNew,IsNew);
};

#endif /* defined(__ProjectMB__MB_DataShowPic__) */
