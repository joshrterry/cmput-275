#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r, g, b;
} Pixel;

void readPPM(FILE *input, char *format, int *width, int *height, int *maxColor, Pixel **image) {
    // Read header
    fscanf(input, "%s", format);
    fscanf(input, "%d %d", width, height);
    fscanf(input, "%d", maxColor);

    // Allocate memory for image
    *image = malloc((*width) * (*height) * sizeof(Pixel));

    // Read pixel data
    for (int i = 0; i < (*width) * (*height); i++) {
        fscanf(input, "%d %d %d", &((*image)[i].r), &((*image)[i].g), &((*image)[i].b));
    }
}

void flipImage(int width, int height, Pixel *image) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            // Swap pixels horizontally
            Pixel temp = image[y * width + x];
            image[y * width + x] = image[y * width + (width - x - 1)];
            image[y * width + (width - x - 1)] = temp;
        }
    }
}

void applySepia(int width, int height, Pixel *image) {
    for (int i = 0; i < width * height; i++) {
        int oldR = image[i].r;
        int oldG = image[i].g;
        int oldB = image[i].b;

        image[i].r = (oldR * 0.393) + (oldG * 0.769) + (oldB * 0.189);
        image[i].g = (oldR * 0.349) + (oldG * 0.686) + (oldB * 0.168);
        image[i].b = (oldR * 0.272) + (oldG * 0.534) + (oldB * 0.131);

        // Clamp values to max color (255)
        image[i].r = image[i].r > 255 ? 255 : image[i].r;
        image[i].g = image[i].g > 255 ? 255 : image[i].g;
        image[i].b = image[i].b > 255 ? 255 : image[i].b;
    }
}

void printPPM(const char *format, int width, int height, int maxColor, Pixel *image) {
    printf("%s\n%d %d\n%d\n", format, width, height, maxColor);
    for (int i = 0; i < width * height; i++) {
        printf("%d %d %d", image[i].r, image[i].g, image[i].b);
        if ((i + 1) % width == 0) {
            printf("\n");  // New row
        } else {
            printf(" ");  // Space between pixels
        }
    }
}

int main(int argc, char *argv[]) {
    char format[3];
    int width, height, maxColor;
    Pixel *image;

    // Read image from stdin
    readPPM(stdin, format, &width, &height, &maxColor, &image);

    // Process command-line arguments
    int flip = 0, sepia = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) flip = 1;
        if (strcmp(argv[i], "-s") == 0) sepia = 1;
    }

    // Apply transformations
    if (flip) flipImage(width, height, image);
    if (sepia) applySepia(width, height, image);

    // Print the output image
    printPPM(format, width, height, maxColor, image);

    // Free allocated memory
    free(image);
    return 0;
}