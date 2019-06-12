#include "FileDialog.h"
#include <windows.h>
#include <shobjidl_core.h>
#include <atlstr.h>

unsigned int FileDialog::Open()
{
	IFileOpenDialog* pfd;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
	{
		DWORD dwOptions;
		if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
		{
			pfd->SetOptions(dwOptions);
		}
		if (SUCCEEDED(pfd->Show(NULL)))
		{
			IShellItem* psi;
			if (SUCCEEDED(pfd->GetResult(&psi)))
			{
				LPWSTR buffer = NULL;
				if (!SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &buffer)))
				{
					MessageBox(NULL, "GetIDListName() failed", NULL, NULL);
				}
				else {
					CString strFilePath(buffer);
					m_FilePath = strFilePath;

					psi->GetDisplayName(SIGDN_NORMALDISPLAY, &buffer);
					CString strFileName(buffer);
					m_FileName = strFileName;
				}
				psi->Release();
			}
		}
		else {
			m_Error = "User cancelled request";
			return -1;
		}
		pfd->Release();
	}
	return 1;
}
