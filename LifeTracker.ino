// setup the the LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pin that will be used for the buttons
int lifeUp = 6;
// Pin that will be used for the buttons
int lifeDown = 5;
// Pin that will be used for the buttons
int cycle = 4;
// Pin that will be used for the buttons
int mode = 3;

// Var used so buttons are only pressed once
bool lifeUp_pressed = false;
// Var used so buttons are only pressed once
bool lifeDown_pressed = false;
// Var used so buttons are only pressed once
bool cycle_pressed = false;
// Var used so buttons are only pressed once
bool mode_pressed = false;

// the 4 players life totals saved
int life[4];

// check if player is in the game
bool in_game[4];

int commander_damage[4][3];

// what mode tracker
int current_mode = 1;

// 1..4 to used as selected player
// will just take it minus 1 when want to use it for life index
int selected_player = 1;

// print the elements that will not change and setup the buttons
void setup()
{
  lcd.begin(16, 2);
  life[0] = 40;
  life[1] = 40;
  life[2] = 40;
  life[3] = 40;
  in_game[0] = true;
  in_game[1] = true;
  in_game[2] = true;
  in_game[3] = true;
  commander_damage[0][0] = 0;
  commander_damage[0][1] = 0;
  commander_damage[0][2] = 0;
  commander_damage[1][0] = 0;
  commander_damage[1][1] = 0;
  commander_damage[1][2] = 0;
  commander_damage[2][0] = 0;
  commander_damage[2][1] = 0;
  commander_damage[2][2] = 0;
  commander_damage[3][0] = 0;
  commander_damage[3][1] = 0;
  commander_damage[3][2] = 0;
  current_mode = 1;
  pinMode(lifeUp, INPUT_PULLUP);
  pinMode(lifeDown, INPUT_PULLUP);
  pinMode(cycle, INPUT_PULLUP);
  pinMode(mode, INPUT_PULLUP);
}

// Print all the life totals
void print_life()
{
  lcd.setCursor(0, 0);
  lcd.print("P1:");
  lcd.setCursor(9, 0);
  lcd.print("P2:");
  lcd.setCursor(9, 1);
  lcd.print("P3:");
  lcd.setCursor(0, 1);
  lcd.print("P4:");
  print_player_life(1);
  print_player_life(2);
  print_player_life(3);
  print_player_life(4);
  print_select(selected_player);
}

void print_player_life(int player)
{
  if (player == 1)
    lcd.setCursor(3, 0);

  else if (player == 2)
    lcd.setCursor(12, 0);

  else if (player == 3)
    lcd.setCursor(12, 1);

  else
    lcd.setCursor(3, 1);

  if (in_game[player - 1])
  {
    lcd.print(life[player - 1]);
    lcd.print(" ");

    if (life[player - 1] < 100)
      lcd.print(" ");
  }
  else
    lcd.print("K.O.");
}

void print_commander_damage()
{
}

// print the * for which player is selected with the cycle
//  have to print black space to clear the last printed *
void print_select(int select)
{
  if (select == 1)
  {
    lcd.setCursor(7, 0);
    lcd.print("* ");
    lcd.setCursor(7, 1);
    lcd.print("  ");
  }
  else if (select == 2)
  {
    lcd.setCursor(7, 0);
    lcd.print(" *");
    lcd.setCursor(7, 1);
    lcd.print("  ");
  }
  else if (select == 3)
  {
    lcd.setCursor(7, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print(" *");
  }
  else if (select == 4)
  {
    lcd.setCursor(7, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("* ");
  }
}

void update_select(bool available[4])
{
  selected_player += 1;
  while (!available[selected_player - 1])
  {
    selected_player += 1;
    if (selected_player >= 5)
    {
      selected_player = 1;
    }
  }
  if (selected_player >= 5)
  {
    selected_player = 1;
  }
}

void life_menu()
{
  print_life();

  if (digitalRead(cycle) == LOW && !cycle_pressed)
  {
    update_select(in_game);
    cycle_pressed = true;
  }
  if (digitalRead(cycle) == HIGH)
  {
    cycle_pressed = false;
  }

  if (digitalRead(lifeUp) == LOW && !lifeUp_pressed)
  {
    life[selected_player - 1] += 1;
    lifeUp_pressed = true;
  }
  if (digitalRead(lifeUp) == HIGH)
  {
    lifeUp_pressed = false;
  }

  if (digitalRead(lifeDown) == LOW && !lifeDown_pressed)
  {
    life[selected_player - 1] -= 1;
    if (life[selected_player - 1] <= 0)
    {
      in_game[selected_player - 1] = false;
      update_select(in_game);
    }
    lifeDown_pressed = true;
  }
  if (digitalRead(lifeDown) == HIGH)
  {
    lifeDown_pressed = false;
  }
}

void commander_menu()
{
  print_commander_damage();
}

// main
void loop()
{

  // reset when up and down pressed
  if (digitalRead(lifeUp) == LOW && digitalRead(lifeDown) == LOW)
  {
    setup();
  }

  switch (current_mode)
  {
  case 1:
    life_menu();
    break;
  case 2:
    commander_menu();
    break;
  }

  if (digitalRead(mode) == LOW && !mode_pressed)
  {
    current_mode += 1;
    if (current_mode > 2)
    {
      current_mode = 1;
    }
    mode_pressed = true;
  }
  if (digitalRead(mode) == HIGH)
  {
    mode_pressed = false;
  }
}
