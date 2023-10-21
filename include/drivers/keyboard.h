
#ifndef __KODEOS__DRIVERS__KEYBOARD_H
#define __KODEOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace kodeos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
            virtual void OnModKeyDown(kodeos::common::uint8_t);
        };
        
        class KeyboardDriver : public kodeos::hardwarecommunication::InterruptHandler, public Driver
        {
            kodeos::hardwarecommunication::Port8Bit dataport;
            kodeos::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(kodeos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual kodeos::common::uint32_t HandleInterrupt(kodeos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
