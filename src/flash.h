#ifdef FLASH_GLOBALS
#define FLASH_EXT
#else
#define FLASH_EXT	extern
#endif

FLASH_EXT char Flash_Erase(unsigned int addr);
FLASH_EXT char Flash_Write(unsigned int addr, unsigned char *dt);
FLASH_EXT char Flash_Read(unsigned int addr, unsigned char *dt, unsigned char length);

