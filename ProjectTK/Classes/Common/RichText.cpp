//
//  RichText.cpp
//  ProjectPM
//
//  Created by chenhongkun on 14-8-26.
//
//

#include "RichText.h"
USING_NS_CC_EXT;
#if CC_USE_LA88_LABELS
#define SHADER_PROGRAM kCCShader_PositionTextureColor
#else
#define SHADER_PROGRAM kCCShader_PositionTextureA8Color
#endif









static const char utf8_skip_data[256] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
    5, 5, 5, 6, 6, 1, 1
};

static const char *const g_utf8_skip = utf8_skip_data;

#define cc_utf8_next_char(p) (char *)((p) + g_utf8_skip[*(unsigned char *)(p)])



struct ColorBrLinkChar
{
	ColorBrLinkChar():_Image(NULL),_IsBr(false),_IsLink(false),_Color(ccc3(0xff,0xff,0xff)),_LineColor(ccc3(0xff,0xff,0x00)),_LinkID(0){};
	ColorBrLinkChar(const char * _char,bool _IsBr,bool _IsLink,const ccColor3B & c3b,const ccColor3B & lc3b,unsigned short linkid)
    :_Image(NULL),_Char(_char),_IsBr(_IsBr),_IsLink(_IsLink),_Color(c3b),_LineColor(lc3b),_LinkID(linkid){};
	~ColorBrLinkChar(){if(_Image){
        _Image->release();
        _Image=NULL;
    }}
	ccColor3B _Color;
	ccColor3B _LineColor;
	bool _IsBr;
	bool _IsLink;
	unsigned short _LinkID;
	std::string _Char;
	CCImage * _Image;
};

RichText::RichText()
:m_Dimensions(CCSizeZero)
,m_FontSize(24.0f)
,m_FontName("")
,m_TouchPriority(0)
,m_SwallowsTouches(true)
,m_hAlignment(kCCTextAlignmentCenter)
,m_vAlignment(kCCVerticalTextAlignmentTop)
,m_Delegate(NULL)
,m_Enabled(true)
{
	
}

RichText::~RichText()
{
    
}

void RichText::setDimensionsSize(CCSize size)
{
    m_Dimensions = size;
    _updateTexture();
}

void RichText::setString( const char * str )
{
	CCAssert(str,"error");
    
	if(m_Text.compare(str))
	{
		m_Text = str;
		this->_updateTexture();
	}
}
const char * RichText::getString()
{
	return m_Text.c_str();
}

void RichText::_updateTexture()
{
	if(m_Text.compare(""))
	{
		bool isPag = false;
		std::vector<ColorBrLinkChar> * pColorBrLinkCharList = _analyzeString(&isPag);
		this->_RequestTexture(pColorBrLinkCharList,isPag);
		delete pColorBrLinkCharList;
	}else
	{
		CCTexture2D * pTexture = new CCTexture2D();
        pTexture->initWithString("",m_FontName.c_str(),m_FontSize);
//		pTexture->initWithString("",CCSizeZero/*m_Dimensions*/,m_hAlignment,m_vAlignment,m_FontName.c_str(),m_FontSize);
		this->setTexture(pTexture);
		pTexture->release();
		CCRect rect = CCRectZero;
		rect.size = m_pobTexture->getContentSize();
		this->setTextureRect(rect);
	}
    getShaderProgram()->updateUniforms();
}

std::vector<ColorBrLinkChar> * RichText::_analyzeString(bool * out_is_pag)
{
	std::vector<ColorBrLinkChar> * ReturnString = new std::vector<ColorBrLinkChar>();
    
	const char * pText = m_Text.c_str();
	unsigned int mLen = strlen(pText);
//	unsigned int zLen =	cc_utf8_strlen(pText,-1);
    
	bool LastIsLink = false;
	bool LastIsBr = false;
	unsigned short LastLinkID = 0;
    
	std::list<ccColor3B> TextColorQueue;
	TextColorQueue.push_back(ccc3(0xff,0xff,0xff));
    
	std::list<ccColor3B> LineColorQueue;
	LineColorQueue.push_back(ccc3(0xff,0xff,0x00));
    
	char pTempStr[7]={0};
	const char * pCurrent=pText;
	unsigned int flen = 0;
	do
	{
		memset(pTempStr,0,sizeof(pTempStr));
		const char * pOrigin = pCurrent;
		pCurrent = cc_utf8_next_char (pOrigin);
		flen += pCurrent-pOrigin;
		memcpy(pTempStr,pOrigin,pCurrent-pOrigin);
        
		if(!strcmp(pTempStr,"["))
		{
			if(flen<mLen-2)
			{
				if(pCurrent[0]=='b' && pCurrent[1]=='r' && pCurrent[2]==']')
				{
					LastIsBr = true;
					pCurrent+=3;
					flen+=3;
					*out_is_pag = true;
					continue;
				}
				if(flen<mLen-5)
				{
					if(pCurrent[0]=='/' && pCurrent[1]=='l' && pCurrent[2]=='i' && pCurrent[3]=='n' && pCurrent[4]=='k' && pCurrent[5]==']')
					{
						if(LineColorQueue.size()>1)
							LineColorQueue.pop_back();
#if (DEF_IS_TEST)
						else CCAssert(false,"error");
#endif
						LastLinkID = 0;
						LastIsLink = false;
						pCurrent+=6;
						flen+=6;
						*out_is_pag = true;
						continue;
					}
					if(flen<mLen-6)
					{
						if(pCurrent[0]=='/' && pCurrent[1]=='c' && pCurrent[2]=='o' && pCurrent[3]=='l' && pCurrent[4]=='o' && pCurrent[5]=='r' && pCurrent[6]==']')
						{
							if(TextColorQueue.size()>1)
								TextColorQueue.pop_back();
#if (DEF_IS_TEST)
							else CCAssert(false,"error");
#endif
							pCurrent+=7;
							flen+=7;
							*out_is_pag = true;
							continue;
						}
						if(flen<mLen-12)
						{
							if(pCurrent[0]=='c' && pCurrent[1]=='o' && pCurrent[2]=='l' && pCurrent[3]=='o' && pCurrent[4]=='r' && pCurrent[5]=='=')
							{
								char tempColorStr[7]={0};
								memcpy(tempColorStr,&(pCurrent[6]),6);
								int ColorRGB=0;
								sscanf(tempColorStr,"%x",&ColorRGB);
								TextColorQueue.push_back(ccc3(ColorRGB>>16,ColorRGB>>8,ColorRGB));
								pCurrent+=13;
								flen+=13;
								*out_is_pag = true;
								continue;
							}
							if(flen<mLen-14)
							{
								if(pCurrent[0]=='l' && pCurrent[1]=='i' && pCurrent[2]=='n' && pCurrent[3]=='k' && pCurrent[4]=='=')
								{
									char tempColorStr[7]={0};
									memcpy(tempColorStr,&(pCurrent[5]),6);
									int ColorRGB=0;
									sscanf(tempColorStr,"%x",&ColorRGB);
									LineColorQueue.push_back(ccc3(ColorRGB>>16, ColorRGB>>8,ColorRGB));
									char tempLinkIDStr[3]={0};
									memcpy(tempLinkIDStr,&(pCurrent[12]),2);
									LastLinkID = atoi(tempLinkIDStr);
									LastIsLink = true;
									pCurrent+=15;
									flen+=15;
									*out_is_pag = true;
									continue;
								}
							}
						}
					}
				}
			}
		}
        
		ReturnString->push_back(ColorBrLinkChar(pTempStr,LastIsBr,LastIsLink,TextColorQueue.back(),LineColorQueue.back(),LastLinkID));
		LastIsBr = false;
        
	} while (*pCurrent);
    
    //#if (DEF_IS_TEST)
    //	for (std::vector<ColorBrLinkChar>::iterator it = ReturnString->begin();it!=ReturnString->end();it++)
    //	{
    //		CCLog("Char:%s IsBr:%d IsLink:%d Color:R:%x G:%x B:%x LineColor:R:%x G:%x B:%x LinkID:%d",(*it)._Char.c_str(),(int)(*it)._IsBr,(int)(*it)._IsLink,(*it)._Color.r,(*it)._Color.g,(*it)._Color.b,(*it)._LineColor.r,(*it)._LineColor.g,(*it)._LineColor.b,(int)((*it)._LinkID));
    //	}
    //#endif
    
	return ReturnString;
}

void RichText::_RequestTexture( std::vector<ColorBrLinkChar> * pColorBrLinkCharList,bool isPag)
{
	if(isPag || ((int)m_Dimensions.width)!=0 || ((int)m_Dimensions.height)!=0)
	{
		for (std::vector<ColorBrLinkChar>::iterator it = pColorBrLinkCharList->begin();it!=pColorBrLinkCharList->end();)
		{
			(*it)._Image = new CCImage();
			(*it)._Image->initWithString((*it)._Char.c_str(),0,0,CCImage::kAlignCenter,m_FontName.c_str(),m_FontSize*CCDirector::sharedDirector()->getContentScaleFactor());
#if (DEF_IS_TEST)
			CCAssert((*it)._Image->hasAlpha(),"error");
#endif
			//isgraph(*(*it)._Char.c_str());
			if(!(*it)._Image->getData())
				it = pColorBrLinkCharList->erase(it);
			else
				it++;
		}
		this->_IntegrationTexture(pColorBrLinkCharList);
	}else
	{
		CCTexture2D * pTexture = new CCTexture2D();
        pTexture->initWithString(m_Text.c_str(), m_FontName.c_str(), m_FontSize, CCSizeZero, m_hAlignment, m_vAlignment);
//		pTexture->initWithString(m_Text.c_str(),CCSizeZero/*m_Dimensions*/,m_hAlignment,m_vAlignment,m_FontName.c_str(),m_FontSize);
		this->setTexture(pTexture);
		pTexture->release();
		CCRect rect = CCRectZero;
		rect.size = m_pobTexture->getContentSize();
		this->setTextureRect(rect);
	}
}

void RichText::_IntegrationTexture( std::vector<ColorBrLinkChar> * pColorBrLinkCharList )
{
	int Dwidth = m_Dimensions.width;
	int Dheight = m_Dimensions.height;
    
	int MaxWidth = 0;
	int MaxHeight = 0;
	int TransWidth = 0;
	int TransHeight = 0;
	int Vertical = 1;
	int CopyWidth = 0;
	int CopyHeight = 0;
	for (std::vector<ColorBrLinkChar>::iterator it = pColorBrLinkCharList->begin();it!=pColorBrLinkCharList->end();it++)
	{
		unsigned short width = (*it)._Image->getWidth();
		unsigned short height = (*it)._Image->getHeight();
		unsigned char * data = (*it)._Image->getData();
		if((*it)._Color.r!=0xff || (*it)._Color.g!=0xff || (*it)._Color.b!=0xff)
		{
			//unsigned int color =  ((0xff)<<24)|(((*it)._Color.b)<<16)|(((*it)._Color.g)<<8)|((*it)._Color.r);
			for (unsigned short index = 0; index<height*width*4 ; index+=4)
				if(data[index])
					//*((unsigned int*)&(data[index])) = color;
					*((unsigned int*)&(data[index]))=((data[index+3])<<24)|(((*it)._Color.b)<<16)|(((*it)._Color.g)<<8)|((*it)._Color.r);
		}
		if((*it)._IsLink)
		{
			unsigned int linecolor =  ((0xff)<<24)|(((*it)._LineColor.b)<<16)|(((*it)._LineColor.g)<<8)|((*it)._LineColor.r);
			int lineW = ceil(height/30.0f);
			for (int index = width*(height-lineW)*4;index<height*width*4 ; index+=4)
				*((unsigned int*)&(data[index]))=linecolor;
		}
        
		do
		{
			if(TransHeight<height)
			{
#if (DEF_IS_TEST)
				CCAssert(TransHeight==0,"error");
#endif
				TransHeight = height;
			}
			if((*it)._IsBr)
			{
				Vertical++;
				TransWidth = width;
				MaxHeight += TransHeight;
				break;
			}else if(Dwidth!=0 && TransWidth+width>Dwidth)
			{
				Vertical++;
				TransWidth = width;
				MaxHeight += TransHeight;
				break;
			}
			TransWidth += width;
			if(TransWidth>MaxWidth)
				MaxWidth = TransWidth;
		} while (false);
	}
	MaxHeight += TransHeight;
	CopyWidth = MaxWidth;
	CopyHeight = MaxHeight;
	if(Dheight!=0 && MaxHeight>Dheight)
		MaxHeight = Dheight;
    
	unsigned char * TextureData = new unsigned char[MaxWidth*MaxHeight*4];
	memset(TextureData,0,MaxWidth*MaxHeight*4);
    
	if(Vertical==1)
	{
		if(m_vAlignment==kCCVerticalTextAlignmentTop)
		{
			for (int h = 0;h<MaxHeight;h++)
			{
				int w = 0;
				for (std::vector<ColorBrLinkChar>::iterator it = pColorBrLinkCharList->begin();it!=pColorBrLinkCharList->end();it++)
				{
					unsigned short width = (*it)._Image->getWidth();
					unsigned short height = (*it)._Image->getHeight();
					unsigned char * data = (*it)._Image->getData();
					if(0==h && (*it)._IsLink)
						m_ClickeList.push_back(ClickedInfo(CCRect(w,0,width,MaxHeight),(*it)._LinkID));
					if(h<height)
						memcpy(&(TextureData[(h*MaxWidth+w)*4]),&(data[(h*width)*4]),width*4);
					w+=width;
				}
			}
		}else if(m_vAlignment==kCCVerticalTextAlignmentBottom)
		{
			for (int h = MaxHeight-1,i = 0;h>=0;h--,i++)
			{
				int w = 0;
				for (std::vector<ColorBrLinkChar>::iterator it = pColorBrLinkCharList->begin();it!=pColorBrLinkCharList->end();it++)
				{
					unsigned short width = (*it)._Image->getWidth();
					unsigned short height = (*it)._Image->getHeight();
					unsigned char * data = (*it)._Image->getData();
					if(MaxHeight-1==h && (*it)._IsLink)
						m_ClickeList.push_back(ClickedInfo(CCRect(w,0,width,MaxHeight),(*it)._LinkID));
					int th = (height-1-i);
					if(th<height && th>=0)
						memcpy(&(TextureData[(h*MaxWidth+w)*4]),&(data[(th*width)*4]),width*4);
					w+=width;
				}
			}
		}else if(m_vAlignment==kCCVerticalTextAlignmentCenter)
		{
			int halfH = MaxHeight/2;
			for (int h = halfH,i = 0;h<MaxHeight;h++,i++)
			{
				int w = 0;
				for (std::vector<ColorBrLinkChar>::iterator it = pColorBrLinkCharList->begin();it!=pColorBrLinkCharList->end();it++)
				{
					unsigned short width = (*it)._Image->getWidth();
					unsigned short height = (*it)._Image->getHeight();
					unsigned char * data = (*it)._Image->getData();
					if(halfH==h && (*it)._IsLink)
						m_ClickeList.push_back(ClickedInfo(CCRect(w,0,width,MaxHeight),(*it)._LinkID));
					int th = (height/2+i);
					if(th<height)
						memcpy(&(TextureData[(h*MaxWidth+w)*4]),&(data[(th*width)*4]),width*4);
					w+=width;
				}
			}
			for (int h = halfH-1,i = 0;h>=0;h--,i++)
			{
				int w = 0;
				for (std::vector<ColorBrLinkChar>::iterator it = pColorBrLinkCharList->begin();it!=pColorBrLinkCharList->end();it++)
				{
					unsigned short width = (*it)._Image->getWidth();
					unsigned short height = (*it)._Image->getHeight();
					unsigned char * data = (*it)._Image->getData();
					int th = (height/2-i);
					if(th<height && th>=0)
						memcpy(&(TextureData[(h*MaxWidth+w)*4]),&(data[(th*width)*4]),width*4);
					w+=width;
				}
			}
		}
	}else
	{
		unsigned char * CopyTextureData = NULL;
		if(CopyWidth!=MaxWidth || CopyHeight!=MaxHeight)
		{
			CopyTextureData = new unsigned char[CopyWidth*CopyHeight*4];
			memset(CopyTextureData,0,CopyWidth*CopyHeight*4);
		}else CopyTextureData = TextureData;
        
		switch (m_hAlignment)
		{
            case kCCTextAlignmentLeft:
			{
				int VectorIndex = 0;
				for (int i=0;i<Vertical;i++)
					VectorIndex = _WriteALineLeft(&(CopyTextureData[CopyWidth*(CopyHeight/Vertical*i)*4]),pColorBrLinkCharList,VectorIndex,CopyWidth,CopyHeight/Vertical,CopyWidth,CopyHeight,i);
			}
                break;
            case kCCTextAlignmentCenter:
			{
				int VectorIndex = 0;
				for (int i=0;i<Vertical;i++)
					VectorIndex = _WriteALineCenter(&(CopyTextureData[CopyWidth*(CopyHeight/Vertical*i)*4]),pColorBrLinkCharList,VectorIndex,CopyWidth,CopyHeight/Vertical,CopyWidth,CopyHeight,i);
			}
                break;
            case kCCTextAlignmentRight:
			{
				int VectorIndex = 0;
				for (int i=0;i<Vertical;i++)
					VectorIndex = _WriteALineRight(&(CopyTextureData[CopyWidth*(CopyHeight/Vertical*i)*4]),pColorBrLinkCharList,VectorIndex,CopyWidth,CopyHeight/Vertical,CopyWidth,CopyHeight,i);
			}
                break;
		}
        
		if(CopyTextureData != TextureData)
		{
			switch (m_vAlignment)
			{
                case kCCVerticalTextAlignmentTop:
				{
					for (int h = 0;h<MaxHeight;h++)
						memcpy(&(TextureData[h*MaxWidth*4]),&(CopyTextureData[h*MaxWidth*4]),MaxWidth*4);
					_TransClickedInfoListForCopy(ccp(0,-(CopyHeight-MaxHeight)));
				}
                    break;
                case kCCVerticalTextAlignmentCenter:
				{
					int StartHeight = (CopyHeight-MaxHeight)/2;
					for (int h = 0;h<MaxHeight;h++)
						memcpy(&(TextureData[h*MaxWidth*4]),&(CopyTextureData[(h+StartHeight)*MaxWidth*4]),MaxWidth*4);
					_TransClickedInfoListForCopy(ccp(0,(CopyHeight-MaxHeight)/-2));
				}
                    break;
                case kCCVerticalTextAlignmentBottom:
				{
					for (int h = MaxHeight-1,i=1;h>=0;h--,i++)
						memcpy(&(TextureData[h*MaxWidth*4]),&(CopyTextureData[(CopyHeight-i)*MaxWidth*4]),MaxWidth*4);
				}
                    break;
			}
			delete[] CopyTextureData;
		}
	}
    
	CCTexture2D * pTexture2D = new CCTexture2D();
	pTexture2D->initWithData(TextureData,kCCTexture2DPixelFormat_RGBA8888,MaxWidth,MaxHeight,CCSizeMake(MaxWidth,MaxHeight));
	this->setTexture(pTexture2D);
	pTexture2D->release();
	CCRect rect = CCRectZero;
	rect.size = m_pobTexture->getContentSize();
	this->setTextureRect(rect);
	delete [] TextureData;
}

void RichText::_TransClickedInfoListForCopy( const CCPoint & offsetPos )
{
	for(std::list<ClickedInfo>::iterator it = m_ClickeList.begin();it!=m_ClickeList.end();)
	{
		(*it).rect.origin.x+=offsetPos.x;
		(*it).rect.origin.y+=offsetPos.y;
		if((*it).rect.origin.y+(*it).rect.size.height<=0.0f)
			it = m_ClickeList.erase(it);
		else
			it++;
	}
}

int RichText::_WriteALineLeft( unsigned char * Buff,std::vector<ColorBrLinkChar> * pColorBrLinkCharList,int Index,int LineWidth,int LineHeight,int BufWidth,int BufHeight,int VerticalIndex )
{
	int Ret = Index;
	for (int h = 0;h<LineHeight;h++)
	{
		int w = 0;
		for (int i = Index;i<pColorBrLinkCharList->size();i++)
		{
			ColorBrLinkChar * pColorBrLinkChar = &((*pColorBrLinkCharList)[i]);
            
			Ret = i;
			if(i!=Index && pColorBrLinkChar->_IsBr)
				break;
            
			unsigned short width = pColorBrLinkChar->_Image->getWidth();
			unsigned short height = pColorBrLinkChar->_Image->getHeight();
			unsigned char * data = pColorBrLinkChar->_Image->getData();
            
			if(w+width>LineWidth)
				break;
            
			if(0==h && pColorBrLinkChar->_IsLink)
				m_ClickeList.push_back(ClickedInfo(CCRect(w,BufHeight-(VerticalIndex*height+height),width,height),pColorBrLinkChar->_LinkID));
            
			if(h<height)
				memcpy(&(Buff[(h*LineWidth+w)*4]),&(data[(h*width)*4]),width*4);
            
			w+=width;
		}
	}
	return Ret;
}

int RichText::_WriteALineCenter( unsigned char * Buff,std::vector<ColorBrLinkChar> * pColorBrLinkCharList,int Index,int LineWidth,int LineHeight,int BufWidth,int BufHeight,int VerticalIndex )
{
	int RealWidth = 0;
	for (int i = Index;i<pColorBrLinkCharList->size();i++)
	{
		ColorBrLinkChar * pColorBrLinkChar = &((*pColorBrLinkCharList)[i]);
		if(i!=Index && pColorBrLinkChar->_IsBr)
			break;
		unsigned short width = pColorBrLinkChar->_Image->getWidth();
		if(RealWidth+width>LineWidth)
			break;
		RealWidth += width;
	}
#if (DEF_IS_TEST)
	CCAssert((LineWidth-RealWidth)>=0,"error");
#endif
	int StarWidth = (LineWidth-RealWidth)/2;
	if(StarWidth<0){StarWidth = 0;}
    
	int Ret = Index;
	for (int h = 0;h<LineHeight;h++)
	{
		int w = StarWidth;
		for (int i = Index;i<pColorBrLinkCharList->size();i++)
		{
			ColorBrLinkChar * pColorBrLinkChar = &((*pColorBrLinkCharList)[i]);
            
			Ret = i;
			if(i!=Index && pColorBrLinkChar->_IsBr)
				break;
            
			unsigned short width = pColorBrLinkChar->_Image->getWidth();
			unsigned short height = pColorBrLinkChar->_Image->getHeight();
			unsigned char * data = pColorBrLinkChar->_Image->getData();
            
			if(w+width>LineWidth)
				break;
            
			if(0==h && pColorBrLinkChar->_IsLink)
				m_ClickeList.push_back(ClickedInfo(CCRect(w,BufHeight-(VerticalIndex*height+height),width,height),pColorBrLinkChar->_LinkID));
            
			if(h<height)
				memcpy(&(Buff[(h*LineWidth+w)*4]),&(data[(h*width)*4]),width*4);
            
			w+=width;
		}
	}
	return Ret;
}

int RichText::_WriteALineRight( unsigned char * Buff,std::vector<ColorBrLinkChar> * pColorBrLinkCharList,int Index,int LineWidth,int LineHeight,int BufWidth,int BufHeight,int VerticalIndex )
{
	int RealWidth = 0;
	for (int i = Index;i<pColorBrLinkCharList->size();i++)
	{
		ColorBrLinkChar * pColorBrLinkChar = &((*pColorBrLinkCharList)[i]);
		if(i!=Index && pColorBrLinkChar->_IsBr)
			break;
		unsigned short width = pColorBrLinkChar->_Image->getWidth();
		if(RealWidth+width>LineWidth)
			break;
		RealWidth += width;
	}
#if (DEF_IS_TEST)
	CCAssert((LineWidth-RealWidth)>=0,"error");
#endif
	int StarWidth = LineWidth-RealWidth;
	if(StarWidth<0){StarWidth = 0;}
    
	int Ret = Index;
	for (int h = 0;h<LineHeight;h++)
	{
		int w = StarWidth;
		for (int i = Index;i<pColorBrLinkCharList->size();i++)
		{
			ColorBrLinkChar * pColorBrLinkChar = &((*pColorBrLinkCharList)[i]);
            
			Ret = i;
			if(i!=Index && pColorBrLinkChar->_IsBr)
				break;
            
			unsigned short width = pColorBrLinkChar->_Image->getWidth();
			unsigned short height = pColorBrLinkChar->_Image->getHeight();
			unsigned char * data = pColorBrLinkChar->_Image->getData();
            
			if(w+width>LineWidth)
				break;
            
			if(0==h && pColorBrLinkChar->_IsLink)
				m_ClickeList.push_back(ClickedInfo(CCRect(w,BufHeight-(VerticalIndex*height+height),width,height),pColorBrLinkChar->_LinkID));
            
			if(h<height)
				memcpy(&(Buff[(h*LineWidth+w)*4]),&(data[(h*width)*4]),width*4);
            
			w+=width;
		}
	}
	return Ret;
}

void RichText::setSwallowsTouches( bool bSwallowsTouches )
{
	if(m_SwallowsTouches!=bSwallowsTouches)
	{
		m_SwallowsTouches = bSwallowsTouches;
		CCTouchDispatcher * pTouchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		CCTargetedTouchHandler * pTargetedTouchHandler = dynamic_cast<CCTargetedTouchHandler*>(pTouchDispatcher->findHandler(this));
		if(pTargetedTouchHandler)
			pTargetedTouchHandler->setSwallowsTouches(m_SwallowsTouches);
	}
}

void RichText::setTouchPriorityLHS( int priority )
{
	if(m_TouchPriority!=priority)
	{
		m_TouchPriority = priority;
		CCTouchDispatcher * pTouchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		CCTouchHandler * pTouchHandler = pTouchDispatcher->findHandler(this);
		if(pTouchHandler)
			pTouchDispatcher->setPriority(m_TouchPriority,this);
	}
}

void RichText::onEnterTransitionDidFinish()
{
	CCSprite::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_TouchPriority, m_SwallowsTouches);
}

void RichText::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool RichText::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	for (CCNode *c = this->getParent(); c != NULL; c = c->getParent())
		if (c->isVisible() == false)
			return false;
    
    for (CCNode *c = this->getParent(); c != NULL; c = c->getParent())
    {
        CCScrollView* pScrollView = dynamic_cast<CCScrollView*>(c);
        if(pScrollView)
        {
            CCPoint pos = pTouch->getLocation();
			CCPoint viewPos = pScrollView->getParent()->convertToWorldSpace(pScrollView->getPosition());
			CCSize viewSize = pScrollView->getViewSize();
			CCRect viewRect(viewPos.x, viewPos.y, viewSize.width, viewSize.height);
			if (!viewRect.containsPoint(pos))
				return false;
        }
    }
    
	bool ret = false;
	if(m_Delegate && this->getParent() && m_bVisible && m_Enabled)
	{
		if(this->boundingBox().containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch)))
		{
			CCPoint pos = this->convertTouchToNodeSpace(pTouch);
			for (std::list<ClickedInfo>::iterator it = m_ClickeList.begin();it!=m_ClickeList.end();it++)
			{
				if((*it).rect.containsPoint(pos))
				{
					(*it).TouchID = pTouch->getID();
					ret = true;
				}
			}
		}
	}
	return ret;
}

void RichText::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_Delegate && this->getParent() && m_bVisible && m_Enabled)
	{
		if(this->boundingBox().containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch)))
		{
			CCPoint pos = this->convertTouchToNodeSpace(pTouch);
			for (std::list<ClickedInfo>::iterator it = m_ClickeList.begin();it!=m_ClickeList.end();it++)
			{
				if((*it).TouchID == pTouch->getID() && (*it).rect.containsPoint(pos))
				{
#if (DEF_IS_TEST)
					CCLog("ClickedText ID: %d",(*it).InfoID);
#endif
					int id = (*it).InfoID;
					(*it).TouchID = -1;
					m_Delegate->onClickedTextTTF(this,id,pTouch);
					return ;
				}
			}
		}
	}
}

void RichText::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	for (std::list<ClickedInfo>::iterator it = m_ClickeList.begin();it!=m_ClickeList.end();it++)
		(*it).TouchID = -1;
}

bool RichText::initWithString( const char *string, const char *fontName, float fontSize, const cocos2d::CCSize &dimensions, CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
	if(CCSprite::init())
	{
		this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));
		m_Dimensions = CCSizeMake(dimensions.width, dimensions.height);
		m_hAlignment = hAlignment;
		m_vAlignment = vAlignment;
		m_FontName = fontName;
		m_FontSize = fontSize;
		this->setString(string);
		return true;
	}
	return false;
}

bool RichText::initWithString( const char *string, const char *fontName, float fontSize )
{
	return this->initWithString(string,fontName,fontSize,CCSizeMake(0.0f,0.0f),kCCTextAlignmentCenter,kCCVerticalTextAlignmentTop);
}

void RichText::setDelegate( RichTextDelegate * _delegate )
{
	m_Delegate = _delegate;
}

bool RichText::isEnabled()
{
	return m_Enabled;
}

void RichText::setEnabled( bool value )
{
	m_Enabled = value;
}
