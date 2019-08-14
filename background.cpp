#include "Arduino.h"
#include "obstacle.h"
#include "background.h"
/*
 * axis system of oled display
 O-----------x
 | ______
 | |     |
 | x,y___|
 y
 */

void backgnd_gen::updt(const int rate){cld_manager.updt(rate);}
void cloud_gen::updt(const int x_decr){
  for(int i=0;i<num_clouds;i++) clouds[i].x-=x_decr;
  if(clouds[0].x<min_x_for_pop) pop();
  if(decision()) push(SCREEN_X_MAX,default_cloud_y);
}
void cloud_gen::push(const int x,const int y){
  if(num_clouds==max_num_clouds) return;
  num_clouds++;
  clouds[num_clouds-1].x=x;  clouds[num_clouds-1].y=y;
}
void cloud_gen::pop(){
  if(!num_clouds) return;
  num_clouds--;
  for(int i=0;i<num_clouds;i++) clouds[i]=clouds[i+1];
}
bool cloud_gen::decision(){
  if(num_clouds==max_num_clouds || clouds[num_clouds-1].x>(SCREEN_X_MAX-min_gap_x)) return false;
  else return randomize();
}
bool cloud_gen::randomize(){return true;}
