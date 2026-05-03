#pragma once

#include <Ogre.h>
#include <vector>

namespace demo
{

class CubeRotator : public Ogre::FrameListener
{
    Ogre::SceneNode *mNode;

public:
    explicit CubeRotator(Ogre::SceneNode *node);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

class TetraRotator : public Ogre::FrameListener
{
    Ogre::SceneNode *mNode;

public:
    explicit TetraRotator(Ogre::SceneNode *node);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

class BallOrbiter : public Ogre::FrameListener
{
    Ogre::SceneNode *mOrbitNode;
    float mAngularSpeed;

public:
    BallOrbiter(Ogre::SceneNode *orbitNode, float angularSpeed);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

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

    void spawnParticle(const Ogre::Vector3 &origin);

public:
    SparkleTrail(Ogre::SceneManager *scnMgr,
                 Ogre::SceneNode *parentNode,
                 const std::vector<Ogre::SceneNode *> &emitters);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

class AuroraBackground : public Ogre::FrameListener
{
    Ogre::ManualObject *mAurora;
    float mTime;

    static constexpr int kSegments = 56;
    void buildAurora(bool isUpdate);

public:
    AuroraBackground(Ogre::SceneManager *scnMgr, Ogre::SceneNode *parentNode);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

class BackgroundColorAnimator : public Ogre::FrameListener
{
    Ogre::Viewport *mViewport;
    Ogre::ColourValue mCurrent;
    Ogre::ColourValue mStart;
    Ogre::ColourValue mTarget;
    float mElapsed;
    float mDuration;

    void chooseNextTarget();

public:
    explicit BackgroundColorAnimator(Ogre::Viewport *viewport);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

class CameraFocusAnimator : public Ogre::FrameListener
{
    Ogre::SceneNode *mCameraNode;
    Ogre::SceneNode *mTargetNode;
    float mTime;

public:
    CameraFocusAnimator(Ogre::SceneNode *cameraNode, Ogre::SceneNode *targetNode);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
};

void createFieldCage(Ogre::SceneManager *scnMgr);
Ogre::SceneNode *createCubeNode(Ogre::SceneManager *scnMgr);
Ogre::SceneNode *createInnerTetraNode(Ogre::SceneManager *scnMgr, Ogre::SceneNode *cubeNode);
Ogre::ManualObject *createBall(Ogre::SceneManager *scnMgr,
                               const Ogre::String &name,
                               const Ogre::ColourValue &color);

} // namespace demo
