
//
//  OCandCppHelper.cpp
//  ProjectTK
//
//  Created by YanJiYong on 13-1-31.
//
//

#include "JavaCppHelper.h"
#include "cocos2d.h"
using namespace cocos2d;
JavaCppHelper * JavaCppHelper::m_pShareHelper = NULL;
JavaCppHelper::JavaCppHelper(){
 
 
}
JavaCppHelper::~JavaCppHelper(){

}

JavaCppHelper *JavaCppHelper::getInstance(){

    if(m_pShareHelper == NULL){
    
        m_pShareHelper = new JavaCppHelper();
    }
    return  m_pShareHelper;

}
void JavaCppHelper::setEnv(JNIEnv*  pEnv){

     m_pEnv = pEnv;
}
char * JavaCppHelper::getMacAddress(){
       
     std::string package =  CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
     package += "JavaToCppHelper";
     jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
     jmethodID getAddress = (m_pEnv)->GetStaticMethodID(javaHelper, "getMacAddress","()Ljava/lang/String;");
     jstring	jstr = (jstring) (m_pEnv)->CallStaticObjectMethod(javaHelper, getAddress);
     return jstringTostring(m_pEnv,jstr);
 }   
bool JavaCppHelper::createFileWithPath(const char *path){

        return false;
 
}
bool JavaCppHelper::isconnectWIFI(){

    std::string package =  CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
     package += "JavaToCppHelper";
     jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
    jmethodID getWifi = (m_pEnv)->GetStaticMethodID(javaHelper, "isconnectWIFI","()Z");
    jboolean	isconnect = (m_pEnv)->CallStaticBooleanMethod(javaHelper, getWifi);  
    return isconnect == 1;
}
int JavaCppHelper::getMem(){
    std::string package =  CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
     package += "JavaToCppHelper";
     jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
    jmethodID getm = (m_pEnv)->GetStaticMethodID(javaHelper, "getRam","()I");
    jint mem = (m_pEnv)->CallStaticIntMethod(javaHelper, getm);  
    return (int)mem;
}
bool JavaCppHelper::isconnect3G(){

     std::string package =  CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
     package += "JavaToCppHelper";
     jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
     jmethodID get3G = (m_pEnv)->GetStaticMethodID(javaHelper, "isconnect3G","()Z");
     jboolean	isconnect = (m_pEnv)->CallStaticBooleanMethod(javaHelper,get3G);
     m_pEnv->DeleteLocalRef (javaHelper);   
     return isconnect == 1 ;
 }

 char* JavaCppHelper::jstringTostring(JNIEnv* env, jstring jstr){

	 char* rtn = NULL;
	 jclass clsstring = env->FindClass("java/lang/String");
	 jstring strencode = env->NewStringUTF("utf-8");
	 jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	 jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	 jsize alen = env->GetArrayLength(barr);
	 jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	 if (alen > 0)
	 {
		 rtn = (char*)malloc(alen + 1);

		 memcpy(rtn, ba, alen);
		 rtn[alen] = 0;
	 }
	 env->ReleaseByteArrayElements(barr, ba, 0);
	 return rtn;
  }
jstring JavaCppHelper::stoJstring(JNIEnv* env, const char* pat){

    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = env->NewStringUTF("utf-8");
    jstring jstr = (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
    env->DeleteLocalRef (bytes);
    env->DeleteLocalRef (strClass);
    return jstr;
}
