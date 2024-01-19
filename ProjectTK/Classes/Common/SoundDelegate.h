
#ifndef __ProjectMB__SoundDelegate__
#define __ProjectMB__SoundDelegate__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

//-----------------------------------------------
//sound delegate
class SoundDelegate:public CCObject
{
public:
                 SoundDelegate();
    virtual     ~SoundDelegate();
public:
            void setTargetSound(std::string file);
public:
    virtual void execute       (CCObject* sender);
private:
    std::string  m_soundfile;
};

//-----------------------------------------------
//CCMenuItem
class MenuSd:public SoundDelegate
{
public:
    virtual void execute (CCObject* sender);
};

//-----------------------------------------------
//CCControlButton
class ButtonSd :public SoundDelegate
{
public:
    virtual void execute (CCObject* sender);
};

//-----------------------------------------------
//CCControlButtonWithFx
class ButtonFxSd :public SoundDelegate
{
public:
    virtual void execute (CCObject* sender);
};

#endif /* defined(__ProjectMB__SoundDelegate__) */
