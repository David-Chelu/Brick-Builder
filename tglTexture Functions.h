#ifndef TGL_TEXTURE_FUNCTIONS_H
    #define TGL_TEXTURE_FUNCTIONS_H



//{TGL::tglTexture functions

bool operator ==(TGL::tglTexture &targetTexture, const COLORREF targetPixel)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==((targetPixel<<8)>>24) &&
        image[1]==((targetPixel<<16)>>24) &&
        image[2]==((targetPixel<<24)>>24))
    {
        return 1;
    }

    return 0;
}
bool operator ==(const COLORREF targetPixel, TGL::tglTexture &targetTexture)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==((targetPixel<<8)>>24) &&
        image[1]==((targetPixel<<16)>>24) &&
        image[2]==((targetPixel<<24)>>24))
    {
        return 1;
    }

    return 0;
}
bool operator !=(TGL::tglTexture &targetTexture, const COLORREF targetPixel)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==((targetPixel<<8)>>24) &&
        image[1]==((targetPixel<<16)>>24) &&
        image[2]==((targetPixel<<24)>>24))
    {
        return 0;
    }

    return 1;
}
bool operator !=(const COLORREF targetPixel, TGL::tglTexture &targetTexture)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==((targetPixel<<8)>>24) &&
        image[1]==((targetPixel<<16)>>24) &&
        image[2]==((targetPixel<<24)>>24))
    {
        return 0;
    }

    return 1;
}
bool operator ==(TGL::tglTexture &targetTexture, const char *targetPixel)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==targetPixel[0] &&
        image[1]==targetPixel[1] &&
        image[2]==targetPixel[2])
    {
        return 1;
    }

    return 0;
}
bool operator ==(const char *targetPixel, TGL::tglTexture &targetTexture)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==targetPixel[0] &&
        image[1]==targetPixel[1] &&
        image[2]==targetPixel[2])
    {
        return 1;
    }

    return 0;
}
bool operator !=(TGL::tglTexture &targetTexture, const char *targetPixel)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==targetPixel[0] &&
        image[1]==targetPixel[1] &&
        image[2]==targetPixel[2])
    {
        return 0;
    }

    return 1;
}
bool operator !=(const char *targetPixel, TGL::tglTexture &targetTexture)
{
    const char
        *image=targetTexture.currentLine()+targetTexture.currentColumn()*targetTexture.bitsPerPixel()/8;

    if (image[0]==targetPixel[0] &&
        image[1]==targetPixel[1] &&
        image[2]==targetPixel[2])
    {
        return 0;
    }

    return 1;
}

//}TGL::tglTexture functions



#endif // TGL_TEXTURE_FUNCTIONS_H






































