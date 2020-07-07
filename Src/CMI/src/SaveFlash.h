
#include "EEPROM.h"

struct dataSave {
    dataSave(){
        EEPROM.begin(1024);
    }
    template<class  T> T _saveFlash (uint16_t BeginAddress,T& data){
		data = EEPROM.put(BeginAddress, data);
        return data ;
    }
    template<class  T> bool _loadFlash (uint16_t BeginAddress,T& data){
		EEPROM.get(BeginAddress, data);
	    return EEPROM.commit();
    }
};