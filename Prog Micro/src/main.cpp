#include <Arduino.h>
#include "NimBLEDevice.h"
#include "conf_project.h"
#include <Time.h>
#include <ESP32Time.h>

ESP32Time rtc;
void taskRtc(void *parameter);
int abrirOcerrar = NULL;

//TEMPORZADOR
struct tm fecha = {
  0,    // tm_sec
  0,    // tm_min
  0,    // tm_hour
  1,    // tm_mday
  0,    // tm_mon
  2000,  // tm_year (e.g., 2000)
  6,    // tm_wday (e.g., Saturday)
  0,    // tm_yday
  0     // tm_isdst
};

struct tm fechaReal = {
  0,    // tm_sec
  0,    // tm_min
  0,    // tm_hour
  1,    // tm_mday
  0,    // tm_mon
  2000,  // tm_year (e.g., 2000)
  6,    // tm_wday (e.g., Saturday)
  0,    // tm_yday
  0     // tm_isdst
};

class MyCallbacks: public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic * pCharacteristic) {
    uint8_t value = pCharacteristic->getValue()[0];
    Serial.print("Valor recibido: ");
    Serial.println(value);
    switch(value){
      case 1:
        motor_UP();
        break;
      case 2:
        motor_DOWN();
        break;
      case 3:
        motor_STOP();
        break;
      default:
        motor_STOP();
        break;
      }
  }
};

class Characteristic2Callbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();  // Obtener el valor escrito en la característica
        if (value.length() >= 16)  // Asegurarse de que el valor tenga al menos 5 caracteres (HH:MM)
        {
            // Obtener la hora y los minutos de la cadena recibida
            int horaSelect = std::stoi(value.substr(0, 2));
            int minutoSelect = std::stoi(value.substr(3, 2));

            int horaReal = std::stoi(value.substr(6, 2));
            int minutoReal = std::stoi(value.substr(9, 2));
            int segundosReal = std::stoi(value.substr(12, 2));
            abrirOcerrar = std::stoi(value.substr(15, 1));

            Serial.print("Hora Seleccionada: ");
            Serial.print(horaSelect);
            Serial.print(":");
            Serial.println(minutoSelect);

            Serial.print("Hora Real: ");
            Serial.print(horaReal);
            Serial.print(":");
            Serial.println(minutoReal);
            
            fecha.tm_hour = horaSelect ;
            fecha.tm_min = minutoSelect;

            fechaReal.tm_hour = horaReal ;
            fechaReal.tm_min = minutoReal;
            fechaReal.tm_sec = segundosReal;

            Serial.println(fecha.tm_hour);
            Serial.println(fecha.tm_min);

            Serial.println(fechaReal.tm_hour);
            Serial.println(fechaReal.tm_min);
            Serial.println(fechaReal.tm_sec);

            rtc.setTime(fechaReal.tm_sec, fechaReal.tm_min, fechaReal.tm_hour, 0, 0, 2020);
            Serial.println(rtc.getTime());
            if(!firstRtc){
              firstRtc = true;
                  xTaskCreate(
                    taskRtc,   // Function that should be called
                    "taskRtc", // Name of the task (for debugging)
                    2000,                  // Stack size (bytes)
                    NULL,                  // Parameter to pass
                    0,                     // Task priority
                    NULL                   // Task handle
                );
              Serial.println("Task created.");
            }
        }
    }
};

class Characteristic3Callbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        uint8_t value  = pCharacteristic->getValue()[0];

        if(value >= 0 && value <= 1){
          switch(value){
            case 0:

              if(lluvia == true){
                lluvia = false;
              }else if(lluvia == false){
                Serial.println("El valor de lluvia ya esta en false");
              }

              break;
            case 1:

              if(lluvia == false){
                lluvia = true;
              }else if(lluvia == true){
                Serial.println("El valor de lluvia ya esta en true");
              }

              break;
          }

            EEPROM.write(5, lluvia);
            EEPROM.commit();

        }else{
          Serial.println("El valor introducido es incorrecto");
        }
    }

      void onRead(NimBLECharacteristic *pCharacteristic)
        {
          uint8_t value = static_cast<uint8_t>(lluvia); 

          pCharacteristic->setValue(&value, sizeof(value));   
        }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  NimBLEDevice::init("BIOCLIMATICA");
  NimBLEServer *pServer = NimBLEDevice::createServer();
  NimBLEService *pService = pServer->createService("ABCD");
  NimBLECharacteristic *pCharacteristic = pService->createCharacteristic("1234");

  NimBLECharacteristic *pCharacteristic2 = pService->createCharacteristic("4321");  

  NimBLECharacteristic *pCharacteristic3 = pService->createCharacteristic("1111");  

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello BLE");

  pCharacteristic2->setCallbacks(new Characteristic2Callbacks());

  pCharacteristic3->setCallbacks(new Characteristic3Callbacks());

  pService->start();

  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("ABCD");
  pAdvertising->start();

  configurarPines();
  init_flash();
  Serial.println("Starting up...");
  crearTareaEmparejamiento();
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop()
{
  NimBLEServer *pServer = NimBLEDevice::getServer();
  uint8_t array_ln = 0;
  int i = 0;
  unsigned long t = 0;
  String command = "";

  while (t < 4000 || t > 6000)
  {
    t = pulseIn(RX433, HIGH, 900000); // Devuelve el tiempo en alto del pulso

    if (DEBUG)
    { // For finding AGC timings
      if (t > 3000 && t < 7000)
        Serial.println(t);
    }
  }

  if (true)
  {
    Serial.print("AGC 2: ");
    Serial.println(t);
    // return; // If modifying this code for another protocol, stop here
  }

  if(t > 5300 && t < 6000){
    array_ln = MISANA_COMMAND_BIT_ARRAY_SIZE_MANDO;
    Serial.println("MODO MANDO");
    modoSensor = false;

    // Segundo pulso AGC:
    // LOW between 2300-2600 us

    while (t < 2300 || t > 2600)
    {
      t = pulseIn(RX433, LOW, 900000); // Devuelve el tiempo en bajo del pulso

      if (DEBUG)
      { // For finding AGC timings
        if (t > 2300 && t < 2600)
          Serial.println(t);
      }
    }

    if (DEBUG)
    {
      Serial.print("AGC 2: ");
      Serial.println(t);
      // return; // If modifying this code for another protocol, stop here
    }

    // Tercer pulso AGC:
    // HIGH between 1100-1900 us

    while (t < 1100 || t > 1900)
    {
      t = pulseIn(RX433, HIGH, 900000);

      if (DEBUG)
      { // For finding AGC timings
        if (t > 500 && t < 3000)
          Serial.println(t);
      }
    }

    if (DEBUG)
    {
      Serial.print("AGC 3: ");
      Serial.println(t);
      // return; // If modifying this code for another protocol, stop here
    }

  }else if (t > 4000 && t < 5300){

    array_ln = MISANA_COMMAND_BIT_ARRAY_SIZE_SENSOR;
    Serial.println("MODO SENSOR");
    modoSensor = true;

    if(lluvia == true){
        Serial.println("El sensor esta en true");
    }else if(lluvia == false){
        Serial.println("El sensor esta en false");
    }

  }

  //----------------------------------------------------

  while (i < array_ln) // Comprobamos bit a bit
  {
    t = pulseIn(RX433, HIGH, 900000);

    if (DEBUG)
    {
      Serial.print(i);
      Serial.print(": ");
      Serial.print(t);
      Serial.print(": ");
    }

    if (t > 450 && t < 850)
    { // Found 1
      command += "1";
      if (DEBUG)
        Serial.println("1");
    }
    else if (t > 100 && t < 430)
    { // Found 0
      command += "0";
      if (DEBUG)
        Serial.println("0");
    }
    else
    { // Bit no reconocido, termina
      if (ADDITIONAL)
      {
        Serial.print("INVALID TIMING: ");
        Serial.println(t);
      }
      i = 0;
      break;
    }  

    i++;
  }

    Serial.println(command.substring(0, 65));

  // La longitud correcta d bits es 40, desechamos las malas capturas:
  if (command.length() != array_ln)
  {

    if (ADDITIONAL)
    {
      Serial.print("Bad capture, invalid command length ");
      Serial.println(command.length());
      Serial.println();
    }
  }
  else
  { 
    
    if(modoSensor == false){
      // Si no se ha emparejado ni ha finalizado el tiempo de emparejamiento, se puede enviar la orden de emparejamiento desde el mando
      if (!flagPair && !flagtemp)
      {
        emparejarDispositivo(readChannel(command.substring(16, 20)), readCommandpair(command.substring(20, 24)));
        vTaskDelay(2 / portTICK_PERIOD_MS);
      }
      if ((flagtemp || flagPair) && FlagEnableMotor && !ModoReverse) // En caso de emparejamiento, fin de tiempo de emparejamiento y que el motor esté habilitado captamos la orden
      {
        if ((readChannel(command.substring(16, 20)) == canal_conf) || (readChannel(command.substring(16, 20)) == CHANNEL_15)) // Acepta ordenes del canal emperejado y del 15(ALL)
        {
          readCommand(command.substring(20, 24)); // Traduce la orden del mando a una accion
          if (ADDITIONAL)
          {
            Serial.print("Remote control ID (DEC): ");
            Serial.println(convertBinaryStringToInt(command.substring(0, 16)), DEC);
            Serial.print("Trailing bits: ");
            Serial.println(convertBinaryStringToInt(command.substring(32, 41)), DEC);
          }
        }
      }
    }else if(modoSensor == true){
      if(lluvia == true){
        motor_DOWN();
        Serial.println("CERRANDO POR LLUVIA");
      }else{
        Serial.println("CERRAR POR LLUVIA DESACTIVADO");
      }
    }

  }

vTaskDelay(2 / portTICK_PERIOD_MS);
  

}

// Funcion de comprobacion de canal previamente emparejado
void init_flash(void)
{
  static uint8_t flash_init = 0x00;
  flash_init = EEPROM.read(2);

  vTaskDelay(2 / portTICK_PERIOD_MS);
  Serial.println("flash_init:" + String(flash_init));
  // En caso de que no se haya emparejado previamente, se sasigna el canal 1 por defecto
  if (flash_init == 0)
  {
    EEPROM.write(0, canal_conf);
    EEPROM.commit();
    EEPROM.write(2, 0x01);
    EEPROM.commit();
    EEPROM.write(5, lluvia);
    EEPROM.commit();
    Serial.println("flash no");
  }
  else
  {
    canal_conf = EEPROM.read(0);
    lluvia = EEPROM.read(5);
    Serial.println("flash ok");
  }
}

// Lectura del canal de la trama
int readChannel(String channel)
{
  int c = convertBinaryStringToInt(channel);

  switch (c)
  {
  case CHANNEL_01: // 1000
    return CHANNEL_01;

  case CHANNEL_02: // 0100
    return CHANNEL_02;

  case CHANNEL_03: // 1100
    return CHANNEL_03;

  case CHANNEL_04: // 0010
    return CHANNEL_04;

  case CHANNEL_05: // 1010
    return CHANNEL_05;

  case CHANNEL_06: // 0110
    return CHANNEL_06;

  case CHANNEL_07: // 1110
    return CHANNEL_07;

  case CHANNEL_08: // 0001
    return CHANNEL_08;

  case CHANNEL_09: // 1001
    return CHANNEL_09;

  case CHANNEL_10: // 0101
    return CHANNEL_10;

  case CHANNEL_11: // 1101
    return CHANNEL_11;

  case CHANNEL_12: // 0011
    return CHANNEL_12;

  case CHANNEL_13: // 1011
    return CHANNEL_13;

  case CHANNEL_14: // 0111
    return CHANNEL_14;

  case CHANNEL_15: // 1111
    return CHANNEL_15;
  }
  return 0;
}
// Lectura de la orden en la trama
String readCommand(String command)
{
  int c = convertBinaryStringToInt(command);

  switch (c)
  {
  case 0x8: // 1000
    FinalAvance = false;
    motor_DOWN();
    Serial.println("CERRANDO POR MANDO");
    return COMMAND_DOWN;

  case 0x3: // 0011
    FinalRetroceso = false;
    motor_UP();
    Serial.println("ABRIENDO POR MANDO");
    return COMMAND_UP;

  case 0xA: // 1010
    motor_STOP();
    Serial.println("PARANDO POR MANDO");
    return COMMAND_STOP;

  case 0x2: // 0010
    // Serial.println("COMMAND PAIR");
    return COMMAND_PAIR;

  case 0x4: // 0100
    // Serial.println("PROGRAM LIMITS (L)");
    return "PROGRAM LIMITS (L)";

  case 0x1: // 0001
    // Serial.println("CHANGE DIRECTION OF ROTATION (STOP + L)");
    return "CHANGE DIRECTION OF ROTATION (STOP + L)";
  }
  //}
  ESP_LOGI(TAG, "UNKNOWN");
  return "UNKNOWN";
}

String readCommandpair(String command)
{
  int c = convertBinaryStringToInt(command);

  switch (c)
  {
  case 0x8: // 1000
    return COMMAND_DOWN;

  case 0x3: // 0011
    return COMMAND_UP;

  case 0xA: // 1010
    return COMMAND_STOP;

  case 0x2: // 0010
    Serial.println("COMMAND PAIR");
    return COMMAND_PAIR;

  case 0x4: // 0100
    Serial.println("PROGRAM LIMITS (L)");
    return "PROGRAM LIMITS (L)";

  case 0x1: // 0001
    Serial.println("CHANGE DIRECTION OF ROTATION (STOP + L)");
    return "CHANGE DIRECTION OF ROTATION (STOP + L)";
  }
  //}
  ESP_LOGI(TAG, "UNKNOWN");
  return "UNKNOWN";
}
// Deteccion del modelo de mando (NO se usa)
String printRemoteModel(String model)
{
  int c = convertBinaryStringToInt(model);

  switch (c)
  {

  case 0x86: // 10000110
    return "BF-305 (5 channels)";

  case 0x3: // 00000011
    return "BF-101 (single channel)";

  case 0x83: // 10000011
    return "BF-301 (single channel)";
  }
  return "UNKNOWN/NEW";
}
// Convierte la trama en string binario a un entero
long convertBinaryStringToInt(String s)
{
  int c = 0;
  long b = 0;

  for (int i = 0; i < s.length(); i++)
  {
    c = convertStringToInt(s.substring(i, i + 1));
    b = b << 1;
    b += c;
  }

  return b;
}

int convertStringToInt(String s)
{
  char carray[2];
  int i = 0;

  s.toCharArray(carray, sizeof(carray));
  i = atoi(carray);

  return i;
}
// Funcion de emparejamiento
void emparejarDispositivo(int canal, String orden)
{
  Serial.println("Emparejando....");
  if (orden == COMMAND_PAIR)
  {
    // Serial.println("canal a guardar: " + canalesString[canal - 1]);
    // EEPROM.write(0, canal);
    // canal_conf = EEPROM.read(0);
    // EEPROM.commit();
    if ((canal == canal_conf) || (canal == CHANNEL_15)) // Si recibe una orden de emparejamiento del canal previamente emparejado o del canal 15
    {                                                   // Se activa el flag de emparejamiento ya finalizado
      flagPair = true;
      // Serial.println("Device already pair");
    }
    else
    {
      canal_conf = canal;
      EEPROM.write(0, canal_conf);
      EEPROM.commit();
      // Serial.println("Device succesfully paired to channel: " + canalesString[canal - 1]);
      digitalWrite(BUZZER, 1);
      vTaskDelay(20 / portTICK_PERIOD_MS);
      digitalWrite(BUZZER, 0);
    }
  }
  else
  {
    if ((canal == canal_conf) || (canal == CHANNEL_15))
    {
      flagPair = true;
      Serial.println("Device already pair");
    }
  }
}

// Temporizador del modo emparejamiento
void timer_Emparejamiento(void *parameter)
{
  Serial.println("modo emparejamiento: start");
  while (contadorEmparejamiento < MAXTEmparejamiento && !flagPair)
  {
    contadorEmparejamiento++;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  Serial.println("Channel Pairing Timout");
  flagtemp = true;
  crearModoFallo();
  vTaskDelete(NULL);
}

// Lectura de señal de comando del maestro
void ReadPulse(uint8_t contador)
{
  switch (contador)
  {
  case 1: // 1 Pulso detectado
    FinalRetroceso = false;
    motor_UP();
    break;
  case 2:
    FinalAvance = false;
    motor_DOWN();
    break;
  case 3:
    motor_STOP();
    break;
  }
}

void configurarPines(void)
{
  EEPROM.begin(EEPROM_SIZE);
  pinMode(RX433, INPUT);
  pinMode(PIN_DEBUG, OUTPUT);
  pinMode(MOTOR_BACKWARD, OUTPUT);
  pinMode(MOTOR_FORWARD, OUTPUT);
  pinMode(ENABLE_SIGNAL, INPUT);

  // Pin entradas señales sensor motor
  gpio_config_t i_conf_2;
  i_conf_2.pin_bit_mask = GPIO_PULSE_SIGNAL; // which pins to apply config to
  i_conf_2.mode = GPIO_MODE_INPUT;           // set as input mode
  i_conf_2.intr_type = GPIO_INTR_DISABLE;
  i_conf_2.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down
  i_conf_2.pull_up_en = GPIO_PULLUP_DISABLE;     // enable pull-up
  gpio_config(&i_conf_2);

  pinMode(KO_SIGNAL, OUTPUT);
  digitalWrite(KO_SIGNAL, 0);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0);
  digitalWrite(MOTOR_BACKWARD, 0);
  digitalWrite(MOTOR_FORWARD, 0);
//*
  xTaskCreate(               // Tarea deteccion de señal
      motor_signal_detect,   // Function that should be called
      "motor_signal_detect", // Name of the task (for debugging)
      2000,                  // Stack size (bytes)
      NULL,                  // Parameter to pass
      0,                     // Task priority
      NULL                   // Task handle
  );
  Serial.println("Task created.");
  //*/
}

void crearModoFallo(void)
{
  //*
  xTaskCreate(            // Tarea lectura entrada pin Enable
      Modo_Fallo_Motor,   // Function that should be called
      "Modo_Fallo_Motor", // Name of the task (for debugging)
      2000,               // Stack size (bytes)
      NULL,               // Parameter to pass
      0,                  // Task priority
      NULL                // Task handle
  );
  //*/
}

void crearModoReverse(void)
{
  xTaskCreate(         // Tarea invierte polaridad motor
      motor_reverse,   // Function that should be called
      "motor_reverse", // Name of the task (for debugging)
      2000,            // Stack size (bytes)
      NULL,            // Parameter to pass
      0,               // Task priority
      NULL             // Task handle
  );
}

void crearTareaEmparejamiento(void)
{
  xTaskCreate(                // Tarea invierte polaridad motor
      timer_Emparejamiento,   // Function that should be called
      "timer_Emparejamiento", // Name of the task (for debugging)
      2000,                   // Stack size (bytes)
      NULL,                   // Parameter to pass
      0,                      // Task priority
      NULL                    // Task handle
  );
}

// Funcion de avance del motor
void motor_UP(void)
{ // Comprueba que no se hayan detectado fallos en el motor, ni fallo en otra unidad ni que el motor ya esté en movimiento en esa direccion
  if (!flagFalloMotor && FlagEnableMotor && !flagUp ) //!flagFalloMotor && FlagEnableMotor && !flagUp && !ModoReverse
  {
    if (!FinalAvance) // Comprobar que no haya llegado al final de carrera
    {
      if (!ModoReverse) // Comprobar que no esté el motor ejecutando la maniobra de comprobacion del motor
      {
        if (FinalRetroceso == true) // resetea el flag de final de carrera en el retroceso
          FinalRetroceso = false;      
      }
      flagUp = false;
      flagDown = false;

      digitalWrite(MOTOR_BACKWARD, 0);
      digitalWrite(MOTOR_FORWARD, 0);
      // Delay para sincronizar movimiento del motor con el se los esclavos
      vTaskDelay(300 / portTICK_PERIOD_MS);
      // Toma de nivel de referencia de la señal de pulso de los motores
      lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
      lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
      lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
      lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);
      // Poner el motor en funcionamiento
      digitalWrite(MOTOR_FORWARD, 1);
      vTaskDelay(20 / portTICK_PERIOD_MS); // Delay para dar tiempo a que la señal de pulsos sea estable antes de realizar la deteccion
      flagUp = true;                       // Flag del sentido del movimiento del motor
      flagDown = false;
    }
  }
}
void motor_UP_reverse(void)
{ // Comprueba que no se hayan detectado fallos en el motor, ni fallo en otra unidad ni que el motor ya esté en movimiento en esa direccion
  if (!flagFalloMotor && FlagEnableMotor && !flagUp)
  {
    if (!FinalAvance) // Comprobar que no haya llegado al final de carrera
    {
      if (!ModoReverse) // Comprobar que no esté el motor ejecutando la maniobra de comprobacion del motor
      {
        if (FinalRetroceso == true) // resetea el flag de final de carrera en el retroceso
          FinalRetroceso = false;        
      }
      flagUp = false;
      flagDown = false;

      digitalWrite(MOTOR_BACKWARD, 0);
      digitalWrite(MOTOR_FORWARD, 0);
      // Delay para sincronizar movimiento del motor con el se los esclavos
      vTaskDelay(300 / portTICK_PERIOD_MS);
      // Toma de nivel de referencia de la señal de pulso de los motores
      lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
      lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
      lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
      lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);
      // Poner el motor en funcionamiento
      digitalWrite(MOTOR_FORWARD, 1);
      vTaskDelay(20 / portTICK_PERIOD_MS); // Delay para dar tiempo a que la señal de pulsos sea estable antes de realizar la deteccion
      flagUp = true;                       // Flag del sentido del movimiento del motor
      flagDown = false;
    }
  }
}
// Funcion de retroceso del motor
void motor_DOWN(void)
{
  if (!flagFalloMotor && FlagEnableMotor && !flagDown)
  {

    if (!FinalRetroceso)
    {
      if (!ModoReverse)
      {
        if (FinalAvance == true)
          FinalAvance = false;  
      }
      flagUp = false;
      flagDown = false;

      digitalWrite(MOTOR_BACKWARD, 0);
      digitalWrite(MOTOR_FORWARD, 0);

      vTaskDelay(300 / portTICK_PERIOD_MS);
      lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
      lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
      lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
      lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);

      digitalWrite(MOTOR_BACKWARD, 1);
      vTaskDelay(20 / portTICK_PERIOD_MS);
      flagDown = true;
      flagUp = false;
    }
  }
}
void motor_DOWN_reverse(void)
{
  if (!flagFalloMotor && FlagEnableMotor && !flagDown)
  {

    if (!FinalRetroceso)
    {
      if (!ModoReverse)
      {
        if (FinalAvance == true)
          FinalAvance = false;
      }
      flagUp = false;
      flagDown = false;

      digitalWrite(MOTOR_BACKWARD, 0);
      digitalWrite(MOTOR_FORWARD, 0);

      vTaskDelay(300 / portTICK_PERIOD_MS);
      lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
      lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
      lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
      lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);

      digitalWrite(MOTOR_BACKWARD, 1);
      vTaskDelay(20 / portTICK_PERIOD_MS);
      flagDown = true;
      flagUp = false;
    }
  }
}
// Funcion de parada del motor
void motor_STOP(void)
{

  if (FlagEnableMotor && !ModoReverse)
  {    
    flagUp = false;
    flagDown = false;
    digitalWrite(MOTOR_BACKWARD, 0);
    digitalWrite(MOTOR_FORWARD, 0);
  }
}
void motor_STOP_reverse(void)
{
  flagUp = false;
  flagDown = false;
  digitalWrite(MOTOR_BACKWARD, 0);
  digitalWrite(MOTOR_FORWARD, 0);
}

// tarea deteccion de señal
void motor_signal_detect(void *parameter)
{
  while (1)
  {
    if (flagUp || flagDown) // Deteccion de la señal unicamente durante el funcionamiento de los motores
    {                       // Lecturas de las señales de pulsos de los motores para comparar con la referencia
      lecturaActual[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
      lecturaActual[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
      lecturaActual[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
      lecturaActual[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);

      for (uint8_t i = 0; i < 4; i++)
      { // Comparacion de valores de la señal de pulso en los 4 motores
        if (lecturaActual[i] != lecturaPrevia[i])
        { // Comparacion contador cambio de nivel con el valor máximo
          if (contadorNivel[i] >= max_lecturas_nivel)
          {                              // Deteccion positiva de cambio de nivel
            flagGoodSignalPar[i] = true; // Flag señal pulsos correcta de cada motor
            contadorNivel[i] = 0;
            lecturaPrevia[i] = lecturaActual[i]; // Actualizamos el nivel de referencia de la señal de pulsos
            contadorNivelConsecutivo[i] = 0;
          }
          contadorNivel[i]++;
        }
        else
        { // No deteccion de cambio de nivel de la señal de pulsos
          contadorNivelConsecutivo[i]++;
          contadorNivel[i] = 0;
        }
      }
      // Flag deteccion señal de pulsos correcta con al menos una deteccion correcta de cada motor
      if ((flagGoodSignalPar[0] || flagGoodSignalPar[1]) && (flagGoodSignalPar[2] || flagGoodSignalPar[3]))
      {
        flagGoodSignal = true;
        prueba = true;

        flagGoodSignalPar[0] = 0;
        flagGoodSignalPar[1] = 0;
        flagGoodSignalPar[2] = 0;
        flagGoodSignalPar[3] = 0;
      }
      // Mala deteccion de señal de pulsos de ambas señales de al menos un motor se toma como fallo
      if (((contadorNivelConsecutivo[0] >= max_lecturas_ciclo) && (contadorNivelConsecutivo[1] >= max_lecturas_ciclo)) || ((contadorNivelConsecutivo[2] >= max_lecturas_ciclo) && (contadorNivelConsecutivo[3] >= max_lecturas_ciclo)))
      {

        contadorNivel[0] = 0;
        contadorNivel[1] = 0;
        contadorNivelConsecutivo[0] = 0;
        contadorNivelConsecutivo[1] = 0;

        contadorNivel[2] = 0;
        contadorNivelConsecutivo[2] = 0;
        contadorNivel[3] = 0;
        contadorNivelConsecutivo[3] = 0;
        flagGoodSignal = false;
        // Primera deteccion de fallo activa el modo reverse
        if (contadorFallo < 1)
        {
          contadorFallo++;
          ModoReverse = true;
          crearModoReverse();
        }
      }
    }
    ets_delay_us(500);
  }
}
// Tarea de ejecucion de maniobra de comprobacion del motor
void motor_reverse(void *parameter)
{
  // Invierte la direccion del motor
  if (flagUp)
  {
    motor_DOWN();
  }
  else if (flagDown)
  {
    motor_UP();
  }
  // Inicializa flag para asegurar la segunda deteccion correcta de la señal de pulsos del motor
  prueba = false;
  // Delay para permitir que se estabilice la señal de pulsos del motor
  vTaskDelay(10 / portTICK_PERIOD_MS);
  // Reseteo de las variables de conteo
  contadorTimer0 = 0;
  contadorTimer1 = 0;
  contadorNivelConsecutivo[0] = 0;
  contadorNivelConsecutivo[1] = 0;
  contadorNivelConsecutivo[2] = 0;
  contadorNivelConsecutivo[3] = 0;

  while (1)
  { // Mientras la deteccion de la señal sea positiva mantenemos el motor activo durante un tiempo designado en MAXTimer0
    if (flagGoodSignal)
    {
      if ((contadorTimer0 < MAXTimer0) && !prueba)
      {
        contadorNivelConsecutivo[0] = 0;
        contadorNivelConsecutivo[1] = 0;
        contadorNivelConsecutivo[2] = 0;
        contadorNivelConsecutivo[3] = 0;
        contadorTimer0++;
      }
      else
      {
        // finaliza el tiempo por lo que el motor ha llegado al final de carrera retroceso
        if (flagUp)
        {
          FinalAvance = false;
          FinalRetroceso = true;
        } // finaliza el tiempo por lo que el motor ha llegado al final de carrera avance
        if (flagDown)
        {
          FinalAvance = true;
          FinalRetroceso = false;
        }
        contadorFallo = 0;
        // La llegar al final de carrera en cualquier sentido se detienen los motores
        if (FinalAvance || FinalRetroceso)
        {
          motor_STOP_reverse();
        }
        else
        {
          if (flagUp)
          {
            motor_DOWN();
          }
          else if (flagDown)
          {
            motor_UP();
          }
        }
        // Desactivamos el modo reverse
        motor_STOP_reverse();
        ModoReverse = false;
        vTaskDelete(NULL);
      }
    }
    else
    { // En caso de no detectar pulsos de los motores se intenta la maniobra de cambio durante más tiempo
      contadorTimer0 = 0;
      if (contadorTimer1 < MAXTimer1)
      {
        contadorTimer1++;
      }
      else
      { // Al terminar el tiempo sin detectar la señal, se activa el flag de fallo del motor
        contadorFallo++;
        contadorTimer1 = 0;
        flagFalloMotor = true; // Flag que informa de deteccion de fallo en esta unidad
        motor_STOP_reverse();
        ModoReverse = false;
        vTaskDelete(NULL);
      }
    }

    vTaskDelay(2 / portTICK_PERIOD_MS);
  }
}
// Tarea de monitorizacion de los fallos
void Modo_Fallo_Motor(void *parameter)
{
  static uint8_t contador = 0;
  static uint8_t contador2 = 0;
  while (1)
  {
    vTaskDelay(20 / portTICK_PERIOD_MS);

    if (flagFalloMotor) // Fallo detectado en esta unidad, detiene el motor y manda señal fallo al siguiente motor
    {
      FlagEnableMotor = false;
      contador2++;
      // Buzzer indicador de fallo en la unidad
      if (contador2 >= 10)
      {
        contador2 = 0;
        digitalWrite(BUZZER, 1);
      }
      else
      {
        digitalWrite(BUZZER, 0);
      }
    }
  }
}

void taskRtc(void *parameter){
  while (true)
  {
    struct tm timeinfo = rtc.getTimeStruct();

    if (timeinfo.tm_hour == fecha.tm_hour){

      if (timeinfo.tm_min == fecha.tm_min){

        if(abrirOcerrar == 0){
          motor_DOWN();
          Serial.println("Cerrando");
          firstRtc = false;
          vTaskDelete(NULL);
        }else if(abrirOcerrar == 1){
          motor_UP();
          Serial.println("Abriendo");
          firstRtc = false;
          vTaskDelete(NULL);
        }else{
          firstRtc = false;
          vTaskDelete(NULL);
        }

      }
    }

    vTaskDelay(5000);

  }
}
