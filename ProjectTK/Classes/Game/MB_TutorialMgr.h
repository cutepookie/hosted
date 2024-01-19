

#ifndef __ProjectMB__MB_TutorialManager__
#define __ProjectMB__MB_TutorialManager__

#include "Game.h"
using namespace std;

class MB_TutorialData: public CCObject
{
    CC_SYNTHESIZE(int, m_nTypeID, TypeID);
    CC_SYNTHESIZE(bool, m_bIsPassed, IsPassed);
};

class MB_TutorialTemplete: public MB_ClientData
{
public:
    bool init(MB_XmlNode *pNode);
    
    CC_SYNTHESIZE(int, m_nID, ID);
    CC_SYNTHESIZE(int, m_nType, Type);
    CC_SYNTHESIZE(int, m_nTagID, TagID);
    CC_SYNTHESIZE(int, m_nRoleLevel, RoleLevel);
    CC_SYNTHESIZE(int, m_nPart, Part);
    CC_SYNTHESIZE(bool, m_bCompleteNode, IsCompleteNode);
    CC_SYNTHESIZE(int, m_nCellIndex, CellIndex);        //列表中索引 从1开始
    CC_SYNTHESIZE(int, m_bGataOpenSkip, GataOpenSkip);  //如果在关卡界面，直接跳过该步骤
    CC_SYNTHESIZE(bool, m_Gohome, Gohome);              //执行完回到主页
    CC_SYNTHESIZE(int, m_nSoundID, SoundID);
    CC_SYNTHESIZE(int, m_nFunId, FunId);                //副本中对应功能ID v1.0.5
    
    MB_TutorialTemplete()
    {
        m_bCompleteNode = false;
        m_nFunId = 0;
        m_nSoundID = -1;
        m_nCellIndex = 0;
        m_Gohome = false;
        m_bGataOpenSkip = 0;
    }
    
    const char* getText(){ return m_strText.c_str();}
private:
    std::string m_strText;
};


class MB_TutorialMgr: public CCObject
{
    friend class MB_ResWindow;
    friend class MB_LayerTutorialDialog;
    friend class MB_TutorialTemplete;
public:

    MB_TutorialMgr();
    ~MB_TutorialMgr();
    
    static MB_TutorialMgr* getInstance();
    static void destroyInstance();
    
    void trigpetComplete();
    void skipTutorial();
    void SetModelDilogState(std::string key,bool value);
    bool HasModelDilog();
    
    int getCellIndex();
    NSGameFunction::FunctionType getFunID();
    
    bool getCompletePveGoHome();
    bool getRoleLevelUpGoHome();          //强制回到主页
    
    bool HasRoleSound()
    {
        return m_bSkipTutorial;
    }
public:
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    bool sendrole_get_guide_state();
    bool recvrole_get_guide_state(MB_MsgBuffer* recvPacket);
    bool sendrole_set_guide_state(uint16_t status);
    bool recvrole_set_guide_state(MB_MsgBuffer* recvPacket);
    bool sendrole_log_guide_state(uint16_t id);
    
    CC_SYNTHESIZE(int, m_curID, CurID);
    CC_SYNTHESIZE(int, m_nCurPart, CurPart);
    CC_SYNTHESIZE(bool, m_bSkipTutorial, SkipTutorial);
    CC_SYNTHESIZE(bool, m_bHasTutorialDilog, HasTutorialDilog);
private:
    int GataOpenSkip();         //如果在关卡界面，直接跳过该步骤
    bool isPassed(int typeID);
    MB_TutorialTemplete* getTempleteByID(int typeID);
    MB_TutorialTemplete* getCurTemplete(){return getTempleteByID(m_curID);}
    bool canTrigpetByTypeID(int typeID);
    bool canTrigpetByTagID(int tagID);
    bool m_bCompletePveGoHome;
    std::vector<int> m_LevelUpGoHomeLevels;
    std::map<std::string,bool> m_ModelDilogMap;
    int m_nMaxPart;
    int m_nMaxID;
    CCArray* m_pData;
    CCArray* m_pTemplete;
    
    bool initTemplete();
    bool initData();
};

#define TutorialAssignLayerWindow if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))return true;
#define TutorialTriggerComplete if(MB_TutorialMgr::getInstance()->getHasTutorialDilog())MB_TutorialMgr::getInstance()->trigpetComplete();
#define TutorialForcedTrigpetComplete MB_TutorialMgr::getInstance()->trigpetComplete();

#endif /* defined(__ProjectMB__MB_TutorialMgr__) */
