/*
 * LFS.h
 *
 *  Created on: 11 abr. 2019
 *      Author: utnso
 */

#ifndef LFS_H_
#define LFS_H_

#include "../sockets/sockets.h"

typedef enum
{
	OK,
	SALIR,
	MENSAJE_MAL_FORMATEADO,
	ERROR
}estado;

typedef struct
{
	estado resultado;
	char* mensaje;
} resultado;

t_log* g_logger;
t_config* g_config;


void iniciar_programa(void);
resultado parsear_mensaje(char *);
resultado select_acc(char *,int);
resultado insert(char*,int,char*,long);
resultado create(char*,char*,int,int);
resultado describe(char*);
resultado drop(char*);
resultado journal();

void iniciar_programa(void);
void terminar_programa(void);
void gestionarConexion(void);


#endif /* LFS_H_ */
