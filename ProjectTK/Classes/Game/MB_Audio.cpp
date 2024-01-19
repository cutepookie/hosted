
#include "MB_Audio.h"
#include "MB_AudioAction.h"

MB_Audio * MB_Audio::m_pAudio = NULL;

MB_Audio::MB_Audio(){

    m_strbackground[0] = '\0';
    m_isBackgroundOpen = true;
    m_isEffectsoundOpen = true;
    m_nisloop = false;
    m_pSysAudio = CocosDenshion::SimpleAudioEngine::sharedEngine();
    setBackGrondOpen(!CCUserDefault::sharedUserDefault()->getBoolForKey("musicOff"));
    setEffectsoundOpen(!CCUserDefault::sharedUserDefault()->getBoolForKey("soundOff"));
}
MB_Audio::~MB_Audio(){

}
MB_Audio * MB_Audio::getInstance(){
    
    if(m_pAudio == NULL){
    
        m_pAudio = new MB_Audio();
    }
    return m_pAudio;
}
void MB_Audio::destroy(){

    if(m_pAudio){
    
        delete  m_pAudio;
        m_pAudio = NULL;
    }
}
void MB_Audio::playBackGround(const char *background,bool isloop ,float duration){

    strcpy(m_strbackground, background);
    m_nisloop = isloop;
    if(m_isBackgroundOpen){
        m_pSysAudio->playBackgroundMusic(background, isloop);
        if(duration >0 ){
        
             CCSequence*  m_volumeAction = CCSequence::create(MB_VolumeFadeOut::create(duration),
                                                MB_VolumeFadeIn::create(duration),
                                                NULL);
              m_volumeAction->startWithTarget(NULL);

        }
    }

    
}
int  MB_Audio::playEffect(const char *effect,bool isloop){

    if(m_isEffectsoundOpen){

      return  m_pSysAudio->playEffect(effect,isloop);
    }
    return 0xFEEDBAB;
}

void MB_Audio::playNormalBgm()
{
    if ((strcmp(m_strbackground, "music/bgm_main.mp3") != 0)&&(strcmp(m_strbackground, "music/bgm_battle.mp3") != 0)&&(strcmp(m_strbackground, "music/bgm_battle_boss.mp3") != 0)) {
        PlayBackGround(kmBackGround_Normal);
    }
}
void MB_Audio::stopBackGround(){

    m_pSysAudio->stopBackgroundMusic();
}
void MB_Audio::stopEffect(int effectid){

    m_pSysAudio->stopEffect(effectid);
}
void MB_Audio::setBackGrondOpen(bool  backgroundOpen){
 
    m_isBackgroundOpen = backgroundOpen;
    if(backgroundOpen){
    
        if(m_strbackground[0] != '\0'){
        
           this->playBackGround(m_strbackground,m_nisloop,0.0f);
        }
    }else {
    
        m_pSysAudio->stopBackgroundMusic(true);
    }
 
}
bool MB_Audio::getBackGroundOpen(){

    return m_isBackgroundOpen;
}
bool MB_Audio::getEffectsoundOpen(){

    return m_isEffectsoundOpen;
}
void MB_Audio::setEffectsoundOpen(bool isEffectsoundOpen){
    
    m_isEffectsoundOpen = isEffectsoundOpen;
}
float MB_Audio::getBackgroundMusicVolume(){

    return m_pSysAudio->getBackgroundMusicVolume();
}
void MB_Audio::setBackgroundMusicVolume(float dt){

    m_pSysAudio->setBackgroundMusicVolume(dt);
}
