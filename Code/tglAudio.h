#ifndef TGL_AUDIO_H
    #define TGL_AUDIO_H



//{class TGL::tglAudio

class TGL::tglAudio
{
public:
    tglAudio();
    tglAudio(const TGL::tglAudio &targetAudio);
    ~tglAudio();

    TGL::tglAudio
        &operator =(const TGL::tglAudio &targetAudio);

    bool
        LoadAudioFile(const char *fileLoadDirectory=NULL),
        Play(),
        Stop(),
        Pause(),
        //Resume(),
        Loop(),
        Restart(),
        PrepareAudio(),
        SavePosition(),
        SetVolume(DWORD newVolume),
        SetVolumeLeft(WORD newVolume),
        SetVolumeRight(WORD newVolume),
        SetPitch(DWORD newPitch),
        SetPlaybackRate(DWORD newPlaybackRate);

    void
        Clear(),
        DisplayValues(FILE *outputStream=stdout),
        InitializeOutputInformation(),
        InitializeOutputFormat();

    static void
        CheckForDevices(),
        PlayAll(size_t targetCategory),
        StopAll(size_t targetCategory),
        PauseAll(size_t targetCategory),
        LoopAll(size_t targetCategory),
        RestartAll(size_t targetCategory),
        SavePositionAll(size_t targetCategory),
        SetVolumeAll(DWORD newVolume, size_t targetCategory),
        SetVolumeLeftAll(WORD newVolume, size_t targetCategory),
        SetVolumeRightAll(WORD newVolume, size_t targetCategory),
        SetPitchAll(DWORD newPitch, size_t targetCategory),
        SetPlaybackRateAll(DWORD newPlaybackRate, size_t targetCategory);

    static bool
        DetectSupportedDevice(),
        HandleMultimediaResult(MMRESULT multimediaResult);

    MMTIME
        currentPosition() const,
        savedPosition() const;

    WAVEHDR
        &outputDataBlock();

    WAVEFORMATEX
        &outputAudioFormat();

    HWAVEIN
        &inputAudioHandle();

    HWAVEOUT
        &outputDeviceHandle();

    DWORD
        volume() const,
        pitch() const,
        playbackRate() const;

    clock_t
        &markedTime();

    bool
        startedAudio() const,
        openedDevice() const;

    const char
        *&directory();

    const char
        *directory() const;

    size_t
        tglObjectID() const,
        auxiliarDeviceCount() const,
        waveInDeviceCount() const,
        waveOutDeviceCount() const,
        &audioCategory();

private:
    void
        Initialize(),
        Monitor();

    static size_t
        _auxiliarDeviceCount,
        _waveInDeviceCount,
        _waveOutDeviceCount;

    TGL::tglAudioFileHeader
        _wavFileHeader;

    MMTIME
        _currentPosition,
        _savedPosition;

    WAVEHDR
        _outputDataBlock;

    WAVEFORMATEX
        _outputAudioFormat;

    HWAVEIN
        _inputAudioHandle;

    HWAVEOUT
        _outputDeviceHandle;

    DWORD
        _volume,
        _pitch,
        _playbackRate;

    size_t
        _audioCategory;

    clock_t
        _markedTime;

    bool
        _startedAudio,
        _openedDevice;

    const char
        *_directory;

    size_t
        _tglObjectID;
};

size_t TGL::tglAudio::_auxiliarDeviceCount;
size_t TGL::tglAudio::_waveInDeviceCount;
size_t TGL::tglAudio::_waveOutDeviceCount;

//}class TGL::tglAudio



//{TGL::tglAudio

TGL::tglAudio::tglAudio()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglAudio::tglAudio(const TGL::tglAudio &targetAudio)
{
    this->Initialize();
    (*this=targetAudio).Monitor();
}

TGL::tglAudio::~tglAudio()
{
    this->Clear();

    TGL::audioActive[this->_tglObjectID]=0;
}

void TGL::tglAudio::Initialize()
{
    this->_markedTime=0;

    this->_startedAudio=0;
    this->_openedDevice=0;
    this->_audioCategory=0;

    this->_directory=NULL;

    ZeroMemory(&this->_outputDataBlock,   sizeof(WAVEHDR));
    ZeroMemory(&this->_outputAudioFormat, sizeof(WAVEFORMATEX));
    ZeroMemory(&this->_currentPosition,   sizeof(MMTIME));
    ZeroMemory(&this->_savedPosition,     sizeof(MMTIME));

    this->_currentPosition.wType=TIME_BYTES;
    this->_savedPosition  .wType=TIME_BYTES;

    this->_inputAudioHandle  =NULL;
    this->_outputDeviceHandle=NULL;

    this->InitializeOutputFormat();
    this->InitializeOutputInformation();
}

void TGL::tglAudio::Monitor()
{
    TGL::audioActive[this->_tglObjectID=TGL::audioCount]=1;
    TGL::audioArray[TGL::audioCount++]=this;
    if (TGL::audioCount==TGL::audioCapacity)
    {
        {
            TGL::tglAudio
                **arrayHandle=TGL::audioArray;

            TGL::audioArray=new TGL::tglAudio*[TGL::audioCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::audioArray, arrayHandle, sizeof(*arrayHandle)*TGL::audioCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::audioActive;

            TGL::audioActive=new bool[TGL::audioCount];
            memcpy(TGL::audioActive, arrayHandle, sizeof(*arrayHandle)*TGL::audioCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglAudio &TGL::tglAudio::operator =(const TGL::tglAudio &targetAudio)
{
    this->_markedTime=targetAudio._markedTime;

    this->_volume      =targetAudio._volume;
    this->_pitch       =targetAudio._pitch;
    this->_playbackRate=targetAudio._playbackRate;

    this->_startedAudio =targetAudio._startedAudio;
    this->_openedDevice =targetAudio._openedDevice;
    this->_audioCategory=targetAudio._audioCategory;

    this->_directory=targetAudio._directory;

    memcpy(&this->_outputDataBlock,   &targetAudio._outputDataBlock,   sizeof(WAVEHDR));
    memcpy(&this->_outputAudioFormat, &targetAudio._outputAudioFormat, sizeof(WAVEFORMATEX));
    memcpy(&this->_currentPosition,   &targetAudio._currentPosition,   sizeof(MMTIME));
    memcpy(&this->_savedPosition,     &targetAudio._savedPosition,     sizeof(MMTIME));

    this->_inputAudioHandle  =targetAudio._inputAudioHandle;
    this->_outputDeviceHandle=targetAudio._outputDeviceHandle;

    return *this;
}



bool TGL::tglAudio::LoadAudioFile(const char *fileLoadDirectory)
{
    if (!fileLoadDirectory)
    {
        if (!(fileLoadDirectory=this->_directory))
        {
            new TGL::tglError(stdout,
                              TGL::errorNullDirectory,
                              "bool TGL::tglAudio::LoadAudioFile(const char *fileLoadDirectory)",
                              "fileLoadDirectory",
                              this);

            return 0;
        }
    }

    static bool
        fileLoadSuccess;

    fileLoadSuccess=1;

    static FILE
        *fileHandle;

    if (!(fileHandle=fopen(fileLoadDirectory, "rb")))
    {
        new TGL::tglError(stdout,
                          TGL::errorLoadingFile,
                          "bool TGL::tglAudio::LoadAudioFile(const char *fileLoadDirectory)",
                          NULL,
                          this);

        return 0;
    }

    fread(&this->_wavFileHeader,
          sizeof(this->_wavFileHeader),
          1,
          fileHandle);

    this->_outputDataBlock.dwBufferLength =this->_wavFileHeader.subchunk2Size;
    this->_outputDataBlock.lpData=new char[this->_wavFileHeader.subchunk2Size];

    if (!fread(this->_outputDataBlock.lpData, this->_wavFileHeader.subchunk2Size, 1, fileHandle))
    {
        new TGL::tglError(stdout,
                          TGL::errorLoadingFile,
                          "bool TGL::tglAudio::LoadAudioFile(const char *fileLoadDirectory)",
                          NULL,
                          this);

        return 0;
    }

    fclose(fileHandle);

    this->_directory=fileLoadDirectory;

    return 1;
}

bool TGL::tglAudio::Play()
{
    if (!this->_startedAudio)
    {
        this->_startedAudio=1;

        waveOutGetVolume(this->_outputDeviceHandle,
                         &this->_volume);

        waveOutGetPitch(this->_outputDeviceHandle,
                        &this->_pitch);

        waveOutGetPlaybackRate(this->_outputDeviceHandle,
                               &this->_playbackRate);

        return
        TGL::tglAudio::HandleMultimediaResult
        (
            waveOutWrite(this->_outputDeviceHandle,
                         &this->_outputDataBlock,
                         sizeof(WAVEHDR))
        );
    }
    else
    {
        return
        TGL::tglAudio::HandleMultimediaResult
        (
            waveOutRestart(this->_outputDeviceHandle)
        );
    }
}

bool TGL::tglAudio::Stop()
{
    this->_startedAudio=0;

    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutReset(this->_outputDeviceHandle)
    );
}

bool TGL::tglAudio::Pause()
{
    if (this->_startedAudio)
    {
        return
        TGL::tglAudio::HandleMultimediaResult
        (
            waveOutPause(this->_outputDeviceHandle)
        );
    }

    return 0;
}

bool TGL::tglAudio::Loop()
{
    return true;
}

bool TGL::tglAudio::Restart()
{
    return
    this->Stop() &&
    this->Play();
}



bool TGL::tglAudio::PrepareAudio()
{
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutOpen(&this->_outputDeviceHandle, //device handle
                    WAVE_MAPPER, //device ID (WAVE_MAPPER means the program selects a capable device)
                    &this->_outputAudioFormat,
                    0, //callback mechanism (callback function (waveOutProc)/window handle/thread identifier/handle to an event/NULL)
                    0, //user-instance data passed to the callback mechanism. This parameter is not used with the window callback mechanism.
                    CALLBACK_NULL) //specifies that the third parameter (dwCallback) is a window handle
    );

    waveOutPrepareHeader(this->_outputDeviceHandle,
                         &this->_outputDataBlock,
                         sizeof(WAVEHDR));

    this->_openedDevice=1;

    return true;
}

bool TGL::tglAudio::SavePosition()
{
    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutGetPosition(this->_outputDeviceHandle,
                           &this->_currentPosition,
                           sizeof(MMTIME))
    );
}

bool TGL::tglAudio::SetVolume(DWORD newVolume)
{
    /*
        Volume:
    -low-order word is left channel.
    -hight-order word is right channel.
    -0x0000 is silence.
    -0xFFFF is maximum volume.
    -for devices that do not support left- and right-channel volume control, the lower 16 bits specify the volume level, and the upper 16 bits are ignored.
    */

    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutSetPlaybackRate(this->_outputDeviceHandle,
                               this->_volume=newVolume)
    );
}

bool TGL::tglAudio::SetVolumeLeft(WORD newVolume)
{/*
           (unsigned long long)(floor(1.5)*0x00010000)|
           (unsigned long long)((1.5-floor(1.5))*0x00010000));

    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutSetPlaybackRate(this->_outputDeviceHandle,
                               this->_volume>>=16)<<16)
    );*/
    return true;
}

bool TGL::tglAudio::SetVolumeRight(WORD newVolume)
{
    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutSetPlaybackRate(this->_outputDeviceHandle,
                               this->_volume)
    );
}

bool TGL::tglAudio::SetPitch(DWORD newPitch)
{
    /*
        Pitch and Playback Rate:
    -the upper 16 bits specify the integer part of the number.
    -the lower 16 bits specify the fractional part.
    -value 1.0 (0x00010000) means the pitch or playback rate is unchanged.
    -examples:
        -the value 1.5 is represented as 0x00018000.
        -the value 0.75 is represented as 0x0000C000.
    */

    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutSetPitch(this->_outputDeviceHandle,
                        this->_pitch=newPitch)
    );
}

bool TGL::tglAudio::SetPlaybackRate(DWORD newPlaybackRate)
{
    /*
        Pitch and Playback Rate:
    -the upper 16 bits specify the integer part of the number.
    -the lower 16 bits specify the fractional part.
    -value 1.0 (0x00010000) means the pitch or playback rate is unchanged.
    -examples:
        -the value 1.5 is represented as 0x00018000.
        -the value 0.75 is represented as 0x0000C000.
    */

    return
    TGL::tglAudio::HandleMultimediaResult
    (
        waveOutSetPlaybackRate(this->_outputDeviceHandle,
                               this->_playbackRate=newPlaybackRate)
    );
}



void TGL::tglAudio::Clear()
{
    if (this->_startedAudio)
    {
        this->Stop();
    }

    if (this->_openedDevice)
    {
        TGL::tglAudio::HandleMultimediaResult
        (
            waveOutUnprepareHeader(this->_outputDeviceHandle,
                                   &this->_outputDataBlock,
                                   sizeof(WAVEHDR))
        );

        TGL::tglAudio::HandleMultimediaResult
        (
            waveOutClose(this->_outputDeviceHandle)
        );
    }

    this->_markedTime=0;

    if (this->_outputDataBlock.lpData)
    {
        delete []this->_outputDataBlock.lpData;

        this->_outputDataBlock.lpData=NULL;
    }

    this->_directory=NULL;
}

void TGL::tglAudio::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglAudio Object #%u:\ndirectory: %s\nmarkedTime: %d\nvolume: %u\npitch: %u\nplaybackRate: %u\naudioCategory: %u\nstartedAudio: %s\nopenedDevice: %s\noutputAudioFormat.nChannels: %d\noutputAudioFormat.nSamplesPerSec: %d\noutputAudioFormat.nAvgBytesPerSec: %d\noutputAudioFormat.nBlockAlign: %d\noutputAudioFormat.wBitsPerSample: %d",
            this->_tglObjectID,
            this->_directory,
            this->_markedTime,
            (unsigned)this->_volume,
            (unsigned)this->_pitch,
            (unsigned)this->_playbackRate,
            (unsigned)this->_audioCategory,
            this->_startedAudio? "Yes":"No",
            this->_openedDevice? "Yes":"No",
            (unsigned)this->_outputAudioFormat.nChannels,
            (unsigned)this->_outputAudioFormat.nSamplesPerSec,
            (unsigned)this->_outputAudioFormat.nAvgBytesPerSec,
            (unsigned)this->_outputAudioFormat.nBlockAlign,
            (unsigned)this->_outputAudioFormat.wBitsPerSample);
}

void TGL::tglAudio::InitializeOutputInformation()
{
    this->_outputDataBlock.dwBytesRecorded=0;
    this->_outputDataBlock.dwUser=0;
    this->_outputDataBlock.dwFlags=0;
    this->_outputDataBlock.dwLoops=0;
    this->_outputDataBlock.lpNext=0;
    this->_outputDataBlock.reserved=0;
}

void TGL::tglAudio::InitializeOutputFormat()
{
    this->_outputAudioFormat.wFormatTag=WAVE_FORMAT_PCM; //format for 22.05 kHz
    this->_outputAudioFormat.nChannels=2; //stereo
    //this->_outputAudioFormat.nSamplesPerSec=22050; //22.05 kHz
    this->_outputAudioFormat.nSamplesPerSec=44100; //44.10 kHz
    this->_outputAudioFormat.nAvgBytesPerSec=88200; //705600 kbps
    this->_outputAudioFormat.wBitsPerSample=16; //16bit sound
    //normal order is nBlockAlign, then wBitsPerSample
    this->_outputAudioFormat.nBlockAlign=(this->_outputAudioFormat.nChannels*this->_outputAudioFormat.wBitsPerSample)/8;
    this->_outputAudioFormat.cbSize=0; //when wFormatTag is WAVE_FORMAT_TCM, this value should be 0
}

void TGL::tglAudio::CheckForDevices()
{
    TGL::tglAudio::_auxiliarDeviceCount=auxGetNumDevs();
    TGL::tglAudio::_waveInDeviceCount  =waveInGetNumDevs();
    TGL::tglAudio::_waveOutDeviceCount =waveOutGetNumDevs();
}

void TGL::tglAudio::PlayAll(size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->Play();
            }
        }
    }
}

void TGL::tglAudio::StopAll(size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->Stop();
            }
        }
    }
}

void TGL::tglAudio::PauseAll(size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->Pause();
            }
        }
    }
}

void TGL::tglAudio::LoopAll(size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->Loop();
            }
        }
    }
}

void TGL::tglAudio::RestartAll(size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->Restart();
            }
        }
    }
}

void TGL::tglAudio::SavePositionAll(size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->SavePosition();
            }
        }
    }
}

void TGL::tglAudio::SetVolumeAll(DWORD newVolume, size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->SetVolume(newVolume);
            }
        }
    }
}

void TGL::tglAudio::SetVolumeLeftAll(WORD newVolume, size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->SetVolumeLeft(newVolume);
            }
        }
    }
}

void TGL::tglAudio::SetVolumeRightAll(WORD newVolume, size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->SetVolumeRight(newVolume);
            }
        }
    }
}

void TGL::tglAudio::SetPitchAll(DWORD newPitch, size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->SetPitch(newPitch);
            }
        }
    }
}

void TGL::tglAudio::SetPlaybackRateAll(DWORD newPlaybackRate, size_t targetCategory)
{
    for (size_t index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            if (TGL::audioArray[index]->_audioCategory==targetCategory ||
                targetCategory==0)
            {
                TGL::audioArray[index]->SetPlaybackRate(newPlaybackRate);
            }
        }
    }
}

bool TGL::tglAudio::DetectSupportedDevice()
{
    TGL::tglAudio::CheckForDevices();

    /*
        void functionDisplayMultimediaDeviceCapabilities(AUXCAPS *auxiliarDeviceCapabilities)
        {
            if (!auxiliarDeviceCapabilities)
            {
                ::printf("Error: cannot display device capabilities (NULL pointer given as parameter).\n");
                return;
            }
            ::printf("AUXCAPS capabilities:\nwMid: %u\nwPid: %u\nvDriverVersion: %u\nszPname: %s\nwTechnology: %u\nwReserved1: %u\ndwSupport: %u\n\n",
                     (unsigned)auxiliarDeviceCapabilities->wMid,
                     (unsigned)auxiliarDeviceCapabilities->wPid,
                     (unsigned)auxiliarDeviceCapabilities->vDriverVersion,
                     auxiliarDeviceCapabilities->szPname,
                     (unsigned)auxiliarDeviceCapabilities->wTechnology,
                     (unsigned)auxiliarDeviceCapabilities->wReserved1,
                     (unsigned)auxiliarDeviceCapabilities->dwSupport);
        }

        void functionDisplayMultimediaDeviceCapabilities(WAVEINCAPS *waveInDeviceCapabilities)
        {
            if (!waveInDeviceCapabilities)
            {
                ::printf("Error: cannot display device capabilities (NULL pointer given as parameter).\n");
                return;
            }
            ::printf("WAVEINCAPS capabilities:\nwMid: %u\nwPid: %u\nvDriverVersion: %u\nszPname: %s\ndwFormats: %u\nwChannels: %u\ndwReserved1: %u\n\n",
                     (unsigned)waveInDeviceCapabilities->wMid,
                     (unsigned)waveInDeviceCapabilities->wPid,
                     (unsigned)waveInDeviceCapabilities->vDriverVersion,
                     waveInDeviceCapabilities->szPname,
                     (unsigned)waveInDeviceCapabilities->dwFormats,
                     (unsigned)waveInDeviceCapabilities->wChannels,
                     (unsigned)waveInDeviceCapabilities->wReserved1);
        }

        void functionDisplayMultimediaDeviceCapabilities(WAVEOUTCAPS *waveOutDeviceCapabilities)
        {
            if (!waveOutDeviceCapabilities)
            {
                ::printf("Error: cannot display device capabilities (NULL pointer given as parameter).\n");
                return;
            }
            ::printf("WAVEOUTCAPS capabilities:\nwMid: %u\nwPid: %u\nvDriverVersion: %u\nszPname: %s\ndwFormats: %u\nwChannels: %u\nwReserved1: %u\ndwSupport: %u\n\n",
                     (unsigned)waveOutDeviceCapabilities->wMid,
                     (unsigned)waveOutDeviceCapabilities->wPid,
                     (unsigned)waveOutDeviceCapabilities->vDriverVersion,
                     waveOutDeviceCapabilities->szPname,
                     (unsigned)waveOutDeviceCapabilities->dwFormats,
                     (unsigned)waveOutDeviceCapabilities->wChannels,
                     (unsigned)waveOutDeviceCapabilities->wReserved1,
                     (unsigned)waveOutDeviceCapabilities->dwSupport);
        }



        AUXCAPS
            auxiliarDeviceCapabilities;

        WAVEINCAPS
            waveInDeviceCapabilities;

        WAVEOUTCAPS
            waveOutDeviceCapabilities;

        ::ZeroMemory(&auxiliarDeviceCapabilities, sizeof(auxiliarDeviceCapabilities));
        ::ZeroMemory(&waveInDeviceCapabilities, sizeof(waveInDeviceCapabilities));
        ::ZeroMemory(&waveOutDeviceCapabilities, sizeof(waveOutDeviceCapabilities));

        for (currentDeviceID=0; currentDeviceID<auxiliarDeviceCount; currentDeviceID++)
        {
            if (functionDisplayMultimediaFunctionResult(auxGetDevCaps(currentDeviceID, &auxiliarDeviceCapabilities, sizeof(auxiliarDeviceCapabilities))))
            {
                functionDisplayMultimediaDeviceCapabilities(&auxiliarDeviceCapabilities);
            }
        }

        for (currentDeviceID=0; currentDeviceID<waveInDeviceCount; currentDeviceID++)
        {
            if (functionDisplayMultimediaFunctionResult(waveInGetDevCaps(currentDeviceID, &waveInDeviceCapabilities, sizeof(waveInDeviceCapabilities))))
            {
                functionDisplayMultimediaDeviceCapabilities(&waveInDeviceCapabilities);
            }
        }

        for (currentDeviceID=0; currentDeviceID<waveOutDeviceCount; currentDeviceID++)
        {
            if (functionDisplayMultimediaFunctionResult(waveOutGetDevCaps(currentDeviceID, &waveOutDeviceCapabilities, sizeof(waveOutDeviceCapabilities))))
            {
                functionDisplayMultimediaDeviceCapabilities(&waveOutDeviceCapabilities);
            }
        }
    */
    return true;
}

bool TGL::tglAudio::HandleMultimediaResult(MMRESULT multimediaResult)
{
    static const char
        *errorMessage;

    static size_t
        errorID;

    switch (multimediaResult)
    {
        case MMSYSERR_NOERROR:
        {
            return 1;
        }
        case MMSYSERR_BADDEVICEID:
        {
            errorID=TGL::audioBadDeviceID;
            errorMessage="Specified device identifier is out of range (error MMSYSERR_BADDEVICEID).";
            break;
        }
        case MMSYSERR_NODRIVER:
        {
            errorID=TGL::audioNoDriver;
            errorMessage="No device driver is present (error MMSYSERR_NODRIVER).";
            break;
        }
        case MMSYSERR_NOMEM:
        {
            errorID=TGL::audioNoMemory;
            errorMessage="Unable to allocate or lock memory (error MMSYSERR_NOMEM).";
            break;
        }
        case MMSYSERR_ALLOCATED:
        {
            errorID=TGL::audioAllocated;
            errorMessage="Specified resource is already allocated (error MMSYSERR_ALLOCATED).";
            break;
        }
        case WAVERR_BADFORMAT:
        {
            errorID=TGL::audioBadFormat;
            errorMessage="Attempted to open with an unsupported waveform-audio format (error MMSYSERR_BADDEVICEID).";
            break;
        }
        case WAVERR_SYNC:
        {
            errorID=TGL::audioSync;
            errorMessage="The device is synchronous but waveOutOpen was called without using the WAVE_ALLOWSYNC flag (error WAVERR_SYNC).";
            break;
        }
        case MMSYSERR_INVALHANDLE:
        {
            errorID=TGL::audioInvalidHandle;
            errorMessage="Specified device handle is invalid (error MMSYSERR_INVALHANDLE).";
            break;
        }
        case WAVERR_UNPREPARED:
        {
            errorID=TGL::audioUnprepared;
            errorMessage="The data block pointed to by the pwh parameter hasn't been prepared (error WAVERR_UNPREPARED).";
            break;
        }
        case WAVERR_STILLPLAYING:
        {
            errorID=TGL::audioStillPlaying;
            errorMessage="There are still buffers in the queue (error WAVERR_STILLPLAYING).";
            break;
        }
        case MMSYSERR_NOTSUPPORTED:
        {
            errorID=TGL::audioNotSupported;
            errorMessage="Function isn't supported (error MMSYSERR_NOTSUPPORTED).";
            break;
        }
        default:
        {
            errorID=TGL::audioUnidentifiableError;
            errorMessage="An unidentifiable error has occurred.";
            break;
        }
    }

    new TGL::tglError(stdout,
                      errorMessage,
                      "bool TGL::tglAudio::HandleMultimediaResult(MMRESULT multimediaResult) const",
                      "multimediaResult",
                      NULL);

    if (HandleError)
    {
        HandleError(errorID);
    }

    return 0;
}



MMTIME TGL::tglAudio::currentPosition() const
{
    return this->_currentPosition;
}

MMTIME TGL::tglAudio::savedPosition() const
{
    return this->_savedPosition;
}

WAVEHDR &TGL::tglAudio::outputDataBlock()
{
    return this->_outputDataBlock;
}

WAVEFORMATEX &TGL::tglAudio::outputAudioFormat()
{
    return this->_outputAudioFormat;
}

HWAVEIN &TGL::tglAudio::inputAudioHandle()
{
    return this->_inputAudioHandle;
}

HWAVEOUT &TGL::tglAudio::outputDeviceHandle()
{
    return this->_outputDeviceHandle;
}

DWORD TGL::tglAudio::volume() const
{
    return this->_volume;
}

DWORD TGL::tglAudio::pitch() const
{
    return this->_pitch;
}

DWORD TGL::tglAudio::playbackRate() const
{
    return this->_playbackRate;
}

clock_t &TGL::tglAudio::markedTime()
{
    return this->_markedTime;
}

bool TGL::tglAudio::startedAudio() const
{
    return this->_startedAudio;
}

const char *&TGL::tglAudio::directory()
{
    return this->_directory;
}

const char *TGL::tglAudio::directory() const
{
    return this->_directory;
}

size_t TGL::tglAudio::tglObjectID() const
{
    return this->_tglObjectID;
}

size_t TGL::tglAudio::auxiliarDeviceCount() const
{
    return TGL::tglAudio::_auxiliarDeviceCount;
}

size_t TGL::tglAudio::waveInDeviceCount() const
{
    return TGL::tglAudio::_waveInDeviceCount;
}

size_t TGL::tglAudio::waveOutDeviceCount() const
{
    return TGL::tglAudio::_waveOutDeviceCount;
}

size_t &TGL::tglAudio::audioCategory()
{
    return this->_audioCategory;
}

/*
if the parameter is a CALLBACK_WINDOW, then the window receives the following messages, indicating the progress:
-MM_WOM_OPEN
-MM_WOM_CLOSE
-MM_WOM_DONE

CF_WAVE - represent data in one of the standard formats (e.g. 11 kHz, 22 kHz PCM)
CF_RIFF - represent more complex data formats that cannot be represented as standard waveform-audio files

MMRESULT waveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
//sends a data block to the given waveform-audio output device

typedef struct wavehdr_tag
{
    LPSTR lpData;
    DWORD dwBufferLength;
    DWORD dwBytesRecorded;
    DWORD dwUser;
    DWORD dwFlags;
    DWORD dwLoops;
    struct wavehdr_tag *lpNext;
    DWORD reserved;
} WAVEHDR,*PWAVEHDR,*LPWAVEHDR;
*/

//}TGL::tglAudio



#include"tglAudio Functions.h"



#endif // TGL_AUDIO_H





































