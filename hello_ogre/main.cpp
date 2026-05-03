#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <memory>
#include <vector>

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

// 四面体専用の回転アニメーション（キューブと逆向き・別軸）
class TetraRotator : public Ogre::FrameListener
{
    Ogre::SceneNode *mNode;

public:
    explicit TetraRotator(Ogre::SceneNode *node) : mNode(node) {}

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override
    {
        mNode->yaw(Ogre::Radian(-evt.timeSinceLastFrame * 1.1f));
        mNode->roll(Ogre::Radian(evt.timeSinceLastFrame * 0.9f));
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

// 球体が通過した軌跡にキラキラ粒子を残す FrameListener
class SparkleTrail : public Ogre::FrameListener
{
    struct SparkParticle
    {
        Ogre::Billboard *billboard;
        Ogre::Vector3 drift;
        float life;
        float maxLife;
        float baseSize;
        bool active;
    };

    Ogre::BillboardSet *mBillboardSet;
    std::vector<Ogre::SceneNode *> mEmitters;
    std::vector<SparkParticle> mParticles;
    float mSpawnAccumulator;

    void spawnParticle(const Ogre::Vector3 &origin)
    {
        for (auto &p : mParticles)
        {
            if (p.active)
                continue;

            const Ogre::Vector3 jitter(
                Ogre::Math::RangeRandom(-0.04f, 0.04f),
                Ogre::Math::RangeRandom(-0.04f, 0.04f),
                Ogre::Math::RangeRandom(-0.04f, 0.04f));

            p.active = true;
            p.life = 0.0f;
            p.maxLife = Ogre::Math::RangeRandom(0.35f, 0.75f);
            p.baseSize = Ogre::Math::RangeRandom(0.03f, 0.08f);
            p.drift = Ogre::Vector3(
                Ogre::Math::RangeRandom(-0.25f, 0.25f),
                Ogre::Math::RangeRandom(0.05f, 0.45f),
                Ogre::Math::RangeRandom(-0.25f, 0.25f));

            p.billboard->setPosition(origin + jitter);
            p.billboard->setDimensions(p.baseSize, p.baseSize);
            p.billboard->setColour(Ogre::ColourValue(
                Ogre::Math::RangeRandom(0.8f, 1.0f),
                Ogre::Math::RangeRandom(0.8f, 1.0f),
                Ogre::Math::RangeRandom(0.7f, 1.0f),
                0.45f));
            return;
        }
    }

public:
    SparkleTrail(Ogre::SceneManager *scnMgr,
                 Ogre::SceneNode *parentNode,
                 const std::vector<Ogre::SceneNode *> &emitters)
        : mBillboardSet(nullptr), mEmitters(emitters), mSpawnAccumulator(0.0f)
    {
        Ogre::MaterialPtr sparkleMat =
            Ogre::MaterialManager::getSingleton().getByName("SparkleMat");
        if (sparkleMat.isNull())
        {
            sparkleMat = Ogre::MaterialManager::getSingleton().create(
                "SparkleMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            Ogre::Pass *pass = sparkleMat->getTechnique(0)->getPass(0);
            pass->setLightingEnabled(false);
            pass->setVertexColourTracking(Ogre::TVC_DIFFUSE);
            pass->setSceneBlending(Ogre::SBT_ADD);
            pass->setDepthWriteEnabled(false);
            pass->setCullingMode(Ogre::CULL_NONE);
        }

        const size_t maxParticles = 900;
        mBillboardSet = scnMgr->createBillboardSet("SparkleTrailBB", maxParticles);
        mBillboardSet->setMaterialName("SparkleMat");
        mBillboardSet->setBillboardType(Ogre::BBT_POINT);
        parentNode->attachObject(mBillboardSet);

        mParticles.reserve(maxParticles);
        for (size_t i = 0; i < maxParticles; ++i)
        {
            Ogre::Billboard *bb = mBillboardSet->createBillboard(
                Ogre::Vector3::ZERO, Ogre::ColourValue(1.0f, 1.0f, 1.0f, 0.0f));
            bb->setDimensions(0.0f, 0.0f);
            mParticles.push_back({bb, Ogre::Vector3::ZERO, 0.0f, 0.0f, 0.0f, false});
        }
    }

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override
    {
        mSpawnAccumulator += evt.timeSinceLastFrame;
        const float spawnInterval = 0.016f;

        while (mSpawnAccumulator >= spawnInterval)
        {
            for (Ogre::SceneNode *emitter : mEmitters)
                spawnParticle(emitter->_getDerivedPosition());
            mSpawnAccumulator -= spawnInterval;
        }

        for (auto &p : mParticles)
        {
            if (!p.active)
                continue;

            p.life += evt.timeSinceLastFrame;
            if (p.life >= p.maxLife)
            {
                p.active = false;
                p.billboard->setDimensions(0.0f, 0.0f);
                p.billboard->setColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 0.0f));
                continue;
            }

            const float t = 1.0f - (p.life / p.maxLife);
            const float size = p.baseSize * (0.6f + 0.8f * t);
            Ogre::Vector3 pos = p.billboard->getPosition() + (p.drift * evt.timeSinceLastFrame);

            p.billboard->setPosition(pos);
            p.billboard->setDimensions(size, size);
            p.billboard->setColour(Ogre::ColourValue(
                Ogre::Math::RangeRandom(0.85f, 1.0f),
                Ogre::Math::RangeRandom(0.85f, 1.0f),
                Ogre::Math::RangeRandom(0.7f, 1.0f),
                t * 0.35f));
        }

        return true;
    }
};

// 背景に自動生成オーロラを描く FrameListener
class AuroraBackground : public Ogre::FrameListener
{
    Ogre::ManualObject *mAurora;
    float mTime;

    static constexpr int kSegments = 56;

    void buildAurora(bool isUpdate)
    {
        if (isUpdate)
            mAurora->beginUpdate(0);
        else
            mAurora->begin("AuroraMat", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

        for (int i = 0; i <= kSegments; ++i)
        {
            const float u = static_cast<float>(i) / static_cast<float>(kSegments);
            const float x = -8.0f + (16.0f * u);

            const float waveA = std::sin((x * 0.65f) + (mTime * 0.8f));
            const float waveB = std::sin((x * 1.35f) - (mTime * 1.2f));
            const float wave = (waveA * 0.7f) + (waveB * 0.3f);

            const float z = -7.0f + (0.35f * std::sin((x * 0.55f) + (mTime * 0.45f)));
            const float topY = 3.5f + (wave * 0.85f);
            const float bottomY = 0.2f + (wave * 0.2f);

            // 上側（明るめ）
            mAurora->position(x, topY, z);
            mAurora->colour(0.2f + (0.2f * u), 0.95f, 0.75f, 0.22f);

            // 下側（薄め）
            mAurora->position(x, bottomY, z);
            mAurora->colour(0.15f, 0.55f + (0.25f * u), 1.0f, 0.05f);
        }

        mAurora->end();
    }

public:
    AuroraBackground(Ogre::SceneManager *scnMgr, Ogre::SceneNode *parentNode)
        : mAurora(nullptr), mTime(0.0f)
    {
        Ogre::MaterialPtr auroraMat =
            Ogre::MaterialManager::getSingleton().getByName("AuroraMat");
        if (auroraMat.isNull())
        {
            auroraMat = Ogre::MaterialManager::getSingleton().create(
                "AuroraMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            Ogre::Pass *pass = auroraMat->getTechnique(0)->getPass(0);
            pass->setLightingEnabled(false);
            pass->setVertexColourTracking(Ogre::TVC_DIFFUSE);
            pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            pass->setDepthWriteEnabled(false);
            pass->setCullingMode(Ogre::CULL_NONE);
        }

        mAurora = scnMgr->createManualObject("AuroraCurtain");
        mAurora->setDynamic(true);
        buildAurora(false);
        parentNode->attachObject(mAurora);
    }

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override
    {
        mTime += evt.timeSinceLastFrame;
        buildAurora(true);
        return true;
    }
};

// 背景色をランダムターゲットへ徐々に遷移させる FrameListener
class BackgroundColorAnimator : public Ogre::FrameListener
{
    Ogre::Viewport *mViewport;
    Ogre::ColourValue mCurrent;
    Ogre::ColourValue mStart;
    Ogre::ColourValue mTarget;
    float mElapsed;
    float mDuration;

    void chooseNextTarget()
    {
        mStart = mCurrent;
        mTarget = Ogre::ColourValue(
            Ogre::Math::RangeRandom(0.02f, 0.18f),
            Ogre::Math::RangeRandom(0.02f, 0.18f),
            Ogre::Math::RangeRandom(0.05f, 0.25f));
        mDuration = Ogre::Math::RangeRandom(3.5f, 7.0f);
        mElapsed = 0.0f;
    }

public:
    explicit BackgroundColorAnimator(Ogre::Viewport *viewport)
        : mViewport(viewport),
          mCurrent(0.03f, 0.03f, 0.08f),
          mStart(mCurrent),
          mTarget(mCurrent),
          mElapsed(0.0f),
          mDuration(1.0f)
    {
        mViewport->setBackgroundColour(mCurrent);
        chooseNextTarget();
    }

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override
    {
        mElapsed += evt.timeSinceLastFrame;
        float t = mElapsed / mDuration;
        if (t > 1.0f)
            t = 1.0f;

        // 急な色変化を避けるための smoothstep 補間
        const float smooth = t * t * (3.0f - (2.0f * t));
        mCurrent.r = mStart.r + ((mTarget.r - mStart.r) * smooth);
        mCurrent.g = mStart.g + ((mTarget.g - mStart.g) * smooth);
        mCurrent.b = mStart.b + ((mTarget.b - mStart.b) * smooth);
        mViewport->setBackgroundColour(mCurrent);

        if (t >= 1.0f)
            chooseNextTarget();

        return true;
    }
};

class HelloOgre : public OgreBites::ApplicationContext,
                  public OgreBites::InputListener
{
    std::unique_ptr<CubeRotator> mRotator;
    std::unique_ptr<TetraRotator> mTetraRotator;
    std::unique_ptr<BallOrbiter> mBallOrbiter;
    std::unique_ptr<BallOrbiter> mBallOrbiter2;
    std::unique_ptr<BallOrbiter> mBallOrbiter3;
    std::unique_ptr<SparkleTrail> mSparkleTrail;
    std::unique_ptr<AuroraBackground> mAuroraBackground;
    std::unique_ptr<BackgroundColorAnimator> mBackgroundColorAnimator;

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
        Ogre::Viewport *mainViewport = getRenderWindow()->addViewport(cam);
        mBackgroundColorAnimator =
            std::make_unique<BackgroundColorAnimator>(mainViewport);
        root->addFrameListener(mBackgroundColorAnimator.get());

        // 環境光（全体照明）
        scnMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

        // 背景オーロラ
        Ogre::SceneNode *auroraNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        mAuroraBackground = std::make_unique<AuroraBackground>(scnMgr, auroraNode);
        root->addFrameListener(mAuroraBackground.get());

        // 頂点カラーを確実に使うマテリアルを新規作成
        Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(
            "CubeNoCull", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        Ogre::Pass *cubePass = mat->getTechnique(0)->getPass(0);
        cubePass->setLightingEnabled(false);
        cubePass->setVertexColourTracking(Ogre::TVC_DIFFUSE);
        cubePass->setCullingMode(Ogre::CULL_NONE);

        // キューブだけ半透明にする専用マテリアル
        Ogre::MaterialPtr cubeTransparentMat = Ogre::MaterialManager::getSingleton().create(
            "CubeTransparent", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        Ogre::Pass *cubeTransparentPass = cubeTransparentMat->getTechnique(0)->getPass(0);
        cubeTransparentPass->setLightingEnabled(false);
        cubeTransparentPass->setVertexColourTracking(Ogre::TVC_DIFFUSE);
        cubeTransparentPass->setCullingMode(Ogre::CULL_NONE);
        cubeTransparentPass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        cubeTransparentPass->setDepthWriteEnabled(false);

        // ManualObject で頂点カラー付き立方体を作成
        Ogre::ManualObject *cube = scnMgr->createManualObject("Cube");
        cube->begin("CubeTransparent", Ogre::RenderOperation::OT_TRIANGLE_LIST);

        // 前面 (z = +0.5)
        cube->position(-0.5f, -0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f, 0.28f);
        cube->position(0.5f, -0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f, 0.28f);
        cube->position(0.5f, 0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f, 0.28f);
        cube->position(-0.5f, 0.5f, 0.5f);
        cube->colour(0.0f, 1.0f, 0.0f, 0.28f);

        // 背面 (z = -0.5)
        cube->position(0.5f, -0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f, 0.28f);
        cube->position(-0.5f, -0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f, 0.28f);
        cube->position(-0.5f, 0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f, 0.28f);
        cube->position(0.5f, 0.5f, -0.5f);
        cube->colour(0.0f, 0.0f, 1.0f, 0.28f);

        // 上面 (y = +0.5)
        cube->position(-0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 1.0f, 0.28f);
        cube->position(0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 1.0f, 0.28f);
        cube->position(0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 1.0f, 0.28f);
        cube->position(-0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 1.0f, 0.28f);

        // 下面 (y = -0.5)
        cube->position(-0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 0.0f, 0.28f);
        cube->position(0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 1.0f, 0.0f, 0.28f);
        cube->position(0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 0.0f, 0.28f);
        cube->position(-0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 1.0f, 0.0f, 0.28f);

        // 右面 (x = +0.5)
        cube->position(0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 0.0f, 0.0f, 0.28f);
        cube->position(0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 0.0f, 0.0f, 0.28f);
        cube->position(0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 0.0f, 0.0f, 0.28f);
        cube->position(0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 0.0f, 0.0f, 0.28f);

        // 左面 (x = -0.5)
        cube->position(-0.5f, -0.5f, -0.5f);
        cube->colour(1.0f, 0.5f, 0.0f, 0.28f);
        cube->position(-0.5f, -0.5f, 0.5f);
        cube->colour(1.0f, 0.5f, 0.0f, 0.28f);
        cube->position(-0.5f, 0.5f, 0.5f);
        cube->colour(1.0f, 0.5f, 0.0f, 0.28f);
        cube->position(-0.5f, 0.5f, -0.5f);
        cube->colour(1.0f, 0.5f, 0.0f, 0.28f);

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

        // キューブ内部に正三角錐（四面体）を配置
        Ogre::ManualObject *tetra = scnMgr->createManualObject("InnerTetra");
        tetra->begin("CubeNoCull", Ogre::RenderOperation::OT_TRIANGLE_LIST);

        const Ogre::Vector3 t0(0.0f, 0.6f, 0.0f);
        const Ogre::Vector3 t1(-0.55f, -0.3f, 0.45f);
        const Ogre::Vector3 t2(0.55f, -0.3f, 0.45f);
        const Ogre::Vector3 t3(0.0f, -0.3f, -0.6f);

        auto addTetraFace = [&](const Ogre::Vector3 &a, const Ogre::Vector3 &b,
                                const Ogre::Vector3 &c, const Ogre::ColourValue &col)
        {
            tetra->position(a);
            tetra->colour(col);
            tetra->position(b);
            tetra->colour(col);
            tetra->position(c);
            tetra->colour(col);
        };

        addTetraFace(t0, t1, t2, Ogre::ColourValue(1.0f, 0.2f, 0.2f));
        addTetraFace(t0, t2, t3, Ogre::ColourValue(0.2f, 1.0f, 0.2f));
        addTetraFace(t0, t3, t1, Ogre::ColourValue(0.2f, 0.6f, 1.0f));
        addTetraFace(t1, t3, t2, Ogre::ColourValue(1.0f, 1.0f, 0.2f));

        for (Ogre::uint32 i = 0; i < 4; ++i)
        {
            Ogre::uint32 base = i * 3;
            tetra->index(base);
            tetra->index(base + 1);
            tetra->index(base + 2);
        }
        tetra->end();

        Ogre::SceneNode *tetraNode = cubeNode->createChildSceneNode();
        tetraNode->setScale(0.55f, 0.55f, 0.55f);
        tetraNode->attachObject(tetra);

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
        mTetraRotator = std::make_unique<TetraRotator>(tetraNode);
        root->addFrameListener(mTetraRotator.get());
        mBallOrbiter = std::make_unique<BallOrbiter>(orbitNode, -1.2f);
        root->addFrameListener(mBallOrbiter.get());
        mBallOrbiter2 = std::make_unique<BallOrbiter>(orbitNode2, -0.9f);
        root->addFrameListener(mBallOrbiter2.get());
        mBallOrbiter3 = std::make_unique<BallOrbiter>(orbitNode3, -0.7f);
        root->addFrameListener(mBallOrbiter3.get());

        std::vector<Ogre::SceneNode *> sparkleEmitters = {ballNode, ballNode2, ballNode3};
        Ogre::SceneNode *sparkleNode =
            scnMgr->getRootSceneNode()->createChildSceneNode();
        mSparkleTrail =
            std::make_unique<SparkleTrail>(scnMgr, sparkleNode, sparkleEmitters);
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
