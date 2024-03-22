#ifndef __TODFOLEY_H__
#define __TODFOLEY_H__

#include "../Resources.h"
#include "../SexyAppFramework/DSoundInstance.h"
using namespace Sexy;

#define MAX_FOLEY_TYPES 110
#define MAX_FOLEY_INSTANCES 8

// ######################################################################################################################################################
// ############################################################# 以下为拟音音效定义相关内容 #############################################################
// ######################################################################################################################################################

enum FoleyFlags
{
    FOLEYFLAGS_LOOP,                // Loop
    FOLEYFLAGS_ONE_AT_A_TIME,       // Disable overlay playback: Specify that there is at most 1 instance of this type of sound effect at the same time. When played repeatedly, only the reference count will be increased and the start time will be refreshed.
    FOLEYFLAGS_MUTE_ON_PAUSE,       // Silent when paused
    FOLEYFLAGS_USES_MUSIC_VOLUME,   // Use music volume, specify that this type of sound effect uses the same volume as the background music
    FOLEYFLAGS_DONT_REPEAT          // Variation duplication is prohibited. The actual variation played each time for a specified type of sound effect must not be the same as the last time.
};

enum FoleyType
{
    FOLEY_SUN,
    FOLEY_SPLAT,
    FOLEY_LAWNMOWER,
    FOLEY_THROW,
    FOLEY_SPAWN_SUN,
    FOLEY_CHOMP,
    FOLEY_CHOMP_SOFT,
    FOLEY_PLANT,
    FOLEY_USE_SHOVEL,
    FOLEY_DROP,
    FOLEY_BLEEP,
    FOLEY_GROAN,
    FOLEY_BRAINS,
    FOLEY_SUKHBIR,
    FOLEY_JACKINTHEBOX,
    FOLEY_ART_CHALLENGE,
    FOLEY_ZAMBONI,
    FOLEY_THUNDER,
    FOLEY_FROZEN,
    FOLEY_ZOMBIESPLASH,
    FOLEY_BOWLINGIMPACT,
    FOLEY_SQUISH,
    FOLEY_TIRE_POP,
    FOLEY_EXPLOSION,
    FOLEY_SLURP,
    FOLEY_LIMBS_POP,
    FOLEY_POGO_ZOMBIE,
    FOLEY_SNOW_PEA_SPARKLES,
    FOLEY_ZOMBIE_FALLING,
    FOLEY_PUFF,
    FOLEY_FUME,
    FOLEY_COIN,
    FOLEY_KERNEL_SPLAT,
    FOLEY_DIGGER,
    FOLEY_JACK_SURPRISE,
    FOLEY_VASE_BREAKING,
    FOLEY_POOL_CLEANER,
    FOLEY_BASKETBALL,
    FOLEY_IGNITE,
    FOLEY_FIREPEA,
    FOLEY_THUMP,
    FOLEY_SQUASH_HMM,
    FOLEY_MAGNETSHROOM,
    FOLEY_BUTTER,
    FOLEY_BUNGEE_SCREAM,
    FOLEY_BOSS_EXPLOSION_SMALL,
    FOLEY_SHIELD_HIT,
    FOLEY_SWING,
    FOLEY_BONK,
    FOLEY_RAIN,
    FOLEY_DOLPHIN_BEFORE_JUMPING,
    FOLEY_DOLPHIN_APPEARS,
    FOLEY_PLANT_WATER,
    FOLEY_ZOMBIE_ENTERING_WATER,
    FOLEY_GRAVEBUSTERCHOMP,
    FOLEY_CHERRYBOMB,
    FOLEY_JALAPENO_IGNITE,
    FOLEY_REVERSE_EXPLOSION,
    FOLEY_PLASTIC_HIT,
    FOLEY_WINMUSIC,
    FOLEY_BALLOONINFLATE,
    FOLEY_BIGCHOMP,
    FOLEY_MELONIMPACT,
    FOLEY_PLANTGROW,
    FOLEY_SHOOP,
    FOLEY_JUICY,
    FOLEY_NEWSPAPER_RARRGH,
    FOLEY_NEWSPAPER_RIP,
    FOLEY_FLOOP,
    FOLEY_COFFEE,
    FOLEY_LOW_GROAN,
    FOLEY_PRIZE,
    FOLEY_YUCK,
    FOLEY_UMBRELLA,
    FOLEY_GRASSSTEP,
    FOLEY_SHOVEL,
    FOLEY_COB_LAUNCH,
    FOLEY_WATERING,
    FOLEY_POLEVAULT,
    FOLEY_GRAVESTONE_RUMBLE,
    FOLEY_DIRT_RISE,
    FOLEY_FERTILIZER,
    FOLEY_PORTAL,
    FOLEY_WAKEUP,
    FOLEY_BUGSPRAY,
    FOLEY_SCREAM,
    FOLEY_PAPER,
    FOLEY_MONEYFALLS,
    FOLEY_IMP,
    FOLEY_HYDRAULIC_SHORT,
    FOLEY_HYDRAULIC,
    FOLEY_GARGANTUDEATH,
    FOLEY_CERAMIC,
    FOLEY_BOSS_BOULDER_ATTACK,
    FOLEY_CHIME,
    FOLEY_CRAZY_DAVE_SHORT,
    FOLEY_CRAZY_DAVE_LONG,
    FOLEY_CRAZY_DAVE_EXTRA_LONG,
    FOLEY_CRAZY_DAVE_CRAZY,
    FOLEY_PHONOGRAPH,
    FOLEY_DANCER,
    FOLEY_FINAL_FANFARE,
    FOLEY_CRAZY_DAVE_SCREAM,
    FOLEY_CRAZY_DAVE_SCREAM_2,
    NUM_FOLEY
};

class FoleyParams
{
public:
    FoleyType           mFoleyType;
    float               mPitchRange;
    int*                mSfxID[10];
    unsigned int        mFoleyFlags;
};

/*inline*/ void         TodFoleyInitialize(FoleyParams* theFoleyParamArray, int theFoleyParamArraySize);
/*inline*/ void         TodFoleyDispose();
FoleyParams*            LookupFoley(FoleyType theFoleyType);

extern int gFoleyParamArraySize;        //[0x6A9F04]
extern FoleyParams* gFoleyParamArray;   //[0x6A9F00]

extern FoleyParams gLawnFoleyParamArray[(int)FoleyType::NUM_FOLEY];  //0x69FAD0

// ######################################################################################################################################################
// ############################################################ 以下正式开始拟音音效相关声明 ############################################################
// ######################################################################################################################################################

class TodDSoundInstance : public DSoundInstance
{
    friend class TodFoley;

public:
    TodDSoundInstance(DSoundManager* theSoundManager, LPDIRECTSOUNDBUFFER theSourceSound) : DSoundInstance(theSoundManager, theSourceSound) { }

    /*inline*/ int      GetSoundPosition();
    /*inline*/ void     SetSoundPosition(int thePosition);
};

class FoleyInstance
{
public:
    SoundInstance*      mInstance;
    int                 mRefCount;
    bool                mPaused;
    int                 mStartTime;
    int                 mPauseOffset;

public:
    FoleyInstance();
};

class FoleyTypeData
{
public:
    FoleyInstance       mFoleyInstances[MAX_FOLEY_INSTANCES];
    int                 mLastVariationPlayed;

public:
    FoleyTypeData();
};

class TodFoley
{
public:
    FoleyTypeData	    mFoleyTypeData[MAX_FOLEY_TYPES];

public:
    void                PlayFoley(FoleyType theFoleyType);
    void                StopFoley(FoleyType theFoleyType);
    bool                IsFoleyPlaying(FoleyType theFoleyType);
    void                GamePause(bool theEnteringPause);
    void                PlayFoleyPitch(FoleyType theFoleyType, float thePitch);
    void                CancelPausedFoley();
    /*inline*/ void     ApplyMusicVolume(FoleyInstance* theFoleyInstance);
    void                RehookupSoundWithMusicVolume();
};

void                    SoundSystemReleaseFinishedInstances(TodFoley* theSoundSystem);
bool                    SoundSystemHasFoleyPlayedTooRecently(TodFoley* theSoundSystem, FoleyType theFoleyType);
FoleyInstance*          SoundSystemFindInstance(TodFoley* theSoundSystem, FoleyType theFoleyType);
FoleyInstance*          SoundSystemGetFreeInstanceIndex(TodFoley* theSoundSystem, FoleyType theFoleyType);

#endif
