#ifndef __TODPARTICLE_H__
#define __TODPARTICLE_H__

#include "TodList.h"
#include "DataArray.h"
#include "../SexyAppFramework/SexyVector.h"
namespace Sexy
{
	class Image;
	class Graphics;
};
using namespace std;
using namespace Sexy;

#define MAX_PARTICLES_SIZE 900
#define MAX_PARTICLE_FIELDS 4

// ######################################################################################################################################################
// ############################################################# 以下为粒子系统定义相关内容 #############################################################
// ######################################################################################################################################################

enum ParticleFlags
{
    PARTICLE_RANDOM_LAUNCH_SPIN,        // Random emission rotation, specifying that the particle uses a random initial rotation angle within [0, 2π] when emitting
    PARTICLE_ALIGN_LAUNCH_SPIN,         // Align the emission angle, specifying that the initial rotation angle of the particle when emitted is consistent with the emission direction (the priority is lower than the random emission rotation)
    PARTICLE_ALIGN_TO_PIXELS,           // Align to pixels, specifies that the coordinates of particles when rendering are rounded and aligned to integer pixel values.
    PARTICLE_SYSTEM_LOOPS,              // System loop, specifying that the emitter returns to the start of the cycle immediately after the end of the life cycle
    PARTICLE_PARTICLE_LOOPS,            // Particle loop, specifying that the particle will return to the start of the cycle immediately after the end of the life cycle.
    PARTICLE_PARTICLES_DONT_FOLLOW,     // Particles do not follow, specifying that when the position of the particle emitter moves, the emitted particles will not move with it.
    PARTICLE_RANDOM_START_TIME,         // Random initial time, specifying that the initial existence time of the particle is a random value between 0 and the maximum duration.
    PARTICLE_DIE_IF_OVERLOADED,         // Overload limit, which specifies that when the number of particles is too large, the particle system to which the emitter belongs cannot be created.
    PARTICLE_ADDITIVE,                  // Additive mode, fixed use of Additive mode when specifying particle rendering
    PARTICLE_FULLSCREEN,                // Full screen mode, specifies that particles will fill a screen-sized rectangle when rendering.
    PARTICLE_SOFTWARE_ONLY,             // Software rendering only, the specified particles can only be rendered when 3D acceleration is not turned on
    PARTICLE_HARDWARE_ONLY              // Hardware rendering only, the specified particles can only be rendered when 3D acceleration is turned on
};

enum ParticleFieldType
{
    FIELD_INVALID,
    FIELD_FRICTION,                     // Friction field: the speed of particles in this field continues to decay at a certain proportion
    FIELD_ACCELERATION,                 // Acceleration field: Particles in this field accelerate with a certain acceleration.
    FIELD_ATTRACTOR,                    // Elastic force field: The magnitude and direction of particle acceleration in this field are affected by the distance between the particle and the emitter
    FIELD_MAX_VELOCITY,                 // Velocity-limiting field: The velocity of particles in this field cannot exceed a certain upper limit.
    FIELD_VELOCITY,                     // Uniform velocity field: the velocity of particles in this field is always a given value
    FIELD_POSITION,                     // Positioning field: The position of particles in this field is always a given value
    FIELD_SYSTEM_POSITION,              // System positioning field: only available for transmitters, the position of the transmitter in this field is always a given value
    FIELD_GROUND_CONSTRAINT,            // Ground restrictions: The longitudinal position of particles cannot be lower than the ground, and the bounce effect will be triggered when touching the ground.
    FIELD_SHAKE,                        // Vibration: The coordinates of the particles will have a random offset from -1.0 to +1.0, calculated independently for each frame
    FIELD_CIRCLE,                       // Gravitational field: Particles in this field make circular motion around the center of the emitter (taking into account the error, it is actually a spiral motion)
    FIELD_AWAY,                         // Repulsion field: Particles in this field continue to move away from the center of the emitter in the radial direction
    PARTICLE_FIELD_COUNT
};  // For details about the particle field, please see the TodParticleEmitter::UpdateParticleField() function (the system positioning field is the TodParticleEmitter::UpdateSystemField() function)

// ################################################################################
// ▲ The following is an example of the correspondence between various types of instances related to particle system definitions and formats in XML.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <Emitter>                                                         —
//                       ↓←Node→↓                                ↑
//     <SpawnRate>[.5 2] [2.5 4.5],40 [5 10]</SpawnRate>    TodEmitterDefinition
//     ↑←      FloatParameterTrack::mNodes        →↑             ↓
// </Emitter>                                                        —
// ################################################################################
// 【!】Defined items that are not given in the XML will be assigned the default value of the item after the reading is completed.

// ====================================================================================================
// ★ [Floating point parameter track node]
// ----------------------------------------------------------------------------------------------------
// Each node describes a stage in which the attribute value changes over time.
// ====================================================================================================
class FloatParameterTrackNode
{
public:
    float                       mTime;                          // phase start time
    float                       mLowValue;                      // Minimum value allowed for data within the stage
    float                       mHighValue;                     // The maximum value allowed for data within the stage
    TodCurves                   mCurveType;                     // Easing effect curve transitioning from the current stage to the next stage
    TodCurves                   mDistribution;                  // The probability distribution curve of the data within the stage between the minimum value and the maximum value
};

// ====================================================================================================
// ★ [Floating point parameter track]
// ----------------------------------------------------------------------------------------------------
// Each track describes the change pattern and value range of an attribute of the transmitter over time.
// ====================================================================================================
class FloatParameterTrack
{
public:
    FloatParameterTrackNode*    mNodes;
    int                         mCountNodes;
};

// ====================================================================================================
// ★ 【Particle Field】
// ----------------------------------------------------------------------------------------------------
// The physical environment in which the particles in the emitter move. Multiple particle fields can be superimposed, up to 4 of them.
// ====================================================================================================
class ParticleField
{
public:
    ParticleFieldType           mFieldType;                     // The type of field determines how the field affects particle motion.
    FloatParameterTrack         mX;                             // Effect of fields on particles in the horizontal direction (transverse direction)
    FloatParameterTrack         mY;                             // Effect of fields on particles in the vertical direction (longitudinal)
};

// ====================================================================================================
// ★ [Transmitter definition]
// ----------------------------------------------------------------------------------------------------
// The definition data of a particle emitter describes the variation patterns and ranges of parameters for its various behaviors.
// ====================================================================================================
class TodEmitterDefinition
{
public:
    Image*                      mImage;
    int                         mImageCol;
    int                         mImageRow;
    int                         mImageFrames;
    int                         mAnimated;
    int                         mParticleFlags;
    EmitterType                 mEmitterType;
    const char*                 mName;
    const char*                 mOnDuration;
    FloatParameterTrack         mSystemDuration;
    FloatParameterTrack         mCrossFadeDuration;
    FloatParameterTrack         mSpawnRate;
    FloatParameterTrack         mSpawnMinActive;
    FloatParameterTrack         mSpawnMaxActive;
    FloatParameterTrack         mSpawnMaxLaunched;
    FloatParameterTrack         mEmitterRadius;
    FloatParameterTrack         mEmitterOffsetX;
    FloatParameterTrack         mEmitterOffsetY;
    FloatParameterTrack         mEmitterBoxX;
    FloatParameterTrack         mEmitterBoxY;
    FloatParameterTrack         mEmitterSkewX;
    FloatParameterTrack         mEmitterSkewY;
    FloatParameterTrack         mEmitterPath;
    FloatParameterTrack         mParticleDuration;
    FloatParameterTrack         mLaunchSpeed;
    FloatParameterTrack         mLaunchAngle;
    FloatParameterTrack         mSystemRed;
    FloatParameterTrack         mSystemGreen;
    FloatParameterTrack         mSystemBlue;
    FloatParameterTrack         mSystemAlpha;
    FloatParameterTrack         mSystemBrightness;
    ParticleField*              mParticleFields;
    int                         mParticleFieldCount;
    ParticleField*              mSystemFields;
    int                         mSystemFieldCount;
    FloatParameterTrack         mParticleRed;
    FloatParameterTrack         mParticleGreen;
    FloatParameterTrack         mParticleBlue;
    FloatParameterTrack         mParticleAlpha;
    FloatParameterTrack         mParticleBrightness;
    FloatParameterTrack         mParticleSpinAngle;
    FloatParameterTrack         mParticleSpinSpeed;
    FloatParameterTrack         mParticleScale;
    FloatParameterTrack         mParticleStretch;
    FloatParameterTrack         mCollisionReflect;
    FloatParameterTrack         mCollisionSpin;
    FloatParameterTrack         mClipTop;
    FloatParameterTrack         mClipBottom;
    FloatParameterTrack         mClipLeft;
    FloatParameterTrack         mClipRight;
    FloatParameterTrack         mAnimationRate;
};

// ====================================================================================================
// ★ [Particle system definition]
// ----------------------------------------------------------------------------------------------------
// The definition data of the particle system is a collection of definition data of each particle emitter in the particle system.
// ====================================================================================================
class TodParticleDefinition
{
public:
    TodEmitterDefinition*       mEmitterDefs;
    int                         mEmitterDefCount;
};

extern int gParticleDefCount;                       // [0x6A9F08]
extern TodParticleDefinition* gParticleDefArray;    // [0x6A9F0C]. Read and assign value in LawnApp::LoadingThreadProc() function

// ====================================================================================================
// ★ 【Particle parameters】
// ----------------------------------------------------------------------------------------------------
// Used to describe the correspondence between a particle system type and the file name of the particle system's data file.
// ====================================================================================================
class ParticleParams
{
public:
    ParticleEffect              mParticleEffect;
    const char*                 mParticleFileName;
};
extern int gParticleParamArraySize;                 // [0x6A9F10]
extern ParticleParams* gParticleParamArray;         // [0x6A9F14]

bool                            TodParticleLoadADef(TodParticleDefinition* theParticleDef, const char* theParticleFileName);
void                            TodParticleLoadDefinitions(ParticleParams* theParticleParamArray, int theParticleParamArraySize);
void                            TodParticleFreeDefinitions();

extern ParticleParams gLawnParticleArray[(int)ParticleEffect::NUM_PARTICLES];  // 0x6A0FF0

// ######################################################################################################################################################
// ############################################################ The following officially begins the particle system related announcements ############################################################
// ######################################################################################################################################################

enum ParticleSystemTracks
{
	TRACK_SPAWN_RATE,
	TRACK_SPAWN_MIN_ACTIVE,
	TRACK_SPAWN_MAX_ACTIVE,
	TRACK_SPAWN_MAX_LAUNCHED,
	TRACK_EMITTER_PATH,
	TRACK_SYSTEM_RED,
	TRACK_SYSTEM_GREEN,
	TRACK_SYSTEM_BLUE,
	TRACK_SYSTEM_ALPHA,
	TRACK_SYSTEM_BRIGHTNESS,
	NUM_SYSTEM_TRACKS
};

enum ParticleTracks
{
	TRACK_PARTICLE_RED,
	TRACK_PARTICLE_GREEN,
	TRACK_PARTICLE_BLUE,
	TRACK_PARTICLE_ALPHA,
	TRACK_PARTICLE_BRIGHTNESS,
	TRACK_PARTICLE_SPIN_SPEED,
	TRACK_PARTICLE_SPIN_ANGLE,
	TRACK_PARTICLE_SCALE,
	TRACK_PARTICLE_STRETCH,
	TRACK_PARTICLE_COLLISION_REFLECT,
	TRACK_PARTICLE_COLLISION_SPIN,
	TRACK_PARTICLE_CLIP_TOP,
	TRACK_PARTICLE_CLIP_BOTTOM,
	TRACK_PARTICLE_CLIP_LEFT,
	TRACK_PARTICLE_CLIP_RIGHT,
	TRACK_PARTICLE_ANIMATION_RATE,
	NUM_PARTICLE_TRACKS
};

class TodParticleSystem;
class TodParticleEmitter;
class TodParticle;
class TodParticleHolder
{
public:
	DataArray<TodParticleSystem>	mParticleSystems;
	DataArray<TodParticleEmitter>	mEmitters;
	DataArray<TodParticle>			mParticles;
	TodAllocator					mParticleListNodeAllocator;
	TodAllocator					mEmitterListNodeAllocator;

public:
    ~TodParticleHolder();

    void							InitializeHolder();
    void							DisposeHolder();
    TodParticleSystem*				AllocParticleSystemFromDef(float theX, float theY, int theRenderOrder, TodParticleDefinition* theDefinition, ParticleEffect theParticleEffect);
    TodParticleSystem*				AllocParticleSystem(float theX, float theY, int theRenderOrder, ParticleEffect theParticleEffect);
    /*inline*/ bool					IsOverLoaded();
};

class ParticleRenderParams
{
public:
	bool							mRedIsSet;
	bool							mGreenIsSet;
	bool							mBlueIsSet;
	bool							mAlphaIsSet;
	bool							mParticleScaleIsSet;
	bool							mParticleStretchIsSet;
	bool							mSpinPositionIsSet;
	bool							mPositionIsSet;
	float							mRed;
	float							mGreen;
	float							mBlue;
	float							mAlpha;
	float							mParticleScale;
	float							mParticleStretch;
	float							mSpinPosition;
	float							mPosX;
	float							mPosY;
};

class TodParticle
{
public:
	TodParticleEmitter*				mParticleEmitter;
	int								mParticleDuration;
	int								mParticleAge;
	float							mParticleTimeValue;
	float							mParticleLastTimeValue;
	float							mAnimationTimeValue;
	SexyVector2						mVelocity;
	SexyVector2						mPosition;
	int								mImageFrame;
	float							mSpinPosition;
	float							mSpinVelocity;
	ParticleID						mCrossFadeParticleID;
	int								mCrossFadeDuration;
	float							mParticleInterp[ParticleTracks::NUM_PARTICLE_TRACKS];
	float							mParticleFieldInterp[MAX_PARTICLE_FIELDS][2];
};

class TodTriangleGroup;
class TodParticleEmitter
{
public:
	TodEmitterDefinition*			mEmitterDef;													//+0x0
	TodParticleSystem*				mParticleSystem;												//+0x4
	TodList<ParticleID>				mParticleList;													//+0x8
	float							mSpawnAccum;													//+0x18
	Sexy::SexyVector2				mSystemCenter;													//+0x1C
	int								mParticlesSpawned;												//+0x24
	int								mSystemAge;														//+0x28
	int								mSystemDuration;												//+0x2C
	float							mSystemTimeValue;												//+0x30
	float							mSystemLastTimeValue;											//+0x34
	bool							mDead;															//+0x38
	Sexy::Color						mColorOverride;													//+0x3C
	bool							mExtraAdditiveDrawOverride;										//+0x4C
	float							mScaleOverride;													//+0x50
	Sexy::Image*					mImageOverride;													//+0x54
	ParticleEmitterID				mCrossFadeEmitterID;											//+0x58
	int								mEmitterCrossFadeCountDown;										//+0x5C
	int								mFrameOverride;													//+0x60
	float							mTrackInterp[ParticleSystemTracks::NUM_SYSTEM_TRACKS];			//+0x64
	float							mSystemFieldInterp[MAX_PARTICLE_FIELDS][2];						//+0x8C

public:
	void							TodEmitterInitialize(float theX, float theY, TodParticleSystem* theSystem, TodEmitterDefinition* theEmitterDef);
	void							Update();
	void							Draw(Graphics* g);
	void							SystemMove(float theX, float theY);
	static bool						GetRenderParams(TodParticle* theParticle, ParticleRenderParams* theParams);
	void							DrawParticle(Graphics* g, TodParticle* theParticle, TodTriangleGroup* theTriangleGroup);
	void							UpdateSpawning();
	bool							UpdateParticle(TodParticle* theParticle);
	TodParticle*					SpawnParticle(int theIndex, int theSpawnCount);
	bool							CrossFadeParticle(TodParticle* theParticle, TodParticleEmitter* theToEmitter);
	void							CrossFadeEmitter(TodParticleEmitter* theToEmitter);
	bool							CrossFadeParticleToName(TodParticle* theParticle, const char* theEmitterName);
	void							DeleteAll();
	void							UpdateParticleField(TodParticle* theParticle, ParticleField* theParticleField, float theParticleTimeValue, int theFieldIndex);
	void							UpdateSystemField(ParticleField* theParticleField, float theParticleTimeValue, int theFieldIndex);
    /*inline*/ float				SystemTrackEvaluate(FloatParameterTrack& theTrack, ParticleSystemTracks theSystemTrack);
	static /*inline*/ float			ParticleTrackEvaluate(FloatParameterTrack& theTrack, TodParticle* theParticle, ParticleTracks theParticleTrack);
	void							DeleteParticle(TodParticle* theParticle);
	void							DeleteNonCrossFading();
};
/*inline*/ float                    CrossFadeLerp(float theFrom, float theTo, bool theFromIsSet, bool theToIsSet, float theFraction);
void								RenderParticle(Graphics* g, TodParticle* theParticle, const Color& theColor, ParticleRenderParams* theParams, TodTriangleGroup* theTriangleGroup);

class TodParticleSystem
{
public:
	ParticleEffect					mEffectType;					//+0x0
    TodParticleDefinition*			mParticleDef;					//+0x4
    TodParticleHolder*				mParticleHolder;				//+0x8
    TodList<ParticleEmitterID>		mEmitterList;					//+0xC
    bool							mDead;							//+0x1C
    bool							mIsAttachment;					//+0x1D
    int								mRenderOrder;					//+0x20
    bool							mDontUpdate;					//+0x24

public:
    TodParticleSystem();
    ~TodParticleSystem();

    void							TodParticleInitializeFromDef(float theX, float theY, int theRenderOrder, TodParticleDefinition* theDefinition, ParticleEffect theEffectType);
    void							ParticleSystemDie();
    void							Update();
    void							Draw(Graphics* g);
    void							SystemMove(float theX, float theY);
    void							OverrideColor(const char* theEmitterName, const Color& theColor);
    void							OverrideExtraAdditiveDraw(const char* theEmitterName, bool theEnableExtraAdditiveDraw);
    void							OverrideImage(const char* theEmitterName, Image* theImage);
    void							OverrideFrame(const char* theEmitterName, int theFrame);
    void							OverrideScale(const char* theEmitterName, float theScale);
    void							CrossFade(const char* theEmitterName);
    TodParticleEmitter*				FindEmitterByName(const char* theEmitterName);
    TodEmitterDefinition*			FindEmitterDefByName(const char* theEmitterName);
};

#endif
