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
#include "matrixes.h"

MatrixPane::MatrixPane(wxNotebook *id, const wxString &title)
    : wxNotebookPage(id, -1)
{
        id->AddPage(this, title);

        // Matricu puslapio sukurimas
        new wxStaticText(this, -1, _("Matrix A:"), wxPoint(20, 20));
        new wxStaticText(this, -1, _("Matrix B:"), wxPoint(240, 20));
        new wxStaticText(this, -1, _("Matrix C:"), wxPoint(460, 20));

        det_text = new wxStaticText(this, -1, _(": 0"), wxPoint(110, 154));

        MatrixA = new wxTextCtrl*[9];
        MatrixB = new wxTextCtrl*[9];
        MatrixC = new wxTextCtrl*[9];

        int i, y;
        for (i = 0; i < 3; ++i)
        {
                for (y = 0; y < 3; ++y)
                {
                        MatrixA[i * 3 + y] = new wxTextCtrl(this, -1, _(i == y ? "1" : "0"), wxPoint(20 + y * 55, 40 + i * 30), wxSize(50 , 23), 0, wxTextValidator(wxFILTER_NUMERIC));
                        MatrixB[i * 3 + y] = new wxTextCtrl(this, -1, _(i == y ? "1" : "0"), wxPoint(240 + y * 55, 40 + i * 30), wxSize(50 , 23), 0, wxTextValidator(wxFILTER_NUMERIC));
                        MatrixC[i * 3 + y] = new wxTextCtrl(this, -1, wxT("0"), wxPoint(460 + y * 55, 40 + i * 30), wxSize(50 , 23), wxTE_READONLY, wxTextValidator(wxFILTER_NUMERIC));
                }
        }
        button_determinant = new wxButton(this, ID_DETERMINANT, wxT("det(A)"), wxPoint(20, 150));
        Connect(ID_DETERMINANT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MatrixPane::OnDeterminant));


        button_multiply_number = new wxButton(this, ID_MULTIPLY_NUMBER, wxT("A *="), wxPoint(20, 178));
        Connect(ID_MULTIPLY_NUMBER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MatrixPane::OnMultiplyNumber));
        text_multiply = new wxTextCtrl(this, -1, wxT("1"), wxPoint(110, 179), wxSize(40 , 23), 0, wxTextValidator(wxFILTER_NUMERIC));

        button_sum = new wxButton(this, ID_SUM, wxT("C = A + B"), wxPoint(20, 206));
        Connect(ID_SUM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MatrixPane::OnSum));

        button_multiply_matrix = new wxButton(this, ID_MULTIPLY_MATRIX, wxT("C = A * B"), wxPoint(20, 234));
        Connect(ID_MULTIPLY_MATRIX, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MatrixPane::OnMultiplyMatrix));

        button_sum = new wxButton(this, ID_INVERSE_MATRIX, wxT("C = A^-1"), wxPoint(20, 262));
        Connect(ID_INVERSE_MATRIX, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MatrixPane::OnInverseMatrix));
}
void MatrixPane::OnDeterminant(wxCommandEvent & event)
{
        double k[9], d;

        if (!RetrieveNumbers(MatrixA, k, 9))
                return;

        d = k[0] * (k[4] * k[8] - k[5] * k[7]) - k[1] * (k[3] * k[8] - k[5] * k[6]) + k[2] * (k[3] * k[7] - k[4] * k[6]);
        det_text->SetLabel(wxString::Format(wxT(": %g"), d));
}
void MatrixPane::OnMultiplyNumber(wxCommandEvent & event)
{
        double s, k[9];
        if (!text_multiply->GetLineText(0).ToDouble(&s))
        {
                wxMessageBox(wxT("Bad number format!"), wxT("Error"));
                return;
        }
        if (!RetrieveNumbers(MatrixA, k, 9))
                return;

        for (int i = 0; i < 9; ++i)
        {
                MatrixA[i]->SetValue(wxString::Format(wxT("%g"), k[i] * s));
        }
}
void MatrixPane::OnSum(wxCommandEvent & event)
{
        double a[9], b[9];

        if (!RetrieveNumbers(MatrixA, a, 9) || !RetrieveNumbers(MatrixB, b, 9))
                return;

        for (int i = 0; i < 9; ++i)
        {
                MatrixC[i]->SetValue(wxString::Format(wxT("%g"), a[i] + b[i]));
        }
}
void MatrixPane::OnMultiplyMatrix(wxCommandEvent & event)
{
        double a[9], b[9], c[9] = {0};
        int i, y, z;

        if (!RetrieveNumbers(MatrixA, a, 9) || !RetrieveNumbers(MatrixB, b, 9))
                return;

        for (y = 0; y < 3; ++y)
        {
                for (i = 0; i < 3; ++i)
                {
                        for (z = 0; z < 3; ++z)
                        {
                                c[y * 3 + i] += a[y * 3 + z] * b[z * 3 + i];
                        }
                        MatrixC[y * 3 + i]->SetValue(wxString::Format(wxT("%g"), c[y * 3 + i]));
                }
        }
}
void MatrixPane::OnInverseMatrix(wxCommandEvent & event)
{
        double k[9], l[9], d;
        if (!RetrieveNumbers(MatrixA, k, 9))
                return;

        d = k[0] * (k[4] * k[8] - k[5] * k[7]) - k[1] * (k[3] * k[8] - k[5] * k[6]) + k[2] * (k[3] * k[7] - k[4] * k[6]);
        if (d == 0)
        {
                wxMessageBox(wxT("Matrix is irreversible!"), wxT("Caution"));
                return;
        }
        for (int y = 0; y < 3; ++y)
        {
                for (int x = 0; x < 3; ++x)
                {
                        l[y * 3 + x] =
                        (k[((y + 1) % 3) * 3 + (x + 1) % 3] * k[((y + 2) % 3) * 3 + (x + 2) % 3]
                        - k[((y + 1) % 3) * 3 + (x + 2) % 3] * k[((y + 2) % 3) * 3 + (x + 1) % 3]) / d;
                        MatrixC[x * 3 + y]->SetValue(wxString::Format(wxT("%g"), l[y * 3 + x]));
                }
        }
}
MatrixPane::~MatrixPane()
{
        delete MatrixA;
        delete MatrixB;
        delete MatrixC;
}
