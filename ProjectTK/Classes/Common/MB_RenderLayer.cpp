//
//  MB_RenderLayer.cpp
//  ProjectPM
//
//  Created by crimoon on 14-7-1.
//
//

#include "MB_RenderLayer.h"
MB_RenderLayer::MB_RenderLayer(){

}
MB_RenderLayer::~MB_RenderLayer(){

}

void MB_RenderLayer::setFileAndPos(CCSprite *sprite2, const char * filename ,cocos2d::CCPoint point,float scale){

    CCSize size =CCDirector::sharedDirector()->getWinSize();
    MB_RenderSprite * sprite = MB_RenderSprite::create(filename);
//    sprite->setPosition(point);
    sprite->setScale(scale);
    
    CCRenderTexture * m_nDarkLayer;
    m_nDarkLayer = CCRenderTexture::create(size.width, size.height);
    m_nDarkLayer->clear(0,0,0,0.7f);
    m_nDarkLayer->begin();
    sprite->visit();
    m_nDarkLayer->end();
    
   // CCSprite *sprite3 = CCSprite::createWithTexture(m_nDarkLayer->getSprite()->getTexture());

    sprite2->setTextureRect(sprite->getTextureRect());
    sprite2->initWithTexture(m_nDarkLayer->getSprite()->getTexture());
    sprite2->setFlipY(true);
    //CCPoint point2 = ccp(size.width/2.0f,size.height/2.0f);
    //point2 = sprite2->getParent()->convertToNodeSpace(point2);
    //sprite2->setPosition(point2);

    

}
MB_RenderSprite::MB_RenderSprite(){

    isDraw = false;
}
MB_RenderSprite::~MB_RenderSprite(){

}
bool MB_RenderSprite::init(const char * filename){

    CCSprite::initWithFile(filename);
    return true;
}
MB_RenderSprite *  MB_RenderSprite::create(const char *filename){

    MB_RenderSprite * ptr = new MB_RenderSprite();
    if( ptr && ptr->init(filename)){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
    
}
void  MB_RenderSprite::draw(){

    CCSprite::draw();//如果不取消的话如果两个lightCCSPrite對象只有一个会產生亮光
    

    // glClear(GL_COLOR_BUFFER_BIT);
    //glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA); //
    glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
    //glColorMask(0.0f, 0.0f, 0.0f, 0.5f);//關键句
    glColorMask(0.0f, 0.0f, 0.0f, 6.0f);
#define kQuadSize sizeof(m_sQuad.bl)
    if (m_pobTexture)
    {
        glBindTexture(GL_TEXTURE_2D, m_pobTexture->getName());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    long offset = (long)&m_sQuad;
    
	// vertex
	int  diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
}