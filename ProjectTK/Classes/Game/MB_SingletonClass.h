//
//  MB_SingletonClass.h
//  ProjectMB
//
//  Created by wenyong on 14-9-10.
//
//

#ifndef __ProjectMB__MB_SingletonClass__
#define __ProjectMB__MB_SingletonClass__

// 使用在非object子类上
template <class T>
class MB_Singleton
{
public:
    static T* getInstance()
    {
        if (m_pSingleton == 0)
        {
            m_pSingleton = new T;
        }
        return m_pSingleton;
    };
    
    static void destroyInstance()
    {
        if (m_pSingleton)
        {
            CC_SAFE_DELETE(m_pSingleton);
        }
    }
private:
    static T* m_pSingleton;
};

template<class T>
T* MB_Singleton<T>::m_pSingleton = 0;

#endif /* defined(__ProjectMB__MB_SingletonClass__) */
