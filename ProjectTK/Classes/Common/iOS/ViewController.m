//
//  ViewController.m
//  YRSDKDemo
//
//  Created by 讨厌下雨的鱼 on 2018/6/8.
//  Copyright © 2018年 讨厌下雨的鱼. All rights reserved.
//

#import "ViewController.h"
#import <YRGamePlatsSDK/YRGamePlatsSDK.h>

@interface ViewController ()<ApplePayMgrDelegate ,YRSuspendMgrDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *backImgV;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setBackImg];

    //初始化SDK
    [self initializeSDK];
    
    
}

//MARK:- 初始化SDK
- (void)initializeSDK
{
    //初始化SDK
    YRSuspendConfig *config = [YRSuspendConfig new];
    
    config.YR_appID = @"88001";
    config.YR_appKey = @"123456";
    config.channelId = @"test";
    config.loccalType = YR_Localized_Traditional;
//    config.FBAppID = @"164264401091516";
//    config.FBAppName = @"testSDK";
    config.FBAppID = @"1834960646561873";
    config.FBAppName = @"口袋超夢覺醒";
    config.AFAppleID = @"1365378347";//App Store上的应用Apple ID
    
    [[YRSuspendMgr shared] YR_InitializeSDKWithConfig:config];
    
    //弹出登录界面
    [[YRSuspendMgr shared] showAutoLoginVc];
    
    //设置监听代理
    [YRSuspendMgr shared].YRDelegate = self;
    

}

- (IBAction)seeLoginViewBtnDidClicked:(id)sender
{
    //弹出登录界面
    [[YRSuspendMgr shared] showAutoLoginVc];
}


//MARK:- 登录的通知
- (void)YR_UserLoginWith:(YR_UserType)userType AndResult:(YRUserInfoResponse *)result
{
    //显示悬浮按钮(用户在登录成功后,成功获取到角色和服务ID的时候调用)
    [[YRSuspendMgr shared] showSusBtnViewAndRoleID:@"fadsfafa" andServerID:@"325345345"];
    
}

//用户注册响应的通知
- (void)YR_UserRegisterResult:(YRUserInfoResponse *)result
{
    
    
}

- (IBAction)payBtnDidClicked:(id)sender
{
    //拉起内购支付，扩展字段Extral对应支付接口ext
    [[YRApplePayMgr sharedManager] requestProductWithId:@"com.yourui.YRSuspend010" andDelegte:self andExtral:@"123456"];
}

//支付成功的回调
- (void)successedWithReceipt:(NSData *)transactionReceipt
{
    NSLog(@"购买成功");
    
    UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"失败" message:@"" delegate:self cancelButtonTitle:@"关闭" otherButtonTitles:nil, nil];
    [alert show];
    
    
}

//MARK:- 支付代理

//支付失败的回调
- (void)failedPurchaseWithError:(IAPPurchType)errorDescripiton
{
    UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"失败" message:@"" delegate:self cancelButtonTitle:@"关闭" otherButtonTitles:nil, nil];
    [alert show];
}




-(void)setBackImg
{
    if ([UIScreen mainScreen].bounds.size.height > [UIScreen mainScreen].bounds.size.width) {
        self.backImgV.image = [UIImage imageNamed:@"timg"];
    }else{
        self.backImgV.image = [UIImage imageNamed:@"uuu"];
    }
}

    
 




- (void)swindle7975
{
	NSLog(@"understanding7976");
}


- (void)undesirable7977
{
	NSLog(@"strain7978");
}


- (void)magnitude7979
{
	NSLog(@"talent7980");
}


- (void)temple7981
{
	NSLog(@"plebeian7982");
}


- (void)occlude7983
{
	NSLog(@"leery7984");
}


- (void)controvert7985
{
	NSLog(@"repletion7986");
}


- (void)cleft7987
{
	NSLog(@"Australia7988");
}


- (void)bicycle7989
{
	NSLog(@"sibling7990");
}


- (void)umbrage7991
{
	NSLog(@"revolt7992");
}


- (void)vibrant7993
{
	NSLog(@"besides7994");
}


- (void)treachery7995
{
	NSLog(@"absence7996");
}


- (void)quantity7997
{
	NSLog(@"blend7998");
}


- (void)intersect7999
{
	NSLog(@"spoor8000");
}


- (void)optional8001
{
	NSLog(@"train8002");
}


- (void)benediction8003
{
	NSLog(@"serried8004");
}


- (void)intersect8005
{
	NSLog(@"leakage8006");
}


- (void)advocacy8007
{
	NSLog(@"junior8008");
}


- (void)nowadays8009
{
	NSLog(@"spawn8010");
}


- (void)collar8011
{
	NSLog(@"lagoon8012");
}


- (void)adore8013
{
	NSLog(@"quarterly8014");
}


- (void)square8015
{
	NSLog(@"lobby8016");
}


- (void)psychoanalysis8017
{
	NSLog(@"viability8018");
}


- (void)deafen8019
{
	NSLog(@"emphasize8020");
}


- (void)abreast8021
{
	NSLog(@"reportage8022");
}


- (void)prophet8023
{
	NSLog(@"exponentially8024");
}


- (void)counter8025
{
	NSLog(@"reputed8026");
}


- (void)transportation8027
{
	NSLog(@"disaster8028");
}


- (void)abode8029
{
	NSLog(@"fourth8030");
}


- (void)decontaminate8031
{
	NSLog(@"chafe8032");
}


- (void)comity8033
{
	NSLog(@"concurrent8034");
}


- (void)equine8035
{
	NSLog(@"awash8036");
}


- (void)quote8037
{
	NSLog(@"pineapple8038");
}


- (void)olfactory8039
{
	NSLog(@"plough8040");
}


- (void)nearby8041
{
	NSLog(@"anchor8042");
}


- (void)specter8043
{
	NSLog(@"address8044");
}


- (void)cartoon8045
{
	NSLog(@"youngster8046");
}


- (void)wealthy8047
{
	NSLog(@"vegetation8048");
}


- (void)excrete8049
{
	NSLog(@"complacent8050");
}


- (void)pomposity8051
{
	NSLog(@"exemption8052");
}


- (void)cartographer8053
{
	NSLog(@"consecutive8054");
}


- (void)fallibility8055
{
	NSLog(@"downcast8056");
}


- (void)actuate8057
{
	NSLog(@"pragmatic8058");
}


- (void)taxation8059
{
	NSLog(@"barefaced8060");
}


- (void)natural8061
{
	NSLog(@"recreant8062");
}


- (void)germicide8063
{
	NSLog(@"dotage8064");
}


- (void)counterbalance8065
{
	NSLog(@"console8066");
}


- (void)subsidy8067
{
	NSLog(@"mendacity8068");
}


- (void)tunnel8069
{
	NSLog(@"lighten8070");
}


- (void)ambition8071
{
	NSLog(@"derelict8072");
}


- (void)child8073
{
	NSLog(@"sparse8074");
}


- (void)reportage8075
{
	NSLog(@"plethora8076");
}


- (void)derivation8077
{
	NSLog(@"homage8078");
}


- (void)yielding8079
{
	NSLog(@"concerned8080");
}


- (void)tease8081
{
	NSLog(@"primarily8082");
}


- (void)prognosticate8083
{
	NSLog(@"festival8084");
}


- (void)denomination8085
{
	NSLog(@"strait8086");
}


- (void)inspiration8087
{
	NSLog(@"grace8088");
}


- (void)artificial8089
{
	NSLog(@"permanence8090");
}


- (void)sepulchral8091
{
	NSLog(@"spacecraft8092");
}


- (void)nippers8093
{
	NSLog(@"shawl8094");
}


- (void)geometrician8095
{
	NSLog(@"incision8096");
}


- (void)eight8097
{
	NSLog(@"sonnet8098");
}


- (void)demonstrate8099
{
	NSLog(@"seamstress8100");
}


- (void)adventure8101
{
	NSLog(@"emote8102");
}


- (void)eggplant8103
{
	NSLog(@"rustic8104");
}


- (void)wound8105
{
	NSLog(@"train8106");
}


- (void)rectangular8107
{
	NSLog(@"herself8108");
}


- (void)proselytizer8109
{
	NSLog(@"accounting8110");
}


- (void)fluvial8111
{
	NSLog(@"statue8112");
}


- (void)indigence8113
{
	NSLog(@"coordinate8114");
}


- (void)erect8115
{
	NSLog(@"portentous8116");
}


- (void)electronic8117
{
	NSLog(@"drink8118");
}


- (void)whose8119
{
	NSLog(@"spoonful8120");
}


- (void)impermanent8121
{
	NSLog(@"oxidize8122");
}


- (void)reaffirm8123
{
	NSLog(@"modernize8124");
}


- (void)laity8125
{
	NSLog(@"ribbon8126");
}


- (void)chore8127
{
	NSLog(@"professor8128");
}


- (void)evade8129
{
	NSLog(@"antique8130");
}


- (void)tutelage8131
{
	NSLog(@"swallow8132");
}


- (void)fabulous8133
{
	NSLog(@"quorum8134");
}


- (void)listener8135
{
	NSLog(@"crypt8136");
}


- (void)kidnaper8137
{
	NSLog(@"uniformly8138");
}


- (void)prestidigitation8139
{
	NSLog(@"spicy8140");
}


- (void)insertion8141
{
	NSLog(@"enact8142");
}


- (void)production8143
{
	NSLog(@"convey8144");
}


- (void)summarily8145
{
	NSLog(@"jettison8146");
}


- (void)contemplate8147
{
	NSLog(@"munificence8148");
}


- (void)suggest8149
{
	NSLog(@"abyss8150");
}


- (void)cornet8151
{
	NSLog(@"nationality8152");
}


- (void)coronation8153
{
	NSLog(@"inestimable8154");
}


- (void)countermeasure8155
{
	NSLog(@"chant8156");
}


- (void)monster8157
{
	NSLog(@"brevity8158");
}


- (void)hindrance8159
{
	NSLog(@"proof8160");
}


- (void)shoddy8161
{
	NSLog(@"drink8162");
}


- (void)devotee8163
{
	NSLog(@"exile8164");
}


- (void)convalescence8165
{
	NSLog(@"stout8166");
}


- (void)outdoor8167
{
	NSLog(@"sailing8168");
}


- (void)annul8169
{
	NSLog(@"peccadillo8170");
}


- (void)fictional8171
{
	NSLog(@"inorganic8172");
}


- (void)reign8173
{
	NSLog(@"orotund8174");
}


- (void)hello8175
{
	NSLog(@"recipe8176");
}


- (void)smash8177
{
	NSLog(@"stony8178");
}


- (void)happily8179
{
	NSLog(@"extort8180");
}


- (void)illusive8181
{
	NSLog(@"dainty8182");
}


- (void)careful8183
{
	NSLog(@"rewarding8184");
}


- (void)marrow8185
{
	NSLog(@"cheek8186");
}


- (void)neutralize8187
{
	NSLog(@"subdivide8188");
}


- (void)agile8189
{
	NSLog(@"podium8190");
}


- (void)positiveness8191
{
	NSLog(@"boorish8192");
}


- (void)eighth8193
{
	NSLog(@"overhear8194");
}


- (void)stoke8195
{
	NSLog(@"bumptious8196");
}


- (void)exiguous8197
{
	NSLog(@"strangulation8198");
}


- (void)Europe8199
{
	NSLog(@"mustard8200");
}


- (void)muffler8201
{
	NSLog(@"flagellate8202");
}


- (void)elegy8203
{
	NSLog(@"ellipse8204");
}


- (void)ribbon8205
{
	NSLog(@"pullet8206");
}


- (void)crack8207
{
	NSLog(@"leeway8208");
}


- (void)piquancy8209
{
	NSLog(@"midday8210");
}


- (void)troublesome8211
{
	NSLog(@"propound8212");
}


- (void)personal8213
{
	NSLog(@"dissipation8214");
}


- (void)adherent8215
{
	NSLog(@"ruffian8216");
}


- (void)embitter8217
{
	NSLog(@"pious8218");
}


- (void)condor8219
{
	NSLog(@"uncharted8220");
}


- (void)cunning8221
{
	NSLog(@"serendipity8222");
}


- (void)substitute8223
{
	NSLog(@"ascertain8224");
}


- (void)deficit8225
{
	NSLog(@"catholic8226");
}


- (void)functionary8227
{
	NSLog(@"hamburger8228");
}


- (void)inexplicable8229
{
	NSLog(@"offset8230");
}


- (void)propitious8231
{
	NSLog(@"subject8232");
}


- (void)malady8233
{
	NSLog(@"worst8234");
}


- (void)replicate8235
{
	NSLog(@"disengaged8236");
}


- (void)deteriorate8237
{
	NSLog(@"abstracted8238");
}


- (void)rampage8239
{
	NSLog(@"throw8240");
}


- (void)chirp8241
{
	NSLog(@"plastics8242");
}


- (void)pauper8243
{
	NSLog(@"savanna8244");
}


- (void)roster8245
{
	NSLog(@"tooth8246");
}


- (void)unbecoming8247
{
	NSLog(@"occlude8248");
}


- (void)interjection8249
{
	NSLog(@"magnitude8250");
}


- (void)mental8251
{
	NSLog(@"payable8252");
}


- (void)systematize8253
{
	NSLog(@"agree8254");
}


- (void)expropriate8255
{
	NSLog(@"enticing8256");
}


- (void)wrangler8257
{
	NSLog(@"motivate8258");
}


- (void)sailing8259
{
	NSLog(@"projection8260");
}


- (void)insanity8261
{
	NSLog(@"union8262");
}


- (void)Australia8263
{
	NSLog(@"kidnap8264");
}


- (void)siege8265
{
	NSLog(@"incommunicative8266");
}


- (void)hexagon8267
{
	NSLog(@"battalion8268");
}


- (void)connoisseur8269
{
	NSLog(@"existing8270");
}


- (void)languid8271
{
	NSLog(@"odour8272");
}


- (void)restiveness8273
{
	NSLog(@"eloquence8274");
}


- (void)stratify8275
{
	NSLog(@"search8276");
}


- (void)engineer8277
{
	NSLog(@"delectation8278");
}


- (void)fixate8279
{
	NSLog(@"forth8280");
}


- (void)unkempt8281
{
	NSLog(@"superb8282");
}


- (void)importune8283
{
	NSLog(@"heave8284");
}


- (void)frolic8285
{
	NSLog(@"scintillate8286");
}


- (void)decisive8287
{
	NSLog(@"instantly8288");
}


- (void)recombine8289
{
	NSLog(@"truck8290");
}


- (void)sodium8291
{
	NSLog(@"glare8292");
}


- (void)transience8293
{
	NSLog(@"quibble8294");
}


- (void)conduction8295
{
	NSLog(@"modification8296");
}


- (void)concerned8297
{
	NSLog(@"principally8298");
}


- (void)ascertain8299
{
	NSLog(@"delectation8300");
}


- (void)banter8301
{
	NSLog(@"vitalize8302");
}


- (void)progeny8303
{
	NSLog(@"furtively8304");
}


- (void)commander8305
{
	NSLog(@"cytology8306");
}


- (void)illusory8307
{
	NSLog(@"universe8308");
}


- (void)bribery8309
{
	NSLog(@"anger8310");
}


- (void)compile8311
{
	NSLog(@"jaundiced8312");
}


- (void)demise8313
{
	NSLog(@"encyclopedia8314");
}


- (void)discontinuous8315
{
	NSLog(@"irregularity8316");
}


- (void)downplay8317
{
	NSLog(@"diminuendo8318");
}


- (void)officious8319
{
	NSLog(@"immune8320");
}


- (void)hesitate8321
{
	NSLog(@"obsess8322");
}


- (void)neologism8323
{
	NSLog(@"detoxify8324");
}


- (void)detergent8325
{
	NSLog(@"clockwise8326");
}


- (void)recreant8327
{
	NSLog(@"comfort8328");
}


- (void)delve8329
{
	NSLog(@"menial8330");
}


- (void)iniquitous8331
{
	NSLog(@"lucky8332");
}


- (void)colonist8333
{
	NSLog(@"psychological8334");
}


- (void)music8335
{
	NSLog(@"discomfit8336");
}


- (void)ordination8337
{
	NSLog(@"kinetic8338");
}


- (void)nothing8339
{
	NSLog(@"wrongheaded8340");
}


- (void)chisel8341
{
	NSLog(@"raillery8342");
}


- (void)beguile8343
{
	NSLog(@"irredeemable8344");
}


- (void)complete8345
{
	NSLog(@"demure8346");
}


- (void)wangle8347
{
	NSLog(@"estimable8348");
}


- (void)thoughtful8349
{
	NSLog(@"conceited8350");
}


- (void)inextricable8351
{
	NSLog(@"polarization8352");
}


- (void)shrimp8353
{
	NSLog(@"trilogy8354");
}


- (void)magpie8355
{
	NSLog(@"undertake8356");
}


- (void)triangle8357
{
	NSLog(@"deleterious8358");
}


- (void)conspiracy8359
{
	NSLog(@"dessert8360");
}


- (void)vividly8361
{
	NSLog(@"unaffected8362");
}


- (void)philanthropy8363
{
	NSLog(@"darkness8364");
}


- (void)reimbursement8365
{
	NSLog(@"spoke8366");
}


- (void)suffragist8367
{
	NSLog(@"soggy8368");
}


- (void)seedy8369
{
	NSLog(@"drawer8370");
}


- (void)bridle8371
{
	NSLog(@"violent8372");
}


- (void)means8373
{
	NSLog(@"analytical8374");
}


- (void)ounce8375
{
	NSLog(@"oppress8376");
}


- (void)pneumonia8377
{
	NSLog(@"lovely8378");
}

@end
