#include <WiFi.h>

///
WiFiServer server(5000);//ポート番号5000でサーバーとして使用する
void loop_in_ctrl();
///



struct wifi_controller_input{
  bool X;
  bool Y;
  bool A;
  bool B;
  bool RB;
  bool LB;
  bool START;
  bool BACK;
  int16_t LEFT_AXISX;
  int16_t LEFT_AXISY;
  int16_t RIGHT_AXISX;
  int16_t RIGHT_AXISY;
  int8_t CROSS_X;
  int8_t CROSS_Y;
  uint8_t RT;
  uint8_t LT;


  wifi_controller_input(){
    X = Y = A = B = RB = LB = START = BACK = false;
    LEFT_AXISX = LEFT_AXISY = RIGHT_AXISX = RIGHT_AXISY = CROSS_X = CROSS_Y = RT = LT =0;
  }
  void wifi_setup(const char* ssid ,const char* password);
  void wifi_setup(const char* ssid ,const char* password,const IPAddress ip,const IPAddress gateway,const IPAddress subnet);
  void READ();
  void Debug_Read();//only use for debug!!!Don't use it except in special cases!!!
  void input(String key,String state);
  void print_state();//only use for debug!!!Don't use it except in special cases!!!


};

inline void wifi_controller_input::wifi_setup(const char* ssid ,const char* password){
    Serial.begin(115200);//ビットレート115200でシリアル通信を開始
    delay(1000);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);//アクセスポイントに接続
    while (WiFi.status() != WL_CONNECTED && WiFi.status() != WL_IDLE_STATUS) {//接続が完了しない場合"・"を打って待機
        delay(500);
        Serial.print(".");
    }

//接続が完了したら以下の内容を表示
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());//自身のIPアドレスを表示
    
    server.begin();//サーバー開始
}

inline void wifi_controller_input::wifi_setup(const char* ssid ,const char* password,const IPAddress ip,const IPAddress gateway,const IPAddress subnet){
    Serial.begin(115200);//ビットレート115200でシリアル通信を開始
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    if(!WiFi.config(ip,gateway,subnet)){
      Serial.println("Failed to configure!");
    }
    WiFi.begin(ssid, password);//アクセスポイントに接続
    while (WiFi.status() != WL_CONNECTED && WiFi.status() != WL_IDLE_STATUS) {//接続が完了しない場合"・"を打って待機
        delay(500);
        Serial.print(".");
    }

//接続が完了したら以下の内容を表示
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());//自身のIPアドレスを表示
    
    server.begin();//サーバー開始
}

inline void wifi_controller_input::READ(){
  WiFiClient client = server.available();//サーバーに接続され、読み取り可能なデータがあるクライアントを取得
  String Key = "";
  String state = "";
  bool not_read_state = true;
  if (client) {//クライアントの情報が取得出来た場合（クライアントに対しサーバーが開かれている場合）
    Serial.println("New Client.");
    while (client.connected()) {            // client.connected()は接続時True,切断時Falth
      if (client.available()) {             // client.available()は読み込み可能なバイト数(接続先のサーバーによってクライアントに書き込まれたデータの量)を返す
        char c = client.read();
        not_read_state = true;
        if(c == '\n'){
          // Serial.print(Key);
          // Serial.print(" : ");
          while(not_read_state){
            if(client.available()){
              char c_ = client.read();
              if(c_ =='\n'){
                // Serial.println(state);
                this->input(Key,state);
                loop_in_ctrl();                
                not_read_state = false;
                Key = "";
                state = "";
              }
              else if(c_ != '\r'){
                state += c_;
              }
            }

          }
        }
        else if(c != '\r'){
          Key += c;
        }
      }
    }
  }
}

inline void wifi_controller_input::Debug_Read(){//only use for debug!!!use it except in special cases!!!
  WiFiClient client = server.available();//サーバーに接続され、読み取り可能なデータがあるクライアントを取得
  String Key = "";
  String state = "";
  bool not_read_state = true;
  if (client) {//クライアントの情報が取得出来た場合（クライアントに対しサーバーが開かれている場合）
    Serial.println("New Client.");
    while (client.connected()) {            // client.connected()は接続時True,切断時Falth
      if (client.available()) {             // client.available()は読み込み可能なバイト数(接続先のサーバーによってクライアントに書き込まれたデータの量)を返す
        char c = client.read();
        not_read_state = true;
        if(c == '\n'){
          Serial.print(Key);
          Serial.print(" : ");
          while(not_read_state){
            if(client.available()){
              char c_ = client.read();
              if(c_ =='\n'){
                Serial.println(state);
                not_read_state = false;
                Key = "";
                state = "";
              }
              else if(c_ != '\r'){
                state += c_;
              }
            }

          }
        }
        else if(c != '\r'){
          Key += c;
        }
      }
    }
  }
}

inline void wifi_controller_input::input(String key,String state){
  // char c[256] ;
  // strcpy(c,state.c_str());
  if(key == "BTN_WEST"){
    if(state == "1")this->X = true;
    else if(state == "0")this->X = false;
    else    Serial.println("Something went wrong in state");
  }
  else if(key == "BTN_NORTH"){
    if(state == "1")this->Y = true;
    else if(state == "0")this->Y = false;
    else    Serial.println("Something went wrong in state");
  }
  else if(key == "BTN_SOUTH"){
    if(state == "1")this->A = true;
    else if(state == "0")this->A = false;    
    else    Serial.println("Something went wrong in state");
  }
  else if(key == "BTN_EAST"){
    if(state == "1")this->B = true;
    else if(state == "0")this->B = false;
    else    Serial.println("Something went wrong in state");
  }
  else if(key == "BTN_TR"){
    if(state == "1")this->RB = true;
    else if(state == "0")this->RB = false;
    else  Serial.println("Something went wrong in state");
  }
  else if(key == "BTN_TL"){
    if(state == "1")this->LB = true;
    else if(state == "0")this->LB = false; 
    else    Serial.println("Something went wrong in state");   
  }
  else if(key == "BTN_SELECT"){
    if(state == "1")this->START = true;
    else if(state == "0")this->START = false;
    else    Serial.println("Something went wrong in state");
  }
  else if(key == "BTN_START"){
    if(state == "1")this->BACK = true;
    else if(state == "0")this->BACK = false;
    else    Serial.println("Something went wrong in state");
  }
  else if(key == "ABS_X"){
    this->LEFT_AXISX = atoi(state.c_str());
  }
  else if(key == "ABS_Y"){
    this->LEFT_AXISY = atoi(state.c_str());
  }
  else if(key == "ABS_RX"){
    this->RIGHT_AXISX = atoi(state.c_str());
  }
  else if(key == "ABS_RY"){
    this->RIGHT_AXISY = atoi(state.c_str());
  }
  else if(key == "ABS_HAT0X"){
    this->CROSS_X = atoi(state.c_str());
  }
  else if(key == "ABS_HAT0Y"){
    this->CROSS_Y = atoi(state.c_str());
  }
  else if(key == "ABS_RZ"){
    this->RT = atoi(state.c_str());
  }
  else if(key == "ABS_Z"){
    this->LT = atoi(state.c_str());
  }  
  else{
    Serial.println("Something went wrong in key");
  }
       

}

inline void wifi_controller_input::print_state(){//only use for debug!!!use it except in special cases!!!
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("CONTROLLER INPUT:");
  Serial.print("X:");Serial.println(this->X);
  Serial.print("Y:");Serial.println(this->Y);
  Serial.print("A:");Serial.println(this->A);
  Serial.print("B:");Serial.println(this->B);
  Serial.print("RB:"); Serial.println(this->RB);
  Serial.print("LB:");Serial.println(this->LB);
  Serial.print("START:");Serial.println(this->START);
  Serial.print("BACK:");Serial.println(this->BACK);
  Serial.print("LEFT_AXISX:");Serial.println(this->LEFT_AXISX);
  Serial.print("LEFT_AXISY:");Serial.println(this->LEFT_AXISY);
  Serial.print("RIGHT_AXISX:");Serial.println(this->RIGHT_AXISX);
  Serial.print("RIGHT_AXISY:"); Serial.println(this->RIGHT_AXISY);
  Serial.print("CROSS_X:");Serial.println(this->CROSS_X);
  Serial.print("CROSS_Y:");Serial.println(this->CROSS_Y);
  Serial.print("RT:");Serial.println(this->RT);
  Serial.print("LT:");Serial.println(this->LT);
  delay(10);
}

wifi_controller_input Controller;
