#ifndef KRISVERS_KSON_H
#define KRISVERS_KSON_H

typedef enum kson_type {
	KSON_TYPE_UNDEFINED = 0,
	KSON_TYPE_NUMBER,
	KSON_TYPE_STRING,
	KSON_TYPE_BOOLEAN,
	KSON_TYPE_OBJECT,
	KSON_TYPE_ARRAY,
	KSON_TYPE_NULL,
} kson_type_enum;

typedef struct kson_array {
	struct kson_symbol * elements;
	unsigned long long int length;
} kson_array_t;

typedef struct kson_object {
	unsigned long long int * keys;
	struct kson_symbol ** values;
	unsigned long long int length;
} kson_object_t;

typedef struct kson_string {
	char * str;
	unsigned long long int length;
} kson_string_t;

typedef union kson_value {
	float number;
	kson_string_t string;
	unsigned char boolean;
	kson_object_t object;
	kson_array_t array;
} kson_value_t;

typedef struct kson_symbol {
	char * name;
	kson_type_enum type;
	kson_value_t value;
} kson_symbol_t;

typedef enum kson_result {
	KSON_RESULT_SUCCESS = 0,
	KSON_RESULT_GENERIC_ERROR,
} kson_result_enum;

typedef void * kson_t;

kson_result_enum kson_load(kson_t * out_kson, void * buffer, unsigned long long int length);
void kson_destroy(kson_t kson);
kson_type_enum kson_symbol(kson_t kson, kson_symbol_t ** out_symbol, const char * name);

#endif
