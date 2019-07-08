/*
 * PoolMem.h
 *
 *  Created on: 29 may. 2019
 *      Author: utnso
 */

#ifndef POOLMEM_H_
#define POOLMEM_H_

#include <commons/collections/list.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/parser.h>
#include <commons/serializacion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

//las puse aca para que no me rompa, buscar un lugar mejor
t_log* g_logger;
t_config* g_config;

int memoriaSocket;			// Almaceno el socket de la memoria para usarlo posteriormente
t_list* socketsPool;

typedef struct{
	char* ipMemoria;
	char* puerto;
	int id;
	int socket;
}Memoria;

// Pool de Memorias
t_list* pool;
Memoria* MemDescribe;

// MANEJO DE MEMORIAS
void obtenerMemorias();
void gossiping(Memoria *mem);
Memoria obtenerMemoria(t_config* config);
Memoria *buscarMemoria(int numero);
void obtenerMemoriaDescribe();

#endif /* POOLMEM_H_ */
