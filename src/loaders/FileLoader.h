//
// Created by Martin on 14. 11. 2015.
//

#ifndef PPGSO_FILELOADER_H
#define PPGSO_FILELOADER_H

#include <stdio.h>
#include <stdlib.h>


class FileLoader {

public:

    typedef struct {
        unsigned char imageTypeCode;
        short int imageWidth;
        short int imageHeight;
        unsigned char bitCount;
        unsigned char *imageData;
    } TGAFILE_t;

    static bool LoadTGAFile(const char *, TGAFILE_t *);
};


#endif //PPGSO_FILELOADER_H