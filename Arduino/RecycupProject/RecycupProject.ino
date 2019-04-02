#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#include <Thread.h>
#include <ThreadController.h>
#include <WiFi.h>

#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

uint8_t pacman[408] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t pacman2[408] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t wall[408] =
{
  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
  2,  8,  8,  8,  8,  8,  8,  8,  2,  8,  8,  8,  8,  8,  8,  8,  2,
  2,  8,  2,  2,  2,  2,  2,  8,  2,  2,  2,  2,  2,  2,  2,  8,  2,
  2,  8,  2,  0,  0,  0,  2,  8,  2,  0,  0,  0,  0,  0,  2,  8,  2,
  2,  8,  2,  0,  0,  0,  2,  8,  2,  0,  0,  0,  0,  0,  2,  8,  2,
  2,  8,  2,  2,  2,  2,  2,  8,  2,  2,  2,  2,  2,  2,  2,  8,  2,
  2,  8,  8,  8,  8,  2,  2,  8,  8,  8,  8,  8,  8,  8,  8,  8,  2,
  2,  2,  2,  2,  8,  2,  8,  8,  2,  8,  2,  2,  2,  2,  2,  2,  2,
  0,  0,  0,  2,  8,  2,  8,  2,  2,  8,  8,  2,  0,  0,  0,  0,  0,
  0,  0,  0,  2,  8,  2,  8,  2,  2,  2,  8,  2,  0,  0,  0,  0,  0,
  2,  2,  2,  2,  8,  2,  8,  2,  0,  2,  8,  2,  2,  2,  2,  2,  2,
  8,  8,  8,  8,  8,  2,  8,  2,  0,  2,  8,  2,  8,  8,  8,  8,  8,
  2,  2,  2,  2,  2,  2,  8,  2,  0,  2,  8,  2,  8,  2,  2,  2,  2,
  0,  0,  0,  0,  0,  2,  8,  2,  2,  2,  8,  2,  8,  2,  0,  0,  0,
  0,  0,  0,  0,  0,  2,  8,  8,  2,  2,  8,  2,  8,  2,  0,  0,  0,
  2,  2,  2,  2,  2,  2,  2,  8,  2,  8,  8,  2,  8,  2,  2,  2,  2,
  2,  8,  8,  8,  8,  8,  8,  8,  8,  8,  2,  2,  8,  8,  8,  8,  2,
  2,  8,  2,  2,  2,  2,  2,  2,  2,  8,  2,  2,  2,  2,  2,  8,  2,
  2,  8,  2,  0,  0,  0,  0,  0,  2,  8,  2,  0,  0,  0,  2,  8,  2,
  2,  8,  2,  0,  0,  0,  0,  0,  2,  8,  2,  0,  0,  0,  2,  8,  2,
  2,  8,  2,  2,  2,  2,  2,  2,  2,  8,  2,  2,  2,  2,  2,  8,  2,
  2,  8,  8,  8,  8,  8,  8,  8,  2,  8,  8,  8,  8,  8,  8,  8,  2,
  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2
};

uint8_t wall2[1] =
{
  2
};

int r_wall_num = 0;
int r_wall2_num = 0;
int l_wall_num = 0;
int l_wall2_num = 0;

int R_Mid_j = 0;
int L_Mid_j = 0;
int Front_j = 0;

int R_Check = 0;
int L_Check = 0;
int f_check = 1;

String c_way = "";
String c_way2 = "";

uint8_t intro_Count = 1;
uint8_t r_check = 0;
uint8_t l_check = 0;

uint8_t R_intro_check = 1;
uint8_t R_intro_check1 = 20;
uint8_t R_intro_check2 = 1;
uint8_t R_intro_check3= 1;

uint8_t L_intro_check = 1;
uint8_t L_intro_check1 = 20;
uint8_t L_intro_check2 = 1;
uint8_t L_intro_check3= 1;

int R_intro_check0 = 612;
int R_intro_check44 = 34;
int R_intro_check55 = 17;

int L_intro_check0 = 612;
int L_intro_check44 = 34;
int L_intro_check55 = 17;


// Map변경
uint8_t stage = 1;
uint8_t stage2 = 1;

// LED배열
int sLEDs[408];

//적외선 센서 상,하,좌,우
byte pinNum[8] = {A0, A1, A3, A4, A8, A9, A11, A12};

//적외선 센서 거리값 초기화
int distance1[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// LED Strip 선언
LPD8806 Strip_Mid = LPD8806(408, 37, 39);
LPD8806 Strip_Mid2 = LPD8806(408, 40, 42);
LPD8806 Strip_Front = LPD8806(24, 46, 48);
LPD8806 Strip_Front2 = LPD8806(24, 45, 47);
LPD8806 Strip_End = LPD8806(24, 32, 34);
LPD8806 Strip_End2 = LPD8806(24, 36, 38);

ThreadController PhaseMain = ThreadController();
ThreadController Startintro = ThreadController();
ThreadController RCheck = ThreadController();
ThreadController LCheck = ThreadController();

Thread Thread_r_distance = Thread();
Thread Thread_l_distance = Thread();
Thread Thread_r_setMove = Thread();
Thread Thread_l_setMove = Thread();

Thread Thread_r_move_pacman = Thread();
Thread Thread_l_move_pacman = Thread();
Thread Thread_A_Front_Rainbow = Thread();

Thread Thread_R_Mid_Rainbow = Thread();
Thread Thread_L_Mid_Rainbow = Thread();

Thread Thread_R_Finish = Thread();
Thread Thread_L_Finish = Thread();
Thread Thread_R_Finish2 = Thread();
Thread Thread_L_Finish2 = Thread();

Thread ReceiveDT = Thread();
Thread ReceiveDT_Byte = Thread();
Thread PostData_R = Thread();
Thread PostData_L = Thread();

//와이파이 설정부분(시작)
char ssid[] = "arirang";  // your network SSID (name)
char pass[] = "12345670";        // your network password

WiFiClient client;
WiFiClient client0;
WiFiClient client1;
WiFiClient client2;

int status = WL_IDLE_STATUS;
char server[] = "www.recycup.com";

String yourdatacolumn = "yourdata=";
String yourdata;
String PostValue_L;
String PostValue_R;

char onoff = 1;
char chksb = 0;
bool complete;

char sr_1[4];
char sr_2[4];
char sr_3[4];
char sr_4[4];
char sl_1[4];
char sl_2[4];
char sl_3[4];
char sl_4[4];

int r_1 = 0;
int r_2 = 0;
int r_3 = 0;
int r_4 = 0;
int l_1 = 0;
int l_2 = 0;
int l_3 = 0;
int l_4 = 0;

//와이파이 설정부분(끝)

void setup()
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif

  //출력용 시리얼 초기화
  Serial.begin(9600);
  Serial.println("ready0");
  while ( status != WL_CONNECTED)
  {
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  
  status = WL_IDLE_STATUS;
  yourdata = "onoff=1";
  Serial.println("ready");
  
  if (client.connect(server, 80))
  {
    client.println("POST /insert_mysql0.php HTTP/1.1");
    client.println("Host: www.recycup.com");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(yourdata.length());
    client.println();
    client.println(yourdata);
    Serial.println("ok");
  } 
  else 
  {
    client.stop();
    Serial.println("error");
  }

  // Start up the LED strip
  Strip_Mid.begin();
  Strip_Mid2.begin();
  Strip_Front.begin();
  Strip_Front2.begin();
  Strip_End.begin();
  Strip_End2.begin();

  // Update the strip, to start they are all 'off'
  Strip_Mid.show();
  Strip_Mid2.show();
  Strip_Front.show();
  Strip_Front2.show();
  Strip_End.show();
  Strip_End2.show();

  //8카운팅
  var_refresh();

  //셋팅
  setLed();

  //R 미드 인트로
  Thread_R_Mid_Rainbow.onRun(R_Mid_Rainbow);
  Thread_R_Mid_Rainbow.setInterval(5);

  //L 미드 인트로
  Thread_L_Mid_Rainbow.onRun(L_Mid_Rainbow);
  Thread_L_Mid_Rainbow.setInterval(5);

  //아크릴 점멸
  Thread_A_Front_Rainbow.onRun(A_Front_Rainbow);
  Thread_A_Front_Rainbow.setInterval(5);
  
  //인트로
  Startintro.add(&Thread_R_Mid_Rainbow);
  Startintro.add(&Thread_L_Mid_Rainbow);

  //체크세팅
  Thread_r_setMove.onRun(r_setMove);
  Thread_r_setMove.setInterval(11);

  Thread_l_setMove.onRun(l_setMove);
  Thread_l_setMove.setInterval(13);

  RCheck.add(&Thread_r_setMove);
  LCheck.add(&Thread_l_setMove);

  //팩맨움직이기
  Thread_r_move_pacman.onRun(r_move_pacman);
  Thread_r_move_pacman.setInterval(80);
  
  Thread_l_move_pacman.onRun(l_move_pacman);
  Thread_l_move_pacman.setInterval(80);

  //전원 데이터 받기
  ReceiveDT.onRun(receiveData);
  ReceiveDT.setInterval(7000);

  ReceiveDT_Byte.onRun(receiveData_Byte);
  ReceiveDT_Byte.setInterval(1);

  //데이터 보내기
  PostData_R.onRun(httpRequest_R);
  PostData_R.setInterval(5000);

  PostData_L.onRun(httpRequest_L);
  PostData_L.setInterval(150);

  //시작 스레드 추가
  PhaseMain.add(&Thread_A_Front_Rainbow);
  PhaseMain.add(&PostData_R);
  PhaseMain.add(&ReceiveDT);
  PhaseMain.add(&ReceiveDT_Byte);
  PhaseMain.add(&Startintro);
}

void loop()
{
  PhaseMain.run();
}

void receiveData_Byte()
{
  if(client0.available())
  {
    complete = client0.peek() == '#';
    //client0.read();
    Serial.println(char(client0.read()));
   
    if(complete == true)
    {
      //client0.read();
      Serial.println(char(client0.read()));
      
      onoff = char(client0.read());
      
  
      if(onoff == '2')
      {
        for (int i = 0; i < Strip_Mid.numPixels(); i++)
        {
          Strip_Mid.setPixelColor(i, 0);
          Strip_Mid2.setPixelColor(i, 0);
        }
      
        for (int i = 0; i < Strip_Front.numPixels(); i++)
        {
          Strip_Front.setPixelColor(i, 0);
          Strip_Front2.setPixelColor(i, 0);
          
          Strip_End.setPixelColor(i, 0);
          Strip_End2.setPixelColor(i, 0);
        }
        
        Strip_Mid.show();
        Strip_Mid2.show();
        Strip_Front.show();
        Strip_Front2.show();
        Strip_End.show();
        Strip_End2.show();
  
        PhaseMain.clear();
        PhaseMain.add(&ReceiveDT);
        PhaseMain.add(&ReceiveDT_Byte);
        
        r_1=0;
        r_2=0;
        r_3=0;
        r_4=0;
        l_1=0;
        l_2=0;
        l_3=0;
        l_4=0;
        chksb = '1';
        complete = false;
        client0.flush();
        Serial.println("off");
      }
      else if(onoff == '1' && chksb == '1')
      {
        chksb = '0';
        
        Startintro.add(&Thread_R_Mid_Rainbow);
        Startintro.add(&Thread_L_Mid_Rainbow);
            
        PhaseMain.add(&Thread_A_Front_Rainbow);
        PhaseMain.add(&PostData_R);
        PhaseMain.add(&ReceiveDT);
        PhaseMain.add(&ReceiveDT_Byte);
        PhaseMain.add(&Startintro);
  
        complete = false;
        client0.flush();
        Serial.println("on");
      }
      else
      {
        client0.flush();
      }
    }
  }
}

void receiveData()
{
  client0.stop();
  Serial.println("recieve");
  
  if (client0.connect(server, 80))
  {
    client0.println("GET /receive_mysql.php HTTP/1.1");
    client0.println("Host: www.recycup.com");
    client0.println("User-Agent: Arduino/1.0");
    client0.println("Connection: close");
    client0.println("Content-Type: application/x-www-form-urlencoded;");
    client0.println("Content-Length: 0");
    client0.println();
  }
}

void httpRequest_R()
{
  itoa(r_1,sr_1,10);
  itoa(r_2,sr_2,10);
  itoa(r_3,sr_3,10);
  itoa(r_4,sr_4,10);
  itoa(l_1,sl_1,10);
  itoa(l_2,sl_2,10);
  itoa(l_3,sl_3,10);
  itoa(l_4,sl_4,10);

  Serial.println(sr_1);
  Serial.println(sr_2);
  Serial.println(sr_3);
  Serial.println(sr_4);
  Serial.println(sl_1);
  Serial.println(sl_2);
  Serial.println(sl_3);
  Serial.println(sl_4);
  PostValue_R = "r_1=0&r_2=0&r_3=0&r_4=0&l_1=0&l_2=1&l_3=0&l_4=0";
  client1.stop();
  
  if (client1.connect(server, 80))
  {
    client1.println("POST /insert_mysql1.php HTTP/1.1");
    client1.println("Host: www.recycup.com");
    client1.println("User-Agent: Arduino/1.0");
    client1.println("Connection: close");
    client1.println("Content-Type: application/x-www-form-urlencoded;");
    client1.print("Content-Length: ");
    client1.println(PostValue_R.length());
    client1.println();
    client1.print("r_1=");
    client1.print(sr_1);
    client1.print("&r_2=");
    client1.print(sr_2);
    client1.print("&r_3=");
    client1.print(sr_3);
    client1.print("&r_4=");
    client1.print(sr_4);

    client1.print("&l_1=");
    client1.print(sl_1);
    client1.print("&l_2=");
    client1.print(sl_2);
    client1.print("&l_3=");
    client1.print(sl_3);
    client1.print("&l_4=");
    client1.println(sl_4);
    
    r_1=0;
    r_2=0;
    r_3=0;
    r_4=0;
    l_1=0;
    l_2=0;
    l_3=0;
    l_4=0;
    Serial.println("Rok");
  } 
  else
  {
    client1.connect(server, 80);
    Serial.println("R22");
  }
}

void httpRequest_L()
{
  if (client2.connect(server, 80))
  {
    client2.println("POST /insert_mysql2.php HTTP/1.1");
    client2.println("Host: www.recycup.com");
    client2.println("User-Agent: Arduino/1.0");
    client2.println("Connection: close");
    client2.println("Content-Type: application/x-www-form-urlencoded;");
    client2.print("Content-Length: ");
    client2.println(PostValue_L.length());
    client2.println();
    client2.println(PostValue_L);
    PhaseMain.remove(&PostData_L);
    Serial.println("Lok");
  } 
  else
  {
    client2.connect(server, 80);
    PhaseMain.remove(&PostData_L);
    Serial.println("L22");
  }
}

void var_refresh()
{
  for (int i = 0; i < 408; i++)
  {
    if (wall[i] == 8)
    {
      r_wall_num = r_wall_num + 1;
      l_wall_num = l_wall_num + 1;
    }
    if (wall2[i] == 8)
    {
      r_wall2_num = r_wall2_num + 1;
      l_wall2_num = l_wall2_num + 1;
    }
  }
}

void r_move_pacman()
{
  int pac = 0;
  int rpac = 0;

  for (int i = 0; i < 408; i++)
  {
    if (pacman[i] == 1)
    {
      rpac = i;
      pac = i;
    }
  }

  if (c_way == "up")
  {
    pac = pac - 17;
    r_Move_Led(pac, rpac);
  }
  else if (c_way == "down")
  {
    pac = pac + 17;
    r_Move_Led(pac, rpac);
  }
  else if (c_way == "left")
  {
    pac = pac + 1;
    r_Move_Led(pac, rpac);
  }
  else if (c_way == "right")
  {
    pac = pac - 1;
    r_Move_Led(pac, rpac);
  }
}

void l_move_pacman()
{
  int pac = 0;
  int rpac = 0;
  for (int i = 0; i < 408; i++)
  {
    if (pacman2[i] == 1)
    {
      rpac = i;
      pac = i;
    }
  }

  if (c_way2 == "up2")
  {
    pac = pac - 17;
    l_Move_Led(pac, rpac);
  }
  else if (c_way2 == "down2")
  {
    pac = pac + 17;
    l_Move_Led(pac, rpac);
  }
  else if (c_way2 == "left2")
  {
    pac = pac + 1;
    l_Move_Led(pac, rpac);
  }
  else if (c_way2 == "right2")
  {
    pac = pac - 1;
    l_Move_Led(pac, rpac);
  }
}

//거리측정
void r_distance()
{
  for (int8_t i = 0; i < 4; i++)
  {
    int data = analogRead(pinNum[i]);
    int volt = map(data, 0, 1023, 0, 5000);
    distance1[i] = (21.61 / (volt - 0.1696)) * 1000;
  }
}

void l_distance()
{
  for (int8_t i = 4; i < 8; i++)
  {
    int data = analogRead(pinNum[i]);
    int volt = map(data, 0, 1023, 0, 5000);
    distance1[i] = (21.61 / (volt - 0.1696)) * 1000;
  }
}

void r_setMove()
{
  r_distance();

  if (distance1[0] < 6)
  {
    r_check = 1;
    r_chk();
    c_way = "up";
    PhaseMain.add(&Thread_r_move_pacman);
    PhaseMain.remove(&RCheck); 
  }
  if (distance1[1] < 6)
  {
    r_check = 1;
    r_chk();
    c_way = "down";
    PhaseMain.add(&Thread_r_move_pacman);
    PhaseMain.remove(&RCheck);
  }
  if (distance1[2] < 6)
  {
    r_check = 1;
    r_chk();
    c_way = "right";
    PhaseMain.add(&Thread_r_move_pacman);
    PhaseMain.remove(&RCheck);
  }
  if (distance1[3] < 6)
  { 
    r_check = 1;
    r_chk();
    c_way = "left";
    PhaseMain.add(&Thread_r_move_pacman);
    PhaseMain.remove(&RCheck);
  }
}


void r_chk()
{
  if(r_check == 1)
  {
    Thread_r_move_pacman.setInterval(300);
    r_check = 0;
  }
  else
  {
    Thread_r_move_pacman.setInterval(20);
  }
}

void l_chk()
{
  if(l_check == 1)
  {
    Thread_l_move_pacman.setInterval(300);
    l_check = 0;
  }
  else
  {
    Thread_l_move_pacman.setInterval(20);
  }
}

void l_setMove()
{
  l_chk();
  l_distance();

  if (distance1[4] < 6)
  {
    l_check = 1;
    l_chk();
     c_way2 = "up2";
    PhaseMain.add(&Thread_l_move_pacman);
    PhaseMain.remove(&LCheck);
  }
  if (distance1[5] < 6)
  {
    l_check = 1;
    l_chk();
    c_way2 = "down2";
    PhaseMain.add(&Thread_l_move_pacman);
    PhaseMain.remove(&LCheck);
  }
  if (distance1[6] < 6)
  {
    l_check = 1;
    l_chk();
    c_way2 = "right2";
    PhaseMain.add(&Thread_l_move_pacman);
    PhaseMain.remove(&LCheck);
  }
  if (distance1[7] < 6)
  {
    l_check = 1;
    l_chk();
    c_way2 = "left2";
    PhaseMain.add(&Thread_l_move_pacman);
    PhaseMain.remove(&LCheck);
  }
}

void R_Mid_Rainbow()
{
  for (int i = 0; i < Strip_Mid.numPixels(); i++)
  {
    Strip_Mid.setPixelColor(i, Wheel( (i + R_Mid_j) % 384, Strip_Mid));
  }

  Strip_Mid.show();

  if (R_Mid_j == 383)
  {
    R_Mid_j = 0;
    SetMap(wall, pacman);
    PhaseMain.add(&RCheck);
    Startintro.remove(&Thread_R_Mid_Rainbow);
  }
  else
  {
    R_Mid_j = R_Mid_j + 1;
  }
}

void L_Mid_Rainbow()
{
  for (int i = 0; i < Strip_Mid2.numPixels(); i++)
  {
    Strip_Mid2.setPixelColor(i, Wheel( (i + L_Mid_j) % 384, Strip_Mid2));
  }

  Strip_Mid2.show();

  if (L_Mid_j == 383)
  {
    L_Mid_j = 0;
    SetMap2(wall, pacman2);
    PhaseMain.add(&LCheck);
    Startintro.remove(&Thread_L_Mid_Rainbow);
  }
  else
  {
    L_Mid_j = L_Mid_j + 1;
  }
}

void A_Front_Rainbow()
{
  for (int i = 0; i < Strip_Front.numPixels(); i++)
  {
    Strip_Front.setPixelColor(i, Wheel( (i + Front_j) % 384, Strip_Front));
    Strip_Front2.setPixelColor(i, Wheel( (i + Front_j) % 384, Strip_Front2));
    
    Strip_End.setPixelColor(i, Wheel( (i + Front_j) % 384, Strip_End));
    Strip_End2.setPixelColor(i, Wheel( (i + Front_j) % 384, Strip_End2));
  }

  Strip_Front.show();
  Strip_Front2.show();
  Strip_End.show();
  Strip_End2.show();


  if (Front_j == 383)
  {
    Front_j = 0;
  }
  else
  {
    Front_j = Front_j + 1;
  }
}

//게임 맵 초기화
void SetMap(uint8_t cWall[], uint8_t cPacman[])
{
  for (int i = 0; i < 408; i++)
  {
    if (cWall[i] == 2)
    {
      Strip_Mid.setPixelColor(sLEDs[i], Strip_Mid.Color(0, 0, 255));
    }
    if (cWall[i] == 8)
    {
      Strip_Mid.setPixelColor(sLEDs[i], Strip_Mid.Color(255, 190, 0));
    }
    if (cWall[i] == 0)
    {
      Strip_Mid.setPixelColor(sLEDs[i], 0);
    }
    if (cPacman[i]  == 1)
    {
      Strip_Mid.setPixelColor(sLEDs[i], Strip_Mid.Color(255, 0, 0));
    }
  }
  Strip_Mid.show();
}

void SetMap2(uint8_t cWall[], uint8_t cPacman[])
{
  for (int i = 0; i < 408; i++)
  {
    if (cWall[i] == 2)
    {
      Strip_Mid2.setPixelColor(sLEDs[i], Strip_Mid2.Color(0, 0, 255));
    }
    if (cWall[i] == 8)
    {
      Strip_Mid2.setPixelColor(sLEDs[i], Strip_Mid2.Color(255, 190, 0));
    }
    if (cWall[i] == 0)
    {
      Strip_Mid2.setPixelColor(sLEDs[i], 0);
    }
    if (cPacman[i] == 1)
    {
      Strip_Mid2.setPixelColor(sLEDs[i], Strip_Mid2.Color(255, 0, 0));
    }
  }
  Strip_Mid2.show();
}

//LED_Mid 배열 재배치
void setLed()
{
  int z = -25;
  int a = -25;
  int b = 0;
  int c = 1;
  int d = 48;
  int e = 1;

  for (int i = 0; i < 408; i++)
  {
    if ( c % 2 == 1)
    {
      a = a + d;
      sLEDs[i] = a;
    }
    else
    {
      b = a + e;
      sLEDs[i] = b;
    }

    if ( c == 17)
    {
      c = 1;
      z = z - 1;
      a = z;
      e = e + 2;

    }
    else
    {
      c = c + 1;
    }
  }
}

uint32_t Wheel(uint16_t WheelPos, LPD8806 WheelStrip)
{
  byte r, g, b;
  switch (WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break;
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break;
    case 2:
      b = 127 - WheelPos % 128;  //blue down
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break;
  }
  return (WheelStrip.Color(r, g, b));
}

void r_Move_Led(int pac1, int rpac1)
{
  if (pac1 >= 0 && pac1 < 408)
  {
    if (stage == 1)
    {
      if (wall[pac1] == 8)
      {
        Strip_Mid.setPixelColor(sLEDs[rpac1], 0);
        Strip_Mid.setPixelColor(sLEDs[pac1], Strip_Mid.Color(255, 0, 0));
        pacman[rpac1] = 8;
        pacman[pac1] = 1;
        R_Check = 0;

        for (int i = 0; i < 408; i++)
        {
          if (pacman[i] == 8)
          {
            R_Check = R_Check + 1;
          }
        }
        R_Check = R_Check + 1;
        Strip_Mid.show();

        if (r_wall_num == R_Check)
        {
          for (int i = 0; i < 408; i++)
          {
            pacman[i] = 0;
          }
          R_Check = 1;
          pacman[18] = 1;
          stage = 1;
          Startintro.add(&Thread_R_Finish2);
          PhaseMain.remove(&Thread_r_move_pacman);
        }
      }
      else
      {
        PhaseMain.add(&RCheck);
        PhaseMain.remove(&Thread_r_move_pacman);
        if(c_way == "up")
          {
            r_1 = r_1 + 1;
          }
          else if( c_way =="down")
          {
            r_2 = r_2 + 1;
          }
          else if( c_way == "right")
          {
             r_3 = r_3 + 1;
          }
          else if( c_way == "left")
          {
             r_4 = r_4 + 1;
          }
      }
    }
    else if (stage == 2)
    {
      if (wall2[pac1] == 8)
      {
        Strip_Mid.setPixelColor(sLEDs[rpac1], 0);
        Strip_Mid.setPixelColor(sLEDs[pac1], Strip_Mid.Color(255, 0, 0));
        pacman[rpac1] = 8;
        pacman[pac1] = 1;
        R_Check = 0;

        for (int i = 0; i < 408; i++)
        {
          if (pacman[i] == 8)
          {
            R_Check = R_Check + 1;
          }
        }
        R_Check = R_Check + 1;
        Strip_Mid.show();

        if (r_wall2_num == R_Check)
        {
          for (int i = 0; i < 408; i++)
          {
            pacman[i] = 0;
          }
          R_Check = 1;
          pacman[18] = 1;
          stage = 1;
          Startintro.add(&Thread_R_Finish2);
          PhaseMain.remove(&Thread_r_move_pacman);
        }
      }
      else
      {
        PhaseMain.add(&RCheck);
        PhaseMain.remove(&Thread_r_move_pacman);
        if(c_way == "up")
          {
            r_1 = r_1 + 1;
          }
          else if( c_way =="down")
          {
            r_2 = r_2 + 1;
          }
          else if( c_way == "right")
          {
             r_3 = r_3 + 1;
          }
          else if( c_way == "left")
          {
             r_4 = r_4 + 1;
          }
      }
    }
  }
  else
  {
    PhaseMain.add(&RCheck);
    PhaseMain.remove(&Thread_r_move_pacman);
  }
}

void l_Move_Led(int pac1, int rpac1)
{
  if (pac1 >= 0 && pac1 < 408)
  {
    if (stage2 == 1)
    {
      if (wall[pac1] == 8)
      {
        Strip_Mid2.setPixelColor(sLEDs[rpac1], 0);
        Strip_Mid2.setPixelColor(sLEDs[pac1], Strip_Mid2.Color(255, 0, 0));
        pacman2[rpac1] = 8;
        pacman2[pac1] = 1;
        L_Check = 0;
        for (int i = 0; i < 408; i++)
        {
          if (pacman2[i] == 8)
          {
            L_Check = L_Check + 1;
          }
        }
        L_Check = L_Check + 1;
        Strip_Mid2.show();

        if (l_wall_num == L_Check)
        {
          for (int i = 0; i < 408; i++)
          {
            pacman2[i] = 0;
          }
          L_Check = 1;
          pacman2[18] = 1;
          stage2 = 1;
          Startintro.add(&Thread_L_Finish2);
          PhaseMain.remove(&Thread_l_move_pacman);
        }
      }
      else
      {
        PhaseMain.add(&LCheck);
        PhaseMain.remove(&Thread_l_move_pacman);
        if(c_way2 == "up2")
          {
            l_1 = l_1 + 1;
          }
          else if( c_way2 =="down2")
          {
            l_2 = l_2 + 1;
          }
          else if( c_way2 == "right2")
          {
             l_3 = l_3 + 1;
          }
          else if( c_way2 == "left2")
          {
             l_4 = l_4 + 1;
          }
      }
    }
    else if (stage2 == 2)
    {
      if (wall2[pac1] == 8)
      {
        Strip_Mid2.setPixelColor(sLEDs[rpac1], 0);
        Strip_Mid2.setPixelColor(sLEDs[pac1], Strip_Mid2.Color(255, 0, 0));
        pacman2[rpac1] = 8;
        pacman2[pac1] = 1;
        L_Check = 0;
        for (int i = 0; i < 408; i++)
        {
          if (pacman2[i] == 8)
          {
            L_Check = L_Check + 1;
          }
        }
        L_Check = L_Check + 1;
        Strip_Mid.show();

        if (l_wall_num == L_Check)
        {
          for (int i = 0; i < 408; i++)
          {
            pacman2[i] = 0;
          }
          L_Check = 1;
          pacman2[18] = 1;
          stage2 = 1;
          Startintro.add(&Thread_L_Finish2);
          PhaseMain.remove(&Thread_l_move_pacman);
         
      }
      else
      {
        PhaseMain.add(&LCheck);
        PhaseMain.remove(&Thread_l_move_pacman);
        if(c_way2 == "up2")
          {
            l_1 = l_1 + 1;
          }
          else if( c_way2 =="down2")
          {
            l_2 = l_2 + 1;
          }
          else if( c_way2 == "right2")
          {
             l_3 = l_3 + 1;
          }
          else if( c_way2 == "left2")
          {
             l_4 = l_4 + 1;
          }
      }
      }
    }
  }
  else
  {
    PhaseMain.add(&LCheck);
    PhaseMain.remove(&Thread_l_move_pacman);
  }
}
