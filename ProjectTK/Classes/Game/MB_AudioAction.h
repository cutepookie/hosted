
#ifndef __ProjectMB__MB_AudioAction__
#define __ProjectMB__MB_AudioAction__

#include "Game.h"

class MB_VolumeFadeOut:public CCActionInterval
{
public:
    MB_VolumeFadeOut(){m_isNewAction = true;}
    virtual void update(float time);
public:
    /** creates the action */
    static  MB_VolumeFadeOut* create(float d);
protected:
    bool    m_isNewAction;
    float   m_startVolume;
};

class MB_VolumeFadeIn:public MB_VolumeFadeOut
{
public:
    virtual void update(float time);
public:
    /** creates the action */
    static  MB_VolumeFadeIn* create(float d);
};

#endif /* defined(__ProjectMB__MB_AudioAction__) */
