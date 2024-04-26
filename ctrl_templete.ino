#include "CTRL.h"
void setup() {
  // const IPAddress ip(~,~,~,~);
  // const IPAddress gateway(~,~,~,~);
  // const IPAddress subnet(~,~,~,~);
  // Controller.wifi_setup("yourssid","yourpassword",ip,gateway,subnet);
  //固定ipを使いたい場合は8行目を消して3~6行目のコメントアウトを解除する
  Controller.wifi_setup("yourssid","yourpassword");
  // put your setup code here, to run once:

}

void loop_in_ctrl(){
  // put your main code here, to run repeatedly:
}

void loop() {//ここじゃなくて上のloop_in_ctrl()関数に書き込む
  Controller.READ();
}
