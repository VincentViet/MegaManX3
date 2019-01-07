#include "settings.h"
#include "jansson/jansson.h"

static json_t* configs = nullptr;

void* azorGetConfigsContent(void* error)
{
	if (!configs)
		configs = json_load_file(
			CONFIGS_PATH,
			JSON_ALLOW_NUL,
			static_cast<json_error_t*>(error));

	return configs;
}
