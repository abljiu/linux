int main(int argc, char **argv)
{
    int data1[2][3] = {{0x636c6557, 0x20656d6f, 0x58206f74},
                       //  u o y i     n i L            \0
                       {0x756f7969, 0x6e694c20, 0x00000000}};
    int data2[] = {0x47207875, 0x70756f72, 0x32303220, 0x00000a32};
    char *a = (char *)data1;
    char *b = (char *)data2;
    char buf[1024];
    strcpy(buf, a);
    strcat(buf, b);
    printf("%s \n", buf);

}