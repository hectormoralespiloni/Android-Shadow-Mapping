#pragma once

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class FileReader
{
public:
	//Reads the contents of the give file
	//Returns the content and the file size
	static void Read( const char* FileName, char** Content, unsigned int* Size );
	static void SetAssetManager(AAssetManager* pManager);

private:
	static AAssetManager *_mAssetMgr;
};
