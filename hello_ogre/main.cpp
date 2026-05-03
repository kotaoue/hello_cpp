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

// キューブ中心を基準に、ボールを逆回転で周回させる FrameListener
class BallOrbiter : public Ogre::FrameListener
{
    Ogre::SceneNode *mOrbitNode;
    float mAngularSpeed;

public:
    BallOrbiter(Ogre::SceneNode *orbitNode, float angularSpeed)
        : mOrbitNode(orbitNode), mAngularSpeed(angularSpeed) {}

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override
    {
        mOrbitNode->yaw(Ogre::Radian(evt.timeSinceLastFrame * mAngularSpeed));
        return true;
    }
};

class HelloOgre : public OgreBites::ApplicationContext,
                  public OgreBites::InputListener
{
    std::unique_ptr<CubeRotator> mRotator;
    std::unique_ptr<BallOrbiter> mBallOrbiter;
    std::unique_ptr<BallOrbiter> mBallOrbiter2;
    std::unique_ptr<BallOrbiter> mBallOrbiter3;

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
        cubeNode->setScale(1.0f, 1.0f, 1.0f);

        // 低分割の球体 ManualObject を作成するヘルパー
        auto createBall = [&](const Ogre::String &name, const Ogre::ColourValue &color)
        {
            Ogre::ManualObject *obj = scnMgr->createManualObject(name);
            obj->begin("CubeNoCull", Ogre::RenderOperation::OT_TRIANGLE_LIST);
            const int stacks = 12;
            const int slices = 18;
            for (int i = 0; i <= stacks; ++i)
            {
                const float v = static_cast<float>(i) / static_cast<float>(stacks);
                const float phi = Ogre::Math::PI * v;
                const float y = std::cos(phi);
                const float r = std::sin(phi);

                for (int j = 0; j <= slices; ++j)
                {
                    const float u = static_cast<float>(j) / static_cast<float>(slices);
                    const float theta = Ogre::Math::TWO_PI * u;
                    const float x = r * std::cos(theta);
                    const float z = r * std::sin(theta);

                    obj->position(0.5f * x, 0.5f * y, 0.5f * z);
                    obj->colour(color);
                }
            }

            for (int i = 0; i < stacks; ++i)
            {
                for (int j = 0; j < slices; ++j)
                {
                    const int row1 = i * (slices + 1);
                    const int row2 = (i + 1) * (slices + 1);
                    const Ogre::uint32 a = static_cast<Ogre::uint32>(row1 + j);
                    const Ogre::uint32 b = static_cast<Ogre::uint32>(row1 + j + 1);
                    const Ogre::uint32 c = static_cast<Ogre::uint32>(row2 + j);
                    const Ogre::uint32 d = static_cast<Ogre::uint32>(row2 + j + 1);

                    obj->index(a);
                    obj->index(c);
                    obj->index(b);
                    obj->index(b);
                    obj->index(c);
                    obj->index(d);
                }
            }
            obj->end();
            return obj;
        };

        Ogre::ManualObject *ball =
            createBall("Ball", Ogre::ColourValue(1.0f, 1.0f, 1.0f));
        Ogre::ManualObject *ball2 =
            createBall("Ball2", Ogre::ColourValue(1.0f, 0.8f, 0.2f));
        Ogre::ManualObject *ball3 =
            createBall("Ball3", Ogre::ColourValue(0.3f, 1.0f, 1.0f));

        // キューブ中心を公転中心にした周回ノードを作り、ボールを配置
        Ogre::SceneNode *orbitNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        Ogre::SceneNode *ballNode = orbitNode->createChildSceneNode();
        ballNode->setPosition(2.0f, 0.0f, 0.0f);
        ballNode->setScale(0.2f, 0.2f, 0.2f);
        ballNode->attachObject(ball);

        // 2つ目は軌道面を傾け、半径を変えて衝突しないようにする
        Ogre::SceneNode *orbitNode2 =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        orbitNode2->pitch(Ogre::Degree(35.0f));
        Ogre::SceneNode *ballNode2 = orbitNode2->createChildSceneNode();
        ballNode2->setPosition(-2.6f, 0.0f, 0.0f);
        ballNode2->setScale(0.2f, 0.2f, 0.2f);
        ballNode2->attachObject(ball2);

        // 3つ目はさらに別の軌道面・半径で配置
        Ogre::SceneNode *orbitNode3 =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        orbitNode3->roll(Ogre::Degree(50.0f));
        Ogre::SceneNode *ballNode3 = orbitNode3->createChildSceneNode();
        ballNode3->setPosition(0.0f, 0.0f, 3.2f);
        ballNode3->setScale(0.2f, 0.2f, 0.2f);
        ballNode3->attachObject(ball3);

        // 回転アニメーションを登録
        mRotator = std::make_unique<CubeRotator>(cubeNode);
        root->addFrameListener(mRotator.get());
        mBallOrbiter = std::make_unique<BallOrbiter>(orbitNode, -1.2f);
        root->addFrameListener(mBallOrbiter.get());
        mBallOrbiter2 = std::make_unique<BallOrbiter>(orbitNode2, -0.9f);
        root->addFrameListener(mBallOrbiter2.get());
        mBallOrbiter3 = std::make_unique<BallOrbiter>(orbitNode3, -0.7f);
        root->addFrameListener(mBallOrbiter3.get());
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
