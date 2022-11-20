#include<stdio.h>
int main(void) {
  int data[] = {0x636c6557, 0x20656d6f, 0x78206f74,
                0x756f7969, 0x6e694c20, 0x67207875,
                0x70756f72, 0x32303220, 0x00000a31};
  puts((const char*)data);
}