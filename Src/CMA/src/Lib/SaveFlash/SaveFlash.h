
#include "EEPROM.h"

template<typename ... Ts>
struct Config;


/*template<>
struct Config<> {
    static size_t get_size() {
        return 0;
    }
    static int load_config(size_t offset, uint16_t* crc16) {
        return 0;
    }
    static int store_config(size_t offset, uint16_t* crc16) {
        return 0;
    }
};
*/

template<typename T, typename ... Ts>
struct Config<T, Ts...> {
    static size_t get_size() {
        return sizeof(T) + Config<Ts...>::get_size();
    }
    static int safe_load_config(T* val0, Ts* ... vals) {
        size_t size = Config<T, Ts...>::get_size() ;
        for (unsigned int t = 0; t < size; t++) {
			*(t) = EEPROM.read(t); 
		}
    }

    static int safe_store_config(const T* val0, const Ts* ... vals) {
        size_t size = Config<T, Ts...>::get_size() + 2;
        //printf("config is %d bytes\r\n", size); osDelay(5);
        for (unsigned int t = 0; t < size; t++) {
            EEPROM.write(t, *(t));
        }
	    return EEPROM.commit();
    }
};
