/*
 * AppModem.c
 *
 *  Created on: 10/12/2022
 *      Author: ggaleano
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "stdbool.h"
#include "modem.h"
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "alarma.h"
#include "AppModem.h"
#include "botones.h"
#include "sensor_temperatura.h"



//Constantes
#define CNTRL_Z 0x1A // fin de cadena de SMS o Publicacion

// Prototipos
char Teclas_CambianEstado(void);
char Mod_Snd_Tmr(char *cmd2Send,unsigned char dlyCmd);

// Variables Globales en RAM.
extern volatile uint8_t rx_ring_buffer[RX_RING_BUFFER_SIZE];
//extern volatile valor_temp1
char var_topic[24];
uint32_t vbleTime=0;
uint32_t cont_temp=0;
int cont = 30;
int32_t nroBytesEnBuffer;
int32_t numeroDeBytesDisponiblesEnBufferRx(void);
float temperatura_sens1;
#define nroByRx numeroDeBytesDisponiblesEnBufferRx

static char appSmsSt;
enum{
	MODEM_OFF, 				// AT+CFUN=0 // Apago y espero 3 Segs
	MODEM_CFG_APN, 	 		// AT+CGDCONT=1,"IP","internet.comcel.com.co"  // y espero 2 Segs  // Configura APN CLARO
	MODEM_ON,  		 		// AT+CFUN=1 // enciende y espera 5 Segs
	MODEM_PIN,  		 	// AT+CPIN? // Mando y espero RX READY , sino volver al estado de entender
	MODEM_CHK_PIN_READY,  	// espera recibir READY
	MODEM_WAIT_KEYS,		// Esperando cambio de teclas
	MODEM_ASK_IP,
	MODEM_ACT_OK,
	MODEM_CONN_MQTT,
	MODEM_CONN_TOPIC,
	MODEM_PUBLIC_DATO,
	MODEM_FIN_MENSAJE,
	MODEM_BUCLE_MENSAJE,
	MODEM_MQTT_RECV,
	MODEM_CHK_REG,    		// AT+CREG?  // Mando y espero Registro "0,1" Home y espero 2 Segs
	MODEM_WAIT_KEY,	 		// Espera Tecla presionada
	MODEM_CFG_TEXT,	 		// AT+CMGF=1  // Configura para SMS en modo Texto
	MODEM_SMS_TEL,	 		// AT+CMGS="nroTel" // Envia mensaje a Tel y espera ">"
	MODEM_MSG		 		// "mensaje" CTRL Z (0x1A) // "CMGS:"
};

/* Parametros del tiempo del modem EC200T de Quectel */

#define TIME_OFF_MODEM 			4 	//[=] Segs que espera para que el modem apague
#define TIME_CFG_APN			2  	//[=] Segs que ...
#define TIME_MODEM_ON			3  	//[=] Segs que ...
#define TIME_WAIT_PIN			4  	//[=] Segs que espera rta al comando de SIM
#define MODEM_TIME_WT_IP		6  	//[=] Segs que espera tener una IP (typ 4 Segs)
#define MODEM_WAIT_CONN_MQTT 	8 	//[=] Segs Tiempo maximo que se tarda la conexion al MQTT Server
#define MODEM_WAIT_CONN_TOPIC   5

void AplicacionModem_Init(void){
	/*!!! Generar el pulso en el PIN de PWRKEY
	varios pulsos: 5 con separacion de 5 segs cada/segs*/
	Mod_Snd_Tmr("ATE0\r\n",2); // Quitar Eco Local.
	appSmsSt = MODEM_OFF;
}

char Modem_Respuesta_OK(char *rtaOk){
	if(strstr((char*)rx_ring_buffer,rtaOk)){
		return 1;
	}else{
		return 0;
	}
}

char Mod_Snd_Tmr(char *cmd2Send,unsigned char dlyCmd){
	if(Alarma_Elapsed(vbleTime)){
		ClearBufRx();
		Modem_Send_Cmd(cmd2Send);
		vbleTime = Alarma_Set(dlyCmd);
		return 1;
	}else{
		return 0;
	}

}


/*Funcion de Aplicacion*/ 
void AplicacionModem_Run(void){
//static char keyCh; //Estatica
	//valor_temp();
	temperatura_sens1 = valor_temp();
	switch(appSmsSt){
		case MODEM_OFF:
			if(Mod_Snd_Tmr("AT+CFUN=0\r\n",TIME_OFF_MODEM)) appSmsSt = MODEM_CFG_APN;
		break;
		case MODEM_CFG_APN: 
			if(Mod_Snd_Tmr("AT+CGDCONT=1,\"IP\",\"internet.comcel.com.co\"\r\n",TIME_CFG_APN)) appSmsSt = MODEM_ON; 
		break;
		case MODEM_ON:
			if(Mod_Snd_Tmr("AT+CFUN=1\r\n",TIME_MODEM_ON)) appSmsSt = MODEM_PIN;
		break;
		case MODEM_PIN:
			if(Mod_Snd_Tmr("AT+CPIN?\r\n",TIME_WAIT_PIN)) appSmsSt = MODEM_CHK_PIN_READY;
		break;
		case MODEM_CHK_PIN_READY:
			if(Alarma_Elapsed(vbleTime)){
				nroBytesEnBuffer = numeroDeBytesDisponiblesEnBufferRx();
				rx_ring_buffer[nroBytesEnBuffer] = 0x00; 					// Fin de cadena
				if(Modem_Respuesta_OK("READY")) appSmsSt = MODEM_CHK_REG; 	// La sim esta insertada correctamente
				else{ 														// Existe error en la SIM
					Modem_Respuesta_OK("SIM PIN"); 							// La sim tiene PIN
					Modem_Respuesta_OK("SIM PUK"); 							// La sim requiere PUK solo 1 vez
					Modem_Respuesta_OK("Error 10"); 						// La sim requiere PUK solo 1 vez
					appSmsSt = MODEM_OFF; 									// Intente de nuevo
				}
			}
		break;
		case MODEM_CHK_REG:
			if(Mod_Snd_Tmr("AT+CREG?\r\n",3)){
				if(Modem_Respuesta_OK("0,1")) appSmsSt = MODEM_ASK_IP;
				//if(Modem_Respuesta_OK("0,1")) appSmsSt = MODEM_WAIT_KEYS;

			}
		break;
		/*
		case MODEM_WAIT_KEYS:
			keyCh = Teclas_CambianEstado();
			if(keyCh) appSmsSt = MODEM_ASK_IP;
		break;
		*/
		case MODEM_ASK_IP:
			if(Mod_Snd_Tmr("AT+QIACT=1\r\n",MODEM_TIME_WT_IP)) appSmsSt = MODEM_ACT_OK;
			//!!! AT+QIACT=1 6 segs
			//!!! Esperar OK
			// Al presionar las teclas actualiza estado en el
			// Servidor MQTT  "TeclaSupeDerPress" "TeclaSupeIzqPress"
			//		"TeclaSupeIzqNoPress" "TeclaSupeDerNoPress"
			//
		break;
		case MODEM_ACT_OK:
			if(Alarma_Elapsed(vbleTime)){
				nroBytesEnBuffer = numeroDeBytesDisponiblesEnBufferRx();
				rx_ring_buffer[nroBytesEnBuffer] = 0x00; // fin de cadena
				if(Modem_Respuesta_OK("OK")){ // se tiene IP
					Mod_Snd_Tmr("AT+QMTOPEN=0,\"54.163.179.109\",1883\r\n", MODEM_WAIT_CONN_MQTT);
					appSmsSt = MODEM_CONN_MQTT;
				}else{
					//!!! hay un error de conexion, posible no hay saldo
					appSmsSt = MODEM_ASK_IP;
					//!!! contador de intentos digamos 20, entonces pasar a MODEM_OFF
				}
			}
		break;
		case MODEM_CONN_MQTT:
			if(Alarma_Elapsed(vbleTime)){
				if(Modem_Respuesta_OK("+QMTOPEN: 0,0")){ // Se conecto al MQTT sin problema
					Mod_Snd_Tmr("AT+QMTCONN=0,\"Medicion_temperatura\"\r\n", MODEM_WAIT_CONN_TOPIC);
					appSmsSt = MODEM_CONN_TOPIC;
				}else{
					appSmsSt = MODEM_OFF;
				}
			}
		break;
		case MODEM_CONN_TOPIC:
			if(Alarma_Elapsed(vbleTime)){
				if(Modem_Respuesta_OK("+QMTCONN: 0,0,0") || Modem_Respuesta_OK("+QMTPUB: 0,0,0")){ // Rta a conexion del Topico OK
					Mod_Snd_Tmr("AT+QMTPUB=0,0,0,0,\"Medicion_temperatura\"\r\n",5);
					appSmsSt = MODEM_PUBLIC_DATO;
				}else{
					appSmsSt = MODEM_OFF;
				}
			}
		break;
		case MODEM_PUBLIC_DATO:
			//!!! manda dato y termina con CTL Z y se va a
			if(Alarma_Elapsed(vbleTime)){
				if(Modem_Respuesta_OK(">")){ // Se conecto al MQTT sin problema
					//cont_temp = cont_temp + 5;
					snprintf(var_topic, 24,"temperatura temp=%2.2f",temperatura_sens1);
					//var_topic = "temperatura temp=30";
					//Mod_Snd_Tmr("temperatura temp=%d",cont_temp,3);
					Mod_Snd_Tmr((char *)(&var_topic),3);
					appSmsSt = MODEM_FIN_MENSAJE;
				}else {
					appSmsSt = MODEM_OFF;
				}
			}
		break;
		case MODEM_FIN_MENSAJE:
			if(Alarma_Elapsed(vbleTime)){
				putchar(CNTRL_Z);
				Mod_Snd_Tmr("\r\n",1);
				appSmsSt = MODEM_CONN_TOPIC;
			}
		break;
		/*
		case MODEM_BUCLE_MENSAJE:
			if(Modem_Respuesta_OK("+QMTPUB: 0,0,0")){ // El mensaje se envió al MQTT sin problema
				appSmsSt = MODEM_CONN_TOPIC;
			}else {
				appSmsSt = MODEM_OFF;
			}

			//!!!!	recibir mensajes del MQTT Server + QMTRECV : 0,0,"LAB1","led on"
		break;
		*/
		case MODEM_CFG_TEXT:
			appSmsSt = MODEM_SMS_TEL;
		break;
		case MODEM_SMS_TEL:
			appSmsSt = MODEM_MSG;
		break;
		case MODEM_MSG:
			appSmsSt = MODEM_WAIT_KEY;
		break;
		default:
			appSmsSt = MODEM_OFF;
		break;
	}
}

