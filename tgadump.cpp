#include <cstdio>

struct TgaFile {
    unsigned char idLength;
    unsigned char colorMapType;
    unsigned char imageType;
    struct ColorMapSpec_t {
        unsigned short firstEntryIndex;
        unsigned short colorMapLength;
        unsigned char entrySize;
    } ColorMapSpec;
    struct ImageSpec_t {
        unsigned short xOrigin;
        unsigned short yOrigin;
        unsigned short width;
        unsigned short height;
        unsigned char pixelDepth;
        unsigned char imageDescriptor;
    } ImageSpec;
    unsigned char *imageId;
    unsigned char *colorMap;
    unsigned char *imageData;
};

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("Not enough arguments!\n");
        return -1;
    }

    printf("%s\n", argv[1]);
    FILE *f = fopen(argv[1], "rb");
    if (f == nullptr) {
        printf("Cannot open file.\n");
        return -1;
    }

    if (fseek(f, 0, SEEK_END)) {
        printf("Failed to seek to end of file.\n");
        return -1;
    }

    int filesize = ftell(f);
    printf("Filesize: %d bytes\n", filesize);

    if (fseek(f, 0, SEEK_SET)) {
        printf("Failed to seek to beginning of file.\n");
        return -1;
    }

    unsigned char *buffer = new unsigned char[filesize];
    int bytesRead = fread(buffer, 1, filesize, f);
    if (bytesRead != filesize) {
        printf("Couldn't read all the bytes for some reason.\n");
        return -1;
    }
    if (fclose(f)) {
        printf("Failed to close the file.\n");
        return -1;
    }

    TgaFile image;
    image.idLength = buffer[0];
    image.colorMapType = buffer[1];
    image.imageType = buffer[2];
    image.ColorMapSpec.firstEntryIndex = buffer[3] | buffer[4] << 8;
    image.ColorMapSpec.colorMapLength = buffer[5] | buffer[6] << 8;
    image.ColorMapSpec.entrySize = buffer[7];
    image.ImageSpec.xOrigin = buffer[8] | buffer[9] << 8;
    image.ImageSpec.yOrigin = buffer[10] | buffer[11] << 8;
    image.ImageSpec.width = buffer[12] | buffer[13] << 8;
    image.ImageSpec.height = buffer[14] | buffer[15] << 8;
    image.ImageSpec.pixelDepth = buffer[16];
    image.ImageSpec.imageDescriptor = buffer[17];
    image.imageId = &buffer[18];
    image.colorMap = &buffer[18] + image.idLength;
    image.imageData = image.colorMap + image.ColorMapSpec.colorMapLength;

    printf("Image ID length: %d\n", image.idLength);
    printf("Color map type: %d\n",  image.colorMapType);
    printf("Image type: %d\n",      image.imageType);
    printf("Color map spec:\n");
    printf("  First Entry Index: %d\n",    image.ColorMapSpec.firstEntryIndex);
    printf("  Color map length: %d\n",     image.ColorMapSpec.colorMapLength);
    printf("  Color map entry size: %d\n", image.ColorMapSpec.entrySize);
    printf("Image spec:\n");
    printf("  X-origin: %d\n",         image.ImageSpec.xOrigin);
    printf("  Y-origin: %d\n",         image.ImageSpec.yOrigin);
    printf("  Width: %u\n",            image.ImageSpec.width);
    printf("  Height: %u\n",           image.ImageSpec.height);
    printf("  Pixel depth: %d\n",      image.ImageSpec.pixelDepth);
    printf("  Image Descriptor: %d\n", image.ImageSpec.imageDescriptor);

    printf("Image ID:\n");
    for (int i = 0; i < image.idLength; i++) {
        printf("0x%02x ", *(image.imageId + i));
    }

    printf("Color map:\n");
    for (int i = 0; i < image.ColorMapSpec.colorMapLength; i++) {
        printf("0x%02x ", *(image.colorMap + i));
    }

    printf("Color data:\n");
    for (int i = 0, cnt = 1; i < (image.ImageSpec.height * image.ImageSpec.width * (image.ImageSpec.pixelDepth / 8)); i++, cnt++) {
        printf("0x%02x ", *(image.imageData + i));
        if (cnt == ((image.ImageSpec.pixelDepth / 8) * image.ImageSpec.width)) {
            printf("\n");
            cnt = 0;
        }
    }
    printf("\n");

    delete [] buffer;
    return 0;
}
