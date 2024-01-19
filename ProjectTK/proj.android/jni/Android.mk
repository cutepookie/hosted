LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -DPLATFORM_YJ=0
LOCAL_MODULE := game_shared
#LOCAL_CFLAGS += -DDEBUG=1

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SHORT_COMMANDS := true
SRC_FILES := hellocpp/main.cpp
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Game/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Common/*.cpp)

LOCAL_SRC_FILES := $(SRC_FILES:$(LOCAL_PATH)/%=%) \
../../Classes/AppDelegate.cpp \
../../Classes/Common/aescrypt/MB_Aescrypt.cpp \
../../Classes/Common/GameLib/CCDebugCodePage.cpp \
../../Classes/Common/GameLib/GameFunctionEntry/CCEventListener.cpp \
../../Classes/Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.cpp \
../../Classes/Common/GameLib/GameHelper/CCGameHelper.cpp \
../../Classes/Common/GameLib/UnityXml/MB_XmlItems.cpp \
../../Classes/Common/GameLib/UnityXml/MB_XmlManager.cpp \
../../Classes/iap/PaymentViewandroid.cpp \
../../Classes/jsoncpp/src/lib_json/json_reader.cpp \
../../Classes/jsoncpp/src/lib_json/json_value.cpp \
../../Classes/jsoncpp/src/lib_json/json_writer.cpp \
../../Classes/Common/md5.c \
../../Classes/YJSDK/MB_YJMgr.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../Classes/Common \
$(LOCAL_PATH)/../../Classes/Common/aescrypt \
$(LOCAL_PATH)/../../Classes/Common/CCControlButtonWithFX \
$(LOCAL_PATH)/../../Classes/Common/CCLabelFX \
$(LOCAL_PATH)/../../Classes/Common/CodeHelper \
$(LOCAL_PATH)/../../Classes/Game \
$(LOCAL_PATH)/../../Classes/iap \
$(LOCAL_PATH)/../../Classes/jsoncpp \
$(LOCAL_PATH)/../../Classes/jsoncpp/include \
$(LOCAL_PATH)/../../Classes/jsoncpp/include/json \
$(LOCAL_PATH)/../../Classes/jsoncpp/src \
$(LOCAL_PATH)/../../Classes/jsoncpp/src/lib_json \
$(LOCAL_PATH)/../../Classes/YJSDK \
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)
$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
