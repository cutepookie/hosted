//
//  MB_UpdateSystem.h
//  ProjectMB
//
//  Created by wenyong on 14-11-19.
//
//

#ifndef __ProjectMB__MB_UpdateSystem__
#define __ProjectMB__MB_UpdateSystem__
#include <cocos2d.h>
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
#include "MB_SingletonClass.h"

class MB_ResourcesPackageUpdate;
class MB_UpdateDelagete : public AssetsManagerDelegateProtocol
{
public:
	virtual void onUpdateComplated() = 0;
	virtual void onNoPatchUpdate() = 0;
};

class MB_PatchDetail :public CCObject
{
private:
	CC_SYNTHESIZE(std::string, m_szVersion, Version);
	CC_SYNTHESIZE(std::string, m_szUpdateUrl, UpdateUrl);
	CC_SYNTHESIZE(int, m_nType, Type);
	CC_SYNTHESIZE(std::string, m_szSize, Size);
};
class MB_UpdateSystem : public CCObject, public AssetsManagerDelegateProtocol
{
public:
	MB_UpdateSystem() :m_pTarget(NULL), m_pResourcePackageUpdater(NULL)
	{
		m_pPatchs = new CCArray;
		isQueRen = false;
		updateState = -1;
	}
	virtual ~MB_UpdateSystem();
	friend class MB_Singleton<MB_UpdateSystem>;
	void sendupdate_check();
	void setDelegate(MB_UpdateDelagete* pDelegate);
	bool updateResource();
	virtual void onError(AssetsManager::ErrorCode errorCode);
	virtual void onProgress(int percent);
	virtual void onSuccess();
	bool goUpdatePatch();
	const std::string& getNotice()const{ return m_szNotice; }
	std::string locationVersion;
	std::string serverVersion;
	int updateState;
private:
	virtual void recvrequest_patch(CCHttpClient* client, CCHttpResponse* response);
	virtual void recvupdate_check(CCHttpClient* client, CCHttpResponse* response);
	void resolvUrlPatch(const std::string& urlList);
	void goUpdatePack(CCObject* pSender);
	vector<string> versionVec;
private:
	void onUpdateClick(CCObject* pSender);
	void onCancelClick(CCObject* pSender);
	void onUpdateResClicked(CCObject* pSender);
	void onCancelResClicked(CCObject* pSender);
	void ready4Patch();
private:
	std::string     m_szNotice;
	CCArray*        m_pPatchs;
	std::string     m_szUpdateUrl;
	MB_UpdateDelagete*  m_pTarget;
	MB_ResourcesPackageUpdate*  m_pResourcePackageUpdater;
	void XMLToMap(bool isLocation);
	std::map<std::string, std::string> resXMLLocation;
	std::map<std::string, std::string> resXMLExternal;
	bool isQueRen;
};

typedef MB_Singleton<MB_UpdateSystem>   MB_PackageUpdateMgr;

#endif /* defined(__ProjectMB__MB_UpdateSystem__) */
