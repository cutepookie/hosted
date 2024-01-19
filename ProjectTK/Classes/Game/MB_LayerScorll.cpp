//
//  MB_LayerScorll.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-9-2.
//
//

#include "MB_LayerScorll.h"
#include "MB_NodeShowCard.h"

#define m_fNormalVelocity 2.0f

MB_LayerScorll::MB_LayerScorll()
{
    m_pArray = new CCArray;
    m_bInMove = false;
    m_fVelocity = m_fNormalVelocity;
    m_fMaxVelocity = m_fNormalVelocity;
    m_fRunTime = 0;
    m_fMaxRunTime = 0;
}

MB_LayerScorll::~MB_LayerScorll()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}

MB_LayerScorll* MB_LayerScorll::create(CCSize size)
{
    MB_LayerScorll* ptr = new MB_LayerScorll;
    if (ptr && ptr->init(size))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}

bool MB_LayerScorll::init(CCSize size)
{
    this->setContentSize(size);
    this->setTouchEnabled(true);
    schedule(schedule_selector(MB_LayerScorll::moveTick));
    return true;
}
void MB_LayerScorll::onResetWnd()
{
    if (m_pArray->count() == 0)
    {
        return;
    }
    m_szNodeSize = ((MB_NodeShowCard*)m_pArray->objectAtIndex(0))->getContentSize();
    this->removeAllChildren();
    for (int i = 0;i<m_pArray->count();i++)
    {
        CCNode* node = (CCNode*)m_pArray->objectAtIndex(i);
        this->addChild(node);
        node->setAnchorPoint(ccp(0.5,0.5));
        node->setPosition(m_szNodeSize.width*(i+0.5),this->getContentSize().height/2);
        node->setTag(i);
    }
    
}
void MB_LayerScorll::addShowNode(CCNode* node)
{
    if (node == NULL)
    {
        return;
    }
    m_pArray->addObject(node);
}

void MB_LayerScorll::move(float dx)
{
    for (int i = 0;i < m_pArray->count();i++)
    {
        CCNode* node = this->getChildByTag(i);
        if (node == NULL)
        {
            continue;
        }
        float movedx = dx + node->getPositionX();
        if (movedx+0.5*m_szNodeSize.width < 0)
        {
            movedx += m_szNodeSize.width * m_pArray->count();
        }
        if (movedx-0.5*m_szNodeSize.width > m_szNodeSize.width*(m_pArray->count()-1))
        {
            movedx -= m_szNodeSize.width * m_pArray->count();
        }
        node->setPositionX(movedx);
    }
}

void MB_LayerScorll::moveTick(float dt)
{
    static float a = 0;
    if (m_fRunTime > 0)
    {
        a = a+dt;
        if (m_fRunTime > m_fMaxRunTime*4/5) {
            //加速
            if (m_fVelocity < m_fMaxVelocity)
            {
                float addVelocity = (dt/(m_fMaxRunTime/5)) * (m_fMaxVelocity-m_fNormalVelocity);
                m_fVelocity += (addVelocity);
            }
            else
            {
                m_fVelocity = m_fMaxVelocity;
            }
            
        }
        else if(m_fRunTime < m_fMaxRunTime*1/2)
        {
            //减速
            if (m_fVelocity > m_fNormalVelocity)
            {
                float addVelocity = (dt/(m_fMaxRunTime/2)) * (m_fMaxVelocity-m_fNormalVelocity);
                m_fVelocity -= addVelocity;
            }
            else
            {
                m_fVelocity = m_fNormalVelocity;
            }
        }
        m_fRunTime-= dt;

    }
    else
    {
        m_fVelocity = m_fNormalVelocity;
    }

    if (!m_bInMove)
    {
        move(-m_fVelocity);
    }
}

CCRect MB_LayerScorll::getViewRect()
{
    CCPoint screenPos = this->convertToWorldSpace(CCPointZero);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (CCNode *p = m_pParent; p != NULL; p = p->getParent()) {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }
    
    return CCRectMake(screenPos.x, screenPos.y, getContentSize().width*scaleX, getContentSize().height*scaleY);
}

void MB_LayerScorll::beforeDraw()
{
//    if (m_bClippingToBounds)
    {
		CCRect frame = getViewRect();
        
        glEnable(GL_SCISSOR_TEST);
        
        CCEGLView::sharedOpenGLView()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
    }
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void MB_LayerScorll::afterDraw()
{
//    if (m_bClippingToBounds)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void MB_LayerScorll::visit()
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }
    
	kmGLPushMatrix();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        this->transformAncestors();
    }
    
	this->transform();
    this->beforeDraw();
    
	if(m_pChildren)
    {
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw();
		
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}
        
	}
    else
    {
		this->draw();
    }
    
    this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }
    
	kmGLPopMatrix();
}


bool MB_LayerScorll::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_bInMove = true;
    m_TouchBegain = pTouch->getLocationInView();
    return true;
}
void MB_LayerScorll::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    move(pTouch->getLocationInView().x - m_TouchBegain.x);
    m_TouchBegain = pTouch->getLocationInView();
}
void MB_LayerScorll::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_bInMove = false;
    move(pTouch->getLocationInView().x - m_TouchBegain.x);
    m_TouchBegain = pTouch->getLocationInView();
}
void MB_LayerScorll::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,4 , false);
}

void MB_LayerScorll::runCards(float time,float MaxVelocity)
{
    m_fMaxRunTime = time;
    m_fRunTime = time;
    m_fMaxVelocity = MaxVelocity;
}
