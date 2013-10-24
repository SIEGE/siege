#ifndef __SG_MODULE_H__
#define __SG_MODULE_H__

#ifndef SG_FPTR
#ifdef SG_BUILD_MODULE
#define SG_FPTR(NAME) NAME
#else
#define SG_FPTR(NAME) (*NAME)
#endif /* SG_BUILD_MODULE */
#endif /* SG_FPTR */

#endif /* __SG_MODULE_H__ */
