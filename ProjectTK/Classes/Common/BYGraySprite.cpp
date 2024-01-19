#include "BYGraySprite.h"

BYGraySprite::BYGraySprite()
	: m_bGray(false)
{

}

BYGraySprite::~BYGraySprite()
{

}

BYGraySprite* BYGraySprite::create(const char *pszFileName)
{
	BYGraySprite* graySprite = new BYGraySprite();
	if (graySprite && graySprite->initWithFile(pszFileName))
	{
		graySprite->autorelease();
		return graySprite;
	}
	else
	{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

BYGraySprite* BYGraySprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	return createWithSpriteFrame(pFrame);
}

BYGraySprite* BYGraySprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	BYGraySprite *pobSprite = new BYGraySprite();
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;

}

bool BYGraySprite::initWithTexture(CCTexture2D* pTexture, const CCRect& tRect ){
	do{
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));

		GLchar* pszFragSource =
			"#ifdef GL_ES \n \
			precision mediump float; \n \
			#endif \n \
			uniform sampler2D u_texture; \n \
			varying vec2 v_texCoord; \n \
			varying vec4 v_fragmentColor; \n \
			void main(void) \n \
			{ \n \
			// Convert to greyscale using NTSC weightings \n \
			vec4 col = texture2D(u_texture, v_texCoord); \n \
			float grey = dot(col.rgb, vec3(0.299, 0.387, 0.114)); \n \
			gl_FragColor = v_fragmentColor * vec4(grey, grey, grey, col.a); \n \
			}";

		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
		this->setShaderProgram(pProgram);
		pProgram->release();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);
	return false;
}

void BYGraySprite::setGray(bool bGray)
{
	m_bGray = bGray;
	GLchar* pszFragSource = NULL;
	if (m_bGray)
	{
		pszFragSource =
			"#ifdef GL_ES \n \
			precision mediump float; \n \
			#endif \n \
			uniform sampler2D u_texture; \n \
			varying vec2 v_texCoord; \n \
			varying vec4 v_fragmentColor; \n \
			void main(void) \n \
			{ \n \
			// Convert to greyscale using NTSC weightings \n \
			vec4 col = texture2D(u_texture, v_texCoord); \n \
			float grey = dot(col.rgb, vec3(0.299, 0.387, 0.114)); \n \
			gl_FragColor = v_fragmentColor * vec4(grey, grey, grey, col.a); \n \
			}";
	}
	else
	{
		pszFragSource =
			"#ifdef GL_ES \n \
			precision mediump float; \n \
			#endif \n \
			uniform sampler2D u_texture; \n \
			varying vec2 v_texCoord; \n \
			varying vec4 v_fragmentColor; \n \
			void main(void) \n \
			{ \n \
			gl_FragColor = v_fragmentColor * texture2D(u_texture, v_texCoord); \n \
			}";
	}
	CCGLProgram* pProgram = new CCGLProgram();
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
	this->setShaderProgram(pProgram);
	pProgram->release();
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->link();
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->updateUniforms();
	CHECK_GL_ERROR_DEBUG();
}

void BYGraySprite::draw(){

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformsForBuiltins();
	
	ccGLBindTexture2D( this->getTexture()->getName() );

#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}