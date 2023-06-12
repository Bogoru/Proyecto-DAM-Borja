#include "conf_project.h"

// void configurarPines(void)
// {
//   EEPROM.begin(EEPROM_SIZE);
//   pinMode(RX433, INPUT);
//   pinMode(MOTOR_BACKWARD, OUTPUT);
//   pinMode(MOTOR_FORWARD, OUTPUT);
//   pinMode(ENABLE_SIGNAL, INPUT);

//   // Pin entradas señales sensor motor
//   gpio_config_t i_conf_2;
//   i_conf_2.pin_bit_mask = GPIO_PULSE_SIGNAL; // which pins to apply config to
//   i_conf_2.mode = GPIO_MODE_INPUT;           // set as input mode
//   i_conf_2.intr_type = GPIO_INTR_DISABLE;
//   i_conf_2.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down
//   i_conf_2.pull_up_en = GPIO_PULLUP_DISABLE;     // enable pull-up
//   gpio_config(&i_conf_2);

//   pinMode(KO_SIGNAL, OUTPUT);
//   digitalWrite(KO_SIGNAL, 0);
//   pinMode(BUZZER, OUTPUT);
//   digitalWrite(BUZZER, 0);
//   digitalWrite(MOTOR_BACKWARD, 0);
//   digitalWrite(MOTOR_FORWARD, 0);

//   xTaskCreate(               // Tarea deteccion de señal
//       motor_signal_detect,   // Function that should be called
//       "motor_signal_detect", // Name of the task (for debugging)
//       2000,                  // Stack size (bytes)
//       NULL,                  // Parameter to pass
//       0,                     // Task priority
//       NULL                   // Task handle
//   );
//   Serial.println("Task created.");
// }

// void crearModoFallo(void)
// {
//   xTaskCreate(            // Tarea lectura entrada pin Enable
//       Modo_Fallo_Motor,   // Function that should be called
//       "Modo_Fallo_Motor", // Name of the task (for debugging)
//       2000,               // Stack size (bytes)
//       NULL,               // Parameter to pass
//       0,                  // Task priority
//       NULL                // Task handle
//   );
// }

// void crearModoReverse(void)
// {
//   xTaskCreate(         // Tarea invierte polaridad motor
//       motor_reverse,   // Function that should be called
//       "motor_reverse", // Name of the task (for debugging)
//       2000,            // Stack size (bytes)
//       NULL,            // Parameter to pass
//       0,               // Task priority
//       NULL             // Task handle
//   );
// }

// void crearTareaEmparejamiento(void)
// {
//   xTaskCreate(                // Tarea invierte polaridad motor
//       timer_Emparejamiento,   // Function that should be called
//       "timer_Emparejamiento", // Name of the task (for debugging)
//       2000,                   // Stack size (bytes)
//       NULL,                   // Parameter to pass
//       0,                      // Task priority
//       NULL                    // Task handle
//   );
// }

// // Funcion de avance del motor
// void motor_UP(void)
// { // Comprueba que no se hayan detectado fallos en el motor, ni fallo en otra unidad ni que el motor ya esté en movimiento en esa direccion
//   if (!flagFalloMotor && FlagEnableMotor && !flagUp && !ModoReverse)
//   {
//     if (!FinalAvance) // Comprobar que no haya llegado al final de carrera
//     {
//       if (!ModoReverse) // Comprobar que no esté el motor ejecutando la maniobra de comprobacion del motor
//       {
//         if (FinalRetroceso == true) // resetea el flag de final de carrera en el retroceso
//           FinalRetroceso = false;
//         if (flagMaestro)
//         {
//           // Genera un pulso para comunicar la orden a los esclavos
//           digitalWrite(KO_SIGNAL, 1);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 0);
//         }
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//       }
//       flagUp = false;
//       flagDown = false;

//       digitalWrite(MOTOR_BACKWARD, 0);
//       digitalWrite(MOTOR_FORWARD, 0);
//       // Delay para sincronizar movimiento del motor con el se los esclavos
//       vTaskDelay(300 / portTICK_PERIOD_MS);
//       // Toma de nivel de referencia de la señal de pulso de los motores
//       lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
//       lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
//       lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
//       lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);
//       // Poner el motor en funcionamiento
//       digitalWrite(MOTOR_FORWARD, 1);
//       vTaskDelay(20 / portTICK_PERIOD_MS); // Delay para dar tiempo a que la señal de pulsos sea estable antes de realizar la deteccion
//       flagUp = true;                       // Flag del sentido del movimiento del motor
//       flagDown = false;
//     }
//   }
// }
// void motor_UP_reverse(void)
// { // Comprueba que no se hayan detectado fallos en el motor, ni fallo en otra unidad ni que el motor ya esté en movimiento en esa direccion
//   if (!flagFalloMotor && FlagEnableMotor && !flagUp)
//   {
//     if (!FinalAvance) // Comprobar que no haya llegado al final de carrera
//     {
//       if (!ModoReverse) // Comprobar que no esté el motor ejecutando la maniobra de comprobacion del motor
//       {
//         if (FinalRetroceso == true) // resetea el flag de final de carrera en el retroceso
//           FinalRetroceso = false;
//         if (flagMaestro)
//         {
//           // Genera un pulso para comunicar la orden a los esclavos
//           digitalWrite(KO_SIGNAL, 1);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 0);
//         }
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//       }
//       flagUp = false;
//       flagDown = false;

//       digitalWrite(MOTOR_BACKWARD, 0);
//       digitalWrite(MOTOR_FORWARD, 0);
//       // Delay para sincronizar movimiento del motor con el se los esclavos
//       vTaskDelay(300 / portTICK_PERIOD_MS);
//       // Toma de nivel de referencia de la señal de pulso de los motores
//       lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
//       lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
//       lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
//       lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);
//       // Poner el motor en funcionamiento
//       digitalWrite(MOTOR_FORWARD, 1);
//       vTaskDelay(20 / portTICK_PERIOD_MS); // Delay para dar tiempo a que la señal de pulsos sea estable antes de realizar la deteccion
//       flagUp = true;                       // Flag del sentido del movimiento del motor
//       flagDown = false;
//     }
//   }
// }
// // Funcion de retroceso del motor
// void motor_DOWN(void)
// {
//   if (!flagFalloMotor && FlagEnableMotor && !flagDown && !ModoReverse)
//   {

//     if (!FinalRetroceso)
//     {
//       if (!ModoReverse)
//       {
//         if (FinalAvance == true)
//           FinalAvance = false;
//         if (flagMaestro)
//         {
//           // Genera dos pulsos para comunicar la orden a los esclavos
//           digitalWrite(KO_SIGNAL, 1);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 0);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 1);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 0);
//         }
//         vTaskDelay(50 / portTICK_PERIOD_MS);
//       }
//       flagUp = false;
//       flagDown = false;

//       digitalWrite(MOTOR_BACKWARD, 0);
//       digitalWrite(MOTOR_FORWARD, 0);

//       vTaskDelay(300 / portTICK_PERIOD_MS);
//       lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
//       lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
//       lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
//       lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);

//       digitalWrite(MOTOR_BACKWARD, 1);
//       vTaskDelay(20 / portTICK_PERIOD_MS);
//       flagDown = true;
//       flagUp = false;
//     }
//   }
// }
// void motor_DOWN_reverse(void)
// {
//   if (!flagFalloMotor && FlagEnableMotor && !flagDown)
//   {

//     if (!FinalRetroceso)
//     {
//       if (!ModoReverse)
//       {
//         if (FinalAvance == true)
//           FinalAvance = false;
//         if (flagMaestro)
//         {
//           // Genera dos pulsos para comunicar la orden a los esclavos
//           digitalWrite(KO_SIGNAL, 1);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 0);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 1);
//           vTaskDelay(10 / portTICK_PERIOD_MS);
//           digitalWrite(KO_SIGNAL, 0);
//         }
//         vTaskDelay(50 / portTICK_PERIOD_MS);
//       }
//       flagUp = false;
//       flagDown = false;

//       digitalWrite(MOTOR_BACKWARD, 0);
//       digitalWrite(MOTOR_FORWARD, 0);

//       vTaskDelay(300 / portTICK_PERIOD_MS);
//       lecturaPrevia[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
//       lecturaPrevia[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
//       lecturaPrevia[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
//       lecturaPrevia[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);

//       digitalWrite(MOTOR_BACKWARD, 1);
//       vTaskDelay(20 / portTICK_PERIOD_MS);
//       flagDown = true;
//       flagUp = false;
//     }
//   }
// }
// // Funcion de parada del motor
// void motor_STOP(void)
// {

//   if (FlagEnableMotor && !ModoReverse)
//   {
//     if (flagMaestro)
//     {
//       // Genera tres pulsos para comunicar la orden a los esclavos
//       digitalWrite(KO_SIGNAL, 1);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 0);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 1);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 0);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 1);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 0);
//     }
//     vTaskDelay(30 / portTICK_PERIOD_MS);
//     flagUp = false;
//     flagDown = false;
//     digitalWrite(MOTOR_BACKWARD, 0);
//     digitalWrite(MOTOR_FORWARD, 0);
//   }
// }
// void motor_STOP_reverse(void)
// {

//   if (FlagEnableMotor && !ModoReverse)
//   {
//     if (flagMaestro)
//     {
//       // Genera tres pulsos para comunicar la orden a los esclavos
//       digitalWrite(KO_SIGNAL, 1);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 0);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 1);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 0);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 1);
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       digitalWrite(KO_SIGNAL, 0);
//     }
//     vTaskDelay(30 / portTICK_PERIOD_MS);
//   }
//   flagUp = false;
//   flagDown = false;
//   digitalWrite(MOTOR_BACKWARD, 0);
//   digitalWrite(MOTOR_FORWARD, 0);
// }

// // tarea deteccion de señal
// void motor_signal_detect(void *parameter)
// {
//   while (1)
//   {
//     if (flagUp || flagDown) // Deteccion de la señal unicamente durante el funcionamiento de los motores
//     {                       // Lecturas de las señales de pulsos de los motores para comparar con la referencia
//       lecturaActual[0] = gpio_get_level(MOTOR_PULSE_SIGNAL_1);
//       lecturaActual[1] = gpio_get_level(MOTOR_PULSE_SIGNAL_2);
//       lecturaActual[2] = gpio_get_level(MOTOR_PULSE_SIGNAL_3);
//       lecturaActual[3] = gpio_get_level(MOTOR_PULSE_SIGNAL_4);

//       for (uint8_t i = 0; i < 4; i++)
//       { // Comparacion de valores de la señal de pulso en los 4 motores
//         if (lecturaActual[i] != lecturaPrevia[i])
//         { // Comparacion contador cambio de nivel con el valor máximo
//           if (contadorNivel[i] >= max_lecturas_nivel)
//           {                              // Deteccion positiva de cambio de nivel
//             flagGoodSignalPar[i] = true; // Flag señal pulsos correcta de cada motor
//             contadorNivel[i] = 0;
//             lecturaPrevia[i] = lecturaActual[i]; // Actualizamos el nivel de referencia de la señal de pulsos
//             contadorNivelConsecutivo[i] = 0;
//           }
//           contadorNivel[i]++;
//         }
//         else
//         { // No deteccion de cambio de nivel de la señal de pulsos
//           contadorNivelConsecutivo[i]++;
//           contadorNivel[i] = 0;
//         }
//       }
//       // Flag deteccion señal de pulsos correcta con al menos una deteccion correcta de cada motor
//       if ((flagGoodSignalPar[0] || flagGoodSignalPar[1]) && (flagGoodSignalPar[2] || flagGoodSignalPar[3]))
//       {
//         flagGoodSignal = true;
//         prueba = true;

//         flagGoodSignalPar[0] = 0;
//         flagGoodSignalPar[1] = 0;
//         flagGoodSignalPar[2] = 0;
//         flagGoodSignalPar[3] = 0;
//       }
//       // Mala deteccion de señal de pulsos de ambas señales de al menos un motor se toma como fallo
//       if (((contadorNivelConsecutivo[0] >= max_lecturas_ciclo) && (contadorNivelConsecutivo[1] >= max_lecturas_ciclo)) || ((contadorNivelConsecutivo[2] >= max_lecturas_ciclo) && (contadorNivelConsecutivo[3] >= max_lecturas_ciclo)))
//       {

//         contadorNivel[0] = 0;
//         contadorNivel[1] = 0;
//         contadorNivelConsecutivo[0] = 0;
//         contadorNivelConsecutivo[1] = 0;

//         contadorNivel[2] = 0;
//         contadorNivelConsecutivo[2] = 0;
//         contadorNivel[3] = 0;
//         contadorNivelConsecutivo[3] = 0;
//         flagGoodSignal = false;
//         // Primera deteccion de fallo activa el modo reverse
//         if (contadorFallo < 1)
//         {
//           contadorFallo++;
//           ModoReverse = true;
//           crearModoReverse();
//         }
//       }
//     }
//     ets_delay_us(500);
//   }
// }
// // Tarea de ejecucion de maniobra de comprobacion del motor
// void motor_reverse(void *parameter)
// {
//   // Invierte la direccion del motor
//   if (flagUp)
//   {
//     motor_DOWN_reverse();
//   }
//   else if (flagDown)
//   {
//     motor_UP_reverse();
//   }
//   // Inicializa flag para asegurar la segunda deteccion correcta de la señal de pulsos del motor
//   prueba = false;
//   // Delay para permitir que se estabilice la señal de pulsos del motor
//   vTaskDelay(10 / portTICK_PERIOD_MS);
//   // Reseteo de las variables de conteo
//   contadorTimer0 = 0;
//   contadorTimer1 = 0;
//   contadorNivelConsecutivo[0] = 0;
//   contadorNivelConsecutivo[1] = 0;
//   contadorNivelConsecutivo[2] = 0;
//   contadorNivelConsecutivo[3] = 0;

//   while (1)
//   { // Mientras la deteccion de la señal sea positiva mantenemos el motor activo durante un tiempo designado en MAXTimer0
//     if (flagGoodSignal)
//     {
//       if ((contadorTimer0 < MAXTimer0) && !prueba)
//       {
//         contadorNivelConsecutivo[0] = 0;
//         contadorNivelConsecutivo[1] = 0;
//         contadorNivelConsecutivo[2] = 0;
//         contadorNivelConsecutivo[3] = 0;
//         contadorTimer0++;
//       }
//       else
//       {
//         // finaliza el tiempo por lo que el motor ha llegado al final de carrera retroceso
//         if (flagUp)
//         {
//           FinalAvance = false;
//           FinalRetroceso = true;
//         } // finaliza el tiempo por lo que el motor ha llegado al final de carrera avance
//         if (flagDown)
//         {
//           FinalAvance = true;
//           FinalRetroceso = false;
//         }
//         contadorFallo = 0;
//         // La llegar al final de carrera en cualquier sentido se detienen los motores
//         if (FinalAvance || FinalRetroceso)
//         {
//           motor_STOP_reverse();
//         }
//         else
//         {
//           if (flagUp)
//           {
//             motor_DOWN();
//           }
//           else if (flagDown)
//           {
//             motor_UP();
//           }
//         }
//         // Desactivamos el modo reverse
//         motor_STOP_reverse();
//         ModoReverse = false;
//         vTaskDelete(NULL);
//       }
//     }
//     else
//     { // En caso de no detectar pulsos de los motores se intenta la maniobra de cambio durante más tiempo
//       contadorTimer0 = 0;
//       if (contadorTimer1 < MAXTimer1)
//       {
//         contadorTimer1++;
//       }
//       else
//       { // Al terminar el tiempo sin detectar la señal, se activa el flag de fallo del motor
//         contadorFallo++;
//         contadorTimer1 = 0;
//         flagFalloMotor = true; // Flag que informa de deteccion de fallo en esta unidad
//         motor_STOP_reverse();
//         ModoReverse = false;
//         vTaskDelete(NULL);
//       }
//     }

//     vTaskDelay(2 / portTICK_PERIOD_MS);
//   }
// }
// // Tarea de monitorizacion de los fallos
// void Modo_Fallo_Motor(void *parameter)
// {
//   static uint8_t contador = 0;
//   static uint8_t contador2 = 0;
//   while (1)
//   {
//     vTaskDelay(20 / portTICK_PERIOD_MS);

//     if (!digitalRead(ENABLE_SIGNAL)) // comprobamos la señal de ENABLE proveniente de al menos una placa esclava
//     {
//       contador++;
//       if (contador > 6)
//       {
//         motor_STOP();
//         FlagEnableMotor = false;
//         digitalWrite(KO_SIGNAL, 1);
//       }
//     }
//     else
//     {
//       contador = 0;
//     }

//     if (flagFalloMotor) // Fallo detectado en esta unidad, detiene el motor y manda señal fallo al siguiente motor
//     {
//       FlagEnableMotor = false;
//       digitalWrite(KO_SIGNAL, 1);
//       contador2++;
//       // Buzzer indicador de fallo en la unidad
//       if (contador2 >= 10)
//       {
//         contador2 = 0;
//         digitalWrite(BUZZER, 1);
//       }
//       else
//       {
//         digitalWrite(BUZZER, 0);
//       }
//     }
//   }
// }
