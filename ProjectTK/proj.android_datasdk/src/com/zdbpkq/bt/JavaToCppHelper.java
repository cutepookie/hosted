package com.zdbpkq.bt;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.UUID;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import android.util.Log;

public class JavaToCppHelper {

	public static String getMacAddress() {

		WifiManager wifi = (WifiManager) ProjectMB.getContext()
				.getSystemService(Context.WIFI_SERVICE);
		WifiInfo info = wifi.getConnectionInfo();
		String string = info.getMacAddress();

		if (string == null) {

			string = getDevID();

		} else if (string.length() <= 0) {

			string = ((ProjectMB) ProjectMB.getContext()).sdkManager
					.getRoleName();
		}

		if (string == null) {

			string = "00:00:00:00:00:00";
		}
		return string;
	}

	public static boolean isconnect3G() {

		ConnectivityManager conMan = (ConnectivityManager) ProjectMB
				.getContext().getSystemService(Context.CONNECTIVITY_SERVICE);
		// mobile 3G Data Network
		State mobile = conMan.getNetworkInfo(ConnectivityManager.TYPE_MOBILE)
				.getState();
		return mobile == State.CONNECTED;
	}

	public static boolean isconnectWIFI() {

		ConnectivityManager conMan = (ConnectivityManager) ProjectMB
				.getContext().getSystemService(Context.CONNECTIVITY_SERVICE);
		// mobile 3G Data Network
		State wifi = conMan.getNetworkInfo(ConnectivityManager.TYPE_WIFI)
				.getState();
		return wifi == State.CONNECTED;
	}

	public static boolean isNetworkAvailable(Context context) {
		ConnectivityManager cm = (ConnectivityManager) context
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		if (cm == null) {
		} else {
			NetworkInfo[] info = cm.getAllNetworkInfo();
			if (info != null) {
				for (int i = 0; i < info.length; i++) {
					if (info[i].getState() == NetworkInfo.State.CONNECTED) {
						return true;
					}
				}
			}
		}
		return false;
	}

	public static boolean createfile(String path) {

		File newFile = new File(path);
		try {

			if (newFile.exists() == false) {

				newFile.mkdirs();
			}
			return true;
		} catch (Exception e) {

			Log.e("createFile", e.getMessage());

		}
		return false;

	}

	public static int getRam() {

		long mTotal;
		// /proc/meminfo读出的内核信息进行解释
		String path = "/proc/meminfo";
		String content = null;
		BufferedReader br = null;
		try {
			br = new BufferedReader(new FileReader(path), 8);
			String line;
			if ((line = br.readLine()) != null) {
				content = line;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

		// beginIndex
		int begin = content.indexOf(':');
		// endIndex
		int end = content.indexOf('k');
		// 截取字符串信息
		content = content.substring(begin + 1, end).trim();
		mTotal = Integer.parseInt(content);
		int mem = (int) (mTotal / 1024.0f);
		Log.e("menmery", content + " " + mem + " M");
		return mem;
	}

	public static String getVersion() {

		PackageManager manager = ProjectMB.getContext().getPackageManager();
		try {

			PackageInfo info = manager.getPackageInfo(ProjectMB.getContext()
					.getPackageName(), 0);
			Log.e("msg", "" + "version " + info.versionName);
			return info.versionName;

		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return "error";
	}

	public static String getProductName() {

		return ProjectMB.getContext().getPackageName();
	}

	public static String getProjectID() {

		return ((ProjectMB) ProjectMB.getContext()).projectID;
	}

	public static void update(String url) {
		Log.e("down", "down" + url);
		((ProjectMB) ProjectMB.getContext()).toUpdate(url);
	}

	public static String getDevID() {

		DeviceUuidFactory data = new DeviceUuidFactory(ProjectMB.getContext());
		String ret = data.getDeviceUuid().toString() + "{"
				+ JavaToCppHelper.getManufacturer() + "-"
				+ JavaToCppHelper.getAndroidVersion() + "-"
				+ JavaToCppHelper.getModel() + "}";
		ret = ret.replaceAll(" +", "");
		return ret;

		/*
		 * return XGPushConfig.getToken(ProjectMB.getContext()) + "{" +
		 * JavaToCppHelper.getManufacturer() + "-" +
		 * JavaToCppHelper.getAndroidVersion() + "}";
		 */

	}

	// 取得 android 版本
	public static int getAndroidVersion() {
		int version = 0;
		Class<android.os.Build.VERSION> build_version_class = android.os.Build.VERSION.class;

		java.lang.reflect.Field field;
		try {
			field = build_version_class.getField("SDK_INT");
			version = (Integer) field.get(new android.os.Build.VERSION());
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		Log.e("android", "SDK版本:" + version);
		return version;
	}

	// 取得牌子
	public static String getManufacturer() {

		String manufacturer = "";
		Class<android.os.Build> build_class = android.os.Build.class;
		java.lang.reflect.Field manu_field;
		try {
			manu_field = build_class.getField("MANUFACTURER");
			manufacturer = (String) manu_field.get(new android.os.Build());
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		Log.e("android", "牌子:" + manufacturer);
		return manufacturer;
	}

	// 取得型号
	public static String getModel() {

		String model = "";
		Class<android.os.Build> build_class = android.os.Build.class;
		java.lang.reflect.Field field2;
		try {
			field2 = build_class.getField("MODEL");
			model = (String) field2.get(new android.os.Build());
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		Log.e("android", "型号:" + model);
		return model;
	}

	// 模組号码
	public static String getDevice() {

		String device = "";
		Class<android.os.Build> build_class = android.os.Build.class;
		java.lang.reflect.Field device_field;
		try {
			device_field = build_class.getField("DEVICE");
			device = (String) device_field.get(new android.os.Build());
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		Log.e("android", "模組号码:" + device);
		return device;
	}
}

class DeviceUuidFactory {

	protected static final String PREFS_FILE = "device_id.xml";
	protected static final String PREFS_DEVICE_ID = "device_id";
	protected UUID uuid;

	public DeviceUuidFactory(Context context) {

		if (uuid == null) {

		}
		synchronized (DeviceUuidFactory.class) {

			if (uuid == null) {

				final SharedPreferences prefs = context.getSharedPreferences(
						PREFS_FILE, 0);
				final String id = prefs.getString(PREFS_DEVICE_ID, null);
				if (id != null) {
					// Use the ids previously computed and stored in the prefs
					// file
					uuid = UUID.fromString(id);

				} else {

					final String androidId = Secure.getString(
							context.getContentResolver(), Secure.ANDROID_ID);
					// Use the Android ID unless it's broken, in which case
					// fallback on deviceId,
					// unless it's not available, then fallback on a random
					// number which we store
					// to a prefs file
					try {

						if (androidId != null
								&& !"9774d56d682e549c".equals(androidId)) {

							uuid = UUID.nameUUIDFromBytes(androidId
									.getBytes("utf8"));

						} else {

							final String deviceId = ((TelephonyManager) context
									.getSystemService(Context.TELEPHONY_SERVICE))
									.getDeviceId();
							if (deviceId != null) {

								uuid = UUID.nameUUIDFromBytes(deviceId
										.getBytes("utf8"));

							} else {

								String getDevid = getDeviceId(context);
								uuid = UUID.nameUUIDFromBytes(getDevid
										.getBytes("utf8"));
							}
						}
					} catch (UnsupportedEncodingException e) {

						throw new RuntimeException(e);
					}
					// Write the value out to the prefs file
					prefs.edit().putString(PREFS_DEVICE_ID, uuid.toString())
							.commit();
				}
			}
		}
	}

	public String getDeviceId(Context context) {

		StringBuilder deviceId = new StringBuilder();
		// 渠道標志
		deviceId.append("a");
		try {

			// wifi mac地址
			WifiManager wifi = (WifiManager) context
					.getSystemService(Context.WIFI_SERVICE);
			WifiInfo info = wifi.getConnectionInfo();
			String wifiMac = info.getMacAddress();
			if (wifiMac != null) {

				deviceId.append("wifi");
				deviceId.append(wifiMac);
				return deviceId.toString();
			}

			// IMEI（imei）
			TelephonyManager tm = (TelephonyManager) context
					.getSystemService(Context.TELEPHONY_SERVICE);
			String imei = tm.getDeviceId();
			if (imei != null) {

				deviceId.append("imei");
				deviceId.append(imei);
				return deviceId.toString();
			}

			// 序列號（sn）
			String sn = tm.getSimSerialNumber();
			if (sn != null) {

				deviceId.append("sn");
				deviceId.append(sn);
				return deviceId.toString();
			}

			// 如果上面都沒有， 則生成一個id：隨機碼
			String uuidx = getUUIDX(context);
			if (uuidx != null) {

				deviceId.append("id");
				deviceId.append(uuidx);
				return deviceId.toString();
			}
		} catch (Exception e) {
			e.printStackTrace();
			deviceId.append("id").append(getUUIDX(context));
			return deviceId.toString();
		}
		return deviceId.toString();
	}

	/**
	 * 得到全局唯一UUID
	 */
	public String getUUIDX(Context context) {

		SharedPreferences mShare = context.getSharedPreferences("sysCacheMap",
				0);
		String uuidx = null;
		if (mShare != null) {

			uuidx = mShare.getString("uuid", "");
		}
		if (uuidx == null) {

			uuidx = UUID.randomUUID().toString();
			mShare.edit().putString("uuid", uuidx).commit();
		}
		return uuidx;

	}

	public UUID getDeviceUuid() {

		Log.e("uuid", "uuid " + uuid.toString());
		return uuid;
	}
}
