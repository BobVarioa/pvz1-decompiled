#include "TodDebug.h"
#include "TodCommon.h"
#include "TodStringFile.h"
#include "../PakLib/PakInterface.h"
#include "../SexyAppFramework/Font.h"

int gTodStringFormatCount;               //[0x69DE4C]
TodStringListFormat* gTodStringFormats;  //[0x69DA34]

int gLawnStringFormatCount = 12;
TodStringListFormat gLawnStringFormats[14] = {    //0x6A5010
	{ "NORMAL",           nullptr,    Color(40,   50,     90,     255),       0,      0U },
	{ "FLAVOR",           nullptr,    Color(143,  67,     27,     255),       0,      1U },
	{ "KEYWORD",          nullptr,    Color(143,  67,     27,     255),       0,      0U },
	{ "NOCTURNAL",        nullptr,    Color(136,  50,     170,    255),       0,      0U },
	{ "AQUATIC",          nullptr,    Color(11,   161,    219,    255),       0,      0U },
	{ "STAT",             nullptr,    Color(204,  36,     29,     255),       0,      0U },
	{ "METAL",            nullptr,    Color(204,  36,     29,     255),       0,      2U },
	{ "KEYMETAL",         nullptr,    Color(143,  67,     27,     255),       0,      2U },
	{ "SHORTLINE",        nullptr,    Color(0,    0,      0,      0),         -9,     0U },
	{ "EXTRASHORTLINE",   nullptr,    Color(0,    0,      0,      0),         -14,    0U },
	{ "CREDITS1",         nullptr,    Color(0,    0,      0,      0),         3,      0U },
	{ "CREDITS2",         nullptr,    Color(0,    0,      0,      0),         2,      0U },
	{ "NORMAL",           nullptr,    Color(40,   50,     90,     255),       0,      0U },
	{ "KEYWORD",          nullptr,    Color(143,  67,     27,     255),       0,      0U }
};

TodStringListFormat::TodStringListFormat()
{
	mFormatName = "";
	mNewFont = nullptr;
	mLineSpacingOffset = 0;
	mFormatFlags = 0U;
}

TodStringListFormat::TodStringListFormat(const char* theFormatName, Font** theFont, const Color& theColor, int theLineSpacingOffset, unsigned int theFormatFlags) : 
	mFormatName(theFormatName), mNewFont(theFont), mNewColor(theColor), mLineSpacingOffset(theLineSpacingOffset), mFormatFlags(theFormatFlags)
{ 
}

void TodStringListSetColors(TodStringListFormat* theFormats, int theCount)
{
	gTodStringFormats = theFormats;
	gTodStringFormatCount = theCount;
}

//0x518E40
bool TodStringListReadName(const char*& thePtr, std::string& theName)
{
	const char* aNameStart = strchr(thePtr, '[');
	if (aNameStart == nullptr)  // If "[" does not exist in the text
	{
		if (strspn(thePtr, " \n\r\t") != strlen(thePtr))  // If the text is not all whitespace characters
		{
			TodTrace("Failed to find string name");
			return false;
		}

		theName = "";
		return true;
	}
	else
	{
		const char* aNameEnd = strchr(aNameStart + 1, ']');
		if (aNameEnd == nullptr)  // If there is no "]" after "["
		{
			TodTrace("Failed to find ']'");
			return false;
		}

		int aCount = aNameEnd - aNameStart - 1;
		theName = Sexy::Trim(string(aNameStart + 1, aCount));  // Get the part between square brackets and remove the whitespace characters before and after the string
		if (theName.size() == 0)
		{
			TodTrace("Name Too Short");
			return false;
		}

		thePtr += aCount + 2;  //Move the read pointer to after "]"
		return true;
	}
}

//0x518F60
void TodStringRemoveReturnChars(std::string& theString)
{
	for (int i = 0; i < theString.size(); )
	{
		if (theString[i] == '\r')
			theString.replace(i, 1, "", 0);  // The "1" and """ here in the original version have been inlined into the function
		else
			i++;
	}
}

//0x518FB0
bool TodStringListReadValue(const char*& thePtr, std::string& theValue)
{
	const char* aValueEnd = strchr(thePtr, '[');
	int aLen = aValueEnd ? aValueEnd - thePtr : strlen(thePtr);
	theValue = Sexy::Trim(string(thePtr, aLen));  // If there is the next "[", get until before "["; otherwise, get all the rest
	TodStringRemoveReturnChars(theValue);  // Remove all newlines
	thePtr += aLen;  //Move the reading pointer to "[" (or the end)
	return true;
}

//0x519080
bool TodStringListReadItems(const char* theFileText)
{
	const char* aPtr = theFileText;
	std::string aName;
	std::string aValue;

	for (;;)
	{
		if (!TodStringListReadName(aPtr, aName))  //Read a tag
			return false;
		if (aName.size() == 0)  // The reading is successful but no tag is read, indicating that the reading is completed
			return true;
		if (!TodStringListReadValue(aPtr, aValue))  //Read the corresponding content
			return false;

		std::string aNameUpper = Sexy::StringToUpper(aName);
		gSexyAppBase->SetString(aNameUpper, Sexy::StringToWString(aValue));
	}
}

//0x519240
bool TodStringListReadFile(const char* theFileName)
{
	PFILE* pFile = p_fopen(theFileName, "rb");
	if (pFile == nullptr)
	{
		TodTrace("Failed to open '%s'", theFileName);
		return false;
	}

	p_fseek(pFile, 0, SEEK_END);  //Adjust the pointer to the end of the file
	int aSize = p_ftell(pFile);  //The current position is the file length
	p_fseek(pFile, 0, SEEK_SET);  //The pointer is moved back to the beginning of the file
	char* aFileText = new char[aSize + 1];
	bool aSuccess = true;
	if (p_fread(aFileText, sizeof(char), aSize, pFile) <= 0)  //Read data by bytes
	{
		TodTrace("Failed to read '%s'", theFileName);
		aSuccess = false;
	}
	aFileText[aSize] = '\0';
	if (aSuccess)
	{
		aSuccess = TodStringListReadItems(aFileText);
	}
	p_fclose(pFile);  // Close the file stream
	delete[] aFileText;

	return aSuccess;
}

//0x519390
void TodStringListLoad(const char* theFileName)
{
	if (!TodStringListReadFile(theFileName))
		TodErrorMessageBox(Sexy::StrFormat("Failed to load string list file '%s'", theFileName).c_str(), "Error");
}

//0x519410
SexyString TodStringListFind(const SexyString& theName)
{
	std::string aNameString = Sexy::SexyStringToString(theName);
	StringWStringMap::iterator anItr = gSexyAppBase->mStringProperties.find(aNameString);
	if (anItr != gSexyAppBase->mStringProperties.end())
	{
		return Sexy::WStringToSexyString(anItr->second);
	}
	else
	{
		return Sexy::StrFormat(_S("<Missing %s>"), theName.c_str());
	}
}

//0x519520
SexyString TodStringTranslate(const SexyString& theString)
{
	if (theString.size() >= 3 && theString[0] == '[')
	{
		SexyString aName = theString.substr(1, theString.size() - 2);  // Take the part between "[" and "]"
		return TodStringListFind(aName);
	}
	return theString;
}

//0x5195D0
SexyString TodStringTranslate(const SexyChar* theString)
{
	if (theString != nullptr)
	{
		int aLen = strlen(theString);
		if (aLen >= 3 && theString[0] == '[')
		{
			SexyString aName(theString, 1, aLen - 2);  // Take the part between "[" and "]"
			return TodStringListFind(aName);
		}
		else
			return theString;
	}
	else
		return "";
}

//0x5196C0
bool TodStringListExists(const SexyString& theString)
{
	if (theString.size() >= 3 && theString[0] == '[')
	{
		SexyString aName = theString.substr(1, theString.size() - 2);  // Take the part between "[" and "]"
		return gSexyAppBase->mStringProperties.find(aName) != gSexyAppBase->mStringProperties.end();
	}
	return false;
}

//0x5197B0
void TodWriteStringSetFormat(const char* theFormat, TodStringListFormat& theCurrentFormat)
{
	for (int i = 0; i < gTodStringFormatCount; i++)
	{
		const TodStringListFormat& aFormat = gTodStringFormats[i];
		if (strncmp(theFormat, aFormat.mFormatName, strlen(aFormat.mFormatName)) == 0)
		{
			if (aFormat.mNewFont != nullptr)
				theCurrentFormat.mNewFont = aFormat.mNewFont;
			if (aFormat.mNewColor != Color(0, 0, 0, 0))
				theCurrentFormat.mNewColor = aFormat.mNewColor;
			theCurrentFormat.mLineSpacingOffset = aFormat.mLineSpacingOffset;
			theCurrentFormat.mFormatFlags = aFormat.mFormatFlags;
			return;
		}
	}
}

bool CharIsSpaceInFormat(char theChar, const TodStringListFormat& theCurrentFormat)
{
	return theChar == ' ' || (TestBit(theCurrentFormat.mFormatFlags, TodStringFormatFlag::TOD_FORMAT_IGNORE_NEWLINES) && theChar == '\n');
}

//0x519870
int TodWriteString(Graphics* g, const SexyString& theString, int theX, int theY, TodStringListFormat& theCurrentFormat, int theWidth, DrawStringJustification theJustification, bool drawString, int theOffset, int theLength)
{
	Font* aFont = *theCurrentFormat.mNewFont;
	if (drawString)  // If actual drawing is required
	{
		int aSpareX = theWidth - TodWriteString(g, theString, theX, theY, theCurrentFormat, theWidth, DrawStringJustification::DS_ALIGN_LEFT, false, theOffset, theLength);
		switch (theJustification)  //Adjust the actual drawn abscissa according to the alignment
		{
		case DrawStringJustification::DS_ALIGN_RIGHT:
		case DrawStringJustification::DS_ALIGN_RIGHT_VERTICAL_MIDDLE:
			theX += aSpareX;
			break;
		case DrawStringJustification::DS_ALIGN_CENTER:
		case DrawStringJustification::DS_ALIGN_CENTER_VERTICAL_MIDDLE:
			theX += aSpareX / 2;
			break;
		}
	}

	if (theLength < 0 || theOffset + theLength > theString.size())
		theLength = theString.size();
	else
		theLength = theOffset + theLength;  //Change theLength to the end of the substring

	SexyString aString;
	int aXOffset = 0;
	bool aPrevCharWasSpace = false;
	for (int i = theOffset; i < theLength; i++)
	{
		if (theString[i] == '{')
		{
			const char* aFormatStart = theString.c_str() + i;
			const char* aFormatEnd = strchr(aFormatStart + 1, '}');
			if (aFormatEnd != nullptr)  // If the complete "{FORMAT}" control character is present
			{
				i += aFormatEnd - aFormatStart;  // i 移动至 "}" 处
				if (drawString)  // If actual drawing is required
					aFont->DrawString(g, theX + aXOffset, theY, aString, theCurrentFormat.mNewColor, g->mClipRect);  // Draw the accumulated characters
				
				aXOffset += aFont->StringWidth(aString);  //The horizontal offset value plus the width of the drawn string
				aString.assign("");  // Clear the string
				TodWriteStringSetFormat(aFormatStart + 1, theCurrentFormat);  //Adjust the format according to the current control character
				Font* aFont = *theCurrentFormat.mNewFont;
			}
		}
		else
		{
			if (TestBit(theCurrentFormat.mFormatFlags, TodStringFormatFlag::TOD_FORMAT_IGNORE_NEWLINES))  // If newlines are treated as spaces
			{
				if (CharIsSpaceInFormat(theString[i], theCurrentFormat))  // If the current character is a space
				{
					if (!aPrevCharWasSpace)  // If the previous character is not a space
						aString.append(1, ' ');  // Accumulate a space
					continue;
				}
				else
					aPrevCharWasSpace = false;  // Ensure that at most 1 consecutive space character appears in the string
			}

			aString.append(1, theString[i]);
		}
	}

	if (drawString)  // If actual drawing is required
		aFont->DrawString(g, theX + aXOffset, theY, aString, theCurrentFormat.mNewColor, g->mClipRect);  // Draw the accumulated characters
	return aXOffset + aFont->StringWidth(aString);
}

int TodWriteWordWrappedHelper(Graphics* g, const SexyString& theString, int theX, int theY, TodStringListFormat& theCurrentFormat, int theWidth, DrawStringJustification theJustification, bool drawString, int theOffset, int theLength, int theMaxChars)
{
	if (theOffset + theLength > theMaxChars)  // If the specified substring exceeds the maximum length of the string
	{
		theLength = theMaxChars - theOffset;  // Correct substring length
		if (theLength <= 0)
			return -1;
	}
	return TodWriteString(g, theString, theX, theY, theCurrentFormat, theWidth, theJustification, drawString, theOffset, theLength);
}

//0x519B50
int TodDrawStringWrappedHelper(Graphics* g, const SexyString& theText, const Rect& theRect, Font* theFont, const Color& theColor, DrawStringJustification theJustification, bool drawString)
{
	int theMaxChars = theText.size();
	TodStringListFormat aCurrentFormat;
	aCurrentFormat.mNewFont = &theFont;
	aCurrentFormat.mNewColor = theColor;
	aCurrentFormat.mFormatName = "";
	aCurrentFormat.mLineSpacingOffset = 0;
	aCurrentFormat.mFormatFlags = 0U;

	int aYOffset = theFont->GetAscent() - theFont->GetAscentPadding();
	int aLineSpacing = theFont->GetLineSpacing() + aCurrentFormat.mLineSpacingOffset;
	SexyString aCurString;
	int aLineFeedPos = 0;
	int aCurPos = 0;
	int aCurWidth = 0;
	SexyChar aCurChar = '\0';
	SexyChar aPrevChar = '\0';
	int aSpacePos = -1;
	int aMaxWidth = 0;
	while (aCurPos < theText.size())
	{
		aCurChar = theText[aCurPos];
		if (aCurChar == '{')  // If the current character is the start mark of a special format control character (i.e. "{")
		{
			const char* aFmtStart = theText.c_str() + aCurPos;
			const char* aFormat = aFmtStart + 1;
			const char* aFmtEnd = strchr(aFormat, '}');
			if (aFmtEnd != nullptr)  // If there is "}" corresponding to "{", there is a complete control character
			{
				aCurPos += aFmtEnd - aFmtStart + 1;  // aCurPos 移至“}”的下一个字符处
				int aOldAscentOffset = theFont->GetAscent() - theFont->GetAscentPadding();
				Color aExistingColor = aCurrentFormat.mNewColor;  // Back up the color of the current format
				TodWriteStringSetFormat(aFormat, aCurrentFormat);  //Set a new format based on the current control character
				aCurrentFormat.mNewColor = aExistingColor;  //Restore to original format color
				int aNewAscentOffset = (*aCurrentFormat.mNewFont)->GetAscent() - (*aCurrentFormat.mNewFont)->GetAscentPadding();
				aLineSpacing = (*aCurrentFormat.mNewFont)->GetLineSpacing() + aCurrentFormat.mLineSpacingOffset;
				aYOffset += aNewAscentOffset - aOldAscentOffset;
				continue;
			}
		}
		else if (CharIsSpaceInFormat(aCurChar, aCurrentFormat))
		{
			aSpacePos = aCurPos;
			aCurChar = ' ';
		}
		else if (aCurChar == '\n')
		{
			aSpacePos = aCurPos;
			aCurWidth = theRect.mWidth + 1;
			aCurPos++;
		}

		aCurWidth += (*aCurrentFormat.mNewFont)->CharWidthKern(aCurChar, aPrevChar);  //The current width plus the width of the current character
		aPrevChar = aCurChar;
		if (aCurWidth > theRect.mWidth)  // If the current width exceeds the width of the restricted area, wrap the line
		{
			int aLineWidth;
			if (aSpacePos != -1)  // If there are space characters in the characters before this line
			{
				int aCurY = (int)g->mTransY + theRect.mY + aYOffset;
				if (aCurY >= g->mClipRect.mY && aCurY <= g->mClipRect.mY + g->mClipRect.mHeight + aLineSpacing)  // Ensure that the ordinate of the current drawing position is within the clipping range
				{
					TodWriteWordWrappedHelper(
						g, 
						theText, 
						theRect.mX, 
						theRect.mY + aYOffset,
						aCurrentFormat, 
						theRect.mWidth, 
						theJustification, 
						drawString, 
						aLineFeedPos, // The position of the last line break is the position where the new line starts
						aSpacePos - aLineFeedPos, //The drawing part is the text starting from the last line break position to the text before the space character in this line
						theMaxChars
					);  // Draw a new line of text (if necessary)
				}

				aLineWidth = aCurWidth;
				if (aLineWidth < 0)  // If the total character width of this line is less than 0
					break;

				aCurPos = aSpacePos + 1;  // Move aCurPos to the beginning of the next line
				if (aCurChar != '\n')
					while (aCurPos < theText.size() && CharIsSpaceInFormat(theText[aCurPos], aCurrentFormat))
						aCurPos++;  // aCurPos 跳过所有连续的空白字符
			}
			else
			{
				if (aCurPos < aLineFeedPos + 1)
					aCurPos++;  // Make sure each line has at least 1 character

				aLineWidth = TodWriteWordWrappedHelper(
					g,
					theText,
					theRect.mX,
					theRect.mY + aYOffset,
					aCurrentFormat, 
					theRect.mWidth, 
					theJustification, 
					drawString, 
					aLineFeedPos, // The position of the last line break is the position where the new line starts
					aCurPos - aLineFeedPos, //The drawing part is the text starting from the last line break position to the current position
					theMaxChars
				);  // Draw a new line of text (if necessary)
				if (aLineWidth < 0)  // If the total character width of this line is less than 0
					break;
			}

			if (aLineWidth > aMaxWidth)
				aMaxWidth = aLineWidth;  //Update maximum row width
			aYOffset += aLineSpacing;
			aLineFeedPos = aCurPos;  //Record the current position as "the position of the last line break"
			aSpacePos = -1;
			aCurWidth = 0;
			aPrevChar = '\0';
		}
		else  // When the current width does not exceed the limit area width
		{
			aCurPos++;  // continue with next character
		}
	}

	if (aLineFeedPos < theText.size())
	{
		int aLastLineLength = TodWriteWordWrappedHelper(
			g,
			theText,
			theRect.mX,
			theRect.mY + aYOffset,
			aCurrentFormat,
			theRect.mWidth,
			theJustification,
			drawString,
			aLineFeedPos, //The position of the last line break is the beginning of the last line
			theText.size() - aLineFeedPos, //The drawing part is all remaining text starting from the last line break position
			theMaxChars
		);  // Draw the text of the last line
		if (aLastLineLength >= 0)
			aYOffset += aLineSpacing;
	}
	else
		aYOffset += aLineSpacing;

	return (*aCurrentFormat.mNewFont)->GetDescent() + aYOffset - aLineSpacing;
}

//0x51A040
void TodDrawStringWrapped(Graphics* g, const SexyString& theText, const Rect& theRect, Font* theFont, const Color& theColor, DrawStringJustification theJustification)
{
	SexyString aTextFinal = TodStringTranslate(theText);
	Rect aRectTodUse = theRect;
	if (theJustification == DrawStringJustification::DS_ALIGN_LEFT_VERTICAL_MIDDLE ||
		theJustification == DrawStringJustification::DS_ALIGN_RIGHT_VERTICAL_MIDDLE ||
		theJustification == DrawStringJustification::DS_ALIGN_CENTER_VERTICAL_MIDDLE)  // If the vertical position needs to be centered
	{
		aRectTodUse.mY += (aRectTodUse.mHeight - TodDrawStringWrappedHelper(g, aTextFinal, aRectTodUse, theFont, theColor, theJustification, false)) / 2;
	}
	TodDrawStringWrappedHelper(g, aTextFinal, aRectTodUse, theFont, theColor, theJustification, true);
}
