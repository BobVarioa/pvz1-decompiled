#include "TodDebug.h"
#include "Definition.h"
#include "TodParticle.h"
#include "EffectSystem.h"
#include "../GameConstants.h"
#include "../SexyAppFramework/Graphics.h"
#include "../SexyAppFramework/D3DInterface.h"

int gParticleDefCount;                      // [0x6A9F08]
TodParticleDefinition* gParticleDefArray;   // [0x6A9F0C]
int gParticleParamArraySize;				// [0x6A9F10]
ParticleParams* gParticleParamArray;		// [0x6A9F14]

ParticleParams gLawnParticleArray[(int)ParticleEffect::NUM_PARTICLES] = {
	{ ParticleEffect::PARTICLE_MELONSPLASH, "particles\\MelonImpact.xml" },
	{ ParticleEffect::PARTICLE_WINTERMELON, "particles\\WinterMelonImpact.xml" },
	{ ParticleEffect::PARTICLE_FUMECLOUD, "particles\\FumeCloud.xml" },
	{ ParticleEffect::PARTICLE_POPCORNSPLASH, "particles\\PopcornSplash.xml" },
	{ ParticleEffect::PARTICLE_POWIE, "particles\\Powie.xml" },
	{ ParticleEffect::PARTICLE_JACKEXPLODE, "particles\\JackExplode.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_HEAD, "particles\\ZombieHead.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_ARM, "particles\\ZombieArm.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_TRAFFIC_CONE, "particles\\ZombieTrafficCone.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_PAIL, "particles\\ZombiePail.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_HELMET, "particles\\ZombieHelmet.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_FLAG, "particles\\ZombieFlag.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_DOOR, "particles\\ZombieDoor.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_NEWSPAPER, "particles\\ZombieNewspaper.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_HEADLIGHT, "particles\\ZombieHeadLight.xml" },
	{ ParticleEffect::PARTICLE_POW, "particles\\Pow.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_POGO, "particles\\ZombiePogo.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_NEWSPAPER_HEAD, "particles\\ZombieNewspaperHead.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_BALLOON_HEAD, "particles\\ZombieBalloonHead.xml" },
	{ ParticleEffect::PARTICLE_SOD_ROLL, "particles\\SodRoll.xml" },
	{ ParticleEffect::PARTICLE_GRAVE_STONE_RISE, "particles\\GraveStoneRise.xml" },
	{ ParticleEffect::PARTICLE_PLANTING, "particles\\Planting.xml" },
	{ ParticleEffect::PARTICLE_PLANTING_POOL, "particles\\PlantingPool.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_RISE, "particles\\ZombieRise.xml" },
	{ ParticleEffect::PARTICLE_GRAVE_BUSTER, "particles\\GraveBuster.xml" },
	{ ParticleEffect::PARTICLE_GRAVE_BUSTER_DIE, "particles\\GraveBusterDie.xml" },
	{ ParticleEffect::PARTICLE_POOL_SPLASH, "particles\\PoolSplash.xml" },
	{ ParticleEffect::PARTICLE_ICE_SPARKLE, "particles\\IceSparkle.xml" },
	{ ParticleEffect::PARTICLE_SEED_PACKET, "particles\\SeedPacket.xml" },
	{ ParticleEffect::PARTICLE_TALL_NUT_BLOCK, "particles\\TallNutBlock.xml" },
	{ ParticleEffect::PARTICLE_DOOM, "particles\\Doom.xml" },
	{ ParticleEffect::PARTICLE_DIGGER_RISE, "particles\\DiggerRise.xml" },
	{ ParticleEffect::PARTICLE_DIGGER_TUNNEL, "particles\\DiggerTunnel.xml" },
	{ ParticleEffect::PARTICLE_DANCER_RISE, "particles\\DancerRise.xml" },
	{ ParticleEffect::PARTICLE_POOL_SPARKLY, "particles\\PoolSparkly.xml" },
	{ ParticleEffect::PARTICLE_WALLNUT_EAT_SMALL, "particles\\WallnutEatSmall.xml" },
	{ ParticleEffect::PARTICLE_WALLNUT_EAT_LARGE, "particles\\WallnutEatLarge.xml" },
	{ ParticleEffect::PARTICLE_PEA_SPLAT, "particles\\PeaSplat.xml" },
	{ ParticleEffect::PARTICLE_BUTTER_SPLAT, "particles\\ButterSplat.xml" },
	{ ParticleEffect::PARTICLE_CABBAGE_SPLAT, "particles\\CabbageSplat.xml" },
	{ ParticleEffect::PARTICLE_PUFF_SPLAT, "particles\\PuffSplat.xml" },
	{ ParticleEffect::PARTICLE_STAR_SPLAT, "particles\\StarSplat.xml" },
	{ ParticleEffect::PARTICLE_ICE_TRAP, "particles\\IceTrap.xml" },
	{ ParticleEffect::PARTICLE_SNOWPEA_SPLAT, "particles\\SnowPeaSplat.xml" },
	{ ParticleEffect::PARTICLE_SNOWPEA_PUFF, "particles\\SnowPeaPuff.xml" },
	{ ParticleEffect::PARTICLE_SNOWPEA_TRAIL, "particles\\SnowPeaTrail.xml" },
	{ ParticleEffect::PARTICLE_LANTERN_SHINE, "particles\\LanternShine.xml" },
	{ ParticleEffect::PARTICLE_SEED_PACKET_PICKUP, "particles\\Award.xml" },
	{ ParticleEffect::PARTICLE_POTATO_MINE, "particles\\PotatoMine.xml" },
	{ ParticleEffect::PARTICLE_POTATO_MINE_RISE, "particles\\PotatoMineRise.xml" },
	{ ParticleEffect::PARTICLE_PUFFSHROOM_TRAIL, "particles\\PuffShroomTrail.xml" },
	{ ParticleEffect::PARTICLE_PUFFSHROOM_MUZZLE, "particles\\PuffShroomMuzzle.xml" },
	{ ParticleEffect::PARTICLE_SEED_PACKET_FLASH, "particles\\SeedPacketFlash.xml" },
	{ ParticleEffect::PARTICLE_WHACK_A_ZOMBIE_RISE, "particles\\WhackAZombieRise.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_LADDER, "particles\\ZombieLadder.xml" },
	{ ParticleEffect::PARTICLE_UMBRELLA_REFLECT, "particles\\UmbrellaReflect.xml" },
	{ ParticleEffect::PARTICLE_SEED_PACKET_PICK, "particles\\SeedPacketPick.xml" },
	{ ParticleEffect::PARTICLE_ICE_TRAP_ZOMBIE, "particles\\IceTrapZombie.xml" },
	{ ParticleEffect::PARTICLE_ICE_TRAP_RELEASE, "particles\\IceTrapRelease.xml" },
	{ ParticleEffect::PARTICLE_ZAMBONI_SMOKE, "particles\\ZamboniSmoke.xml" },
	{ ParticleEffect::PARTICLE_GLOOMCLOUD, "particles\\GloomCloud.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_POGO_HEAD, "particles\\ZombiePogoHead.xml" },
	{ ParticleEffect::PARTICLE_ZAMBONI_TIRE, "particles\\ZamboniTire.xml" },
	{ ParticleEffect::PARTICLE_ZAMBONI_EXPLOSION, "particles\\ZamboniExplosion.xml" },
	{ ParticleEffect::PARTICLE_ZAMBONI_EXPLOSION2, "particles\\ZamboniExplosion2.xml" },
	{ ParticleEffect::PARTICLE_CATAPULT_EXPLOSION, "particles\\CatapultExplosion.xml" },
	{ ParticleEffect::PARTICLE_MOWER_CLOUD, "particles\\MowerCloud.xml" },
	{ ParticleEffect::PARTICLE_BOSS_ICE_BALL, "particles\\BossIceBallTrail.xml" },
	{ ParticleEffect::PARTICLE_BLASTMARK, "particles\\BlastMark.xml" },
	{ ParticleEffect::PARTICLE_COIN_PICKUP_ARROW, "particles\\CoinPickupArrow.xml" },
	{ ParticleEffect::PARTICLE_PRESENT_PICKUP, "particles\\PresentPickup.xml" },
	{ ParticleEffect::PARTICLE_IMITATER_MORPH, "particles\\ImitaterMorph.xml" },
	{ ParticleEffect::PARTICLE_MOWERED_ZOMBIE_HEAD, "particles\\MoweredZombieHead.xml" },
	{ ParticleEffect::PARTICLE_MOWERED_ZOMBIE_ARM, "particles\\MoweredZombieArm.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_HEAD_POOL, "particles\\ZombieHeadPool.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_BOSS_FIREBALL, "particles\\Zombie_boss_fireball.xml" },
	{ ParticleEffect::PARTICLE_FIREBALL_DEATH, "particles\\FireballDeath.xml" },
	{ ParticleEffect::PARTICLE_ICEBALL_DEATH, "particles\\IceballDeath.xml" },
	{ ParticleEffect::PARTICLE_ICEBALL_TRAIL, "particles\\Iceball_Trail.xml" },
	{ ParticleEffect::PARTICLE_FIREBALL_TRAIL, "particles\\Fireball_Trail.xml" },
	{ ParticleEffect::PARTICLE_BOSS_EXPLOSION, "particles\\BossExplosion.xml" },
	{ ParticleEffect::PARTICLE_SCREEN_FLASH, "particles\\ScreenFlash.xml" },
	{ ParticleEffect::PARTICLE_TROPHY_SPARKLE, "particles\\TrophySparkle.xml" },
	{ ParticleEffect::PARTICLE_PORTAL_CIRCLE, "particles\\PortalCircle.xml" },
	{ ParticleEffect::PARTICLE_PORTAL_SQUARE, "particles\\PortalSquare.xml" },
	{ ParticleEffect::PARTICLE_POTTED_PLANT_GLOW, "particles\\PottedPlantGlow.xml" },
	{ ParticleEffect::PARTICLE_POTTED_WATER_PLANT_GLOW, "particles\\PottedWaterPlantGlow.xml" },
	{ ParticleEffect::PARTICLE_POTTED_ZEN_GLOW, "particles\\PottedZenGlow.xml" },
	{ ParticleEffect::PARTICLE_MIND_CONTROL, "particles\\MindControl.xml" },
	{ ParticleEffect::PARTICLE_VASE_SHATTER, "particles\\VaseShatter.xml" },
	{ ParticleEffect::PARTICLE_VASE_SHATTER_LEAF, "particles\\VaseShatterLeaf.xml" },
	{ ParticleEffect::PARTICLE_VASE_SHATTER_ZOMBIE, "particles\\VaseShatterZombie.xml" },
	{ ParticleEffect::PARTICLE_AWARD_PICKUP_ARROW, "particles\\AwardPickupArrow.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_SEAWEED, "particles\\Zombie_seaweed.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_MUSTACHE, "particles\\ZombieMustache.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_SUNGLASS, "particles\\ZombieFutureGlasses.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_PINATA, "particles\\Pinata.xml" },
	{ ParticleEffect::PARTICLE_DUST_SQUASH, "particles\\Dust_Squash.xml" },
	{ ParticleEffect::PARTICLE_DUST_FOOT, "particles\\Dust_Foot.xml" },
	{ ParticleEffect::PARTICLE_ZOMBIE_DAISIES, "particles\\Daisy.xml" },
	{ ParticleEffect::PARTICLE_CREDIT_STROBE, "particles\\Credits_Strobe.xml" },
	{ ParticleEffect::PARTICLE_CREDITS_RAYSWIPE, "particles\\Credits_RaysWipe.xml" },
	{ ParticleEffect::PARTICLE_CREDITS_ZOMBIEHEADWIPE, "particles\\Credits_ZombieHeadWipe.xml" },
	{ ParticleEffect::PARTICLE_STARBURST, "particles\\Starburst.xml" },
	{ ParticleEffect::PARTICLE_CREDITS_FOG, "particles\\Credits_fog.xml" },
	{ ParticleEffect::PARTICLE_PERSENT_PICK_UP_ARROW, "particles\\UpsellArrow.xml" },
};  // 0x6A0FF0

//0x515640 : (ecx = *theParticleFileName, *theParticleDef)  //esp -= 4
bool TodParticleLoadADef(TodParticleDefinition* theParticleDef, const char* theParticleFileName)
{
	TodHesitationBracket(_S("Load Particle %s"), theParticleFileName);
	if (!DefinitionLoadXML(theParticleFileName, &gParticleDefMap, theParticleDef))
	{
		char aBuf[512];
		sprintf(aBuf, _S("Failed to load particle '%s'"), theParticleFileName);
		TodErrorMessageBox(aBuf, _S("Error"));
		return false;
	}
	else
	{
		for (int i = 0; i < theParticleDef->mEmitterDefCount; i++)
		{
			TodEmitterDefinition& aDef = theParticleDef->mEmitterDefs[i];
			FloatTrackSetDefault(aDef.mSystemDuration, 0.0f);
			FloatTrackSetDefault(aDef.mSpawnRate, 0.0f);
			FloatTrackSetDefault(aDef.mSpawnMinActive, -1.0f);
			FloatTrackSetDefault(aDef.mSpawnMaxActive, -1.0f);
			FloatTrackSetDefault(aDef.mSpawnMaxLaunched, -1.0f);
			FloatTrackSetDefault(aDef.mEmitterRadius, 0.0f);
			FloatTrackSetDefault(aDef.mEmitterOffsetX, 0.0f);
			FloatTrackSetDefault(aDef.mEmitterOffsetY, 0.0f);
			FloatTrackSetDefault(aDef.mEmitterBoxX, 0.0f);
			FloatTrackSetDefault(aDef.mEmitterBoxY, 0.0f);
			FloatTrackSetDefault(aDef.mEmitterSkewX, 0.0f);
			FloatTrackSetDefault(aDef.mEmitterSkewY, 0.0f);
			FloatTrackSetDefault(aDef.mParticleDuration, 100.0f);
			FloatTrackSetDefault(aDef.mLaunchSpeed, 0.0f);
			FloatTrackSetDefault(aDef.mSystemRed, 1.0f);
			FloatTrackSetDefault(aDef.mSystemGreen, 1.0f);
			FloatTrackSetDefault(aDef.mSystemBlue, 1.0f);
			FloatTrackSetDefault(aDef.mSystemAlpha, 1.0f);
			FloatTrackSetDefault(aDef.mSystemBrightness, 1.0f);
			FloatTrackSetDefault(aDef.mLaunchAngle, 0.0f);
			FloatTrackSetDefault(aDef.mCrossFadeDuration, 0.0f);
			FloatTrackSetDefault(aDef.mParticleRed, 1.0f);
			FloatTrackSetDefault(aDef.mParticleGreen, 1.0f);
			FloatTrackSetDefault(aDef.mParticleBlue, 1.0f);
			FloatTrackSetDefault(aDef.mParticleAlpha, 1.0f);
			FloatTrackSetDefault(aDef.mParticleBrightness, 1.0f);
			FloatTrackSetDefault(aDef.mParticleSpinAngle, 0.0f);
			FloatTrackSetDefault(aDef.mParticleSpinSpeed, 0.0f);
			FloatTrackSetDefault(aDef.mParticleScale, 1.0f);
			FloatTrackSetDefault(aDef.mParticleStretch, 1.0f);
			FloatTrackSetDefault(aDef.mCollisionReflect, 0.0f);
			FloatTrackSetDefault(aDef.mCollisionSpin, 0.0f);
			FloatTrackSetDefault(aDef.mClipTop, 0.0f);
			FloatTrackSetDefault(aDef.mClipBottom, 0.0f);
			FloatTrackSetDefault(aDef.mClipLeft, 0.0f);
			FloatTrackSetDefault(aDef.mClipRight, 0.0f);
			FloatTrackSetDefault(aDef.mAnimationRate, 0.0f);
			if (aDef.mImage)
				((MemoryImage*)aDef.mImage)->mD3DFlags |= D3DImageFlags::D3DImageFlag_MinimizeNumSubdivisions;
		}
		return true;
	}
}

//0x515CE0
void TodParticleLoadDefinitions(ParticleParams* theParticleParamArray, int theParticleParamArraySize)
{
	TodHesitationBracket aHesitiation("TodParticleLoadDefinitions");
	TOD_ASSERT(!gParticleParamArray && !gParticleDefArray);
	gParticleParamArraySize = theParticleParamArraySize;
	gParticleParamArray = theParticleParamArray;
	gParticleDefCount = theParticleParamArraySize;
	gParticleDefArray = new TodParticleDefinition[theParticleParamArraySize];

	for (int i = 0; i < gParticleParamArraySize; i++)
	{
		ParticleParams& aParticleParams = gParticleParamArray[i];
		TOD_ASSERT(aParticleParams.mParticleEffect == i);
		if (!TodParticleLoadADef(&gParticleDefArray[i], aParticleParams.mParticleFileName))
		{
			char aBuf[512];
			sprintf(aBuf, "Failed to load particle '%s'", aParticleParams.mParticleFileName);
			TodErrorMessageBox(aBuf, "Error");
		}
		gSexyAppBase->mNumLoadingThreadTasks += 6;
	}
}

//0x515E30
void TodParticleFreeDefinitions()
{
	for (int i = 0; i < gParticleDefCount; i++)
		DefinitionFreeMap(&gParticleDefMap, &gParticleDefArray[i]);
	delete[] gParticleDefArray;
	gParticleDefArray = nullptr;
	gParticleDefCount = 0;
	gParticleParamArray = nullptr;
	gParticleParamArraySize = 0;
}

TodParticleSystem::TodParticleSystem()
{
	mEffectType = ParticleEffect::PARTICLE_NONE;
	mParticleDef = nullptr;
	mParticleHolder = nullptr;
	mDead = false;
	mDontUpdate = false;
	mIsAttachment = false;
	mRenderOrder = 0;
}

TodParticleSystem::~TodParticleSystem()
{
	ParticleSystemDie();
	mEmitterList.RemoveAll();
}

//0x515E90 : (edx = theEffectType, *theDefinition, ecx = theRenderOrder, theY, theX, *this)
void TodParticleSystem::TodParticleInitializeFromDef(float theX, float theY, int theRenderOrder, TodParticleDefinition* theDefinition, ParticleEffect theEffectType)
{
	TOD_ASSERT(mParticleHolder);
	mEmitterList.SetAllocator(&mParticleHolder->mEmitterListNodeAllocator);
	mParticleDef = theDefinition;
	mEffectType = theEffectType;
	mRenderOrder = theRenderOrder;

	for (int i = 0; i < theDefinition->mEmitterDefCount; i++)
	{
		TodEmitterDefinition& aDef = theDefinition->mEmitterDefs[i];
		if (!FloatTrackIsSet(aDef.mCrossFadeDuration))
		{
			if (TestBit(aDef.mParticleFlags, (int)ParticleFlags::PARTICLE_DIE_IF_OVERLOADED) && mParticleHolder->IsOverLoaded())
			{
				ParticleSystemDie();
				break;
			}
			TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayAlloc();
			aEmitter->TodEmitterInitialize(theX, theY, this, &aDef);
			mEmitterList.AddTail((ParticleEmitterID)mParticleHolder->mEmitters.DataArrayGetID(aEmitter));
		}
	}
}

//0x515F70 : (*theEmitterDef, *theSystem, theY, theX, ecx = *this)
void TodParticleEmitter::TodEmitterInitialize(float theX, float theY, TodParticleSystem* theSystem, TodEmitterDefinition* theEmitterDef)
{
	mSpawnAccum = 0.0f;
	mParticlesSpawned = 0;
	mSystemTimeValue = -1.0f;
	mSystemLastTimeValue = -1.0f;
	mSystemAge = -1;
	mDead = false;
	mColorOverride = Sexy::Color::White;
	mSystemCenter.x = theX;
	mSystemCenter.y = theY;
	mFrameOverride = -1;
	mParticleSystem = theSystem;
	mScaleOverride = 1.0f;
	mExtraAdditiveDrawOverride = false;
	mImageOverride = nullptr;
	mSystemDuration = 0;
	mEmitterDef = theEmitterDef;
	mParticleList.SetAllocator(&theSystem->mParticleHolder->mEmitterListNodeAllocator);

	if (FloatTrackIsSet(mEmitterDef->mSystemDuration))
		mSystemDuration = FloatTrackEvaluate(mEmitterDef->mSystemDuration, 0.0f, Sexy::Rand(1.0f));
	else
		mSystemDuration = FloatTrackEvaluate(mEmitterDef->mParticleDuration, 0.0f, 1.0f);
	mSystemDuration = max(1, mSystemDuration);

	for (int i = 0; i < mEmitterDef->mSystemFieldCount; i++)
	{
		mSystemFieldInterp[i][0] = Sexy::Rand(1.0f);
		mSystemFieldInterp[i][1] = Sexy::Rand(1.0f);
	}
	for (int j = 0; j < 10; j++)
		mTrackInterp[j] = Sexy::Rand(1.0f);

	Update();
}

//0x5160C0
void TodParticleSystem::ParticleSystemDie()
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		aEmitter->DeleteAll();
		mParticleHolder->mEmitters.DataArrayFree(aEmitter);
	}
	mEmitterList.RemoveAll();
	mDead = true;
}

//0x516160
TodParticle* TodParticleEmitter::SpawnParticle(int theIndex, int theSpawnCount)
{
	DataArray<TodParticle>& aDataArray = mParticleSystem->mParticleHolder->mParticles;
	if (aDataArray.mSize == aDataArray.mMaxSize)
	{
		TodTraceWithoutSpamming("Too many particles '%s'\n", mEmitterDef->mName);
		return nullptr;
	}

	register TodParticle* aParticle = aDataArray.DataArrayAlloc();
	TOD_ASSERT(mEmitterDef->mParticleFieldCount <= MAX_PARTICLE_FIELDS);
	for (int i = 0; i < mEmitterDef->mParticleFieldCount; i++)
	{
		aParticle->mParticleFieldInterp[i][0] = Sexy::Rand(1.0f);  // Initialize the lateral interpolation of each particle field
		aParticle->mParticleFieldInterp[i][1] = Sexy::Rand(1.0f);  // Initialize the longitudinal interpolation of each particle field
	}
	for (int i = 0; i < (int)ParticleTracks::NUM_PARTICLE_TRACKS; i++)
		aParticle->mParticleInterp[i] = Sexy::Rand(1.0f);  // Initialize the interpolation of each channel

	float aParticleDurationInterp = Sexy::Rand(1.0f);
	float aLaunchSpeedInterp = Sexy::Rand(1.0f);
	float aEmitterOffsetXInterp = Sexy::Rand(1.0f);
	float aEmitterOffsetYInterp = Sexy::Rand(1.0f);
	aParticle->mParticleDuration = FloatTrackEvaluate(mEmitterDef->mParticleDuration, mSystemTimeValue, aParticleDurationInterp);
	aParticle->mParticleDuration = max(1, aParticle->mParticleDuration);  //Initialize particle duration (at least 1)
	aParticle->mParticleAge = 0;
	aParticle->mParticleEmitter = this;
	aParticle->mParticleTimeValue = -1.0f;
	aParticle->mParticleLastTimeValue = -1.0f;
	if (TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_RANDOM_START_TIME))
		aParticle->mParticleAge = Sexy::Rand(aParticle->mParticleDuration);  // For particles with "random initial time"
	float aLaunchSpeed = FloatTrackEvaluate(mEmitterDef->mLaunchSpeed, mSystemTimeValue, aLaunchSpeedInterp) * 0.01f;
	float aLaunchAngleInterp = Sexy::Rand(1.0f);

	float aLaunchAngle;
	if (mEmitterDef->mEmitterType == EmitterType::EMITTER_CIRCLE_PATH)
	{
		// launch angle = base angle on the circle calculated based on path definition + angle of additional offset calculated based on launch angle definition
		aLaunchAngle = FloatTrackEvaluate(mEmitterDef->mEmitterPath, mSystemTimeValue, mTrackInterp[ParticleSystemTracks::TRACK_EMITTER_PATH]) * 2 * PI;
		aLaunchAngle += DEG_TO_RAD(FloatTrackEvaluate(mEmitterDef->mLaunchAngle, mSystemTimeValue, aLaunchAngleInterp));
	}
	else if (mEmitterDef->mEmitterType == EmitterType::EMITTER_CIRCLE_EVEN_SPACING)
		//The basic emission angle should make theSpawnCount particles evenly cover the circle
		aLaunchAngle = 2 * PI * theIndex / theSpawnCount + DEG_TO_RAD(FloatTrackEvaluate(mEmitterDef->mLaunchAngle, mSystemTimeValue, aLaunchAngleInterp));
	else if (FloatTrackIsConstantZero(mEmitterDef->mLaunchAngle))
		// For undefined orbits, the launch angle directly takes a random value of [0, 2π]
		aLaunchAngle = Sexy::Rand((float)(2 * PI));
	else
		// In other cases, calculated based on the defined value of the launch angle
		aLaunchAngle = DEG_TO_RAD(FloatTrackEvaluate(mEmitterDef->mLaunchAngle, mSystemTimeValue, aLaunchAngleInterp));

	float aPosX, aPosY;
	switch (mEmitterDef->mEmitterType)
	{
	case EmitterType::EMITTER_CIRCLE:
	case EmitterType::EMITTER_CIRCLE_PATH:
	case EmitterType::EMITTER_CIRCLE_EVEN_SPACING:
	{
		float aEmitterRadiusInterp = Sexy::Rand(1.0f);
		float aRadius = FloatTrackEvaluate(mEmitterDef->mEmitterRadius, mSystemTimeValue, aEmitterRadiusInterp);
		// ★ 以竖直向下的方向为 0 角度
		aPosX = sin(aLaunchAngle) * aRadius;
		aPosY = cos(aLaunchAngle) * aRadius;
		break;
	}
	case EmitterType::EMITTER_BOX:
	{
		float aEmitterBoxXInterp = Sexy::Rand(1.0f);
		float aEmitterBoxYInterp = Sexy::Rand(1.0f);
		aPosX = FloatTrackEvaluate(mEmitterDef->mEmitterBoxX, mSystemTimeValue, aEmitterBoxXInterp);
		aPosY = FloatTrackEvaluate(mEmitterDef->mEmitterBoxY, mSystemTimeValue, aEmitterBoxYInterp);
		break;
	}
	case EmitterType::EMITTER_BOX_PATH:
	{
		float aEmitterPathPosition = FloatTrackEvaluate(mEmitterDef->mEmitterPath, mSystemTimeValue, mTrackInterp[ParticleSystemTracks::TRACK_EMITTER_PATH]);
		float aMinX = FloatTrackEvaluate(mEmitterDef->mEmitterBoxX, mSystemTimeValue, 0.0f);
		float aMaxX = FloatTrackEvaluate(mEmitterDef->mEmitterBoxX, mSystemTimeValue, 1.0f);
		float aMinY = FloatTrackEvaluate(mEmitterDef->mEmitterBoxY, mSystemTimeValue, 0.0f);
		float aMaxY = FloatTrackEvaluate(mEmitterDef->mEmitterBoxY, mSystemTimeValue, 1.0f);
		float aDistanceX = aMaxX - aMinX;  //The horizontal width of the path rectangle
		float aDistanceY = aMaxY - aMinY;  //The vertical height of the path rectangle
		float aPathPos = aEmitterPathPosition * (aDistanceY + aDistanceX + aDistanceY + aDistanceX);  // The emission point is located on the edge of the rectangle
		// ★ 注释规定：以矩形左上的顶点开始，按逆时针方向依次将矩形的四个顶点标记为 A、B、C、D，并标记发射点为 P
		// ★           如此，aPathPos 即为 P 点与 A 点在矩形路径上的距离。注意，游戏中取横向水平向右和纵向竖直向下为正方向。
		if (aPathPos < aDistanceY)  //The emission point falls on the AB side (left) of the rectangle
		{
			aPosX = aMinX;  // Abscissa = abscissa of the left end of the rectangle
			aPosY = aMinY + aPathPos;  // Vertical coordinate = rectangular bottom coordinate + |PA|
		}
		else if (aPathPos < aDistanceY + aDistanceX)  //The emission point falls on the BC side (top side) of the rectangle
		{
			aPosX = aMinX + (aPathPos - aDistanceY);  // Abscissa = abscissa of the left end of the rectangle + |PB|
			aPosY = aMaxY;
		}
		else if (aPathPos < aDistanceY + aDistanceX + aDistanceY)  //The emission point falls on the CD side (right) of the rectangle
		{
			aPosX = aMaxX;
			aPosY = aMaxY - (aPathPos - aDistanceY - aDistanceX);  // Vertical coordinate = Vertical coordinate of the top of the rectangle - |PC|
		}
		else  //The emission point falls on the AD side (bottom) of the rectangle
		{
			aPosX = aMaxX - (aPathPos - aDistanceY - aDistanceX - aDistanceY);  // Abscissa = abscissa of the right end of the rectangle - |PD|
			aPosY = aMinY;
		}
		break;
	}
	default:
		TOD_ASSERT(false);
		break;
	}
	float aEmitterSkewXInterp = Sexy::Rand(1.0f);
	float aEmitterSkewYInterp = Sexy::Rand(1.0f);
	float aSkewX = FloatTrackEvaluate(mEmitterDef->mEmitterSkewX, mSystemTimeValue, aEmitterSkewXInterp);
	float aSkewY = FloatTrackEvaluate(mEmitterDef->mEmitterSkewY, mSystemTimeValue, aEmitterSkewYInterp);
	aParticle->mPosition.x = mSystemCenter.x + aPosX + aPosY * aSkewX;  // The amplitude of horizontal (left and right) tilt is affected by the vertical coordinate
	aParticle->mPosition.y = mSystemCenter.y + aPosY + aPosX * aSkewY;  // The vertical (up and down) tilt amplitude is affected by the abscissa
	aParticle->mVelocity.x = sin(aLaunchAngle) * aLaunchSpeed;
	aParticle->mVelocity.y = cos(aLaunchAngle) * aLaunchSpeed;
	aParticle->mPosition.x += FloatTrackEvaluate(mEmitterDef->mEmitterOffsetX, mSystemTimeValue, aEmitterOffsetXInterp);  //The abscissa plus the lateral offset value
	aParticle->mPosition.y += FloatTrackEvaluate(mEmitterDef->mEmitterOffsetY, mSystemTimeValue, aEmitterOffsetYInterp);  //The vertical coordinate plus the vertical offset value
	
	aParticle->mAnimationTimeValue = 0.0f;
	if (mEmitterDef->mAnimated || FloatTrackIsSet(mEmitterDef->mAnimationRate))
		aParticle->mImageFrame = 0;  // If the particle dynamics or animation rate is defined, the current frame of the particle will be calculated in real time based on the particle time value or animation cycle rate, and is initialized to 0 here.
	else
		aParticle->mImageFrame = Sexy::Rand(mEmitterDef->mImageFrames);  // For particles with a fixed frame, randomly obtain a frame among all frames of the texture, and it will generally not change subsequently.

	if (TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_RANDOM_LAUNCH_SPIN))
		aParticle->mSpinPosition = Sexy::Rand((float)(2 * PI));  // Randomly obtain an initial rotation angle between [0, 2π]
	else if (TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_ALIGN_LAUNCH_SPIN))
		aParticle->mSpinPosition = aLaunchAngle;  // Particle rotation angle aligns with emission angle
	else
		aParticle->mSpinPosition = 0.0f;  // No initial rotation by default
	aParticle->mSpinVelocity = 0.0f;
	aParticle->mCrossFadeDuration = 0;
	aParticle->mCrossFadeParticleID = ParticleID::PARTICLEID_NULL;

	ParticleID aParticleID = (ParticleID)aDataArray.DataArrayGetID(aParticle);
	mParticleList.AddHead(aParticleID);
	mParticlesSpawned++;
	UpdateParticle(aParticle);
	return aParticle;
}

float TodParticleEmitter::ParticleTrackEvaluate(FloatParameterTrack& theTrack, TodParticle* theParticle, ParticleTracks theParticleTrack)
{
	return FloatTrackEvaluate(theTrack, theParticle->mParticleTimeValue, theParticle->mParticleInterp[(int)theParticleTrack]);
}

//0x516820
void TodParticleEmitter::UpdateParticleField(TodParticle* theParticle, ParticleField* theParticleField, float theParticleTimeValue, int theFieldIndex)
{
	TOD_ASSERT(theFieldIndex < MAX_PARTICLE_FIELDS);
	float aInterpX = theParticle->mParticleFieldInterp[theFieldIndex][0];
	float aInterpY = theParticle->mParticleFieldInterp[theFieldIndex][1];
	float x = FloatTrackEvaluate(theParticleField->mX, theParticleTimeValue, aInterpX);
	float y = FloatTrackEvaluate(theParticleField->mY, theParticleTimeValue, aInterpY);

	switch (theParticleField->mFieldType)
	{
	case ParticleFieldType::FIELD_INVALID:
		break;
	case ParticleFieldType::FIELD_FRICTION:  // Friction field
		theParticle->mVelocity.x *= 1 - x;
		theParticle->mVelocity.y *= 1 - y;
		break;
	case ParticleFieldType::FIELD_ACCELERATION:  // acceleration field
		theParticle->mVelocity.x += 0.01f * x;
		theParticle->mVelocity.y += 0.01f * y;
		break;
	case ParticleFieldType::FIELD_ATTRACTOR:  // elastic force field
	{
		float aDiffX = x - (theParticle->mPosition.x - mSystemCenter.x);
		float aDiffY = y - (theParticle->mPosition.y - mSystemCenter.y);
		// The direction of acceleration is always from the particle's position to the "standard position"
		theParticle->mVelocity.x += 0.01f * aDiffX;
		theParticle->mVelocity.y += 0.01f * aDiffY;
		break;
	}
	case ParticleFieldType::FIELD_MAX_VELOCITY:  // speed limit field
		theParticle->mVelocity.x = ClampFloat(theParticle->mVelocity.x, -x, x);
		theParticle->mVelocity.y = ClampFloat(theParticle->mVelocity.y, -y, y);
		break;
	case ParticleFieldType::FIELD_VELOCITY:  // uniform velocity field
		theParticle->mPosition.x += 0.01 * x;
		theParticle->mPosition.y += 0.01 * y;
		break;
	case ParticleFieldType::FIELD_POSITION:  // positioning field
	{
		float aLastX = FloatTrackEvaluateFromLastTime(theParticleField->mX, theParticle->mParticleLastTimeValue, aInterpX);
		float aLastY = FloatTrackEvaluateFromLastTime(theParticleField->mY, theParticle->mParticleLastTimeValue, aInterpY);
		theParticle->mPosition.x += x - aLastX;
		theParticle->mPosition.y += y - aLastY;
		break;
	}
	case ParticleFieldType::FIELD_GROUND_CONSTRAINT:
		if (theParticle->mPosition.y > mSystemCenter.y + y)  // Determine whether it touches the ground
		{
			theParticle->mPosition.y = mSystemCenter.y + y;  //Reset coordinates to the ground
			float aCollisionReflect = FloatTrackEvaluate(
				mEmitterDef->mCollisionReflect, theParticleTimeValue, theParticle->mParticleInterp[ParticleTracks::TRACK_PARTICLE_COLLISION_REFLECT]
			);
			float aCollisionSpin = FloatTrackEvaluate(
				mEmitterDef->mCollisionSpin, theParticleTimeValue, theParticle->mParticleInterp[ParticleTracks::TRACK_PARTICLE_COLLISION_SPIN]
			) / 1000.0f;
			theParticle->mSpinVelocity = theParticle->mVelocity.y * aCollisionSpin;
			theParticle->mVelocity.x *= aCollisionReflect;
			theParticle->mVelocity.y *= -aCollisionReflect;
		}
		break;
	case ParticleFieldType::FIELD_SHAKE:  //vibration
	{
		float aLastX = FloatTrackEvaluateFromLastTime(theParticleField->mX, theParticle->mParticleLastTimeValue, aInterpX);
		float aLastY = FloatTrackEvaluateFromLastTime(theParticleField->mY, theParticle->mParticleLastTimeValue, aInterpY);
		// First restore the influence of the last vibration effect
		int aLastRandSeed = theParticle->mParticleAge - 1;
		if (aLastRandSeed == -1)
			aLastRandSeed = theParticle->mParticleDuration - 1;
		srand(aLastRandSeed * (int)theParticle);
		theParticle->mPosition.x -= aLastX * ((float)rand() / RAND_MAX * 2.0f - 1.0f);
		theParticle->mPosition.y -= aLastY * ((float)rand() / RAND_MAX * 2.0f - 1.0f);
		// Then randomly obtain the vibration effect of the current frame
		srand(theParticle->mParticleAge * (int)theParticle);
		theParticle->mPosition.x += x * ((float)rand() / RAND_MAX * 2.0f - 1.0f);
		theParticle->mPosition.y += y * ((float)rand() / RAND_MAX * 2.0f - 1.0f);
		break;
	}
	case ParticleFieldType::FIELD_CIRCLE:  // circumference
	{
		SexyVector2 aToCenter = theParticle->mPosition - mSystemCenter;
		SexyVector2 aMotion = aToCenter.Perp().Normalize();  //Normalized normal vector
		float aRadius = aToCenter.Magnitude();
		aMotion *= 0.01 * (x + aRadius * y);
		theParticle->mPosition += aMotion;
		break;
	}
	case ParticleFieldType::FIELD_AWAY:  // keep away
	{
		SexyVector2 aToCenter = theParticle->mPosition - mSystemCenter;
		SexyVector2 aMotion = aToCenter.Normalize();  //Normalized direction vector
		float aRadius = aToCenter.Magnitude();
		aMotion *= 0.01 * (x + aRadius * y);
		theParticle->mPosition += aMotion;
		break;
	}
	default:
		TOD_ASSERT(0);
		break;
	}
}

float TodParticleEmitter::SystemTrackEvaluate(FloatParameterTrack& theTrack, ParticleSystemTracks theSystemTrack)
{
	return FloatTrackEvaluate(theTrack, mSystemTimeValue, mTrackInterp[(int)theSystemTrack]);
}

//0x516D70
void TodParticleEmitter::UpdateSystemField(ParticleField* theParticleField, float theParticleTimeValue, int theFieldIndex)
{
	TOD_ASSERT(theFieldIndex < MAX_PARTICLE_FIELDS);
	float aInterpX = mSystemFieldInterp[theFieldIndex][0];
	float aInterpY = mSystemFieldInterp[theFieldIndex][1];
	float x = FloatTrackEvaluate(theParticleField->mX, theParticleTimeValue, aInterpX);
	float y = FloatTrackEvaluate(theParticleField->mY, theParticleTimeValue, aInterpY);

	switch (theParticleField->mFieldType)
	{
	case ParticleFieldType::FIELD_SYSTEM_POSITION:
	{
		float aLastX = FloatTrackEvaluateFromLastTime(theParticleField->mX, mSystemLastTimeValue, aInterpX);
		float aLastY = FloatTrackEvaluateFromLastTime(theParticleField->mY, mSystemLastTimeValue, aInterpY);
		mSystemCenter.x += x - aLastX;
		mSystemCenter.y += y - aLastY;
		break;
	}
	default:
		TOD_ASSERT(0);
		break;
	}
}

//0x516E70
bool TodParticleEmitter::CrossFadeParticleToName(TodParticle* theParticle, const char* theEmitterName)
{
	TodEmitterDefinition* aDef = mParticleSystem->FindEmitterDefByName(theEmitterName);
	if (aDef == nullptr)
	{
		TodTrace("Can't find emitter to cross fade: %s\n", theEmitterName);
		return false;
	}
	if (mParticleSystem->mParticleHolder->mEmitters.mSize == mParticleSystem->mParticleHolder->mEmitters.mMaxSize)
	{
		TodTrace("Too many emitters to cross fade\n");
		return false;
	}

	TodParticleEmitter* aEmitter = mParticleSystem->mParticleHolder->mEmitters.DataArrayAlloc();
	aEmitter->TodEmitterInitialize(mSystemCenter.x, mSystemCenter.y, mParticleSystem, aDef);
	ParticleEmitterID aEmitterID = (ParticleEmitterID)mParticleSystem->mParticleHolder->mEmitters.DataArrayGetID(aEmitter);
	mParticleSystem->mEmitterList.AddTail(aEmitterID);
	return CrossFadeParticle(theParticle, aEmitter);
}

//0x516F00
bool TodParticleEmitter::UpdateParticle(TodParticle* theParticle)
{
	if (theParticle->mParticleAge >= theParticle->mParticleDuration)  // When the particle's life cycle ends
	{
		if (TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_PARTICLE_LOOPS))  // Determine whether the particles are circulating
			theParticle->mParticleAge = 0;  //Reset the current frame of particles
		else if (theParticle->mCrossFadeDuration > 0)  // Determine whether the particles are in the cross-mixing process
			theParticle->mParticleAge = theParticle->mParticleDuration - 1;  //Keep particles in the last frame
		else if (*mEmitterDef->mOnDuration == '\0' || !CrossFadeParticleToName(theParticle, mEmitterDef->mOnDuration))  //try cross blending
			return false;
	}
	if (theParticle->mCrossFadeParticleID != ParticleID::PARTICLEID_NULL &&
		mParticleSystem->mParticleHolder->mParticles.DataArrayTryToGet(theParticle->mCrossFadeParticleID) == nullptr)
		return false;  // When there is no cross-mixing of particles, particles can be deleted

	theParticle->mParticleTimeValue = theParticle->mParticleAge / ((float)theParticle->mParticleDuration - 1);
	for (int i = 0; i < mEmitterDef->mParticleFieldCount; i++)  //Update particles affected by each particle field
		UpdateParticleField(theParticle, &mEmitterDef->mParticleFields[i], theParticle->mParticleTimeValue, i);
	theParticle->mPosition += theParticle->mVelocity;
	float aSpinSpeed = ParticleTrackEvaluate(mEmitterDef->mParticleSpinSpeed, theParticle, ParticleTracks::TRACK_PARTICLE_SPIN_SPEED) * 0.01;
	float aSpinAngle = ParticleTrackEvaluate(mEmitterDef->mParticleSpinAngle, theParticle, ParticleTracks::TRACK_PARTICLE_SPIN_ANGLE);
	float aLastSpinAngle = FloatTrackEvaluateFromLastTime(
		mEmitterDef->mParticleSpinAngle, theParticle->mParticleLastTimeValue, theParticle->mParticleInterp[ParticleTracks::TRACK_PARTICLE_SPIN_ANGLE]);
	theParticle->mSpinPosition += DEG_TO_RAD(aSpinSpeed + aSpinAngle - aLastSpinAngle) + theParticle->mSpinVelocity;  //Update particle rotation angle

	if (FloatTrackIsSet(mEmitterDef->mAnimationRate))  // If animation rate is defined
	{
		float aAnimTime = ParticleTrackEvaluate(mEmitterDef->mAnimationRate, theParticle, ParticleTracks::TRACK_PARTICLE_ANIMATION_RATE) * 0.01;
		theParticle->mAnimationTimeValue += aAnimTime;  //Update animation time value (animation loop rate)
		while (theParticle->mAnimationTimeValue >= 1.0f)
			theParticle->mAnimationTimeValue -= 1.0f;
		while (theParticle->mAnimationTimeValue < 0.0f)
			theParticle->mAnimationTimeValue += 1.0f;
	}

	theParticle->mParticleAge++;
	theParticle->mParticleLastTimeValue = theParticle->mParticleTimeValue;
	return true;
}

//0x517160
void TodParticleEmitter::UpdateSpawning()
{
	TodParticleEmitter* aCrossFadeEmitter = mParticleSystem->mParticleHolder->mEmitters.DataArrayTryToGet((unsigned int)mCrossFadeEmitterID);
	TodParticleEmitter* aSpawningEmitter = !aCrossFadeEmitter ? this : aCrossFadeEmitter;  // All data calculations are based on this "main transmitter"
	mSpawnAccum += aSpawningEmitter->SystemTrackEvaluate(aSpawningEmitter->mEmitterDef->mSpawnRate, ParticleSystemTracks::TRACK_SPAWN_RATE) * 0.01;
	int aSpawnCount = (int)mSpawnAccum;
	mSpawnAccum -= aSpawnCount;

	int aSpawnMinActive = (int)aSpawningEmitter->SystemTrackEvaluate(aSpawningEmitter->mEmitterDef->mSpawnMinActive, ParticleSystemTracks::TRACK_SPAWN_MIN_ACTIVE);
	if (aSpawnMinActive >= 0 && aSpawnCount < aSpawnMinActive - mParticleList.mSize)
		aSpawnCount = aSpawnMinActive - mParticleList.mSize;  // Make sure to increase the number of particles to at least aSpawnMinActive
	int aSpawnMaxActive = (int)aSpawningEmitter->SystemTrackEvaluate(aSpawningEmitter->mEmitterDef->mSpawnMaxActive, ParticleSystemTracks::TRACK_SPAWN_MAX_ACTIVE);
	if (aSpawnMaxActive >= 0 && aSpawnCount > aSpawnMaxActive - mParticleList.mSize)
		aSpawnCount = aSpawnMaxActive - mParticleList.mSize;  // At most, the number of particles is guaranteed not to exceed aSpawnMaxActive
	if (FloatTrackIsSet(aSpawningEmitter->mEmitterDef->mSpawnMaxLaunched))
	{
		int aSpawnMaxLaunched = aSpawningEmitter->SystemTrackEvaluate(aSpawningEmitter->mEmitterDef->mSpawnMaxLaunched, ParticleSystemTracks::TRACK_SPAWN_MAX_LAUNCHED);
		if (aSpawnCount > aSpawnMaxLaunched - mParticlesSpawned)
			aSpawnCount = aSpawnMaxLaunched - mParticlesSpawned;  // Ensure that the number of emissions does not exceed the maximum number that the emitter can emit in total
	}

	for (int i = 0; i < aSpawnCount; i++)
	{
		TodParticle* aParticle = SpawnParticle(i, aSpawnCount);
		if (aCrossFadeEmitter != nullptr)
			CrossFadeParticle(aParticle, aCrossFadeEmitter);
	}
}

//0x5172C0
void TodParticleEmitter::DeleteNonCrossFading()
{
	for (TodListNode<ParticleID>* aNode = mParticleList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticle* aParticle = mParticleSystem->mParticleHolder->mParticles.DataArrayGet((unsigned int)aNode->mValue);
		if (aParticle->mCrossFadeDuration <= 0)  // When the particle is not in the cross-mixing state, delete the particle
			DeleteParticle(aParticle);
	}
}

//0x517300
void TodParticleEmitter::DeleteAll()
{
	while (mParticleList.mSize != 0)
	{
		ParticleID anId = mParticleList.RemoveHead();
		DataArray<TodParticle>& aDataArray = mParticleSystem->mParticleHolder->mParticles;
		aDataArray.DataArrayFree(aDataArray.DataArrayGet(anId));
	}
}

//0x517370
void TodParticleSystem::Update()
{
	if (!mDontUpdate)
	{
		bool aEmitterAlive = false;
		for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
		{
			TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
			aEmitter->Update();
			if ((FloatTrackIsSet(aEmitter->mEmitterDef->mCrossFadeDuration) && aEmitter->mParticleList.mSize > 0) || !aEmitter->mDead)
				aEmitterAlive = true;
		}
		if (!aEmitterAlive)
			mDead = true;
	}
}

//0x5173E0
bool TodParticleEmitter::CrossFadeParticle(TodParticle* theParticle, TodParticleEmitter* theToEmitter)
{
	if (theParticle->mCrossFadeDuration > 0)  // The particles are already in the process of cross-mixing
	{
		TodTrace("We don't support cross fading more than one at a time\n");
		return false;
	}
	if (!FloatTrackIsSet(theToEmitter->mEmitterDef->mCrossFadeDuration))  // The target emitter has no cross-mix duration track set
	{
		TodTrace("Can't cross fade to emitter that doesn't have CrossFadeDuration");
		return false;
	}
	TOD_ASSERT(theToEmitter != this);  // Cannot cross-mix to itself

	TodParticle* aToParticle = theToEmitter->SpawnParticle(0, 1);
	if (aToParticle == nullptr)
		return false;
	if (mEmitterCrossFadeCountDown > 0)  // If the source emitter is in the process of cross-blending
		theParticle->mCrossFadeDuration = mEmitterCrossFadeCountDown;  //The duration of the source particle's cross-mixing is the remaining duration of the source emitter's cross-mixing
	else
	{
		float aCrossFadeDurationInterp = Sexy::Rand(1);
		int aCrossFadeDuration = FloatTrackEvaluate(theToEmitter->mEmitterDef->mCrossFadeDuration, mSystemTimeValue, aCrossFadeDurationInterp);
		theParticle->mCrossFadeDuration = max(1, aCrossFadeDuration);  // Randomly obtain the duration of cross-mixing (at least 1 frame)
	}
	if (!FloatTrackIsSet(theToEmitter->mEmitterDef->mParticleDuration))  // If the target emitter has no defined particle duration
		aToParticle->mParticleDuration = theParticle->mCrossFadeDuration;  //The duration of the target particle is equal to the cross-blending time
	aToParticle->mCrossFadeParticleID = (ParticleID)mParticleSystem->mParticleHolder->mParticles.DataArrayGetID(theParticle);  //Assign the particle number of the cross-mixing source
	return true;
}

//0x517490
void TodParticleEmitter::DeleteParticle(TodParticle* theParticle)
{
	TodParticle* aCrossFadeParticle = mParticleSystem->mParticleHolder->mParticles.DataArrayTryToGet((unsigned int)theParticle->mCrossFadeParticleID);
	if (aCrossFadeParticle != nullptr)
	{
		aCrossFadeParticle->mParticleEmitter->DeleteParticle(aCrossFadeParticle);  // Delete the cross-blended source particles at the same time
		theParticle->mCrossFadeParticleID = ParticleID::PARTICLEID_NULL;
	}
	
	ParticleID aParticleID = (ParticleID)mParticleSystem->mParticleHolder->mParticles.DataArrayGetID(theParticle);
	mParticleList.RemoveAt(mParticleList.Find(aParticleID));
	mParticleSystem->mParticleHolder->mParticles.DataArrayFree(theParticle);
}

//0x517550
void TodParticleEmitter::Update()
{
	if (mDead)
		return;

	mSystemAge++;
	bool aDie = false;
	if (mSystemAge >= mSystemDuration)  // When the emitter's life cycle ends
	{
		if (TestBit(mEmitterDef->mParticleFlags, (unsigned int)ParticleFlags::PARTICLE_SYSTEM_LOOPS))  // Determine whether the emitter is looping
			mSystemAge = 0;  //Reset the current frame of the emitter
		else
		{
			mSystemAge = mSystemDuration - 1;  // Hang the emitter on the last frame
			aDie = true;
		}
	}

	if (mEmitterCrossFadeCountDown > 0)
	{
		mEmitterCrossFadeCountDown--;  // Update the emitter's cross-blend
		if (mEmitterCrossFadeCountDown == 0)
			aDie = true;
	}
	if (mCrossFadeEmitterID != ParticleEmitterID::PARTICLEEMITTERID_NULL)
	{
		TodParticleEmitter* aCrossFadeEmitter = mParticleSystem->mParticleHolder->mEmitters.DataArrayTryToGet(mCrossFadeEmitterID);
		if (aCrossFadeEmitter == nullptr || aCrossFadeEmitter->mDead)
			aDie = true;
	}

	mSystemTimeValue = mSystemAge / (float)(mSystemDuration - 1);
	for (int i = 0; i < mEmitterDef->mSystemFieldCount; i++)
		UpdateSystemField(&mEmitterDef->mSystemFields[i], mSystemTimeValue, i);  // Update emitter affected by each system field
	for (TodListNode<ParticleID>* aNode = mParticleList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticle* aParticle = mParticleSystem->mParticleHolder->mParticles.DataArrayGet((unsigned int)aNode->mValue);
		if (!UpdateParticle(aParticle))  // Update each particle in the emitter
			DeleteParticle(aParticle);
	}
	UpdateSpawning();  //Update particle emission

	if (aDie)
	{
		DeleteNonCrossFading();
		if (mParticleList.mSize == 0)
		{
			mDead = true;
			return;
		}
	}
	mSystemLastTimeValue = mSystemTimeValue;
}

float CrossFadeLerp(float theFrom, float theTo, bool theFromIsSet, bool theToIsSet, float theFraction)
{
	if (!theFromIsSet)
		return theTo;
	if (!theToIsSet)
		return theFrom;
	return theFrom + (theTo - theFrom) * theFraction;
}

//0x5176A0
bool TodParticleEmitter::GetRenderParams(TodParticle* theParticle, ParticleRenderParams* theParams)
{
	register TodParticleEmitter* aEmitter = theParticle->mParticleEmitter;
	register TodEmitterDefinition* aDef = aEmitter->mEmitterDef;

	// color. For each color channel, when any of the system corresponding track, particle corresponding track and corresponding override is defined, the channel is considered to be set.
	theParams->mRedIsSet = false;
	theParams->mRedIsSet |= FloatTrackIsSet(aDef->mSystemRed);
	theParams->mRedIsSet |= FloatTrackIsSet(aDef->mParticleRed);
	theParams->mRedIsSet |= aEmitter->mColorOverride.mRed != 1.0f;
	theParams->mGreenIsSet = false;
	theParams->mGreenIsSet |= FloatTrackIsSet(aDef->mSystemGreen);
	theParams->mGreenIsSet |= FloatTrackIsSet(aDef->mParticleGreen);
	theParams->mGreenIsSet |= aEmitter->mColorOverride.mGreen != 1.0f;
	theParams->mBlueIsSet = false;
	theParams->mBlueIsSet |= FloatTrackIsSet(aDef->mSystemBlue);
	theParams->mBlueIsSet |= FloatTrackIsSet(aDef->mParticleBlue);
	theParams->mBlueIsSet |= aEmitter->mColorOverride.mBlue != 1.0f;
	theParams->mAlphaIsSet = false;
	theParams->mAlphaIsSet |= FloatTrackIsSet(aDef->mSystemAlpha);
	theParams->mAlphaIsSet |= FloatTrackIsSet(aDef->mParticleAlpha);
	theParams->mAlphaIsSet |= aEmitter->mColorOverride.mAlpha != 1.0f;
	// zoom
	theParams->mParticleScaleIsSet = false;
	theParams->mParticleScaleIsSet |= FloatTrackIsSet(aDef->mParticleScale);
	theParams->mParticleScaleIsSet |= (aEmitter->mScaleOverride != 1.0f);
	// stretch
	theParams->mParticleStretchIsSet = FloatTrackIsSet(aDef->mParticleStretch);
	// Rotation angle. The rotation angle is also considered set when the particles use a random initial rotation angle or an aligned emission direction angle.
	theParams->mSpinPositionIsSet = false;
	theParams->mSpinPositionIsSet |= FloatTrackIsSet(aDef->mParticleSpinSpeed);
	theParams->mSpinPositionIsSet |= FloatTrackIsSet(aDef->mParticleSpinAngle);
	theParams->mSpinPositionIsSet |= TestBit(aDef->mParticleFlags, (int)ParticleFlags::PARTICLE_RANDOM_LAUNCH_SPIN);
	theParams->mSpinPositionIsSet |= TestBit(aDef->mParticleFlags, (int)ParticleFlags::PARTICLE_ALIGN_LAUNCH_SPIN);
	// Location
	theParams->mPositionIsSet = false;
	theParams->mPositionIsSet |= (aDef->mParticleFieldCount > 0.0f);
	theParams->mPositionIsSet |= FloatTrackIsSet(aDef->mEmitterRadius);
	theParams->mPositionIsSet |= FloatTrackIsSet(aDef->mEmitterOffsetX);
	theParams->mPositionIsSet |= FloatTrackIsSet(aDef->mEmitterOffsetY);
	theParams->mPositionIsSet |= FloatTrackIsSet(aDef->mEmitterBoxX);
	theParams->mPositionIsSet |= FloatTrackIsSet(aDef->mEmitterBoxY);

	float aSystemRed = aEmitter->SystemTrackEvaluate(aDef->mSystemRed, ParticleSystemTracks::TRACK_SYSTEM_RED);
	float aSystemGreen = aEmitter->SystemTrackEvaluate(aDef->mSystemGreen, ParticleSystemTracks::TRACK_SYSTEM_GREEN);
	float aSystemBlue = aEmitter->SystemTrackEvaluate(aDef->mSystemBlue, ParticleSystemTracks::TRACK_SYSTEM_BLUE);
	float aSystemAlpha = aEmitter->SystemTrackEvaluate(aDef->mSystemAlpha, ParticleSystemTracks::TRACK_SYSTEM_ALPHA);
	float aSystemBrightness = aEmitter->SystemTrackEvaluate(aDef->mSystemBrightness, ParticleSystemTracks::TRACK_SYSTEM_BRIGHTNESS);
	float aParticleRed = aEmitter->ParticleTrackEvaluate(aDef->mParticleRed, theParticle, ParticleTracks::TRACK_PARTICLE_RED);
	float aParticleGreen = aEmitter->ParticleTrackEvaluate(aDef->mParticleGreen, theParticle, ParticleTracks::TRACK_PARTICLE_GREEN);
	float aParticleBlue = aEmitter->ParticleTrackEvaluate(aDef->mParticleBlue, theParticle, ParticleTracks::TRACK_PARTICLE_BLUE);
	float aParticleAlpha = aEmitter->ParticleTrackEvaluate(aDef->mParticleAlpha, theParticle, ParticleTracks::TRACK_PARTICLE_ALPHA);
	float aParticleBrightness = aEmitter->ParticleTrackEvaluate(aDef->mParticleBrightness, theParticle, ParticleTracks::TRACK_PARTICLE_BRIGHTNESS);
	float aBrightness = aParticleBrightness * aSystemBrightness;
	// Actual color = particle color * system color * override color * brightness
	theParams->mRed = aParticleRed * aSystemRed * aEmitter->mColorOverride.mRed * aBrightness;
	theParams->mGreen = aParticleGreen * aSystemGreen * aEmitter->mColorOverride.mGreen * aBrightness;
	theParams->mBlue = aParticleBlue * aSystemBlue * aEmitter->mColorOverride.mBlue * aBrightness;
	theParams->mAlpha = aParticleAlpha * aSystemAlpha * aEmitter->mColorOverride.mAlpha * aBrightness;
	theParams->mPosX = theParticle->mPosition.x;
	theParams->mPosY = theParticle->mPosition.y;
	float aParticleScale = aEmitter->ParticleTrackEvaluate(aDef->mParticleScale, theParticle, ParticleTracks::TRACK_PARTICLE_SCALE);
	theParams->mParticleStretch = aEmitter->ParticleTrackEvaluate(aDef->mParticleStretch, theParticle, ParticleTracks::TRACK_PARTICLE_STRETCH);
	theParams->mParticleScale = aParticleScale * aEmitter->mScaleOverride;
	theParams->mSpinPosition = theParticle->mSpinPosition;

	TodParticle* aCrossFadeParticle = aEmitter->mParticleSystem->mParticleHolder->mParticles.DataArrayTryToGet((unsigned int)theParticle->mCrossFadeParticleID);
	if (aCrossFadeParticle != nullptr)  // When there are cross-mixed particles, mix the rendering parameters of the two (cross-mixing from aCrossFadeParticle to theParticle)
	{
		ParticleRenderParams aCrossFadeParams;
		if (TodParticleEmitter::GetRenderParams(aCrossFadeParticle, &aCrossFadeParams))
		{
			float aFraction = theParticle->mParticleAge / (float)(aCrossFadeParticle->mCrossFadeDuration - 1);
			// Each value is mixed according to the proportion of aFraction
			theParams->mRed = CrossFadeLerp(aCrossFadeParams.mRed, theParams->mRed, aCrossFadeParams.mRedIsSet, theParams->mRedIsSet, aFraction);
			theParams->mGreen = CrossFadeLerp(aCrossFadeParams.mGreen, theParams->mGreen, aCrossFadeParams.mGreenIsSet, theParams->mGreenIsSet, aFraction);
			theParams->mBlue = CrossFadeLerp(aCrossFadeParams.mBlue, theParams->mBlue, aCrossFadeParams.mBlueIsSet, theParams->mBlueIsSet, aFraction);
			theParams->mAlpha = CrossFadeLerp(aCrossFadeParams.mAlpha, theParams->mAlpha, aCrossFadeParams.mAlphaIsSet, theParams->mAlphaIsSet, aFraction);
			theParams->mParticleScale = CrossFadeLerp(
				aCrossFadeParams.mParticleScale, theParams->mParticleScale, aCrossFadeParams.mParticleScaleIsSet, theParams->mParticleScaleIsSet, aFraction);
			theParams->mParticleStretch = CrossFadeLerp(
				aCrossFadeParams.mParticleStretch, theParams->mParticleStretch, aCrossFadeParams.mParticleStretchIsSet, theParams->mParticleStretchIsSet, aFraction);
			theParams->mSpinPosition = CrossFadeLerp(
				aCrossFadeParams.mSpinPosition, theParams->mSpinPosition, aCrossFadeParams.mSpinPositionIsSet, theParams->mSpinPositionIsSet, aFraction);
			theParams->mPosX = CrossFadeLerp(aCrossFadeParams.mPosX, theParams->mPosX, aCrossFadeParams.mPositionIsSet, theParams->mPositionIsSet, aFraction);
			theParams->mPosY = CrossFadeLerp(aCrossFadeParams.mPosY, theParams->mPosY, aCrossFadeParams.mPositionIsSet, theParams->mPositionIsSet, aFraction);
			// When an item of the cross-mixing source has been set, it can be considered that the corresponding item of the particle has also been set.
			theParams->mRedIsSet |= aCrossFadeParams.mRedIsSet;
			theParams->mGreenIsSet |= aCrossFadeParams.mGreenIsSet;
			theParams->mBlueIsSet |= aCrossFadeParams.mBlueIsSet;
			theParams->mAlphaIsSet |= aCrossFadeParams.mAlphaIsSet;
			theParams->mParticleScaleIsSet |= aCrossFadeParams.mParticleScaleIsSet;
			theParams->mParticleStretchIsSet |= aCrossFadeParams.mParticleStretchIsSet;
			theParams->mSpinPositionIsSet |= aCrossFadeParams.mSpinPositionIsSet;
			theParams->mPositionIsSet |= aCrossFadeParams.mPositionIsSet;
		}
	}
	return true;
}

//0x517E20
void RenderParticle(Graphics* g, TodParticle* theParticle, const Color& theColor, ParticleRenderParams* theParams, TodTriangleGroup* theTriangleGroup)
{
	TodParticleEmitter* aEmitter = theParticle->mParticleEmitter;
	register TodEmitterDefinition* aEmitterDef = aEmitter->mEmitterDef;
	Image* aImage = aEmitter->mImageOverride != nullptr ? aEmitter->mImageOverride : aEmitterDef->mImage;  // Priority is given to using overwriting textures. If there is no overwriting texture, the defined texture will be used.
	if (aImage == nullptr)
		return;  //Cancel drawing when there is no texture

	int aCelWidth = aImage->GetCelWidth();
	int aCelHeight = aImage->GetCelHeight();
	int aFrame = aEmitter->mFrameOverride;
	if (aFrame == -1)  // If override frame is not defined
	{
		if (FloatTrackIsSet(aEmitterDef->mAnimationRate))  // If animation rate is defined
			aFrame = ClampInt(theParticle->mAnimationTimeValue * aEmitterDef->mImageFrames, 0, aEmitterDef->mImageFrames - 1);  // Animation time value (loop rate) * total number of frames to get the current frame
		else if (aEmitterDef->mAnimated)
			aFrame = ClampInt(theParticle->mParticleTimeValue * aEmitterDef->mImageFrames, 0, aEmitterDef->mImageFrames - 1);  // Particle time value * total number of frames to get the current frame
		else
			aFrame = theParticle->mImageFrame;  //For particles with a fixed frame, directly take the texture frame
	}
	aFrame += aEmitterDef->mImageCol;  // Add the current frame to the starting column of the image in the definition to get the number of columns of the current frame in the texture.
	if (aFrame >= aImage->mNumCols)
		aFrame = aImage->mNumCols - 1;

	Rect aSrcRect(aFrame * aCelWidth, min(aEmitterDef->mImageRow, aImage->mNumRows - 1) * aCelHeight, aCelWidth, aCelHeight);
	float aClipTop = TodParticleEmitter::ParticleTrackEvaluate(aEmitterDef->mClipTop, theParticle, ParticleTracks::TRACK_PARTICLE_CLIP_TOP);
	float aClipBottom = TodParticleEmitter::ParticleTrackEvaluate(aEmitterDef->mClipBottom, theParticle, ParticleTracks::TRACK_PARTICLE_CLIP_BOTTOM);
	float aClipLeft = TodParticleEmitter::ParticleTrackEvaluate(aEmitterDef->mClipLeft, theParticle, ParticleTracks::TRACK_PARTICLE_CLIP_LEFT);
	float aClipRight = TodParticleEmitter::ParticleTrackEvaluate(aEmitterDef->mClipRight, theParticle, ParticleTracks::TRACK_PARTICLE_CLIP_RIGHT);
	TOD_ASSERT(aClipTop >= 0.0f && aClipTop <= 1.0f);
	TOD_ASSERT(aClipBottom >= 0.0f && aClipBottom <= 1.0f);
	TOD_ASSERT(aClipLeft >= 0.0f && aClipLeft <= 1.0f);
	TOD_ASSERT(aClipRight >= 0.0f && aClipRight <= 1.0f);
	theParams->mPosX += aClipLeft * aCelWidth;
	theParams->mPosY += aClipTop * aCelHeight;
	aSrcRect.mX += FloatRoundToInt(aClipLeft * aCelWidth);
	aSrcRect.mY += FloatRoundToInt(aClipTop * aCelHeight);
	aSrcRect.mWidth -= FloatRoundToInt(aCelWidth * (aClipLeft + aClipRight));
	aSrcRect.mHeight -= FloatRoundToInt(aCelHeight * (aClipBottom + aClipTop));  //The above adjusts the source rectangle according to the proportion of each direction of cropping
	TOD_ASSERT(aSrcRect.mX == aCelWidth * aFrame + FloatRoundToInt(aClipLeft * aCelWidth));
	TOD_ASSERT(aSrcRect.mY == aCelHeight * aEmitterDef->mImageRow + FloatRoundToInt(aClipTop * aCelHeight));
	TOD_ASSERT(aSrcRect.mX >= 0 && aSrcRect.mX < 10000);
	TOD_ASSERT(aSrcRect.mY >= 0 && aSrcRect.mY < 10000);

	if (TestBit(aEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_ALIGN_TO_PIXELS))  //Align coordinates to integer pixels
	{
		theParams->mPosX = FloatRoundToInt(theParams->mPosX);
		theParams->mPosY = FloatRoundToInt(theParams->mPosY);
	}
	int aDrawMode = g->mDrawMode;
	if (TestBit(aEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_ADDITIVE))  // Use overlay mode
		aDrawMode = Graphics::DRAWMODE_ADDITIVE;
	if (TestBit(aEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_FULLSCREEN))  // full screen mode
	{
		theTriangleGroup->DrawGroup(g);
		Color anOldColor = g->GetColor();
		int anOldDrawMode = g->GetDrawMode();
		g->SetColor(theColor);
		g->FillRect(-g->mTransX, -g->mTransY, BOARD_WIDTH, BOARD_HEIGHT);
		g->SetColor(anOldColor);
		g->SetDrawMode(anOldDrawMode);
	}
	else
	{
		SexyMatrix3 aTransform;
		TodScaleRotateTransformMatrix(
			aTransform, 
			theParams->mPosX, 
			theParams->mPosY, 
			theParams->mSpinPosition, 
			theParams->mParticleScale, 
			theParams->mParticleStretch * theParams->mParticleScale
		);
		theTriangleGroup->AddTriangle(g, aImage, aTransform, g->mClipRect, theColor, aDrawMode, aSrcRect);
		if (aEmitter->mExtraAdditiveDrawOverride)
			theTriangleGroup->AddTriangle(g, aImage, aTransform, g->mClipRect, theColor, Graphics::DRAWMODE_ADDITIVE, aSrcRect);
	}
}

//0x518210
void TodParticleEmitter::DrawParticle(Graphics* g, TodParticle* theParticle, TodTriangleGroup* theTriangleGroup)
{
	if (theParticle->mCrossFadeDuration > 0)  // Cross-mixed source particles are not drawn
		return;

	ParticleRenderParams aParams;
	if (GetRenderParams(theParticle, &aParams))
	{
		Color aColor(
			ClampInt(FloatRoundToInt(aParams.mRed), 0, 255), 
			ClampInt(FloatRoundToInt(aParams.mGreen), 0, 255), 
			ClampInt(FloatRoundToInt(aParams.mBlue), 0, 255), 
			ClampInt(FloatRoundToInt(aParams.mAlpha), 0, 255)
		);
		if (aColor.mAlpha > 0)  // When the opacity is 0, no drawing
		{
			aParams.mPosX += g->mTransX;
			aParams.mPosY += g->mTransY;

			TodParticle* aParticle;
			if (mImageOverride || mEmitterDef->mImage)  //When the particle has a texture, render the particle
				aParticle = theParticle;
			else  // When the particles have no texture, try to render the particles from the cross-mixing source.
				aParticle = mParticleSystem->mParticleHolder->mParticles.DataArrayTryToGet((unsigned int)theParticle->mCrossFadeParticleID);
			if (aParticle != nullptr)
				RenderParticle(g, aParticle, aColor, &aParams, theTriangleGroup);
		}
	}
}

//0x518370
void TodParticleSystem::Draw(Graphics* g)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
		mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue)->Draw(g);
}

//0x5183A0
void TodParticleEmitter::Draw(Graphics* g)
{
	bool aHardWare = gSexyAppBase->Is3DAccelerated();
	if ((TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_SOFTWARE_ONLY) && aHardWare) ||
		(TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_HARDWARE_ONLY) && !aHardWare))
		return;

	TodTriangleGroup aTriangleGroup;
	for (TodListNode<ParticleID>* aNode = mParticleList.mHead; aNode != nullptr; aNode = aNode->mNext)
		DrawParticle(g, mParticleSystem->mParticleHolder->mParticles.DataArrayGet((unsigned int)aNode->mValue), &aTriangleGroup);
	aTriangleGroup.DrawGroup(g);
}

//0x518440
void TodParticleSystem::SystemMove(float theX, float theY)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
		mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue)->SystemMove(theX, theY);
}

//0x518480
void TodParticleEmitter::SystemMove(float theX, float theY)
{
	float aDeltaX = theX - mSystemCenter.x;
	float aDeltaY = theY - mSystemCenter.y;
	if (FloatApproxEqual(aDeltaX, 0.0f) && FloatApproxEqual(aDeltaY, 0.0f))  // When the coordinates before and after the move are almost equal, no operation is required
		return;
	
	mSystemCenter.x = theX;
	mSystemCenter.y = theY;
	if (!TestBit(mEmitterDef->mParticleFlags, (int)ParticleFlags::PARTICLE_PARTICLES_DONT_FOLLOW))
	{
		for (TodListNode<ParticleID>* aNode = mParticleList.mHead; aNode != nullptr; aNode = aNode->mNext)
		{
			TodParticle* aParticle = mParticleSystem->mParticleHolder->mParticles.DataArrayGet((unsigned int)aNode->mValue);
			aParticle->mPosition.x += aDeltaX;
			aParticle->mPosition.y += aDeltaY;
		}
	}
}

//0x518560
void TodParticleSystem::OverrideColor(const char* theEmitterName, const Color& theColor)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (theEmitterName == nullptr || stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			aEmitter->mColorOverride = theColor;
	}
}

//0x5185D0
void TodParticleSystem::OverrideExtraAdditiveDraw(const char* theEmitterName, bool theEnableExtraAdditiveDraw)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (theEmitterName == nullptr || stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			aEmitter->mExtraAdditiveDrawOverride = theEnableExtraAdditiveDraw;
	}
}

//0x518600
void TodParticleSystem::OverrideImage(const char* theEmitterName, Image* theImage)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (theEmitterName == nullptr || stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			aEmitter->mImageOverride = theImage;
	}
}

void TodParticleSystem::OverrideFrame(const char* theEmitterName, int theFrame)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (theEmitterName == nullptr || stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			aEmitter->mFrameOverride = theFrame;
	}
}

//0x518630
void TodParticleSystem::OverrideScale(const char* theEmitterName, float theScale)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (theEmitterName == nullptr || stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			aEmitter->mScaleOverride = theScale;
	}
}

TodParticleEmitter* TodParticleSystem::FindEmitterByName(const char* theEmitterName)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			return aEmitter;
	}
	return nullptr;
}

//0x518670
TodEmitterDefinition* TodParticleSystem::FindEmitterDefByName(const char* theEmitterName)
{
	for (int i = 0; i < mParticleDef->mEmitterDefCount; i++)
	{
		TodEmitterDefinition* aEmitterDef = &mParticleDef->mEmitterDefs[i];
		if (stricmp(theEmitterName, aEmitterDef->mName) == 0)
			return aEmitterDef;
	}
	return nullptr;
}

//0x5186D0
void TodParticleEmitter::CrossFadeEmitter(TodParticleEmitter* theToEmitter)
{
	if (mEmitterCrossFadeCountDown > 0)
	{
		TodTrace("We don't support cross fading emitters more than one at a time\n");
		return;
	}
	if (!FloatTrackIsSet(theToEmitter->mEmitterDef->mCrossFadeDuration))
	{
		TodTrace("Can't cross fade to emitter that doesn't have CrossFadeDuration");
		return;
	}
	TOD_ASSERT(theToEmitter != this);

	float aCrossFadeDurationInterp = Sexy::Rand(1.0f);
	mEmitterCrossFadeCountDown = FloatTrackEvaluate(theToEmitter->mEmitterDef->mCrossFadeDuration, mSystemTimeValue, aCrossFadeDurationInterp);
	mEmitterCrossFadeCountDown = max(1, mEmitterCrossFadeCountDown);
	mCrossFadeEmitterID = (ParticleEmitterID)mParticleSystem->mParticleHolder->mEmitters.DataArrayGetID(theToEmitter);
	if (!FloatTrackIsSet(theToEmitter->mEmitterDef->mSystemDuration))
		theToEmitter->mSystemDuration = mEmitterCrossFadeCountDown;

	for (TodListNode<ParticleID>* aNode = mParticleList.mHead; aNode != nullptr; aNode = aNode->mNext)
		CrossFadeParticle(mParticleSystem->mParticleHolder->mParticles.DataArrayGet((unsigned int)aNode->mValue), theToEmitter);
}

//0x518790
void TodParticleSystem::CrossFade(const char* theEmitterName)
{
	TodEmitterDefinition* aEmitterDef = FindEmitterDefByName(theEmitterName);
	if (aEmitterDef == nullptr)
	{
		TodTrace("Can't find cross fade emitter: %s\n", theEmitterName);
		return;
	}
	if (!FloatTrackIsSet(aEmitterDef->mCrossFadeDuration))
	{
		TodTrace("Can't cross fade without duration set: %s\n", theEmitterName);
		return;
	}
	if (mParticleHolder->mEmitters.mSize + mEmitterList.mSize > mParticleHolder->mEmitters.mMaxSize)
	{
		TodTrace("Too many emitters to cross fade\n");
		ParticleSystemDie();
		return;
	}

	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (aEmitter->mEmitterDef != aEmitterDef)  // Cannot be cross-mixed to emitters of the same type
		{
			TodParticleEmitter* aCrossFadeEmitter = mParticleHolder->mEmitters.DataArrayAlloc();
			aCrossFadeEmitter->TodEmitterInitialize(aEmitter->mSystemCenter.x, aEmitter->mSystemCenter.y, this, aEmitterDef);
			ParticleEmitterID aCrossFadeEmitterID = (ParticleEmitterID)mParticleHolder->mEmitters.DataArrayGetID(aCrossFadeEmitter);
			mEmitterList.AddTail(aCrossFadeEmitterID);
			aEmitter->CrossFadeEmitter(aCrossFadeEmitter);
		}
	}
}

//0x518870
TodParticleHolder::~TodParticleHolder()
{
	DisposeHolder();
}

//0x518900
void TodParticleHolder::InitializeHolder()
{
	mParticleSystems.DataArrayInitialize(1024U, "particle systems");
	mEmitters.DataArrayInitialize(1024U, "emitters");
	mParticles.DataArrayInitialize(1024U, "particles");
	mParticleListNodeAllocator.Initialize(1024, sizeof(TodListNode<ParticleID>));
	mEmitterListNodeAllocator.Initialize(1024, sizeof(TodListNode<ParticleEmitterID>));
}

//0x5189A0
void TodParticleHolder::DisposeHolder()
{
	mParticleSystems.DataArrayDispose();
	mEmitters.DataArrayDispose();
	mParticles.DataArrayDispose();
	mParticleListNodeAllocator.FreeAll();
	mEmitterListNodeAllocator.FreeAll();
}

bool TodParticleHolder::IsOverLoaded()
{
	return mParticleSystems.mSize > MAX_PARTICLES_SIZE || mEmitters.mSize > MAX_PARTICLES_SIZE || mParticles.mSize > MAX_PARTICLES_SIZE;
}

TodParticleSystem* TodParticleHolder::AllocParticleSystemFromDef(float theX, float theY, int theRenderOrder, TodParticleDefinition* theDefinition, ParticleEffect theParticleEffect)
{
	if (mParticleSystems.mSize == mParticleSystems.mMaxSize)
	{
		TodTrace("Too many particle systems\n");
		return nullptr;
	}
	if (theDefinition->mEmitterDefCount + mEmitters.mSize > mEmitters.mMaxSize)
	{
		TodTrace("Too many particle emitters\n");
		return nullptr;
	}

	TodParticleSystem* aTodParticle = mParticleSystems.DataArrayAlloc();
	aTodParticle->mParticleHolder = this;
	aTodParticle->TodParticleInitializeFromDef(theX, theY, theRenderOrder, theDefinition, theParticleEffect);
	return aTodParticle;
}

//0x518A70
TodParticleSystem* TodParticleHolder::AllocParticleSystem(float theX, float theY, int theRenderOrder, ParticleEffect theParticleEffect)
{
	TOD_ASSERT((int)theParticleEffect >= 0 && (int)theParticleEffect < gParticleDefCount);
	return AllocParticleSystemFromDef(theX, theY, theRenderOrder, &gParticleDefArray[(int)theParticleEffect], theParticleEffect);
}
