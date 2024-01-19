#ifndef __BYGRAYSPRITE_H__
#define __BYGRAYSPRITE_H__

#include "cocoa/CCGeometry.h"
#include "cocos2d.h"

USING_NS_CC;

class  BYGraySprite : public CCSprite
{
public:
	BYGraySprite();
	virtual ~BYGraySprite();

	static BYGraySprite* create(const char *pszFileName);
	static BYGraySprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
	static BYGraySprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect);
	virtual void draw();
	void setGray(bool bGray);
	bool getGray() {return m_bGray;}
private:
	bool m_bGray;
};

#endif  // __BYGRAYSPRITE_H__