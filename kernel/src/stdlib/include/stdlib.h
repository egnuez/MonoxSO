#ifndef STDLIB_H
#define STDLIB_H

typedef signed char          int8;
typedef signed char          sint8;
typedef unsigned char        uint8;
typedef short int            int16;
typedef unsigned short int   uint16;
typedef int                  int32;
typedef signed int           sint32;
typedef unsigned int         uint32;
typedef char*                string;

/* String functions */

uint16 strlen(char *str);
void itoa (char *buf, int base, int d);

/* Ports */

uint8 inportb (uint16 _port);
void outportb (uint16 _port, uint8 _data);

/* Memory */

extern uint8 *memcpy(uint8 *dest, const uint8 *src, uint32 count);
extern uint16 *memcpyw(uint16 *dest, const uint16 *src, uint32 count);
extern uint8 *memset(uint8 *dest, uint8 val, uint32 count);
extern uint16 *memsetw(uint16 *dest, uint16 val, uint32 count);

#endif
