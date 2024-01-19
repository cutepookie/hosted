//
//  MB_LayerMailView.h
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#ifndef __ProjectMB__MB_LayerMailView__
#define __ProjectMB__MB_LayerMailView__

#include "MB_MailMainView.h"

class MB_LayerMailView : public MB_MailMainView
{
public:
    MB_LayerMailView();
    CREATE_FUNC(MB_LayerMailView);
    virtual CCTableViewCell* tableCellAtIndex (CCTableView *table, unsigned int idx);
    void recvmail_draw_reward(MB_MsgBuffer* pRecv);
    void onInitDidFinish();
protected:
    
};

#endif /* defined(__ProjectMB__MB_LayerMailView__) */
