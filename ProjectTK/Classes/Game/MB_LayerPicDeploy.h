//
//  MB_LayerPicDeploy.h
//  ProjectMB
//
//  Created by yuanwugang on 14-11-23.
//
//

#ifndef __ProjectMB__MB_LayerPicDeploy__
#define __ProjectMB__MB_LayerPicDeploy__
#define actionSpanTime (0.05f)
#define actionMoveTime (0.25f)
#include "MB_LayerDeploy.h"
#include "MB_NodeDeploy.h"
enum
{
    kTypePetPic = 1,
    kTypeEquipPic,
    kTypeTreasurePic,
};
class MB_LayerPicDeploy : public MB_LayerDeploy
{
public:
    static MB_LayerPicDeploy* create(CCSize size,int type);
    virtual bool init(CCSize size,int type);
    virtual void onResetWnd();
    virtual void onClickNode();
    void sort();
private:
    CCScrollView*   m_pScrollView;
    int m_nType;
};



class MB_NodePetDeploy : public MB_NodeDeploy
{
public:
    CREATE_FUNC(MB_NodePetDeploy);
    void setData(int nStar);
    virtual void setDeploy();
private:
    int m_nStar;
};


class MB_NodeEquipDeploy : public MB_NodeDeploy
{
public:
    CREATE_FUNC(MB_NodeEquipDeploy);
    void setData(int nStar);
    virtual void setDeploy();
private:
    int m_nStar;
};



class MB_NodeTreasureDeploy : public MB_NodeDeploy
{
public:
    CREATE_FUNC(MB_NodeTreasureDeploy);
    virtual void setDeploy();
};
#endif /* defined(__ProjectMB__MB_LayerPicDeploy__) */
