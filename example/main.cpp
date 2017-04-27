#include "MCP4922.h"
#define STRIDE 200
constexpr int csPin = 10;
constexpr int lDacPin = 9;

int main(){

    MCP4922 mcp(csPin,lDacPin);
    mcp.init(); //one time only
    mcp.enableBufAll(); // hw buf enabled;
    mcp.OutPutGainEqualAll(); // val singled

    for(;;){

        for(int i = 0 ; i < 4095 ; i += STRIDE){
            mcp.write(0,i); //MCP4922::write(ch,val) write to register, ch A == 0 ,B == 1
            mcp.drive(); // lDacPin Low value applied
        }

        for(int i = 4095 ; i > 0 ; i -= STRIDE){
            mcp.write(0,i);
            mcp.drive();
        }

    }
}
