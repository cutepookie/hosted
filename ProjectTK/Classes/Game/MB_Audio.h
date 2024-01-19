
#ifndef __ProjectMB__MB_Audio__
#define __ProjectMB__MB_Audio__

#include "Game.h"

class MB_Audio :public cocos2d::CCObject{

    private:
    
        MB_Audio();
        bool    m_isBackgroundOpen;
        bool    m_isEffectsoundOpen;
        bool    m_nisloop ;
        char    m_strbackground[300];
        static MB_Audio *m_pAudio;
        CocosDenshion::SimpleAudioEngine * m_pSysAudio;
    
    public  :

        ~MB_Audio();
        void playBackGround(const char *background ,float duration = 0){
            
            playBackGround(background,false ,duration);
        }
        void playBackGround(const char *background,bool isloop = true,float duration = 0);
        int  playEffect(const char *effect){
    
            if (effect == NULL || strlen(effect)==0)
            {
                return 0;
            }
                return playEffect(effect,false);
        }
        int  playEffect(const char *effect, bool isloopp);
        void stopBackGround();
        void stopEffect(int effectid);
        void setBackGrondOpen(bool  backgroundOpen);
        bool getBackGroundOpen();
        bool getEffectsoundOpen();
        void setEffectsoundOpen(bool isEffectsoundOpen);
        static MB_Audio * getInstance();
        static void destroy();
        float getBackgroundMusicVolume();
        void setBackgroundMusicVolume(float dt);
    void playNormalBgm();
};
#define PlayBackGround(type)    MB_Audio::getInstance()->playBackGround(GET_BACKGROUND(type).c_str(),true);
#define PlayBackGround2(type)   MB_Audio::getInstance()->playBackGround(GET_BACKGROUND(type).c_str(),false);
#endif /* defined(__ProjectMB__MB_Audio__) */
