#include "DataSync.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "../../SexyAppFramework/SexyAppBase.h"

using namespace Sexy;
static int gProfileVersion = 14;

//0x46A7C0
PlayerInfo* ProfileMgr::GetAnyProfile()
{
    if (mProfileMap.size() == 0)
        return nullptr;

    PlayerInfo* aPlayerInfo = &mProfileMap.begin()->second;
    aPlayerInfo->LoadDetails();
    aPlayerInfo->mUseSeq = mNextProfileUseSeq++;
    return aPlayerInfo;
}

//0x46A7F0
void ProfileMgr::Clear()
{
    mProfileMap.clear();
    mNextProfileId = 1U;
    mNextProfileUseSeq = 1U;
}

//0x46A830
void ProfileMgr::SyncState(DataSync& theSync)
{
    DataReader* aReader = theSync.GetReader();
    DataWriter* aWriter = theSync.GetWriter();

    int aVersion = gProfileVersion;
    theSync.SyncLong(aVersion);
    theSync.SetVersion(aVersion);
    if (aVersion == gProfileVersion)
    {
        if (aReader)
        {
            mProfileMap.clear();

            int aMaxProfileId = 0;
            int aMaxUseSeq = 0;
            for (int aProfileCount = aReader->ReadShort(); aProfileCount > 0; aProfileCount--)
            {
                PlayerInfo aProfile;
                aProfile.SyncSummary(theSync);

                if (aProfile.mId > aMaxProfileId)
                    aMaxProfileId = aProfile.mId;
                if (aProfile.mUseSeq > aMaxUseSeq)
                    aMaxUseSeq = aProfile.mUseSeq;

                mProfileMap[aProfile.mName] = aProfile;
            }

            mNextProfileId = aMaxProfileId + 1;
            mNextProfileUseSeq = aMaxUseSeq + 1;
        }
        else
        {
            aWriter->WriteShort((short)mProfileMap.size());
            
            for (auto anItr = mProfileMap.begin(); anItr != mProfileMap.end(); anItr++)
                anItr->second.SyncSummary(theSync);
        }
    }
}

//0x46ABC0
void ProfileMgr::Load()
{
    Buffer aBuffer;
    std::string aFileName = GetAppDataFolder() + "userdata/users.dat";

    try
    {
        if (gSexyAppBase->ReadBufferFromFile(aFileName, &aBuffer, false))
        {
            DataReader aReader;
            aReader.OpenMemory(aBuffer.GetDataPtr(), aBuffer.GetDataLen(), false);
            DataSync aSync(aReader);
            SyncState(aSync);
        }
    }
    catch (DataReaderException&)
    {
        Clear();
    }
}

//0x46AD80
void ProfileMgr::Save()
{
    DataWriter aWriter;
    aWriter.OpenMemory(0x20);
    DataSync aSync(aWriter);
    SyncState(aSync);

    MkDir(GetAppDataFolder() + "userdata");
    std::string aFileName = GetAppDataFolder() + "userdata/users.dat";
    gSexyAppBase->WriteBytesToFile(aFileName, aWriter.GetDataPtr(), aWriter.GetDataLen());
}

void ProfileMgr::DeleteProfile(ProfileMap::iterator theProfile)
{
    theProfile->second.DeleteUserFiles();
    mProfileMap.erase(theProfile);
}

//0x46AF70
bool ProfileMgr::DeleteProfile(const SexyString& theName)
{
    auto anItr = mProfileMap.find(theName);
    if (anItr == mProfileMap.end())
        return false;

    DeleteProfile(anItr);
    return true;
}

//0x46AFF0
bool ProfileMgr::RenameProfile(const SexyString& theOldName, const SexyString& theNewName)
{
    auto anOldItr = mProfileMap.find(theOldName);
    if (anOldItr == mProfileMap.end())
        return false;
    else
    {
        // Determine whether the user names before and after modification are consistent. If they are consistent, modify them directly in the original archive. Otherwise, additional operations are required.
        if (_stricmp(theOldName.c_str(), theNewName.c_str()) == 0)
            anOldItr->second.mName = theNewName;
        else
        {
            // Insert a pair consisting of new username and old profile into mProfileMap
            auto aRet = mProfileMap.emplace(theNewName, anOldItr->second);  // auto aRet = mProfileMap.insert({theNewName, anOldItr->second});
            // Use the return value to check whether the new username is the same as the original archive. If it is repeated, false will be returned. If the insertion is successful, continue the operation.
            if (!aRet.second)
                return false;
            else
            {
                // Delete the key-value pairs of the original username and old archive in mProfileMap
                mProfileMap.erase(anOldItr);
                // Modify the username archived in the newly inserted key-value pair
                aRet.first->second.mName = theNewName;
            }
        }
        return true;
    }
}

//0x46B1C0
void ProfileMgr::DeleteOldestProfile()
{
    if (mProfileMap.size() == 0)
        return;

    // Record the location of the smallest archive of mUseSeq in the anOldest iterator
    auto anOldest = mProfileMap.begin();
    for (auto anItr = anOldest; anItr != mProfileMap.end(); anItr++)
        if (anItr->second.mUseSeq < anOldest->second.mUseSeq)
            anOldest = anItr;
    // mUseSeq minimal archive of deleted records
    DeleteProfile(anOldest);
}

//0x46B290
PlayerInfo* ProfileMgr::GetProfile(const SexyString& theName)
{
    auto anItr = mProfileMap.find(theName);
    if (anItr != mProfileMap.end())
    {
        PlayerInfo* aProfile = &anItr->second;
        aProfile->LoadDetails();
        aProfile->mUseSeq = mNextProfileUseSeq++;
        return aProfile;
    }
    return nullptr;
}

//0x46B310
PlayerInfo* ProfileMgr::AddProfile(const SexyString& theName)
{
    auto aRet = mProfileMap.emplace(theName, PlayerInfo());
    if (aRet.second)
    {
        PlayerInfo* aProfile = &aRet.first->second;
        aProfile->mName = theName;
        aProfile->mId = mNextProfileId++;
        aProfile->mUseSeq = mNextProfileUseSeq++;
        DeleteOldProfiles();
        return aProfile;
    }
    return nullptr;
}
