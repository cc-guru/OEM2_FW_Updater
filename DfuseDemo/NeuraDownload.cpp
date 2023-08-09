#include "stdafx.h"
#include "NeuraDownload.h"

BOOL CNeuraDownloadDLG::OnInitDialog()
{
	CDfuSeDemoDlg::OnInitDialog();

	ModifyStyle(WS_CAPTION, 0); // to hide title bar
	prepAndLaunchDownload();  //find the DFU port and download the DFU file!
	return TRUE;
}


void CNeuraDownloadDLG::DownloadIt()
{
	CString m_CurrDFUName;
	HANDLE hdl;
	if (STDFU_Open((LPSTR)(LPCSTR)m_CurrDFUName, &hdl) == STDFU_NOERROR)
	{
		if (STDFU_SelectCurrentConfiguration(&hdl, 0, 0, 1) == STDFU_NOERROR)
		{
			DFUSTATUS DFUStatus;

			STDFU_Getstatus(&hdl, &DFUStatus);
			while (DFUStatus.bState != STATE_DFU_IDLE)
			{
				STDFU_Clrstatus(&hdl);
				STDFU_Getstatus(&hdl, &DFUStatus);
			}

			LPBYTE m_pBuffer = (LPBYTE)malloc(0x10);
			memset(m_pBuffer, 0xFF, 0x10);
			m_pBuffer[0] = 0x92;


			STDFU_Dnload(&hdl, m_pBuffer, 0x01, 0);

			STDFU_Getstatus(&hdl, &DFUStatus);
			/*while(DFUStatus.bState != STATE_DFU_IDLE)
			{
				STDFU_Clrstatus(&hdl);
				STDFU_Getstatus(&hdl, &DFUStatus);
			}*/
		}
		STDFU_Close(&hdl);
	}

}