// variable arrays
int LEDPins[4] = {2, 3, 4, 5};
int buttonPins[4] = {6, 7, 8, 9};
long LEDSequence[32];

// define inputs and outputs
void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < 4; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(0));
}
// main loop
void loop()
{
  // lose variable
  bool lose = false;
  // seed sequence
  for(int i = 0; i < 32; i++)
  {
    LEDSequence[i] = random(0, 4);
  }
  // main game loop
  for(int level = 0; level < 32; level++)
  {
    // display
    for(int i = 0; i <= level; i++)
    {
      int store = LEDSequence[i];
      Serial.println(store); // debug
      digitalWrite(LEDPins[store], HIGH);
      delay(500);
      digitalWrite(LEDPins[store], LOW);
      delay(500);
    }
    // get input (could not figure out how to get sample working)
    for(int i = 0; i <= level; i++)
    {
      int button = -1;
      while(button < 0)
      {
        delay(10);
        for(int j = 0; j <=4 ; j++)
        {
          if(digitalRead(buttonPins[j]) == HIGH)
          {
            continue;
          }
          else
          {
            button = j;
          }
        }
        delay(10);
      }
      // check for lose
      if(LEDSequence[i] != button)
      {
        lose = true;
      }
      Serial.println("Sequence"); // debug
      Serial.println(button); // debug
      Serial.println(LEDSequence[i]); // debug
      Serial.println("end check"); // debug
      // display pushed
      digitalWrite(LEDPins[button], HIGH);
      delay(250);
      digitalWrite(LEDPins[button], LOW);
      delay(250);
    }
    // check if win or loss
    if(lose == true)
    {
      loseSeq();
      break;
    }else if((lose == false) && (level == 31)){
      winSeq();
    }
  }
}
// lose sequence
void loseSeq()
{
  for(int i = 0; i < 4; i++)
  {
    digitalWrite(LEDPins[i], HIGH);
  }
  delay(1000);
  int flush = 500;
  for(int i = 3; i > -1 ; i--)
  {
    digitalWrite(LEDPins[i], LOW);
    delay(flush);
    flush = flush + (flush / 2);
  }
  
}
// win sequence
void winSeq()
{
  for(int j = 0; j < 4; j++)
  {
    for(int i = 3; i > -1 ; i--)
  	{
  	  digitalWrite(LEDPins[i], LOW);
  	}
    delay(250);
  	for(int i = 0; i < 4; i++)
  	{
  	  digitalWrite(LEDPins[i], HIGH);
 	 }
  	delay(500);
  	for(int i = 3; i > -1 ; i--)
  	{
  	  digitalWrite(LEDPins[i], LOW);
  	}
    delay(250);
  }
}