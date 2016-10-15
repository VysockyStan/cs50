#include <stdio.h>
#include <stdint.h>
 
 const int BLOCK_SIZE = 512;
 
 int main(int argc, char *agrv[])
 {
    FILE *file;
    
    file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        fprintf(stderr, "Cannot open the file.\n");
        return 1;
    }
    
    uint8_t buf[512];
    
    int counter = 0;
    FILE *file_w = NULL;
    
    // Loop through the file
    while (fread(buf, BLOCK_SIZE, 1, file))
    {
        // Check if the first four bytes are JPEG signature
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff
            && (buf[3] == 0xe0 || buf[3] == 0xe1))
        {
            // Close the file if it is opened
            if (file_w != NULL)
                fclose(file_w);
            
            char filename[3];
            sprintf(filename, "%03d.jpg", counter);
                
            // Open a new JPEG file for writing
            file_w = fopen(filename, "w");
            
            counter++;
        }
        
        if (file_w != NULL)
            fwrite(buf, BLOCK_SIZE, 1, file_w);
    }
    
    if (file_w != NULL)
        fclose(file_w);
    
    fclose(file);
 
    return 0;
 } 