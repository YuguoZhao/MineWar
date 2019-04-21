#include "Type.h"

void Utils_getDocPath(const char *fileName, char *path)
{
	sprintf(path, "%s", fileName);
}

void Utils_getAssetsPath(const char *fileName, char *path)
{
	sprintf(path, ".\\assets\\%s", fileName);
}

void Utils_getResPath(const char *fileName, char *path)
{
	sprintf(path, ".\\res\\%s", fileName);
}
