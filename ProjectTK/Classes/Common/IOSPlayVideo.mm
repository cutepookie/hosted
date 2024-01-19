//
//  IOSPlayVideo.cpp
//  video
//
//  Created by cri-mac on 14-5-15.
//
//

#include "IOSPlayVideo.h"
#include "AppController.h"

void IOSPlayVideo::playVideoForIOS(const char* pfile)
{
    AppController *app = (AppController*) [[UIApplication sharedApplication] delegate];
    [app playVideo: [NSString stringWithUTF8String:pfile]];
}



