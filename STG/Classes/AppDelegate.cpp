#include "AppDelegate.h"
#include "TitleScene.h"

#pragma execution_character_set("utf-8")
USING_NS_CC;

//�E�B���h�E�T�C�Y
static cocos2d::Size designResolutionSize = cocos2d::Size(480,800);


//�R���X�g���N�^
AppDelegate::AppDelegate()
{

}

//�f�X�g���N�^
AppDelegate::~AppDelegate()
{
}

//OpenGL�̏����ݒ�
void AppDelegate::initGLContextAttrs()
{
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

//�p�b�P�[�W�o�^
static int register_all_packages()
{
	return 0; //flag for packages manager
}

//�N�����̏���
bool AppDelegate::applicationDidFinishLaunching()
{
	//�����ݒ�
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	//�E�B���h�E�쐬
	if (!glview)
	{
		glview = GLViewImpl::createWithRect("�V���[�e�B���O�Q�[��", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		director->setOpenGLView(glview);
	}

	//FPS���w�肷��
	director->setDisplayStats(true);

	//��ʍX�V���x
	director->setAnimationInterval(1.0 / 60);

	//��ʃT�C�Y�𓝈�
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);

	//����󋵂̕\��
	director->setDisplayStats(false);

	register_all_packages();

	//�ŏ��̃V�[��
	auto scene = TitleScene::createScene();

	//�Q�[���X�^�[�g
	director->runWithScene(scene);

	return true;
}

//�o�b�N�O���E���h�ɉ�����Ƃ��̏���
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	//�wSimpleAudioEngine�x���g���Ă�ꍇ�͈ꎞ��~����
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//�t�H�A�O���E���h�ɖ߂����Ƃ��̏���
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	//�wSimpleAudioEngine�x���g���Ă�ꍇ�͍ĊJ����
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}