#ifndef __KODEOS__STDFUN_H
#define __KODEOS__STDFUN_H

#include <common/types.h>


namespace standard{
    
    static kodeos::common::String _istr;
    static int _si,MAX_WIDTH=80,MAX_HEIGHT=25;
    static bool _reading = true, showKeys = false; 
    static kodeos::common::uint8_t x = 0, y = 0,INITX=0,INITY=0;

    void _setInput(char *);
    void read();

    int compare(char *,char *);
    int length(char *);
    kodeos::common::String toStr(int);
    
    void printf(kodeos::common::String);
    void printf(char*,int ,int);
    void printch(char);
    void printch(char,int ,int );
    void printfHex(kodeos::common::uint8_t);
    void updateCursor(int,int);
    void updatePrintScale(int,int);

    bool showKey();
    void setShowKey(bool);

}
#endif