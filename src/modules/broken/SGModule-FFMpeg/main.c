/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));

    av_register_all();

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    free(minfo);
    return SG_OK;
}

//SGuint SG_EXPORT sgModuleFree(void* data)

SGuint SG_EXPORT sgAudioLoadFile(char* fname, SGuint* channels, SGuint* type, SGuint* frequency, void** data, SGuint* datalen)
{
    AVFormatContext* avFormatCtx;
    AVCodecContext* avCodecCtx;
    AVCodec* avCodec;

    if(av_open_input_file(&avFormatCtx, fname, NULL, 0, NULL) != 0)
      return SG_UNKNOWN_ERROR;
    if(av_find_stream_info(avFormatCtx) < 0)
      return SG_UNKNOWN_ERROR;

    dump_format(avFormatCtx, 0, fname, 0); // DEBUG

    SGuint i;
    SGint avStreamNum = -1;
    for(i = 0; i < avFormatCtx->nb_streams; i++)
    {
        if(avFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO) // note to self: use CODEC_TYPE_VIDEO for video input (later on, when we have a video backend)
        {
            avStreamNum = i;
            break;
        }
    }
    if(avStreamNum == -1)
        return SG_UNKNOWN_ERROR; // TODO: change this so something more appropriate (no audio stream)

    avCodecCtx = avFormatCtx->streams[avStreamNum]->codec;

    avCodec = avcodec_find_decoder(avCodecCtx->codec_id);
    if(avCodec == NULL)
        return SG_UNKNOWN_ERROR; // TODO: change (unsupported codec)

    if(avcodec_open(avCodecCtx, avCodec) < 0)
        return SG_UNKNOWN_ERROR; // TODO: change this to something more appropriate (could not open codec)

    return SG_OK;
}

/*SGuint SG_EXPORT sgAudioLoadStream(void* stream, SGuint* channels, SGuint* type, SGuint* frequency, void** data, SGuint* datalen)
{
    return 1;
}*/

SGuint SG_EXPORT sgAudioLoadFreeData(void* data)
{
    free(data);
    return SG_OK;
}
