#include "ScaleFormALL.h"

#include <map>
#include <list>

const char*	LastControlDown;
const char*	LastControlUp;

uint32_t	LastKeycodeDown;
uint32_t	LastKeycodeUp;

uint32_t	ForceContainerCategorization{ 0 };
uint8_t     DisableMapMenuMouseWheel{ 0 };

float		LastX;
float		LastY;

IndexStorageTable	s_indexTable;