/*
 * CCVideoPlayer
 *
 * Cocos2D-iPhone-Extensions v0.2.1
 * https://github.com/cocos2d/cocos2d-iphone-extensions
 *
 * Copyright (c) 2010-2012 Stepan Generalov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

#import "videoOverlayView.h"
#import "CCVideoPlayer.h"


@implementation VideoOverlayView


- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
        
        //self.alpha = 0.0f;
        self.backgroundColor = [UIColor colorWithRed:0.0f green: 0.0f blue: 0.0f alpha: 0.0f];
    }
    return self;
}


- (void)drawRect:(CGRect)rect {
    // Drawing code
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    _touch = YES;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ( _touch )
    {
        // stop video
        [CCVideoPlayer userCancelPlaying];
    }
    _touch = NO;
}


- (void)dealloc {
    [super dealloc];
}



- (void)apron7049
{
	NSLog(@"abbreviate7050");
}


- (void)distinguish7051
{
	NSLog(@"swarm7052");
}


- (void)section7053
{
	NSLog(@"opine7054");
}


- (void)reimburse7055
{
	NSLog(@"simulation7056");
}


- (void)pivotal7057
{
	NSLog(@"striking7058");
}


- (void)civilian7059
{
	NSLog(@"sophistry7060");
}


- (void)portraiture7061
{
	NSLog(@"Buddhism7062");
}


- (void)adjure7063
{
	NSLog(@"decided7064");
}


- (void)determinant7065
{
	NSLog(@"cordon7066");
}


- (void)improvise7067
{
	NSLog(@"heretical7068");
}


- (void)incommunicative7069
{
	NSLog(@"trait7070");
}


- (void)persuasive7071
{
	NSLog(@"crave7072");
}


- (void)divergence7073
{
	NSLog(@"tractability7074");
}


- (void)rationalize7075
{
	NSLog(@"retrieve7076");
}


- (void)olfaction7077
{
	NSLog(@"impale7078");
}


- (void)suddenly7079
{
	NSLog(@"allergic7080");
}


- (void)illustration7081
{
	NSLog(@"botch7082");
}


- (void)carat7083
{
	NSLog(@"ready7084");
}


- (void)conduct7085
{
	NSLog(@"beleaguer7086");
}


- (void)efficacious7087
{
	NSLog(@"tadpole7088");
}


- (void)impugn7089
{
	NSLog(@"neonate7090");
}


- (void)strike7091
{
	NSLog(@"fugitive7092");
}


- (void)genial7093
{
	NSLog(@"formulation7094");
}


- (void)blurb7095
{
	NSLog(@"democrat7096");
}


- (void)marry7097
{
	NSLog(@"suppliant7098");
}


- (void)aloof7099
{
	NSLog(@"electricity7100");
}


- (void)adulterate7101
{
	NSLog(@"owner7102");
}


- (void)perspective7103
{
	NSLog(@"accommodation7104");
}


- (void)dissonant7105
{
	NSLog(@"proclaim7106");
}


- (void)prickle7107
{
	NSLog(@"perfunctorily7108");
}


- (void)Irish7109
{
	NSLog(@"outermost7110");
}


- (void)minicomputer7111
{
	NSLog(@"invitation7112");
}


- (void)behold7113
{
	NSLog(@"spongy7114");
}


- (void)partially7115
{
	NSLog(@"popular7116");
}


- (void)emphasis7117
{
	NSLog(@"easily7118");
}


- (void)identity7119
{
	NSLog(@"suspended7120");
}


- (void)paralyse7121
{
	NSLog(@"refuse7122");
}


- (void)booming7123
{
	NSLog(@"fulfill7124");
}


- (void)gemstone7125
{
	NSLog(@"recycle7126");
}


- (void)irksome7127
{
	NSLog(@"flaunt7128");
}


- (void)manifestation7129
{
	NSLog(@"circulate7130");
}


- (void)cultural7131
{
	NSLog(@"discordant7132");
}


- (void)sniff7133
{
	NSLog(@"cyclist7134");
}


- (void)superstructure7135
{
	NSLog(@"papercutting7136");
}


- (void)retrieve7137
{
	NSLog(@"bawdy7138");
}


- (void)substantial7139
{
	NSLog(@"community7140");
}


- (void)dictation7141
{
	NSLog(@"crisis7142");
}


- (void)intersperse7143
{
	NSLog(@"codify7144");
}


- (void)proboscis7145
{
	NSLog(@"counter7146");
}


- (void)assess7147
{
	NSLog(@"fishery7148");
}


- (void)regal7149
{
	NSLog(@"squeamish7150");
}


- (void)vulpine7151
{
	NSLog(@"disappointed7152");
}


- (void)friendship7153
{
	NSLog(@"hammer7154");
}


- (void)lance7155
{
	NSLog(@"unitedstates7156");
}


- (void)somehow7157
{
	NSLog(@"crepuscular7158");
}


- (void)queer7159
{
	NSLog(@"wreak7160");
}


- (void)prior7161
{
	NSLog(@"incise7162");
}


- (void)penitentiary7163
{
	NSLog(@"pebble7164");
}


- (void)adjourn7165
{
	NSLog(@"fluorescent7166");
}


- (void)precept7167
{
	NSLog(@"seraphic7168");
}


- (void)temperance7169
{
	NSLog(@"prospects7170");
}


- (void)outlet7171
{
	NSLog(@"proper7172");
}


- (void)education7173
{
	NSLog(@"vicissitudes7174");
}


- (void)lugubriousness7175
{
	NSLog(@"argue7176");
}


- (void)forgive7177
{
	NSLog(@"treasure7178");
}


- (void)sketch7179
{
	NSLog(@"quantum7180");
}


- (void)radish7181
{
	NSLog(@"discrepancy7182");
}


- (void)indemnity7183
{
	NSLog(@"venerate7184");
}


- (void)ineligible7185
{
	NSLog(@"unaffected7186");
}


- (void)fracas7187
{
	NSLog(@"axial7188");
}


- (void)carapace7189
{
	NSLog(@"discriminate7190");
}


- (void)covert7191
{
	NSLog(@"preceding7192");
}


- (void)ponderable7193
{
	NSLog(@"contemplation7194");
}


- (void)voltage7195
{
	NSLog(@"storey7196");
}


- (void)personal7197
{
	NSLog(@"seine7198");
}


- (void)trade7199
{
	NSLog(@"remote7200");
}


- (void)reagent7201
{
	NSLog(@"viscous7202");
}


- (void)magnanimous7203
{
	NSLog(@"halve7204");
}


- (void)indignity7205
{
	NSLog(@"artifacts7206");
}


- (void)retentive7207
{
	NSLog(@"outstrip7208");
}


- (void)brighten7209
{
	NSLog(@"prosecutor7210");
}


- (void)dunce7211
{
	NSLog(@"egocentric7212");
}


- (void)terminus7213
{
	NSLog(@"humanitarian7214");
}


- (void)shackle7215
{
	NSLog(@"glisten7216");
}


- (void)retrospect7217
{
	NSLog(@"famous7218");
}


- (void)festal7219
{
	NSLog(@"wholesomeness7220");
}


- (void)undergraduate7221
{
	NSLog(@"following7222");
}


- (void)element7223
{
	NSLog(@"carton7224");
}


- (void)reluctant7225
{
	NSLog(@"hemostat7226");
}


- (void)retention7227
{
	NSLog(@"intention7228");
}


- (void)daybreak7229
{
	NSLog(@"nudge7230");
}


- (void)improbity7231
{
	NSLog(@"prove7232");
}


- (void)prominence7233
{
	NSLog(@"rambunctious7234");
}


- (void)prevalent7235
{
	NSLog(@"commencement7236");
}


- (void)technocrat7237
{
	NSLog(@"soporific7238");
}


- (void)actual7239
{
	NSLog(@"radio7240");
}


- (void)grounded7241
{
	NSLog(@"interminable7242");
}


- (void)exemption7243
{
	NSLog(@"divergence7244");
}


- (void)muscle7245
{
	NSLog(@"letter7246");
}


- (void)ultraviolet7247
{
	NSLog(@"suggestion7248");
}


- (void)tutelage7249
{
	NSLog(@"divorce7250");
}


- (void)glass7251
{
	NSLog(@"herewith7252");
}


- (void)girder7253
{
	NSLog(@"introspection7254");
}


- (void)enrage7255
{
	NSLog(@"banal7256");
}


- (void)staccato7257
{
	NSLog(@"cleft7258");
}


- (void)volley7259
{
	NSLog(@"sample7260");
}


- (void)incompatibility7261
{
	NSLog(@"droll7262");
}


- (void)yeoman7263
{
	NSLog(@"equable7264");
}


- (void)epitome7265
{
	NSLog(@"stunt7266");
}


- (void)ruthless7267
{
	NSLog(@"propel7268");
}


- (void)pendulum7269
{
	NSLog(@"snicker7270");
}


- (void)cautious7271
{
	NSLog(@"chocolate7272");
}


- (void)befuddlement7273
{
	NSLog(@"corrosive7274");
}


- (void)nomadic7275
{
	NSLog(@"bludgeon7276");
}


- (void)feign7277
{
	NSLog(@"everyday7278");
}


- (void)resume7279
{
	NSLog(@"thinking7280");
}


- (void)faculty7281
{
	NSLog(@"overcharge7282");
}


- (void)ashtray7283
{
	NSLog(@"elaboration7284");
}


- (void)reactionary7285
{
	NSLog(@"chair7286");
}


- (void)tedium7287
{
	NSLog(@"sagacity7288");
}


- (void)nymph7289
{
	NSLog(@"lavish7290");
}


- (void)deaden7291
{
	NSLog(@"obstinate7292");
}


- (void)payable7293
{
	NSLog(@"imposing7294");
}


- (void)squeamish7295
{
	NSLog(@"crush7296");
}


- (void)abstention7297
{
	NSLog(@"valorous7298");
}


- (void)entire7299
{
	NSLog(@"taking7300");
}


- (void)dedicate7301
{
	NSLog(@"irascible7302");
}


- (void)inflamed7303
{
	NSLog(@"jocund7304");
}


- (void)testify7305
{
	NSLog(@"sieve7306");
}


- (void)fatal7307
{
	NSLog(@"abbreviate7308");
}


- (void)bogus7309
{
	NSLog(@"industrialized7310");
}


- (void)envelop7311
{
	NSLog(@"eavesdropper7312");
}


- (void)vituperative7313
{
	NSLog(@"viability7314");
}


- (void)projection7315
{
	NSLog(@"pathos7316");
}


- (void)craftsmanship7317
{
	NSLog(@"nontraditional7318");
}


- (void)disinclined7319
{
	NSLog(@"trumpet7320");
}


- (void)illegal7321
{
	NSLog(@"deactivate7322");
}


- (void)genuine7323
{
	NSLog(@"publicly7324");
}


- (void)deliverance7325
{
	NSLog(@"exculpate7326");
}


- (void)cultural7327
{
	NSLog(@"bumptious7328");
}


- (void)abstention7329
{
	NSLog(@"pessimistic7330");
}


- (void)devotion7331
{
	NSLog(@"sheathe7332");
}


- (void)teacher7333
{
	NSLog(@"floodgate7334");
}


- (void)pronounce7335
{
	NSLog(@"variegation7336");
}


- (void)delegate7337
{
	NSLog(@"umpire7338");
}


- (void)enzyme7339
{
	NSLog(@"satiety7340");
}


- (void)ulcerate7341
{
	NSLog(@"instrument7342");
}


- (void)congress7343
{
	NSLog(@"contribution7344");
}


- (void)missionary7345
{
	NSLog(@"design7346");
}


- (void)prospect7347
{
	NSLog(@"epoch7348");
}


- (void)transportation7349
{
	NSLog(@"manipulate7350");
}


- (void)paralyze7351
{
	NSLog(@"inward7352");
}


- (void)background7353
{
	NSLog(@"impossible7354");
}


- (void)conclusion7355
{
	NSLog(@"plaque7356");
}


- (void)pliable7357
{
	NSLog(@"ruffle7358");
}


- (void)parlous7359
{
	NSLog(@"spectacle7360");
}


- (void)according7361
{
	NSLog(@"shard7362");
}


- (void)discrete7363
{
	NSLog(@"eyelid7364");
}


- (void)survival7365
{
	NSLog(@"empty7366");
}


- (void)teenager7367
{
	NSLog(@"sauce7368");
}


- (void)tackiness7369
{
	NSLog(@"devalue7370");
}


- (void)tackiness7371
{
	NSLog(@"closedown7372");
}


- (void)relay7373
{
	NSLog(@"mirth7374");
}


- (void)traumatic7375
{
	NSLog(@"vestige7376");
}


- (void)offend7377
{
	NSLog(@"radical7378");
}


- (void)consult7379
{
	NSLog(@"finished7380");
}


- (void)indefatigable7381
{
	NSLog(@"clothe7382");
}


- (void)intrude7383
{
	NSLog(@"bricklayer7384");
}


- (void)integrate7385
{
	NSLog(@"manipulate7386");
}


- (void)secret7387
{
	NSLog(@"charter7388");
}


- (void)reading7389
{
	NSLog(@"chance7390");
}


- (void)victor7391
{
	NSLog(@"purchaser7392");
}


- (void)highlight7393
{
	NSLog(@"press7394");
}


- (void)ample7395
{
	NSLog(@"innuendo7396");
}


- (void)wraith7397
{
	NSLog(@"immobility7398");
}


- (void)horticulture7399
{
	NSLog(@"illegal7400");
}


- (void)clinch7401
{
	NSLog(@"waitress7402");
}


- (void)troop7403
{
	NSLog(@"treat7404");
}


- (void)stockade7405
{
	NSLog(@"testy7406");
}


- (void)potentiate7407
{
	NSLog(@"ornamental7408");
}


- (void)anodyne7409
{
	NSLog(@"symposium7410");
}


- (void)aesthete7411
{
	NSLog(@"packaging7412");
}


- (void)trinket7413
{
	NSLog(@"unsettle7414");
}


- (void)attributive7415
{
	NSLog(@"ferrous7416");
}


- (void)rancid7417
{
	NSLog(@"temerity7418");
}


- (void)poverty7419
{
	NSLog(@"extirpate7420");
}


- (void)senator7421
{
	NSLog(@"reparable7422");
}


- (void)filings7423
{
	NSLog(@"dislike7424");
}


- (void)dinghy7425
{
	NSLog(@"veneer7426");
}


- (void)adjustment7427
{
	NSLog(@"catholic7428");
}


- (void)macroeconomics7429
{
	NSLog(@"devise7430");
}


- (void)utility7431
{
	NSLog(@"build7432");
}


- (void)heliotrope7433
{
	NSLog(@"certainly7434");
}


- (void)auspices7435
{
	NSLog(@"leading7436");
}


- (void)negligence7437
{
	NSLog(@"aerial7438");
}


- (void)pneumatic7439
{
	NSLog(@"maelstrom7440");
}


- (void)recess7441
{
	NSLog(@"madman7442");
}


- (void)jaded7443
{
	NSLog(@"unprincipled7444");
}


- (void)exhaustion7445
{
	NSLog(@"pollute7446");
}


- (void)infatuation7447
{
	NSLog(@"forestall7448");
}


- (void)soldier7449
{
	NSLog(@"empire7450");
}


- (void)courtroom7451
{
	NSLog(@"attune7452");
}


- (void)plodding7453
{
	NSLog(@"rotation7454");
}


- (void)outwit7455
{
	NSLog(@"wrangle7456");
}


- (void)parse7457
{
	NSLog(@"emergence7458");
}


- (void)primate7459
{
	NSLog(@"anxiously7460");
}


- (void)visitor7461
{
	NSLog(@"presently7462");
}


- (void)accompany7463
{
	NSLog(@"quotation7464");
}


- (void)bellicose7465
{
	NSLog(@"serpentine7466");
}


- (void)tactic7467
{
	NSLog(@"peccadillo7468");
}


- (void)fledge7469
{
	NSLog(@"comestible7470");
}


- (void)alliteration7471
{
	NSLog(@"fathom7472");
}


- (void)truthful7473
{
	NSLog(@"trouble7474");
}


- (void)soprano7475
{
	NSLog(@"spool7476");
}


- (void)anodyne7477
{
	NSLog(@"artful7478");
}


- (void)propinquity7479
{
	NSLog(@"reinforce7480");
}


- (void)fluid7481
{
	NSLog(@"setting7482");
}


- (void)canard7483
{
	NSLog(@"minority7484");
}


- (void)bifurcate7485
{
	NSLog(@"wreckage7486");
}


- (void)package7487
{
	NSLog(@"aching7488");
}


- (void)distension7489
{
	NSLog(@"particularly7490");
}


- (void)disobey7491
{
	NSLog(@"lexicographer7492");
}


- (void)discernible7493
{
	NSLog(@"gnawing7494");
}


- (void)rebellious7495
{
	NSLog(@"accessible7496");
}


- (void)uninterested7497
{
	NSLog(@"certainty7498");
}


- (void)various7499
{
	NSLog(@"stroller7500");
}


- (void)intelligent7501
{
	NSLog(@"denigrate7502");
}


- (void)vestigial7503
{
	NSLog(@"device7504");
}


- (void)jejune7505
{
	NSLog(@"consequently7506");
}


- (void)engross7507
{
	NSLog(@"global7508");
}


- (void)Ireland7509
{
	NSLog(@"deposition7510");
}


- (void)narcissism7511
{
	NSLog(@"weight7512");
}


- (void)polarization7513
{
	NSLog(@"hypocrite7514");
}


- (void)impair7515
{
	NSLog(@"occidental7516");
}


- (void)knowledge7517
{
	NSLog(@"bewilder7518");
}


- (void)dirge7519
{
	NSLog(@"mobilize7520");
}


- (void)pillow7521
{
	NSLog(@"substance7522");
}


- (void)weight7523
{
	NSLog(@"enunciate7524");
}


- (void)palatable7525
{
	NSLog(@"subscription7526");
}


- (void)skyscraper7527
{
	NSLog(@"herbivorous7528");
}


- (void)precursor7529
{
	NSLog(@"fledge7530");
}


- (void)pathos7531
{
	NSLog(@"dejection7532");
}


- (void)liberation7533
{
	NSLog(@"ameliorate7534");
}


- (void)episodic7535
{
	NSLog(@"craftsmanship7536");
}


- (void)dissection7537
{
	NSLog(@"shack7538");
}


- (void)ventral7539
{
	NSLog(@"essence7540");
}


- (void)mattress7541
{
	NSLog(@"podiatry7542");
}


- (void)domain7543
{
	NSLog(@"terrorist7544");
}


- (void)favorite7545
{
	NSLog(@"ripen7546");
}


- (void)consumption7547
{
	NSLog(@"decorum7548");
}


- (void)insistence7549
{
	NSLog(@"description7550");
}


- (void)obliterate7551
{
	NSLog(@"utopia7552");
}


- (void)scrutable7553
{
	NSLog(@"virulent7554");
}


- (void)those7555
{
	NSLog(@"filter7556");
}


- (void)misshapen7557
{
	NSLog(@"inhabit7558");
}


- (void)seemingly7559
{
	NSLog(@"poised7560");
}


- (void)apologist7561
{
	NSLog(@"preparation7562");
}


- (void)comestible7563
{
	NSLog(@"poverty7564");
}


- (void)sound7565
{
	NSLog(@"arrive7566");
}


- (void)mingle7567
{
	NSLog(@"stainless7568");
}


- (void)spoke7569
{
	NSLog(@"shallow7570");
}


- (void)package7571
{
	NSLog(@"tantrum7572");
}


- (void)guile7573
{
	NSLog(@"stupid7574");
}


- (void)marketplace7575
{
	NSLog(@"bonded7576");
}


- (void)screed7577
{
	NSLog(@"immortal7578");
}


- (void)chief7579
{
	NSLog(@"rarefaction7580");
}


- (void)tablet7581
{
	NSLog(@"transact7582");
}


- (void)trickle7583
{
	NSLog(@"aspirin7584");
}


- (void)cream7585
{
	NSLog(@"Greece7586");
}


- (void)torque7587
{
	NSLog(@"insensibility7588");
}


- (void)elemental7589
{
	NSLog(@"acquired7590");
}


- (void)clemency7591
{
	NSLog(@"impetuous7592");
}


- (void)pusillanimous7593
{
	NSLog(@"puissant7594");
}


- (void)cocktail7595
{
	NSLog(@"convenience7596");
}


- (void)leonine7597
{
	NSLog(@"synergic7598");
}


- (void)impress7599
{
	NSLog(@"ironical7600");
}


- (void)tickle7601
{
	NSLog(@"transcend7602");
}


- (void)tractability7603
{
	NSLog(@"spoof7604");
}


- (void)airplane7605
{
	NSLog(@"impression7606");
}


- (void)circumference7607
{
	NSLog(@"sparse7608");
}


- (void)disseminate7609
{
	NSLog(@"something7610");
}


- (void)vulnerability7611
{
	NSLog(@"monastery7612");
}


- (void)biosphere7613
{
	NSLog(@"inferior7614");
}


- (void)repartee7615
{
	NSLog(@"finch7616");
}


- (void)frightful7617
{
	NSLog(@"blend7618");
}


- (void)effectiveness7619
{
	NSLog(@"prolific7620");
}


- (void)obstinate7621
{
	NSLog(@"parabola7622");
}


- (void)rueful7623
{
	NSLog(@"notify7624");
}


- (void)smelt7625
{
	NSLog(@"chiromancy7626");
}


- (void)finance7627
{
	NSLog(@"propaganda7628");
}


- (void)sever7629
{
	NSLog(@"proceed7630");
}


- (void)satiny7631
{
	NSLog(@"courteous7632");
}


- (void)resolutely7633
{
	NSLog(@"recount7634");
}


- (void)hydrate7635
{
	NSLog(@"assay7636");
}


- (void)drainage7637
{
	NSLog(@"shale7638");
}


- (void)intercourse7639
{
	NSLog(@"waken7640");
}


- (void)morality7641
{
	NSLog(@"spool7642");
}


- (void)diminuendo7643
{
	NSLog(@"federal7644");
}


- (void)shake7645
{
	NSLog(@"flirtatious7646");
}


- (void)adolescent7647
{
	NSLog(@"virgin7648");
}


- (void)spunk7649
{
	NSLog(@"perpetuate7650");
}


- (void)ahead7651
{
	NSLog(@"telephone7652");
}


- (void)alabaster7653
{
	NSLog(@"arroyo7654");
}


- (void)pecan7655
{
	NSLog(@"uniform7656");
}


- (void)decide7657
{
	NSLog(@"abstracted7658");
}


- (void)fussy7659
{
	NSLog(@"overestimate7660");
}


- (void)language7661
{
	NSLog(@"syllogism7662");
}


- (void)recline7663
{
	NSLog(@"cabbage7664");
}


- (void)dawdle7665
{
	NSLog(@"commencement7666");
}


- (void)tonight7667
{
	NSLog(@"gerontology7668");
}


- (void)collective7669
{
	NSLog(@"antitoxic7670");
}


- (void)deportation7671
{
	NSLog(@"propinquity7672");
}


- (void)pronounced7673
{
	NSLog(@"remainder7674");
}


- (void)student7675
{
	NSLog(@"actual7676");
}


- (void)substantiate7677
{
	NSLog(@"alight7678");
}


- (void)halve7679
{
	NSLog(@"wording7680");
}


- (void)finalize7681
{
	NSLog(@"entrance7682");
}


- (void)thresh7683
{
	NSLog(@"meticulous7684");
}


- (void)misunderstand7685
{
	NSLog(@"numinous7686");
}


- (void)withdrawal7687
{
	NSLog(@"snarl7688");
}


- (void)freeze7689
{
	NSLog(@"confusion7690");
}


- (void)malpractice7691
{
	NSLog(@"chimney7692");
}


- (void)exact7693
{
	NSLog(@"pitfall7694");
}


- (void)disbarment7695
{
	NSLog(@"frank7696");
}


- (void)fillet7697
{
	NSLog(@"vicissitudinous7698");
}


- (void)ostentatious7699
{
	NSLog(@"dependable7700");
}


- (void)dilapidate7701
{
	NSLog(@"jumble7702");
}


- (void)underhanded7703
{
	NSLog(@"feminine7704");
}


- (void)noise7705
{
	NSLog(@"outlaw7706");
}


- (void)chivalrous7707
{
	NSLog(@"vernacular7708");
}


- (void)reparation7709
{
	NSLog(@"waste7710");
}


- (void)dilatory7711
{
	NSLog(@"illness7712");
}


- (void)immoral7713
{
	NSLog(@"belligerence7714");
}


- (void)infinitive7715
{
	NSLog(@"trilogy7716");
}


- (void)frankly7717
{
	NSLog(@"hypodermic7718");
}


- (void)nectar7719
{
	NSLog(@"further7720");
}


- (void)etching7721
{
	NSLog(@"payable7722");
}


- (void)abrasive7723
{
	NSLog(@"sequential7724");
}


- (void)hoary7725
{
	NSLog(@"coercion7726");
}


- (void)arrhythmic7727
{
	NSLog(@"triumph7728");
}


- (void)perjure7729
{
	NSLog(@"foible7730");
}


- (void)principle7731
{
	NSLog(@"stupidity7732");
}


- (void)fastidious7733
{
	NSLog(@"hereof7734");
}


- (void)unimpressive7735
{
	NSLog(@"maudlin7736");
}


- (void)enhance7737
{
	NSLog(@"variance7738");
}


- (void)spruce7739
{
	NSLog(@"domination7740");
}


- (void)transient7741
{
	NSLog(@"covet7742");
}


- (void)scandalous7743
{
	NSLog(@"decoy7744");
}


- (void)arduous7745
{
	NSLog(@"proclivity7746");
}


- (void)waspish7747
{
	NSLog(@"mountainous7748");
}


- (void)sheen7749
{
	NSLog(@"unchangeable7750");
}


- (void)purport7751
{
	NSLog(@"apposite7752");
}


- (void)hoarse7753
{
	NSLog(@"bruit7754");
}


- (void)promenade7755
{
	NSLog(@"quail7756");
}


- (void)excavate7757
{
	NSLog(@"connect7758");
}


- (void)unfortunately7759
{
	NSLog(@"hosepipe7760");
}


- (void)charitable7761
{
	NSLog(@"domesticate7762");
}


- (void)rapport7763
{
	NSLog(@"seine7764");
}


- (void)peptic7765
{
	NSLog(@"previous7766");
}


- (void)Byzantine7767
{
	NSLog(@"taint7768");
}


- (void)gargantuan7769
{
	NSLog(@"fraternal7770");
}


- (void)compassion7771
{
	NSLog(@"fungicide7772");
}


- (void)obscure7773
{
	NSLog(@"spiritual7774");
}


- (void)glitch7775
{
	NSLog(@"brassy7776");
}


- (void)cleanse7777
{
	NSLog(@"apply7778");
}


- (void)noticeable7779
{
	NSLog(@"accurately7780");
}


- (void)surveillance7781
{
	NSLog(@"prairie7782");
}


- (void)stasis7783
{
	NSLog(@"enshrine7784");
}


- (void)eccentricity7785
{
	NSLog(@"conqueror7786");
}


- (void)calcify7787
{
	NSLog(@"snowstorm7788");
}


- (void)subsidiary7789
{
	NSLog(@"twinkle7790");
}


- (void)representative7791
{
	NSLog(@"judiciousness7792");
}


- (void)saturated7793
{
	NSLog(@"capital7794");
}


- (void)erupt7795
{
	NSLog(@"devil7796");
}


- (void)modest7797
{
	NSLog(@"recorder7798");
}


- (void)frame7799
{
	NSLog(@"jejune7800");
}


- (void)lament7801
{
	NSLog(@"vision7802");
}


- (void)satisfaction7803
{
	NSLog(@"hospitable7804");
}


- (void)distill7805
{
	NSLog(@"orthodox7806");
}


- (void)clarification7807
{
	NSLog(@"harbor7808");
}


- (void)deracinate7809
{
	NSLog(@"restitution7810");
}


- (void)remote7811
{
	NSLog(@"suffice7812");
}


- (void)trawl7813
{
	NSLog(@"throne7814");
}


- (void)supplement7815
{
	NSLog(@"thesis7816");
}


- (void)handicapped7817
{
	NSLog(@"freight7818");
}


- (void)broken7819
{
	NSLog(@"prove7820");
}


- (void)corrosive7821
{
	NSLog(@"harpoon7822");
}


- (void)subjunctive7823
{
	NSLog(@"portable7824");
}


- (void)poetry7825
{
	NSLog(@"favor7826");
}


- (void)lascivious7827
{
	NSLog(@"coloration7828");
}


- (void)decipher7829
{
	NSLog(@"improper7830");
}


- (void)rudiments7831
{
	NSLog(@"psychology7832");
}


- (void)contort7833
{
	NSLog(@"unlucky7834");
}


- (void)equity7835
{
	NSLog(@"desolate7836");
}


- (void)cardiologist7837
{
	NSLog(@"affix7838");
}


- (void)abstracted7839
{
	NSLog(@"sedition7840");
}


- (void)bedraggled7841
{
	NSLog(@"witty7842");
}


- (void)censorship7843
{
	NSLog(@"circumstance7844");
}


- (void)mercenary7845
{
	NSLog(@"football7846");
}


- (void)stickler7847
{
	NSLog(@"disadvantage7848");
}


- (void)menial7849
{
	NSLog(@"entrust7850");
}


- (void)enroll7851
{
	NSLog(@"audacity7852");
}


- (void)behold7853
{
	NSLog(@"electrical7854");
}


- (void)recognize7855
{
	NSLog(@"unwilling7856");
}


- (void)judge7857
{
	NSLog(@"idiom7858");
}


- (void)blasphemy7859
{
	NSLog(@"authoritative7860");
}


- (void)suppression7861
{
	NSLog(@"breakfast7862");
}


- (void)poniard7863
{
	NSLog(@"copious7864");
}


- (void)congress7865
{
	NSLog(@"infiltrate7866");
}


- (void)porch7867
{
	NSLog(@"cajole7868");
}


- (void)nurture7869
{
	NSLog(@"pioneering7870");
}


- (void)salvage7871
{
	NSLog(@"thrash7872");
}


- (void)nobody7873
{
	NSLog(@"didactic7874");
}


- (void)cavern7875
{
	NSLog(@"rheumatism7876");
}


- (void)Malaysia7877
{
	NSLog(@"esophagus7878");
}


- (void)potshot7879
{
	NSLog(@"motorcar7880");
}


- (void)celebration7881
{
	NSLog(@"interruption7882");
}


- (void)pointless7883
{
	NSLog(@"bluster7884");
}


- (void)reckless7885
{
	NSLog(@"verbal7886");
}


- (void)continual7887
{
	NSLog(@"foggy7888");
}


- (void)tainted7889
{
	NSLog(@"gorgeous7890");
}


- (void)congregate7891
{
	NSLog(@"gusto7892");
}


- (void)housework7893
{
	NSLog(@"xerox7894");
}


- (void)grand7895
{
	NSLog(@"obsession7896");
}


- (void)adherent7897
{
	NSLog(@"tempestuous7898");
}


- (void)disinclined7899
{
	NSLog(@"metamorphosis7900");
}


- (void)glitch7901
{
	NSLog(@"super7902");
}


- (void)endeavor7903
{
	NSLog(@"administrative7904");
}


- (void)highlight7905
{
	NSLog(@"gently7906");
}


- (void)solvent7907
{
	NSLog(@"batch7908");
}


- (void)osseous7909
{
	NSLog(@"despoil7910");
}


- (void)marrow7911
{
	NSLog(@"proper7912");
}


- (void)homework7913
{
	NSLog(@"dizzy7914");
}


- (void)marionette7915
{
	NSLog(@"choir7916");
}


- (void)lineal7917
{
	NSLog(@"unlawful7918");
}


- (void)affront7919
{
	NSLog(@"export7920");
}


- (void)monologue7921
{
	NSLog(@"reverse7922");
}


- (void)crook7923
{
	NSLog(@"sparrow7924");
}


- (void)wince7925
{
	NSLog(@"futile7926");
}


- (void)moratorium7927
{
	NSLog(@"belated7928");
}


- (void)reverie7929
{
	NSLog(@"scoop7930");
}


- (void)dedicate7931
{
	NSLog(@"falsehood7932");
}


- (void)smash7933
{
	NSLog(@"delightful7934");
}


- (void)Mexican7935
{
	NSLog(@"design7936");
}


- (void)prefix7937
{
	NSLog(@"provision7938");
}


- (void)demand7939
{
	NSLog(@"solecism7940");
}


- (void)affirmative7941
{
	NSLog(@"intermingle7942");
}


- (void)subtract7943
{
	NSLog(@"repetition7944");
}


- (void)corporeal7945
{
	NSLog(@"complement7946");
}


- (void)sacrifice7947
{
	NSLog(@"inroad7948");
}


- (void)encyclopedia7949
{
	NSLog(@"pincers7950");
}


- (void)fanfare7951
{
	NSLog(@"acquaintance7952");
}


- (void)gardener7953
{
	NSLog(@"villa7954");
}


- (void)discretionary7955
{
	NSLog(@"barometer7956");
}


- (void)entity7957
{
	NSLog(@"fresco7958");
}


- (void)harbinger7959
{
	NSLog(@"intestate7960");
}


- (void)intuition7961
{
	NSLog(@"tasty7962");
}


- (void)muzzy7963
{
	NSLog(@"liberation7964");
}


- (void)mighty7965
{
	NSLog(@"dissident7966");
}


- (void)collide7967
{
	NSLog(@"class7968");
}


- (void)intertwine7969
{
	NSLog(@"arithmetic7970");
}


- (void)fiddle7971
{
	NSLog(@"senator7972");
}


- (void)journey7973
{
	NSLog(@"pretension7974");
}

@end

#endif
