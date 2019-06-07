/*
 * serializacion.c
 *
 *  Created on: 4 jun. 2019
 *      Author: viegasm
 */

#include "serializacion.h"

char* serializarPaquete(resultadoParser* rp, int* total_size) {
	int offset = 0;
	int size_to_send;

	switch(rp->accionEjecutar) {
	case(INSERT): {
		int nombreTabla_size;
		int value_size;
		contenidoInsert* ci;
		offset = 0;
		ci = (contenidoInsert *) (rp->contenido);

		*total_size = sizeof(ci->key) + (strlen(ci->nombreTabla) + 1) * sizeof(char)
				+ sizeof(ci->timestamp) + (strlen(ci->value) + 1) * sizeof(char)
				+ sizeof(rp->accionEjecutar) + sizeof(int) + sizeof(value_size) + sizeof(nombreTabla_size);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(*total_size);
		memcpy(paqueteSerializado + offset, total_size, size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(ci->key);
		memcpy(paqueteSerializado + offset, &(ci->key), size_to_send);
		offset += size_to_send;


		value_size = strlen(ci->value) + 1;
		size_to_send = sizeof(value_size);
		memcpy(paqueteSerializado + offset, &value_size, size_to_send);
		offset += size_to_send;


		size_to_send = value_size;
		memcpy(paqueteSerializado + offset, ci->value, size_to_send);
		offset += size_to_send;

		nombreTabla_size = strlen(ci->nombreTabla) + 1;
		size_to_send = sizeof(nombreTabla_size);
		memcpy(paqueteSerializado + offset, &nombreTabla_size, size_to_send);
		offset += size_to_send;


		size_to_send = nombreTabla_size;
		memcpy(paqueteSerializado + offset, ci->nombreTabla, size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(ci->timestamp);
		memcpy(paqueteSerializado + offset, &(ci->timestamp), size_to_send);

		return paqueteSerializado;

		break;
	}
	case(SELECT): {
		int nombreTabla_size;
		contenidoSelect* cs;
		offset = 0;
		cs = (contenidoSelect *) (rp->contenido);

		*total_size = sizeof(rp->accionEjecutar) + sizeof(int)
				+ (strlen(cs->nombreTabla) + 1) * sizeof(char) + sizeof(nombreTabla_size)
				+ sizeof(cs->key);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(*total_size);
		memcpy(paqueteSerializado + offset, total_size, size_to_send);
		offset += size_to_send;


		nombreTabla_size = strlen(cs->nombreTabla) + 1;
		size_to_send = sizeof(nombreTabla_size);
		memcpy(paqueteSerializado + offset, &nombreTabla_size, size_to_send);
		offset += size_to_send;


		size_to_send = nombreTabla_size;
		memcpy(paqueteSerializado + offset, cs->nombreTabla, size_to_send);
		offset += size_to_send;

		size_to_send = sizeof(cs->key);
		memcpy(paqueteSerializado + offset, &(cs->key), size_to_send);
		offset += size_to_send;


		return paqueteSerializado;

		break;
	}
	case(CREATE): {
		int nombreTabla_size;
		int consistencia_size;
		contenidoCreate* cc;
		offset = 0;
		cc = (contenidoSelect *) (rp->contenido);

		*total_size = sizeof(rp->accionEjecutar) + sizeof(int)
				+ (strlen(cc->nombreTabla) + 1) * sizeof(char) + sizeof(nombreTabla_size)
				+ (strlen(cc->consistencia) + 1) * sizeof(char) + sizeof(consistencia_size)
				+ sizeof(cc->cant_part)
				+ sizeof(cc->tiempo_compresion);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(*total_size);
		memcpy(paqueteSerializado + offset, total_size, size_to_send);
		offset += size_to_send;


		nombreTabla_size = strlen(cc->nombreTabla) + 1;
		size_to_send = sizeof(nombreTabla_size);
		memcpy(paqueteSerializado + offset, &nombreTabla_size, size_to_send);
		offset += size_to_send;

		size_to_send = nombreTabla_size;
		memcpy(paqueteSerializado + offset, cc->nombreTabla, size_to_send);
		offset += size_to_send;

		consistencia_size = strlen(cc->consistencia) + 1;
		size_to_send = sizeof(consistencia_size);
		memcpy(paqueteSerializado + offset, &consistencia_size, size_to_send);
		offset += size_to_send;

		size_to_send = consistencia_size;
		memcpy(paqueteSerializado + offset, cc->consistencia, size_to_send);
		offset += size_to_send;

		size_to_send = sizeof(cc->cant_part);
		memcpy(paqueteSerializado + offset, &(cc->cant_part), size_to_send);
		offset += size_to_send;

		size_to_send = sizeof(cc->tiempo_compresion);
		memcpy(paqueteSerializado + offset, &(cc->tiempo_compresion), size_to_send);
		offset += size_to_send;

		return paqueteSerializado;

		break;
	}
	case(DESCRIBE): {
		int nombreTabla_size;
		contenidoDescribe* cd;
		offset = 0;
		cd = (contenidoDescribe *) (rp->contenido);

		*total_size = sizeof(rp->accionEjecutar) + sizeof(int)
				+ (strlen(cd->nombreTabla) + 1) * sizeof(char) + sizeof(nombreTabla_size);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(*total_size);
		memcpy(paqueteSerializado + offset, total_size, size_to_send);
		offset += size_to_send;


		nombreTabla_size = strlen(cd->nombreTabla) + 1;
		size_to_send = sizeof(nombreTabla_size);
		memcpy(paqueteSerializado + offset, &nombreTabla_size, size_to_send);
		offset += size_to_send;

		size_to_send = nombreTabla_size;
		memcpy(paqueteSerializado + offset, cd->nombreTabla, size_to_send);
		offset += size_to_send;

		return paqueteSerializado;

		break;
	}
	case(DROP): {
		int nombreTabla_size;
		contenidoDrop* cd;
		offset = 0;
		cd = (contenidoDrop *) (rp->contenido);

		*total_size = sizeof(rp->accionEjecutar) + sizeof(int)
				+ (strlen(cd->nombreTabla) + 1) * sizeof(char) + sizeof(nombreTabla_size);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(*total_size);
		memcpy(paqueteSerializado + offset, total_size, size_to_send);
		offset += size_to_send;


		nombreTabla_size = strlen(cd->nombreTabla) + 1;
		size_to_send = sizeof(nombreTabla_size);
		memcpy(paqueteSerializado + offset, &nombreTabla_size, size_to_send);
		offset += size_to_send;

		size_to_send = nombreTabla_size;
		memcpy(paqueteSerializado + offset, cd->nombreTabla, size_to_send);
		offset += size_to_send;

		return paqueteSerializado;

		break;
	}
	case(ADD): {
		int criterio_size;
		contenidoAdd* ca;
		offset = 0;
		ca = (contenidoAdd *) (rp->contenido);

		*total_size = sizeof(rp->accionEjecutar) + sizeof(int)
				+ sizeof(ca->numMem)
				+ (strlen(ca->criterio) + 1) * sizeof(char) + sizeof(criterio_size);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;

		size_to_send = sizeof(*total_size);
		memcpy(paqueteSerializado + offset, total_size, size_to_send);
		offset += size_to_send;


		size_to_send = sizeof(ca->numMem);
		memcpy(paqueteSerializado + offset, &(ca->numMem), size_to_send);
		offset += size_to_send;

		criterio_size = strlen(ca->criterio) + 1;
		size_to_send = sizeof(criterio_size);
		memcpy(paqueteSerializado + offset, &criterio_size, size_to_send);
		offset += size_to_send;

		size_to_send = criterio_size;
		memcpy(paqueteSerializado + offset, ca->criterio, size_to_send);
		offset += size_to_send;

		return paqueteSerializado;

		break;
	}
	case(JOURNAL): {
		offset = 0;

		*total_size = sizeof(rp->accionEjecutar);

		char* paqueteSerializado = (char*) malloc(*total_size);

		size_to_send = sizeof(rp->accionEjecutar);
		memcpy(paqueteSerializado + offset, &(rp->accionEjecutar), size_to_send);
		offset += size_to_send;

		return paqueteSerializado;

		break;
	}
	default:
		return NULL;
	}

}


int recibirYDeserializarPaquete(int socketCliente, resultadoParser* rp) {
	int status;
	contenidoInsert* ci = malloc(sizeof(contenidoInsert));
	int total_size;

	int buffer_size = sizeof(int);
	char* buffer = malloc(buffer_size);
	char* bufferTimestamp = malloc(sizeof(long));

	int valueSize;
	int nombreTablaSize;

	switch(rp->accionEjecutar) {
	case(INSERT): {
		printf("[recibirYDeserializarPaquete] Entro en el case INSERT\n");

		status = recv(socketCliente, buffer, sizeof(int), 0);
		memcpy(&total_size, buffer, buffer_size);
		if (!status) return -2;

		status = recv(socketCliente, buffer, sizeof(int), 0);
		memcpy(&(ci->key), buffer, buffer_size);
		if (!status) return -2;

		status = recv(socketCliente, buffer, sizeof(int), 0);
		memcpy(&valueSize, buffer, buffer_size);
		if (!status) return -2;

		ci->value = malloc(sizeof(valueSize));
		status = recv(socketCliente, ci->value, valueSize, 0);
		if (!status) return -2;

		status = recv(socketCliente, buffer, sizeof(int), 0);
		memcpy(&nombreTablaSize, buffer, buffer_size);
		if (!status) return -2;

		ci->nombreTabla = malloc(nombreTablaSize);
		status = recv(socketCliente, ci->nombreTabla, nombreTablaSize, 0);
		if (!status) return -2;

		status = recv(socketCliente, bufferTimestamp, sizeof(long), 0);
		memcpy(&(ci->timestamp), bufferTimestamp, sizeof(long));
		if (!status) return -2;

		rp->contenido = ci;

		break;
	}
	default:
		return -1;
	}

	return 0;

}

