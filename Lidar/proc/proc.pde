
import processing.serial.*;
Serial myPort;
int received = 0;
int x = 0;
int y = 0;
int char_to_int(int c)
{ 
  return c-48;
}

void setup()
{
  size(1200,800);
  myPort = new Serial(this, Serial.list()[0], 115200);
  
  background(0);
}

void draw()
{

  int c_A = 0;
  int c_D = 0;
  int checkA = 0;
  int checkD = 0;
  int[] tab = new int[360];
  int[] tab_A = new int[3];
  for (int i = 0; i< 3; i++)
    tab_A[i] = 0;
  for (int i = 0; i< 360; i++)
     tab[i] = 0;
  while (myPort.available() > 0)
  {
    received = myPort.read();
    if (received == 83)
    {
       c_A = 0;
       c_D = 0;
    }
    if (received == 
    if (received != 65)
    {
      tab_A[c_A] = char_to_int(received);
      c_A++;
    }
    else
    {
       c_A = 0;
       checkA = 1;
    }
    if (received == 79)
      stroke(255);
    if (received == 88)
      stroke(0);
    point(x, y);
    x++;
    if (x == 200)
    {
      y++;
      x= 0;
    }
    println(y);
    //print(received);
  }
}
