#ifndef TGL_STRING_H
    #define TGL_STRING_H



//{class TGL::tglString

class TGL::tglString
{
public:
    tglString();
    tglString(const TGL::tglString &targetString);
    tglString(const TGL::tglString &targetString, size_t startingPosition, size_t numberOfCharactersToCopy=TGL::allElements);
    tglString(const char *targetCharacterArray, size_t numberOfCharactersToCopy=TGL::allElements);
    tglString(char targetCharacter, size_t numberOfCopies=1);
    ~tglString();

    TGL::tglString
        &operator =(const TGL::tglString &targetString),
        &operator =(const char *targetCharacterArray),
        &operator =(char targetCharacter),
        &operator +=(const TGL::tglString &targetString),
        &operator +=(const char *targetCharacterArray),
        &operator +=(char targetCharacter);

    char
        &operator [](size_t index);

    const char
        &operator [](size_t index) const;

    void
        Resize(size_t newLength, char fillerCharacter=0),
        Reserve(size_t newCapacity=0),
        Clear(),
        ShrinkToFit(),
        PushBack(char targetCharacter),
        Swap(TGL::tglString &targetString),
        PopBack(),
        DisplayValues(FILE *outputStream=stdout);

    size_t
        Size() const,
        MaximumLength() const,
        MaximumSize() const,
        Copy(char *targetString, size_t numberOfCharactersToCopy, size_t startingPosition=0) const,
        Find(const TGL::tglString &targetString, size_t startingPosition=0) const,
        Find(const char *targetCharacterArray, size_t startingPosition=0, size_t numberOfCharactersToMatch=TGL::allElements) const,
        Find(char targetCharacter, size_t startingPosition=0) const,
        FindLast(const TGL::tglString &targetString, size_t startingPosition=TGL::lastElement) const,
        FindLast(const char *targetCharacterArray, size_t startingPosition=TGL::lastElement, size_t numberOfCharactersToMatch=TGL::allElements) const,
        FindLast(char targetCharacter, size_t startingPosition=TGL::lastElement) const;

    bool
        IsEmpty() const;

    TGL::tglString
        &Append(const TGL::tglString &targetString, size_t startingPosition=0, size_t numberOfCharactersToCopy=TGL::allElements),
        &Append(const char *targetCharacterArray, size_t numberOfCharactersToCopy=TGL::allElements),
        &Append(char targetCharacter, size_t numberOfCopies=1),
        &Assign(const TGL::tglString &targetString, size_t startingPosition=0, size_t numberOfCharactersToCopy=TGL::allElements),
        &Assign(const char *targetCharacterArray, size_t numberOfCharactersToCopy=TGL::allElements),
        &Assign(char targetCharacter, size_t numberOfCopies=1),
        &Insert(size_t insertionPosition, const TGL::tglString &targetString, size_t startingPosition=0, size_t numberOfCharactersToCopy=TGL::allElements),
        &Insert(size_t insertionPosition, const char *targetCharacterArray, size_t numberOfCharactersToCopy=TGL::allElements),
        &Insert(size_t insertionPosition, char targetCharacter, size_t numberOfCopies=1),
        &Erase(size_t startingPosition=0, size_t numberOfCharacters=TGL::allElements),
        &Replace(size_t destinationPosition, size_t destinationLength, const TGL::tglString &targetString, size_t sourcePosition=0, size_t sourceLength=TGL::allElements), //Not defined yet
        &Replace(size_t destinationPosition, size_t destinationLength, const char *targetCharacterArray, size_t sourceLength=TGL::allElements), //Not defined yet
        &Replace(size_t destinationPosition, size_t destinationLength, char targetCharacter, size_t numberOfCopies=1), //Not defined yet
        Substring(size_t startingPosition=0, size_t numberOfCharactersToCopy=TGL::allElements);

    const size_t
        tglObjectID() const;

    const char
        *characterArray() const;

    size_t
        length() const,
        capacity() const;

private:
    void
        Initialize(),
        Monitor();

    static const size_t
        _maximumLength=-4;

    char
        *_characterArray;

    size_t
        _length,
        _capacity,
        _tglObjectID;
};

//}class TGL::tglString



//{TGL::tglString

TGL::tglString::tglString()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglString::tglString(const TGL::tglString &targetString)
{
    this->Initialize();
    this->Assign(targetString).Monitor();
}

TGL::tglString::tglString(const TGL::tglString &targetString, size_t startingPosition, size_t numberOfCharactersToCopy)
{
    this->Initialize();
    this->Assign(targetString, startingPosition, numberOfCharactersToCopy).Monitor();
}

TGL::tglString::tglString(const char *targetCharacterArray, size_t numberOfCharactersToCopy)
{
    this->Initialize();
    this->Assign(targetCharacterArray, numberOfCharactersToCopy).Monitor();
}

TGL::tglString::tglString(char targetCharacter, size_t numberOfCopies)
{
    this->Initialize();
    this->Assign(targetCharacter, numberOfCopies).Monitor();
}

TGL::tglString::~tglString()
{
    this->Clear();
    TGL::stringActive[this->_tglObjectID]=0;
}

void TGL::tglString::Initialize()
{
    this->_characterArray=NULL;
    this->_length=this->_capacity=0;
}

void TGL::tglString::Monitor()
{
    TGL::stringActive[this->_tglObjectID=TGL::stringCount]=1;
    TGL::stringArray[TGL::stringCount++]=this;
    if (TGL::stringCount==TGL::stringCapacity)
    {
        {
            TGL::tglString
                **arrayHandle=TGL::stringArray;

            TGL::stringArray=new TGL::tglString*[TGL::stringCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::stringArray, arrayHandle, sizeof(*arrayHandle)*TGL::stringCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::stringActive;

            TGL::stringActive=new bool[TGL::stringCount];
            memcpy(TGL::stringActive, arrayHandle, sizeof(*arrayHandle)*TGL::stringCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglString &TGL::tglString::operator =(const TGL::tglString &targetString)
{
    return this->Assign(targetString);
}

TGL::tglString &TGL::tglString::operator =(const char *targetCharacterArray)
{
    return this->Assign(targetCharacterArray);
}

TGL::tglString &TGL::tglString::operator =(char targetCharacter)
{
    return this->Assign(targetCharacter);
}

TGL::tglString &TGL::tglString::operator +=(const TGL::tglString &targetString)
{
    return this->Append(targetString);
}

TGL::tglString &TGL::tglString::operator +=(const char *targetCharacterArray)
{
    return this->Append(targetCharacterArray);
}

TGL::tglString &TGL::tglString::operator +=(char targetCharacter)
{
    return this->Append(targetCharacter);
}

char &TGL::tglString::operator [](size_t index)
{
    if (index>=this->_length)
    {
        new TGL::tglError(stdout,
                          TGL::errorMessageOutOfBounds,
                          "const char &TGL::tglString::operator [](size_t index) const",
                          "TGL::tglString::_characterArray[index]",
                          &this->_characterArray);

        if (TGL::HandleError)
        {
            TGL::HandleError(TGL::arrayOutOfBounds);
        }
    }

    return this->_characterArray[index];
}

const char &TGL::tglString::operator [](size_t index) const
{
    if (index>=this->_length)
    {
        new TGL::tglError(stdout,
                          TGL::errorMessageOutOfBounds,
                          "const char &TGL::tglString::operator [](size_t index) const",
                          "TGL::tglString::_characterArray[index]",
                          &this->_characterArray);

        if (TGL::HandleError)
        {
            TGL::HandleError(TGL::arrayOutOfBounds);
        }
    }

    return this->_characterArray[index];
}



void TGL::tglString::Resize(size_t newLength, char fillerCharacter)
{
	if (this->_length!=newLength)
	{
		if (this->_length<newLength)
		{
			if (newLength>this->_capacity)
			{
				char
					*characterArrayHandle=new char[(this->_capacity=newLength)+1];
				memcpy(characterArrayHandle, this->_characterArray, this->_length);
				this->_characterArray? delete []this->_characterArray:(void)NULL;
				this->_characterArray=characterArrayHandle;
			}
			memset(this->_characterArray+this->_length, fillerCharacter, newLength-this->_length);
			this->_characterArray[this->_length=newLength]=0;
		}
		else //if (this->_length>newLength)
		{
			if (this->_length>0)
			{
				this->_characterArray[this->_length=newLength]=0;
			}
		}
	}
}

void TGL::tglString::Reserve(size_t newCapacity)
{
	if (this->_characterArray)
	{
		if (newCapacity!=this->_capacity)
		{
			if (newCapacity>this->_capacity)
			{
				char
					*characterArrayHandle=new char[(this->_capacity=newCapacity)+1];
				memcpy(characterArrayHandle, this->_characterArray, this->_length+1);
				delete []this->_characterArray;
				this->_characterArray=characterArrayHandle;
			}
			else //if (newCapacity<this->_capacity)
			{
				char
					*characterArrayHandle=new char[TGL::Max<size_t>(this->_length, this->_capacity=newCapacity)+1];
				memcpy(characterArrayHandle, this->_characterArray, this->_length+1);
				delete []this->_characterArray;
				this->_characterArray=characterArrayHandle;
			}
		}
	}
	else
	{
		if (newCapacity>0)
		{
			this->_characterArray=new char[this->_capacity=newCapacity];
		}
	}
}

void TGL::tglString::Clear()
{
    if (this->_characterArray)
    {
        delete []this->_characterArray;
    }
    this->Initialize();
}

void TGL::tglString::ShrinkToFit()
{
    if (this->_capacity>this->_length)
    {
		if (this->_length>0)
		{
			char
				*characterArrayHandle=new char[(this->_capacity=this->_length)+1];
			memcpy(characterArrayHandle, this->_characterArray, this->_length+1);
			delete []this->_characterArray;
			this->_characterArray=characterArrayHandle;
		}
		else
		{
			this->Clear();
		}
    }
}

void TGL::tglString::PushBack(char targetCharacter)
{
	if (this->_characterArray)
	{
		if (this->_capacity==this->_length)
		{
			char
				*characterArrayHandle=new char[(++this->_capacity)+1];
			memcpy(characterArrayHandle, this->_characterArray, this->_length);
			delete this->_characterArray;
			this->_characterArray=characterArrayHandle;
		}
	}
	else
	{
		this->_characterArray=new char[(this->_capacity=1)+1];
		this->_length=0;
	}
	this->_characterArray[this->_length++]=targetCharacter;
	this->_characterArray[this->_length]=0;
}

void TGL::tglString::Swap(TGL::tglString &targetString)
{
    {
        size_t
            attributeHandle;

        attributeHandle=this->_length;
        this->_length=targetString._length;
        targetString._length=attributeHandle;

        attributeHandle=this->_capacity;
        this->_capacity=targetString._capacity;
        targetString._capacity=attributeHandle;
    }
    {
        char
            *attributeHandle;

        attributeHandle=this->_characterArray;
        this->_characterArray=targetString._characterArray;
        targetString._characterArray=attributeHandle;
    }
}

void TGL::tglString::PopBack()
{
	if (this->_length>0)
	{
		this->_characterArray[--this->_length]=0;
	}
}

void TGL::tglString::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglString Object #%u:\nMaximum Length: %u\nMaximum Size: %u\nCapacity: %u\nLength: %u\nSize: %u\nCharacter Array: %s\n",
            this->_tglObjectID,
            this->MaximumLength(),
            this->MaximumSize(),
            this->_capacity,
            this->_length,
            this->Size(),
            this->_characterArray);
}

size_t TGL::tglString::Size() const
{
    return this->_length*sizeof(*this->_characterArray);
}

size_t TGL::tglString::MaximumLength() const
{
    return TGL::tglString::_maximumLength;
}

size_t TGL::tglString::MaximumSize() const
{
    return TGL::tglString::_maximumLength*sizeof(*this->_characterArray);
}

size_t TGL::tglString::Copy(char *targetString, size_t numberOfCharactersToCopy, size_t startingPosition) const
{
	static size_t
		numberOfCharactersCopied;

	if (this->_length<=startingPosition)
	{
		numberOfCharactersCopied=0;
	}
	else
	{
	    size_t
            endingPosition;
		endingPosition=TGL::Min<size_t>(this->_length, (numberOfCharactersToCopy==TGL::allElements? this->_length:numberOfCharactersToCopy)+startingPosition);

		if (endingPosition>startingPosition)
		{
			memcpy(targetString, this->_characterArray+startingPosition, numberOfCharactersCopied=endingPosition-startingPosition);
		}
		else
		{
            numberOfCharactersCopied=0;
		}
	}

	return numberOfCharactersCopied;
}

size_t TGL::tglString::Find(const TGL::tglString &targetString, size_t startingPosition) const
{
    if (this->_length>0)
    {
        for (size_t index=startingPosition; index<this->_length; index++)
        {
            if (!strncmp(this->_characterArray+index, targetString._characterArray, targetString._length))
            {
                return index;
            }
        }
    }
    else
    {
        if (targetString._length==0)
        {
            return 0;
        }
    }

    return TGL::notInString;
}

size_t TGL::tglString::Find(const char *targetCharacterArray, size_t startingPosition, size_t numberOfCharactersToMatch) const
{
    if (numberOfCharactersToMatch==TGL::allElements)
    {
        numberOfCharactersToMatch=strlen(targetCharacterArray);
    }

	if (this->_length>0)
	{
	    for (size_t index=startingPosition; index<this->_length; index++)
        {
            if (!strncmp(this->_characterArray+index, targetCharacterArray, numberOfCharactersToMatch))
            {
                return index;
            }
        }
	}
	else
    {
        if (*targetCharacterArray==0)
        {
            return 0;
        }
    }

	return TGL::notInString;
}

size_t TGL::tglString::Find(char targetCharacter, size_t startingPosition) const
{
    if (this->_length>0 && startingPosition<this->_length)
    {
        char
            *addressFound;

        if (addressFound=strchr(this->_characterArray+startingPosition, int(targetCharacter)))
        {
            return addressFound-this->_characterArray;
        }
    }

    return TGL::notInString;
}

size_t TGL::tglString::FindLast(const TGL::tglString &targetString, size_t startingPosition) const
{
    if (this->_length>0)
    {
        startingPosition=TGL::Min<size_t>(startingPosition, this->_length-1);

        for (size_t index=0; index<=startingPosition; index++)
        {
            if (!strncmp(this->_characterArray+startingPosition-index, targetString._characterArray, targetString._length))
            {
                return startingPosition-index;
            }
        }
    }
    else
    {
        if (targetString._length==0)
        {
            return 0;
        }
    }

    return TGL::notInString;
}

size_t TGL::tglString::FindLast(const char *targetCharacterArray, size_t startingPosition, size_t numberOfCharactersToMatch) const
{
    if (this->_length>0)
    {
        if (numberOfCharactersToMatch==TGL::allElements)
        {
            numberOfCharactersToMatch=strlen(targetCharacterArray);
        }

        startingPosition=TGL::Min<size_t>(startingPosition, this->_length-1);

        for (size_t index=0; index<=startingPosition; index++)
        {
            if (!strncmp(this->_characterArray+startingPosition-index, targetCharacterArray, numberOfCharactersToMatch))
            {
                return startingPosition-index;
            }
        }
	}
	else
    {
        if (*targetCharacterArray==0)
        {
            return 0;
        }
    }

	return TGL::notInString;
}

size_t TGL::tglString::FindLast(char targetCharacter, size_t startingPosition) const
{

    if (this->_length>0)
    {
        startingPosition=TGL::Min<size_t>(startingPosition, this->_length-1);

        for (size_t index=0; index<=startingPosition; index++)
        {
            if (this->_characterArray[startingPosition-index]==targetCharacter)
            {
                return startingPosition-index;
            }
        }
    }

    return TGL::notInString;
}

bool TGL::tglString::IsEmpty() const
{
	if (!this->_characterArray || !this->_length)
	{
		return 1;
	}
	return 0;
}

TGL::tglString &TGL::tglString::Append(const TGL::tglString &targetString, size_t startingPosition, size_t numberOfCharactersToCopy)
{
    if (targetString._length>0 && startingPosition<targetString._length)
    {
        numberOfCharactersToCopy=TGL::Min<size_t>(numberOfCharactersToCopy, targetString._length>startingPosition? targetString._length-startingPosition:0);

        if (this->_capacity>=this->_length+numberOfCharactersToCopy)
        {
            memcpy(this->_characterArray+this->_length,
                   targetString._characterArray+startingPosition,
                   numberOfCharactersToCopy);

            this->_characterArray[this->_length+=numberOfCharactersToCopy]=0;
        }
        else
        {
            char
                *characterArrayHandle=new char[(this->_capacity=this->_length+numberOfCharactersToCopy)+1];

            memcpy(characterArrayHandle,
                   this->_characterArray,
                   this->_length);

            memcpy(characterArrayHandle+this->_length,
                   targetString._characterArray,
                   numberOfCharactersToCopy);

            characterArrayHandle[this->_length=this->_capacity]=0;

			this->_characterArray? delete []this->_characterArray:(void)NULL;
			this->_characterArray=characterArrayHandle;
        }
    }

    return *this;
}

TGL::tglString &TGL::tglString::Append(const char *targetCharacterArray, size_t numberOfCharactersToCopy)
{
    if (*targetCharacterArray)
    {
        numberOfCharactersToCopy=TGL::Min<size_t>(strlen(targetCharacterArray), numberOfCharactersToCopy);

        if (this->_capacity>=this->_length+numberOfCharactersToCopy)
        {
            memcpy(this->_characterArray+this->_length,
                   targetCharacterArray,
                   numberOfCharactersToCopy);

            this->_characterArray[this->_length+=numberOfCharactersToCopy]=0;
        }
        else
        {
            char
                *characterArrayHandle=new char[(this->_capacity=this->_length+numberOfCharactersToCopy)+1];

            memcpy(characterArrayHandle,
                   this->_characterArray,
                   this->_length);

            memcpy(characterArrayHandle+this->_length,
                   targetCharacterArray,
                   numberOfCharactersToCopy);

            characterArrayHandle[this->_length=this->_capacity]=0;

			this->_characterArray? delete []this->_characterArray:(void)NULL;
			this->_characterArray=characterArrayHandle;
        }
    }

    return *this;
}

TGL::tglString &TGL::tglString::Append(char targetCharacter, size_t numberOfCopies)
{
    if (this->_capacity>=this->_length+numberOfCopies)
    {
        memset(this->_characterArray+this->_length,
               targetCharacter,
               numberOfCopies);

        this->_characterArray[this->_length+=numberOfCopies]=0;
    }
    else
    {
        char
            *characterArrayHandle=new char[(this->_capacity=this->_length+numberOfCopies)+1];

        memcpy(characterArrayHandle,
               this->_characterArray,
               this->_length);

        memset(characterArrayHandle+this->_length,
               targetCharacter,
               numberOfCopies);

        characterArrayHandle[this->_length=this->_capacity]=0;

        this->_characterArray? delete []this->_characterArray:(void)NULL;
        this->_characterArray=characterArrayHandle;
    }

    return *this;
}

TGL::tglString &TGL::tglString::Assign(const TGL::tglString &targetString, size_t startingPosition, size_t numberOfCharactersToCopy)
{
	this->Clear();

	if (targetString._length>0)
    {
        numberOfCharactersToCopy=TGL::Min<size_t>(numberOfCharactersToCopy, targetString._length>startingPosition? targetString._length-startingPosition:0);

        if (numberOfCharactersToCopy>0)
        {
            this->_characterArray=new char[(this->_capacity=this->_length=numberOfCharactersToCopy)+1];

            memcpy(this->_characterArray,
                   targetString._characterArray+startingPosition,
                   numberOfCharactersToCopy);

            this->_characterArray[numberOfCharactersToCopy]=0;
        }
    }

    return *this;
}

TGL::tglString &TGL::tglString::Assign(const char *targetCharacterArray, size_t numberOfCharactersToCopy)
{
	this->Clear();

	if (*targetCharacterArray)
	{
	    numberOfCharactersToCopy=TGL::Min<size_t>(strlen(targetCharacterArray), numberOfCharactersToCopy);

        if (numberOfCharactersToCopy>0)
        {
            this->_characterArray=new char[(this->_capacity=this->_length=numberOfCharactersToCopy)+1];

            memcpy(this->_characterArray,
                   targetCharacterArray,
                   numberOfCharactersToCopy);

            this->_characterArray[numberOfCharactersToCopy]=0;
        }
	}

	return *this;
}

TGL::tglString &TGL::tglString::Assign(char targetCharacter, size_t numberOfCopies)
{
	this->Clear();

    if (numberOfCopies>0)
    {
        this->_characterArray=new char[(this->_capacity=this->_length=numberOfCopies)+1];

        memset(this->_characterArray,
               targetCharacter,
               numberOfCopies);

        this->_characterArray[numberOfCopies]=0;
    }

	return *this;
}

TGL::tglString &TGL::tglString::Insert(size_t insertionPosition, const TGL::tglString &targetString, size_t startingPosition, size_t numberOfCharactersToCopy)
{
	if (targetString._length>0)
    {
        numberOfCharactersToCopy=TGL::Min<size_t>(numberOfCharactersToCopy, targetString._length>startingPosition? targetString._length-startingPosition:0);

        if (numberOfCharactersToCopy>0)
        {
            if (this->_capacity>=this->_length+numberOfCharactersToCopy)
            {
                memmove(this->_characterArray+insertionPosition+numberOfCharactersToCopy,
                        this->_characterArray+insertionPosition,
                        this->_length-insertionPosition);

                memcpy(this->_characterArray+insertionPosition,
                       targetString._characterArray+startingPosition,
                       numberOfCharactersToCopy);

                this->_characterArray[this->_length+=numberOfCharactersToCopy]=0;
            }
            else
            {
                char
                    *characterArrayHandle=new char[(this->_capacity=this->_length+numberOfCharactersToCopy)+1];

                memcpy(characterArrayHandle,
                       this->_characterArray,
                       insertionPosition);

                memcpy(characterArrayHandle+insertionPosition,
                       targetString._characterArray+startingPosition,
                       numberOfCharactersToCopy);

                memcpy(characterArrayHandle+insertionPosition+numberOfCharactersToCopy,
                       this->_characterArray+insertionPosition,
                       this->_length-insertionPosition);

                characterArrayHandle[this->_length=this->_capacity]=0;

                this->_characterArray? delete []this->_characterArray:(void)NULL;
                this->_characterArray=characterArrayHandle;
            }
        }
    }

    return *this;
}

TGL::tglString &TGL::tglString::Insert(size_t insertionPosition, const char *targetCharacterArray, size_t numberOfCharactersToCopy)
{
	if (*targetCharacterArray)
    {
	    numberOfCharactersToCopy=TGL::Min<size_t>(strlen(targetCharacterArray), numberOfCharactersToCopy);

        if (numberOfCharactersToCopy>0)
        {
            if (this->_capacity>=this->_length+numberOfCharactersToCopy)
            {
                memmove(this->_characterArray+insertionPosition+numberOfCharactersToCopy,
                        this->_characterArray+insertionPosition,
                        this->_length-insertionPosition);

                memcpy(this->_characterArray+insertionPosition,
                       targetCharacterArray,
                       numberOfCharactersToCopy);

                this->_characterArray[this->_length+=numberOfCharactersToCopy]=0;
            }
            else
            {
                char
                    *characterArrayHandle=new char[(this->_capacity=this->_length+numberOfCharactersToCopy)+1];

                memcpy(characterArrayHandle,
                       this->_characterArray,
                       insertionPosition);

                memcpy(characterArrayHandle+insertionPosition,
                       targetCharacterArray,
                       numberOfCharactersToCopy);

                memcpy(characterArrayHandle+insertionPosition+numberOfCharactersToCopy,
                       this->_characterArray+insertionPosition,
                       this->_length-insertionPosition);

                characterArrayHandle[this->_length=this->_capacity]=0;

                this->_characterArray? delete []this->_characterArray:(void)NULL;
                this->_characterArray=characterArrayHandle;
            }
        }
    }

    return *this;
}

TGL::tglString &TGL::tglString::Insert(size_t insertionPosition, char targetCharacter, size_t numberOfCopies)
{
    if (numberOfCopies>0)
    {
        if (this->_capacity>=this->_length+numberOfCopies)
        {
            memmove(this->_characterArray+insertionPosition+numberOfCopies,
                    this->_characterArray+insertionPosition,
                    this->_length-insertionPosition);

            memset(this->_characterArray+insertionPosition,
                   targetCharacter,
                   numberOfCopies);

            this->_characterArray[this->_length+=numberOfCopies]=0;
        }
        else
        {
            char
                *characterArrayHandle=new char[(this->_capacity=this->_length+numberOfCopies)+1];

            memcpy(characterArrayHandle,
                   this->_characterArray,
                   insertionPosition);

            memset(characterArrayHandle+insertionPosition,
                   targetCharacter,
                   numberOfCopies);

            memcpy(characterArrayHandle+insertionPosition+numberOfCopies,
                   this->_characterArray+insertionPosition,
                   this->_length-insertionPosition);

            characterArrayHandle[this->_length=this->_capacity]=0;

            this->_characterArray? delete []this->_characterArray:(void)NULL;
            this->_characterArray=characterArrayHandle;
        }
    }

    return *this;
}

TGL::tglString &TGL::tglString::Erase(size_t startingPosition, size_t numberOfCharacters)
{
    numberOfCharacters=TGL::Min<size_t>(numberOfCharacters, this->_length>startingPosition? this->_length-startingPosition:0);

    if (this->_length>numberOfCharacters+startingPosition)
    {
        memmove(this->_characterArray+startingPosition,
                this->_characterArray+startingPosition+numberOfCharacters,
                this->_length-numberOfCharacters-startingPosition);
    }

    this->_characterArray[this->_length-=numberOfCharacters]=0;

	return *this;
}

TGL::tglString &TGL::tglString::Replace(size_t destinationPosition, size_t destinationLength, const TGL::tglString &targetString, size_t sourcePosition, size_t sourceLength)
{/*
    destinationLength=TGL::Min<size_t>(destinationLength, this->_length>destinationPosition? this->_length-destinationPosition:0);

    sourceLength=TGL::Min<size_t>(sourceLength, this->_length>sourcePosition? this->_length-sourcePosition:0);

    if (this->_capacity>=this->_length+sourceLength-destinationLength)
    {
        memmove(this->_characterArray+destinationPosition+sourceLength,
                this->_characterArray+destinationPosition+destinationLength,
                this->_length-(destinationPosition+destinationLength));

        memcpy(this->_characterArray+destinationPosition,
               targetString._characterArray+sourcePosition,
               sourceLength);

        this->_characterArray[this->_length=this->_length+sourceLength-destinationLength]=0;
    }
    else
    {
        char
            *characterArrayHandle=new char[(this->_capacity=this->_length+sourceLength-destinationLength)+1];

        memcpy(characterArrayHandle,
               this->_characterArray,
               destinationPosition);

        memcpy(characterArrayHandle+destinationPosition,
               targetString._characterArray+sourcePosition,
               sourceLength);

        memcpy(characterArrayHandle+destinationPosition+sourceLength,
               this->_characterArray+destinationPosition,
               this->_length-(destinationPosition+destinationLength));

        characterArrayHandle[this->_length=this->_capacity]=0;

        this->_characterArray? delete []this->_characterArray:(void)NULL;
        this->_characterArray=characterArrayHandle;
    }

    */
    return *this;
}
/*
TGL::tglString &TGL::tglString::Replace(size_t destinationPosition, size_t destinationLength, const char *targetCharacterArray, size_t sourceLength)


TGL::tglString &TGL::tglString::Replace(size_t destinationPosition, size_t destinationLength, char targetCharacter, size_t numberOfCopies)
*/

TGL::tglString TGL::tglString::Substring(size_t startingPosition, size_t numberOfCharactersToCopy)
{
    numberOfCharactersToCopy=TGL::Min<size_t>(numberOfCharactersToCopy, this->_length>startingPosition? this->_length-startingPosition:0);

    TGL::tglString
        resultString;

    resultString.Assign(*this, startingPosition, numberOfCharactersToCopy);

    return resultString;
}



const size_t TGL::tglString::tglObjectID() const
{
    return this->_tglObjectID;
}

const char *TGL::tglString::characterArray() const
{
    return this->_characterArray;
}

size_t TGL::tglString::length() const
{
    return this->_length;
}

size_t TGL::tglString::capacity() const
{
    return this->_capacity;
}

//}TGL::tglString



#include"tglString Functions.h"



#endif // TGL_STRING_H






































