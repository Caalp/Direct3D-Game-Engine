#include "FileUtils.h"
#include <shobjidl.h> 
#include "json/json.hpp"



namespace FileUtils
{
	std::wstring OpenFileDialog()
	{
		LPWSTR pszFilePath;
		std::wstring filepath;
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							filepath = pszFilePath;
							
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}

		return filepath;
	}
	
	FILE* OpenFile(const char* filepath)
	{
		FILE* pFile;
		fopen_s(&pFile,filepath, "r");

		if (pFile == NULL)
		{
			perror("File can't be opened!");
			delete pFile;
			return NULL;
		}

		else
		{
			return pFile;
		}
	}
}
