#ifndef background_h
#define background_h
/*
 * axis system of oled display
 O-----------x
 |
 |
 |
 y
 */
#include "Arduino.h"
#include "obstacle.h"

const static int SCREEN_X_MAX=123;

class cloud_gen{
  const static int max_num_clouds=2;
  const static int min_x_for_pop=0;
  const static int min_gap_x=40;
  const static int default_cloud_y=15;
  void pop();
  void push(const int x,const int y);
  bool decision();
  bool randomize();
  public:
    const static int cloud_length=16;
    const static int cloud_height=8;
    int num_clouds=0;
    location clouds[max_num_clouds];
    void updt(const int rate);
};
class backgnd_gen{
  public:
    cloud_gen cld_manager;
    void updt(const int rate);
};


#endif
