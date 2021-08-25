#include "stdafx.h"


USING_NS_CC;

CCSize g_PhoneSize;

typedef struct tagResource

{

    cocos2d::CCSize size;

    char directory[100];

}Resource;




static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };

static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };

static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };





static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(D_PHONE_WIDTH, D_PHONE_HEIGHT);


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	//glview->setFrameSize((D_SCREEN_SCALE_WIDTH(100)), (D_SCREEN_SCALE_HEIGHT(100)));
	
	srand((unsigned int)time(NULL));

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(720 * 0.8 , 1280 * 0.8);
#endif
	glview->setDesignResolutionSize(720 , 1280 ,kResolutionNoBorder);
	
	g_PhoneSize = glview->getFrameSize();
    // turn on display FPS
    //director->setDisplayStats(true);
	//director->set



    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = LogoScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	D_SOUNDMNG->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	
	D_SOUNDMNG->resumeBackgroundMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
