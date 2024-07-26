/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

//Parabens do buzzer notas musicais
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
///parabens do buzzer notas musicais
int tempo = 140;
int x = -1;
int y = -1;
// change this to whichever pin you want to use
int buzzer = 10;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Happy Birthday
  // Score available at https://musescore.com/user/8221/scores/26906

  NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
  NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
  NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

  NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4, 
  NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
  NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
  NOTE_F4,-2,
 
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;








// Ligações do Arduino



const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int col0= 0;
int col1= 1;
int col2= 2;
int col3= 3;
int col4= 4;
int col5= 5;
int col6= 6;
int col7= 7;
int col8= 8;
int col9= 9;
int col10 = 10;
int col11 = 11;
int col12 = 12;
int col13 = 13;
int col14 = 14;
int col15 = 15;
int col16 = 16;




void setup() {
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2); // Aqui informo que são 16 caracteres e 2 linhas
   // To colocando para exibir a frase na coluna 0 e linha 0 (opcional)
   // Escrevo "Arduino"
  //lcd.setCursor(0, 1); // E agora to colocando para exibir a frase na coluna 0 e linha 1
  //lcd.print("Display LCD"); // E escrevo "Display LCD"

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}



///////(coluna , linha)
void loop() {
/////linha 0
for(int i = 0; i< 16;i++){
  lcd.setCursor(col0, 0);
  lcd.print("F");
  lcd.setCursor(col1, 0);

  lcd.print("E");
  lcd.setCursor(col2, 0);

  lcd.print("L");
  lcd.setCursor(col3, 0);

  lcd.print("I");
  lcd.setCursor(col4, 0);

  lcd.print("Z");
  lcd.setCursor(col5, 0);

  lcd.print(" ");
  lcd.setCursor(col6, 0);

  lcd.print("A");
  lcd.setCursor(col7, 0);

  lcd.print("N");
  lcd.setCursor(col8, 0);

  lcd.print("I");
  lcd.setCursor(col9, 0);

  lcd.print("V");
  lcd.setCursor(col10, 0);

  lcd.print("E");
  lcd.setCursor(col11, 0);

  lcd.print("R");
  lcd.setCursor(col12, 0);

  lcd.print("!");
  lcd.setCursor(col13, 0);

  lcd.print(" ");
  lcd.setCursor(col14, 0);

  lcd.print(" ");
  lcd.setCursor(col15, 0);

  lcd.print(" ");
  lcd.setCursor(col16,0);
  lcd.print(" ");

////linha 1
  lcd.setCursor(col0, 1);
  lcd.print("K");
  lcd.setCursor(col1, 1);
  lcd.print("A");
  lcd.setCursor(col2, 1);
  lcd.print("M");
  lcd.setCursor(col3, 1);
  lcd.print("I");
  lcd.setCursor(col4, 1);
  lcd.print("L");
  lcd.setCursor(col5, 1);
  lcd.print("A");
  lcd.setCursor(col6, 1);
  lcd.print(" ");
  lcd.setCursor(col7, 1);
  lcd.print(" ");
  lcd.setCursor(col8, 1);
  lcd.print(" ");
  lcd.setCursor(col9, 1);
  lcd.print(" ");
  lcd.setCursor(col10, 1);
  lcd.print(" ");
  lcd.setCursor(col11, 1);
  lcd.print(" ");
  lcd.setCursor(col12, 1);
  lcd.print(" ");
  lcd.setCursor(col13, 1);
  lcd.print(" ");
  lcd.setCursor(col14, 1);
  lcd.print(" ");
  lcd.setCursor(col15, 1);
  lcd.print(" ");
  lcd.setCursor(col16, 1);
  lcd.print(" ");
  
  col0++;
  col1++;
  col2++;
  col3++;
  col4++;
  col5++;
  col6++;
  col7++;
  col8++;
  col9++;
  col10++;
  col11++;
  col12++;
  col13++;
  col14++;
  col15++;
  col16++;


  delay(500);
  x++;
  y++;
  lcd.setCursor(x, 0);
  lcd.print(" ");
  lcd.setCursor(y, 1);
  lcd.print(" ");
  }
}
