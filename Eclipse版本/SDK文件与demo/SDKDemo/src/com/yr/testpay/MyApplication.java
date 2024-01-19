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
        //��ʼ������������
        ContextUtil contextUtil = ContextUtil.getInstance();
        //����application
        contextUtil.setApplication(this);
        //����ȫ��������
        contextUtil.setApplicationContext(this.getApplicationContext());

        //��־ģʽ
        YRGameSDKManager.setIsDebugModel(true); //����ʱ��ǵùر���־
        //��������
        GameSDKConfig instance = GameSDKConfig.getInstance();
        /**
         *
         *  sdkAppId  ƽ̨�����appId
         *  sdkAppKey ƽ̨�����appKey
         *  sdkMailingAddress ƽ̨�������ַ
         *  fbApplicationId ƽ̨�����facebookAPPID
         */
         //�ȿ����¼ܰ�
       // instance.init("88006", "9f6d146450850ea70e9bf4", getString(R.string.facebook_app_id));
        instance.init("88001", "123456", getString(R.string.facebook_app_id));


        //���������н��г�ʼ��SDK
        boolean isMainProcess = OSUtils.isMainProcess(this);
        SDKLoggerUtil.getLogger().e(TAG, "******* Application (%s) onCreate *******", (isMainProcess ? "main" : "mult"));
        if (isMainProcess) {
            YRGameSDKManager.sdkInitialize(this);
        }
       //���Գ�ʼ��
       //LanguageUtil.getInstance().setLocaleLanguage(Language.zh_rCN);

    }


}
