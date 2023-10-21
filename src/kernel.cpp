#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <stdfun.h>
#include <CPU.h>
#include <tmvga.h>

using namespace kodeos;
using namespace kodeos::common;
using namespace GUI;
using namespace System;
using namespace kodeos::drivers;
using namespace kodeos::hardwarecommunication;
using namespace standard;

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        if(showKey()){
        char *foo = " ";
        foo[0] = c;
        _setInput(foo);
        printf(foo);
        }
    }
    void OnModKeyDown(uint8_t modifier){
        if(modifier == 0x1C){
            if(GET_SELVIEW()){
                enterSelection();
            }
        }

        if(modifier == 0x01){
            if(getAppLoaded())
            endApplication();
        }

        if(GET_SELVIEW()){
            if(GET_SIndex){
                changeSelection(modifier);
            }

        }
    }
};

class MouseToConsole : public MouseEventHandler
{

    int8_t x, y;

public:
    MouseToConsole()
    {
        uint16_t *VideoMemory = (uint16_t *)0xb8000;
        x = 50;
        y = 2;
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4 | (VideoMemory[80 * y + x] & 0xF000) >> 4 | (VideoMemory[80 * y + x] & 0x00FF);
    }

    virtual void OnMouseMove(int xoffset, int yoffset)
    {
        static uint16_t *VideoMemory = (uint16_t *)0xb8000;
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4 | (VideoMemory[80 * y + x] & 0xF000) >> 4 | (VideoMemory[80 * y + x] & 0x00FF);

        x += xoffset;
        if (x >= 80)
            x = 79;
        if (x < 0)
            x = 0;
        y += yoffset;
        if (y >= 25)
            y = 24;
        if (y < 0)
            y = 0;

        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4 | (VideoMemory[80 * y + x] & 0xF000) >> 4 | (VideoMemory[80 * y + x] & 0x00FF);
    }
    
        virtual void OnMouseDown(uint8_t button){
        switch(button){
            case 0x1:
                clickedOn(x,y);
            break;
            case 0x2:
     
            break;
            case 0x4:
            break;
        }
    }

    virtual void OnMouseUp(uint8_t button){
        switch(button){
            case 0x1:

               /* if( y >= 14 && y<15){
                    if(x>=55 && x<70){
                        printf("Clicked");
                    }
                }
               /* if(m){
                    drawer.rect(px,py,10);
                    m=0;
                }*/
            break;
        }
    }

};

class Listener : public ActionListener{
    public:
    virtual void actionPerformed(String id){
        if(compare(id,"o_btn")){
            SET_SC(0xF0);
            updateCursor(8,4);
            printf("File opened successfuly");
        }
        else if(compare(id,"s_btn")){   
            SET_SC(0xF0); 
            updateCursor(8,5);
            printf("File closed successfuly");
        }
    }
};


class Editor : public TextApp{
    public:
    virtual void Start(){
        setShowKey(true);
        Frame frame("Text Editor");
        SET_SC(0xF0);
        updatePrintScale(5,3);
    }
};

class About : public TextApp{
    public:
    virtual void Start(){
        Frame frame("About");
        updatePrintScale(15,5);
        SET_SC(0xF0);
        updateCursor(15,8);
        printf("KODE OS\nVersion: 1.24\n");
        CpuDetect();
    }
};

class CALC : public TextApp{
    public:
    virtual void Start(){
        Frame frame("CALC");
    }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(const void *multiboot_structure, uint32_t /*multiboot_magic*/)
{

   
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);
    printf("Initializing Hardware [..");
    DriverManager drvManager;
    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&interrupts, &kbhandler);
    drvManager.AddDriver(&keyboard);
    printf("..");
    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler);
    drvManager.AddDriver(&mouse);
    printf("..");
    drvManager.ActivateAll();
    printf("..] ");
    interrupts.Activate();
    printf("Done.\nWelcome to Kode OS");

    screen_init();

    Desktop start_menu("KODE OS");

    printf("APPLICATIONS",5,3);

   

    About ab;
    Icon aic("About",5,5);
    aic.bindApplication(&ab);

    Editor editor;
    Icon editorIcon("Edit",15,5);
    editorIcon.bindApplication(&editor);

    CALC calc;
    Icon calculatorIcon("CALC",25,5);
    calculatorIcon.bindApplication(&calc);

    while (1);
}