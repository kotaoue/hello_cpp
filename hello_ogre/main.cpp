#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>

#include <memory>
#include <vector>

#include "scene_components.h"

class HelloOgre : public OgreBites::ApplicationContext,
                  public OgreBites::InputListener
{
    std::unique_ptr<demo::CubeRotator> mRotator;
    std::unique_ptr<demo::TetraRotator> mTetraRotator;
    std::unique_ptr<demo::BallOrbiter> mBallOrbiter;
    std::unique_ptr<demo::BallOrbiter> mBallOrbiter2;
    std::unique_ptr<demo::BallOrbiter> mBallOrbiter3;
    std::unique_ptr<demo::SparkleTrail> mSparkleTrail;
    std::unique_ptr<demo::AuroraBackground> mAuroraBackground;
    std::unique_ptr<demo::BackgroundColorAnimator> mBackgroundColorAnimator;
    std::unique_ptr<demo::CameraFocusAnimator> mCameraFocusAnimator;

public:
    HelloOgre() : OgreBites::ApplicationContext("Hello OGRE") {}

    bool oneTimeConfig() override
    {
        Ogre::Root *root = getRoot();
        Ogre::RenderSystem *rs =
            root->getRenderSystemByName("OpenGL 3+ Rendering Subsystem");
        if (!rs)
            rs = root->getRenderSystemByName("OpenGL Rendering Subsystem");
        if (!rs)
            return false;
        root->setRenderSystem(rs);
        return true;
    }

    void setup() override
    {
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        Ogre::Root *root = getRoot();
        Ogre::SceneManager *scnMgr = root->createSceneManager();

        Ogre::RTShader::ShaderGenerator *shadergen =
            Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        Ogre::SceneNode *camNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0.0f, 0.0f, 6.0f);
        camNode->lookAt(Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Node::TS_WORLD);

        Ogre::Camera *cam = scnMgr->createCamera("MainCam");
        cam->setNearClipDistance(0.1f);
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        Ogre::Viewport *mainViewport = getRenderWindow()->addViewport(cam);
        mBackgroundColorAnimator =
            std::make_unique<demo::BackgroundColorAnimator>(mainViewport);
        root->addFrameListener(mBackgroundColorAnimator.get());

        scnMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

        Ogre::SceneNode *auroraNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        mAuroraBackground = std::make_unique<demo::AuroraBackground>(scnMgr, auroraNode);
        root->addFrameListener(mAuroraBackground.get());

        demo::createFieldCage(scnMgr);

        Ogre::SceneNode *cubeNode = demo::createCubeNode(scnMgr);
        Ogre::SceneNode *tetraNode = demo::createInnerTetraNode(scnMgr, cubeNode);

        mCameraFocusAnimator = std::make_unique<demo::CameraFocusAnimator>(camNode, cubeNode);
        root->addFrameListener(mCameraFocusAnimator.get());

        Ogre::ManualObject *ball =
            demo::createBall(scnMgr, "Ball", Ogre::ColourValue(1.0f, 1.0f, 1.0f));
        Ogre::ManualObject *ball2 =
            demo::createBall(scnMgr, "Ball2", Ogre::ColourValue(1.0f, 0.8f, 0.2f));
        Ogre::ManualObject *ball3 =
            demo::createBall(scnMgr, "Ball3", Ogre::ColourValue(0.3f, 1.0f, 1.0f));

        Ogre::SceneNode *orbitNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        Ogre::SceneNode *ballNode = orbitNode->createChildSceneNode();
        ballNode->setPosition(2.0f, 0.0f, 0.0f);
        ballNode->setScale(0.2f, 0.2f, 0.2f);
        ballNode->attachObject(ball);

        Ogre::SceneNode *orbitNode2 =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        orbitNode2->pitch(Ogre::Degree(35.0f));
        Ogre::SceneNode *ballNode2 = orbitNode2->createChildSceneNode();
        ballNode2->setPosition(-2.6f, 0.0f, 0.0f);
        ballNode2->setScale(0.2f, 0.2f, 0.2f);
        ballNode2->attachObject(ball2);

        Ogre::SceneNode *orbitNode3 =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        orbitNode3->roll(Ogre::Degree(50.0f));
        Ogre::SceneNode *ballNode3 = orbitNode3->createChildSceneNode();
        ballNode3->setPosition(0.0f, 0.0f, 3.2f);
        ballNode3->setScale(0.2f, 0.2f, 0.2f);
        ballNode3->attachObject(ball3);

        mRotator = std::make_unique<demo::CubeRotator>(cubeNode);
        root->addFrameListener(mRotator.get());
        mTetraRotator = std::make_unique<demo::TetraRotator>(tetraNode);
        root->addFrameListener(mTetraRotator.get());
        mBallOrbiter = std::make_unique<demo::BallOrbiter>(orbitNode, -1.2f);
        root->addFrameListener(mBallOrbiter.get());
        mBallOrbiter2 = std::make_unique<demo::BallOrbiter>(orbitNode2, -0.9f);
        root->addFrameListener(mBallOrbiter2.get());
        mBallOrbiter3 = std::make_unique<demo::BallOrbiter>(orbitNode3, -0.7f);
        root->addFrameListener(mBallOrbiter3.get());

        std::vector<Ogre::SceneNode *> sparkleEmitters = {ballNode, ballNode2, ballNode3};
        Ogre::SceneNode *sparkleNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        mSparkleTrail =
            std::make_unique<demo::SparkleTrail>(scnMgr, sparkleNode, sparkleEmitters);
        root->addFrameListener(mSparkleTrail.get());
    }

    bool keyPressed(const OgreBites::KeyboardEvent &evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
            getRoot()->queueEndRendering();
        return true;
    }
};

int main()
{
    HelloOgre app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
