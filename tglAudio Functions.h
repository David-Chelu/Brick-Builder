#ifndef TGL_AUDIO_FUNCTIONS_H
    #define TGL_AUDIO_FUNCTIONS_H



//{TGL::tglAudio functions

void CALLBACK TGL::tglAudioOutputProcedure(HWAVEOUT  hwo,
                                           UINT      uMsg,
                                           DWORD_PTR dwInstance,
                                           DWORD_PTR dwParam1,
                                           DWORD_PTR dwParam2)
{
    switch (uMsg)
    {
        case MM_WOM_CLOSE:
        {
            //Sent when the device is closed by using the waveOutClose function.
            break;
        }
        case MM_WOM_DONE:
        {
            //Sent when the device driver is finished with a data block sent by using the waveOutWrite function.
            break;
        }
        case MM_WOM_OPEN:
        {
            //Sent when the device is opened by using the waveOutOpen function.
            break;
        }
        default:
        {
            break;
        }
    }
}

void CALLBACK TGL::tglAudioInputProcedure(HWAVEIN   hwi,
                                          UINT      uMsg,
                                          DWORD_PTR dwInstance,
                                          DWORD_PTR dwParam1,
                                          DWORD_PTR dwParam2)
{
    switch (uMsg)
    {
        case MM_WIM_CLOSE:
        {
            //Sent when the device is closed by using the waveInClose function.
            break;
        }
        case MM_WIM_DATA:
        {
            //Sent when the device driver is finished with a buffer sent by using the waveInAddBuffer function.
            break;
        }
        case MM_WIM_OPEN:
        {
            //Sent when the device is opened by using the waveInOpen function.
            break;
        }
    }
}

//}TGL::tglAudio functions



#endif // TGL_AUDIO_FUNCTIONS_H





































