//
//  MB_FunctionMgr.h
//  ProjectPM
//O
//  Created by WenYong on 14-3-26.
//
//

#ifndef __ProjectMB__MB_FunctionMgr__
#define __ProjectMB__MB_FunctionMgr__

#include "../Common/GameLib/CCGameLib.h"
#include "MB_FunctionModule.h"

using namespace NSGameFunction;

class MB_FunctionOperator:public CCObject
{
public:
    MB_FunctionOperator();
    virtual ~MB_FunctionOperator();
    void safeRelease(int iType);
    void insertFunction(int iType,CCFunctionInterface* pInterface);
    bool queryFunctionByType(int iType,CCFunctionInterface** lpInterface);
    template<class T>
    T*  queryFunctionByType(int iType)
    {
        CCFunctionInterface* pInterface = NULL;
        if (queryFunctionByType(iType,&pInterface))
        {
            return dynamic_cast<T*>(pInterface);
        }
        return NULL;
    }
    void removeFunction(int iType);
protected:
    virtual bool init()=0;
protected:
    std::map<int,CCFunctionInterface*> m_pFunctionContainer;
};

class MB_FunctionMgr:public MB_FunctionOperator
{

public:
    static MB_FunctionMgr* getInstance();
    static void destroyInstance();
    void initPushMessage();
    void onLoadingScene();
    virtual ~MB_FunctionMgr();
    virtual bool onRoleLevelUp(int nRoleLevel);
    bool bindEntry2Target(uint32_t kType,CCNode* pNode);
    bool bindMainDialog2Target(uint32_t kType,CCNode* pNode);
    bool goFunction(int kType,CCObject* pSender);
    MB_ResWindow* getFunctionMainWndByType(int kType);
    CCArray* getFunctionLevelUpTips(int nLevel);
    virtual void onDayPassed();
protected:
    virtual bool init();
private:
    MB_FunctionMgr();
    static MB_FunctionMgr* m_pSingletonInstance;
};

#define QUERY_FUNCTION_BEGIN(class,type,var)\
NSGameFunction::CCFunctionInterface *__pInterface = NULL;\
if(MB_FunctionMgr::getInstance()->queryFunctionByType(type ,&__pInterface))\
{\
class* var = dynamic_cast<class*>(__pInterface);\
if (var)\
{\

#define QUERY_FUNCTION_END \
}\
}\


#endif /* defined(__ProjectMB__MB_FunctionMgr__) */
