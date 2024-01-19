

#include "CCEditBoxLoader.h"

#define PROPERTY_BACKGROUND_RESNAME "BackgroundResName"
#define PROPERTY_PLACEHOLDER        "PlaceHolder"
#define PROPERTY_LENGTH_MAX         "MaxLength"
#define PROPERTY_RETURNTYPE         "ReturnType"

NS_CC_EXT_BEGIN

void CCEditBoxLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    CCControlButtonLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
}

void CCEditBoxLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    if (strcmp( PROPERTY_BACKGROUND_RESNAME, pPropertyName) == 0)
    {
        CCSize* size = new CCSize( pNode->getContentSize());
        ((CCEditBox*)pNode)->initWithSizeAndBackgroundSprite(*size, CCScale9Sprite::create(pString), pNode->getPosition());
        CC_SAFE_DELETE(size);
    }
    else if ( strcmp( PROPERTY_PLACEHOLDER, pPropertyName) == 0)
    {
        ((CCEditBox*)pNode)->setPlaceHolder(pString);
    }
    else
    {
        CCControlButtonLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}

void CCEditBoxLoader::onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pInteger, CCBReader * pCCBReader)
{
    if (strcmp(PROPERTY_LENGTH_MAX, pPropertyName) == 0)
    {
        ((CCEditBox*)pNode)->setMaxLength(pInteger);
    }
    else if ( strcmp(PROPERTY_RETURNTYPE, pPropertyName) == 0)
    {
        ((CCEditBox*)pNode)->setReturnType((KeyboardReturnType)pInteger);
    }
}

void CCEditBoxLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader)
{
        CCControlButtonLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
}

void CCEditBoxLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, CCBReader * pCCBReader)
{
    CCControlButtonLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
}

void CCEditBoxLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader)
{
    CCControlButtonLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
}

void CCEditBoxLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, CCBReader * pCCBReader)
{
        CCControlButtonLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
}

void CCEditBoxLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader)
{
    CCControlButtonLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
}

void CCEditBoxLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader)
{
    CCControlButtonLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
}

NS_CC_EXT_END