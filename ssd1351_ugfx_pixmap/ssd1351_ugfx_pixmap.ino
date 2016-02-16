#include <ssd1351-ugfx-config.h>
 
#define PIXMAP_WIDTH  25
#define PIXMAP_HEIGHT 25
 
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
  delay(10);

  Serial.println("width: " + String(gdispGetWidth()));
  Serial.println("height: " + String(gdispGetHeight()));

  for(j = 0; j < PIXMAP_HEIGHT; j++) {
    for(i = 0; i < PIXMAP_WIDTH; i++) {
      surface[j*PIXMAP_WIDTH + i] = RGB2COLOR(0, 255-i*(256/PIXMAP_WIDTH), j*(256/PIXMAP_HEIGHT));
    }
  }
 
  gdispGDrawLine(pixmap, 0, 0, gdispGGetWidth(pixmap)-1, gdispGGetHeight(pixmap)-1, White);
 
  i = j = 0;
  pinMode(15, OUTPUT);

  for(int m=10; m > 0; m--){
    digitalWriteFast(15, LOW);
    delay(m);
    digitalWriteFast(15, HIGH);
    delay(m);
  }

}


void loop() {
    digitalWriteFast(15, HIGH);

    // Clear the old position
    gdispGFillArea(pixmap, i, j, PIXMAP_WIDTH, PIXMAP_HEIGHT, White);
    // Change the position
    i += PIXMAP_WIDTH/2;
    if (i >= width - PIXMAP_WIDTH/2) {
      i %= width - PIXMAP_WIDTH/2;
      j = (j + PIXMAP_HEIGHT/2) % (height - PIXMAP_HEIGHT/2);
    }
    // Blit the pixmap to the real display at the new position
    gdispGBlitArea(pixmap, i, j, PIXMAP_WIDTH, PIXMAP_HEIGHT,10,10, 1, surface);
    // Wait
    gfxSleepMilliseconds(100);
    
    digitalWriteFast(15, LOW);

}
