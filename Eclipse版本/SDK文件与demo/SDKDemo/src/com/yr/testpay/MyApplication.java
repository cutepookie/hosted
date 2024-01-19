package com.yr.testpay;

import android.app.Activity;
import android.app.Application;
import android.content.res.Configuration;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

import com.yr.gamesdk.config.GameSDKConfig;
import com.yr.gamesdk.config.Language;
import com.yr.gamesdk.manager.YRGameSDKManager;
import com.yr.gamesdk.utils.ContextUtil;
import com.yr.gamesdk.utils.LanguageUtil;
import com.yr.gamesdk.utils.OSUtils;
import com.yr.gamesdk.utils.logger.SDKLoggerUtil;

import java.util.Locale;

/**
 * @author Anmi on 2018/4/17.
 */

public class MyApplication extends Application {
    private static final String TAG = MyApplication.class.getSimpleName();

    @Override
    public void onCreate() {
        super.onCreate();
        //初始化上下文配置
        ContextUtil contextUtil = ContextUtil.getInstance();
        //传入application
        contextUtil.setApplication(this);
        //设置全局上下文
        contextUtil.setApplicationContext(this.getApplicationContext());

        //日志模式
        YRGameSDKManager.setIsDebugModel(true); //发布时请记得关闭日志
        //加载配置
        GameSDKConfig instance = GameSDKConfig.getInstance();
        /**
         *
         *  sdkAppId  平台分配的appId
         *  sdkAppKey 平台分配的appKey
         *  sdkMailingAddress 平台的请求地址
         *  fbApplicationId 平台分配的facebookAPPID
         */
         //比卡丘下架包
       // instance.init("88006", "9f6d146450850ea70e9bf4", getString(R.string.facebook_app_id));
        instance.init("88001", "123456", getString(R.string.facebook_app_id));


        //在主进程中进行初始化SDK
        boolean isMainProcess = OSUtils.isMainProcess(this);
        SDKLoggerUtil.getLogger().e(TAG, "******* Application (%s) onCreate *******", (isMainProcess ? "main" : "mult"));
        if (isMainProcess) {
            YRGameSDKManager.sdkInitialize(this);
        }
       //语言初始化
       //LanguageUtil.getInstance().setLocaleLanguage(Language.zh_rCN);

    }


}
