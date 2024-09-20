/*Arduino Uno Serial + LED RGB

Conrolado via porta serial:
Digite la letra (r, g, b) seguido de algun nro entre 0 y 255
para controlar el brillo del LED via PWM
Digitar 0 resetea el led
Digitar ? muestra ayuda

*/

int ledvm = 3; // LED ROJO
int ledvd = 6; // LED VERDE
int ledaz = 5; //LED AZUL

int ledvm2 = 9; // LED 2 ROJO
int ledvd2 = 11;  // LED 2 VERDE
int ledaz2 = 10;  // LED 2 AZUL 


void setup()
{
  Serial.begin(9600);
  pinMode(ledvm,OUTPUT);
  pinMode(ledvd,OUTPUT);
  pinMode(ledaz,OUTPUT);
  pinMode(ledvm2,OUTPUT);
  pinMode(ledvd2,OUTPUT);
  pinMode(ledaz2,OUTPUT);
}

void loop()
{
    while (Serial.available())
    {
      //Adquirir el dato del puerto serie
      byte c = Serial.read();					
      if (c == 'r')								
      { // si es r minuscula
        byte vmval100 = Serial.read();	// bit 100
        //Serial.println(vmval100);
        byte vmval010 = Serial.read();	// bit 10
        //Serial.println(vmval010);
        byte vmval001 = Serial.read();	// bit 1
        //Serial.println(vmval001);
        
        //Suma los bits y resta 48 debido a la tabla ASCII
        byte vmPWM = ((vmval100-48) *100) + ((vmval010-48) *10) + (vmval001-48);
        //Limita los valores dentro de 0 y 255
        constrain(vmPWM,0,255);	
        
        Serial.print("Rojo: ");	//Imprime
        Serial.println(vmPWM);
        analogWrite(ledvm,vmPWM);//Setea PWM
      }  
      else if (c == 'g')						
      { // caso g minuscula
        byte vdval100 = Serial.read();			// bit 100
        byte vdval010 = Serial.read();			// bit 10
        byte vdval001 = Serial.read();			// bit 1
       	
        //Suma los bits y resta 48 debido a la tabla ASCII
        byte vdPWM = ((vdval100-48) *100) + ((vdval010-48) *10) + (vdval001-48);
        constrain(vdPWM,0,255);//Limita os valores dentro de 0 - 255
        
        Serial.print("Verde: ");				//Imprime
        Serial.println(vdPWM);
        analogWrite(ledvd,vdPWM); //Setea PWM
      }
      else if (c == 'b')						
      {
        byte azval100 = Serial.read();			//Lê o bit 100
        byte azval010 = Serial.read();			//Lê o bit 10
        byte azval001 = Serial.read();			//Lê o bit 1
        										//Soma os bits e subtrai 48 por causa da tabela ASCII
        byte azPWM = ((azval100-48) *100) + ((azval010-48) *10) + (azval001-48);
        constrain(azPWM,0,255);	
        
        Serial.print("Azul: ");	//Imprime
        Serial.println(azPWM);
        analogWrite(ledaz,azPWM);	// setea pwm
      }
      else if (c == '0')
      {
        digitalWrite(ledvm,LOW);
        digitalWrite(ledvd,LOW);
        digitalWrite(ledaz,LOW);
        Serial.println("Apagar todo");
      }
      else if (c == '?')
      {
        Serial.println("Ingrese r, g o la letra ");
        Serial.println("Seguido de tres digitos sin espacio.");
        Serial.println("O 0 para apagar el led.");
        Serial.println("-------");
      }
    }
  // el LED 2 muestra colores aleatorios
  analogWrite(ledvm2, random(0,256));
  analogWrite(ledvd2, random(0,256));
  analogWrite(ledaz2, random(0,256));
  
  delay(100);
}