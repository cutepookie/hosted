////
////  MB_LayerPetProperty.h
////  ProjectMB
////
////  Created by yuanwugang on 14-11-22.
////
////
//
//#ifndef __ProjectMB__MB_LayerPetProperty__
//#define __ProjectMB__MB_LayerPetProperty__
//
//#include "MB_LayerDeploy.h"
//#include "MB_NodeDeploy.h"
//
//enum
//{
//    kTypeAttibutes = 1,
//    kTypeEnterSkills = 2,
//    kTypeSkills = 3,
//    kTypeRanSkills = 4
//};
//
//class MB_PetData;
//class MB_LayerPetProperty : public MB_LayerDeploy
//{
//public:
//    static MB_LayerPetProperty* create(CCSize size,MB_PetData* petData);
//    MB_LayerPetProperty();
//    ~MB_LayerPetProperty();
//    virtual bool init(CCSize size,MB_PetData* petData);
//    virtual void onResetWnd();
//    virtual void onClickNode(){};
////    void sort();
////    void resetOffset();
//private:
////    CCScrollView*   m_pScrollView;
//    MB_PetData*  m_pData;
//};
//
//
//
//class MB_NodePetAttibutes : public MB_NodeDeploy
//{
//public:
//    MB_NodePetAttibutes();
//    ~MB_NodePetAttibutes();
//    CREATE_FUNC(MB_NodePetAttibutes);
//    void setMB_PetData(MB_PetData* data);
//    virtual void setDeploy();
//    void recvpet_detail(MB_MsgBuffer* pRecv);
//    void onMsgRecv(CCNode* node, SocketResponse* response);
//private:
//    MB_PetData*  m_pMB_PetData;
//};
//
////组合技能
//class MB_NodeSkills : public MB_NodeDeploy
//{
//public:
//    MB_NodeSkills();
//    ~MB_NodeSkills();
//    CREATE_FUNC(MB_NodeSkills);
//    void setMB_PetData(MB_PetData* data);
//    virtual void setDeploy();
//private:
//    MB_PetData*  m_pMB_PetData;
//};
//
//
////初始技能
//class MB_NodeEnterSkills : public MB_NodeDeploy
//{
//public:
//    MB_NodeEnterSkills();
//    ~MB_NodeEnterSkills();
//    CREATE_FUNC(MB_NodeEnterSkills);
//    void setMB_PetData(MB_PetData* data);
//    virtual void setDeploy();
//private:
//    MB_PetData*  m_pMB_PetData;
//};
////进化技能
//class MB_NodeRankSkills : public MB_NodeDeploy
//{
//public:
//    MB_NodeRankSkills();
//    ~MB_NodeRankSkills();
//    CREATE_FUNC(MB_NodeRankSkills);
//    void setMB_PetData(MB_PetData* data);
//    virtual void setDeploy();
//private:
//    MB_PetData*  m_pMB_PetData;
//};
//#endif /* defined(__ProjectMB__MB_LayerPetProperty__) */
