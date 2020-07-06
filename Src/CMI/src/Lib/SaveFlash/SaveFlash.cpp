#include "SaveFlash.h"


template<typename T>
void EpromStruct::saveFlash (uint16_t address,T* data){
    for (uint16_t t = 0; t < sizeof(T); t++) {
		EEPROM.write(address + t, *(&data + t));
	}
	return EEPROM.commit();
}

template<typename T>
void EpromStruct::LoadFlash(uint16_t address, T* data){
		for (unsigned int t = 0; t < sizeof(T); t++) {
			*(&data + t) = EEPROM.read(address + t); 
		}
}