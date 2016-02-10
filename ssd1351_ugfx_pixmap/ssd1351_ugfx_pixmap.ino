#include <ssd1351-ugfx-config.h>
 
#define PIXMAP_WIDTH  128
#define PIXMAP_HEIGHT 96
 
static GDisplay* pixmap;
static pixel_t* surface;

coord_t height, width;
coord_t i, j;

void setup() {

  gfxInit();

  width = gdispGetWidth();
  height = gdispGetHeight();

  pixmap = gdispPixmapCreate(PIXMAP_WIDTH, PIXMAP_HEIGHT);
  surface = gdispPixmapGetBits(pixmap);


  Serial.println("width: " + String(gdispGetWidth()));
  Serial.println("height: " + String(gdispGetHeight()));

    for(j = 0; j < PIXMAP_HEIGHT; j++)
      for(i = 0; i < PIXMAP_WIDTH; i++)
        surface[j*PIXMAP_WIDTH + i] = RGB2COLOR(0, 255-i*(256/PIXMAP_WIDTH), j*(256/PIXMAP_HEIGHT));
 
    gdispGDrawLine(pixmap, 0, 0, gdispGGetWidth(pixmap)-1, gdispGGetHeight(pixmap)-1, White);
 
    i = j = 0;

}


void loop() {
      // Clear the old position
      gdispFillArea(i, j, PIXMAP_WIDTH, PIXMAP_HEIGHT, Black);
 
      // Change the position
      i += PIXMAP_WIDTH/2;
      if (i >= width - PIXMAP_WIDTH/2) {
        i %= width - PIXMAP_WIDTH/2;
        j = (j + PIXMAP_HEIGHT/2) % (height - PIXMAP_HEIGHT/2);
      }
      // Blit the pixmap to the real display at the new position
      gdispBlitArea(i, j, PIXMAP_WIDTH, PIXMAP_HEIGHT, surface);
 
      // Wait
      gfxSleepMilliseconds(100);
}
