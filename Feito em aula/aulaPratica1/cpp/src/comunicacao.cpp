/*
 * comunicacao.cpp
 *
 *  Created on: 08/10/2015
 *      Author: randler
 */

#include <stdlib.h>
#ifdef __linux__
#include <stdio.h>
#include <fcntl.h>
#endif

#include "../include/Comunicacao.h"

Comunicacao:: Comunicacao(char* por){
	hPorta = 0;
	this->porta = porta;
}

int Comunicacao::iniciar(){
	int resultado = EXIT_SUCCESS;
#ifdef _WIN32 || _WIN64
	hPorta = CreateFile(porta, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN _EXISTING, 0, NULL);
	if(hPorta == INVALID_HANDLE_VALUE){
		resultado = GetLastError();
	}else{
		//Configuracao da porta
		DCB dcb;
		memset(&dcb, 0, sizeof(dcb));
		dcb.DCblength = sizeof(dcb);
		dcb.BaudRate = CBR_9600;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.ByteSize = 8;

		if(!SetCommState(hPorta, &dcb)){
			resultado = GetLastError();
		}
	}
#endif

#ifdef __linux__
	hPorta = open(porta, O_RDWR | O_NOCTTY | O_NDELAY);
	if(hPorta == 1){
		resultado = EXIT_FAILURE;
	}else{
		fcntl(hPorta, F_SETFL, 0);
	}

#endif

	sleep(2000);

	return resultado;

}


int Comunicacao::ler(char* buffer,
		long unsigned int  bytesParaLer){
	int resultado = EXIT_FAILURE;
	long unsigned int bytesLidos;

#ifdef _WIN32 || _WIN64
	ReadFile(hPorta, buffer, bytesParaLer, &bytesLidos, NULL);
#endif

#ifdef __linux__
	bytesLidos = read(hPorta, (void*)buffer, bytesParaLer);
#endif

	if(bytesLidos == bytesParaLer){
		resultado = EXIT_SUCCESS;
	}

	return resultado;
}

int Comunicacao::finalizar(){

#ifdef _WIN32 || _WIN64
	CloseHandle(hPorta);
#endif

#ifdef __linux__
	// Tem que fechar a Conta!
#endif
}
