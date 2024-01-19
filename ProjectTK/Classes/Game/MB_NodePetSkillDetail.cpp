
#include "MB_NodePetSkillDetail.h"

MB_NodePetSkillDetail::MB_NodePetSkillDetail(){

    m_pNodeSize = NULL;
    m_pSkillname = NULL ;
    m_pSkilldes = NULL;
    m_pSkillactivity = NULL;
}

MB_NodePetSkillDetail::~MB_NodePetSkillDetail(){
    
   CC_SAFE_RELEASE(m_pNodeSize);
   CC_SAFE_RELEASE(m_pSkillname);
   CC_SAFE_RELEASE(m_pSkilldes);
   CC_SAFE_RELEASE(m_pSkillactivity);
}
MB_NodePetSkillDetail *MB_NodePetSkillDetail::create(uint8_t index, int skillid,uint8_t rank){

    MB_NodePetSkillDetail  *ptr = new MB_NodePetSkillDetail();
    if(ptr && ptr->init(index, skillid, rank)){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}
bool MB_NodePetSkillDetail::init(uint8_t index,int skillid,uint8_t rank){
  
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_skill_unit.ccbi", this);
    this->addChild(node);
    CC_SAFE_RELEASE(pCCBReader);

    MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(skillid);
    if(data == NULL){
    
        return true;
    }
    m_pSkilldes->setString(data->getSkillDescription());
    
    ccColor3B color = {195,200,206};
    std::string skillName = "";
    std::string skillActivy = "";
    if(index == 0){
    
        color.r = 0;
        color.g = 250;
        color.b =  124;
        skillName = "普通攻击：";
        skillName += data->getSkillName();
        

    }else if(index == 1){
        
        color.r = 0;
        color.g = 250;
        color.b =  124;
        skillName = "必杀技能：";
        skillName += data->getSkillName();
    
    }else if(index == 2){
        
        skillName = "入门技能：";
        skillName += data->getSkillName();
        skillActivy = "进化+2激活";
        if(rank >= 2 ){
        
            color.r = 0;
            color.g = 250;
            color.b =  124;
        }        
        
    }else if(index == 3){
        
        skillName = "初级进化技：";
        skillName += data->getSkillName();
        skillActivy = "进化+5激活";
        if(rank >= 5 ){
            
            color.r = 0;
            color.g = 250;
            color.b =  124;
        }

        
    }else if(index == 4){
        
        skillName = "中级进化技：";
        skillName += data->getSkillName();
        skillActivy = "完成[一转]激活";
        if(rank >= 10 ){
            
            color.r = 0;
            color.g = 250;
            color.b =  124;
        }
        
    }else if(index == 5){
        
        skillName = "高级进化技：";
        skillName += data->getSkillName();
        skillActivy = "[一转] + 5激活";
        if(rank >= 15 ){
            
            color.r = 0;
            color.g = 250;
            color.b =  124;
        }
        
    }else if(index == 6){
        
        skillName = "超级进化技：";
        skillName += data->getSkillName();
        skillActivy = "完成[二转]激活";
        if(rank >= 20 ){
            
            color.r = 0;
            color.g = 250;
            color.b =  124;
        }
        
    }
    m_pSkillname->setString(skillName.c_str());
    m_pSkillname->setColor(color);
    m_pSkillactivity->setString(skillActivy.c_str());
    m_pSkillactivity->setColor(color);
    m_pSkilldes->setColor(color);
    return true;
}
CCSize MB_NodePetSkillDetail::getUnitSize(){

    return  m_pNodeSize->getContentSize();
}
cocos2d::SEL_MenuHandler MB_NodePetSkillDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodePetSkillDetail::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;
}
bool MB_NodePetSkillDetail::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cellSize", CCNode *,    m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "skillname", CCLabelTTF *,  m_pSkillname);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "skilldes", CCLabelTTF *,  m_pSkilldes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "skillactivity", CCLabelTTF *,  m_pSkillactivity);

    return NULL;
}
