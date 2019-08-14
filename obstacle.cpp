
#include "Arduino.h"
#include "obstacle.h"

/*
 * axis system of oled display
 O-----------x
 | ______
 | |     |
 | x,y___|
 y
 */

/*class obstacle{
  public:
    int obs_len;
    int obs_breadth;
    int obs_type;
    obstacle(int l,int b,int t=0){obs_len=l;obs_breadth=b;type=t;}
    void updt(obstacle o) { obs_len=o.obs_len; obs_breadth=o.obs_breadth; obs_type=o.obs_type(); }
};*/
obstacle::obstacle(int l,int b,int t){obs_len=l;obs_breadth=b;obs_type=t;}
void obstacle::updt(obstacle o) { obs_len=o.obs_len; obs_breadth=o.obs_breadth; obs_type=o.obs_type;}
//class location{
//  public:
//    int x,y;
//    location(int a,int b){x=a;y=b;}
//    void updt(location l){x=l.x; y=l.y;}
//};
location::location(int a,int b):x(a),y(b){}
void location::updt(location l){x=l.x; y=l.y;}
//class obs_gen{
//  public:
//    obstacle obs[5]={obstacle(0,0,0),obstacle(0,0,0),obstacle(0,0,0),obstacle(0,0,0),obstacle(0,0,0)};
//    int obs_num=0;
//    location locs[5]={locs(0,0),locs(0,0),locs(0,0),locs(0,0),locs(0,0)};
//    void loc_update(int);
//    bool obs_gen_dec();
//    void push(int,int,int,int,int);
//    void pop();
//};
bool obs_gen::obs_gen_dec(){
  if(obs_num==0) return true;
  return (locs[obs_num-1].x<=80-5*x_dcr);
}
void obs_gen::loc_update(){
  //increment all x s
  for(int i=0;i<obs_num;i++) locs[i].x-=x_dcr;
  //check if new obstacle is required
  if(obs_gen_dec() && chance[random(3)]) push();
  //check if object to be removed
  if(obs_num!=0 && locs[0].x<=0) pop();
}
void obs_gen::push(){
  if(obs_num==q_max) return;
  obs_num++;
  obs[obs_num-1].obs_type=random(5);
  //obs[obs_num-1].obs_len=l;  obs[obs_num-1].obs_breadth=b;  obs[obs_num-1].obs_type=t;
  obs[obs_num-1].obs_len=obs_typ[obs[obs_num-1].obs_type][0];
  obs[obs_num-1].obs_breadth=obs_typ[obs[obs_num-1].obs_type][1];
  locs[obs_num-1].x=127-obs[obs_num-1].obs_len;  
  if(obs[obs_num-1].obs_type<3)locs[obs_num-1].y=gnd_lvl;
  else locs[obs_num-1].y=random(gnd_lvl-16,gnd_lvl-2); 
}
void obs_gen::pop(){
  if(!obs_num) return;
  obs_num--;
  for(int i=0;i<obs_num;i++) {obs[i].updt(obs[i+1]); locs[i].updt(locs[i+1]); }
  score+=5;
  i++;
  if(i>3 && score<100 ){x_dcr++;i=0;}
  //else if(i>10){x_dcr++;i=0;}
}

void player_gen::plr_pos_dec(){
  
  if(plr.is_jmp){plr.jmp_stat++;
  //Serial.println("ho");
  plr.plr_y=gnd_lvl-plr.plr_height[plr.jmp_stat];}
  if(plr.jmp_stat==12){plr.is_jmp=false; plr.jmp_stat=0;}
}

void player_gen::collision_det(int x, int y, int l, int b){
  //len is x breadth is y
  if((plr.plr_x+plr.plr_len>=x && plr.plr_x<=x+l)&&(plr.plr_y>=y && plr.plr_y<=y+b)) {plr.is_lost=true;tone(D5,1000, 500);}
  
}
