#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreColourValue.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreInput.h>

class HelloOgreApp : public OgreBites::ApplicationContext,
                     public OgreBites::InputListener
{
public:
    HelloOgreApp() : OgreBites::ApplicationContext("OGRE Hello World") {}

    void setup() override
    {
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        Ogre::SceneManager* scnMgr = getRoot()->createSceneManager();
        scnMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

        // カメラの作成
        Ogre::Camera* cam = scnMgr->createCamera("MainCam");
        cam->setNearClipDistance(5.0f);

        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0.0f, 0.0f, 500.0f);
        camNode->lookAt(Ogre::Vector3::ZERO, Ogre::Node::TS_WORLD);
        camNode->attachObject(cam);

        // ビューポートの設定（背景色: 紺色）
        Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(0.1f, 0.2f, 0.4f));
        cam->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
            getRoot()->queueEndRendering();
        return true;
    }
};

int main()
{
    HelloOgreApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
