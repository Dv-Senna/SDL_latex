#ifndef SDL_LATEX_TEX_HASH_H
#define SDL_LATEX_TEX_HASH_H



#ifdef __cplusplus
	extern "C" {
#endif


/// @brief Create a hash of `string`. Isn't very tested but is used only for generating file name
/// @param string The string to create a hash
/// @param output The hash generated
/// @param size The size of the font of `string`. Use as an offset
void TEX_Hash(const char *string, char *output, int size);


#ifdef __cplusplus
	}
#endif

#endif