//
//  MB_SuitAttribute.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#include "MB_SuitAttribute.h"

MB_SuitAttribute::MB_SuitAttribute()
{
    m_nType = 0;
    m_nValue = 0;
}

MB_SuitAttribute::~MB_SuitAttribute()
{
    m_nType = 0;
    m_nValue = 0;
}

bool MB_SuitAttribute::init(MB_XmlNode* pNode)
{
    if (NULL == pNode)
    {
        return false;
    }

    m_nType = pNode->queryAttributeByName("type")->intValue();
    m_nValue = pNode->queryAttributeByName("value")->intValue();

    return true;
}

MB_SuitAttribute* MB_SuitAttribute::create(MB_XmlNode* pNode)
{
    MB_SuitAttribute* pAttr = new MB_SuitAttribute;

    if (pAttr && pAttr->init(pNode))
    {
        pAttr->autorelease();
        return pAttr;
    }
    else
    {
        CC_SAFE_RELEASE_NULL(pAttr);
    }

    return pAttr;
}


/*
 enum eItem_Attribute_Type
 {
 eItem_Attribute_Type_Attack = 1,//攻击
 eItem_Attribute_Type_HP,        //生命
 eItem_Attribute_Type_PDAdd,     //破甲
 eItem_Attribute_Type_PDRed,     //护甲
 eItem_Attribute_Type_MDAdd,     //法穿
 eItem_Attribute_Type_MDRed,     //法抗
 eItem_Attribute_Type_Critic,    //暴击
 eItem_Attribute_Type_CriticRed, //韧性
 eItem_Attribute_Type_Doom,      //命中
 eItem_Attribute_Type_Miss,      //闪避
 eItem_Attribute_Type_SPInit,    //能量
 eItem_Attribute_Type_SPLeft,    //固元
 eItem_Attribute_Type_Absorb,    //吸血 1
 eItem_Attribute_Type_DamageBack,//反弹 1
 eItem_Attribute_Type_Reel,      //击晕
 eItem_Attribute_Type_ReelRed,   //抗晕
 eItem_Attribute_Type_Count,     //数量
 };
 */
const char* MB_SuitAttribute::getAttrDescribe()const
{
    static char descirbe[64] = {"未知的属性"};
    switch (m_nType)
    {
        case 1:
            sprintf(descirbe,"+%d攻击", m_nValue);
            break;
        case 2:
            sprintf(descirbe,"+%d生命", m_nValue);
            break;
        case 3:
            sprintf(descirbe,"+%d破甲", m_nValue);
            break;
        case 5:
            sprintf(descirbe,"+%d法穿", m_nValue);
            break;
        case 4:
            sprintf(descirbe,"+%d护甲", m_nValue);
            break;
        case 6:
            sprintf(descirbe,"+%d法抗", m_nValue);
            break;
        case 7:
            sprintf(descirbe,"+%d暴击", m_nValue);
            break;
        case 8:
            sprintf(descirbe,"+%d韧性", m_nValue);
            break;
        case 9:
            sprintf(descirbe,"+%d命中", m_nValue);
            break;
        case 10:
            sprintf(descirbe,"+%d闪避", m_nValue);
            break;
        case 11:
            sprintf(descirbe,"+%d初始能量", m_nValue);
            break;
        case 12:
            sprintf(descirbe,"+%d能量上限", m_nValue);
            break;
        case 13:
            sprintf(descirbe,"+%d%%吸血", m_nValue / 100);
            break;
        case 14:
            sprintf(descirbe,"+%d%%反弹", m_nValue / 100);
            break;
        case 15:
            sprintf(descirbe,"+%d击晕", m_nValue);
            break;
        case 16:
            sprintf(descirbe,"+%d抗晕", m_nValue);
            break;
        case 21:
            sprintf(descirbe,"+%d%%攻击", m_nValue / 100);
            break;
        case 22:
            sprintf(descirbe,"+%d%%生命", m_nValue / 100);
            break;
        default:
            CCLog("Unknow attribute:%d",m_nType);
            descirbe[0] = 0;
            break;
    }
    return descirbe;
}

CCLabelTTF* MB_SuitAttribute::createAttrPanel(float fontSz)
{
    const char* pDescribe = getAttrDescribe();

    CCLabelTTF* pLabel = CCLabelTTF::create(pDescribe,"" ,fontSz);

    return pLabel;
}


