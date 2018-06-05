#ifndef MATRIX_PAGE
#define MATRIX_PAGE

#include "CalculatorMain.h"

#define ID_DETERMINANT 10
#define ID_MULTIPLY_NUMBER 20
#define ID_MULTIPLY_MATRIX 30
#define ID_SUM 40
#define ID_INVERSE_MATRIX 50

class MatrixPane: public wxNotebookPage
{
    public:
        MatrixPane(wxNotebook *id, const wxString& title);
        ~MatrixPane();

        // Viskas matricoms
        wxButton *button_determinant, *button_multiply_number, *button_sum, *button_multiply_matrix, *button_inverse_matrix;
        wxTextCtrl **MatrixA, **MatrixB, **MatrixC, *text_multiply;
        wxStaticText *det_text;

        void OnDeterminant(wxCommandEvent & event);
        void OnMultiplyNumber(wxCommandEvent & event);
        void OnMultiplyMatrix(wxCommandEvent & event);
        void OnInverseMatrix(wxCommandEvent & event);
        void OnSum(wxCommandEvent & event);
};

#endif
