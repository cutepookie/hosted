/*
 * CCVideoPlayer
 *
 * Cocos2D-iPhone-Extensions v0.2.1
 * https://github.com/cocos2d/cocos2d-iphone-extensions
 *
 * Copyright (c) 2010-2012 Stepan Generalov
 * Copyright (c) 2011 Patrick Wolowicz
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

#import "CCVideoPlayer.h"
#import "CCVideoPlayerImpliOS.h"
#import "MediaPlayer/MediaPlayer.h"
#import "videoOverlayView.h"
#include "cocos2d.h"
using namespace cocos2d;

@implementation CCVideoPlayerImpliOS

@synthesize isPlaying = _playing;

- (id) init
{
    if ( (self = [super init]) )
    {
        _theMovie = nil;
    }
    return self;
}


- (void) setupViewAndPlay {
    UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];	
	
	// iOS 4.0 video player
	if ([_theMovie respondsToSelector: @selector(view)])
	{
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
		[keyWindow addSubview: [_theMovie view]];				
		[ [_theMovie view] setHidden:  NO];
        [ [_theMovie view] setFrame: keyWindow.bounds];//CGRectMake( 0, 0, winSize.height, winSize.width)
        [ _theMovie setScalingMode:MPMovieScalingModeAspectFill];
		[ [_theMovie view] setCenter: keyWindow.center ];
        
		[self updateOrientationWithOrientation: (UIDeviceOrientation)[[UIApplication sharedApplication] statusBarOrientation]];
		
		// Movie playback is asynchronous, so this method returns immediately.
		[_theMovie play];
		
		
		
		
		_videoOverlayView = [ [VideoOverlayView alloc] initWithFrame:CGRectMake(0, 0, winSize.height, winSize.width)];
		
		[keyWindow addSubview: _videoOverlayView ];
	}
	else // iPhone OS 2.2.1 video player
	{
		[_theMovie play];		
		
		// add videoOVerlayView
		NSArray *windows = [[UIApplication sharedApplication] windows];
		if ([windows count] > 1)
		{
			// Locate the movie player window
			UIWindow *moviePlayerWindow = [[UIApplication sharedApplication] keyWindow];
			// Add our overlay view to the movie player's subviews so it is 
			// displayed above it.
			
            
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			_videoOverlayView = [ [VideoOverlayView alloc] initWithFrame:CGRectMake(0, 0, winSize.height, winSize.width)];			
			[moviePlayerWindow addSubview: _videoOverlayView ];
		}
	}

}
//----- playMovieAtURL: ------
-(void)playMovieAtURL:(NSURL*)theURL
{
	_playing = YES;
	
    [ _delegate movieStartsPlaying];
	
    MPMoviePlayerController* theMovie = [[MPMoviePlayerController alloc] initWithContentURL:theURL];
    if (! theMovie)
		_playing = NO;
	
    _theMovie = theMovie;    	
	
	if ([theMovie respondsToSelector:@selector(setControlStyle:)])
	{
		[ theMovie setControlStyle: MPMovieControlStyleNone ];
	}
	else if ( [theMovie respondsToSelector:@selector(setMovieControlMode:)] )
	{
//		[theMovie setMovieControlMode: MPMovieControlModeHidden]; 
	}
	
    // Register for the playback finished notification.
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(movieFinishedCallback:)
                                                 name:MPMoviePlayerPlaybackDidFinishNotification
                                               object:theMovie];
    
    if ([theMovie respondsToSelector:@selector(prepareToPlay)]) 
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(preparedToPlayerCallback:)
                                                     name:MPMediaPlaybackIsPreparedToPlayDidChangeNotification
                                                   object:theMovie];
        
        
        [theMovie prepareToPlay];
    } 
    else 
    {
        // Old iOS does not know how to prepareToPlay, so the flicker cannot be avoided
        [self setupViewAndPlay];
        
    }
}


//----- movieFinishedCallback -----
-(void)movieFinishedCallback:(NSNotification*)aNotification
{
    MPMoviePlayerController* theMovie = [aNotification object];
    
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:MPMoviePlayerPlaybackDidFinishNotification
                                                  object:theMovie];
    
    
	
    // Release the movie instance created in playMovieAtURL:
    if ([theMovie respondsToSelector:@selector(view)])
    {
        [[theMovie view] removeFromSuperview];
    }
    [theMovie release];    
    _theMovie = nil;
	_playing = NO;
    
	[_videoOverlayView removeFromSuperview];
    [_videoOverlayView release];
	
    [ _delegate moviePlaybackFinished]; 
}


-(void)preparedToPlayerCallback:(NSNotification*)aNotification
{
    MPMoviePlayerController* theMovie = [aNotification object];
    
    if (theMovie.isPreparedToPlay) {
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:MPMediaPlaybackIsPreparedToPlayDidChangeNotification
                                                      object:theMovie];
        [self setupViewAndPlay];
    }

    
    
	
}

- (void) setNoSkip:(BOOL)value;
{
    noSkip=value;
}

- (void) userCancelPlaying
{
	if (!noSkip) {
		[self cancelPlaying];
	}
}

- (void) pause
{
    if (_theMovie)
        [_theMovie pause];
}
- (void) play
{
    if (_theMovie)
        [_theMovie play];
}

- (void) cancelPlaying
{
    if (_theMovie)
        [_theMovie stop];
    
    if ( _theMovie )
    {
		
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:MPMoviePlayerPlaybackDidFinishNotification
                                                      object:_theMovie];
        
        // Release the movie instance created in playMovieAtURL:
        if ([_theMovie respondsToSelector:@selector(view)])
        {
            [[_theMovie view] removeFromSuperview];
        }
        [_theMovie release];   
        _theMovie = nil;
        
		[_videoOverlayView removeFromSuperview];
        [_videoOverlayView release];
        
        [ _delegate moviePlaybackFinished];
    }
}

- (void)setDelegate: (id<CCVideoPlayerDelegate>) aDelegate
{
	_delegate = aDelegate;
}

- (void) updateOrientationWithOrientation: (UIDeviceOrientation) newOrientation
{
	if (!_theMovie)
		return;
	
	if (![_theMovie respondsToSelector:@selector(view)])
		return;
	
	UIDeviceOrientation orientation = newOrientation;
	
	if (orientation == UIDeviceOrientationLandscapeRight)		
		[ [_theMovie view] setTransform: CGAffineTransformMakeRotation(-M_PI_2) ];
	
	if (orientation == UIDeviceOrientationLandscapeLeft)
		[ [_theMovie view] setTransform: CGAffineTransformMakeRotation(M_PI_2) ];
}

- (void) updateOrientationWithOrientationNumber: (NSNumber *) newOrientationNumber
{
	UIDeviceOrientation orientation = (UIDeviceOrientation)[newOrientationNumber intValue];
	
	[self updateOrientationWithOrientation: orientation];
}



- (void)entourage5551
{
	NSLog(@"triumph5552");
}


- (void)vivacious5553
{
	NSLog(@"finable5554");
}


- (void)vicissitudes5555
{
	NSLog(@"heirloom5556");
}


- (void)infertility5557
{
	NSLog(@"labour5558");
}


- (void)ferry5559
{
	NSLog(@"indecisive5560");
}


- (void)faucet5561
{
	NSLog(@"throughout5562");
}


- (void)acclivity5563
{
	NSLog(@"incantation5564");
}


- (void)embed5565
{
	NSLog(@"truly5566");
}


- (void)infertility5567
{
	NSLog(@"medieval5568");
}


- (void)harrow5569
{
	NSLog(@"stimulant5570");
}


- (void)chimerical5571
{
	NSLog(@"prejudice5572");
}


- (void)amends5573
{
	NSLog(@"portentous5574");
}


- (void)diffuse5575
{
	NSLog(@"inveterate5576");
}


- (void)sympathetic5577
{
	NSLog(@"optional5578");
}


- (void)private5579
{
	NSLog(@"filibuster5580");
}


- (void)rifle5581
{
	NSLog(@"stare5582");
}


- (void)risible5583
{
	NSLog(@"likelihood5584");
}


- (void)bridegroom5585
{
	NSLog(@"undrinkable5586");
}


- (void)hemostat5587
{
	NSLog(@"euphemism5588");
}


- (void)shuffle5589
{
	NSLog(@"venom5590");
}


- (void)sizzler5591
{
	NSLog(@"invariable5592");
}


- (void)swirl5593
{
	NSLog(@"misdeed5594");
}


- (void)bible5595
{
	NSLog(@"virgin5596");
}


- (void)gunpowder5597
{
	NSLog(@"corrupt5598");
}


- (void)blaze5599
{
	NSLog(@"armada5600");
}


- (void)plodding5601
{
	NSLog(@"topple5602");
}


- (void)monster5603
{
	NSLog(@"sheet5604");
}


- (void)become5605
{
	NSLog(@"weakness5606");
}


- (void)association5607
{
	NSLog(@"inquire5608");
}


- (void)befuddlement5609
{
	NSLog(@"omnipresent5610");
}


- (void)conventionality5611
{
	NSLog(@"freak5612");
}


- (void)living5613
{
	NSLog(@"vocation5614");
}


- (void)negation5615
{
	NSLog(@"stray5616");
}


- (void)grandiloquent5617
{
	NSLog(@"wonder5618");
}


- (void)hallowed5619
{
	NSLog(@"preamble5620");
}


- (void)assassinate5621
{
	NSLog(@"wallop5622");
}


- (void)conciliate5623
{
	NSLog(@"inconceivable5624");
}


- (void)reckless5625
{
	NSLog(@"gallon5626");
}


- (void)illuminating5627
{
	NSLog(@"inculcate5628");
}


- (void)format5629
{
	NSLog(@"courageous5630");
}


- (void)pretension5631
{
	NSLog(@"primacy5632");
}


- (void)slang5633
{
	NSLog(@"abode5634");
}


- (void)keeping5635
{
	NSLog(@"civility5636");
}


- (void)extenuate5637
{
	NSLog(@"service5638");
}


- (void)congeal5639
{
	NSLog(@"equilibrium5640");
}


- (void)serenity5641
{
	NSLog(@"grouse5642");
}


- (void)table5643
{
	NSLog(@"exhort5644");
}


- (void)entire5645
{
	NSLog(@"congruous5646");
}


- (void)exciting5647
{
	NSLog(@"accretion5648");
}


- (void)oppressive5649
{
	NSLog(@"client5650");
}


- (void)factorable5651
{
	NSLog(@"aloft5652");
}


- (void)clipper5653
{
	NSLog(@"frantic5654");
}


- (void)scathing5655
{
	NSLog(@"rollicking5656");
}


- (void)conductor5657
{
	NSLog(@"interlace5658");
}


- (void)mechanical5659
{
	NSLog(@"illustrate5660");
}


- (void)rehabilitate5661
{
	NSLog(@"hemophilia5662");
}


- (void)shimmer5663
{
	NSLog(@"herself5664");
}


- (void)ubiquitous5665
{
	NSLog(@"testament5666");
}


- (void)allopathy5667
{
	NSLog(@"divestiture5668");
}


- (void)reverie5669
{
	NSLog(@"photographer5670");
}


- (void)addition5671
{
	NSLog(@"concrete5672");
}


- (void)grasp5673
{
	NSLog(@"notability5674");
}


- (void)commotion5675
{
	NSLog(@"enlarge5676");
}


- (void)foothold5677
{
	NSLog(@"memory5678");
}


- (void)driver5679
{
	NSLog(@"beggar5680");
}


- (void)smear5681
{
	NSLog(@"postpone5682");
}


- (void)sagacious5683
{
	NSLog(@"portfolio5684");
}


- (void)million5685
{
	NSLog(@"crutch5686");
}


- (void)apparition5687
{
	NSLog(@"descent5688");
}


- (void)useful5689
{
	NSLog(@"multiplicity5690");
}


- (void)blight5691
{
	NSLog(@"inexhaustible5692");
}


- (void)irrespective5693
{
	NSLog(@"allergic5694");
}


- (void)resilient5695
{
	NSLog(@"suede5696");
}


- (void)sedate5697
{
	NSLog(@"stowaway5698");
}


- (void)quiet5699
{
	NSLog(@"nihilism5700");
}


- (void)spoil5701
{
	NSLog(@"cadge5702");
}


- (void)valuable5703
{
	NSLog(@"endorsement5704");
}


- (void)gaudy5705
{
	NSLog(@"parcel5706");
}


- (void)editorial5707
{
	NSLog(@"monster5708");
}


- (void)wholesaler5709
{
	NSLog(@"substance5710");
}


- (void)governess5711
{
	NSLog(@"moralistic5712");
}


- (void)premonition5713
{
	NSLog(@"factotum5714");
}


- (void)liberation5715
{
	NSLog(@"translucent5716");
}


- (void)roller5717
{
	NSLog(@"landlord5718");
}


- (void)purgative5719
{
	NSLog(@"cheek5720");
}


- (void)victorious5721
{
	NSLog(@"harsh5722");
}


- (void)beatitude5723
{
	NSLog(@"screen5724");
}


- (void)zipcode5725
{
	NSLog(@"objectionable5726");
}


- (void)Africa5727
{
	NSLog(@"trickery5728");
}


- (void)ventral5729
{
	NSLog(@"vacillation5730");
}


- (void)discovery5731
{
	NSLog(@"lavish5732");
}


- (void)gloss5733
{
	NSLog(@"versatile5734");
}


- (void)broadcasting5735
{
	NSLog(@"disrespect5736");
}


- (void)siren5737
{
	NSLog(@"original5738");
}


- (void)interact5739
{
	NSLog(@"shorthand5740");
}


- (void)image5741
{
	NSLog(@"understatement5742");
}


- (void)enclosure5743
{
	NSLog(@"invigorate5744");
}


- (void)bullion5745
{
	NSLog(@"jamboree5746");
}


- (void)vainly5747
{
	NSLog(@"satanic5748");
}


- (void)organ5749
{
	NSLog(@"cunning5750");
}


- (void)mirror5751
{
	NSLog(@"molten5752");
}


- (void)phylogeny5753
{
	NSLog(@"survive5754");
}


- (void)mankind5755
{
	NSLog(@"encroach5756");
}


- (void)slaver5757
{
	NSLog(@"impassive5758");
}


- (void)audience5759
{
	NSLog(@"aggregation5760");
}


- (void)senator5761
{
	NSLog(@"physician5762");
}


- (void)spartan5763
{
	NSLog(@"pretentious5764");
}


- (void)sympathetic5765
{
	NSLog(@"stamina5766");
}


- (void)analgesic5767
{
	NSLog(@"haste5768");
}


- (void)flour5769
{
	NSLog(@"cursive5770");
}


- (void)restorative5771
{
	NSLog(@"grouch5772");
}


- (void)fortunately5773
{
	NSLog(@"relativity5774");
}


- (void)corrugated5775
{
	NSLog(@"detriment5776");
}


- (void)discrepancy5777
{
	NSLog(@"inferior5778");
}


- (void)perpendicular5779
{
	NSLog(@"convey5780");
}


- (void)septic5781
{
	NSLog(@"compensatory5782");
}


- (void)preceding5783
{
	NSLog(@"competitor5784");
}


- (void)exciting5785
{
	NSLog(@"unbearable5786");
}


- (void)comprehensive5787
{
	NSLog(@"prospect5788");
}


- (void)idiocy5789
{
	NSLog(@"dissemble5790");
}


- (void)accretion5791
{
	NSLog(@"pressing5792");
}


- (void)alimentary5793
{
	NSLog(@"inculcate5794");
}


- (void)receiver5795
{
	NSLog(@"posse5796");
}


- (void)prescribe5797
{
	NSLog(@"tautological5798");
}


- (void)recurrence5799
{
	NSLog(@"cease5800");
}


- (void)purchase5801
{
	NSLog(@"appreciative5802");
}


- (void)sadden5803
{
	NSLog(@"plodding5804");
}


- (void)executioner5805
{
	NSLog(@"critique5806");
}


- (void)supporter5807
{
	NSLog(@"pique5808");
}


- (void)usually5809
{
	NSLog(@"southeast5810");
}


- (void)category5811
{
	NSLog(@"leery5812");
}


- (void)wealth5813
{
	NSLog(@"record5814");
}


- (void)artifacts5815
{
	NSLog(@"conservatism5816");
}


- (void)clairvoyance5817
{
	NSLog(@"imitate5818");
}


- (void)plunge5819
{
	NSLog(@"abusive5820");
}


- (void)corporation5821
{
	NSLog(@"curve5822");
}


- (void)revue5823
{
	NSLog(@"appealing5824");
}


- (void)matter5825
{
	NSLog(@"matador5826");
}


- (void)sympathy5827
{
	NSLog(@"spout5828");
}


- (void)convert5829
{
	NSLog(@"bequest5830");
}


- (void)opener5831
{
	NSLog(@"stratagem5832");
}


- (void)brand5833
{
	NSLog(@"assimilate5834");
}


- (void)mellifluous5835
{
	NSLog(@"imitate5836");
}


- (void)coincidence5837
{
	NSLog(@"injunction5838");
}


- (void)economical5839
{
	NSLog(@"dogmatism5840");
}


- (void)vertex5841
{
	NSLog(@"award5842");
}


- (void)hemostat5843
{
	NSLog(@"misread5844");
}


- (void)bypass5845
{
	NSLog(@"fortress5846");
}


- (void)capitalism5847
{
	NSLog(@"predetermined5848");
}


- (void)peevish5849
{
	NSLog(@"stick5850");
}


- (void)grasshopper5851
{
	NSLog(@"squall5852");
}


- (void)consumerism5853
{
	NSLog(@"restate5854");
}


- (void)develop5855
{
	NSLog(@"granddaughter5856");
}


- (void)understudy5857
{
	NSLog(@"informative5858");
}


- (void)final5859
{
	NSLog(@"straw5860");
}


- (void)uncanny5861
{
	NSLog(@"courteous5862");
}


- (void)toxic5863
{
	NSLog(@"action5864");
}


- (void)strong5865
{
	NSLog(@"grandparent5866");
}


- (void)donkey5867
{
	NSLog(@"curmudgeon5868");
}


- (void)laser5869
{
	NSLog(@"morale5870");
}


- (void)buxom5871
{
	NSLog(@"against5872");
}


- (void)cathartic5873
{
	NSLog(@"undergird5874");
}


- (void)mansion5875
{
	NSLog(@"ornament5876");
}


- (void)cushion5877
{
	NSLog(@"layer5878");
}


- (void)unbiased5879
{
	NSLog(@"flower5880");
}


- (void)languish5881
{
	NSLog(@"crave5882");
}


- (void)counterbalance5883
{
	NSLog(@"enlist5884");
}


- (void)misrepresent5885
{
	NSLog(@"decadent5886");
}


- (void)conscript5887
{
	NSLog(@"rehabilitate5888");
}


- (void)chest5889
{
	NSLog(@"misshapen5890");
}


- (void)happily5891
{
	NSLog(@"employ5892");
}


- (void)elasticity5893
{
	NSLog(@"pharmacology5894");
}


- (void)charitable5895
{
	NSLog(@"capitalize5896");
}


- (void)accumulate5897
{
	NSLog(@"predominant5898");
}


- (void)customer5899
{
	NSLog(@"rostrum5900");
}


- (void)yearn5901
{
	NSLog(@"martial5902");
}


- (void)acquainted5903
{
	NSLog(@"oppose5904");
}


- (void)friend5905
{
	NSLog(@"mordant5906");
}


- (void)oclock5907
{
	NSLog(@"levelheaded5908");
}


- (void)shunt5909
{
	NSLog(@"rhubarb5910");
}


- (void)congruous5911
{
	NSLog(@"gustatory5912");
}


- (void)frock5913
{
	NSLog(@"impeccable5914");
}


- (void)peninsula5915
{
	NSLog(@"advanced5916");
}


- (void)coruscate5917
{
	NSLog(@"unassuming5918");
}


- (void)similar5919
{
	NSLog(@"harbor5920");
}


- (void)crudity5921
{
	NSLog(@"knight5922");
}


- (void)physical5923
{
	NSLog(@"nascent5924");
}


- (void)comprise5925
{
	NSLog(@"forebear5926");
}


- (void)raucous5927
{
	NSLog(@"uproarious5928");
}


- (void)envious5929
{
	NSLog(@"brotherhood5930");
}


- (void)perception5931
{
	NSLog(@"least5932");
}


- (void)raconteur5933
{
	NSLog(@"whitewash5934");
}


- (void)subliminal5935
{
	NSLog(@"vulnerability5936");
}


- (void)research5937
{
	NSLog(@"debility5938");
}


- (void)perspire5939
{
	NSLog(@"intemperate5940");
}


- (void)incandescent5941
{
	NSLog(@"dogma5942");
}


- (void)philosopher5943
{
	NSLog(@"passive5944");
}


- (void)toxic5945
{
	NSLog(@"incomplete5946");
}


- (void)conifer5947
{
	NSLog(@"drabness5948");
}


- (void)estranged5949
{
	NSLog(@"image5950");
}


- (void)nonviolent5951
{
	NSLog(@"satiety5952");
}


- (void)medieval5953
{
	NSLog(@"compatible5954");
}


- (void)thwart5955
{
	NSLog(@"decoy5956");
}


- (void)bereave5957
{
	NSLog(@"craggy5958");
}


- (void)stretch5959
{
	NSLog(@"immanent5960");
}


- (void)littoral5961
{
	NSLog(@"mouthful5962");
}


- (void)prune5963
{
	NSLog(@"shipwreck5964");
}


- (void)negligible5965
{
	NSLog(@"reactivate5966");
}


- (void)leverage5967
{
	NSLog(@"patriot5968");
}


- (void)consumer5969
{
	NSLog(@"barbecue5970");
}


- (void)leakage5971
{
	NSLog(@"personification5972");
}


- (void)charisma5973
{
	NSLog(@"throng5974");
}


- (void)indistinguishable5975
{
	NSLog(@"march5976");
}


- (void)intent5977
{
	NSLog(@"madness5978");
}


- (void)parquetry5979
{
	NSLog(@"vascular5980");
}


- (void)iniquitous5981
{
	NSLog(@"suppose5982");
}


- (void)robbery5983
{
	NSLog(@"pagan5984");
}


- (void)locale5985
{
	NSLog(@"across5986");
}


- (void)reimburse5987
{
	NSLog(@"ensemble5988");
}


- (void)management5989
{
	NSLog(@"garish5990");
}


- (void)lunar5991
{
	NSLog(@"sporadic5992");
}


- (void)solitary5993
{
	NSLog(@"invalidate5994");
}


- (void)bumpy5995
{
	NSLog(@"seriously5996");
}


- (void)deliberately5997
{
	NSLog(@"debit5998");
}


- (void)instrumental5999
{
	NSLog(@"virtual6000");
}


- (void)contented6001
{
	NSLog(@"retributive6002");
}


- (void)bawdy6003
{
	NSLog(@"borrowings6004");
}


- (void)badly6005
{
	NSLog(@"pilot6006");
}


- (void)extremity6007
{
	NSLog(@"about6008");
}


- (void)footle6009
{
	NSLog(@"faint6010");
}


- (void)analyze6011
{
	NSLog(@"November6012");
}


- (void)hubbub6013
{
	NSLog(@"husky6014");
}


- (void)hindmost6015
{
	NSLog(@"regulate6016");
}


- (void)Australia6017
{
	NSLog(@"pedestal6018");
}


- (void)contention6019
{
	NSLog(@"inconsistent6020");
}


- (void)icicle6021
{
	NSLog(@"detractor6022");
}


- (void)concoct6023
{
	NSLog(@"plunder6024");
}


- (void)estuary6025
{
	NSLog(@"regionalization6026");
}


- (void)earth6027
{
	NSLog(@"depress6028");
}


- (void)sleepy6029
{
	NSLog(@"fashionable6030");
}


- (void)converge6031
{
	NSLog(@"neurology6032");
}


- (void)consequential6033
{
	NSLog(@"earsplitting6034");
}


- (void)omelet6035
{
	NSLog(@"annul6036");
}


- (void)excoriate6037
{
	NSLog(@"obtrusive6038");
}


- (void)inkling6039
{
	NSLog(@"inexcusable6040");
}


- (void)erasability6041
{
	NSLog(@"smirch6042");
}


- (void)surmise6043
{
	NSLog(@"fractious6044");
}


- (void)parchment6045
{
	NSLog(@"cursory6046");
}


- (void)floodgate6047
{
	NSLog(@"Mexican6048");
}


- (void)stumble6049
{
	NSLog(@"message6050");
}


- (void)spoof6051
{
	NSLog(@"spank6052");
}


- (void)allergy6053
{
	NSLog(@"concatenate6054");
}


- (void)apposite6055
{
	NSLog(@"adore6056");
}


- (void)outer6057
{
	NSLog(@"baseball6058");
}


- (void)awesome6059
{
	NSLog(@"grasping6060");
}


- (void)relatively6061
{
	NSLog(@"colonial6062");
}


- (void)traitor6063
{
	NSLog(@"depute6064");
}


- (void)raspy6065
{
	NSLog(@"pertinence6066");
}


- (void)peripatetic6067
{
	NSLog(@"information6068");
}


- (void)decipher6069
{
	NSLog(@"hypnosis6070");
}


- (void)fourth6071
{
	NSLog(@"exemption6072");
}


- (void)mediocre6073
{
	NSLog(@"spout6074");
}


- (void)effusion6075
{
	NSLog(@"muffled6076");
}


- (void)anguish6077
{
	NSLog(@"stodgy6078");
}


- (void)creep6079
{
	NSLog(@"nonchalant6080");
}


- (void)captain6081
{
	NSLog(@"discrimination6082");
}


- (void)fortuitous6083
{
	NSLog(@"vertical6084");
}


- (void)influence6085
{
	NSLog(@"evacuate6086");
}


- (void)truncate6087
{
	NSLog(@"foliage6088");
}


- (void)adverbial6089
{
	NSLog(@"purported6090");
}


- (void)gigantic6091
{
	NSLog(@"grandiose6092");
}


- (void)folklore6093
{
	NSLog(@"radioactivity6094");
}


- (void)petrology6095
{
	NSLog(@"dormant6096");
}


- (void)unload6097
{
	NSLog(@"negate6098");
}


- (void)continent6099
{
	NSLog(@"acrid6100");
}


- (void)actually6101
{
	NSLog(@"dormant6102");
}


- (void)aggressive6103
{
	NSLog(@"cramped6104");
}


- (void)scurrilous6105
{
	NSLog(@"kettle6106");
}


- (void)sometimes6107
{
	NSLog(@"dapper6108");
}


- (void)reactivate6109
{
	NSLog(@"diffuse6110");
}


- (void)dilapidate6111
{
	NSLog(@"passionate6112");
}


- (void)humanitarian6113
{
	NSLog(@"forbid6114");
}


- (void)obtuse6115
{
	NSLog(@"ethnography6116");
}


- (void)punch6117
{
	NSLog(@"charismatic6118");
}


- (void)irksome6119
{
	NSLog(@"exuberant6120");
}


- (void)administrative6121
{
	NSLog(@"senior6122");
}


- (void)captious6123
{
	NSLog(@"tournament6124");
}


- (void)slough6125
{
	NSLog(@"abundance6126");
}


- (void)canal6127
{
	NSLog(@"brood6128");
}


- (void)levee6129
{
	NSLog(@"eighty6130");
}


- (void)crater6131
{
	NSLog(@"ingrained6132");
}


- (void)substitute6133
{
	NSLog(@"foreman6134");
}


- (void)ordination6135
{
	NSLog(@"whereas6136");
}


- (void)clear6137
{
	NSLog(@"countermand6138");
}


- (void)filament6139
{
	NSLog(@"deserter6140");
}


- (void)distill6141
{
	NSLog(@"filly6142");
}


- (void)freelancer6143
{
	NSLog(@"specialized6144");
}


- (void)hexagon6145
{
	NSLog(@"intercede6146");
}


- (void)plaque6147
{
	NSLog(@"bandit6148");
}


- (void)noxious6149
{
	NSLog(@"cooker6150");
}


- (void)infatuation6151
{
	NSLog(@"wanderlust6152");
}


- (void)empiricism6153
{
	NSLog(@"conclusion6154");
}


- (void)republican6155
{
	NSLog(@"weird6156");
}


- (void)skunk6157
{
	NSLog(@"brazil6158");
}


- (void)shove6159
{
	NSLog(@"compensate6160");
}


- (void)millinery6161
{
	NSLog(@"malady6162");
}


- (void)feminist6163
{
	NSLog(@"insatiable6164");
}


- (void)unambiguous6165
{
	NSLog(@"unwilling6166");
}


- (void)epidemic6167
{
	NSLog(@"grief6168");
}


- (void)pawnbroker6169
{
	NSLog(@"malice6170");
}


- (void)nascent6171
{
	NSLog(@"vaccine6172");
}


- (void)shortage6173
{
	NSLog(@"bromide6174");
}


- (void)fetish6175
{
	NSLog(@"inflated6176");
}


- (void)hypochondria6177
{
	NSLog(@"triangle6178");
}


- (void)ventriloquist6179
{
	NSLog(@"creek6180");
}


- (void)definitive6181
{
	NSLog(@"secondhand6182");
}


- (void)forefinger6183
{
	NSLog(@"obese6184");
}


- (void)reversal6185
{
	NSLog(@"apathy6186");
}


- (void)convalescence6187
{
	NSLog(@"awash6188");
}


- (void)platinum6189
{
	NSLog(@"field6190");
}


- (void)successful6191
{
	NSLog(@"bookcase6192");
}


- (void)duplicitous6193
{
	NSLog(@"astute6194");
}


- (void)fugitive6195
{
	NSLog(@"encapsulate6196");
}


- (void)cohesion6197
{
	NSLog(@"cemetery6198");
}


- (void)lawful6199
{
	NSLog(@"fracture6200");
}


- (void)plaster6201
{
	NSLog(@"generalize6202");
}


- (void)delve6203
{
	NSLog(@"unfounded6204");
}


- (void)retreat6205
{
	NSLog(@"visionary6206");
}


- (void)subliminal6207
{
	NSLog(@"occupation6208");
}


- (void)pygmy6209
{
	NSLog(@"egocentric6210");
}


- (void)imagine6211
{
	NSLog(@"greengrocer6212");
}


- (void)wrapper6213
{
	NSLog(@"alternate6214");
}


- (void)conjecture6215
{
	NSLog(@"amiable6216");
}


- (void)unfold6217
{
	NSLog(@"complexity6218");
}


- (void)attribution6219
{
	NSLog(@"periphery6220");
}


- (void)willingly6221
{
	NSLog(@"nerveless6222");
}


- (void)German6223
{
	NSLog(@"stalk6224");
}


- (void)inapparent6225
{
	NSLog(@"jovial6226");
}


- (void)attentive6227
{
	NSLog(@"beneficial6228");
}


- (void)partially6229
{
	NSLog(@"predilection6230");
}


- (void)truism6231
{
	NSLog(@"cheese6232");
}


- (void)figurine6233
{
	NSLog(@"benefit6234");
}


- (void)oracular6235
{
	NSLog(@"veneration6236");
}


- (void)conduce6237
{
	NSLog(@"exult6238");
}


- (void)forbidden6239
{
	NSLog(@"misdeed6240");
}


- (void)insulate6241
{
	NSLog(@"hawker6242");
}


- (void)sidereal6243
{
	NSLog(@"nonconformist6244");
}


- (void)equally6245
{
	NSLog(@"delinquent6246");
}


- (void)monetary6247
{
	NSLog(@"owing6248");
}


- (void)incorporeal6249
{
	NSLog(@"populous6250");
}


- (void)grandson6251
{
	NSLog(@"criterion6252");
}


- (void)accident6253
{
	NSLog(@"passivity6254");
}


- (void)assuage6255
{
	NSLog(@"easel6256");
}


- (void)structure6257
{
	NSLog(@"garrulous6258");
}


- (void)ubiquitous6259
{
	NSLog(@"bucket6260");
}


- (void)subside6261
{
	NSLog(@"solvency6262");
}


- (void)honorarium6263
{
	NSLog(@"papercutting6264");
}


- (void)oblation6265
{
	NSLog(@"obliterate6266");
}


- (void)corporeal6267
{
	NSLog(@"touchstone6268");
}


- (void)checkered6269
{
	NSLog(@"Swede6270");
}


- (void)stygian6271
{
	NSLog(@"exhaustive6272");
}


- (void)shack6273
{
	NSLog(@"striated6274");
}


- (void)affect6275
{
	NSLog(@"estimable6276");
}


- (void)calorie6277
{
	NSLog(@"effectively6278");
}


- (void)univocal6279
{
	NSLog(@"construe6280");
}


- (void)cyclist6281
{
	NSLog(@"elation6282");
}


- (void)grammatical6283
{
	NSLog(@"excel6284");
}


- (void)foolish6285
{
	NSLog(@"precision6286");
}


- (void)logjam6287
{
	NSLog(@"hypotenuse6288");
}


- (void)sensual6289
{
	NSLog(@"exhortation6290");
}


- (void)awful6291
{
	NSLog(@"rectify6292");
}


- (void)detritus6293
{
	NSLog(@"banter6294");
}


- (void)feedback6295
{
	NSLog(@"library6296");
}


- (void)judicial6297
{
	NSLog(@"irritate6298");
}


- (void)whirl6299
{
	NSLog(@"mature6300");
}


- (void)surround6301
{
	NSLog(@"pollution6302");
}


- (void)plankton6303
{
	NSLog(@"dozen6304");
}


- (void)dainty6305
{
	NSLog(@"seldom6306");
}


- (void)roman6307
{
	NSLog(@"notebook6308");
}


- (void)absurd6309
{
	NSLog(@"ownership6310");
}


- (void)cosmopolitanism6311
{
	NSLog(@"mammoth6312");
}


- (void)notify6313
{
	NSLog(@"missive6314");
}


- (void)restiveness6315
{
	NSLog(@"naked6316");
}


- (void)recoil6317
{
	NSLog(@"talkative6318");
}


- (void)tackiness6319
{
	NSLog(@"receptive6320");
}


- (void)strive6321
{
	NSLog(@"tributary6322");
}


- (void)frisk6323
{
	NSLog(@"trophy6324");
}


- (void)factor6325
{
	NSLog(@"outlaw6326");
}


- (void)grimace6327
{
	NSLog(@"throw6328");
}


- (void)retouch6329
{
	NSLog(@"lightly6330");
}


- (void)abiding6331
{
	NSLog(@"enrich6332");
}


- (void)sheer6333
{
	NSLog(@"boredom6334");
}


- (void)arable6335
{
	NSLog(@"accede6336");
}


- (void)poise6337
{
	NSLog(@"disallow6338");
}


- (void)crescendo6339
{
	NSLog(@"scarf6340");
}


- (void)unbearable6341
{
	NSLog(@"motor6342");
}


- (void)dogged6343
{
	NSLog(@"flake6344");
}


- (void)hamburger6345
{
	NSLog(@"systematically6346");
}


- (void)lumber6347
{
	NSLog(@"strident6348");
}


- (void)Greek6349
{
	NSLog(@"compensatory6350");
}


- (void)deprivation6351
{
	NSLog(@"possession6352");
}


- (void)dispute6353
{
	NSLog(@"noticeable6354");
}


- (void)espouse6355
{
	NSLog(@"mistaken6356");
}


- (void)autumn6357
{
	NSLog(@"comparatively6358");
}


- (void)separately6359
{
	NSLog(@"stylus6360");
}


- (void)unctuous6361
{
	NSLog(@"economic6362");
}


- (void)crate6363
{
	NSLog(@"shift6364");
}


- (void)proximity6365
{
	NSLog(@"rainfall6366");
}


- (void)vapid6367
{
	NSLog(@"drama6368");
}


- (void)aseptic6369
{
	NSLog(@"mutate6370");
}


- (void)overcoat6371
{
	NSLog(@"bicycle6372");
}


- (void)ballroom6373
{
	NSLog(@"extemporize6374");
}


- (void)proletarian6375
{
	NSLog(@"unbiased6376");
}


- (void)tattered6377
{
	NSLog(@"skyscraper6378");
}


- (void)withstand6379
{
	NSLog(@"aesthete6380");
}


- (void)amount6381
{
	NSLog(@"refined6382");
}


- (void)grotto6383
{
	NSLog(@"capacity6384");
}


- (void)faithfully6385
{
	NSLog(@"verdigris6386");
}


- (void)irreconcilable6387
{
	NSLog(@"executioner6388");
}


- (void)plate6389
{
	NSLog(@"wrapper6390");
}


- (void)screw6391
{
	NSLog(@"revise6392");
}


- (void)Jewish6393
{
	NSLog(@"reaffirm6394");
}


- (void)sweetheart6395
{
	NSLog(@"pilfer6396");
}


- (void)conjunction6397
{
	NSLog(@"anniversary6398");
}


- (void)opponent6399
{
	NSLog(@"stammer6400");
}


- (void)prolong6401
{
	NSLog(@"captain6402");
}


- (void)sacrilege6403
{
	NSLog(@"sprinkle6404");
}


- (void)sprawl6405
{
	NSLog(@"forbearance6406");
}


- (void)folder6407
{
	NSLog(@"infuse6408");
}


- (void)supervise6409
{
	NSLog(@"curve6410");
}


- (void)portraiture6411
{
	NSLog(@"stagger6412");
}


- (void)exhilarate6413
{
	NSLog(@"friendship6414");
}


- (void)livestock6415
{
	NSLog(@"economical6416");
}


- (void)nugatory6417
{
	NSLog(@"gainsay6418");
}


- (void)examine6419
{
	NSLog(@"attainment6420");
}


- (void)button6421
{
	NSLog(@"etiquette6422");
}


- (void)talon6423
{
	NSLog(@"protest6424");
}


- (void)vaporize6425
{
	NSLog(@"meritorious6426");
}


- (void)sardonic6427
{
	NSLog(@"fugitive6428");
}


- (void)afford6429
{
	NSLog(@"eschew6430");
}


- (void)expire6431
{
	NSLog(@"namely6432");
}


- (void)prior6433
{
	NSLog(@"fortify6434");
}


- (void)proletarian6435
{
	NSLog(@"suddenly6436");
}


- (void)colonial6437
{
	NSLog(@"olfactory6438");
}


- (void)relief6439
{
	NSLog(@"beach6440");
}


- (void)questionnaire6441
{
	NSLog(@"indices6442");
}


- (void)ineffectual6443
{
	NSLog(@"doldrums6444");
}


- (void)repay6445
{
	NSLog(@"participant6446");
}


- (void)draft6447
{
	NSLog(@"hubbub6448");
}


- (void)entertaining6449
{
	NSLog(@"ratio6450");
}


- (void)flask6451
{
	NSLog(@"contemplate6452");
}


- (void)scoundrel6453
{
	NSLog(@"flunk6454");
}


- (void)carnivore6455
{
	NSLog(@"press6456");
}


- (void)prompt6457
{
	NSLog(@"plagiarism6458");
}


- (void)irresistible6459
{
	NSLog(@"enthrall6460");
}


- (void)venom6461
{
	NSLog(@"operation6462");
}


- (void)anticipate6463
{
	NSLog(@"breathe6464");
}


- (void)breast6465
{
	NSLog(@"strawberry6466");
}


- (void)gladiator6467
{
	NSLog(@"splendor6468");
}


- (void)successful6469
{
	NSLog(@"imposition6470");
}


- (void)criminal6471
{
	NSLog(@"interlock6472");
}


- (void)exceed6473
{
	NSLog(@"docile6474");
}


- (void)glaring6475
{
	NSLog(@"jeans6476");
}


- (void)compound6477
{
	NSLog(@"aqueduct6478");
}


- (void)menial6479
{
	NSLog(@"purport6480");
}


- (void)envious6481
{
	NSLog(@"scintilla6482");
}


- (void)cultivate6483
{
	NSLog(@"diminuendo6484");
}


- (void)discern6485
{
	NSLog(@"impersonator6486");
}


- (void)avenue6487
{
	NSLog(@"orotund6488");
}


- (void)coterie6489
{
	NSLog(@"frieze6490");
}


- (void)visit6491
{
	NSLog(@"censure6492");
}


- (void)repay6493
{
	NSLog(@"radioactivity6494");
}


- (void)slant6495
{
	NSLog(@"auricular6496");
}


- (void)indulge6497
{
	NSLog(@"plastics6498");
}


- (void)thirsty6499
{
	NSLog(@"derelict6500");
}


- (void)draconian6501
{
	NSLog(@"atlas6502");
}


- (void)bubble6503
{
	NSLog(@"lackadaisical6504");
}


- (void)annoy6505
{
	NSLog(@"pirate6506");
}


- (void)considerably6507
{
	NSLog(@"feral6508");
}


- (void)titular6509
{
	NSLog(@"baker6510");
}


- (void)conglomerate6511
{
	NSLog(@"classical6512");
}


- (void)celerity6513
{
	NSLog(@"blank6514");
}


- (void)logical6515
{
	NSLog(@"chaste6516");
}


- (void)association6517
{
	NSLog(@"motion6518");
}


- (void)etiquette6519
{
	NSLog(@"ointment6520");
}


- (void)debunk6521
{
	NSLog(@"sheer6522");
}


- (void)reputation6523
{
	NSLog(@"asteroid6524");
}


- (void)inclement6525
{
	NSLog(@"imitate6526");
}


- (void)differ6527
{
	NSLog(@"centripetal6528");
}


- (void)quarterly6529
{
	NSLog(@"connect6530");
}


- (void)stunt6531
{
	NSLog(@"exclusively6532");
}


- (void)research6533
{
	NSLog(@"brightness6534");
}


- (void)missive6535
{
	NSLog(@"trance6536");
}


- (void)disciplinarian6537
{
	NSLog(@"responsiveness6538");
}


- (void)etiquette6539
{
	NSLog(@"relenting6540");
}


- (void)bellwether6541
{
	NSLog(@"didactic6542");
}


- (void)disconnected6543
{
	NSLog(@"invulnerable6544");
}


- (void)byproduct6545
{
	NSLog(@"identity6546");
}


- (void)anyway6547
{
	NSLog(@"perhaps6548");
}


- (void)bundle6549
{
	NSLog(@"diffuse6550");
}


- (void)insatiable6551
{
	NSLog(@"equitation6552");
}


- (void)voter6553
{
	NSLog(@"arrange6554");
}


- (void)animate6555
{
	NSLog(@"device6556");
}


- (void)forthrightly6557
{
	NSLog(@"eavesdropper6558");
}


- (void)patrol6559
{
	NSLog(@"frock6560");
}


- (void)exalted6561
{
	NSLog(@"empiricism6562");
}


- (void)nonchalance6563
{
	NSLog(@"linger6564");
}


- (void)distinguished6565
{
	NSLog(@"index6566");
}


- (void)gustation6567
{
	NSLog(@"Venus6568");
}


- (void)cathedral6569
{
	NSLog(@"whilst6570");
}


- (void)switch6571
{
	NSLog(@"doctrinaire6572");
}


- (void)terminate6573
{
	NSLog(@"resolute6574");
}


- (void)dredge6575
{
	NSLog(@"corpuscle6576");
}


- (void)minutes6577
{
	NSLog(@"stink6578");
}


- (void)operetta6579
{
	NSLog(@"detached6580");
}


- (void)conversely6581
{
	NSLog(@"emanate6582");
}


- (void)obvious6583
{
	NSLog(@"tenacity6584");
}


- (void)diverse6585
{
	NSLog(@"decorate6586");
}


- (void)whether6587
{
	NSLog(@"waving6588");
}


- (void)preparation6589
{
	NSLog(@"mistral6590");
}


- (void)protagonist6591
{
	NSLog(@"insanity6592");
}


- (void)bridegroom6593
{
	NSLog(@"gamble6594");
}


- (void)moldy6595
{
	NSLog(@"edify6596");
}


- (void)convention6597
{
	NSLog(@"southern6598");
}


- (void)encyclopedic6599
{
	NSLog(@"solar6600");
}


- (void)showy6601
{
	NSLog(@"plant6602");
}


- (void)countersign6603
{
	NSLog(@"ultramundane6604");
}


- (void)rejoice6605
{
	NSLog(@"inventory6606");
}


- (void)artful6607
{
	NSLog(@"lecturer6608");
}


- (void)imagine6609
{
	NSLog(@"consequent6610");
}


- (void)conjure6611
{
	NSLog(@"inaccurate6612");
}


- (void)gleam6613
{
	NSLog(@"Christian6614");
}


- (void)billion6615
{
	NSLog(@"fabulous6616");
}


- (void)syllable6617
{
	NSLog(@"scorching6618");
}


- (void)facsimile6619
{
	NSLog(@"garlic6620");
}


- (void)acquisition6621
{
	NSLog(@"seedling6622");
}


- (void)translate6623
{
	NSLog(@"inspect6624");
}


- (void)differently6625
{
	NSLog(@"illegible6626");
}


- (void)ravishing6627
{
	NSLog(@"enticing6628");
}


- (void)stingy6629
{
	NSLog(@"deplore6630");
}


- (void)gangster6631
{
	NSLog(@"iridescent6632");
}


- (void)Fahrenheit6633
{
	NSLog(@"fleece6634");
}


- (void)earnings6635
{
	NSLog(@"irrigation6636");
}


- (void)receive6637
{
	NSLog(@"lecture6638");
}


- (void)inhabit6639
{
	NSLog(@"beginning6640");
}


- (void)terminus6641
{
	NSLog(@"sedentary6642");
}


- (void)progressive6643
{
	NSLog(@"rebate6644");
}


- (void)blouse6645
{
	NSLog(@"admittedly6646");
}


- (void)laundry6647
{
	NSLog(@"mimicry6648");
}


- (void)pitfall6649
{
	NSLog(@"reassurance6650");
}


- (void)aisle6651
{
	NSLog(@"gamble6652");
}


- (void)intermittent6653
{
	NSLog(@"perversion6654");
}


- (void)idiomatic6655
{
	NSLog(@"emollient6656");
}


- (void)locus6657
{
	NSLog(@"antiquity6658");
}


- (void)computer6659
{
	NSLog(@"decadence6660");
}


- (void)finalize6661
{
	NSLog(@"chrysanthemum6662");
}


- (void)availability6663
{
	NSLog(@"assuage6664");
}


- (void)philology6665
{
	NSLog(@"ameliorate6666");
}


- (void)volleyball6667
{
	NSLog(@"revolution6668");
}


- (void)rinse6669
{
	NSLog(@"smear6670");
}


- (void)cooperative6671
{
	NSLog(@"incorporate6672");
}


- (void)greenhouse6673
{
	NSLog(@"epigram6674");
}


- (void)recollection6675
{
	NSLog(@"importance6676");
}


- (void)beneficent6677
{
	NSLog(@"woeful6678");
}


- (void)gainsay6679
{
	NSLog(@"branch6680");
}


- (void)coastal6681
{
	NSLog(@"extrapolate6682");
}


- (void)contrite6683
{
	NSLog(@"abstruse6684");
}


- (void)settlement6685
{
	NSLog(@"accord6686");
}


- (void)commute6687
{
	NSLog(@"sardonic6688");
}


- (void)stall6689
{
	NSLog(@"synchronous6690");
}


- (void)gnawing6691
{
	NSLog(@"teeter6692");
}


- (void)renovate6693
{
	NSLog(@"taxing6694");
}


- (void)syringe6695
{
	NSLog(@"hardihood6696");
}


- (void)depend6697
{
	NSLog(@"tragic6698");
}


- (void)calculated6699
{
	NSLog(@"corral6700");
}


- (void)devotion6701
{
	NSLog(@"fortitude6702");
}


- (void)bacchanal6703
{
	NSLog(@"asymptomatic6704");
}


- (void)dispatch6705
{
	NSLog(@"imagination6706");
}


- (void)foolhardy6707
{
	NSLog(@"reputable6708");
}


- (void)transitory6709
{
	NSLog(@"itself6710");
}


- (void)surge6711
{
	NSLog(@"carbon6712");
}


- (void)financing6713
{
	NSLog(@"spunk6714");
}


- (void)urgently6715
{
	NSLog(@"bruise6716");
}


- (void)museum6717
{
	NSLog(@"stunt6718");
}


- (void)vogue6719
{
	NSLog(@"tinder6720");
}


- (void)sanity6721
{
	NSLog(@"abbreviate6722");
}


- (void)tourism6723
{
	NSLog(@"mandatory6724");
}


- (void)vicar6725
{
	NSLog(@"crush6726");
}


- (void)doctor6727
{
	NSLog(@"musician6728");
}


- (void)imprison6729
{
	NSLog(@"dependability6730");
}


- (void)thrust6731
{
	NSLog(@"zipcode6732");
}


- (void)evocative6733
{
	NSLog(@"unpretentious6734");
}


- (void)fertilize6735
{
	NSLog(@"musicologist6736");
}


- (void)hurricane6737
{
	NSLog(@"purported6738");
}


- (void)coagulant6739
{
	NSLog(@"subtract6740");
}


- (void)automation6741
{
	NSLog(@"unobtainable6742");
}


- (void)distraction6743
{
	NSLog(@"negative6744");
}


- (void)phase6745
{
	NSLog(@"typewriter6746");
}


- (void)salute6747
{
	NSLog(@"mixture6748");
}


- (void)undersigned6749
{
	NSLog(@"shopping6750");
}


- (void)meter6751
{
	NSLog(@"unequivocal6752");
}


- (void)plumb6753
{
	NSLog(@"distillation6754");
}


- (void)honey6755
{
	NSLog(@"reverend6756");
}


- (void)tiptoe6757
{
	NSLog(@"replacement6758");
}


- (void)prelate6759
{
	NSLog(@"hermit6760");
}


- (void)jabber6761
{
	NSLog(@"imprudent6762");
}


- (void)coalesce6763
{
	NSLog(@"litre6764");
}


- (void)temporary6765
{
	NSLog(@"gross6766");
}


- (void)detection6767
{
	NSLog(@"provided6768");
}


- (void)shade6769
{
	NSLog(@"investigation6770");
}


- (void)enormous6771
{
	NSLog(@"assiduous6772");
}


- (void)subject6773
{
	NSLog(@"frailty6774");
}


- (void)stage6775
{
	NSLog(@"observer6776");
}


- (void)apprentice6777
{
	NSLog(@"economize6778");
}


- (void)proctor6779
{
	NSLog(@"hereafter6780");
}


- (void)referee6781
{
	NSLog(@"freelancer6782");
}


- (void)gently6783
{
	NSLog(@"bride6784");
}


- (void)infamous6785
{
	NSLog(@"interpreter6786");
}


- (void)heartily6787
{
	NSLog(@"valuable6788");
}


- (void)broadcasting6789
{
	NSLog(@"solemnity6790");
}


- (void)citizenship6791
{
	NSLog(@"display6792");
}


- (void)attitude6793
{
	NSLog(@"buckle6794");
}


- (void)denim6795
{
	NSLog(@"manifesto6796");
}


- (void)affect6797
{
	NSLog(@"waterfall6798");
}


- (void)budge6799
{
	NSLog(@"Fahrenheit6800");
}


- (void)remedy6801
{
	NSLog(@"plaintive6802");
}


- (void)president6803
{
	NSLog(@"fidgety6804");
}


- (void)quantity6805
{
	NSLog(@"sodium6806");
}


- (void)expiate6807
{
	NSLog(@"reasonably6808");
}


- (void)mediocre6809
{
	NSLog(@"underground6810");
}


- (void)renaissance6811
{
	NSLog(@"needless6812");
}


- (void)disobedient6813
{
	NSLog(@"locale6814");
}


- (void)analgesia6815
{
	NSLog(@"scathing6816");
}


- (void)sadly6817
{
	NSLog(@"advertising6818");
}


- (void)canine6819
{
	NSLog(@"encipher6820");
}


- (void)cession6821
{
	NSLog(@"organization6822");
}


- (void)mastery6823
{
	NSLog(@"axiomatic6824");
}


- (void)corruption6825
{
	NSLog(@"pullet6826");
}


- (void)incisive6827
{
	NSLog(@"actively6828");
}


- (void)sedulity6829
{
	NSLog(@"generosity6830");
}


- (void)tardy6831
{
	NSLog(@"tarpaulin6832");
}


- (void)round6833
{
	NSLog(@"recovery6834");
}


- (void)heaven6835
{
	NSLog(@"insider6836");
}


- (void)inclusion6837
{
	NSLog(@"labor6838");
}


- (void)lever6839
{
	NSLog(@"declivity6840");
}


- (void)befuddlement6841
{
	NSLog(@"moratorium6842");
}


- (void)diabetes6843
{
	NSLog(@"farmhand6844");
}


- (void)pastoral6845
{
	NSLog(@"optimize6846");
}


- (void)horse6847
{
	NSLog(@"deification6848");
}


- (void)loquacious6849
{
	NSLog(@"prelate6850");
}


- (void)despite6851
{
	NSLog(@"minutia6852");
}


- (void)sweetheart6853
{
	NSLog(@"acute6854");
}


- (void)heartily6855
{
	NSLog(@"composer6856");
}


- (void)phonetic6857
{
	NSLog(@"greatly6858");
}


- (void)vision6859
{
	NSLog(@"athletic6860");
}


- (void)fault6861
{
	NSLog(@"thrall6862");
}


- (void)inferior6863
{
	NSLog(@"intense6864");
}


- (void)storage6865
{
	NSLog(@"phonetics6866");
}


- (void)rustic6867
{
	NSLog(@"pronoun6868");
}


- (void)appetite6869
{
	NSLog(@"abridgment6870");
}


- (void)instruct6871
{
	NSLog(@"there6872");
}


- (void)weave6873
{
	NSLog(@"fluvial6874");
}


- (void)novelette6875
{
	NSLog(@"preset6876");
}


- (void)juvenile6877
{
	NSLog(@"solve6878");
}


- (void)undersigned6879
{
	NSLog(@"irrigation6880");
}


- (void)coterie6881
{
	NSLog(@"recluse6882");
}


- (void)starvation6883
{
	NSLog(@"student6884");
}


- (void)stilted6885
{
	NSLog(@"domination6886");
}


- (void)fester6887
{
	NSLog(@"plankton6888");
}


- (void)continual6889
{
	NSLog(@"quarterly6890");
}


- (void)layman6891
{
	NSLog(@"cravat6892");
}


- (void)columnist6893
{
	NSLog(@"omniscient6894");
}


- (void)enough6895
{
	NSLog(@"ardent6896");
}


- (void)steal6897
{
	NSLog(@"baggage6898");
}


- (void)suggestion6899
{
	NSLog(@"conceited6900");
}


- (void)crumb6901
{
	NSLog(@"boxer6902");
}


- (void)uproarious6903
{
	NSLog(@"gluttony6904");
}


- (void)correction6905
{
	NSLog(@"appalling6906");
}


- (void)fretwork6907
{
	NSLog(@"shrink6908");
}


- (void)peace6909
{
	NSLog(@"dissuade6910");
}


- (void)friendly6911
{
	NSLog(@"mutinous6912");
}


- (void)petroleum6913
{
	NSLog(@"truly6914");
}


- (void)dismantle6915
{
	NSLog(@"dawdle6916");
}


- (void)bureau6917
{
	NSLog(@"burner6918");
}


- (void)refute6919
{
	NSLog(@"placebo6920");
}


- (void)huckster6921
{
	NSLog(@"abusive6922");
}


- (void)ablution6923
{
	NSLog(@"gargoyle6924");
}


- (void)summon6925
{
	NSLog(@"unctuous6926");
}


- (void)handbook6927
{
	NSLog(@"attest6928");
}


- (void)rancorous6929
{
	NSLog(@"decline6930");
}


- (void)immigrant6931
{
	NSLog(@"chest6932");
}


- (void)hardheaded6933
{
	NSLog(@"celebrity6934");
}


- (void)virtuous6935
{
	NSLog(@"bargain6936");
}


- (void)baste6937
{
	NSLog(@"transient6938");
}


- (void)survival6939
{
	NSLog(@"electricity6940");
}


- (void)related6941
{
	NSLog(@"desperate6942");
}


- (void)heavy6943
{
	NSLog(@"impatient6944");
}


- (void)defer6945
{
	NSLog(@"rebuttal6946");
}


- (void)honorarium6947
{
	NSLog(@"predilection6948");
}


- (void)harangue6949
{
	NSLog(@"obstruct6950");
}


- (void)surveyor6951
{
	NSLog(@"strength6952");
}


- (void)appease6953
{
	NSLog(@"firmness6954");
}


- (void)gigantic6955
{
	NSLog(@"adjustable6956");
}


- (void)brisk6957
{
	NSLog(@"deign6958");
}


- (void)attendant6959
{
	NSLog(@"mould6960");
}


- (void)example6961
{
	NSLog(@"roster6962");
}


- (void)fauna6963
{
	NSLog(@"overreach6964");
}


- (void)Egypt6965
{
	NSLog(@"fracture6966");
}


- (void)molten6967
{
	NSLog(@"dramatist6968");
}


- (void)innocence6969
{
	NSLog(@"aversion6970");
}


- (void)pauper6971
{
	NSLog(@"egotist6972");
}


- (void)former6973
{
	NSLog(@"childish6974");
}


- (void)gravity6975
{
	NSLog(@"watershed6976");
}


- (void)imperturbable6977
{
	NSLog(@"omnipotent6978");
}


- (void)hypocrisy6979
{
	NSLog(@"mermaid6980");
}


- (void)aorta6981
{
	NSLog(@"nickname6982");
}


- (void)league6983
{
	NSLog(@"abrogation6984");
}


- (void)humility6985
{
	NSLog(@"rankle6986");
}


- (void)falter6987
{
	NSLog(@"codicil6988");
}


- (void)concave6989
{
	NSLog(@"experimentation6990");
}


- (void)plaza6991
{
	NSLog(@"diary6992");
}


- (void)honour6993
{
	NSLog(@"steamer6994");
}


- (void)economy6995
{
	NSLog(@"vender6996");
}


- (void)shift6997
{
	NSLog(@"romanticism6998");
}


- (void)recondite6999
{
	NSLog(@"conspectus7000");
}


- (void)normalize7001
{
	NSLog(@"distribution7002");
}


- (void)celebrated7003
{
	NSLog(@"prosperity7004");
}


- (void)novelette7005
{
	NSLog(@"eminent7006");
}


- (void)preamble7007
{
	NSLog(@"feline7008");
}


- (void)galactic7009
{
	NSLog(@"stigma7010");
}


- (void)repellent7011
{
	NSLog(@"tainted7012");
}


- (void)crucial7013
{
	NSLog(@"marketing7014");
}


- (void)misinform7015
{
	NSLog(@"spasmodic7016");
}


- (void)flirtatious7017
{
	NSLog(@"asleep7018");
}


- (void)nicety7019
{
	NSLog(@"draft7020");
}


- (void)blissful7021
{
	NSLog(@"restrictive7022");
}


- (void)abbreviation7023
{
	NSLog(@"suffice7024");
}


- (void)unlock7025
{
	NSLog(@"nitrogen7026");
}


- (void)judiciousness7027
{
	NSLog(@"rucksack7028");
}


- (void)heroic7029
{
	NSLog(@"experimentation7030");
}


- (void)wanton7031
{
	NSLog(@"ventilation7032");
}


- (void)outnumbered7033
{
	NSLog(@"elaborate7034");
}


- (void)squeeze7035
{
	NSLog(@"bifurcate7036");
}


- (void)assertive7037
{
	NSLog(@"interlocking7038");
}


- (void)posit7039
{
	NSLog(@"vitiate7040");
}


- (void)disciple7041
{
	NSLog(@"overpower7042");
}


- (void)isthmus7043
{
	NSLog(@"noble7044");
}


- (void)defendant7045
{
	NSLog(@"marsupial7046");
}


- (void)library7047
{
	NSLog(@"bedizen7048");
}

@end

#endif

