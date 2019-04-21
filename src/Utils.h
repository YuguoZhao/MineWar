/**
	\addtogroup Utils
	declaration of utils tool api.
*/
/*@{*/
/***************************************************************************//**
	\file		utils.h
	\brief		declaration of utils api.
	\author		XA
	\date		2016-7-1
	\version	1.0.1
*******************************************************************************/
#ifndef _UTILS_H
#define _UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************//**
	\fn			void Utils_getDocPath(const char *fileName, char *path)
	\brief		get doc path file full path.
	\param[in]	fileName :file name.
	\param[out]	path :full path file name.
*******************************************************************************/
void Utils_getDocPath(const char *fileName, char *path);

/***************************************************************************//**
	\fn			void Utils_getAssetsPath(const char *fileName, char *path)
	\brief		get assets path file full path.
	\param[in]	fileName :file name.
	\param[out]	path :full path file name.
*******************************************************************************/
void Utils_getAssetsPath(const char *fileName, char *path);

/***************************************************************************//**
	\fn			void Utils_getResPath(const char *fileName, char *path)
	\brief		get resource path file full path.
	\param[in]	fileName :file name.
	\param[out]	path :full path file name.
*******************************************************************************/
void Utils_getResPath(const char *fileName, char *path);

#ifdef __cplusplus
}
#endif
#endif	//_UTILS_H
/*@}*/
