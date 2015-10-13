/*
 * Comunicacao.h
 * Prover uma classe cujos metodos possibilitam
 * comunicacao com um dispositivo controlador
 * que realiza a leitura de sensores de 10 eixos
 *
 *  Created on: 08/10/2015
 *      Author: randler
 */

#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#ifdef _WIN32 || _WIN64
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#define Sleep(x); usleep(x*1000)/
#endif

class Comunicacao{
private:
	char* porta;
#ifdef __linux__
	int hPorta;
#endif
#ifdef _WIN32 || _WIN64
	HANDLE hPorta
#endif


public:
	Comunicacao(char* porta);

	// inicia a comunicacao com a porta
	int iniciar();

	//realiza a leitura de um buffer a partir da porta
	int ler(char* buffer, long unsigned int  bytesParaLer);

	//finaliza o uso da porta serial
	int fnalizar();
};





#endif /* COMUNICACAO_H_ */
