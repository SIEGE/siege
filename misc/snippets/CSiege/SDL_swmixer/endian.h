#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#define _SWM_Flip8(i) (i)
#define _SWM_Flip16(i) ((((i) & 0xFF) << 8) | ((i) >> 8))
#define _SWM_Flip24(i) ((((i) & 0xFF) << 16) | ((i) & 0xFF00) | ((i) >> 16))

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#   define _SWM_ToLE8(i) (i)
#   define _SWM_ToBE8(i) _SWM_Flip8(i)
#   define _SWM_ToLE16(i) (i)
#   define _SWM_ToBE16(i) _SWM_Flip16(i)
#   define _SWM_ToLE24(i) (i)
#   define _SWM_ToBE24(i) _SWM_Flip24(i)
#else
#   define _SWM_ToLE8(i) _SWM_Flip8(i)
#   define _SWM_ToBE8(i) (i)
#   define _SWM_ToLE16(i) _SWM_Flip16(i)
#   define _SWM_ToBE16(i) (i)
#   define _SWM_ToLE24(i) _SWM_Flip24(i)
#   define _SWM_ToBE24(i) (i)
#endif

#endif // __ENDIAN_H__
