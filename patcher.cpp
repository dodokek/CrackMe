#include "include/patcher.h"


int main()
{                       
    char* buffer_res = (char*) calloc (MAX_BIN_FILE_LEN, sizeof(char));
    patch_comfile(buffer_res);


    free (buffer_res);
    buffer_res = nullptr;

    return 0;
}


void patch_comfile (char* buffer_res)
{
    FILE* com_file = get_file ("hard_crack.com", "rb");

    int file_len = read_file (com_file, &buffer_res);
    close_file (com_file, "hard_crack.com");

    printf ("Total len: %d\n", file_len);

    for (int i = 0; i < file_len; i++)
    {
        if (buffer_res[i] == 0x75)
        {
            if (buffer_res[i+1] == 0x30)
            {
                printf ("Patching...\n");

                buffer_res[i] = 0xEB;
                buffer_res[i+1] = 0x14;
            }
        }
    }

    com_file = get_file ("sanya_cr.com", "wb+");
    fwrite(buffer_res, sizeof (char), file_len, com_file);
    close_file (com_file, "sanya_cr.com");
}


