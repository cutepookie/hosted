package com.yr.testpay;

import java.util.ArrayList;
import java.util.List;

import android.app.ActionBar;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import com.yr.gamesdk.QuitBaseActivity;
import com.yr.gamesdk.bean.LoginResult;
import com.yr.gamesdk.bean.PayResult;
import com.yr.gamesdk.bean.RegisterResult;
import com.yr.gamesdk.config.GameSDKConfig;
import com.yr.gamesdk.config.Language;
import com.yr.gamesdk.imp.GameSDKPayListener;
import com.yr.gamesdk.imp.GameSDKUserBehaviorListener;
import com.yr.gamesdk.manager.YRGameSDKManager;
import com.yr.gamesdk.utils.JSONUtil;
import com.yr.gamesdk.utils.LanguageUtil;
import com.yr.gamesdk.utils.Utility;
import com.yr.gamesdk.utils.logger.SDKLoggerUtil;
import com.yr.gamesdk.utils.payutils.GooglePurchaseUtil;

public class MainActivity extends QuitBaseActivity {

	private static final String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvdyf4xvI2cGuX/FvGbARDu6Xhh0kLJ59sZ5xX105mWe3BL19+hUo11xmyjHMCFH3soZqUNrlXEi7hdNCBbIKcDZgqqh4a9Jmn9QenzWQg7qkSlRk48MKiawTgcdwh3Z+C9XgujD4U4r+4X5bgQHoIz+mreTggHqPmCbcMZnzt4D2jXll8EEmuegEnC7rp+Tp1QLqkwQQvoVrQ58qR/4BW2DQx7YvJlXWsDhZpMs/4SX1QN8jhTcAvkV8GRmS8n2RnHTb5OEp/yU8v2+YVYaItsPmRfAd08vtaUOBi4XxNJKLuO+ml24oelGTtb+kkBfZ/7DaxiDiCK4O8UHPvO1JDQIDAQAB";
	View float_view;
	View logout;
	private EditText edKey;
	private View btnPay;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		login = (Button) findViewById(R.id.test_auto_login);
		spinner = ((Spinner) findViewById(R.id.spinner));
		float_view = findViewById(R.id.float_view);
		edKey = ((EditText) findViewById(R.id.ed_show));
		btnPay = findViewById(R.id.pay);
		logout = findViewById(R.id.logout);
		// �������ڴ�����ֱ������͸��״̬������Ч
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
			WindowManager.LayoutParams localLayoutParams = getWindow()
					.getAttributes();
			localLayoutParams.flags = (WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS | localLayoutParams.flags);
		}
		ActionBar bar=getActionBar();
		if(bar!=null){
			bar.hide();
		}

		final List<String> datas = new ArrayList<String>();
		datas.add("ѡ��SDK����");
		datas.add("���ģ����壩");
		datas.add("Ӣ��");
		datas.add("Խ����");
		datas.add("̩��");
		datas.add("���ģ�̨�壩");
		datas.add("���ģ���ۣ�");

		ArrayAdapter arrayAdapter = new ArrayAdapter(this,
				android.R.layout.simple_list_item_1, datas);
		spinner.setAdapter(arrayAdapter);

		/** ѡ��ѡ����� */
		spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
			@Override
			public void onItemSelected(AdapterView<?> parent, View view,
					int position, long id) {

				Language language = Language.en;
				switch (position) {
				case 1:
					language = Language.zh_rCN;
					break;
				case 2:
					language = Language.en;
					break;
				case 3:
					language = Language.vi;
					break;
				case 4:
					language = Language.th;
					break;
				case 5:
					language = Language.zh_rTW;
					break;
				case 6:
					language = Language.zh_rHK;
					break;
				}
				if (position != 0) {
					LanguageUtil.getInstance().setLocaleLanguage(language);
					SDKLoggerUtil.getLogger().e("change------");
					restartApplication();
				}

			}

			@Override
			public void onNothingSelected(AdapterView<?> parent) {

			}
		});

		// ���ƽ̨��ʼ����У��
		YRGameSDKManager.getInstance().initCorrectionSDK(this,
				new YRGameSDKManager.InitializeCallback() {
					@Override
					public void onInitialized(boolean status) {
						if (status) {
							/**
							 * ����Ƿ���������Զ���¼����
							 */
							boolean canAutoLoginView = YRGameSDKManager
									.getInstance().isCanAutoLoginView();
							if (canAutoLoginView == false) {
								login.setVisibility(View.VISIBLE);

							}
						}
					}
				});

		// ������������Զ���¼���棬���ֶ���¼
		login.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				YRGameSDKManager.getInstance().openLoginView();
			}
		});

		// ��¼��ע��ص�
		YRGameSDKManager.getInstance().setSdkUserBehaviorListener(
				new GameSDKUserBehaviorListener() {
					@Override
					public void onLogin(LoginResult result) {
						LoginType loginType = result.getLoginType();
						String str = "";
						if (loginType == LoginType.ACCOUNTS) {
							str = "ϵͳ�û�";
						} else if (loginType == LoginType.GUEST) {
							str = "�ο��û�";
						} else if (loginType == LoginType.FACEBOOK) {
							str = "facebook�û�";
						}
						if (result.getLoginStatus() == Status.LOGIN_TYPE_SUCCEED) {
							// ��ת����Ϸ����
							SDKLoggerUtil.getLogger().e(
									str + "��¼�ɹ���ģ����ת����Ϸ����result:" + result);
							float_view.setVisibility(View.VISIBLE);
							logout.setVisibility(View.VISIBLE);
							btnPay.setVisibility(View.VISIBLE);
							login.setVisibility(View.GONE);
						} else {

							login.setVisibility(View.VISIBLE);
							float_view.setVisibility(View.GONE);
							logout.setVisibility(View.GONE);
							btnPay.setVisibility(View.GONE);
						}
					}

					@Override
					public void onRegister(RegisterResult registerResult) {
						if (registerResult.getRegisterStatus() == Status.REGISTER_TYPE_SUCCEED) {
							// ��ת����Ϸ����
							SDKLoggerUtil.getLogger().e(
									"ע��ɹ���ģ����ת����Ϸ���� registerResult:"
											+ registerResult.toString());
							float_view.setVisibility(View.VISIBLE);
							logout.setVisibility(View.VISIBLE);
							login.setVisibility(View.GONE);
							btnPay.setVisibility(View.VISIBLE);
						} else {

							login.setVisibility(View.VISIBLE);
							float_view.setVisibility(View.GONE);
							logout.setVisibility(View.GONE);
							btnPay.setVisibility(View.GONE);
						}
					}

				});

		/**
		 * ��ʼ��google֧��
		 */
		GooglePurchaseUtil.getInstance().initPurchaseData(MainActivity.this,
				base64EncodedPublicKey, new GameSDKPayListener() {
					@Override
					public void onPay(PayResult payResult) {
						Toast.makeText(MainActivity.this, payResult.toString(),
								Toast.LENGTH_SHORT).show();
					}
				});

		findViewById(R.id.pay).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {

				/**
				 * 
				 * @param pid
				 *            ���Ǻ�̨��Ӧ��productID
				 * @param payloadCpOrderId
				 *            ҵ�����Ķ�����
				 * @param _extral
				 *            �������
				 */
				// GooglePurchaseUtil.getInstance().buy("10001",
				// "123454ab5221255","");
				GooglePurchaseUtil.getInstance().buy("com.joy.helper.1usd",
						"123454ab5221255", "");

			}
		});

		String s = YRGameSDKManager.getInstance().getKeyHash();
		if (!Utility.isNullOrEmpty(s)) {
			Toast.makeText(this, "key:" + s, Toast.LENGTH_SHORT).show();
			edKey.setText(s.replace("\n", ""));
			Log.e("Key Hash=", s);
		}
	}

	Button login;

	private Spinner spinner;

	@Override
	protected void onPause() {
		super.onPause();
		// �ͷ�������ص���
		YRGameSDKManager.getInstance().dismissNetLoadDialog();
	}

	@Override
	protected void onDestroy() {
		/**
		 * �ͷ���Դ
		 */
		YRGameSDKManager.getInstance().release();
		super.onDestroy();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// ����Ҫ��superǰ������������䣬�������ݻص�
		YRGameSDKManager.getInstance().onActivityResult(requestCode,
				resultCode, data);
		super.onActivityResult(requestCode, resultCode, data);

		// СǮ��֧���ص�
		if (requestCode == GameSDKConfig.TOP_UP_HELP_REQUEST_CODE
				&& resultCode == GameSDKConfig.TOP_UP_HELP_RESULT_CODE) {
			if (data != null) {
				String payResultJson = data
						.getStringExtra(GameSDKConfig.TOP_UP_HELP_RESULT_DATA_KEY);
				if (!Utility.isNullOrEmpty(payResultJson)) {
					
                    SDKLoggerUtil.getLogger().e(payResultJson);
					PayResult payResult = (PayResult) JSONUtil.jsonToObject(
							payResultJson, PayResult.class);
					if (payResult.getPayStatus() == GameSDKPayListener.PayStatus.SUCCEED) {
						// ֧���ɹ�
						Toast.makeText(MainActivity.this, payResult.toString(),
								Toast.LENGTH_LONG).show();
					}

				}
			}
		}

	}

	public static void start(Context context) {
		Intent starter = new Intent(context, MainActivity.class);
		context.startActivity(starter);
	}

	public void onClick(View view) {
		switch (view.getId()) {
		case R.id.btn_come_back:
			boolean canAutoLoginView = YRGameSDKManager.getInstance()
					.isCanAutoLoginView();
			if (canAutoLoginView == false) {
				Toast.makeText(this, "��û��¼�������ܵ�����ӭ��������", Toast.LENGTH_SHORT)
						.show();
			}
			break;
		case R.id.float_view:
			YRGameSDKManager.getInstance().openFloatView("123", "1212");
			break;
		case R.id.logout:
			YRGameSDKManager.getInstance().logout();
			Toast.makeText(this, "ע���ɹ�", Toast.LENGTH_SHORT).show();
			float_view.setVisibility(View.GONE);
			logout.setVisibility(View.GONE);
			btnPay.setVisibility(View.GONE);
			login.setVisibility(View.VISIBLE);
			break;

		}

	}

	private void restartApplication() {
		// �л�������Ϣ����Ҫ���� Activity ����ʵ��
		Intent intent = new Intent(this, MainActivity.class);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK
				| Intent.FLAG_ACTIVITY_CLEAR_TASK);
		startActivity(intent);
	}
}
