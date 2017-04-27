
#ifndef MCP4922BITSET_H
#define MCP4922BITSET_H
#include <stdint.h>

#define DEF_BIT 0x30
struct MCP4922SettingBit{
    MCP4922SettingBit(){}
    uint16_t val:12;
    uint8_t shdn:1;
    uint8_t gain:1;
    uint8_t buf:1;
    uint8_t ch:1;
};

union MCP4922BitUnit{
    MCP4922BitUnit(){
        streamBit[1] = DEF_BIT;
        streamBit[0] = 0x00;
    }

    MCP4922BitUnit(MCP4922BitUnit& bu){
        *this = bu;
    }

    MCP4922BitUnit operator = (const MCP4922BitUnit& bu){
        this -> streamBit[0] = bu.streamBit[0];
        this -> streamBit[1] = bu.streamBit[1];
        return *this;
    }

    MCP4922SettingBit settingBit;
    uint8_t streamBit[2];
};

#endif /* end of include guard: MCP4922BITSET_ H*/
