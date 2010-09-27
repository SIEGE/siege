#include "common.h"
#include "save.h"

#include "buffer.h"
#include <stdio.h>

//http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
//todo: get it working!
void paBufferSaveWAV16(Buffer* buffer, char* fname)
{
    paBufferFinalizeS(buffer);

    FILE* f = fopen(fname, "w");

    uint32_t buf32;
    uint16_t buf16;
    fwrite("RIFF", 4, 1, f);
    buf32 = 4 // cksize
          + 24 // format
          + 8 + 2 * buffer->slength; // data
    fwrite(&buf32, 1, 4, f);
    fwrite("WAVE", 4, 1, f);

    // Format chunk
    fwrite("fmt ", 4, 1, f);
    buf32 = 16; // cksize
    fwrite(&buf32, 1, 4, f);
    buf16 = 0x0001; // wFormatTag = WAVE_FORMAT_PCM
    fwrite(&buf16, 1, 2, f);
    buf16 = 1; // nChannels
    fwrite(&buf16, 1, 2, f);
    buf32 = buffer->context->frequency; // nBuffersPerSec
    fwrite(&buf32, 1, 4, f);
    buf32 = 2 * buffer->context->frequency; // nAvgBytesPerSec
    fwrite(&buf32, 1, 4, f);
    buf16 = 2; // nBlockAlign
    fwrite(&buf16, 1, 2, f);
    buf16 = 8 * 2; // wBitsPerBuffer
    fwrite(&buf16, 1, 2, f);

    // Data chunk
    fwrite("data", 4, 1, f);
    buf32 = 2 * buffer->slength; // cksize
    fwrite(&buf32, 1, 4, f);
    fwrite(buffer->cdata, buffer->slength, 2, f);
    //fwrite(buffer->data, buffer->slength, 4, f);

    fclose(f);
}
