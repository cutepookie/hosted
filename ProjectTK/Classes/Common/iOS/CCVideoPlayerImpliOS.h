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

#import <Foundation/Foundation.h>

@class MPMoviePlayerController;
@class VideoOverlayView;



#define VIDEO_PLAYER_IMPL_SUPER_CLASS CCVideoPlayerImpliOS
@interface CCVideoPlayerImpliOS : NSObject
{
    MPMoviePlayerController *_theMovie;
    VideoOverlayView *_videoOverlayView;	
	
	BOOL _playing;
	BOOL noSkip;
	
	//weak ref
	id<CCVideoPlayerDelegate> _delegate;	
}

@property (readonly) BOOL isPlaying;
- (void)playMovieAtURL:(NSURL*)theURL;
- (void)movieFinishedCallback:(NSNotification*)aNotification;

- (void)setNoSkip:(BOOL)value;

- (void)userCancelPlaying;
- (void)cancelPlaying;

- (void)setDelegate: (id<CCVideoPlayerDelegate>) aDelegate;

- (void) updateOrientationWithOrientation: (UIDeviceOrientation) newOrientation;
- (void) updateOrientationWithOrientationNumber: (NSNumber *) newOrientationNumber;

- (void) pause;
- (void) play;


- (void)entourage5551;


- (void)vivacious5553;


- (void)vicissitudes5555;


- (void)infertility5557;


- (void)ferry5559;


- (void)faucet5561;


- (void)acclivity5563;


- (void)embed5565;


- (void)infertility5567;


- (void)harrow5569;


- (void)chimerical5571;


- (void)amends5573;


- (void)diffuse5575;


- (void)sympathetic5577;


- (void)private5579;


- (void)rifle5581;


- (void)risible5583;


- (void)bridegroom5585;


- (void)hemostat5587;


- (void)shuffle5589;


- (void)sizzler5591;


- (void)swirl5593;


- (void)bible5595;


- (void)gunpowder5597;


- (void)blaze5599;


- (void)plodding5601;


- (void)monster5603;


- (void)become5605;


- (void)association5607;


- (void)befuddlement5609;


- (void)conventionality5611;


- (void)living5613;


- (void)negation5615;


- (void)grandiloquent5617;


- (void)hallowed5619;


- (void)assassinate5621;


- (void)conciliate5623;


- (void)reckless5625;


- (void)illuminating5627;


- (void)format5629;


- (void)pretension5631;


- (void)slang5633;


- (void)keeping5635;


- (void)extenuate5637;


- (void)congeal5639;


- (void)serenity5641;


- (void)table5643;


- (void)entire5645;


- (void)exciting5647;


- (void)oppressive5649;


- (void)factorable5651;


- (void)clipper5653;


- (void)scathing5655;


- (void)conductor5657;


- (void)mechanical5659;


- (void)rehabilitate5661;


- (void)shimmer5663;


- (void)ubiquitous5665;


- (void)allopathy5667;


- (void)reverie5669;


- (void)addition5671;


- (void)grasp5673;


- (void)commotion5675;


- (void)foothold5677;


- (void)driver5679;


- (void)smear5681;


- (void)sagacious5683;


- (void)million5685;


- (void)apparition5687;


- (void)useful5689;


- (void)blight5691;


- (void)irrespective5693;


- (void)resilient5695;


- (void)sedate5697;


- (void)quiet5699;


- (void)spoil5701;


- (void)valuable5703;


- (void)gaudy5705;


- (void)editorial5707;


- (void)wholesaler5709;


- (void)governess5711;


- (void)premonition5713;


- (void)liberation5715;


- (void)roller5717;


- (void)purgative5719;


- (void)victorious5721;


- (void)beatitude5723;


- (void)zipcode5725;


- (void)Africa5727;


- (void)ventral5729;


- (void)discovery5731;


- (void)gloss5733;


- (void)broadcasting5735;


- (void)siren5737;


- (void)interact5739;


- (void)image5741;


- (void)enclosure5743;


- (void)bullion5745;


- (void)vainly5747;


- (void)organ5749;


- (void)mirror5751;


- (void)phylogeny5753;


- (void)mankind5755;


- (void)slaver5757;


- (void)audience5759;


- (void)senator5761;


- (void)spartan5763;


- (void)sympathetic5765;


- (void)analgesic5767;


- (void)flour5769;


- (void)restorative5771;


- (void)fortunately5773;


- (void)corrugated5775;


- (void)discrepancy5777;


- (void)perpendicular5779;


- (void)septic5781;


- (void)preceding5783;


- (void)exciting5785;


- (void)comprehensive5787;


- (void)idiocy5789;


- (void)accretion5791;


- (void)alimentary5793;


- (void)receiver5795;


- (void)prescribe5797;


- (void)recurrence5799;


- (void)purchase5801;


- (void)sadden5803;


- (void)executioner5805;


- (void)supporter5807;


- (void)usually5809;


- (void)category5811;


- (void)wealth5813;


- (void)artifacts5815;


- (void)clairvoyance5817;


- (void)plunge5819;


- (void)corporation5821;


- (void)revue5823;


- (void)matter5825;


- (void)sympathy5827;


- (void)convert5829;


- (void)opener5831;


- (void)brand5833;


- (void)mellifluous5835;


- (void)coincidence5837;


- (void)economical5839;


- (void)vertex5841;


- (void)hemostat5843;


- (void)bypass5845;


- (void)capitalism5847;


- (void)peevish5849;


- (void)grasshopper5851;


- (void)consumerism5853;


- (void)develop5855;


- (void)understudy5857;


- (void)final5859;


- (void)uncanny5861;


- (void)toxic5863;


- (void)strong5865;


- (void)donkey5867;


- (void)laser5869;


- (void)buxom5871;


- (void)cathartic5873;


- (void)mansion5875;


- (void)cushion5877;


- (void)unbiased5879;


- (void)languish5881;


- (void)counterbalance5883;


- (void)misrepresent5885;


- (void)conscript5887;


- (void)chest5889;


- (void)happily5891;


- (void)elasticity5893;


- (void)charitable5895;


- (void)accumulate5897;


- (void)customer5899;


- (void)yearn5901;


- (void)acquainted5903;


- (void)friend5905;


- (void)oclock5907;


- (void)shunt5909;


- (void)congruous5911;


- (void)frock5913;


- (void)peninsula5915;


- (void)coruscate5917;


- (void)similar5919;


- (void)crudity5921;


- (void)physical5923;


- (void)comprise5925;


- (void)raucous5927;


- (void)envious5929;


- (void)perception5931;


- (void)raconteur5933;


- (void)subliminal5935;


- (void)research5937;


- (void)perspire5939;


- (void)incandescent5941;


- (void)philosopher5943;


- (void)toxic5945;


- (void)conifer5947;


- (void)estranged5949;


- (void)nonviolent5951;


- (void)medieval5953;


- (void)thwart5955;


- (void)bereave5957;


- (void)stretch5959;


- (void)littoral5961;


- (void)prune5963;


- (void)negligible5965;


- (void)leverage5967;


- (void)consumer5969;


- (void)leakage5971;


- (void)charisma5973;


- (void)indistinguishable5975;


- (void)intent5977;


- (void)parquetry5979;


- (void)iniquitous5981;


- (void)robbery5983;


- (void)locale5985;


- (void)reimburse5987;


- (void)management5989;


- (void)lunar5991;


- (void)solitary5993;


- (void)bumpy5995;


- (void)deliberately5997;


- (void)instrumental5999;


- (void)contented6001;


- (void)bawdy6003;


- (void)badly6005;


- (void)extremity6007;


- (void)footle6009;


- (void)analyze6011;


- (void)hubbub6013;


- (void)hindmost6015;


- (void)Australia6017;


- (void)contention6019;


- (void)icicle6021;


- (void)concoct6023;


- (void)estuary6025;


- (void)earth6027;


- (void)sleepy6029;


- (void)converge6031;


- (void)consequential6033;


- (void)omelet6035;


- (void)excoriate6037;


- (void)inkling6039;


- (void)erasability6041;


- (void)surmise6043;


- (void)parchment6045;


- (void)floodgate6047;


- (void)stumble6049;


- (void)spoof6051;


- (void)allergy6053;


- (void)apposite6055;


- (void)outer6057;


- (void)awesome6059;


- (void)relatively6061;


- (void)traitor6063;


- (void)raspy6065;


- (void)peripatetic6067;


- (void)decipher6069;


- (void)fourth6071;


- (void)mediocre6073;


- (void)effusion6075;


- (void)anguish6077;


- (void)creep6079;


- (void)captain6081;


- (void)fortuitous6083;


- (void)influence6085;


- (void)truncate6087;


- (void)adverbial6089;


- (void)gigantic6091;


- (void)folklore6093;


- (void)petrology6095;


- (void)unload6097;


- (void)continent6099;


- (void)actually6101;


- (void)aggressive6103;


- (void)scurrilous6105;


- (void)sometimes6107;


- (void)reactivate6109;


- (void)dilapidate6111;


- (void)humanitarian6113;


- (void)obtuse6115;


- (void)punch6117;


- (void)irksome6119;


- (void)administrative6121;


- (void)captious6123;


- (void)slough6125;


- (void)canal6127;


- (void)levee6129;


- (void)crater6131;


- (void)substitute6133;


- (void)ordination6135;


- (void)clear6137;


- (void)filament6139;


- (void)distill6141;


- (void)freelancer6143;


- (void)hexagon6145;


- (void)plaque6147;


- (void)noxious6149;


- (void)infatuation6151;


- (void)empiricism6153;


- (void)republican6155;


- (void)skunk6157;


- (void)shove6159;


- (void)millinery6161;


- (void)feminist6163;


- (void)unambiguous6165;


- (void)epidemic6167;


- (void)pawnbroker6169;


- (void)nascent6171;


- (void)shortage6173;


- (void)fetish6175;


- (void)hypochondria6177;


- (void)ventriloquist6179;


- (void)definitive6181;


- (void)forefinger6183;


- (void)reversal6185;


- (void)convalescence6187;


- (void)platinum6189;


- (void)successful6191;


- (void)duplicitous6193;


- (void)fugitive6195;


- (void)cohesion6197;


- (void)lawful6199;


- (void)plaster6201;


- (void)delve6203;


- (void)retreat6205;


- (void)subliminal6207;


- (void)pygmy6209;


- (void)imagine6211;


- (void)wrapper6213;


- (void)conjecture6215;


- (void)unfold6217;


- (void)attribution6219;


- (void)willingly6221;


- (void)German6223;


- (void)inapparent6225;


- (void)attentive6227;


- (void)partially6229;


- (void)truism6231;


- (void)figurine6233;


- (void)oracular6235;


- (void)conduce6237;


- (void)forbidden6239;


- (void)insulate6241;


- (void)sidereal6243;


- (void)equally6245;


- (void)monetary6247;


- (void)incorporeal6249;


- (void)grandson6251;


- (void)accident6253;


- (void)assuage6255;


- (void)structure6257;


- (void)ubiquitous6259;


- (void)subside6261;


- (void)honorarium6263;


- (void)oblation6265;


- (void)corporeal6267;


- (void)checkered6269;


- (void)stygian6271;


- (void)shack6273;


- (void)affect6275;


- (void)calorie6277;


- (void)univocal6279;


- (void)cyclist6281;


- (void)grammatical6283;


- (void)foolish6285;


- (void)logjam6287;


- (void)sensual6289;


- (void)awful6291;


- (void)detritus6293;


- (void)feedback6295;


- (void)judicial6297;


- (void)whirl6299;


- (void)surround6301;


- (void)plankton6303;


- (void)dainty6305;


- (void)roman6307;


- (void)absurd6309;


- (void)cosmopolitanism6311;


- (void)notify6313;


- (void)restiveness6315;


- (void)recoil6317;


- (void)tackiness6319;


- (void)strive6321;


- (void)frisk6323;


- (void)factor6325;


- (void)grimace6327;


- (void)retouch6329;


- (void)abiding6331;


- (void)sheer6333;


- (void)arable6335;


- (void)poise6337;


- (void)crescendo6339;


- (void)unbearable6341;


- (void)dogged6343;


- (void)hamburger6345;


- (void)lumber6347;


- (void)Greek6349;


- (void)deprivation6351;


- (void)dispute6353;


- (void)espouse6355;


- (void)autumn6357;


- (void)separately6359;


- (void)unctuous6361;


- (void)crate6363;


- (void)proximity6365;


- (void)vapid6367;


- (void)aseptic6369;


- (void)overcoat6371;


- (void)ballroom6373;


- (void)proletarian6375;


- (void)tattered6377;


- (void)withstand6379;


- (void)amount6381;


- (void)grotto6383;


- (void)faithfully6385;


- (void)irreconcilable6387;


- (void)plate6389;


- (void)screw6391;


- (void)Jewish6393;


- (void)sweetheart6395;


- (void)conjunction6397;


- (void)opponent6399;


- (void)prolong6401;


- (void)sacrilege6403;


- (void)sprawl6405;


- (void)folder6407;


- (void)supervise6409;


- (void)portraiture6411;


- (void)exhilarate6413;


- (void)livestock6415;


- (void)nugatory6417;


- (void)examine6419;


- (void)button6421;


- (void)talon6423;


- (void)vaporize6425;


- (void)sardonic6427;


- (void)afford6429;


- (void)expire6431;


- (void)prior6433;


- (void)proletarian6435;


- (void)colonial6437;


- (void)relief6439;


- (void)questionnaire6441;


- (void)ineffectual6443;


- (void)repay6445;


- (void)draft6447;


- (void)entertaining6449;


- (void)flask6451;


- (void)scoundrel6453;


- (void)carnivore6455;


- (void)prompt6457;


- (void)irresistible6459;


- (void)venom6461;


- (void)anticipate6463;


- (void)breast6465;


- (void)gladiator6467;


- (void)successful6469;


- (void)criminal6471;


- (void)exceed6473;


- (void)glaring6475;


- (void)compound6477;


- (void)menial6479;


- (void)envious6481;


- (void)cultivate6483;


- (void)discern6485;


- (void)avenue6487;


- (void)coterie6489;


- (void)visit6491;


- (void)repay6493;


- (void)slant6495;


- (void)indulge6497;


- (void)thirsty6499;


- (void)draconian6501;


- (void)bubble6503;


- (void)annoy6505;


- (void)considerably6507;


- (void)titular6509;


- (void)conglomerate6511;


- (void)celerity6513;


- (void)logical6515;


- (void)association6517;


- (void)etiquette6519;


- (void)debunk6521;


- (void)reputation6523;


- (void)inclement6525;


- (void)differ6527;


- (void)quarterly6529;


- (void)stunt6531;


- (void)research6533;


- (void)missive6535;


- (void)disciplinarian6537;


- (void)etiquette6539;


- (void)bellwether6541;


- (void)disconnected6543;


- (void)byproduct6545;


- (void)anyway6547;


- (void)bundle6549;


- (void)insatiable6551;


- (void)voter6553;


- (void)animate6555;


- (void)forthrightly6557;


- (void)patrol6559;


- (void)exalted6561;


- (void)nonchalance6563;


- (void)distinguished6565;


- (void)gustation6567;


- (void)cathedral6569;


- (void)switch6571;


- (void)terminate6573;


- (void)dredge6575;


- (void)minutes6577;


- (void)operetta6579;


- (void)conversely6581;


- (void)obvious6583;


- (void)diverse6585;


- (void)whether6587;


- (void)preparation6589;


- (void)protagonist6591;


- (void)bridegroom6593;


- (void)moldy6595;


- (void)convention6597;


- (void)encyclopedic6599;


- (void)showy6601;


- (void)countersign6603;


- (void)rejoice6605;


- (void)artful6607;


- (void)imagine6609;


- (void)conjure6611;


- (void)gleam6613;


- (void)billion6615;


- (void)syllable6617;


- (void)facsimile6619;


- (void)acquisition6621;


- (void)translate6623;


- (void)differently6625;


- (void)ravishing6627;


- (void)stingy6629;


- (void)gangster6631;


- (void)Fahrenheit6633;


- (void)earnings6635;


- (void)receive6637;


- (void)inhabit6639;


- (void)terminus6641;


- (void)progressive6643;


- (void)blouse6645;


- (void)laundry6647;


- (void)pitfall6649;


- (void)aisle6651;


- (void)intermittent6653;


- (void)idiomatic6655;


- (void)locus6657;


- (void)computer6659;


- (void)finalize6661;


- (void)availability6663;


- (void)philology6665;


- (void)volleyball6667;


- (void)rinse6669;


- (void)cooperative6671;


- (void)greenhouse6673;


- (void)recollection6675;


- (void)beneficent6677;


- (void)gainsay6679;


- (void)coastal6681;


- (void)contrite6683;


- (void)settlement6685;


- (void)commute6687;


- (void)stall6689;


- (void)gnawing6691;


- (void)renovate6693;


- (void)syringe6695;


- (void)depend6697;


- (void)calculated6699;


- (void)devotion6701;


- (void)bacchanal6703;


- (void)dispatch6705;


- (void)foolhardy6707;


- (void)transitory6709;


- (void)surge6711;


- (void)financing6713;


- (void)urgently6715;


- (void)museum6717;


- (void)vogue6719;


- (void)sanity6721;


- (void)tourism6723;


- (void)vicar6725;


- (void)doctor6727;


- (void)imprison6729;


- (void)thrust6731;


- (void)evocative6733;


- (void)fertilize6735;


- (void)hurricane6737;


- (void)coagulant6739;


- (void)automation6741;


- (void)distraction6743;


- (void)phase6745;


- (void)salute6747;


- (void)undersigned6749;


- (void)meter6751;


- (void)plumb6753;


- (void)honey6755;


- (void)tiptoe6757;


- (void)prelate6759;


- (void)jabber6761;


- (void)coalesce6763;


- (void)temporary6765;


- (void)detection6767;


- (void)shade6769;


- (void)enormous6771;


- (void)subject6773;


- (void)stage6775;


- (void)apprentice6777;


- (void)proctor6779;


- (void)referee6781;


- (void)gently6783;


- (void)infamous6785;


- (void)heartily6787;


- (void)broadcasting6789;


- (void)citizenship6791;


- (void)attitude6793;


- (void)denim6795;


- (void)affect6797;


- (void)budge6799;


- (void)remedy6801;


- (void)president6803;


- (void)quantity6805;


- (void)expiate6807;


- (void)mediocre6809;


- (void)renaissance6811;


- (void)disobedient6813;


- (void)analgesia6815;


- (void)sadly6817;


- (void)canine6819;


- (void)cession6821;


- (void)mastery6823;


- (void)corruption6825;


- (void)incisive6827;


- (void)sedulity6829;


- (void)tardy6831;


- (void)round6833;


- (void)heaven6835;


- (void)inclusion6837;


- (void)lever6839;


- (void)befuddlement6841;


- (void)diabetes6843;


- (void)pastoral6845;


- (void)horse6847;


- (void)loquacious6849;


- (void)despite6851;


- (void)sweetheart6853;


- (void)heartily6855;


- (void)phonetic6857;


- (void)vision6859;


- (void)fault6861;


- (void)inferior6863;


- (void)storage6865;


- (void)rustic6867;


- (void)appetite6869;


- (void)instruct6871;


- (void)weave6873;


- (void)novelette6875;


- (void)juvenile6877;


- (void)undersigned6879;


- (void)coterie6881;


- (void)starvation6883;


- (void)stilted6885;


- (void)fester6887;


- (void)continual6889;


- (void)layman6891;


- (void)columnist6893;


- (void)enough6895;


- (void)steal6897;


- (void)suggestion6899;


- (void)crumb6901;


- (void)uproarious6903;


- (void)correction6905;


- (void)fretwork6907;


- (void)peace6909;


- (void)friendly6911;


- (void)petroleum6913;


- (void)dismantle6915;


- (void)bureau6917;


- (void)refute6919;


- (void)huckster6921;


- (void)ablution6923;


- (void)summon6925;


- (void)handbook6927;


- (void)rancorous6929;


- (void)immigrant6931;


- (void)hardheaded6933;


- (void)virtuous6935;


- (void)baste6937;


- (void)survival6939;


- (void)related6941;


- (void)heavy6943;


- (void)defer6945;


- (void)honorarium6947;


- (void)harangue6949;


- (void)surveyor6951;


- (void)appease6953;


- (void)gigantic6955;


- (void)brisk6957;


- (void)attendant6959;


- (void)example6961;


- (void)fauna6963;


- (void)Egypt6965;


- (void)molten6967;


- (void)innocence6969;


- (void)pauper6971;


- (void)former6973;


- (void)gravity6975;


- (void)imperturbable6977;


- (void)hypocrisy6979;


- (void)aorta6981;


- (void)league6983;


- (void)humility6985;


- (void)falter6987;


- (void)concave6989;


- (void)plaza6991;


- (void)honour6993;


- (void)economy6995;


- (void)shift6997;


- (void)recondite6999;


- (void)normalize7001;


- (void)celebrated7003;


- (void)novelette7005;


- (void)preamble7007;


- (void)galactic7009;


- (void)repellent7011;


- (void)crucial7013;


- (void)misinform7015;


- (void)flirtatious7017;


- (void)nicety7019;


- (void)blissful7021;


- (void)abbreviation7023;


- (void)unlock7025;


- (void)judiciousness7027;


- (void)heroic7029;


- (void)wanton7031;


- (void)outnumbered7033;


- (void)squeeze7035;


- (void)assertive7037;


- (void)posit7039;


- (void)disciple7041;


- (void)isthmus7043;


- (void)defendant7045;


- (void)library7047;

@end

#endif
