#ifndef QUATERNION_PAGE
#define QUATERNION_PAGE

#include "CalculatorMain.h"

#define ID_MULTIPLY_QU 100
#define ID_DIVIDE_QU 110
#define ID_SUM_QU 120
#define ID_LENGTH 130

class QuaternionPane: public wxNotebookPage
{
    public:
        QuaternionPane(wxNotebook *id, const wxString& title);
        ~QuaternionPane();

        // Viskas kvaternionams
        wxTextCtrl **QuA, **QuB, **QuC;
        wxButton *button_multiply_qu, *button_divide_qu, *button_sum_qu, *button_length;
        wxStaticText *length_text;

        void OnMultiplyQu(wxCommandEvent & event);
        void OnDivideQu(wxCommandEvent & event);
        void OnSumQu(wxCommandEvent & event);
        void OnLength(wxCommandEvent & event);
};

#endif
