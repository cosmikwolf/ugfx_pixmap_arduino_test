the ssd1351_ugfx_pixmap folder contains the test sketch, the folder named libraries contains all arduino libraries EXCEPT the ugfx implementation I am using, which is the same WITH THE ONE EXCEPTION:


the file ugfx/src/gdisp/gdisp_mk.c has line 23 commented out:

//#include "gdisp_pixmap.c"

This file is explicitly included in ugfx_arduino.c 
