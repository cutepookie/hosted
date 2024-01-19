//
//  CCDebugCodePage.h
//  ProjectTK
//
//  Created by yong wen on 2/26/14.
//
//

#ifndef __ProjectTK__CCDebugCodePage__
#define __ProjectTK__CCDebugCodePage__
#ifndef __CODE_DEBUG__
#define __CODE_DEBUG__
#endif
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include "../RichText.h"
namespace cocos2d
{
    class CCNode;
}
class SerBuffer;
namespace NSDebugSpace
{
    void beginDebugCode();
    void endDebugCode();
    void debugXmlFile();
    void debugReadXmlDirect();
    void debugXmlFileManager();
    void debugCardStarConfig();

    /*
     message sc_fight_request[id=20002]{
     repeated 	p_fighter		fighterList		=1;//戰鬥單位列表
     repeated	p_action		actionList		=2;//戰鬥序列
     required	bool			result			=3;//戰鬥是否勝利
     }
     */
     //參与戰鬥的單位的數据結构
     struct p_fighter
     {
         uint64_t			gerID;          //精靈ID
         uint16_t			gerTypeID;      //精靈模版ID
         int8_t			    gerPos;         //精靈位置，gerPos*=gerCamp
         uint32_t			gerHp;          //精靈當前血量
         uint32_t			gerHpMax;       //精靈血量上限
         uint32_t			gerSp;          //精靈當前能量
         uint8_t			gerQuality;     //精靈品階
         uint16_t           gerLevel;       //精靈模版ID
         void getDecribe(char* buff)
         {
             sprintf(buff, "-------\nGerPos:%d\n-------\n",gerPos);
         }
     };

     //每个攻擊動作的數据結构
    struct p_action
    {
        p_action()
        {
            memset(targetPos, 0, 6);
        }
        int8_t              gerPos;         //精靈站位
        uint8_t             actionID;       //動作ID
        int8_t              targetPos[6];   //目标位置列表  //repeated
        int8_t              addSp;          //增加的能量，如果是扣能量，则為负值
        int32_t             addHp;          //增加的血量，如果是扣血量，则為负值
        uint8_t             state;          //第一位表示是否暴擊，第二位表示是否擊晕
        void getDecribe(char* buff)
        {
            sprintf(buff, "-------\nGerPos:%d\nTargetPos:%d,%d,%d,%d,%d,%d\n-------\n",gerPos,targetPos[0],targetPos[1],targetPos[2],targetPos[3],targetPos[4],targetPos[5]);
        }
    };

    void runWithScene(cocos2d::CCNode* pNode);
    void saveFightStruct(SerBuffer* pRev);

    class CCDebugInterface
    {
    public:
        virtual ~CCDebugInterface(){};
        virtual void begin()=0;
        virtual void end(){}
    };
    class CCDebugSuitSystem:public CCDebugInterface
    {
    public:
        virtual void begin();
        virtual void end();
    };
    
    class CCDebugUI:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
    class CCDebugChar:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
    class CCDebugSavePhoto:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
    class CCDebugScale9Sprite:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
    class CCDebugSynopsisConfig:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
    
    class CCGuiCodeGenerator:public CCDebugInterface
    {
    public:
        virtual void begin();
        void generate(const char* pClassName,const char* pFile);
    };

    class CCRichTextDebug:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
    
    class CCCalenderDebug:public CCDebugInterface
    {
    public:
        virtual void begin();
    };
};

#endif /* defined(__ProjectTK__CCDebugCodePage__) */
