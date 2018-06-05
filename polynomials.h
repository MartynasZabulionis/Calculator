#ifndef POLYNOMIAL_PAGE
#define POLYNOMIAL_PAGE

#include "CalculatorMain.h"

#define ID_MULTIPLY_NUMBER_POL 60
#define ID_MULTIPLY_POL 70
#define ID_SUM_POL 80
#define ID_DIFF 90

class PolynomialPane: public wxNotebookPage
{
    public:
        PolynomialPane(wxNotebook *id, const wxString& title);
        ~PolynomialPane();

        // Viskas polinomams
        wxTextCtrl **PolA, **PolB, **PolC, *text_multiply_pol;
        wxButton *button_multiply_number_pol, *button_multiply_pol, *button_sum_pol, *button_diff;

        void OnMultiplyNumberPol(wxCommandEvent & event);
        void OnMultiplyPol(wxCommandEvent & event);
        void OnDiff(wxCommandEvent & event);
        void OnSumPol(wxCommandEvent & event);
};

#endif
