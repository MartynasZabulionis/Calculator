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
#include "polynomials.h"

PolynomialPane::PolynomialPane(wxNotebook *id, const wxString &title)
    : wxNotebookPage(id, -1)
{
        id->AddPage(this, title);

        // Polinomu puslapio sukurimas
        new wxStaticText(this, -1, wxT("Polynomial A:"), wxPoint(20, 20));
        new wxStaticText(this, -1, wxT("Polynomial B:"), wxPoint(20, 60));
        new wxStaticText(this, -1, wxT("Polynomial C:"), wxPoint(20, 100));

        PolA = new wxTextCtrl*[6];
        PolB = new wxTextCtrl*[6];
        PolC = new wxTextCtrl*[6];

        for (int i = 0; i < 6; ++i)
        {
                if (i != 0)
                {
                        new wxStaticText(this, -1, wxString::Format(wxT("x^%d  + "), i), wxPoint(675 - i * 100, 20));
                        new wxStaticText(this, -1, wxString::Format(wxT("x^%d  + "), i), wxPoint(675 - i * 100, 60));
                        new wxStaticText(this, -1, wxString::Format(wxT("x^%d  + "), i), wxPoint(675 - i * 100, 100));
                }
                PolA[5 - i] = new wxTextCtrl(this, -1, wxT("1"), wxPoint(120 + i * 100, 16), wxSize(50 , 23), wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC));
                PolB[5 - i] = new wxTextCtrl(this, -1, wxT("1"), wxPoint(120 + i * 100, 56), wxSize(50 , 23), wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC));
                PolC[5 - i] = new wxTextCtrl(this, -1, wxT("1"), wxPoint(120 + i * 100, 96), wxSize(50 , 23), wxTE_RIGHT|wxTE_READONLY, wxTextValidator(wxFILTER_NUMERIC));
        }

        button_multiply_number_pol = new wxButton(this, ID_MULTIPLY_NUMBER_POL, wxT("A *="), wxPoint(20, 178));
        Connect(ID_MULTIPLY_NUMBER_POL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PolynomialPane::OnMultiplyNumberPol));
        text_multiply_pol = new wxTextCtrl(this, -1, wxT("1"), wxPoint(110, 179), wxSize(40 , 23), 0, wxTextValidator(wxFILTER_NUMERIC));

        button_sum_pol = new wxButton(this, ID_SUM_POL, wxT("C = A + B"), wxPoint(20, 206));
        Connect(ID_SUM_POL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PolynomialPane::OnSumPol));

        button_multiply_pol = new wxButton(this, ID_MULTIPLY_POL, wxT("C = A * B"), wxPoint(20, 234));
        Connect(ID_MULTIPLY_POL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PolynomialPane::OnMultiplyPol));

        button_diff = new wxButton(this, ID_DIFF, wxT("C = A'"), wxPoint(20, 262));
        Connect(ID_DIFF, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PolynomialPane::OnDiff));
}
void PolynomialPane::OnMultiplyNumberPol(wxCommandEvent & event)
{
        double s, k[6];
        if (!text_multiply_pol->GetLineText(0).ToDouble(&s))
        {
                wxMessageBox(wxT("Bad number format!"), wxT("Error"));
                return;
        }
        if (!RetrieveNumbers(PolA, k, 6))
                return;

        for (int i = 0; i < 6; ++i)
        {
                PolA[i]->SetValue(wxString::Format(wxT("%g"), k[i] * s));
        }
}
void PolynomialPane::OnSumPol(wxCommandEvent & event)
{
        double a[6], b[6];

        if (!RetrieveNumbers(PolA, a, 6) || !RetrieveNumbers(PolB, b, 6))
                return;

        for (int i = 0; i < 6; ++i)
        {
                PolC[i]->SetValue(wxString::Format(wxT("%g"), a[i] + b[i]));
        }
}
void PolynomialPane::OnMultiplyPol(wxCommandEvent & event)
{
        double a[6], b[6], c[6] = {0};
        int i, y;

        if (!RetrieveNumbers(PolA, a, 6) || !RetrieveNumbers(PolB, b, 6))
                return;

        for (y = 0; y < 6; ++y)
        {
                for (i = 0; i < 6; ++i)
                {
                        if (y + i > 5)
                        {
                                if (a[y] && b[i])
                                {
                                        wxMessageBox(wxT("Polynomial degree is higher than 5!"), wxT("Error"));
                                        return;
                                }
                        }
                        else
                                c[y + i] += a[y] * b[i];
                }
        }
        for (i = 0; i < 6; ++i)
        {
                PolC[i]->SetValue(wxString::Format(wxT("%g"), c[i]));
        }
}
void PolynomialPane::OnDiff(wxCommandEvent & event)
{
        double a[6];

        if (!RetrieveNumbers(PolA, a, 6))
                return;

        PolC[5]->SetValue(wxT("0"));
        for (int i = 1; i < 6; ++i)
        {
                PolC[i - 1]->SetValue(wxString::Format(wxT("%g"), a[i] * i));
        }
}
PolynomialPane::~PolynomialPane()
{
        delete PolA;
        delete PolB;
        delete PolC;
}
