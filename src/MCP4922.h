#ifndef  MCP4922_H
#define MCP4922_H
#include <Arduino.h>
#include "MCP4922BitSet.h"
#include <SPI.h>

class MCP4922{
public:
    MCP4922(int cs, int lDac)
    : csPin(cs)
    , lDac(lDac)
    , settings(200000000,  MSBFIRST, SPI_MODE0) //20MHz MAX
    {}

    void init(){
        SPI.begin();
        pinMode(csPin, OUTPUT);
        pinMode(lDac, OUTPUT);
        digitalWrite(csPin, HIGH);
        digitalWrite(lDac, HIGH);
        bitUnit[0].settingBit.ch = 0;
        bitUnit[1].settingBit.ch = 1;
    }

    void write(const uint8_t ch, const uint16_t value){
        bitUnit[ch].settingBit.val = value;
        digitalWrite(lDac, HIGH);
        SPI.beginTransaction(settings);
        digitalWrite(csPin, LOW);
        SPI.transfer(bitUnit[ch].streamBit[1]);
        SPI.transfer(bitUnit[ch].streamBit[0]);
        digitalWrite(csPin, HIGH);
        SPI.endTransaction();
    };

    void drive(){
        digitalWrite(lDac, LOW);
    }

    void setBuffer(const uint8_t ch, const bool isUse){
        if(isUse){
            enableBuf(ch);
        }else{
            disableBuf(ch);
        }
    }

    void setBufferAll(const bool isUse){
        if(isUse){
            enableBufAll();
        }else{
            disableBufAll();
        }
    }

    void enableBuf(const uint8_t ch){
        bitUnit[ch].settingBit.buf = 1;
    }
    void disableBuf(const uint8_t ch){
        bitUnit[ch].settingBit.buf = 0;
    }

    void enableBufAll(){
        bitUnit[0].settingBit.buf = 1;
        bitUnit[1].settingBit.buf = 1;
    }

    void disableBufAll(){
        bitUnit[0].settingBit.buf = 0;
        bitUnit[1].settingBit.buf = 0;
    }

    void setOutPutGainSelect(const int ch, const bool isDoubled){
        if(isDoubled){
            OutPutGainDoubled(ch);
        }else{
            OutPutGainEqual(ch);
        }
    }

    void setOutPutGainSelectAll(const bool isDoubled){
        if(isDoubled){
            OutPutGainDoubledAll();
        }else{
            OutPutGainEqualAll();
        }
    }

    void OutPutGainDoubled(const int ch){
        bitUnit[ch].settingBit.gain = 1;
    }

    void OutPutGainEqual(const int ch){
        bitUnit[ch].settingBit.gain = 0;
    }

    void OutPutGainDoubledAll(){
        bitUnit[0].settingBit.gain = 1;
        bitUnit[1].settingBit.gain = 1;
    }

    void OutPutGainEqualAll(){
        bitUnit[0].settingBit.gain = 0;
        bitUnit[1].settingBit.gain = 0;
    }

    MCP4922BitUnit& getBitUnit(const int ch){
        return bitUnit[ch];
    }

    MCP4922BitUnit getBitUnit(const int ch) const {
        return bitUnit[ch];
    }
private:
    const int csPin;
    const int lDac;
    const SPISettings settings;
    MCP4922BitUnit bitUnit[2];
};
#endif /* end of include guard: MCP4922_H */
