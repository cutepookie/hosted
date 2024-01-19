//
//  RichText.h
//  ProjectPM
//
//  Created by chenhongkun on 14-8-26.
//
//

#ifndef __ProjectMB__RichText__
#define __ProjectMB__RichText__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;



/**********************************************************************
 [color=ffffff]text[/color]
 [br]
 [link=ffffff=01]text[/link]
 **********************************************************************/
class RichText;
class RichTextDelegate
{
public:
	virtual void onClickedTextTTF(RichText * obj,int id,CCTouch *pTouch)=0;
};

struct ColorBrLinkChar;
class RichText : public CCSprite , public CCTouchDelegate
{
public:
    
	struct ClickedInfo
	{
		ClickedInfo():InfoID(0),TouchID(-1){};
		ClickedInfo(const CCRect & _rect,int infoid):rect(_rect),InfoID(infoid){};
		CCRect rect;
		int InfoID;
		int TouchID;
	};
    
    static RichText* create(const char *string = "", float fontSize = 24,
                            const cocos2d::CCSize &dimensions = CCSizeMake(0, 0), CCTextAlignment hAlignment = kCCTextAlignmentLeft,
                            CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop)
    {
        RichText* p = new RichText();
        if(p)
        {
            p->autorelease();
            p->initWithString(string, "", fontSize,dimensions,hAlignment,vAlignment);
            p->setAnchorPoint(ccp(0,1));
            return p;
        }
        CC_SAFE_RELEASE_NULL(p);
        return NULL;
    }

	RichText();
	~RichText();
    
	bool initWithString(const char *string, const char *fontName, float fontSize,
                        const cocos2d::CCSize &dimensions, CCTextAlignment hAlignment,
                        CCVerticalTextAlignment vAlignment);
	bool initWithString(const char *string, const char *fontName, float fontSize);
    
    
	//touch
	void setSwallowsTouches(bool bSwallowsTouches);
	void setTouchPriorityLHS(int priority);
    
    
	virtual bool isEnabled();
	virtual void setEnabled(bool value);
    
	//string
	void setString(const char * str);
	const char * getString();
    
    
	void setDelegate(RichTextDelegate * _delegate);
    
    
public:
	void onEnterTransitionDidFinish();
	void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void setDimensionsSize(CCSize size);
    
private:
	void _updateTexture();
	std::vector<ColorBrLinkChar> * _analyzeString(bool * out_is_pag);
	void _RequestTexture(std::vector<ColorBrLinkChar> * pColorBrLinkCharList,bool isPag);
	void _IntegrationTexture(std::vector<ColorBrLinkChar> * pColorBrLinkCharList);
	int _WriteALineLeft(unsigned char * Buff,std::vector<ColorBrLinkChar> * pColorBrLinkCharList,int Index,int LineWidth,int LineHeight,int BufWidth,int BufHeight,int VerticalIndex);
	int _WriteALineCenter(unsigned char * Buff,std::vector<ColorBrLinkChar> * pColorBrLinkCharList,int Index,int LineWidth,int LineHeight,int BufWidth,int BufHeight,int VerticalIndex);
	int _WriteALineRight(unsigned char * Buff,std::vector<ColorBrLinkChar> * pColorBrLinkCharList,int Index,int LineWidth,int LineHeight,int BufWidth,int BufHeight,int VerticalIndex);
	void _TransClickedInfoListForCopy(const CCPoint & offsetPos);
    
protected:
	std::string m_Text;
	CCSize m_Dimensions;
	std::string m_FontName;
	float m_FontSize;
	CCTextAlignment         m_hAlignment;
	CCVerticalTextAlignment m_vAlignment;
    
protected:
	int m_TouchPriority;
	bool m_SwallowsTouches;
	RichTextDelegate * m_Delegate;
	std::list<ClickedInfo> m_ClickeList;
	bool m_Enabled;
};


#endif /* defined(__ProjectMB__RichText__) */
