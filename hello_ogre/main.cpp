#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <memory>

// 回転アニメーション用の FrameListener
class CubeRotator : public Ogre::FrameListener
{
    Ogre::SceneNode *mNode;

public:
    explicit CubeRotator(Ogre::SceneNode *node) : mNode(node) {}

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override
    {
        mNode->yaw(Ogre::Radian(evt.timeSinceLastFrame));
        mNode->pitch(Ogre::Radian(evt.timeSinceLastFrame * 0.5f));
        return true;
    }
};

class HelloOgre : public OgreBites::ApplicationContext,
                  public OgreBites::InputListener
{
    std::unique_ptr<CubeRotator> mRotator;

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

        // RTShader システムへのシーン登録
        Ogre::RTShader::ShaderGenerator *shadergen =
            Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // カメラの設定
        Ogre::SceneNode *camNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0.0f, 0.0f, 6.0f);
        camNode->lookAt(Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Node::TS_WORLD);

        Ogre::Camera *cam = scnMgr->createCamera("MainCam");
        cam->setNearClipDistance(0.1f);
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        getRenderWindow()->addViewport(cam);

        // 環境光（全体照明）
        scnMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

        // 頂点カラーを確実に使うマテリアルを新規作成
        Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(
            "CubeNoCull", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        Ogre::Pass *cubePass = mat->getTechnique(0)->getPass(0);
        cubePass->setLightingEnabled(false);
        cubePass->setVertexColourTracking(Ogre::TVC_DIFFUSE);
        cubePass->setCullingMode(Ogre::CULL_NONE);

        // ManualObject で頂点カラー付き立方体を作成
        Ogre::ManualObject *cube = scnMgr->createManualObject("Cube");
        cube->begin("CubeNoCull", Ogre::RenderOperation::OT_TRIANGLE_LIST);

        // 前面 (z = +0.5)
        cube->position(-0.5f, -0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f);
        cube->position(0.5f, -0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f);
        cube->position(0.5f, 0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f);
        cube->position(-0.5f, 0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f);

        // 背面 (z = -0.5)
        cube->position(0.5f, -0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f);
        cube->position(-0.5f, -0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f);
        cube->position(-0.5f, 0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f);
        cube->position(0.5f, 0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f);

        // 上面 (y = +0.5)
        cube->position(-0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 1.0f);
        cube->position(0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 1.0f);
        cube->position(0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 1.0f);
        cube->position(-0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 1.0f);

        // 下面 (y = -0.5)
        cube->position(-0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 0.0f);
        cube->position(0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 0.0f);
        cube->position(0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 0.0f);
        cube->position(-0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 0.0f);

        // 右面 (x = +0.5)
        cube->position(0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 0.0f, 0.0f);
        cube->position(0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 0.0f, 0.0f);
        cube->position(0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 0.0f, 0.0f);
        cube->position(0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 0.0f, 0.0f);

        // 左面 (x = -0.5)
        cube->position(-0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 0.5f, 0.0f);
        cube->position(-0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 0.5f, 0.0f);
        cube->position(-0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 0.5f, 0.0f);
        cube->position(-0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 0.5f, 0.0f);

        // 各面 2 三角形 × 6 面のインデックス
        for (Ogre::uint32 i = 0; i < 6; ++i)
        {
            Ogre::uint32 base = i * 4;
            cube->index(base);
            cube->index(base + 1);
            cube->index(base + 2);
            cube->index(base);
            cube->index(base + 2);
            cube->index(base + 3);
        }
        cube->end();

        Ogre::SceneNode *cubeNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        cubeNode->attachObject(cube);
        cubeNode->setScale(0.6f, 0.6f, 0.6f);

        // 回転アニメーションを登録
        mRotator = std::make_unique<CubeRotator>(cubeNode);
        root->addFrameListener(mRotator.get());
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
