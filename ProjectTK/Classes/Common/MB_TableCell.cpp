
#include "MB_TableCell.h"

MB_TableCell::MB_TableCell(){

    m_pIsTouchEnable = true;
}
MB_TableCell::~MB_TableCell(){

}
MB_TableCell* MB_TableCell::create(){

    MB_TableCell * ptr = new MB_TableCell();
    if( ptr && ptr-> init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return  NULL;
}
bool  MB_TableCell::init(){
  
    if(MB_ResWindow::init() == false){
    
        return false;
    }
    return  true;
}
bool  MB_TableCell::checkInTouch(CCPoint worldPoint){
    
    CCPoint pos = this->convertToNodeSpace(worldPoint);
    if(pos.x >= 0  && pos.x <= this->getContentSize().width && pos.y >= 0 && pos.y <=  this->getContentSize().height){
    
        return true;
    }
    return  false;
}
void MB_TableCell::activate(){
}
void MB_TableCell::selected(){
}
void MB_TableCell::unselected(){

}
