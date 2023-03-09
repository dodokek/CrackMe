#include <SFML/Window.hpp>

#include "include/patcher.h"


int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");


    // char* buffer_res = (char*) calloc (MAX_BIN_FILE_LEN, sizeof(char));
    // patch_comfile(buffer_res);

    // FILE* com_file = get_file ("vlads.com", "r");
    // char* buffer_origin = (char*) calloc (MAX_BIN_FILE_LEN, sizeof(char));
    // int file_len = read_file (com_file, &buffer_origin);
    // close_file (com_file, "vlads.com");

    // for (int i = 0; i < file_len; i++)
    // {
    //     if (buffer_origin[i] != buffer_res[i])
    //     {
    //         printf ("Difference in i = %d, origin: %c, patched: %c\n",
    //                 i, buffer_origin[i], buffer_res[i]);
    //     }
    // }

    // free (buffer_origin);
    // buffer_origin = nullptr;

    // free (buffer_res);
    // buffer_res = nullptr;

    return 0;
}


void patch_comfile (char* buffer_res)
{
    FILE* com_file = get_file ("vlads.com", "r");

    int file_len = read_file (com_file, &buffer_res);
    close_file (com_file, "vlads.com");

    printf ("Total len: %d\n", file_len);

    for (int i = 0; i < file_len; i++)
    {
        if (buffer_res[i] == 0x3D)
        {
            if (buffer_res[i+1] == 0 && i < 120)
            {
                printf ("Patching...\n");

                // buffer_res[i] = 0x3B;
                // buffer_res[i+1] = 0xC0;
                // buffer_res[i+2] = 0x90;
            }
        }
    }

    com_file = get_file ("vlads_cr.com", "w+");
    fwrite(buffer_res, sizeof (char), file_len, com_file);
    close_file (com_file, "vlads_cr.com");
}


