
import org.openkinect.freenect.*;
import org.openkinect.processing.*;
import processing.serial.*; 

int xpos=90; // set x servo's value to mid point (0-180);
int ypos=90; // and the same here

Serial port; // The serial port we will be using

// Kinect Library object
Kinect kinect;


float minThresh = 360;
float maxThresh = 825;

PImage img; 
void setup() {
  // Rendering in P3D
  size(600, 500);
  String portName = Serial.list()[0];
 port = new Serial(this, Serial.list()[0], 9600);
  kinect = new Kinect(this);
  kinect.initDepth();
  img = createImage(kinect.width,kinect.height,RGB); 
  
}

void draw() {

  background(0);
  img.loadPixels();
  
  
  // Get the raw depth as array of integers
  int[] depth = kinect.getRawDepth();
  //int record = 4500;
  int record = kinect.height;
  int rx = 0;
  int ry = 0;
  PImage dImg = kinect.getDepthImage();
  
  float sumX = 0;
  float sumY = 0;
  float totalPix = 0;
  
  
  
  for (int x = 0; x < kinect.width; x++) {
    for (int y = 0; y < kinect.height; y++) {
      int offset = x + y*kinect.width;
      int d = depth[offset];
      
      if(d > minThresh && d < maxThresh ){
        img.pixels[offset] = color(255,0,150);
        //sumX += x;
       // sumY += y;
       // totalPix++;
       if  (y < record){
         record = y;
         rx = x;
         ry = y;
       }
       
      }else{
         img.pixels[offset] = dImg.pixels[offset];
      }
      
    }
  }
  img.updatePixels();
  image(img,0,0);
  float avgX = sumX / totalPix;
  float avgY = sumY / totalPix;
  noStroke();
 fill(0,0,0,64);
  ellipse(rx,ry,30,30);
  ellipse(rx,ry,60,60);
  ellipse(rx,ry,90,90);
  println((rx/2)*180/350 +","+(ry/2)*180/240);
  update(rx, ry);


  
}
void update(int x, int y)
{
  //Calculate servo postion from mouseX
  xpos= (x/2)*180/350;
  ypos = (y/2)*180/240;
  //Output the servo position ( from 0 to 180)
  port.write(xpos+"x");
  port.write(ypos+"y");
}