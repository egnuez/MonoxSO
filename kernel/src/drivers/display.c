#ifndef SCREEN_H
#define SCREEN_H
#define VIDEO_SEGMENT 0xB8000
#include "../stdlib/include/stdlib.h"

int cursorX = 0, cursorY = 0;
const uint8 sw = 80, sh = 25, sd = 2;

static void clear_line(uint8 from, uint8 to){
    uint16 i = sw * from * sd;
    string vidmem = (string) VIDEO_SEGMENT;
    while (i<sw*(to+1)*sd){
        vidmem[i] = 0x0;
        i++;
    }
}

static void update_cursor()
{

  unsigned temp;

  temp = cursorY * sw + cursorX;

  outportb(0x3D4, 14);
  outportb(0x3D5, temp >> 8);
  outportb(0x3D4, 15);
  outportb(0x3D5, temp);

}

void clear_screen(){
    clear_line(0, sh-1);
    cursorX = 0;
    cursorY = 0;
    update_cursor();
}

void printch(char c){
    if (c == '\n' || c == '\r'){
        cursorX = 0;
        cursorY++;
    }else{
        string vidmem = (string) VIDEO_SEGMENT;
        vidmem[(cursorY * sw + cursorX)*sd] = c;
        vidmem[(cursorY * sw + cursorX)*sd+1] = 0x0F;
        cursorX++;
    }
    update_cursor();
}

void print (string ch){
    uint16 i = 0;
    uint16 n = strlen(ch);
    while(i<n){
        printch(ch[i]);
        i++;
    }
}

void print_hex(uint8 key){
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    print(foo);
}

void print_hex16(uint16 key){
    print_hex((key >> 8) & 0xFF);
    print_hex( key & 0xFF);
}

void print_hex32(uint32 key){
    print_hex((key >> 24) & 0xFF);
    print_hex((key >> 16) & 0xFF);
    print_hex((key >> 8) & 0xFF);
    print_hex( key & 0xFF);
}

void printf (const char *format, ...) {
    char **arg = (char **) &format;
    int c;
    char buf[20];
    arg++;
    while ((c = *format++) != 0){
        if (c != '%')
            printch (c);
        else {
            char *p;
            c = *format++;
            switch (c){
                case 'd':
                case 'u':
                case 'x':
                   itoa (buf, c, *((int *) arg++));
                   p = buf;
                   goto string;
                   break;
                case 's':
                   p = *arg++;
                   if (! p)
                     p = "(null)";
                   string:
                   while (*p)
                     printch (*p++);
                   break;
                 default:
                   printch (*((int *) arg++));
                   break;
            }
        }
    }
}

#endif
