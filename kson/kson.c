#include "kson.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct kson_internal {
	kson_symbol_t * symbols;
	unsigned long long int * hashes;
	unsigned long long int length;
} kson_internal_t;

typedef enum {
	STAGE_NONE = 0,
	STAGE_NAME,
	STAGE_VALUE,
	STAGE_ARRAY,
	STAGE_NEXT_ELEMENT,
} stage_enum;

/* named because a soapbox is a small/minor stage
   and this represents a finer grained (minor) stage in parellel
   to the regular stage state */
typedef enum {
	SOAPBOX_NONE = 0,
	SOAPBOX_QUOTING,
	SOAPBOX_ASSIGNING,
	SOAPBOX_BRACING,
	SOAPBOX_COMMAING,
} soapbox_enum;

kson_result_enum kson_load(kson_t * out_kson, void * buffer, unsigned long long int length) {
	char * buf = (char *) buffer;
	char c = ' ';
	char nextc = ' ';
	char prevc = ' ';
	unsigned long long int i = 0;

	struct {
		char * start;
		unsigned long long int len;
	} word = {
		NULL, 0
	};

	struct {
		stage_enum stage;
		soapbox_enum soapbox;
		kson_type_enum type;
	} state = {
		STAGE_NONE,
		SOAPBOX_NONE,
		KSON_TYPE_UNDEFINED,
	};

	for (; i < length; ++i) {
		c = buf[i];
		prevc = c;
		if (i < length - 1) {
			nextc = buf[i];
		}

		if (state.soapbox == SOAPBOX_NONE && (c == ' ' || c == '\t' || c == '\n' || c == '\r')) {
			continue;
		} else if (c == '\'') {
			if (state.soapbox == SOAPBOX_QUOTING) {
				state.soapbox = SOAPBOX_NONE;
			} else {
				state.soapbox = SOAPBOX_QUOTING;
			}
			continue;
		} else if (c == ':') {
			state.soapbox = SOAPBOX_ASSIGNING;
			continue;
		} else if (c == '{') {
			state.soapbox = SOAPBOX_BRACING;
			continue;
		} else if (c == '}') {
			state.soapbox = SOAPBOX_NONE;
			continue;
		} else if (c == ',') {
			state.soapbox = SOAPBOX_COMMAING;
			continue;
		}

		putc(c, stdout);

		switch (state.stage) {
			default:
			case STAGE_NONE:
				break;
		}
	}

	return KSON_RESULT_SUCCESS;
}

void kson_destroy(kson_t kson) {
	
}

kson_type_enum kson_symbol(kson_t kson, kson_symbol_t ** out_symbol, const char * name) {
	return KSON_TYPE_UNDEFINED;
}
