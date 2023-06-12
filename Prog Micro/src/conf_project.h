#pragma once
#include <Arduino.h>
#include <WString.h>
#include <EEPROM.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define EEPROM_SIZE 24
#define PAIRING_TIME 25000000           // In useconds
//#define MY_REMOTE_ID_1                    "0000000000000000"    // Enter your 16 bit remote ID here or make up a binary number and confirm/pair it with the motor
// #define DEFAULT_CHANNEL                     "1000"                // Channel information is only required for multichannel remotes like the BF-305
// #define DEFAULT_REMOTE_MODEL                "10000011"            // We default to BF-301, but this is actually ignored by motors and could be plain zeroes
// #define DEFAULT_TRAILING_BITS               "000000000"           // Last 9 bits of the command. What do they mean? No idea. Again, ignored by motors.
#define COMMAND_DOWN                        "1000"                // Remote button DOWN
#define COMMAND_UP                          "0011"                // Remote button UP
#define COMMAND_STOP                        "1010"                // Remote button STOP
#define COMMAND_PAIR                        "0010"                // Remote button C
#define MISANA_COMMAND_BIT_ARRAY_SIZE_SENSOR       65                // Command bit count
#define MISANA_COMMAND_BIT_ARRAY_SIZE_MANDO        40                // Command bit count
#define CHANNEL_01  0x8
#define CHANNEL_02  0x4
#define CHANNEL_03  0xC
#define CHANNEL_04  0x2
#define CHANNEL_05  0xA
#define CHANNEL_06  0X6
#define CHANNEL_07  0XE
#define CHANNEL_08  0X1
#define CHANNEL_09  0X9
#define CHANNEL_10  0X5
#define CHANNEL_11  0XD
#define CHANNEL_12  0X3
#define CHANNEL_13  0XB
#define CHANNEL_14  0X7
#define CHANNEL_15  0xF

// Plug your 433.92MHz receiver to digital pin 34:
#define RX433 22
#define MOTOR_BACKWARD GPIO_NUM_5
#define MOTOR_FORWARD  GPIO_NUM_18
#define MOTOR_PULSE_SIGNAL_1 GPIO_NUM_15     //P1
#define MOTOR_PULSE_SIGNAL_2 GPIO_NUM_7     //P2
#define MOTOR_PULSE_SIGNAL_3 GPIO_NUM_12     //P3
#define MOTOR_PULSE_SIGNAL_4 GPIO_NUM_14     //P4
//#define MOTOR_PULSE_SIGNAL ((1ULL << MOTOR_PULSE_SIGNAL_1) | (1ULL << MOTOR_PULSE_SIGNAL_2)
#define ENABLE_SIGNAL GPIO_NUM_16
#define KO_SIGNAL GPIO_NUM_13 // GPIO_NUM_9
#define BUZZER GPIO_NUM_23
#define GPIO_MOTOR ((1ULL << MOTOR_BACKWARD) | (1ULL << MOTOR_FORWARD))
#define GPIO_PULSE_SIGNAL ((1ULL << MOTOR_PULSE_SIGNAL_1) || (1ULL << MOTOR_PULSE_SIGNAL_2) || (1ULL << MOTOR_PULSE_SIGNAL_3) || (1ULL << MOTOR_PULSE_SIGNAL_4))
#define GPIO_ENABLE_INPUT 1ULL << ENABLE_SIGNAL
#define KO_SIGNAL_OUTPUT 1ULL << KO_SIGNAL 
//#define GPIO_BUZZER 1ULL << BUZZER

// Enable debug mode if there's no serial output or if you're modifying this code for
// another protocol/device. However, note that serial output delays receiving, causing
// data bit capture to fail. So keep debug disabled unless absolutely required:
#define DEBUG         false
#define ADDITIONAL    false    // Dislay some additional info after capture
#define PIN_DEBUG   GPIO_NUM_2 

static int canal_conf = CHANNEL_01;
// Contador de muestras maestro-esclavo y flag
static int timerAsignacionModo = 200;
static int contadorAsignacionModo = 0;
static int MAXcontadorAsignacionModo = 100;
static bool flagMaestro = false;


//Variable Lluvia
static bool lluvia = false; 

//Variable modo -> Si la variable esta en false es modo mando y si esta en true es modo sensor
static bool modoSensor = false; 

// Variable para saber si no esta inicializado el RTC
static bool firstRtc = false; 

// max medidas de señal del motor
const int max_lecturas_ciclo = 200;
const int max_lecturas_nivel = 0;
static int contadorNivel [4]= {0,0,0,0};
static int contadorNivelConsecutivo[4] = {0,0,0,0};
//flag de emparejamiento de receptor
static bool flagPair = false; 
static bool flagtemp = false;
//Flags de funcionamiento motor
static bool flagUp = false;
static bool flagDown = false;
// Flags de final de carrera de los motores
static bool FinalAvance = false;
static bool FinalRetroceso = false;
//Lecturas señal motor1
static bool lecturaActual[4] = {0,0,0,0};
static bool lecturaPrevia[4] =  {0,0,0,0};
//Flag deteccion de señal cuadrada 
static bool flagGoodSignalPar[4] =  {0,0,0,0};
static bool flagGoodSignal;
static bool prueba;

//Flags fallo motor
static bool flagFalloMotor = false; //Fallo detectado en esta unidad
static bool activacionBuzzer = false;
static bool FlagEnableMotor = true; // (Input) Desabilita motor si detecta fallo en otra unidad
static bool KO_Signal = 0; // (Output) Señal generada por mal funcionamiento de esta unidad
// Flag cambio polaridad motor (final de carrera)
static bool ModoReverse = false ;
static int contadorFallo = 0;
// Contadores para temporizar el modo reverse
static int contadorTimer0 = 0;
static uint16_t contadorTimer1 = 0;
static int MAXTimer0 = 5;   //en ms
static uint16_t MAXTimer1 = 15;   //en ms
// Tiempo entre pitods del buzzer
static int delayBuzzer = 50; //en ms
// Contador de tiempo de emparejamiento
static int contadorEmparejamiento = 0;
// Valor máximo de tiempo de emparejamento
static int MAXTEmparejamiento = 250;
 //static bool flagMotorCambio  = false;
//static int contadorMotorCambio = 0;
const int MaxTimerMotorSolo = 5; 
//static int contadorFlatSignal = 0;

// Funciones configuracion
void configurarPines(void);
void emparejarDispositivo(int , String );
//Tratamiento trama RF
long convertBinaryStringToInt(String);
int convertStringToInt(String );
int readChannel(String );
String readCommand(String );
String readCommandpair(String );
String printRemoteModel(String );

//Funciones control motor
void motor_signal_detect(void *parameter);
void motor_reverse(void *parameter);
void motor_UP(void);
void motor_DOWN(void);
void motor_STOP(void);
void crearModoReverse(void);
void crearModoFallo(void);
void Modo_Fallo_Motor(void *parameter);
void ReadPulse(uint8_t contador);
void timer_Emparejamiento(void *parameter);
void crearTareaEmparejamiento(void);
void init_flash(void);