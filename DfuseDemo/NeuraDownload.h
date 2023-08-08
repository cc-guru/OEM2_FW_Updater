#pragma once

#include "DfuSeDemoDlg.h"
#include "hexedit.h"
#include "TextProgressCtrl.h"

class CNeuraDownloadDLG :
    public CDfuSeDemoDlg
{

    void CNeuraDownloadDLG::DownloadIt();

protected:
    virtual BOOL OnInitDialog();


};

