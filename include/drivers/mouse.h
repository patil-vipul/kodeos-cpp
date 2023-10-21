
#ifndef __KODEOS__DRIVERS__MOUSE_H
#define __KODEOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace kodeos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(kodeos::common::uint8_t button);
            virtual void OnMouseUp(kodeos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public kodeos::hardwarecommunication::InterruptHandler, public Driver
        {
            kodeos::hardwarecommunication::Port8Bit dataport;
            kodeos::hardwarecommunication::Port8Bit commandport;
            kodeos::common::uint8_t buffer[3];
            kodeos::common::uint8_t offset;
            kodeos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(kodeos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual kodeos::common::uint32_t HandleInterrupt(kodeos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
