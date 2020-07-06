#include "SaveFlash.h"


template<typename T>
bool EpromStruct::saveFlash (uint16_t BeginAddress,T* data){
    for (uint16_t t = 0; t < sizeof(T); t++) {
		EEPROM.write(BeginAddress + t, *(&data + t));
	}
	return EEPROM.commit();
}

template<typename T>
void EpromStruct::LoadFlash(uint16_t BeginAddress, T* data){
		for (unsigned int t = 0; t < sizeof(T); t++) {
			*(&data + t) = EEPROM.read(BeginAddress + t); 
		}
}