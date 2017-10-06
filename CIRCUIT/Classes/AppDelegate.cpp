#include "AppDelegate.h"
#include "SplashScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(600,900);


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
	
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {

		glview = GLViewImpl::createWithRect("CIRCUIT", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));

        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
    

    register_all_packages();

	FileUtils::getInstance()->addSearchPath("GameScene/images");
	FileUtils::getInstance()->addSearchPath("ResultScene");
	FileUtils::getInstance()->addSearchPath("RankUpScene");
	FileUtils::getInstance()->addSearchPath("RankUpScene/message");
	FileUtils::getInstance()->addSearchPath("SplashScene");
	FileUtils::getInstance()->addSearchPath("Title");
	FileUtils::getInstance()->addSearchPath("StageSelect/Rank");
	FileUtils::getInstance()->addSearchPath("GameScene");
	FileUtils::getInstance()->addSearchPath("timerNum");


    // create a scene. it's an autorelease object
	auto scene = SplashScene::create();
	//auto scene = StageSelectScene::create();
	
	

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
