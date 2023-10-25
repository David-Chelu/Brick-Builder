#ifndef TGL_H
    #define TGL_H



#if _WIN32_WINNT<0x0500
    #define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT



#include<windows.h>
#include<stdio.h>
#include<math.h>
#include<inttypes.h>
#include<time.h>



typedef void (*ERROR_COMBINATION)(size_t, FILE*);



namespace TGL
{

    //{TGL classes

        class tglError;
        class tglString;
        class tglTexture;
        class tglDisplay;
        class tglWindow;
        class tglVector;
        class tglAngler;
        class tglAudio;
        class tglButton;
        class tglInterface;
        class tglNumber;
        class tglTextIO;

    //}TGL classes



    //{TGL variables

        //{miscellaneous

            HDC
                disposableDCForWindowProcedure;

            PAINTSTRUCT
                disposablePaintStructureForWindowProcedure;

            const short
                STANDARD_ALLOCATION=5;

            void
                *NO_REPLACE=operator new(1);

            double
                pi=3.14159265359;

            //the following definitions apply to PCM.
            //For non-PCM, there's additional variables, and a few values are slightly different.
            struct tglAudioFileHeader
            {
                char chunkID[4];
                unsigned long chunkSize;
                char format[4];
                char subchunk1ID[4];
                unsigned long subchunk1Size;
                unsigned short audioFormat;
                unsigned short numChannels;
                unsigned long sampleRate;
                unsigned long byteRate;
                unsigned short blockAlign;
                unsigned short bitsPerSample;
                char subchunk2ID[4];
                unsigned long subchunk2Size;
            };

        //}miscellaneous

        //{tglError

            const char
                *defaultErrorMessage="An error has occurred.",
                *errorMessageOutOfBounds="Attempted to access an out of range index in array.",
                *errorMessageNullArray="Attempted to access pixel in a NULL image(array).",
                *errorLoadingFile="Could not open file. Check the file name/directory and try again.",
                *errorNullDirectory="Null string was given as argument. Cannot complete task.";

            size_t
                arrayOutOfBounds=0,
                divideBy0=1,
                nullArrayAccess=2,
                audioBadDeviceID=3,
                audioNoDriver=4,
                audioNoMemory=5,
                audioAllocated=6,
                audioBadFormat=7,
                audioSync=8,
                audioInvalidHandle=9,
                audioUnprepared=10,
                audioStillPlaying=11,
                audioNotSupported=12,
                audioUnidentifiableError=13;

        //}tglError

        //{tglString

            const size_t
                allElements=-1,
                lastElement=-2,
                notInString=-3;

        //}tglString

        //{tglTexture

        //}tglTexture

        //{tglDisplay

        //}tglDisplay

        //{tglWindow

            int
                screenWidth =GetSystemMetrics(SM_CXSCREEN),
                screenHeight=GetSystemMetrics(SM_CYSCREEN);

            HINSTANCE
                windowCreationInstance=(HINSTANCE)::GetModuleHandle(0);

        //}tglWindow

        //{tglVector

        //}tglVector

        //{tglDisplay

            size_t
                BITS_PER_PIXEL=24;

        //}tglDisplay

        //{tglAngler

        //}tglAngler

        //{tglAudio

        //}tglAudio

        //{object monitoring

            size_t
                errorCount  =0, errorCapacity  =TGL::STANDARD_ALLOCATION,
                stringCount =0, stringCapacity =TGL::STANDARD_ALLOCATION,
                textureCount=0, textureCapacity=TGL::STANDARD_ALLOCATION,
                displayCount=0, displayCapacity=TGL::STANDARD_ALLOCATION,
                windowCount =0, windowCapacity =TGL::STANDARD_ALLOCATION,
                vectorCount =0, vectorCapacity =TGL::STANDARD_ALLOCATION,
                anglerCount =0, anglerCapacity =TGL::STANDARD_ALLOCATION,
                audioCount  =0, audioCapacity  =TGL::STANDARD_ALLOCATION;

            bool
                *errorActive  =new bool[TGL::STANDARD_ALLOCATION],
                *stringActive =new bool[TGL::STANDARD_ALLOCATION],
                *textureActive=new bool[TGL::STANDARD_ALLOCATION],
                *displayActive=new bool[TGL::STANDARD_ALLOCATION],
                *windowActive =new bool[TGL::STANDARD_ALLOCATION],
                *vectorActive =new bool[TGL::STANDARD_ALLOCATION],
                *anglerActive =new bool[TGL::STANDARD_ALLOCATION],
                *audioActive  =new bool[TGL::STANDARD_ALLOCATION];

            TGL::tglError
                **errorArray=new TGL::tglError*[TGL::STANDARD_ALLOCATION];

            TGL::tglString
                **stringArray=new TGL::tglString*[TGL::STANDARD_ALLOCATION];

            TGL::tglTexture
                **textureArray=new TGL::tglTexture*[TGL::STANDARD_ALLOCATION];

            TGL::tglDisplay
                **displayArray=new TGL::tglDisplay*[TGL::STANDARD_ALLOCATION];

            TGL::tglWindow
                **windowArray=new TGL::tglWindow*[TGL::STANDARD_ALLOCATION];

            TGL::tglVector
                **vectorArray=new TGL::tglVector*[TGL::STANDARD_ALLOCATION];

            TGL::tglAngler
                **anglerArray=new TGL::tglAngler*[TGL::STANDARD_ALLOCATION];

            TGL::tglAudio
                **audioArray=new TGL::tglAudio*[TGL::STANDARD_ALLOCATION];

        //}object monitoring

    //}TGL variables



    //{TGL functions

        //{miscellaneous Functions

            void
                ClearTGL();

            template<class parameterDataType> parameterDataType
                Min(parameterDataType firstOperand, parameterDataType secondOperand);

            template<class parameterDataType> parameterDataType
                Max(parameterDataType firstOperand, parameterDataType secondOperand);

            template<class parameterDataType> parameterDataType
                Module(parameterDataType value);

            COLORREF
                PixelRGB(unsigned char red, unsigned char green, unsigned char blue),
                PixelRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

            template<class parameterDataType> void
                SwitchEndian(parameterDataType &value);

        //}miscellaneous Functions

        //{tglError Functions

            void
                DisplayError(size_t index, FILE *outputStream=stdout),
                DisplayLastError(FILE *outputStream=stdout),
                DisplayAllErrors(FILE *outputStream=stdout),
                ExportToFile(size_t index, const char *directory),
                ErrorCombination000(size_t index, FILE *output),
                ErrorCombination001(size_t index, FILE *output),
                ErrorCombination010(size_t index, FILE *output),
                ErrorCombination011(size_t index, FILE *output),
                ErrorCombination100(size_t index, FILE *output),
                ErrorCombination101(size_t index, FILE *output),
                ErrorCombination110(size_t index, FILE *output),
                ErrorCombination111(size_t index, FILE *output);

            const ERROR_COMBINATION
                DisplayErrorCombination[8]=
                {
                    ErrorCombination000,
                    ErrorCombination001,
                    ErrorCombination010,
                    ErrorCombination011,
                    ErrorCombination100,
                    ErrorCombination101,
                    ErrorCombination110,
                    ErrorCombination111
                };

            void
                _HandleError(size_t),
                (*HandleError)(size_t)=NULL;

        //}tglError Functions

        //{tglString Functions

            void
                Swap(TGL::tglString &targetString1, TGL::tglString &targetString2);

            TGL::tglString
                operator +(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator +(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator +(const char           *leftOperand, const TGL::tglString &rightOperand),
                operator +(const TGL::tglString &leftOperand, char                  rightOperand),
                operator +(char                  leftOperand, const TGL::tglString &rightOperand);

            bool
                operator ==(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator ==(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator ==(const char           *leftOperand, const TGL::tglString &rightOperand),
                operator !=(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator !=(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator !=(const char           *leftOperand, const TGL::tglString &rightOperand),
                operator  <(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator  <(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator  <(const char           *leftOperand, const TGL::tglString &rightOperand),
                operator <=(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator <=(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator <=(const char           *leftOperand, const TGL::tglString &rightOperand),
                operator  >(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator  >(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator  >(const char           *leftOperand, const TGL::tglString &rightOperand),
                operator >=(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand),
                operator >=(const TGL::tglString &leftOperand, const char           *rightOperand),
                operator >=(const char           *leftOperand, const TGL::tglString &rightOperand);

        //}tglString Functions

        //{tglTexture Functions

            bool
                operator ==(TGL::tglTexture &targetTexture, const COLORREF   targetPixel),
                operator ==(const COLORREF   targetPixel,   TGL::tglTexture &targetTexture),
                operator !=(TGL::tglTexture &targetTexture, const COLORREF   targetPixel),
                operator !=(const COLORREF   targetPixel,   TGL::tglTexture &targetTexture),
                operator ==(TGL::tglTexture &targetTexture, const char      *targetPixel),
                operator ==(const char      *targetPixel,   TGL::tglTexture &targetTexture),
                operator !=(TGL::tglTexture &targetTexture, const char      *targetPixel),
                operator !=(const char      *targetPixel,   TGL::tglTexture &targetTexture);

        //}tglTexture Functions

        //{tglDisplay Functions

        //}tglDisplay Functions

        //{tglWindow Functions

            LRESULT CALLBACK
                tglWindowProcedure(HWND windowHandle,
                                   UINT windowMessage,
                                   WPARAM wordParameter,
                                   LPARAM longParameter);

        //}tglWindow Functions

        //{tglVector Functions

            bool
                operator ==(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand),
                operator !=(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand);

            TGL::tglVector
                operator +(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand),
                operator +(const TGL::tglVector &leftOperand, int                   rightOperand),
                operator +(int                   leftOperand, const TGL::tglVector &rightOperand),

                operator -(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand),
                operator -(const TGL::tglVector &leftOperand, int                   rightOperand),
                operator -(int                   leftOperand, const TGL::tglVector &rightOperand),

                operator *(const TGL::tglVector &leftOperand, int                   rightOperand),
                operator *(int                   leftOperand, const TGL::tglVector &rightOperand),

                operator /(const TGL::tglVector &leftOperand, int                   rightOperand),
                operator /(int                   leftOperand, const TGL::tglVector &rightOperand);

        //}tglVector Functions

        //{tglDisplay Functions

        //}tglDisplay Functions

        //{tglAngler Functions

        //}tglAngler Functions

        //{tglAudio Functions

            void CALLBACK
                tglAudioOutputProcedure(HWAVEOUT  hwo,
                                        UINT      uMsg,
                                        DWORD_PTR dwInstance,
                                        DWORD_PTR dwParam1,
                                        DWORD_PTR dwParam2),
                tglAudioInputProcedure(HWAVEIN   hwi,
                                       UINT      uMsg,
                                       DWORD_PTR dwInstance,
                                       DWORD_PTR dwParam1,
                                       DWORD_PTR dwParam2);

        //}tglAudio Functions

    //}TGL functions

}



#include"tglError.h"
#include"tglString.h"
#include"tglWindow.h"
#include"tglVector.h"
#include"tglTexture.h"
#include"tglDisplay.h"
#include"tglAngler.h"
#include"tglAudio.h"
#include"tgl Functions.h"



#endif // TGL_H



























