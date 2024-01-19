//
//  OCandCppHelper.h
//  ProjectTK
//
//  Created by YanJiYong on 13-1-31.
//
//c＋＋和 oc轉接類

#ifndef ProjectMB_JavaCppHelper_h
#define ProjectMB_JavaCppHelper_h
#include "Game.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
class JavaCppHelper {

private:

    JNIEnv*  m_pEnv;
    static  JavaCppHelper *m_pShareHelper;
    
public :

     JavaCppHelper();
    ~JavaCppHelper();
     static JavaCppHelper *getInstance();
     void setEnv(JNIEnv*  pEnv);
     JNIEnv*  getEnv(){
      
        return m_pEnv;
      
      }
     char * getMacAddress();
     char* jstringTostring(JNIEnv* env, jstring jstr);
     bool createFileWithPath(const char *path);    
     bool isconnectWIFI();
     bool isconnect3G();
     jstring stoJstring(JNIEnv* env, const char* pat);
     int getMem();
};
#endif
