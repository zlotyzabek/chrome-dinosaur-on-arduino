#include <LiquidCrystal.h>

const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
bool ButtonClick;
int cactus_x[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned long long cactuses = 0;
unsigned long long cactusTimeRespawn = 0;
unsigned long long jumpTime = 0;
unsigned long long isjumping = 0;
unsigned long long updateCactus = 0;
unsigned long long jump_reload = 0;
int old_cactus = 1;
int score = 0;
bool lose = false;
bool lose_finish = false;

byte dinosaur[] = {
  B01110,
  B00101,
  B00111,
  B00110,
  B01111,
  B01110,
  B11110,
  B01010
};

byte cactus1[] = {
  B00000,
  B00000,
  B01110,
  B11110,
  B01111,
  B01110,
  B11110,
  B01110
};

byte cactus2[] = {
  B01000,
  B01100,
  B01101,
  B01111,
  B11100,
  B01110,
  B01100,
  B01100
};

void setup() {
  pinMode(9, INPUT);
  lcd.begin(16, 2);
  lcd.createChar(0, dinosaur);
  lcd.createChar(1, cactus1);
  lcd.createChar(2, cactus2);
  Serial.begin(9600);
}

void add_cactus(){
  cactus_x[15] = random(1, 3);
  cactuses ++;
  }
  
void update_cactus(){
  for (int i = 0; i < 16; i ++) {
    if(cactus_x[i] > 0){
      lcd.setCursor(i, 1);
      lcd.write(cactus_x[i]);
      lcd.setCursor(i +1, 1);
      lcd.println(" ");
      old_cactus = cactus_x[i];
      cactus_x[i] = 0;
      if(i > 0);
        cactus_x[i - 1] = old_cactus;
      }
      else{
        lcd.setCursor(i, 1);  
        lcd.print(" ");
      }
          
      if(i == 2 and cactus_x[i - 1] > 0){
        if (jumpTime < millis()){
          lcd.clear();
          lcd.setCursor(10, 0);
          lcd.print("LOSE ");
          updateCactus = 0xFFFFFFFFFFFFFFF;
          lose = true;
          }
        }
     
  }
  
  }

void loop() {
  ButtonClick = digitalRead(9);
  if (cactusTimeRespawn < millis()){
    cactusTimeRespawn = millis() + random(1000, 2500);
      add_cactus();
    }
  if (lose == false){
  if (ButtonClick == 0 and isjumping == 0 and jump_reload < millis()){
    isjumping = 1;
    jumpTime = millis() + 1000;
    jump_reload = millis() + 1250;
    }
  if (ButtonClick == 1){
    isjumping = 0;
    
    }
  }
  if (lose == false){
  if (jumpTime < millis()){
    lcd.setCursor(2, 1);
    lcd.write(byte(0));
    lcd.setCursor(2, 0);
    lcd.print(" ");
    
    }
 else{
    lcd.setCursor(2, 1);
    lcd.print(" ");
    lcd.setCursor(2, 0);
    lcd.write(byte(0));
  
  }
  if (updateCactus < millis()){
    updateCactus = millis() + 200;
    update_cactus();
    score ++;
  }
  }
   if (lose == false){
          lcd.setCursor(10, 0);
          lcd.print(score);
        
        }
   if (lose == true and lose_finish == false){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print(score);
          Serial.println(score);
          lcd.setCursor(0, 0);
          lcd.print("SCORE: ");
          lose_finish = true;
        }
  delay(10);
}
