
#include "SoundDelegate.h"
#include "Game.h"
#include "MB_CommonType.h"
#include "MB_GameInfo.h"
SoundDelegate::SoundDelegate()
{
    m_soundfile = "";
}

SoundDelegate::~SoundDelegate()
{
}

void SoundDelegate::setTargetSound(std::string file)
{
    m_soundfile = file;
}

void SoundDelegate::execute(cocos2d::CCObject *sender)
{
    MB_Audio::getInstance()->playEffect(m_soundfile!=""?m_soundfile.c_str():
                        GET_BACKGROUND(kmBackGround_Default_Effect_Sound).c_str());
}

//----------------------------------------------------------------------
void MenuSd::execute(cocos2d::CCObject *sender)
{
    SoundDelegate::execute(sender);
}

//----------------------------------------------------------------------
void ButtonSd::execute(cocos2d::CCObject *sender)
{
    SoundDelegate::execute(sender);
}

//----------------------------------------------------------------------
void ButtonFxSd::execute(cocos2d::CCObject *sender)
{
    SoundDelegate::execute(sender);
}
