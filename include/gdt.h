#ifndef __KODEOS__GDT_H
#define __KODEOS__GDT_H

#include <common/types.h>

namespace kodeos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    kodeos::common::uint16_t limit_lo;
                    kodeos::common::uint16_t base_lo;
                    kodeos::common::uint8_t base_hi;
                    kodeos::common::uint8_t type;
                    kodeos::common::uint8_t limit_hi;
                    kodeos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(kodeos::common::uint32_t base, kodeos::common::uint32_t limit, kodeos::common::uint8_t type);
                    kodeos::common::uint32_t Base();
                    kodeos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            kodeos::common::uint16_t CodeSegmentSelector();
            kodeos::common::uint16_t DataSegmentSelector();
    };

}
    
#endif
