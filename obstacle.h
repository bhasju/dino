#ifndef obstacle_h
#define obstacle_h
/*
 * axis system of oled display
 O-----------x
 |
 |
 |
 y
 */
#include "Arduino.h"
#define gnd_lvl 50
class obstacle{
  public:
  //len is x breadth is y
    int obs_len=5;
    int obs_breadth=5;
    int obs_type=0;
    obstacle(int l=5,int b=5,int t=0);
    void updt(obstacle o);
};
class location{
  public:
    int x=123,y=32;
    location(int a=0,int b=0);
    void updt(location l);
};
class obs_gen{
  const static int q_max=20;
  public:
    obstacle obs[q_max];//={obstacle(0,0,0),obstacle(0,0,0),obstacle(0,0,0),obstacle(0,0,0),obstacle(0,0,0)};
    int obs_typ[5][2]={{5,7},{7,9},{6,10},{8,8},{6,6}};//first 3 are cacti, last two are birds or whatever
    int x_dcr=5;
    int obs_num=0;
    location locs[q_max];//={locs(0,0),locs(0,0),locs(0,0),locs(0,0),locs(0,0)};
    int chance[3]={0,1,1};// to give a 1/3rd chance of generating an obstacle
    int score=0;
    int highest_score=0;
    int i=0;
    void loc_update();
    bool obs_gen_dec();
    void push();
    void pop();
};

class player{
  public:
  //len is x breadth is y
    int plr_len=10;
    int plr_breadth=10;
    int plr_x=10;
    int plr_y=gnd_lvl;
    bool is_jmp=false;
    int jmp_stat=0;
    int plr_height[12]={0,12,16,18,19,20,20,19,18,16,12,0};
    int score=0;
    bool is_lost=false;
    
    //{0,8,12,14,15,16,16,15,14,12,8,0}
};
class player_gen{
  public:
    player plr;
    void plr_pos_dec();
    void collision_det(int,int,int,int);
    
};




#endif
