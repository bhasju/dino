#include "obstacle.h"
#include "background.h"
#include "static.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>



U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);




backgnd_gen background_manager;

obs_gen generator;
player_gen gen;
player &dino = gen.plr;
bool button;
bool button_pressed(){
  int val=digitalRead(D4);
  if(!button && val){button=true;return true;}
  if(button && val)button=false;
  return false;
}

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  //general
  Serial.begin(115200);
 // obs_gen generator();
 pinMode(D4, INPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  if (!gen.plr.is_lost){
    
    generator.loc_update();
    for(int i=0;i<generator.obs_num; i++){
      obstacle o=generator.obs[i];
      location l = generator.locs[i];
      u8g2.drawXBM(l.x,l.y-o.obs_breadth,o.obs_len,o.obs_breadth, obstacles[o.obs_type]);
    }

    
    cloud_gen &cm=background_manager.cld_manager;
    for(int i=0;i<cm.num_clouds; i++){
      location l = cm.clouds[i];
      u8g2.drawXBM(l.x,l.y,cm.cloud_length,cm.cloud_height, clouds);
    }
    background_manager.updt(generator.x_dcr);
    
    
    if(!digitalRead(D4)){dino.is_jmp=true;tone(D5,1000,200);}
    gen.plr_pos_dec();
    gen.collision_det(generator.locs[0].x,generator.locs[0].y,generator.obs[0].obs_len,generator.obs[0].obs_breadth);
    //u8g2.drawBox(gen.plr.plr_x, gen.plr.plr_y-gen.plr.plr_breadth, gen.plr.plr_len, gen.plr.plr_breadth)
    u8g2.setBitmapMode(1);
    u8g2.drawXBM( dino.plr_x, dino.plr_y-10, dino.plr_len ,dino.plr_breadth, trex);
    u8g2.setFont(u8g2_font_u8glib_4_tf);
    u8g2.setCursor(10,10);
    u8g2.print("score: ");
    u8g2.print(generator.score); 
    u8g2.print("  highscore: ");
    u8g2.print(generator.highest_score); 
    u8g2.drawHLine(0,gnd_lvl,128);
    
  }
  else{
    
    if (generator.score > generator.highest_score) generator.highest_score=generator.score;
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(10,32,"Game Over"); 
    u8g2.setFont(u8g2_font_u8glib_4_tf);
    u8g2.setCursor(10,10);
    u8g2.print("score: ");
    u8g2.print(generator.score); 
    u8g2.print("  highscore: ");
    u8g2.print(generator.highest_score); 
    if(!digitalRead(D4)){gen.plr.is_lost=false; generator.obs_num=0; 
    
    generator.score=0;generator.x_dcr=5;generator.i=0;
    dino.is_jmp=0;
    dino.jmp_stat=0;
    
    }
     
  }
//  while(gen.plr.is_lost){
//    u8g2.setFont(u8g2_font_ncenB14_tr);
//    u8g2.drawStr(10,32,"Game Over"); 
//    if(!digitalRead(D4)) {gen.plr.is_lost=false; generator.
    
//  }
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(100);
  
}
