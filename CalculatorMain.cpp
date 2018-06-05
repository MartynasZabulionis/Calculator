/***************************************************************
 * Name:      LangasMain.cpp
 * Purpose:   Code for Application Frame
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

//#include "main.h"
#include "CalculatorMain.h"
#include "matrixes.h"
#include "polynomials.h"
#include "quaternions.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(Window, wxDialog)
    EVT_CLOSE(Window::OnClose)
END_EVENT_TABLE()


Window::Window(wxDialog *dlg, const wxString &title)
    : wxDialog(dlg, -1, title, wxDefaultPosition, wxSize(700, 400))
{
        wxNotebook *notebook = new wxNotebook(this, 19/*, wxDefaultPosition, wxSize(200, 200), wxNB_MULTILINE */);

        new MatrixPane(notebook, wxT("Matrixes"));
        new PolynomialPane(notebook, wxT("Polynomials"));
        new QuaternionPane(notebook, wxT("Quaternions"));

        //notebook->Layout();
        Centre();
}

void Window::OnClose(wxCloseEvent& event)
{
        Destroy();
}
Window::~Window()
{
}

bool RetrieveNumbers(wxTextCtrl **t,double *k, int size)
{
        for (int i = 0; i < size; ++i)
        {
                if (!t[i]->GetLineText(0).ToDouble(&k[i]))
                {
                        wxMessageBox(wxT("Bad number format!"), wxT("Error"));
                        return false;
                }
        }
        return true;
}
