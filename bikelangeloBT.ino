//TODO: falta relacionar el delayInchar y "delayInword" con la V que devuelve el tacometro

/*
  inspired on Ahmad Saeeds persitence of vision project

  This code is capable of displaying the following characters;
  0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ .-_!%&#$,()@?
  You must send an '&' at the end of the sentence to "close" it
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

//////////////////// Message to Customize  ///////////////////
int msgLength;                              ///
String msgBody;                ///
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////




#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7
#define LED6 8
#define LED7 9

//---------------- tacometro -----------

volatile byte state = LOW;


//--------------------------------------

boolean pintState;
int columnNum = -1;
String charToWrite;

int done = 0;
int cont = 0;

void setup() {
  Serial.begin(9600);

  mySerial.begin(38400);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(13, OUTPUT);

  //------------------ tacometro ------------

  attachInterrupt(0, magnet_detect, FALLING);

  //-----------------------------------------


}

void loop() {
  while (done == 0)
  {
    // Serial.println("en el while");
    while (mySerial.available())
    {
      delay(20);
      char c = mySerial.read();
      Serial.println(c);

      switch (c)
      {
        case '&':
          done = 1;
          digitalWrite(13, HIGH);
          break;
      }

      if (c != '&')
      {
        msgBody += c;
        cont++;
      }

    }
    state = LOW;

  }
  msgLength = cont;
  byte msgCode[(7 * msgLength) + 10];
  msgBody.toUpperCase();
  Serial.print("frase: ");
  Serial.println(msgBody);


  //// Convert all text to binary array ////////////////////////
  if ( columnNum == -1 ) // This block needs to be done once//
  { //
    for (int c = 0; c < (msgBody.length()); c++)  {         //
      //Separate the following character                    //
      charToWrite = msgBody.substring(c, c + 1);            //
      //Send the separated characted to addChar function    //
      Serial.print("char to write: ");
      Serial.println(charToWrite);
      addChar(charToWrite, msgCode);                               //
    }                                                       //
    //Add a little space after each character             //

    addChar(" ", msgCode);                                         //
    addChar(" ", msgCode);                                         //
  }                                                         //
  //////////////////////////////////////////////////////////////

  //// Display the binary arrays after all characters are coded //
  for (int c = 0; c < (sizeof(msgCode)); )  {


    if (state == 1)
    {

      Serial.println(msgCode[c]);
      pintState = (msgCode[c] / B1000000) % B10;                //
      digitalWrite(LED1, pintState);
      Serial.print("LED 1: ");
      Serial.println(pintState);
      pintState = (msgCode[c] / B100000) % B10;                 //
      digitalWrite(LED2, pintState);
      Serial.print("LED 2: ");
      Serial.println(pintState);//
      pintState = (msgCode[c] / B10000) % B10;                  //
      digitalWrite(LED3, pintState);
      Serial.print("LED 3: ");
      Serial.println(pintState);//
      pintState = (msgCode[c] / B1000) % B10;                   //
      digitalWrite(LED4, pintState);
      Serial.print("LED 4: ");
      Serial.println(pintState);//
      pintState = (msgCode[c] / B100) % B10;                    //
      digitalWrite(LED5, pintState);
      Serial.print("LED 5: ");
      Serial.println(pintState);//
      pintState = (msgCode[c] / B10) % B10;                     //
      digitalWrite(LED6, pintState);
      Serial.print("LED 6: ");
      Serial.println(pintState);//
      pintState = msgCode[c] % B10;;                            //
      digitalWrite(LED7, pintState);
      Serial.print("LED 7: ");
      Serial.println(pintState);

      c++;
      state = 0;
    }
  }
}



void addChar(String y, byte msgCode[]) {
  if (y == "1") {
    addColumn(B0010001, msgCode);
    addColumn(B0100001, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "2") {
    addColumn(B0100001, msgCode);
    addColumn(B1000011, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "3") {
    addColumn(B0100010, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "4") {
    addColumn(B0001100, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0100100, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000100, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "5") {
    addColumn(B1110010, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1001110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "6") {
    addColumn(B0111110, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "7") {
    addColumn(B1000000, msgCode);
    addColumn(B1000111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1010000, msgCode);
    addColumn(B1100000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "8") {
    addColumn(B0110110, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "9") {
    addColumn(B0110010, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "0") {
    addColumn(B0111110, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "A") {
    addColumn(B0011111, msgCode);
    addColumn(B0100100, msgCode);
    addColumn(B1000100, msgCode);
    addColumn(B1000100, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "B") {
    addColumn(B1111111, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "C") {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0100010, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "D") {
    addColumn(B1111111, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "E") {
    addColumn(B1111111, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "F") {
    addColumn(B1111111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "G") {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "H") {
    addColumn(B1111111, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "I") {
    addColumn(B0000000, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "J") {
    addColumn(B0000000, msgCode);
    addColumn(B0000010, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "K") {
    addColumn(B1111111, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0100010, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "L") {
    addColumn(B1111111, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "M") {
    addColumn(B1111111, msgCode);
    addColumn(B0100000, msgCode);
    addColumn(B0011000, msgCode);
    addColumn(B0100000, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "N") {
    addColumn(B1111111, msgCode);
    addColumn(B0010000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0000100, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "O") {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "P") {
    addColumn(B1111111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B0110000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);

  }
  else if (y == "Q") {
    addColumn(B0111100, msgCode);
    addColumn(B1000010, msgCode);
    addColumn(B1000010, msgCode);
    addColumn(B1000010, msgCode);
    addColumn(B0111101, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "R") {
    addColumn(B1111111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001100, msgCode);
    addColumn(B1001010, msgCode);
    addColumn(B0110001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "S") {
    addColumn(B0110010, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "T") {
    addColumn(B1000000, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "U") {
    addColumn(B1111110, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B1111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "V") {
    addColumn(B1111100, msgCode);
    addColumn(B0000010, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000010, msgCode);
    addColumn(B1111100, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "W") {
    addColumn(B1111110, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000110, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B1111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "X") {
    addColumn(B1100011, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B1100011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "Y") {
    addColumn(B1110000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001111, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B1110000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "Z") {
    addColumn(B1000011, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1000011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "Z") {
    addColumn(B1000011, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1000011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == " ") {
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == ".") {
    addColumn(B0000000, msgCode);
    addColumn(B0000011, msgCode);
    addColumn(B0000011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "_") {
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "-") {
    addColumn(B0000000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "!") {
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B1111101, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "(") {
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == ")") {
    addColumn(B1000001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "%") {
    addColumn(B1100010, msgCode);
    addColumn(B1100100, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0010011, msgCode);
    addColumn(B0100011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == ",") {
    addColumn(B0000000, msgCode);
    addColumn(B0000101, msgCode);
    addColumn(B0000110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "?") {
    addColumn(B0100000, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B0110000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "#") {
    addColumn(B0010100, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "@") {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1011101, msgCode);
    addColumn(B1011101, msgCode);
    addColumn(B0111000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
  else if (y == "$") {
    addColumn(B0110010, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
  }
}

void addColumn(byte x, byte msgCode[]) {
  columnNum += 1;
  msgCode[columnNum] = (x); // TO DO: tengo que meter este array como argumento de la funcion por que si no no puedo declararlo despues de leer lo largo q es el texto

}

void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
{
  //Serial.print("detect: ");
  state = !state;
  //Serial.println(state);
}
