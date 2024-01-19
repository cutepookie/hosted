

#include "MB_MailReportSubItem.h"

MB_MailReportSubItem::MB_MailReportSubItem()
{
}


bool MB_MailReportSubItem::init()
{
    MB_ResWindow::init();
    CCNode* pNode = loadResource("res/report_node_unit.ccbi");
    this->addChild(pNode);
    onInitDidFinish();
    return true;
}
