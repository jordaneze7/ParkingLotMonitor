#include <LiquidCrystal.h> //Fichier de définition des fonctions pour l'écran LCD
#include <RTClib.h>
//Définition pour l'écran LCD
#define DB0 30
#define DB1 31
#define DB2 32
#define DB3 33
#define DB4 34
#define DB5 35
#define DB6 36
#define DB7 37
#define ENABLE 38
#define RW 39
#define RS 40
#define BKLT 41
#define DELG 12
#define DELJ 11
#define DELR 10
#define BTE 6
#define BTS 5

//Création de l'objet lcd. Ici il faut spécifier dans l'ordre les différents 
//branchements.
LiquidCrystal lcd(RS, RW, ENABLE, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7);
RTC_DS1307 rtc;
int voiture_max = 150;
static int nb_voiture = 0;

void rtc_build()
{
  DateTime now = rtc.now();
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print("h");
  lcd.print(now.minute(), DEC);
  lcd.setCursor(0,1);


}

void bouton()
{
  if(digitalRead(BTE) == LOW)
  {
    while(digitalRead(BTE) == LOW);
    nb_voiture++;

    if(nb_voiture > voiture_max)
    {
      nb_voiture = 150;
    }
  }
  if(digitalRead(BTS) == LOW)
  {
    while(digitalRead(BTS) == LOW);
    nb_voiture--;
    if(nb_voiture < 0)
    {
      nb_voiture = 0;
    }
  }
  
}

void lumiere(){
if(nb_voiture >= 0 && nb_voiture <= 100)
{
  
  digitalWrite(DELJ, LOW);
  digitalWrite(DELR, LOW);
  digitalWrite(DELG, HIGH);
}
else if(nb_voiture > 100 && nb_voiture < 150)
{
  digitalWrite(DELG, LOW);
  digitalWrite(DELR, LOW);
  digitalWrite(DELJ, HIGH);
}
else if(nb_voiture == voiture_max)
{
  digitalWrite(DELG, LOW);
  digitalWrite(DELJ, LOW);
  digitalWrite(DELR, HIGH);
}

}

void setup() {
  //Démarre l'afficheur LCD 16 caractères sur 2 lignes.  
  Serial.begin(9600);
  pinMode(DELG, OUTPUT);
  pinMode(DELJ, OUTPUT);
  pinMode(DELR, OUTPUT);
  pinMode(BTE, INPUT_PULLUP);
  pinMode(BTS, INPUT_PULLUP);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  if(!rtc.begin())
  {
    Serial.print("Erreur! RTC non-detecte!");
    while(1);
  }
}
void loop() 
{
  lcd.print("Cars: ");
  lcd.print(nb_voiture);
  lcd.setCursor(0,0);
  rtc_build();
  bouton();
  lumiere();
}