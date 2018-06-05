/***************************************************************
 * Name:      CalculatorApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2017-04-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "CalculatorApp.h"
#include "CalculatorMain.h"

IMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
        Window* dlg = new Window(0L, wxT("Calculator"));
        dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
        dlg->Show();
    return true;
}
