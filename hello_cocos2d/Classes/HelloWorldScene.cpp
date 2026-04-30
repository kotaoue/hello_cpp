#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 背景色（黒）を設定するレイヤー
    auto background = LayerColor::create(Color4B(0, 0, 0, 255));
    this->addChild(background, 0);

    // "Hello, World!" ラベルをウィンドウ中央に配置
    auto label = Label::createWithSystemFont("Hello, World!", "Arial", 48);
    label->setTextColor(Color4B(255, 255, 255, 255));
    label->setPosition(Vec2(origin.x + visibleSize.width  / 2,
                            origin.y + visibleSize.height / 2));
    this->addChild(label, 1);

    return true;
}
