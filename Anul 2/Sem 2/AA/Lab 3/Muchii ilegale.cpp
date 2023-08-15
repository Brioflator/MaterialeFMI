#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

// Function to get cofactor of
// mat[p][q] in temp[][]. n is
// current dimension of mat[][]
void getCofactor(int mat[4][4],
                 int temp[4][4], int p,
                 int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of
    // the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // Copying into temporary matrix
            // only those element which are
            // not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                // Row is filled, so increase row
                // index and reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding
   determinant of matrix.
   n is current dimension of mat[][]. */
int determinantOfMatrix(int mat[4][4], int n)
{
    // Initialize result
    int D = 0;

    //  Base case : if matrix contains
    // single element
    if (n == 1)
        return mat[0][0];

    // To store cofactors
    int temp[4][4];

    // To store sign multiplier
    int sign = 1;

    // Iterate for each element of
    // first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] *
             determinantOfMatrix(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

int main() {
    int xA, yA, xB, yB, xC, yC, xD, yD;
    cin >> xA >> yA >> xB >> yB >> xC >> yC>> xD >> yD;

        int D[4][4] = {
                {xA, yA, xA*xA + yA*yA, 1},
                {xB, yB, xB*xB + yB*yB, 1},
                {xC, yC, xC*xC + yC*yC, 1},
                {xD, yD, xD*xD + yD*yD, 1}
        };

        int A[4][4] = {

                {xB, yB, xB*xB + yB*yB, 1},
                {xC, yC, xC*xC + yC*yC, 1},
                {xD, yD, xD*xD + yD*yD, 1},
                {xA, yA, xA*xA + yA*yA, 1}
        };

        int det_D = determinantOfMatrix(D, 4);
        int det_A = determinantOfMatrix(A, 4);
        cout<<"AC: ";
        if(det_D > 0) {
            cout << "ILLEGAL" << endl;
        } else {
            cout << "LEGAL" << endl;
        }

        cout<<"BD: ";
        if(det_A > 0) {
            cout << "ILLEGAL" << endl;
        } else {
            cout << "LEGAL" << endl;
        }

    return 0;
}