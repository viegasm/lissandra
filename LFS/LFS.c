/*
 ============================================================================
 Name        : LFS.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "LFS.h"


int main(void) {
	resultado res;
	char* mensaje;
	res.resultado= OK;
	int server_fd;
	iniciar_programa();

	//gestionarConexion();

	while(res.resultado != SALIR)
	{
		mensaje = readline(">");
		res = parsear_mensaje(mensaje);
		if(res.resultado == OK)
		{
			log_info(g_logger,res.mensaje);
		}
		else if(res.resultado == ERROR)
		{
			log_info(g_logger,"Ocurrio un error al ejecutar la acción");
		}
		else if(res.resultado == MENSAJE_MAL_FORMATEADO)
		{
			log_info(g_logger,"Mensaje incorrecto");
		}
		//atender_clientes();
	}

	terminar_programa(&server_fd);

}

void iniciar_programa()
{
	//Inicio el logger
	g_logger = log_create("LFS.log", "LFS", 1, LOG_LEVEL_INFO);
	log_info(g_logger,"Inicio Aplicacion LFS");

	//Inicio las configs
	g_config = config_create("LFS.config");
	log_info(g_logger,"Configuraciones inicializadas");

	//Inicio la memtable
	iniciar_memtable();

	//*server_fd = iniciarServidor(config_get_string_value(g_config,"PUERTO_SERVIDOR"));
	//int clienteMem_fd = esperarCliente(*server_fd,"Se conecto un cliente\n");
}

resultado parsear_mensaje(char* mensaje)
{
	resultado res;
	resultadoParser resParser = parseConsole(mensaje);
	switch(resParser.accionEjecutar){
		case SELECT:
		{
			contenidoSelect* contSel;
			contSel = (contenidoSelect*)resParser.contenido;
			res = select_acc(contSel->nombreTabla,contSel->key);
			break;
		}
		case DESCRIBE:
		{
			contenidoDescribe* contDes = resParser.contenido;
			res = describe(contDes->nombreTabla);
			break;
		}
		case INSERT:
		{
			contenidoInsert* contIns = resParser.contenido;
			res = insert(contIns->nombreTabla,contIns->key,contIns->value,contIns->timestamp);
			break;
		}
		case JOURNAL:
		{
			journal();
			break;
		}
		case CREATE:
		{
			contenidoCreate* contCreate = resParser.contenido;
			res = create(contCreate->nombreTabla,contCreate->consistencia,contCreate->cant_part,contCreate->tiempo_compresion);
			break;
		}
		case DROP:
		{
			contenidoDrop* contDrop = resParser.contenido;
			res = drop(contDrop->nombreTabla);
			break;
		}
		case DUMP:
		{
			res = dump();
			break;
		}
		case ERROR_PARSER:
		{
			res.resultado = MENSAJE_MAL_FORMATEADO;
			res.mensaje = "";
			break;
		}
		case SALIR_CONSOLA:
		{
			res.resultado = SALIR;
			res.mensaje = "";
			break;
		}
		default:
		{
			res.resultado = SALIR;
			res.mensaje = "";
			break;
		}
	}
	return res;

}

resultado select_acc(char* tabla,int key)
{
	resultado res;
	//Hago un select a la memtable
	registro* reg = memtable_select(tabla,key);
	if(reg == NULL){
		res.mensaje="Registro no obtenido";
	}else{
		res.mensaje= string_duplicate(reg->value);
	}

	res.resultado=OK;
	return res;
}

resultado insert(char* tabla,int key,char* value,long timestamp)
{
	//Creo un registro que es con el que voy a llamar a los proyectos
	registro reg;
	reg.key=key;
	reg.value = string_duplicate(value);
	reg.timestamp = timestamp;

	//Llamo al insert
	memtable_insert(tabla,reg);

	//Devuelvo el resultado
	resultado res;
	res.mensaje="Registro insertado exitosamente";
	res.resultado=OK;
	return res;
}

resultado create(char* tabla,char* t_cons,int cant_part,int tiempo_comp)
{
	resultado res;
	res.mensaje="Salida prueba";
	res.resultado=OK;
	return res;
}

resultado describe(char* tabla)
{
	if(tabla != NULL){
		obtenerMetadata(tabla);
	}else{
		obtenerTodasMetadata();
	}
	resultado res;
	res.mensaje="Salida prueba";
	res.resultado=OK;
	return res;
}

resultado drop(char* tabla)
{
	resultado res;
	res.mensaje="Salida prueba";
	res.resultado=OK;
	return res;
}

resultado journal()
{
	if(existeMetadata("colores") == 0){
		metadataTabla masd = obtenerMetadata("colores");
		log_info(g_logger,masd.consistency);
	}
	resultado res;
	res.mensaje="Salida prueba";
	res.resultado=OK;
	return res;
}

resultado dump(){
	resultado res;
	res.mensaje="Salida prueba";
	res.resultado=OK;
	return res;
}

void terminar_programa()
{
	//Destruyo el logger
	log_destroy(g_logger);

	//Destruyo las configs
	config_destroy(g_config);

	//Finalizar programa
	finalizar_memtable();

	//close(*server_fd);
}

void gestionarConexion()
{
	int estado=1;
	char buffer[PACKAGESIZE];

	//int serverLiss_fd = iniciarServidor(config_get_string_value(g_config,"PUERTO_SERVIDOR"));
	//int clienteMem_fd = esperarCliente(serverLiss_fd,"Se conecto la memoria!");

	while(estado){

//		recibir_mensaje(clienteMem_fd,buffer,"La memoria me mando el mensaje");
		//recv(clienteMem_fd, (void*) buffer, PACKAGESIZE, 0);	//Recibo mensaje de la memorias

		if(strcmp(buffer,"exit")==0)
			estado = 0;
		else{
			printf( "\n%s: %s\n","La memoria me mando el mensaje", buffer);
			printf( "Tamaño: %d\n", strlen(buffer));
		}

	}
	/*
    close(clienteMem_fd);
    close(serverLiss_fd);
    */
}

/*int atender_clientes() {
	recibir_mensaje(clienteMem_fd,buffer,"La memoria me mando el mensaje");
}*/
