#ifndef __SIEGE_GRAPHICS_SPRITE_H__
#define __SIEGE_GRAPHICS_SPRITE_H__

#include "../common.h"
#include "../core/entity.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
typedef struct SGSprite
{
    SGEntity* client;

    float xoffset;
    float yoffset;
    SGbool extimages;
    SGuint numimages;
    SGTexture** subimages;
    float image;
    float speed;

} SGSprite;

void SG_EXPORT _sgSpriteEvTick(SGEntity* client);

SGSprite* SG_EXPORT sgSpriteCreateTexture2f(SGTexture* texture, float xoffset, float yoffset);
SGSprite* SG_EXPORT sgSpriteCreateTexture(SGTexture* texture);
SGSprite* SG_EXPORT sgSpriteCreateFile2f(char* fname, float xoffset, float yoffset);
SGSprite* SG_EXPORT sgSpriteCreateFile(char* fname);
void SG_EXPORT sgSpriteDestroy(SGSprite* sprite);

void SG_EXPORT sgSpriteDrawRads3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawDegs3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawRads2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawDegs2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawRads3f1f(SGSprite* sprite, float x, float y, float z, float angle);
void SG_EXPORT sgSpriteDrawDegs3f1f(SGSprite* sprite, float x, float y, float z, float angle);
void SG_EXPORT sgSpriteDrawRads2f1f(SGSprite* sprite, float x, float y, float angle);
void SG_EXPORT sgSpriteDrawDegs2f1f(SGSprite* sprite, float x, float y, float angle);
void SG_EXPORT sgSpriteDraw3f2f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale);
void SG_EXPORT sgSpriteDraw2f2f(SGSprite* sprite, float x, float y, float xscale, float yscale);
void SG_EXPORT sgSpriteDraw3f(SGSprite* sprite, float x, float y, float z);
void SG_EXPORT sgSpriteDraw2f(SGSprite* sprite, float x, float y);

void SG_EXPORT sgSpriteGetSize(SGSprite* sprite, SGuint* width, SGuint* height);
SGuint SG_EXPORT sgSpriteGetWidth(SGSprite* sprite);
SGuint SG_EXPORT sgSpriteGetHeight(SGSprite* sprite);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_SPRITE_H__
