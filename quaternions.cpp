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
#include "quaternions.h"

QuaternionPane::QuaternionPane(wxNotebook *id, const wxString &title)
    : wxNotebookPage(id, -1)
{
        id->AddPage(this, title);

        // Kvaternionu puslapio sukurimas
        new wxStaticText(this, -1, wxT("Quaternion A:"), wxPoint(20, 20));
        new wxStaticText(this, -1, wxT("Quaternion B:"), wxPoint(20, 60));
        new wxStaticText(this, -1, wxT("Quaternion C:"), wxPoint(20, 100));

        QuA = new wxTextCtrl*[4];
        QuB = new wxTextCtrl*[4];
        QuC = new wxTextCtrl*[4];

        char letter[4] = {' ', 'i', 'j', 'k'};
        for (int i = 0; i < 4; ++i)
        {
                new wxStaticText(this, -1, wxString::Format(wxT("%c%s"), letter[i], i == 3 ? wxT("") : wxT("     + ")), wxPoint(195 + i * 100, 20));
                new wxStaticText(this, -1, wxString::Format(wxT("%c%s"), letter[i], i == 3 ? wxT("") : wxT("     + ")), wxPoint(195 + i * 100, 60));
                new wxStaticText(this, -1, wxString::Format(wxT("%c%s"), letter[i], i == 3 ? wxT("") : wxT("     + ")), wxPoint(195 + i * 100, 100));

                QuA[i] = new wxTextCtrl(this, -1, wxT("1"), wxPoint(140 + i * 100, 16), wxSize(50 , 23), wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC));
                QuB[i] = new wxTextCtrl(this, -1, wxT("1"), wxPoint(140 + i * 100, 56), wxSize(50 , 23), wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC));
                QuC[i] = new wxTextCtrl(this, -1, wxT("1"), wxPoint(140 + i * 100, 96), wxSize(50 , 23), wxTE_RIGHT|wxTE_READONLY, wxTextValidator(wxFILTER_NUMERIC));
        }

        button_sum_qu = new wxButton(this, ID_SUM_QU, wxT("C = A + B"), wxPoint(20, 150));
        Connect(ID_SUM_QU, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(QuaternionPane::OnSumQu));

        button_multiply_qu = new wxButton(this, ID_MULTIPLY_QU, wxT("C = A * B"), wxPoint(20, 178));
        Connect(ID_MULTIPLY_QU, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(QuaternionPane::OnMultiplyQu));

        button_divide_qu = new wxButton(this, ID_DIVIDE_QU, wxT("C = A / B"), wxPoint(20, 206));
        Connect(ID_DIVIDE_QU, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(QuaternionPane::OnDivideQu));

        length_text = new wxStaticText(this, -1, _(": 0"), wxPoint(110, 238));
        button_length = new wxButton(this, ID_LENGTH, wxT("||A||"), wxPoint(20, 234));
        Connect(ID_LENGTH, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(QuaternionPane::OnLength));
}
void QuaternionPane::OnSumQu(wxCommandEvent & event)
{
        double a[4], b[4];

        if (!RetrieveNumbers(QuA, a, 4) || !RetrieveNumbers(QuB, b, 4))
                return;

        for (int i = 0; i < 4; ++i)
        {
                QuC[i]->SetValue(wxString::Format(wxT("%g"), a[i] + b[i]));
        }
}
void QuaternionPane::OnMultiplyQu(wxCommandEvent & event)
{
        double a[4], b[4], c[4] = {0};
        int i, y;

        // 1 i j k
        int index[4][4] = {{0, 1, 2, 3}, {1, 0, 3, 2}, {2, 3, 0, 1}, {3, 2, 1, 0}};
        bool negative[4][4] = {{false, false, false, false}, {false, true, false, true}, {false, true, true, false}, {false, false, true, true}};
        if (!RetrieveNumbers(QuA, a, 4) || !RetrieveNumbers(QuB, b, 4))
                return;

        for (y = 0; y < 4; ++y)
        {
                for (i = 0; i < 4; ++i)
                {
                        c[index[y][i]] += a[y] * b[i] * (negative[y][i] ? -1 : 1);
                }
        }
        for (i = 0; i < 4; ++i)
        {
                QuC[i]->SetValue(wxString::Format(wxT("%g"), c[i]));
        }
}
void QuaternionPane::OnDivideQu(wxCommandEvent & event)
{
        double a[4], b[4];

        if (!RetrieveNumbers(QuA, a, 4) || !RetrieveNumbers(QuB, b, 4))
                return;

        QuC[0]->SetValue(wxString::Format(wxT("%g"),
        (b[0]*a[0] + b[1]*a[1] + b[2]*a[2] + b[3]*a[3]) / (b[0]*b[0] + b[1]*b[1] + b[2]*b[2] + b[3]*b[3])
        ));
        QuC[1]->SetValue(wxString::Format(wxT("%g"),
        (b[0]*a[1] + b[1]*a[0] + b[2]*a[3] + b[3]*a[2]) / (b[0]*b[0] + b[1]*b[1] + b[2]*b[2] + b[3]*b[3])
        ));
        QuC[2]->SetValue(wxString::Format(wxT("%g"),
        (b[0]*a[2] + b[1]*a[3] + b[2]*a[0] + b[3]*a[1]) / (b[0]*b[0] + b[1]*b[1] + b[2]*b[2] + b[3]*b[3])
        ));
        QuC[3]->SetValue(wxString::Format(wxT("%g"),
        (b[0]*a[3] + b[1]*a[2] + b[2]*a[1] + b[3]*a[0]) / (b[0]*b[0] + b[1]*b[1] + b[2]*b[2] + b[3]*b[3])
        ));
}
void QuaternionPane::OnLength(wxCommandEvent & event)
{
        double a[4];

        if (!RetrieveNumbers(QuA, a, 4))
                return;

        length_text->SetLabel(wxString::Format(wxT(": %g"), sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2] + a[3]*a[3])));
}
QuaternionPane::~QuaternionPane()
{
        delete QuA;
        delete QuB;
        delete QuC;
}
