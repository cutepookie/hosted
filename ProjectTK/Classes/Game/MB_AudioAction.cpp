
#include "MB_AudioAction.h"


void MB_VolumeFadeOut::update(float time)
{
    if(m_isNewAction)
     m_startVolume = MB_Audio::getInstance()->getBackgroundMusicVolume();
    
    m_isNewAction = false;
    MB_Audio::getInstance()->setBackgroundMusicVolume(m_startVolume*(1.0f - time));
    //MB_LOG("volume: %f ",m_startVolume*(1.0f - time));
}
/** creates the action */
MB_VolumeFadeOut* MB_VolumeFadeOut::create(float d)
{
    MB_VolumeFadeOut* pAction = new MB_VolumeFadeOut();
    
    pAction->initWithDuration(d);
    pAction->autorelease();
    
    return pAction;
}

void MB_VolumeFadeIn::update(float time)
{
    if(m_isNewAction)
        m_startVolume =   MB_Audio::getInstance()->getBackgroundMusicVolume();
    
    m_isNewAction = false;    
    float distance =  MB_Audio::getInstance()->getBackgroundMusicVolume() - m_startVolume;
    
    MB_Audio::getInstance()->setBackgroundMusicVolume(m_startVolume + distance*time);
    //MB_LOG("volume: %f ",m_startVolume + distance*time);
}

MB_VolumeFadeIn* MB_VolumeFadeIn::create(float d)
{
    MB_VolumeFadeIn* pAction = new MB_VolumeFadeIn();
    
    pAction->initWithDuration(d);
    pAction->autorelease();
    
    return pAction;
}
