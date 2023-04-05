#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Adafruit_ADS1115 ads(0x48);
  
const float FACTOR = 30; //30A/1V
const float multiplier = 0.0625F;

int cont = 0;

const int RESOLUTION_BITS = 9; // Resolución de 9 bits (512 valores posibles)

int binArray[9]; // Creamos un array de enteros para almacenar los bits

int PWM_OUT_VENT = 11;   // Gris
int PWM_OUT_BOMBA = 10;  // Verde
float Valor_salida_pwm;
float Valor_salida_pwm_bomb;
float cv_a = 0;
float cv_b = 0;
float suma;
float autoSave;


int Valor_watts_nxp = 0;
int inPin = A0; // pin de salida analógica
int x = 0;

void ImprimirMedidas(String prefix, float value, String postfix);

void setup() {

  pinMode(PWM_OUT_VENT,OUTPUT);  
  pinMode(PWM_OUT_BOMBA,OUTPUT);  
  pinMode(inPin,OUTPUT);
  
  /*---------Pines[0-9]->Binarios-------*/     
  pinMode(13,OUTPUT);       // Ultimo bit
  pinMode(12,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);        // Bit más significativo

  Serial.begin(9600);

  sensors.begin();
  sensors.setResolution(12);

  ads.setGain(GAIN_TWO);        // ±2.048V  1 bit = 0.0625mV
  ads.begin();
}

void loop() {

  float CorrienteRMS = getCorriente();
  float Potencia = 110.0 * CorrienteRMS;  

  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.println(temperatureC);

  char temperatureString[8];
  if(x == 0){
    dtostrf(temperatureC, 4, 1, temperatureString);
  }else if(x == 1){
    dtostrf(Potencia, 4, 1, temperatureString);
  }
  //Serial.print("Temperature as string: ");
  //Serial.println(temperatureString);

  int temperatureInt = (int)(atof(temperatureString) * 10);
  //Serial.print("Temperature as integer: ");
  //Serial.println(temperatureInt);

  uint16_t temperatureBinary = (uint16_t)temperatureInt;
  if(x==0){
    Serial.print("Temperatura in binary: ");
  }else if(x == 1){
    Serial.print("Potencia in binary: ");
  }
  for (int i = RESOLUTION_BITS - 1; i >= 0; i--) {
    Serial.print((temperatureBinary >> i) & 1, BIN);
  }
  Serial.println();

  for (int i = 0; i < 9; i++) {
  binArray[i] = (temperatureBinary >> i) & 1; // Almacenamos cada bit en el array
  }
  /*
  for (int i = 0; i < 9; i++) {
  Serial.print(binArray[i]);
  }
  Serial.println();
  */

  digitalWrite(13, binArray[8]);
  digitalWrite(12, binArray[7]);
  digitalWrite(9, binArray[6]);
  digitalWrite(8, binArray[5]);
  digitalWrite(7, binArray[4]);
  digitalWrite(6, binArray[3]);
  digitalWrite(5, binArray[2]);
  digitalWrite(4, binArray[1]);
  digitalWrite(3, binArray[0]);
  digitalWrite(inPin,x);

  ImprimirMedidas("Irms: ", CorrienteRMS, "A ,");
  ImprimirMedidas("Potencia: ", Potencia, "W");


  x++;
  if(x >= 2){
    x = 0;
  }

  suma =0;
  for(int i=0; i<5 ; i++){
    suma = temperatureC + suma;
    delay(200);
  }
  if(temperatureC > 27.2){
    autoSave = 0;
    cv_a = 100.0;
  }else if(temperatureC < 26.6){
    cv_a = 0;
    autoSave = 1;
  }else{
    if(autoSave == 0){
      cv_a = 85.0;
    }else{
      cv_a = 0;
    }
  }

  if(temperatureC > 28.0){
    cv_b = 100.0;
  }else if(temperatureC <= 28.0 && temperatureC >= 27.0){
    cv_b = 80.0;
  }else{
    cv_b = 50.0;
  }
  Valor_salida_pwm = cv_a*(255.0/100.0);
  Valor_salida_pwm_bomb = cv_b*(255.0/100.0);
  analogWrite(PWM_OUT_VENT,Valor_salida_pwm);       //0-255
  analogWrite(PWM_OUT_BOMBA,Valor_salida_pwm_bomb); //0-255

  delay(100);
}

void ImprimirMedidas(String prefix, float value, String postfix)
{
 Serial.print(prefix);
 Serial.print(value, 3);
 Serial.println(postfix);
}

float getCorriente()
{
 float Volt_diferencial;
 float corriente;
 float sum = 0;
 long tiempo = millis();
 int counter = 0;
 
 while (millis() - tiempo < 1000)
 {
   Volt_diferencial = ads.readADC_Differential_0_1() * multiplier;
   
   //-----------------------------------------------------
   //Volt_diferencial = ads.readADC_Differential_2_3() * multiplier;
   //-----------------------------------------------------
   
   corriente = Volt_diferencial * FACTOR;
   corriente /= 1000.0;
 
   sum += sq(corriente);
   counter = counter + 1;
  }
 
 corriente = sqrt(sum / counter);
 return(corriente);
}