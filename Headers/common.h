#ifndef __COMMON_H__
#define __COMMON_H__
#include "tablahash.h"
#include "dictionary.h"

TablaHash readDictionary(char *dictPath);
void text(char *texPath, TablaHash dict);

#endif /* __COMMON_H__ */