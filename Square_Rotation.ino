#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>
#include <math.h>

double vertices[8][3] = {{-50,-50, 50},{50,-50, 50},{50, 50, 50},{-50,50, 50}, {-50,-50, -50},{50,-50, -50},{50, 50, -50},{-50,50,-50}};
int segments[12][2] = {{0, 1},{1, 2},{2, 3},{3,0}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6,7}, {7, 4}};
int vertices_count = 8;
int segment_count = 12;

int x_text = 0;
int y_text = 0;

long interval = 1000;
long previousMillis = 0; 
 
void setup() {
    TFT_BL_ON;
    Tft.TFTinit();  
    drawScreen();
}

void drawScreen() {
  rotate3D(0, 0, 5);
  Tft.fillRectangle(30, 70, 180,190,BLACK);
   for (int i=0; i < segment_count; i++) {
      drawline(segments[i], WHITE);
   }
}

void loop() {
  drawScreen();
  delay(1050);  
}

void drawline(int *segment, int color) {
  int x1 = translate_x(vertices[segment[0]][0]);
  int y1 = translate_y(vertices[segment[0]][1]);

  int x2 = translate_x(vertices[segment[1]][0]);
  int y2 = translate_y(vertices[segment[1]][1]);

  Tft.drawLine(x1, y1, x2, y2, color);
  
}

int translate_x(int x) {
  return x + 120;
}

int translate_y(int y) {
  return y + 160;
}

void coord_text(int x, int y) {
  String text = String(String(x) + "," + String(y) );
  int len = text.length();
  char text2[30];
  text.toCharArray(text2, 30);
  
  Tft.drawString(text2,translate_x(x),translate_y(y) - 10,1,WHITE);    // draw string: "world!!", (80, 230), size: 4, color: WHITE
}

void rotate3D(int x_theta, int y_theta, int z_theta) {
  
     double x_sinTheta = sin(x_theta);
     double x_cosTheta = cos(x_theta);
    
     double y_sinTheta = sin(y_theta);
     double y_cosTheta = cos(y_theta);
    
     double z_sinTheta = sin(z_theta);
     double z_cosTheta = cos(z_theta);

   for (int n = 0; n < vertices_count; n++) {
      if(x_theta > 0) {
          double y = vertices[n][1];
          double z = vertices[n][2];
          vertices[n][1] = y * x_cosTheta - z * x_sinTheta;
          vertices[n][2] = z * x_cosTheta + y * x_sinTheta;
      }
      if(y_theta > 0) {
          double x = vertices[n][0];
          double z = vertices[n][2];
          vertices[n][0] = x * y_cosTheta - z * y_sinTheta;
          vertices[n][2] = z * y_cosTheta + x * y_sinTheta;
      }
      if(z_theta > 0) {
          double x = vertices[n][0];
          double y = vertices[n][1];
          vertices[n][0] = x * z_cosTheta - y * z_sinTheta;
          vertices[n][1] = y * z_cosTheta + x * z_sinTheta;
      }
   }
};
