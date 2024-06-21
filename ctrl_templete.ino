#include "CTRL.h"
void loop_in_ctrl();

void setup() {
  // const IPAddress ip(~,~,~,~);
  // const IPAddress gateway(~,~,~,~);
  // const IPAddress subnet(~,~,~,~);
  // Controller.wifi_setup("yourssid","yourpassword",ip,gateway,subnet);
  //固定ipを使いたい場合は10行目を消して5~8行目のコメントアウトを解除する
  Controller.wifi_setup("Buffalo-G-EB08","whg5xmds3jf6w");
  // put your setup code here, to run once:





while(true){
  Controller.READ(loop_in_ctrl);
  // Controller.Debug_Read();
}


}

void loop_in_ctrl(){
  // put your main code here, to run repeatedly:
}

void loop() {//ここじゃなくて上のloop_in_ctrl()関数に書き込む

  
}
