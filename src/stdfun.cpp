#include <stdfun.h>
#include <tmvga.h>

using namespace standard;
using namespace GUI;
using namespace kodeos::common;

void standard::_setInput(char *str)
{
    if (str[0] != '\n')
    {
        _istr[_si++] = str[0];
    }
    else
    {
        _istr[_si] = '\0';
        _si = 0;
        _reading = false;
    }
}

String standard::toStr(int n)
{
    char *buffer;
    int i = 0;
    bool isNeg = n < 0;
    unsigned int n1 = isNeg ? -n : n;

    while (n1 != 0)
    {
        buffer[i++] = n1 % 10 + '0';
        n1 = n1 / 10;
    }

    if (isNeg)
        buffer[i++] = '-';

    buffer[i] = '\0';

    for (int t = 0; t < i / 2; t++)
    {
        buffer[t] ^= buffer[i - t - 1];
        buffer[i - t - 1] ^= buffer[t];
        buffer[t] ^= buffer[i - t - 1];
    }

    if (n == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
    }

    return buffer;
}

int standard::length(char *str)
{
    int i = 0;
    while (str[i++]);
    return --i;
}

int standard::compare(char *s1, char *s2)
{

    int8_t result = 1;
    int8_t size = length(s1);
    if (size != length(s2))
        return 0;
    else
    {
        int8_t i = 0;
        for (i; i <= size; i++)
        {
            if (s1[i] != s2[i])
                return 0;
        }
    }
    return result;
}

void standard::read()
{
    while (_reading);
    _reading = true;
    printf(_istr);
}

void standard::printf(String str)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        switch (str[i])
        {
           
        case '\n':
            x = INITX;
            y++;
            break;
            
        default:

            VideoMemory[80 * y + x] = GET_SC() << 8 | str[i];
            x++;
            break;
        
        }

        if (x >= MAX_WIDTH)
        {
            x = INITX;
            y++;
        }

        if (y >= MAX_HEIGHT)
        {
            for (y = INITY; y < MAX_HEIGHT; y++)
                for (x = INITX; x < MAX_WIDTH; x++)
                    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
            x = INITX;
            y = INITY;
        }
    }
}

void standard::printch(char ch)
{
    uint8_t COLOR = GET_SC();
    char *VideoMemory = (char *)0xb8000;

    switch (ch)
    {
    case '\n':
        x = INITX;
        y++;
        break;
    default:

        VideoMemory[(80 * y + x) * 2] = ch;
        VideoMemory[((80 * y + x) * 2) + 1] = COLOR;
        x++;
        break;
    }

    if (x >= MAX_WIDTH)
    {
        x = INITX;
        y++;
    }

    if (y >= MAX_HEIGHT)
    {
        for (y = INITY; y < MAX_HEIGHT; y++)
            for (x = INITX; x < MAX_WIDTH; x++)
            {
                VideoMemory[(80 * y + x) * 2] = ' ';
                VideoMemory[((80 * y + x) * 2) + 1] = COLOR;
            }

        x = INITX;
        y = INITY;
    }
}

void standard::printch(char ch, int X_LOC, int Y_LOC)
{
    char *VideoMemory = (char *)0xb8000;

    VideoMemory[(80 * Y_LOC + X_LOC) * 2] = ch;
    VideoMemory[((80 * Y_LOC + X_LOC) * 2) + 1] = GET_SC();
}

void standard::printf(char *str,int X_LOC, int Y_LOC)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        switch (str[i])
        {
        case '\n':
            X_LOC = INITX;
            Y_LOC++;
            break;
        default:

            VideoMemory[80 * Y_LOC + X_LOC] = GET_SC() << 8 | str[i];
            X_LOC++;
            break;
        }

        if (X_LOC >= MAX_WIDTH)
        {
            X_LOC = INITX;
            Y_LOC++;
        }

        if (Y_LOC >= MAX_HEIGHT)
        {
            for (Y_LOC = INITY; Y_LOC < MAX_HEIGHT; Y_LOC++)
                for (X_LOC = INITX; X_LOC < MAX_WIDTH; X_LOC++)
                    VideoMemory[80 * Y_LOC + X_LOC] = (VideoMemory[80 * Y_LOC + X_LOC] & 0xFF00) | ' ';
            X_LOC = INITX;
            Y_LOC = INITY;
        }
    }
}

void standard::printfHex(kodeos::common::uint8_t key)
{
    char *foo = "00";
    char *hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}

void standard::updateCursor(int xp, int yp){
    x=xp;
    y=yp;
}

void standard::updatePrintScale(int xp, int yp){
    INITY = yp;
    INITX = xp;
    MAX_WIDTH = 80 - xp;
    MAX_HEIGHT = 25 - yp;
    x=xp;
    y=yp;
}

bool standard::showKey(){
    return showKeys;
}

void standard::setShowKey(bool b){
    showKeys = b;
}


