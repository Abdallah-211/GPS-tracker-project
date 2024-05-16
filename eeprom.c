#include "tm4c123gh6pm.h"
#define FLOAT_SCALE_FACTOR 1000000

int i;
int lat_int;
int long_int;

void delay(int n) {
    for (i = 0; i < n; i++); // delay loop
}

int eeprom_start(void) {
    SYSCTL_RCGCEEPROM_R |= 0x01; // Activating EEPROM
    delay(6); // Delay for EEPROM initialization
    while (EEPROM_EEDONE_R & 0x01); // Wait for EEPROM to complete power on
    if ((EEPROM_EESUPP_R & 0x04) || (EEPROM_EESUPP_R & 0x08)) { 
        return -1; // Error: EEPROM write protection or error flags are set
    }
    return 1; // EEPROM initialization successful
}

void eeprom_error_recovery(void) {
    EEPROM_EESUPP_R = EEPROM_EESUPP_START;
    while (EEPROM_EEDONE_R & 0x01); // Wait for recovery to complete
}

void eeprom_init(void) {
    int flag = eeprom_start();
    if (flag != 1) {
        eeprom_error_recovery();
    }
}

void write(int data, int block, int address) {
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = address;
    EEPROM_EERDWR_R = data;
    while (EEPROM_EEDONE_R & 0x01); // Wait for write to complete
}

int read(int block, int address) {
    int data;
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = address;
    data = EEPROM_EERDWR_R;
    while (EEPROM_EEDONE_R & 0x01); // Wait for read to complete
    return data;
}

void eeprom_write(float latitude[], float longitude[], int size) {
    int block = 0, address = 0;
    for (i = 0; i < size; i++) {
			lat_int = (int)(latitude[i] * FLOAT_SCALE_FACTOR);
        write(lat_int, block, address);
        if (address == 15) {
            block++;
            address = 0;
        } else {
            address++;
        }
    }
    for (i = 0; i < size; i++) {
			int long_int = (int)(longitude[i] * FLOAT_SCALE_FACTOR);
        write(long_int, block, address);
        if (address == 15) {
            block++;
            address = 0;
        } else {
            address++;
        }
    }
}

void eeprom_read(float latitude[], float longitude[], int size) {
    int block = 0, address = 0;
    for (i = 0; i < size; i++) {
        lat_int = read(block, address);
			latitude[i] = (float)lat_int / FLOAT_SCALE_FACTOR;
        if (address == 15) {
            block++;
            address = 0;
        } else {
            address++;
        }
    }
    for (i = 0; i < size; i++) { 
        long_int = read(block, address);
			longitude[i] = (float)long_int / FLOAT_SCALE_FACTOR;
        if (address == 15) {
            block++;
            address = 0;
        } else {
            address++;
        }
    }
}