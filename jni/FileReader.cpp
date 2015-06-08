#include <inc/FileReader.h>

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

AAssetManager* FileReader::_mAssetMgr;

void FileReader::SetAssetManager( AAssetManager* pManager )
{
	_mAssetMgr = pManager;
}

//Reads the contents of the give file return the content and the file size.
//The calling function is responsible for free the memory allocated for Content.
void FileReader::Read( const char* FileName, char** Content, unsigned int* Size )
{
    // Open files
    AAsset* pFile = AAssetManager_open( _mAssetMgr, FileName, AASSET_MODE_UNKNOWN );

    if( pFile != NULL )
    {
        // Determine file size
        off_t FileSize = AAsset_getLength( pFile );
        
        // Read data
        char* pData = (char*)malloc( FileSize );
        AAsset_read( pFile, pData, FileSize );
    
        // Allocate space for the file content
        *Content = (char*)malloc( FileSize );
    
        // Copy the content
        memcpy( *Content, pData, FileSize );
        *Size = FileSize;
        
        // Close the file
        AAsset_close( pFile );
    }
}
