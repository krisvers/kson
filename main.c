#include <stdio.h>
#include "kson/kson.h"

const char * json =
"{\n"
"	'ted': {\n"
"		'age': 9,\n"
"		'adult': false,\n"
"		'holding': {\n"
"			'name': 'bottle',\n"
"			'edible': true\n"
"		},\n"
"		'friends': [ 'john', 'lucy' ]\n"
"	},\n"
"	'john': {\n"
"		'age': 23,\n"
"		'adult': false,\n"
"		'holding': {\n"
"			'name': 'apple',\n"
"			'edible': true\n"
"		},\n"
"		'friends': [ 'ted', 'mark', 'lucy' ]\n"
"	}\n"
"}";

int main(int argc, char ** argv) {
	printf("json:\n%s", json);

	kson_t kson;
	kson_result_enum r = kson_load(&kson, (void *) json, sizeof(json));
	if (r != KSON_RESULT_SUCCESS) {
		printf("Failed to load KSON %i 0x%x", r, r);
		return 1;
	}

	kson_symbol_t * ted;
	if (kson_symbol(kson, &ted, "ted") == KSON_TYPE_OBJECT) {
		//printf("%s %i %s", ted->name, ted->type, ted->value.object.key_strings[0]);
	}

	kson_destroy(kson);

	return 0;
}
