#ifndef PROTOBUF_C_H
#define PROTOBUF_C_H

#include <stdio.h>
#include <stdint.h>

#define PBC_ARRAY_CAP 64

typedef struct _pbc_array { char _data[PBC_ARRAY_CAP]; } pbc_array[1];

struct pbc_slice {
	void *buffer;
	int len;
};

struct pbc_pattern;
struct pbc_env;
struct pbc_rmessage;
struct pbc_wmessage;

struct pbc_env * pbc_new(void);
void pbc_delete(struct pbc_env *);
int pbc_register(struct pbc_env *, struct pbc_slice * slice);

// message api

struct pbc_rmessage * pbc_rmessage_new(struct pbc_env * env, const char * typename , struct pbc_slice * slice);
void pbc_rmessage_delete(struct pbc_rmessage *);

uint32_t pbc_rmessage_integer(struct pbc_rmessage * , const char *key , int index, uint32_t *hi);
double pbc_rmessage_real(struct pbc_rmessage * , const char *key , int index);
const char * pbc_rmessage_string(struct pbc_rmessage * , const char *key , int index, int *sz);
struct pbc_rmessage * pbc_rmessage_message(struct pbc_rmessage *, const char *key, int index);
int pbc_rmessage_size(struct pbc_rmessage *, const char *key);

struct pbc_wmessage * pbc_wmessage_new(struct pbc_env * env, const char *typename);
void pbc_wmessage_delete(struct pbc_wmessage *);

// for negative integer, pass -1 to hi
void pbc_wmessage_integer(struct pbc_wmessage *, const char *key, uint32_t low, uint32_t hi);
void pbc_wmessage_real(struct pbc_wmessage *, const char *key, double v);
void pbc_wmessage_string(struct pbc_wmessage *, const char *key, const char * v, int len);
struct pbc_wmessage * pbc_wmessage_message(struct pbc_wmessage *, const char *key);
void * pbc_wmessage_buffer(struct pbc_wmessage *, struct pbc_slice * slice);

// array api 

int pbc_array_size(pbc_array);
uint32_t pbc_array_integer(pbc_array array, int index, uint32_t *hi);
double pbc_array_real(pbc_array array, int index);
struct pbc_slice * pbc_array_slice(pbc_array array, int index);

void pbc_array_push_integer(pbc_array array, uint32_t low, uint32_t hi);
void pbc_array_push_slice(pbc_array array, struct pbc_slice *);
void pbc_array_push_real(pbc_array array, double v);

struct pbc_pattern * pbc_pattern_new(struct pbc_env * , const char * message, const char *format, ...);
void pbc_pattern_delete(struct pbc_pattern *);

// return bytes , -1 for error
int pbc_pattern_pack(struct pbc_pattern *, void *input, struct pbc_slice * s);

// <0 for error
int pbc_pattern_unpack(struct pbc_pattern *, struct pbc_slice * s , void * output);

void pbc_pattern_set_default(struct pbc_pattern * , void *data);
void pbc_pattern_close_arrays(struct pbc_pattern *, void *data);

#endif
