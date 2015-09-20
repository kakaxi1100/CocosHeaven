LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameData.cpp \
                   ../../proj.win32/BackgroudLayer.cpp \
                   ../../proj.win32/Cat.cpp \
                   ../../proj.win32/Dog.cpp \
                   ../../proj.win32/FishboneBullet.cpp \
                   ../../proj.win32/GameLayer.cpp \
                   ../../proj.win32/GameOverLayer.cpp \
                   ../../proj.win32/GameScene.cpp \
                   ../../proj.win32/MenuLayer.cpp \
                   ../../proj.win32/MenuScene.cpp \
                   ../../proj.win32/TubeBullet.cpp \
                   ../../proj.win32/UILayer.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static  

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
#$(call import-module,audio/android) 
#$(call import-module,extensions) 

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
