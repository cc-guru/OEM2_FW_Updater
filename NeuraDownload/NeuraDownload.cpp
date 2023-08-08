// NeuraDownload.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <dbt.h>
#include "../STDFU/STDFU.H"
#include <wtypes.h>
#include "../DfuseDemo/DfuSeDemoDlg.h"

#define STVendorID		  0x0483 //used
#define VENDOR_USAGE_PAGE 0xFF00 //used
#define USAGE_DETACH	  0x0055 //used

static GUID	GUID_DFU = { 0x3fe809ab, 0xfb91, 0x4cb5, { 0xa6, 0x43, 0x69, 0x67, 0x0d, 0x52, 0x36, 0x6e } };
//static GUID GUID_APP = { 0xcb979912, 0x5029, 0x420a, { 0xae, 0xb1, 0x34, 0xfc, 0x0a, 0x7d,0x57,0x26 } };
static GUID GUID_APP1 = { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30} };//midifyied by havenxie
static GUID GUID_APP = { 0x745a17a0, 0x74d3, 0x11d0, { 0xb6, 0xfe, 0x00, 0xa0, 0xc9, 0x0f, 0x57, 0xda} };



int main()
{
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
		ReadProtected = FALSE;
	}

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
