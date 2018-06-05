/***************************************************************
 * Name:      CalculatorMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2017-04-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef CALCULATORMAIN_H
#define CALCULATORMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "CalculatorApp.h"

#include <wx/button.h>
#include <wx/statline.h>
#include <wx/notebook.h>


class Window: public wxDialog
{
    public:
        Window(wxDialog *dlg, const wxString& title);
        ~Window();

    private:
        void OnClose(wxCloseEvent& event);
        DECLARE_EVENT_TABLE();
};

bool RetrieveNumbers(wxTextCtrl **t,double *k, int size);

#endif // CALCULATORMAIN_H
