//HC-12 Useful Functions and Operators Receive
//Autor Tom Heylen tomtomheylen.com

#include <SoftwareSerial.h>

SoftwareSerial mySerial(50, 51); // TX, RX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.print("TEST");
}

void loop() {
  
  if(mySerial.available() > 1){

    
    String input = mySerial.readString();//read string
    //Serial.println(input);
    /*
    String first4 = input.substring(0,4);//first 4 characters
    Serial.println(first4);
    
    String last = input.substring(4);//all characters after the 4th character
    Serial.println(last);
    
    int integer = last.toInt();//Convert to integer
    Serial.println(integer);
    Serial.println("****************************");
    */
    Serial.println("Receiver...");
    
    String TempC = input.substring(4,9);//all characters after the 4th character
    Serial.print("Tempterature C: ");
    Serial.println(TempC);

    String TempF = input.substring(14,19);//all characters after the 4th character
    Serial.print("Tempterature F: ");
    Serial.println(TempF);

    String IndexC = input.substring(24,29);//all characters after the 4th character
    Serial.print("Index C: ");
    Serial.println(IndexC);

    String IndexF = input.substring(34,39);//all characters after the 4th character
    Serial.print("Index F: ");
    Serial.println(IndexF);

  }
  delay(100);
}
/*
//here are more operators and functions

    Serial.parseInt()// read serial input and convert to integer
    Serial.parseFloat()// read serial input and convert to float
    Serial.read() - '0'; // deduct ascii value of '0' to find numeric value of 
    
    isAlphaNumeric()// it's alphanumeric
    isAlpha()// it's alphabetic
    isAscii()// it's ASCII
    isWhitespace()// it's whitespace
    isControl()// it's a control character
    isDigit()// it's a numeric digit
    isGraph()// it's a printable character that's not whitespace
    isLowerCase()// it's lower case
    isPrintable()// it's printable
    isPunct()// it's punctuation
    isSpace()// it's a space character
    isUpperCase()// it's upper case
    isHexadecimalDigit()// it's a valid hexadecimaldigit (i.e. 0 - 9, a - F, or A - F) 

*/
