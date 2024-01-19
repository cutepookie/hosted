//
//  MB_YJMgr.cpp
//  ProjectTK
//
//  Created by WORKER on 13-8-21.
//
//

#include "MB_YJMgr_IOS.h"
#include "OCandCppHelper.h"
#include "MB_LayerFirstLogin.h"
#include <fcntl.h>
#import <SMPCQuickSDK/SMPCQuickSDK.h>
#ifdef __cplusplus
extern "C" {
#endif
    
    void __attribute__ ((visibility ("default"))) ijiami(){
        
        char* cpuinfo = NULL;
        int cpuinfo_len;
        
        int fd, ret, result = 0;
        char buffer[256];
        
        fd = open("/proc/cpuinfo", 0x00);
        if (fd > 0) {
            
            for (;;) {
                int ret = read(fd, buffer, sizeof buffer);
                if (ret < 0) {
                    break;
                }
                if (ret == 0)
                    break;
                
                result += ret;
            }
            cpuinfo_len = result;
        }
        
        if (cpuinfo_len > 0) {
            
            cpuinfo = (char*)malloc(cpuinfo_len);
            if (cpuinfo != NULL) {
                
                int count = 0;
                while (count <  cpuinfo_len) {
                    int ret = read(fd, cpuinfo + count, cpuinfo_len - count);
                    if (ret < 0) {
                        
                        if (count == 0)
                            count = -1;
                        break;
                    }
                    if (ret == 0)
                        break;
                    count += ret;
                }
            }
            free(cpuinfo);
            close(fd);
        }
    }
    
#ifdef __cplusplus
}
#endif



MB_YJMgr_IOS * MB_YJMgr_IOS::m_pShareUCManager = NULL;

MB_YJMgr_IOS::MB_YJMgr_IOS(){
    
    IsCheckSetRoleData = false;
    m_pDelegate = NULL;
    strcpy(sid,"");
    sid[0] ='\0';
}
MB_YJMgr_IOS::~MB_YJMgr_IOS(){
    
    m_pDelegate = NULL;
}


void MB_YJMgr_IOS::registDelegate(CCObject *delegate){
    
    m_pDelegate = delegate;
}
void MB_YJMgr_IOS::unregistDelegate(CCObject *delegate){
    
    if(m_pDelegate == delegate){
        
        m_pDelegate = NULL;
    }
}
//void MB_YJMgr_IOS::onLoginSuccess(SFNativeOnlineUser* user, const char* remain) {
//
//    //    stringstream url;
//    //    url << CP_LOGIN_CHECK_URL;
//    //    url << "?app=" << this->urlencode(user->productCode);
//    //    url << "&sdk=" << this->urlencode(user->channelId);
//    //    /*对userId做url编码转换*/
//    //    url << "&uin=" << this->urlencode(user->channelUserId);
//    //    /*对token做url编码转换*/
//    //    url << "&sess=" << this->urlencode(user->token);
//    //
//    //    std::string urlS = url.str();
//    //
//    //    char *cstr = new char[urlS.length() + 1];
//    //    strcpy(cstr, urlS.c_str());
//
//    CCArray * arr = CCArray::create();
//    arr->addObject(cocos2d::CCString::create(user->productCode));
//    arr->addObject(cocos2d::CCString::create(user->channelId));
//    arr->addObject(cocos2d::CCString::create(user->channelUserId));
//    arr->addObject(cocos2d::CCString::create(user->token));
//
//    this->login(arr);
//
//}
void MB_YJMgr_IOS::login(const char * appid, const char* channelid, const char *userid, const char *token){
    
    strcpy(sid, userid);
    if (m_pDelegate) {
//
        MB_LayerFirstLogin *layer;
        layer = dynamic_cast<MB_LayerFirstLogin *>(m_pDelegate);
        if (layer) {
            
            layer->onLoginStart(appid, channelid,
                                userid, token);
        }
        return;
        
    }
//    if(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN) == NULL){
//
//        CCDirector::sharedDirector()->popToRootScene();
//    }
//    MB_RoleData::destroyInstance();
//    MB_ServerList::destroyInstance();
//    MB_ClientSocket::destroyInstance();
//    CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
//    CCScene *pScene = MB_SceneLoginBackground::scene();
//    CCDirector::sharedDirector()->popToRootScene();
//    CCDirector::sharedDirector()->replaceScene(pScene);
//
//    MB_LayerFirstLogin *layer;
//    layer = dynamic_cast<MB_LayerFirstLogin *>(m_pDelegate);
//    if (layer) {
//
//        layer->onLoginStart(sid);
//    }
    
    
}
bool MB_YJMgr_IOS::hasLogin(){
    
    int len = strlen(sid);
    return len > 0;
}
void MB_YJMgr_IOS::logout(){

    if(strlen(sid) > 0){

        sid[0] = '\0';
       
        MB_RoleData::destroyInstance();
        MB_ServerList::destroyInstance();
        MB_ClientSocket::destroyInstance();
        CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
        CCScene *pScene = MB_SceneLoginBackground::scene();
        CCDirector::sharedDirector()->popToRootScene();
        CCDirector::sharedDirector()->replaceScene(pScene);
        PlayBackGround(kmBackGround_Normal);
    }
}
void  MB_YJMgr_IOS::onGuestToNormal(){
    
    CCDirector::sharedDirector()->getRunningScene()->onEnter();
}
MB_YJMgr_IOS* MB_YJMgr_IOS::getInstance(){
    
    if(m_pShareUCManager == NULL){
        
        m_pShareUCManager = new MB_YJMgr_IOS();
    }
    return m_pShareUCManager;
}
void MB_YJMgr_IOS::distroy(){
    
    if (m_pShareUCManager != NULL) {
        
        delete  m_pShareUCManager;
        m_pShareUCManager = NULL;
    }
    
}
int  MB_YJMgr_IOS::getCurrentLoginState(){
    
    return  false;
}

void MB_YJMgr_IOS::goLogin(){
    int error = [[SMPCQuickSDK defaultInstance] login];
    if (error != 0) {
        NSLog(@"%d",error);
    }
}

bool  MB_YJMgr_IOS::isAutoLogin(){
    
    return     false;
}
void MB_YJMgr_IOS::goLogout(){
    
    //代码注销
    [[SMPCQuickSDK defaultInstance] logout];
    logout();
}
void MB_YJMgr_IOS::setPay(const char * payid){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
     int amount = 0;
    CCArray* payArray = MB_RoleData::getInstance()->getPayArray();
    CCObject * obj;
    int tag = atoi(payid);
    CCARRAY_FOREACH(payArray, obj){
    
        MB_PayTemplete *templete = (MB_PayTemplete *)obj;
        if (templete->getID() == tag ) {
            
            amount = templete->getPrice();
            break;
        }
    }
    char roleid[100] ;
    char payinfo[100];
    char serverId[100];
    char serverName[100];
    char gameRoleName[100];
    char vipLevel[10];
    char gameUserLevel[10];
    
    
    sprintf(payinfo,"%d",MB_RoleData::getInstance()->getUID());
    sprintf(roleid,"%d",MB_RoleData::getInstance()->getUID());
    sprintf(serverId,"%d",MB_ServerList::getInstance()->getNowServerID());
    sprintf(serverName,"%s",MB_ServerList::getInstance()->getNowServerName());
    sprintf(gameRoleName,"%s",MB_RoleData::getInstance()->getName());
    sprintf(vipLevel,"%d",MB_RoleData::getInstance()->getVipLevel());
    sprintf(gameUserLevel,"%d",MB_RoleData::getInstance()->getLevel());
    
    std::string callbackInfoStr;
    callbackInfoStr.append(serverId);
    callbackInfoStr.append("|");
    callbackInfoStr.append(roleid);
    callbackInfoStr = urlencode(callbackInfoStr);
    
    //充值
    CFUUIDRef theUUID = CFUUIDCreate(NULL);
    CFStringRef guid = CFUUIDCreateString(NULL, theUUID);
    CFRelease(theUUID);
    NSString *uuidString = [((__bridge NSString *)guid) stringByReplacingOccurrencesOfString:@"-" withString:@""];
    CFRelease(guid);
    
    SMPCQuickSDKGameRoleInfo *role = [[SMPCQuickSDKGameRoleInfo alloc] init];
    SMPCQuickSDKPayOrderInfo *order = [[SMPCQuickSDKPayOrderInfo alloc] init];
    role.serverName = [NSString stringWithUTF8String:serverName]; //必填
    role.gameRoleName =[NSString stringWithUTF8String:gameRoleName] ;//@""
    role.serverId = [NSString stringWithUTF8String:serverId]; //需要是数字字符串
    role.gameRoleID =[NSString stringWithUTF8String:roleid] ;//
    role.gameUserBalance = @"0";//
    role.vipLevel = [NSString stringWithUTF8String:vipLevel];//
    role.gameUserLevel = [NSString stringWithUTF8String:gameUserLevel];
    role.partyName = @"ios";//
    order.goodsID = [NSString stringWithFormat:@"%d",1]; //必填 iap时注意和苹果开发者后台一致，或者渠道映射的
    order.productName = @"宝石";//必填
    order.cpOrderID = [uuidString lowercaseString]; //必填 游戏订单号
    order.count = 1;  //必填 数量
    order.amount = amount; //必填 总价
//    order.callbackUrl = @"";
    order.extrasParams =[NSString stringWithCString:callbackInfoStr.c_str() encoding:[NSString defaultCStringEncoding]]; 
    int error = [[SMPCQuickSDK defaultInstance] payOrderInfo:order
                                                    roleInfo:role];
    if (error!=0)
        NSLog(@"%d", error);

}

void  MB_YJMgr_IOS::setRoleData(){
    char roleid[100] ;
    char payinfo[100];
    char serverId[100];
    char serverName[100];
    char gameRoleName[100];
    char vipLevel[10];
    char gameUserLevel[10];
    
    sprintf(payinfo,"%d",MB_RoleData::getInstance()->getUID());
    sprintf(roleid,"%d",MB_RoleData::getInstance()->getUID());
    sprintf(serverId,"%d",MB_ServerList::getInstance()->getNowServerID());
    sprintf(serverName,"%s",MB_ServerList::getInstance()->getNowServerName());
    sprintf(gameRoleName,"%s",MB_RoleData::getInstance()->getName());
    sprintf(vipLevel,"%d",MB_RoleData::getInstance()->getVipLevel());
    sprintf(gameUserLevel,"%d",MB_RoleData::getInstance()->getLevel());
    
    // 更新角色信息
    SMPCQuickSDKGameRoleInfo *gameRoleInfo = [SMPCQuickSDKGameRoleInfo new];
    gameRoleInfo.serverName =[NSString stringWithUTF8String:serverName];
    gameRoleInfo.gameRoleName = [NSString stringWithUTF8String:gameRoleName] ;
    gameRoleInfo.serverId = [NSString stringWithUTF8String:serverId]; //需要是数字字符串
    gameRoleInfo.gameRoleID = [NSString stringWithUTF8String:roleid] ;;
    gameRoleInfo.gameUserBalance = @"0";
    gameRoleInfo.vipLevel = [NSString stringWithUTF8String:vipLevel];;
    gameRoleInfo.gameUserLevel = [NSString stringWithUTF8String:gameUserLevel];;
    gameRoleInfo.partyName = @"";
    
    [[SMPCQuickSDK defaultInstance] updateRoleInfoWith:gameRoleInfo isCreate:NO];//如果这个角色是刚刚创建的，这里isCreate可以传YES
    
}
void  MB_YJMgr_IOS::creatRole(){
    char roleid[100] ;
    char payinfo[100];
    char serverId[100];
    char serverName[100];
    char gameRoleName[100];
    char vipLevel[10];
    char gameUserLevel[10];
    
    sprintf(payinfo,"%d",MB_RoleData::getInstance()->getUID());
    sprintf(roleid,"%d",MB_RoleData::getInstance()->getUID());
    sprintf(serverId,"%d",MB_ServerList::getInstance()->getNowServerID());
    sprintf(serverName,"%s",MB_ServerList::getInstance()->getNowServerName());
    sprintf(gameRoleName,"%s",MB_RoleData::getInstance()->getName());
    sprintf(vipLevel,"%d",MB_RoleData::getInstance()->getVipLevel());
    sprintf(gameUserLevel,"%d",MB_RoleData::getInstance()->getLevel());
    
    // 更新角色信息
    SMPCQuickSDKGameRoleInfo *gameRoleInfo = [SMPCQuickSDKGameRoleInfo new];
    gameRoleInfo.serverName =[NSString stringWithUTF8String:serverName];
    gameRoleInfo.gameRoleName = [NSString stringWithUTF8String:gameRoleName] ;
    gameRoleInfo.serverId = [NSString stringWithUTF8String:serverId]; //需要是数字字符串
    gameRoleInfo.gameRoleID = [NSString stringWithUTF8String:roleid] ;;
    gameRoleInfo.gameUserBalance = @"0";
    gameRoleInfo.vipLevel = [NSString stringWithUTF8String:vipLevel];;
    gameRoleInfo.gameUserLevel = [NSString stringWithUTF8String:gameUserLevel];;
    gameRoleInfo.partyName = @"";
    [[SMPCQuickSDK defaultInstance] updateRoleInfoWith:gameRoleInfo isCreate:YES];//如果这个角色是刚刚创建的，这里isCreate可以传YES
}

//roleInfo.put("roleId", roleId);
//roleInfo.put("roleName", roleName); //当前登录的玩家角色名，不能为空，不能为 null
//roleInfo.put("roleLevel", String.valueOf(roleLevel)); //当前登录的玩家角色等级，必须为数字，且不能为 0，若无，传入 1
//roleInfo.put("zoneId", String.valueOf(serverId)); //当前登录的游戏区服 ID，必须为数字，且不能为 0，若无，传入 1
//roleInfo.put("zoneName", serverName);//当前登录的游戏区服名称，不能为空，不能为null
//roleInfo.put("balance", "0"); //用户游戏币余额，必须为数字，若无，传入 0
//roleInfo.put("vip", "1"); //当前用户 VIP 等级，必须为数字，若无，传入 1
//roleInfo.put("partyName", "无帮派");//当前角色所属帮派，不能为空，不能为 null，若无，传入“无帮派”
//roleInfo.put("roleCTime", String.valueOf(System.currentTimeMillis())); //单位为秒，创建角色的时间
//SFOnlineHelper.setData((ProjectMB) ProjectMB.getContext(),"enterServer",roleInfo.toString());
void  MB_YJMgr_IOS::enterGame(){
    setRoleData();

}
void  MB_YJMgr_IOS::roleLevelUp(){
    setRoleData();
}
void MB_YJMgr_IOS::onBuySuccess(const char *receipt,int payid,const char *deviceid){

}

void MB_YJMgr_IOS::removeLoading()
{
    MB_Message::sharedMB_Message()->removeALLMessage();
}


std::string MB_YJMgr_IOS::urlencode(std::string str_source) {
    char const *in_str = str_source.c_str();
    int in_str_len = strlen(in_str);
    int out_str_len = 0;
    std::string out_str;
    register unsigned char c;
    unsigned char *to, *start;
    unsigned char const *from, *end;
    unsigned char hexchars[] = "0123456789ABCDEF";
    
    from = (unsigned char *) in_str;
    end = (unsigned char *) in_str + in_str_len;
    start = to = (unsigned char *) malloc(3 * in_str_len + 1);
    
    while (from < end) {
        c = *from++;
        
        if (c == ' ') {
            *to++ = '+';
        } else if ((c < '0' && c != '-' && c != '.') || (c < 'A' && c > '9')
                   || (c > 'Z' && c < 'a' && c != '_') || (c > 'z' && c != '~')) {
            to[0] = '%';
            to[1] = hexchars[c >> 4];
            to[2] = hexchars[c & 15];
            to += 3;
        } else {
            *to++ = c;
        }
    }
    *to = 0;
    
    out_str_len = to - start;
    out_str = (char *) start;
    free(start);
    return out_str;
}
