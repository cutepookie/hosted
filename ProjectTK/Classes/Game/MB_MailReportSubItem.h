
#ifndef __ProjectMB__MB_MailReportSubItem__
#define __ProjectMB__MB_MailReportSubItem__

#include <iostream>
#include "MB_MailSubItem.h"
class MB_MailReportSubItem:public MB_MailSubItem
{
public:
    MB_MailReportSubItem();
    bool init();
    CREATE_FUNC(MB_MailReportSubItem)
};

#endif /* defined(__ProjectMB__MB_MailReportSubItem__) */
