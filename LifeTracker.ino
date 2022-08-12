//setup the the LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Pins that will be used for the buttons
int lifeUp = 6;
int lifeDown = 5;
int cycle = 4;

//Var used so buttons are only pressed once
int lifeUp_pressed = 0;
int lifeDown_pressed = 0;
int cycle_pressed = 0;

//the 4 players life totals saved
int life[4] = {40,40,40,40};

//1..4 to used as selected player
//will just take it minus 1 when want to use it for life index
int selected_player = 1;

//print the elements that will not change and setup the buttons
void setup() {
  lcd.begin(16, 2);
  lcd.print("P1: ");

  lcd.setCursor(9, 0);
  lcd.print("P2: ");

  lcd.setCursor(9, 1);
  lcd.print("P3: ");

  lcd.setCursor(0, 1);
  lcd.print("P4: ");

  pinMode(lifeUp, INPUT_PULLUP);
  pinMode(lifeDown, INPUT_PULLUP);
  pinMode(cycle, INPUT_PULLUP);
}

//Print all the life totals
void print_life() {
  lcd.setCursor(3, 0);
  lcd.print(life[0]);

  lcd.setCursor(12, 0);
  lcd.print(life[1]);

  lcd.setCursor(12, 1);
  lcd.print(life[2]);

  lcd.setCursor(3, 1);
  lcd.print(life[3]);
}

//print the * for which player is selected with the cycle
// have to print black space to clear the last printed *
void print_select(int player) {
  if (player == 1) {
    lcd.setCursor(7, 0);
    lcd.print("* ");
    lcd.setCursor(7, 1);
    lcd.print("  ");
  }
  else if (player == 2) {
    lcd.setCursor(7, 0);
    lcd.print(" *");
    lcd.setCursor(7, 1);
    lcd.print("  ");
  }
  else if (player == 3) {
    lcd.setCursor(7, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print(" *");
  }
  else if (player == 4) {
    lcd.setCursor(7, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("* ");
  }
}

void loop() {
  print_life();
  print_select(selected_player);

  if (digitalRead(lifeUp) == LOW && digitalRead(lifeDown) == LOW)
  {
    life[0] = 40;
    life[1] = 40;
    life[2] = 40;
    life[3] = 40;
  }

  if (digitalRead(cycle) == LOW && cycle_pressed == 0)
  {
    selected_player+=1;
    if (selected_player >= 5)
    {
      selected_player = 1;
    }
    cycle_pressed = 1;
  }
  if (digitalRead(cycle) == HIGH)
  {
    cycle_pressed = 0;
  }

  if (digitalRead(lifeUp) == LOW && lifeUp_pressed == 0)
  {
    life[selected_player-1]+=1;
    lifeUp_pressed = 1;
  }
  if (digitalRead(lifeUp) == HIGH)
  {
    lifeUp_pressed = 0;
  }

  if (digitalRead(lifeDown) == LOW && lifeDown_pressed == 0)
  {
    life[selected_player-1]-=1;
    lifeDown_pressed = 1;
  }
  if (digitalRead(lifeDown) == HIGH)
  {
    lifeDown_pressed = 0;
  }
}
