#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// ===================== SERVO CODE =====================

Servo servo_14; // Upper right [paw]
Servo servo_12; // Upper right [arm]
Servo servo_13; // Lower right [arm]
Servo servo_15; // Lower right [paw]
Servo servo_16; // Upper left [paw]
Servo servo_5;  // Upper left [arm]
Servo servo_4;  // Lower left [arm]
Servo servo_2;  // Lower left [paw]

String item;

const int PWMRES_Min = 1;
const int PWMRES_Max = 180;
const int ALLMATRIX = 9;
const int ALLSERVOS = 8;
const int SERVOMIN = 400;
const int SERVOMAX = 2400;

int Running_Servo_POS[ALLMATRIX];

const int BASEDELAYTIME = 10;

// =====================================================
// SPEED SETTING
// =====================================================
const int SPEED_PERCENT = 80;


// ===================== SERVO POSITIONS =====================

const int Servo_Act_0[] PROGMEM = {
  90, 90, 90, 90, 90, 90, 90, 90, 500
};

const int Servo_Act_1[] PROGMEM = {
  60, 90, 90, 120, 120, 90, 90, 60, 500
};


// ===================== STANDBY =====================

const int Servo_Prg_1_Step = 2;

const int Servo_Prg_1[][ALLMATRIX] PROGMEM = {
  {90,90,90,90,90,90,90,90,500},
  {60,90,90,120,120,90,90,60,500},
};


// ===================== FORWARD =====================

const int Servo_Prg_2_Step = 11;

const int Servo_Prg_2[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,200},
  {90,90,90,110,110,90,90,90,200},
  {90,120,90,110,110,90,60,90,200},
  {70,120,90,110,110,90,60,70,200},
  {70,120,90,90,90,90,60,70,200},
  {70,90,90,90,90,90,90,70,200},
  {70,90,120,90,90,60,90,70,200},
  {70,90,120,110,110,60,90,70,200},
  {90,90,120,110,110,60,90,90,200},
  {90,90,90,110,110,90,90,90,200},
  {70,90,90,110,110,90,90,70,200},
};


// ===================== BACKWARD =====================

const int Servo_Prg_3_Step = 11;

const int Servo_Prg_3[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,200},
  {90,90,90,110,110,90,90,90,200},
  {90,60,90,110,110,90,120,90,200},
  {70,60,90,110,110,90,120,70,200},
  {70,60,90,90,90,90,120,70,200},
  {70,90,90,90,90,90,90,70,200},
  {70,90,60,90,90,120,90,70,200},
  {70,90,60,110,110,120,90,70,200},
  {90,90,60,110,110,120,90,90,200},
  {90,90,90,110,110,90,90,90,200},
  {70,90,90,110,110,90,90,70,200},
};


// ===================== LEFT SHIFT =====================

const int Servo_Prg_4_Step = 11;

const int Servo_Prg_4[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,200},
  {70,90,90,90,90,90,90,70,200},
  {70,90,60,90,90,120,90,70,200},
  {70,90,60,110,110,120,90,70,200},
  {90,90,60,110,110,120,90,90,200},
  {90,90,90,110,110,90,90,90,200},
  {90,120,90,110,110,90,60,90,200},
  {70,120,90,110,110,90,60,70,200},
  {70,120,90,90,90,90,60,70,200},
  {70,90,90,90,90,90,90,70,200},
  {70,90,90,110,110,90,90,70,200},
};


// ===================== RIGHT SHIFT =====================

const int Servo_Prg_5_Step = 11;

const int Servo_Prg_5[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,200},
  {90,90,90,110,110,90,90,90,200},
  {90,60,90,110,110,90,120,90,200},
  {70,60,90,110,110,90,120,70,200},
  {70,60,90,90,90,90,120,70,200},
  {70,90,90,90,90,90,90,70,200},
  {70,90,120,90,90,60,90,70,200},
  {70,90,120,110,110,60,90,70,200},
  {90,90,120,110,110,60,90,90,200},
  {90,90,90,110,110,90,90,90,200},
  {70,90,90,110,110,90,90,70,200},
};


// ===================== TURN LEFT =====================

const int Servo_Prg_6_Step = 8;

const int Servo_Prg_6[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,200},
  {90,90,90,110,110,90,90,90,200},
  {90,135,90,110,110,90,135,90,200},
  {70,135,90,110,110,90,135,70,200},
  {70,135,90,90,90,90,135,70,200},
  {70,135,135,90,90,135,135,70,200},
  {70,135,135,110,110,135,135,70,200},
  {70,90,90,110,110,90,90,70,200},
};


// ===================== TURN RIGHT =====================

const int Servo_Prg_7_Step = 8;

const int Servo_Prg_7[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,200},
  {70,90,90,90,90,90,90,70,200},
  {70,90,45,90,90,45,90,70,200},
  {70,90,45,110,110,45,90,70,200},
  {90,90,45,110,110,45,90,90,200},
  {90,45,45,110,110,45,45,90,200},
  {70,45,45,110,110,45,45,70,200},
  {70,90,90,110,110,90,90,70,200},
};


// ===================== LIE =====================

const int Servo_Prg_8_Step = 1;

const int Servo_Prg_8[][ALLMATRIX] PROGMEM = {
  {110,90,90,70,70,90,90,110,500},
};


// ===================== SAY HI =====================

const int Servo_Prg_9_Step = 7;

const int Servo_Prg_9[][ALLMATRIX] PROGMEM = {
  {70,90,135,90,90,90,90,90,400},
  {170,90,135,90,90,90,90,90,400},
  {170,130,135,90,90,90,90,90,400},
  {170,50,135,90,90,90,90,90,400},
  {170,130,135,90,90,90,90,90,400},
  {170,90,135,90,90,90,90,90,400},
  {70,90,135,90,90,90,90,90,400},
};


// ===================== FIGHTING =====================

const int Servo_Prg_10_Step = 11;

const int Servo_Prg_10[][ALLMATRIX] PROGMEM = {
  {120,90,90,110,60,90,90,70,500},
  {120,70,70,110,60,70,70,70,500},
  {120,110,110,110,60,110,110,70,500},
  {120,70,70,110,60,70,70,70,500},
  {120,110,110,110,60,110,110,70,500},
  {70,90,90,70,110,90,90,110,500},
  {70,70,70,70,110,70,70,110,500},
  {70,110,110,70,110,110,110,110,500},
  {70,70,70,70,110,70,70,110,500},
  {70,110,110,70,110,110,110,110,500},
  {70,90,90,70,110,90,90,110,500},
};


// ===================== PUSH UP =====================

const int Servo_Prg_11_Step = 7;

const int Servo_Prg_11[][ALLMATRIX] PROGMEM = {
  {70,90,90,110,110,90,90,70,100},
  {90,90,90,90,90,90,90,90,600},
  {70,90,90,110,110,90,90,70,500},
  {90,90,90,90,90,90,90,100,700},
  {70,90,90,110,110,90,90,70,500},
  {90,90,90,90,90,90,90,100,800},
  {70,90,90,110,110,90,90,70,500},
};


// ===================== SLEEP =====================

const int Servo_Prg_12_Step = 2;

const int Servo_Prg_12[][ALLMATRIX] PROGMEM = {
  {30,90,90,150,150,90,90,30,500},
  {30,45,135,150,150,135,45,30,500},
};


// ===================== DANCE 1 =====================

const int Servo_Prg_13_Step = 10;

const int Servo_Prg_13[][ALLMATRIX] PROGMEM = {
  {90,90,90,90,90,90,90,90,400},
  {50,90,90,90,90,90,90,90,400},
  {90,90,90,130,90,90,90,90,400},
  {90,90,90,90,90,90,90,50,400},
  {90,90,90,90,130,90,90,90,400},
  {50,90,90,90,90,90,90,90,400},
  {90,90,90,130,90,90,90,90,400},
  {90,90,90,90,90,90,90,50,400},
  {90,90,90,90,130,90,90,90,400},
  {90,90,90,90,90,90,90,90,400},
};


// ===================== DANCE 2 =====================

const int Servo_Prg_14_Step = 9;

const int Servo_Prg_14[][ALLMATRIX] PROGMEM = {
  {70,45,135,110,110,135,45,70,400},
  {115,45,135,65,110,135,45,70,400},
  {70,45,135,110,65,135,45,115,400},
  {115,45,135,65,110,135,45,70,400},
  {70,45,135,110,65,135,45,115,400},
  {115,45,135,65,110,135,45,70,400},
  {70,45,135,110,65,135,45,115,400},
  {115,45,135,65,110,135,45,70,400},
  {75,45,135,105,110,135,45,70,400},
};


// ===================== DANCE 3 =====================

const int Servo_Prg_15_Step = 10;

const int Servo_Prg_15[][ALLMATRIX] PROGMEM = {
  {70,45,45,110,110,135,135,70,400},
  {110,45,45,60,70,135,135,70,400},
  {70,45,45,110,110,135,135,70,400},
  {110,45,45,110,70,135,135,120,400},
  {70,45,45,110,110,135,135,70,400},
  {110,45,45,60,70,135,135,70,400},
  {70,45,45,110,110,135,135,70,400},
  {110,45,45,110,70,135,135,120,400},
  {70,45,45,110,110,135,135,70,400},
  {70,90,90,110,110,90,90,70,400},
};


// =====================================================
// SERVO CONTROL FUNCTIONS
// =====================================================

void Set_PWM_to_Servo(int iServo, int iValue) {

  int NewPWM = map(
    iValue,
    PWMRES_Min,
    PWMRES_Max,
    SERVOMIN,
    SERVOMAX
  );

  if (iServo >= 7)
    servo_2.writeMicroseconds(NewPWM);

  else if (iServo >= 6)
    servo_4.writeMicroseconds(NewPWM);

  else if (iServo >= 5)
    servo_5.writeMicroseconds(NewPWM);

  else if (iServo >= 4)
    servo_16.writeMicroseconds(NewPWM);

  else if (iServo >= 3)
    servo_15.writeMicroseconds(NewPWM);

  else if (iServo >= 2)
    servo_13.writeMicroseconds(NewPWM);

  else if (iServo >= 1)
    servo_12.writeMicroseconds(NewPWM);

  else
    servo_14.writeMicroseconds(NewPWM);
}


void Servo_PROGRAM_Run(
  const int iMatrix[][ALLMATRIX],
  int iSteps
) {

  for (int MainLoopIndex = 0;
       MainLoopIndex < iSteps;
       MainLoopIndex++) {

    // Get original movement time
    int InterTotalTime =
      pgm_read_word(
        &(iMatrix[MainLoopIndex][ALLMATRIX - 1])
      );

    // ============================================
    // MODERATE SPEED INCREASE
    // 200ms becomes 160ms
    // 400ms becomes 320ms
    // 500ms becomes 400ms
    // ============================================

    InterTotalTime =
      InterTotalTime * SPEED_PERCENT / 100;

    int InterDelayCounter =
      InterTotalTime / BASEDELAYTIME;

    for (int InterStepLoop = 0;
         InterStepLoop < InterDelayCounter;
         InterStepLoop++) {

      for (int ServoIndex = 0;
           ServoIndex < ALLSERVOS;
           ServoIndex++) {

        int INT_TEMP_A =
          Running_Servo_POS[ServoIndex];

        int INT_TEMP_B =
          pgm_read_word(
            &(iMatrix[MainLoopIndex][ServoIndex])
          );

        int INT_TEMP_C;

        if (INT_TEMP_A == INT_TEMP_B) {

          INT_TEMP_C = INT_TEMP_B;

        }

        else if (INT_TEMP_A > INT_TEMP_B) {

          INT_TEMP_C =
            map(
              BASEDELAYTIME * InterStepLoop,
              0,
              InterTotalTime,
              0,
              INT_TEMP_A - INT_TEMP_B
            );

          if (INT_TEMP_A - INT_TEMP_C >= INT_TEMP_B) {

            Set_PWM_to_Servo(
              ServoIndex,
              INT_TEMP_A - INT_TEMP_C
            );

          }

        }

        else {

          INT_TEMP_C =
            map(
              BASEDELAYTIME * InterStepLoop,
              0,
              InterTotalTime,
              0,
              INT_TEMP_B - INT_TEMP_A
            );

          if (INT_TEMP_A + INT_TEMP_C <= INT_TEMP_B) {

            Set_PWM_to_Servo(
              ServoIndex,
              INT_TEMP_A + INT_TEMP_C
            );

          }

        }

      }

      delay(BASEDELAYTIME);

    }

    for (int Index = 0;
         Index < ALLMATRIX;
         Index++) {

      Running_Servo_POS[Index] =
        pgm_read_word(
          &(iMatrix[MainLoopIndex][Index])
        );

    }

  }
}


void Servo_PROGRAM_Zero() {

  for (int Index = 0;
       Index < ALLMATRIX;
       Index++) {

    Running_Servo_POS[Index] =
      pgm_read_word(&(Servo_Act_0[Index]));

  }

  for (int iServo = 0;
       iServo < ALLSERVOS;
       iServo++) {

    Set_PWM_to_Servo(
      iServo,
      Running_Servo_POS[iServo]
    );

    delay(10);
  }


  for (int Index = 0;
       Index < ALLMATRIX;
       Index++) {

    Running_Servo_POS[Index] =
      pgm_read_word(&(Servo_Act_1[Index]));

  }

  for (int iServo = 0;
       iServo < ALLSERVOS;
       iServo++) {

    Set_PWM_to_Servo(
      iServo,
      Running_Servo_POS[iServo]
    );

    delay(10);
  }

}


// ===================== MOVEMENT FUNCTIONS =====================

void standby() {
  Servo_PROGRAM_Run(
    Servo_Prg_1,
    Servo_Prg_1_Step
  );
}

void sleep() {
  Servo_PROGRAM_Run(
    Servo_Prg_1,
    Servo_Prg_1_Step
  );

  Servo_PROGRAM_Run(
    Servo_Prg_12,
    Servo_Prg_12_Step
  );
}

void lie() {
  Servo_PROGRAM_Run(
    Servo_Prg_8,
    Servo_Prg_8_Step
  );
}

void forward() {
  Servo_PROGRAM_Run(
    Servo_Prg_2,
    Servo_Prg_2_Step
  );
}

void back() {
  Servo_PROGRAM_Run(
    Servo_Prg_3,
    Servo_Prg_3_Step
  );
}

void turnleft() {
  Servo_PROGRAM_Run(
    Servo_Prg_6,
    Servo_Prg_6_Step
  );
}

void turnright() {
  Servo_PROGRAM_Run(
    Servo_Prg_7,
    Servo_Prg_7_Step
  );
}

void leftmove() {
  Servo_PROGRAM_Run(
    Servo_Prg_4,
    Servo_Prg_4_Step
  );
}

void rightmove() {
  Servo_PROGRAM_Run(
    Servo_Prg_5,
    Servo_Prg_5_Step
  );
}

void hello() {

  Servo_PROGRAM_Run(
    Servo_Prg_9,
    Servo_Prg_9_Step
  );

  Servo_PROGRAM_Run(
    Servo_Prg_1,
    Servo_Prg_1_Step
  );

}

void dance1() {
  Servo_PROGRAM_Run(
    Servo_Prg_13,
    Servo_Prg_13_Step
  );
}

void dance2() {
  Servo_PROGRAM_Run(
    Servo_Prg_14,
    Servo_Prg_14_Step
  );
}

void dance3() {
  Servo_PROGRAM_Run(
    Servo_Prg_15,
    Servo_Prg_15_Step
  );
}

void pushup() {
  Servo_PROGRAM_Run(
    Servo_Prg_11,
    Servo_Prg_11_Step
  );
}

void fighting() {
  Servo_PROGRAM_Run(
    Servo_Prg_10,
    Servo_Prg_10_Step
  );
}


// =====================================================
// ESP8266 WIFI CONTROL
// =====================================================

const char* ssid = "Bionic Spider";
const char* password = "";

WiFiServer server(100);
WiFiClient client;

String sendBuff;

byte RX_package[17] = {0};

byte callback_forward_package[5] =
  {0xff,0x55,0x02,0x01,0x01};

byte callback_back_package[5] =
  {0xff,0x55,0x02,0x01,0x02};

byte callback_leftmove_package[5] =
  {0xff,0x55,0x02,0x01,0x03};

byte callback_rightmove_package[5] =
  {0xff,0x55,0x02,0x01,0x04};

byte callback_turnleft_package[5] =
  {0xff,0x55,0x02,0x01,0x05};

byte callback_turnright_package[5] =
  {0xff,0x55,0x02,0x01,0x06};

byte callback_standby_package[5] =
  {0xff,0x55,0x02,0x01,0x07};

byte callback_sleep_package[5] =
  {0xff,0x55,0x02,0x01,0x08};

byte callback_lie_package[5] =
  {0xff,0x55,0x02,0x01,0x09};

byte callback_hello_package[5] =
  {0xff,0x55,0x02,0x01,0x0a};

byte callback_pushup_package[5] =
  {0xff,0x55,0x02,0x01,0x0b};

byte callback_fighting_package[5] =
  {0xff,0x55,0x02,0x01,0x0c};

byte callback_dance1_package[5] =
  {0xff,0x55,0x02,0x01,0x0d};

byte callback_dance2_package[5] =
  {0xff,0x55,0x02,0x01,0x0e};

byte callback_dance3_package[5] =
  {0xff,0x55,0x02,0x01,0x0f};


byte Serial_package[5] = {0};

byte dataLen;
byte index_a = 0;

char buffer[52];

unsigned char prevc = 0;

bool isStart = false;
bool ED_client = true;
bool WA_en = false;
bool st = false;


// ===================== COMMANDS =====================

#define CMD_RUN 1
#define CMD_daiji 3
#define CMD_jiaozun 4
#define CMD_suijiao 5
#define CMD_padi 6
#define CMD_dazaohu 7
#define CMD_fuwoceng 8
#define CMD_zandou 9
#define CMD_dance1 10
#define CMD_dance2 11
#define CMD_dance3 12


unsigned char readBuffer(int index_r) {

  return buffer[index_r];

}


void writeBuffer(
  int index_w,
  unsigned char c
) {

  buffer[index_w] = c;

}


// ===================== RUN MODULE =====================

void runModule(int device) {

  switch (device) {

    case 0x0C: {

      int val = readBuffer(12);

      switch (val) {

        case 0x01:
          forward();
          client.write(
            callback_forward_package,
            5
          );
          break;

        case 0x02:
          back();
          client.write(
            callback_back_package,
            5
          );
          break;

        case 0x03:
          leftmove();
          client.write(
            callback_leftmove_package,
            5
          );
          break;

        case 0x04:
          rightmove();
          client.write(
            callback_rightmove_package,
            5
          );
          break;

        case 0x05:
          turnleft();
          client.write(
            callback_turnleft_package,
            5
          );
          break;

        case 0x06:
          turnright();
          client.write(
            callback_turnright_package,
            5
          );
          break;

        default:
          break;

      }

    }
    break;

  }

}


// ===================== PARSE DATA =====================

void parseData() {

  isStart = false;

  int action = readBuffer(9);
  int device = readBuffer(10);

  switch (action) {

    case CMD_RUN:

      runModule(device);

      break;


    case CMD_daiji:

      standby();

      client.write(
        callback_standby_package,
        5
      );

      break;


    case CMD_jiaozun:

      break;


    case CMD_suijiao:

      sleep();

      client.write(
        callback_sleep_package,
        5
      );

      break;


    case CMD_padi:

      lie();

      client.write(
        callback_lie_package,
        5
      );

      break;


    case CMD_dazaohu:

      hello();

      client.write(
        callback_hello_package,
        5
      );

      break;


    case CMD_fuwoceng:

      pushup();

      client.write(
        callback_pushup_package,
        5
      );

      break;


    case CMD_zandou:

      fighting();

      client.write(
        callback_fighting_package,
        5
      );

      break;


    case CMD_dance1:

      dance1();

      client.write(
        callback_dance1_package,
        5
      );

      break;


    case CMD_dance2:

      dance2();

      client.write(
        callback_dance2_package,
        5
      );

      break;


    case CMD_dance3:

      dance3();

      client.write(
        callback_dance3_package,
        5
      );

      break;

  }

}


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.setTimeout(10);
  Serial.begin(115200);


  // Create WiFi Access Point

  WiFi.mode(WIFI_AP);

  WiFi.softAP(
    ssid,
    password,
    5
  );

  server.begin();

  delay(100);


  // Attach all servos

  servo_14.attach(
    14,
    SERVOMIN,
    SERVOMAX
  );

  servo_12.attach(
    12,
    SERVOMIN,
    SERVOMAX
  );

  servo_13.attach(
    13,
    SERVOMIN,
    SERVOMAX
  );

  servo_15.attach(
    15,
    SERVOMIN,
    SERVOMAX
  );

  servo_16.attach(
    16,
    SERVOMIN,
    SERVOMAX
  );

  servo_5.attach(
    5,
    SERVOMIN,
    SERVOMAX
  );

  servo_4.attach(
    4,
    SERVOMIN,
    SERVOMAX
  );

  servo_2.attach(
    2,
    SERVOMIN,
    SERVOMAX
  );


  // Initialise servo position

  Servo_PROGRAM_Zero();

}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  client = server.available();


  if (client) {

    WA_en = true;
    ED_client = true;

    Serial.println("[Client connected]");


    unsigned long previousMillis =
      millis();

    const unsigned long timeoutDuration =
      3000;


    while (client.connected()) {


      if (
        (millis() - previousMillis)
        > timeoutDuration
        &&
        client.available() == 0
        &&
        st == true
      ) {

        break;

      }


      if (client.available()) {

        previousMillis = millis();


        unsigned char c =
          client.read() & 0xff;


        Serial.write(c);

        st = false;


        if (c == 200)
          st = true;


        if (
          c == 0x55
          &&
          isStart == false
        ) {

          if (prevc == 0xff) {

            index_a = 1;

            isStart = true;

          }

        }

        else {

          prevc = c;


          if (isStart) {

            if (index_a == 2) {

              dataLen = c;

            }

            else if (index_a > 2) {

              dataLen--;

            }


            if (
              index_a < sizeof(buffer)
            ) {

              writeBuffer(
                index_a,
                c
              );

            }

          }

        }


        index_a++;


        if (index_a > 50) {

          index_a = 0;

          isStart = false;

        }


        if (
          isStart
          &&
          dataLen == 0
          &&
          index_a > 3
        ) {

          isStart = false;

          parseData();

          index_a = 0;

        }

      }


      if (Serial.available()) {

        char c =
          Serial.read();


        sendBuff += c;


        client.print(sendBuff);


        Serial.print(sendBuff);


        sendBuff = "";

      }


      static unsigned long Test_time = 0;


      if (
        millis() - Test_time
        > 1000
      ) {

        Test_time = millis();


        if (
          WiFi.softAPgetStationNum()
          == 0
        ) {

          break;

        }

      }

    }


    client.stop();


    Servo_PROGRAM_Zero();


    Serial.println(
      "[Client disconnected]"
    );

  }


  else {

    if (ED_client == true) {

      ED_client = false;

    }

  }

}