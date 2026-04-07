// Simon game
// by Milan Soukup, Filip Novák


int maxCount = 7;  //Počet kol
int rndSeq[50] ;
int debounceDelay = 30;

const int buzzerPin = 2; 

int relayPin = 3; // Pin připojený na IN relé 

const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;

const int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int button4 = 7;
  
const int note_G3 = 196;  
const int note_A3 = 220;
const int note_B3 = 247;
const int note_C4 = 262;

int iCount;
int iiCount;
int highScore = 0;
int score = 0; 
int hry = 0;


int freq[4] = {196, 220, 247, 262};
int seqDuration = 250; //délka tónu
int seqDelay = 350;   
int replayDelay = 1500; 
int button;

void setup() 
{
pinMode(buzzerPin, OUTPUT);
pinMode(ledPin1, OUTPUT);  
pinMode(ledPin2, OUTPUT);  
pinMode(ledPin3, OUTPUT); 
pinMode(ledPin4, OUTPUT); 
  
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);
pinMode(button4, INPUT_PULLUP); 

  pinMode(relayPin, OUTPUT); // Nastavení pinu jako výstup 
    
Serial.begin(9600); 

}

void loop()
{ 
if (hry == 1){ 
    
}

if (hry == 0){



  digitalWrite(relayPin, LOW); 
  delay(1000); 
  
  melody1(); 
  delay(500);
  beepStart();  
  delay(1000);  
  

int randomStart = analogRead(A3);
  randomSeed(randomStart);
  Serial.print("Random seed = ");
  Serial.println(randomStart);
  for (int count =0 ; count < maxCount ; count++)
  {rndSeq[count] = random(1,5);
  }

  Serial.println("Sequence = ");
  for (int count =0 ; count <maxCount ; count++)
  {Serial.print(rndSeq[count]);
  }  
  Serial.println();
  Serial.println();
    
 
  boolean correctResponse = true;

  int loopCount = 0;          
  while (loopCount < maxCount) 
  {
  iCount = 0;
    score = loopCount+1;
    while (iCount <= loopCount)  
    {
     button = rndSeq[iCount];
     Serial.print(button);  
     digitalWrite(ledPin1, LOW);  
     digitalWrite(ledPin2, LOW);
     digitalWrite(ledPin3, LOW);  
     digitalWrite(ledPin4, LOW);
     
  if (button == 1) 
     {digitalWrite(ledPin1, HIGH);
     tone(buzzerPin, freq[button-1], seqDuration);
     delay(seqDelay);
     digitalWrite(ledPin1, LOW);
     delay(50);}
  if (button == 2) 
     {digitalWrite(ledPin2, HIGH);
     tone(buzzerPin, freq[button-1], seqDuration);
     delay(seqDelay);
     digitalWrite(ledPin2, LOW);
     delay(50);}
  if (button == 3) 
     {digitalWrite(ledPin3, HIGH);
     tone(buzzerPin, freq[button-1], seqDuration); 
     delay(seqDelay);
     digitalWrite(ledPin3, LOW);
     delay(50);}
  if (button == 4) 
     {digitalWrite(ledPin4, HIGH);
     tone(buzzerPin, freq[button-1], seqDuration);
     delay(seqDelay);
     digitalWrite(ledPin4, LOW);
     delay(50);} 
     iCount = iCount+1; 
    }  
    
 
    Serial.println( ); 
    Serial.println("Enter your response: "); 
    iiCount = 0;
    
  while (iiCount <= loopCount) {
    digitalWrite(ledPin1, LOW);  
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);  
    digitalWrite(ledPin4, LOW);
 

  if (digitalRead(button1) == LOW ) 
    {button = 1;
    if (button==rndSeq[iiCount]) 
      {correctResponse = true;
      digitalWrite(ledPin1, HIGH); 
      tone(buzzerPin, freq[0],seqDuration);
      delay(debounceDelay); 
      iiCount=iiCount+1;     } 
    else 
      {correctResponse=false;
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);
      tone(buzzerPin, 140, 500);
      delay(seqDuration);
      iiCount=999;
      }    
    while (digitalRead(button1) == LOW ) 
      {delay(debounceDelay);} 
    digitalWrite(ledPin1, LOW); 
    }
   
  
  if (digitalRead(button2) == LOW )
    {button = 2;
    if (button==rndSeq[iiCount]) 
      {correctResponse = true;    
      digitalWrite(ledPin2, HIGH); 
      tone(buzzerPin, freq[1],seqDuration);
      delay(debounceDelay);          
      iiCount=iiCount+1;
      } 
    else 
      {correctResponse=false;
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);
      tone(buzzerPin, 140, 500);
      delay(seqDuration);
      iiCount=999;
      }    
    while (digitalRead(button2) == LOW ) 
      {delay(debounceDelay);}  
    digitalWrite(ledPin2, LOW);    
    }
  
   
  if (digitalRead(button3) == LOW )
    {button = 3;
    if (button==rndSeq[iiCount]) 
      {correctResponse = true;
       digitalWrite(ledPin3, HIGH); 
       tone(buzzerPin, freq[2],seqDuration);
       delay(debounceDelay);
       iiCount=iiCount+1;
       }          
    else 
      {correctResponse=false;
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);
      tone(buzzerPin, 140, 500);
      delay(seqDuration);
      iiCount=999;
      }  
    while (digitalRead(button3) == LOW ) 
      {delay(debounceDelay);} 
    digitalWrite(ledPin3, LOW);
    } 
    
  
  if (digitalRead(button4) == LOW )
    {button = 4;
    if (button==rndSeq[iiCount]) 
      {correctResponse = true;
      digitalWrite(ledPin4, HIGH); 
      tone(buzzerPin, freq[3],seqDuration);
      delay(debounceDelay);          
      iiCount=iiCount+1;     
      } 
    else 
      {correctResponse=false;
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);
      tone(buzzerPin, 140, 500);
      delay(seqDuration);
      iiCount=999;
      }  
    while (digitalRead(button4) == LOW )
      {delay(debounceDelay);} 
    digitalWrite(ledPin4, LOW);
    }

    if (correctResponse==false) 
    {iiCount= 999; iCount=999; 
    loopCount = 111;
    Serial.println("Wrong one.");
    }                        
  }           
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);
         
   delay(replayDelay); 
   loopCount = loopCount+1;  
  }  



if(correctResponse==true)
{
  Serial.println("Winner!");
  melody1(); 
  digitalWrite(relayPin, HIGH); // Sepne relé
  delay(1000); 
hry = 1;
} 
else 
{ 
  digitalWrite(relayPin, LOW); // Sepne relé
  delay(1000); 

  Serial.println("Sorry");  melody2();
  score = score-1; 
}
 

   Serial.print("Score = ");Serial.println(score);
   Serial.println("game over - restarting");
   delay(2500);
}
}
void melody1()  
{

int thisNote;
int pauseDuration;
int playDuration;
int notes1 = 7;
int melody1[] = {note_G3, note_A3, note_B3, note_C4, 0, note_G3, note_C4};


int noteDurations1[] = { 8, 8, 8, 4, 4, 4, 2};
int wholeNoteDuration = 2000;

  for (thisNote = 0; thisNote < notes1; thisNote++) 
  { 

  noteDurations1[thisNote] = wholeNoteDuration / noteDurations1[thisNote]; 
  }

  for (thisNote = 0; thisNote < notes1; thisNote++) 
  {
  playDuration = noteDurations1[thisNote] * .7 ; 
  pauseDuration = noteDurations1[thisNote] *.3 ;
    
  if (melody1[thisNote] == note_G3) {digitalWrite(ledPin1, HIGH);}
  if (melody1[thisNote] == note_A3) {digitalWrite(ledPin2, HIGH);}
  if (melody1[thisNote] == note_B3) {digitalWrite(ledPin3, HIGH);}
  if (melody1[thisNote] == note_C4) {digitalWrite(ledPin4, HIGH);}
   
  tone(buzzerPin, melody1[thisNote], playDuration);
    
    delay(playDuration);
    digitalWrite(ledPin1, LOW);   
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);  
    digitalWrite(ledPin4, LOW);  
    noTone(buzzerPin);           
  } 
}

void melody2()
{

int thisNote;
int pauseDuration;
int playDuration;
int wholeNoteDuration = 2000;
int notes2 = 7;
int melody2[] = {note_C4, note_G3, note_G3, note_A3, note_G3, note_B3, note_C4};

int noteDurations2[] = {  4, 8, 8, 4, 2, 4, 4};

  

for (thisNote = 0; thisNote < notes2; thisNote++) 
{ 
  
  noteDurations2[thisNote] = wholeNoteDuration / noteDurations2[thisNote]; 
}  
  for (thisNote = 0; thisNote < notes2; thisNote++) 
  {
  playDuration = noteDurations2[thisNote] * .7 ; 
  pauseDuration = noteDurations2[thisNote] *.3 ;
    
  if (melody2[thisNote] == note_G3) {digitalWrite(ledPin1, HIGH);}
  if (melody2[thisNote] == note_A3) {digitalWrite(ledPin2, HIGH);}
  if (melody2[thisNote] == note_B3) {digitalWrite(ledPin3, HIGH);}
  if (melody2[thisNote] == note_C4) {digitalWrite(ledPin4, HIGH);}
   
  tone(buzzerPin, melody2[thisNote], playDuration);
    
    delay(playDuration);
    digitalWrite(ledPin1, LOW);   
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);  
    digitalWrite(ledPin4, LOW);  
    noTone(buzzerPin);           
  } 
}
void beepStart()
{
int toneFreq = 100;
  for(int i=1; i<12; i++)
{  tone(buzzerPin, toneFreq, 200);
    digitalWrite(ledPin1, HIGH);  
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);  
    digitalWrite(ledPin4, HIGH);
   delay(100);
    digitalWrite(ledPin1, LOW);  
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);  
    digitalWrite(ledPin4, LOW);
   delay(100);
   toneFreq= float(toneFreq)*1.12;
}
}
