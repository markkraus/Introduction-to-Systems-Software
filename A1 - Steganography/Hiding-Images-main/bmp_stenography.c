// Including our standard I/O, standard library, and string header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BMP file Header Structure
#pragma pack(1)             //Ensuring no padding between elements
typedef struct {
    unsigned char format[2];
    unsigned int size;
    unsigned short int reserved1, reserved2;
    unsigned int offset;
} BMPHEADER;

// DIB Header Structure
#pragma pack(1)
typedef struct{
    unsigned int size;
    int width, height;
    unsigned short int color_planes;
    unsigned short int bits_per_pixel;
    unsigned int compression_scheme;
    unsigned int image_size;
    int horizontal_resolution, vertical_resolution;
    unsigned int colors_in_palette;
    unsigned int important_colors;
} DIBHEADER;

// Pixel Structure
#pragma pack(1)
typedef struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} PIXEL;


int main(int argc, char *argv[]) {

    if(argc < 3){
        printf("Error: Expected at least 3 arguments, received %d\n", argc - 1);
        return 1;
    }

    // Open the BMP/DIB files for reading and writing
    FILE *fp_1 = fopen(argv[2], "r+");
        
    // Create BMP/DIB/Pixel types to read from
    BMPHEADER bmp_header;
    DIBHEADER dib_header;
    PIXEL pixel;

    // Read the BMP file
    fread(&bmp_header, sizeof(bmp_header), 1, fp_1);

    // Moving to the beginning of DIB Header
    fseek(fp_1, sizeof(bmp_header), SEEK_SET);
    
    // Read the DIB Header
    fread(&dib_header, sizeof(dib_header), 1, fp_1);


        // BMP Header format validation:
        // If the BMP file's type is not '.bmp', we don't support the file
        if (bmp_header.format[0] != 'B' || bmp_header.format[1] != 'M') {
            printf("Error: file format is not supported\n");
            fclose(fp_1);
            return 1;

        }

        // DIB Header format validaton:
        // 1. If the DIB header != size 40, we don't support the file
        // 2. If our bits per pixel != 24, we don't support the file
        if(dib_header.size != 40 || dib_header.bits_per_pixel != 24){
            printf("Error: file format is not supported\n");
            fclose(fp_1);
            return 1;

        }


    // Displays the BMP/DIB information if '--info' is inputted as 2nd argument
    if(strcasecmp(argv[1], "--info") == 0){

        // Display the contents of BMP file header
        printf("=== BMP Header ===\n");
        printf("Type: %c%c\n", bmp_header.format[0], bmp_header.format[1]);
        printf("Size: %d\n", bmp_header.size);
        printf("Reserved 1: %d\n", bmp_header.reserved1);
        printf("Reserved 2: %d\n", bmp_header.reserved2);
        printf("Image offset: %d\n", bmp_header.offset);
        printf("\n");

    
        // Display the contents of DIB header
        printf("=== DIB Header ===\n");
        printf("Size: %d\n", dib_header.size);
        printf("Width: %d\n", dib_header.width);
        printf("Height: %d\n", dib_header.height);
        printf("# color planes: %d\n", dib_header.color_planes);
        printf("# bits per pixel: %d\n", dib_header.bits_per_pixel);
        printf("Compression scheme: %d\n", dib_header.compression_scheme);
        printf("Image size: %d\n", dib_header.image_size);
        printf("Horizontal resolution: %d\n", dib_header.horizontal_resolution);
        printf("Vertical resolution: %d\n", dib_header.vertical_resolution);
        printf("# colors in palette: %d\n", dib_header.colors_in_palette);
        printf("# important colors: %d\n", dib_header.important_colors);

        // Returns file pointer to start of BMP Header
        fseek(fp_1, sizeof(bmp_header), SEEK_SET);

    } // END IF

    // Moving file pointer to start of the pixel array - [the end of the BMP Header file]
    fseek(fp_1, bmp_header.offset, SEEK_SET);

    // Calculate the padding amount for each row of pixels - - - **Final modulo ensures number is positive**
    int padding = (4 - (dib_header.width * 3) % 4) % 4;

    // Transforms pixels if '--reveal' is inputted as 2nd argument
    if(strcasecmp(argv[1], "--reveal") == 0){

        // Loop through rows
        for(int i = 0; i < dib_header.height; i++){

            // Loop through each pixel in given row
            for(int j = 0; j < dib_header.width; j++){

                // Read in each pixel
                fread(&pixel, sizeof(pixel), 1, fp_1);

                // Swap red's 4MSB <--> 4LSB
                unsigned char MSB_red = pixel.red >> 4;
                unsigned char LSB_red = pixel.red & 0x0F; // masking
                LSB_red = LSB_red << 4;
                pixel.red = MSB_red | LSB_red;

                // Swap green's 4MSB <--> 4LSB
                unsigned char MSB_green = pixel.green >> 4;
                unsigned char LSB_green = pixel.green & 0x0F; // masking
                LSB_green = LSB_green << 4;
                pixel.green = MSB_green | LSB_green;

                // Swap blue's 4MSB <--> 4LSB
                unsigned char MSB_blue = pixel.blue >> 4;
                unsigned char LSB_blue = pixel.blue & 0x0F; // masking
                LSB_blue = LSB_blue << 4;
                pixel.blue = MSB_blue | LSB_blue;

                // Move pointer back to the beginning of the current pixel
                fseek(fp_1, -sizeof(pixel), SEEK_CUR);

                // Write in each pixel
                fwrite(&pixel, sizeof(pixel), 1, fp_1);

            } // END INNER LOOP

            // Skip the padded bytes
            fseek(fp_1, padding, SEEK_CUR);

        } //END OUTER LOOP

    } // END IF

    // Returns file pointer to start of BMP Header
    fseek(fp_1, sizeof(bmp_header), SEEK_SET);

    // If we have want to '--hide':
    if(strcasecmp(argv[1], "--hide") == 0){

        // Open a second file pointer
        FILE *fp_2 = fopen(argv[3], "r+");

        // Create a second DIB Header to read from
        BMPHEADER bmp_header_2;
        DIBHEADER dib_header_2;
        PIXEL pixel_2;

        // Read the contents of the second BMP File
        fread(&bmp_header_2, sizeof(BMPHEADER), 1, fp_2);

        // Move to the start of the DIB Header
        fseek(fp_1, sizeof(BMPHEADER), SEEK_SET);
        fseek(fp_2, sizeof(BMPHEADER), SEEK_SET);
        
        //Read both file's DIB header
        fread(&dib_header, sizeof(DIBHEADER), 1, fp_1);
        fread(&dib_header_2, sizeof(DIBHEADER), 1, fp_2);

        // If the files' height and width are different, throw an error
        if(dib_header.width != dib_header_2.width || dib_header.height != dib_header_2.height){

            printf("Error: File heights and widths are not equal\n");
            fclose(fp_1);
            fclose(fp_2);
            return 1;
        }

        // Move both file pointers to the start of pixel structures
        fseek(fp_1, bmp_header.offset, SEEK_SET);
        fseek(fp_2, bmp_header_2.offset, SEEK_SET);

        for(int i = 0; i < dib_header.height; i++){

            for(int j = 0; j < dib_header.width; j++){

                // Read both pixels
                fread(&pixel, sizeof(PIXEL), 1, fp_1);
                fread(&pixel_2, sizeof(PIXEL), 1, fp_2);

                unsigned char red_2 = pixel_2.red & 0xF0;
                unsigned char red = pixel.red & 0xF0;
                red_2 = red_2 >> 4;
                pixel.red = red | red_2;

                unsigned char green_2 = pixel_2.green & 0xF0;
                unsigned char green = pixel.green & 0xF0;
                green_2 = green_2 >> 4;
                pixel.green = green | green_2;

                unsigned char blue_2 = pixel_2.blue & 0xF0;
                unsigned char blue = pixel.blue & 0xF0;
                blue_2 = blue_2 >> 4;
                pixel.blue = blue | blue_2;

                // Move pointer back to the original pixel
                fseek(fp_1, -sizeof(PIXEL), SEEK_CUR);
                fseek(fp_2, -sizeof(PIXEL), SEEK_CUR);

                // Write in each pixel
                fwrite(&pixel, sizeof(PIXEL), 1, fp_1);
                fwrite(&pixel_2, sizeof(PIXEL), 1, fp_2);

            } // END INNER LOOP

            // Skip the padded bytes
            fseek(fp_1, padding, SEEK_CUR);
            fseek(fp_2, padding, SEEK_CUR);

        } // END OUTER LOOP

        // Close the second file
        fclose(fp_2);

    } // END IF

    // Close the first file
    fclose(fp_1);


    return 0;

}// END MAIN