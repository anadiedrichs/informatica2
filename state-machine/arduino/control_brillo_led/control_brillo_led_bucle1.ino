// C++ code
/*
Si ingresa letra A : aumenta el brillo
Si ingresa letra D: decrementa el brillo
Si ingresa ?: muestra ayuda
*/
int ledPin = 11;
int ledVal;
int incomingByte = 0; // for incoming serial data
int estado;

void setup()
{
  Serial.begin(9600); //salida consola serie
  pinMode(ledPin, OUTPUT); // pin led
  ledVal = 255 ;
}

void loop()
{
  
 /* for (int ledVal=0;ledVal<255;ledVal++){
    
    analogWrite(ledPin,ledVal);
    Serial.println(ledVal);
    delay(250);
  }*/
  
  
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    
    if(incomingByte == 'D')
    {
      
      Serial.println("DDDDD");
      estado = 'D' ;
      
    }else if(incomingByte == 'A')
    {
      Serial.println("AAAA");
       estado = 'A' ;
      
    }else if(incomingByte == '?')
    {
       estado = '?' ;
      
    }
  
  }
  
    if(estado == 'D')
    {
      
      Serial.println("decremento");
      
      if(ledVal > 0) ledVal -- ;
      
    }else if(estado == 'A')
    {
      Serial.println("aumenta");
      
      if(ledVal < 255) ledVal ++ ;
      
    }else if(estado == '?')
    {
      
      Serial.println("MENU");
      Serial.println("A para incrementar luz");
      Serial.println("D oara bajar brillo");
      Serial.println("? muestra este menu");
      estado = 'R';
    }else
    {
      ledVal = 0 ;// apago led
    }
  
    analogWrite(ledPin,ledVal);
    Serial.println(ledVal);
    delay(250);
    
  
}