#include <mbed.h>
#include <iostream>
#include "BufferedSerial.h"
#include "rplidar.h"
#include "MapLidar.h"
#include "Vector2i.h"
#include "stdlib.h"

RPLidar lidar;
BufferedSerial se_lidar(A0, A1);
Serial pc(USBTX, USBRX);
DigitalIn user_button(USER_BUTTON);
MapLidar map;
Vector2i pos_actuel(0, 0);

void get_info_lidar()
{
  if (IS_OK(lidar.waitPoint()))
  {
    map.updateMap(pos_actuel, lidar.dis, lidar.ang);
    //pc.printf("%d, %d\n", lidar.dis, lidar.ang);
  }
  else
  {

    lidar.startScan();
  }
}

int main()
{
  pc.baud(2000000);
  lidar.begin(se_lidar);
  lidar.setAngle(0, 360);
  Timer t;

  t.start();
  while (1)
  {
    get_info_lidar();
    if (t.read() > 0.1f)
    {
      for (int i = 0; i < 360; i++)
      {
        /*if (lidar.Data[i] > 1000)
        {
          pc.printf("%f\n", 0.0f);
        }
        else
        {*/
        pc.printf("%f\n", (float)lidar.Data[i]);
        //}
      }
      pc.printf("%f\n", 100.0f);
      t.reset();
    }
  }
  return 0;
}