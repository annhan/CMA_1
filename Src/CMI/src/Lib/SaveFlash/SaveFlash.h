
#include "EEPROM.h"
class EpromStruct{
public:
    template<typename T>
    void saveFlash (uint16_t address,T* data); 

    template<typename T>
    void LoadFlash(uint16_t address, T* data);
};
