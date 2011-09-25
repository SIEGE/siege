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

#define SG_BUILD_LIBRARY
#include <siege/audio/buffer.h>
#include <siege/modules/audio.h>

#include <stdlib.h>

SGbool SG_EXPORT _sgAudioBufferInit(void)
{
    return SG_TRUE;
}
SGbool SG_EXPORT _sgAudioBufferDeinit(void)
{
    return SG_TRUE;
}

SGAudioBuffer* SG_EXPORT sgAudioBufferCreateFile(const char* fname)
{
    SGAudioBuffer* buffer = malloc(sizeof(SGAudioBuffer));

    if(psgmAudioBufferCreate != NULL)
        psgmAudioBufferCreate(&buffer->handle);

    SGuint channels = 0;
    SGuint format = 0;
    SGuint frequency = 0;
    void* data = NULL;
    SGuint datalen = 0;
    SGuint nsamples = 0;
    void* file = NULL;
    void* handle = NULL;
    if(psgmAudioFileCreate)
		psgmAudioFileCreate(&file, fname, &channels, &format, &frequency);

	if(psgmAudioFileGetHandle
	&& psgmAudioFileGetHandle(file, &handle) == SG_OK
	&& psgmAudioBufferSetHandle(buffer->handle, handle) == SG_OK)
	{
	}
	else
	{
		if(psgmAudioFileNumSamples)
			psgmAudioFileNumSamples(file, &nsamples);
		switch(format)
		{
			case SG_AUDIO_FORMAT_S8:
			case SG_AUDIO_FORMAT_U8:
				datalen = nsamples * channels;
				break;
			case SG_AUDIO_FORMAT_S16:
			case SG_AUDIO_FORMAT_U16:
				datalen = 2 * nsamples * channels;
				break;
			case SG_AUDIO_FORMAT_S24:
			case SG_AUDIO_FORMAT_U24:
				datalen = 3 * nsamples * channels;
				break;
			case SG_AUDIO_FORMAT_S32:
			case SG_AUDIO_FORMAT_U32:
				datalen = 4 * nsamples * channels;
				break;
			case SG_AUDIO_FORMAT_F:
				datalen = 4 * nsamples * channels;
				break;
			case SG_AUDIO_FORMAT_D:
				datalen = 8 * nsamples * channels;
				break;
		}
		data = malloc(datalen);
		if(psgmAudioFileRead)
			psgmAudioFileRead(file, data, &datalen);
		if(psgmAudioBufferSetData != NULL)
			psgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
		free(data);
	}

	if(psgmAudioFileDestroy)
		psgmAudioFileDestroy(file);

    return buffer;
}
void SG_EXPORT sgAudioBufferDestroy(SGAudioBuffer* buffer)
{
    if(buffer == NULL)
        return;

    if(psgmAudioBufferDestroy != NULL)
        psgmAudioBufferDestroy(buffer->handle);
    free(buffer);
}

void SG_EXPORT sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, size_t datalen)
{
    if(buffer == NULL)
        return;
    if(psgmAudioBufferSetData != NULL)
        psgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
}
