#include "AppDelegate.h"
#include "TitleScene.h"

#pragma execution_character_set("utf-8")
USING_NS_CC;

//ウィンドウサイズ
static cocos2d::Size designResolutionSize = cocos2d::Size(480,800);


//コンストラクタ
AppDelegate::AppDelegate()
{

}

//デストラクタ
AppDelegate::~AppDelegate()
{
}

//OpenGLの初期設定
void AppDelegate::initGLContextAttrs()
{
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

//パッケージ登録
static int register_all_packages()
{
	return 0; //flag for packages manager
}

//起動時の処理
bool AppDelegate::applicationDidFinishLaunching()
{
	//初期設定
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	//ウィンドウ作成
	if (!glview)
	{
		glview = GLViewImpl::createWithRect("シューティングゲーム", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		director->setOpenGLView(glview);
	}

	//FPSを指定する
	director->setDisplayStats(true);

	//画面更新速度
	director->setAnimationInterval(1.0 / 60);

	//画面サイズを統一
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);

	//動作状況の表示
	director->setDisplayStats(false);

	register_all_packages();

	//最初のシーン
	auto scene = TitleScene::createScene();

	//ゲームスタート
	director->runWithScene(scene);

	return true;
}

//バックグラウンドに回ったときの処理
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	//『SimpleAudioEngine』を使ってる場合は一時停止する
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//フォアグラウンドに戻ったときの処理
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	//『SimpleAudioEngine』を使ってる場合は再開する
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}