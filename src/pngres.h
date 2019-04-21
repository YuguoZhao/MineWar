#ifndef _PNGRES_H
#define _PNGRES_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4996)

void *load_png(const char *filepath, int *pw, int *ph);

#ifdef __cplusplus
}
#endif

#endif //_PNGRES_H
