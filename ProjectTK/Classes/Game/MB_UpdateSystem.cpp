//
//  MB_UpdateSystem.cpp
//  ProjectMB
//
//  Created by wenyong on 14-11-19.
//
//

#include "MB_UpdateSystem.h"
#include "SDS_NetWorkDefine.h"
#include "OCandCppHelper.h"
#include "cppjson.h"
#include "MB_Message.h"
#include "MB_ResourcesPackageUpdate.h"
#include "MB_LoginBackground.h"
#include "MB_LayerResourceUpdate.h"
using namespace std;
MB_UpdateSystem::~MB_UpdateSystem()
{
	m_pTarget = NULL;
	CC_SAFE_RELEASE_NULL(m_pPatchs);
	CC_SAFE_DELETE(m_pResourcePackageUpdater);
}
//http://127.0.0.1:11010/update_info?package_id=net.moongame.com&project_id=0&cversion=1.0.5&rversion=10000&notice_type=1&src_type=1
void MB_UpdateSystem::sendupdate_check()
{
	m_pResourcePackageUpdater = new MB_ResourcesPackageUpdate;
	m_pResourcePackageUpdater->setSearchPath();

	CCHttpRequest* httpRequest = new CCHttpRequest();
	httpRequest->setRequestType(CCHttpRequest::kHttpGet);
	httpRequest->setUrl("http://47.112.249.68:8088/xjl_hotfix/serverVersion.json");

	httpRequest->setTag("version check");
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_UpdateSystem::recvupdate_check));
	CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();
}

void MB_UpdateSystem::recvupdate_check(CCHttpClient* client, CCHttpResponse* response)
{
	if (response->getResponseCode() != 200)
	{
		onCancelClick(NULL);
		return;
	}
	Json::Reader reader;
	Json::Value  root;
	std::string data;
	std::string responseData;
	data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
	reader.parse(data, root);

	std::string isOpenUpdate = root["isOpenUpdate"].asString();
	if (isOpenUpdate == "0")
	{
		updateState = 1;
		return;
	}
	Json::Value & resultValue = root["serverVersion"];
	Json::Value & perSize = root["perSize"];
	locationVersion = CCUserDefault::sharedUserDefault()->getStringForKey("locationVersion");
	if (locationVersion == "")
	{
		locationVersion = OCandCppHelper::getVervion();
	}

	serverVersion = resultValue[resultValue.size() - 1].asString();

	if (locationVersion != serverVersion)
	{
		bool isAdd = false;
		float sumSize = 0;
		for (unsigned int i = 0; i < resultValue.size(); i++)
		{
			string _versionStr = resultValue[i].asString();
			if (locationVersion == _versionStr)
			{
				isAdd = true;
				continue;
			}
			if (isAdd)
			{
				sumSize += atof(perSize[i].asCString());
				MB_PatchDetail* pDetail = new MB_PatchDetail;
				pDetail->setVersion("1");
				pDetail->setUpdateUrl(CCString::createWithFormat("http://47.112.249.68:8088/xjl_hotfix/res%s.zip", _versionStr.c_str())->getCString());

				m_pPatchs->addObject(pDetail);
				CC_SAFE_RELEASE_NULL(pDetail);
				versionVec.push_back(_versionStr);
			}
		}
		const char* sizeChar;
		if (sumSize < 1024)
		{
			sizeChar = CCString::createWithFormat("%.2fKB", sumSize)->getCString();
		}
		else
		{
			sizeChar = CCString::createWithFormat("%.2fM", sumSize / 1024)->getCString();
		}

		MB_Message::sharedMB_Message()->showMessage("提示", CCString::createWithFormat("当前需要更新%s资源才能继续进行游戏，是否更新?", sizeChar)->getCString(), "更新", this, menu_selector(MB_UpdateSystem::onUpdateResClicked));
	}
	else
	{
		updateState = 1;
	}

}

void MB_UpdateSystem::onUpdateClick(CCObject* pSender)
{
	if (!m_szUpdateUrl.empty())
	{
		OCandCppHelper::goUpdate(m_szUpdateUrl.c_str());
		if (m_pTarget)
		{
			m_pTarget->onUpdateComplated();
		}
	}
}

void MB_UpdateSystem::goUpdatePack(CCObject* pSender)
{
	CCSequence* p = CCSequence::create(CCDelayTime::create(0.2), CCCallFuncO::create(this, callfuncO_selector(MB_UpdateSystem::onUpdateClick), this), NULL);
	CCDirector::sharedDirector()->getRunningScene()->runAction(p);
}

void MB_UpdateSystem::onCancelClick(CCObject* pSender)
{
	if (m_pTarget)
	{
		m_pTarget->onUpdateComplated();
	}
}

void MB_UpdateSystem::setDelegate(MB_UpdateDelagete* pDelegate)
{
	m_pTarget = pDelegate;
}

void MB_UpdateSystem::onError(AssetsManager::ErrorCode errorCode)
{
	if (m_pTarget)
	{
		m_pTarget->onError(errorCode);
	}
}

void MB_UpdateSystem::onProgress(int percent)
{
	if (m_pTarget)
	{
		m_pTarget->onProgress(percent);
	}
}

void MB_UpdateSystem::onSuccess()
{
	if (m_pResourcePackageUpdater)
	{
		m_pResourcePackageUpdater->storeVersionFile();
	}
	CCUserDefault::sharedUserDefault()->setStringForKey("locationVersion", versionVec.front());
	versionVec.erase(versionVec.begin());
	if (m_pPatchs->count() == 0)
	{
		if (m_pTarget)
		{
			m_pTarget->onSuccess();
		}
	}
	else
	{
		ready4Patch();
	}
}

bool MB_UpdateSystem::updateResource()
{
	if (m_pPatchs->count() == 0)
	{
		return false;
	}
	MB_PatchDetail* pDetail = (MB_PatchDetail*)(m_pPatchs->objectAtIndex(0));

	if (m_pResourcePackageUpdater && m_pResourcePackageUpdater->init())
	{
		m_pResourcePackageUpdater->setPackageUrl(pDetail->getUpdateUrl().c_str());
		m_pResourcePackageUpdater->setTargetVersion(pDetail->getVersion().c_str());
		m_pResourcePackageUpdater->setConnectionTimeout(3);
		m_pResourcePackageUpdater->setDelegate(this);
		m_pPatchs->removeObjectAtIndex(0);


		((MB_LoginBackground*)m_pTarget)->setSomeVisible(true);

		return m_pResourcePackageUpdater->goUpdate();
	}

	m_pPatchs->removeObjectAtIndex(0);
	return false;
}

bool MB_UpdateSystem::goUpdatePatch()
{
	MB_Message::sharedMB_Message()->showMessage("", 15);
	return true;
}

void MB_UpdateSystem::recvrequest_patch(CCHttpClient* client, CCHttpResponse* response)
{
	MB_Message::sharedMB_Message()->showMessage("", 15);
	if (response->getResponseCode() != 200)
	{
		//MB_ResWindow::showMessage("錯誤", "伺服器連接失敗,請检查網絡.", "確定");
		if (m_pTarget)
		{
			CCLOG("资源服务器链接失败");
			m_pTarget->onNoPatchUpdate();
		}
		return;
	}

	Json::Reader reader;
	Json::Value  root;
	std::string data;
	std::string responseData;
	data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
	reader.parse(data, root);

	int result = root["result"].asInt();
	if (result == 2)
	{
		if (m_pTarget)
		{
			CCLOG("没有可用资源更新");
			m_pTarget->onNoPatchUpdate();
		}
	}
	else if (result == 1)
	{
		//        Json::Value::Members m = root.getMemberNames();
		//        m.pop_back();
		//        m_pPatchs->removeAllObjects();
		//        while (!m.empty())
		//        {
		//            MB_PatchDetail* pDetail = new MB_PatchDetail;
		//            pDetail->setUpdateUrl(root[m.back()].asString());
		//            pDetail->setVersion(m.back());
		//            m_pPatchs->insertObject(pDetail, 0);
		//            CC_SAFE_RELEASE_NULL(pDetail);
		//            m.pop_back();
		//        }
		std::string str = root["urllist"].asString();
		resolvUrlPatch(str);
		if (m_pPatchs->count() != 0)
		{
			ready4Patch();
		}
		else
		{
			if (m_pTarget)
			{
				CCLOG("更新资源不可用");
				m_pTarget->onNoPatchUpdate();
			}
		}
	}
}

/*
 {"result":1,"urllist":"10000,0,1024B,http://101.251.223.115/10000.zip\n20000,0,512KB,http://101.251.223.115/20000.zip\n30000,0,100MB,http://101.251.223.115/30000.zip"}
 */
void MB_UpdateSystem::resolvUrlPatch(const std::string& urlList)
{
	m_pPatchs->removeAllObjects();
	if (!urlList.empty())
	{
		char* pBuff = new char[urlList.length() + 1];
		strcpy(pBuff, urlList.c_str());
		char * pch;
		pch = strtok(pBuff, ",");
		while (pch != NULL)
		{
			MB_PatchDetail* pDetail = new MB_PatchDetail;
			pDetail->setVersion(pch);
			pch = strtok(NULL, ",");
			pDetail->setType(atoi(pch));
			pch = strtok(NULL, ",");
			pDetail->setSize(pch);
			pch = strtok(NULL, "\n");
			pDetail->setUpdateUrl(pch);
			m_pPatchs->addObject(pDetail);
			CC_SAFE_RELEASE_NULL(pDetail);
			pch = strtok(NULL, ",");
		}
		delete[] pBuff;
	}
}

void MB_UpdateSystem::ready4Patch()
{
	if (m_pPatchs->count() > 0)
	{
		onUpdateResClicked(NULL);
	}
	else
	{
		if (m_pTarget)
		{
			m_pTarget->onSuccess();
		}
	}
}



void MB_UpdateSystem::XMLToMap(bool isLocation)
{
	std::string target;
	MB_ResourcesPackageUpdate::getStoragePath(target);
	MB_XmlFile* pFile;
	if (isLocation)
	{
		pFile = MB_XmlFile::create(CCString::createWithFormat("%sres%s.xml", target.c_str(), locationVersion.c_str())->getCString());
	}
	else
	{
		pFile = MB_XmlFile::create(CCString::createWithFormat("%sres%s.xml", target.c_str(), serverVersion.c_str())->getCString());
	}
	if (pFile)
	{
		CCArray* pArray = CCArray::create();
		if (pFile->queryNodesByName("res", pArray))
		{
			MB_XmlNode* pNode = (MB_XmlNode*)pArray->objectAtIndex(0);
			CCArray* pArray2 = CCArray::create();
			pNode->queryNodesByName("file", pArray2);

			CCObject* child;
			CCARRAY_FOREACH(pArray2, child)
			{
				MB_XmlNode* node = (MB_XmlNode*)child;
				if (isLocation)
				{

					resXMLLocation.insert(pair<string, string>(node->queryAttributeByName("name")->getCString(), node->queryAttributeByName("md5")->getCString()));
				}
				else
				{
					resXMLExternal.insert(pair<string, string>(node->queryAttributeByName("name")->getCString(), node->queryAttributeByName("md5")->getCString()));
				}
			}
		}
	}

}

void MB_UpdateSystem::onUpdateResClicked(CCObject* pSender)
{
	updateResource();
}
void MB_UpdateSystem::onCancelResClicked(CCObject* pSender)
{
	if (m_pTarget)
	{
		m_pTarget->onNoPatchUpdate();
	}
}
