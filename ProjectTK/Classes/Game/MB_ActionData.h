

#ifndef __ProjectMB__MB_ActionData__
#define __ProjectMB__MB_ActionData__
#include "Game.h"
class MB_ActionData{

private:
        static  MB_ActionData* s_pData ;
        std::map <uint8_t, MB_Action*> m_mapAction;
        void initActions();
public:
        MB_ActionData();
        ~MB_ActionData();
    
        static MB_ActionData * getInstance();
        static void destroyInstance();
        MB_Action *getActionByID(uint8_t actionId);
  
    void testActionCcbFiles();
};

#endif /* defined(__ProjectMB__MB_ActionData__) */
