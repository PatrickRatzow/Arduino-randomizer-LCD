/** Arduino character randomizer by Patrick Ratzow (2016)
 * Randomizes a character ranging from A-V using a button.
 * 
 * Useful if you need reference on how to use a LCD panel 
 * or if you need to just need an idea how to randomize and apply it.
 */

/**
 * Include the LiquidCrystal library
 * Used for the LCD display that's used in this program 
 */
#include <LiquidCrystal.h>
/**
 * Declare lcd variable with the datatype LiquidCrystal
 * There's 6 parameters, 1 for each pin.
 * For specifics about the parameters https://www.arduino.cc/en/Reference/LiquidCrystalConstructor
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/**
 * Used for the active character.
 */
char activeChar;
/**
 * Which pin is the button connected to on the Arduino board?
 */
unsigned int buttonPin = 13;
/**
 * Works as a switch for the button, so it doesnt shift constantly in loop()
 */
unsigned long buttonLastUsed = 0;
/**
 * Amount of seconds to wait for the character to change.
 * Functions as a cooldown, primarily used to prevent a new character every time loop() is called
 * and button is pressed. But could also be adjusted to suit your own needs, if you come up with a new rule.
 */
float buttonDelay = 0.35;

void setup() {
 /**
  * Feed the psuedo-random generator with random noice.
  * This helps with randomness, doesn't make it real random though.
  */ 
  randomSeed(analogRead(0));
 /** 
  * Initialize the LCD display.
  * Works like a box with dimensions
  * x = 16
  * y = 2
  */ 
  lcd.begin(16, 2);
 /**
  * Set the cursor to 0, 0
  * This is where what we print is rendered
  */
  lcd.setCursor(0, 0);
 /**
  * Print the message that's shown upon startup.
  */
  lcd.print("Start");
}

void loop() {
  /* Check if the button is down aka pressed */
  checkButtonPressed();
}

void checkButtonPressed() {
  /* Read the digital pin thats defined at top of file */
  int button = digitalRead(buttonPin);
  /**
   * Localize the getSeconds() as a variable 
   * The code will execute faster by localizing it as a variable instead of calling getSeconds() twice.
   * Micro-optimizations ¯\_(ツ)_/¯
   */
  unsigned long seconds = getSeconds();
  /**
   * If the button is not down it will return 0
   * If the button is down it will return 1
   * getSeconds() returns amount of seconds since the board started by doing millis() * 1000
   * 
   */
  if (button != 0 && seconds >= buttonLastUsed) {
    buttonPressed();
    /* Set $buttonLastUsed to now + $buttonDelay */
    buttonLastUsed = seconds + buttonDelay;
  }
}
/**
 * Returns amount of seconds since the board started up.
 */
unsigned long getSeconds() {
  return millis() / 1000;
}
/**
 * Sets $activeChar to a new letter.
 * 
 * Calls setCharacter() and generateCharacter()
 */
void buttonPressed() {
  /* Declare $character as a boolean and have it false by default */
  boolean character = false;

  /* If $character is false then execute code inside */
  while (!character) {
    /**
     * set $character to true or false. 
     * Will be true if setCharacter(generateCharacter()) set $activeChar to something new.
     * Otherwise $character will be false.
     */
    character = setCharacter(generateCharacter());
    
    /* If $character is true then then call renderCharacter() */
    if (character) {
      renderCharacter();
    }
  }
}
/**
 * Clears the LCD panel and renders $activeChar onto it.
 */ 
void renderCharacter() {
  lcd.clear();
  lcd.print(activeChar);
}
/**
 * @param char $character
 *
 * @return bool. Whether it was a success or not.
 *
 * Checks if a character matches the parameter.
 * If it matches the method will return false.
 * If it doesn't match the method will set $activeChar to @param character and return true
 */
bool setCharacter(char character) {
  if (character == activeChar) {
    /* @param $character matches $activeChar. EJECT! */
    return false;/
  }

  /* Set $activeChar to character */
  activeChar = character;
  
  /* Everything went as planned, return true to indicate it was a success */
  return true;
}
/**
 * Generates a random character ranging from A-V
 *
 * @return char
 */
char generateCharacter() {
  /**
   * Declare randNumber as datatype char.
   * This is the variable that the random character gets set to.
   */
  char randNumber;

  randNumber = round(random(65, 86)); /* A-V, only uppercase. */
  /**
   * Return the character.
   */
  return randNumber;
}

