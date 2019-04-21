#include "C.h"

static int bgr_r = 0;
static int bgr_g = 128;
static int bgr_b = 0;
C_t C;

static UIColor RGBA(int r, int g, int b, int a)
{
    return (((r)&0x000000FF)
		|(((g)&0x000000FF)<<8)
		|(((b)&0x000000FF)<<16)
		|(((a)&0x000000FF)<<24));
}

static UIColor RGB(int r, int g, int b)
{
    return (((r)&0x000000FF)
		|(((g)&0x000000FF)<<8)
		|(((b)&0x000000FF)<<16)
		|(((255)&0x000000FF)<<24));
}

static UIColor BGR(void)
{
    return RGB(bgr_r, bgr_g, bgr_b);
}

static void setBGR(int r, int g, int b)
{
    bgr_r = r;
    bgr_g = g;
    bgr_b = b;
}

void C_init(C_t *c)
{
	c->BGR = BGR;
	c->RGB = RGB;
	c->RGBA = RGBA;
	c->setBGR = setBGR;
}
