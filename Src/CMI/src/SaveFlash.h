
#include "EEPROM.h"
class EpromStruct{
public:
    template<typename T>
    bool saveFlash (uint16_t BeginAddress,T* data); 

    template<typename T>
    void LoadFlash (uint16_t BeginAddress, T* data);
};
