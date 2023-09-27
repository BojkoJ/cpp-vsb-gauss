#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class GaussianElimination {
public:

    vector<double> count(vector<vector<double>>& A, vector<double>& b) { //funkce p��j�m� adresy matice a vektoru

        int n = A.size();

        // Roz���en� matice A o pravou stranu - co� je vektor b
        for (int i = 0; i < n; ++i) {
            A[i].push_back(b[i]);
        }

        //po tomto kroku matice vypad� takto:
        /*
           { 1, 2,-3, 4, 5 | 4 }
           { 2, 1, 0, 3, 0 | 9 }
           { 0, 2, 1, 2,-1 | 5 }
           { 3,-1, 0, 5, 2 | 3 }
           { 2, 1, 2, 3,-4 | 2 }
        */

        // Prov�d�n� p��m� eliminace
        // postupn� se p�evede matice A na horn� troj�heln�kovou formu.

        for (int i = 0; i < n - 1; i++) {

            // Proch�z�me ��dky nad diagon�lou (nad hlavn� diagon�lou matice).
            for (int j = i + 1; j < n; j++) {

                // Spo��t�me faktor, kter�m budeme n�sleduj�c� ��dek upravovat,
                // aby nulov� prvek pod diagon�lou.
                double factor = A[j][i] / A[i][i];

                // Proch�z�me v�echny sloupce od aktu�ln�ho i.
                for (int k = i; k <= n; k++) {

                    // Aktualizujeme hodnoty v matici A a� po sloupec (n),
                    // aby eliminovali prvky pod diagon�lou.
                    A[j][k] -= factor * A[i][k];

                }
            }
        }


        // Kontrola, zda neexistuj� ��dn� �e�en� nebo nekone�n� �e�en�
        for (int i = 0; i < n; i++) {
            // Zde se kontroluje, zda hlavn� diagon�la matice obsahuje velmi mal� hodnoty (t�m�� nulov�).

            if (abs(A[i][i]) < 0.00001 && abs(A[i][n]) > 0.00001) {
                // Jestli je diagon�ln� prvek skoro nulov�, ale prav� strana nen� nulov�, tak p��klad nem� ��dn� �e�en�.
                cout << "Reseni neexistuje." << endl;
                return vector<double>();
            }
            else if (abs(A[i][i]) < 0.00001 && abs(A[i][n]) < 0.00001) {
                // Jestli je diagon�ln� prvek skoro nulov� a prav� strana je taky t�m�� nulov�, tak m� p��klad nekone�n� mnoho �e�en� (singul�rn� matice).
                cout << "Existuje nekonecne mnoho reseni." << endl;
                return vector<double>();
            }
        }

        // Zp�tn� substituce
        // Vytvo�en� vektoru x pro ulo�en� �e�en�. Vektor m� stejnou d�lku jako po�et nezn�m�ch (n).

        vector<double> x(n);

        // Zde prob�hne zp�tn� substituce pro �e�en� line�rn�ch rovnic.
        for (int i = n - 1; i >= 0; i--) {
            // ��dek i - za��n� od prvn�ho a jde dol� -> (krom� posledn�ho)

            // Nastaven� po��te�n� hodnoty vektoru x na odpov�daj�c� pravou stranu rovnice (prvek v matici A na pozici [i][n]).
            x[i] = A[i][n];

            // Nyn� je t�eba proj�t v�echny ��dky pod ��dkem i
            for (int j = i + 1; j < n; j++) {

                // V tomto cyklu se proch�z� prvky nad hlavn� diagon�lou (v horn� ��sti matice),
                // a tyto hodnoty se od��taj� od aktu�ln�ho prvku na pozici [i][j] n�soben�ho odpov�daj�c�m prvkem vektoru x.
                x[i] -= A[i][j] * x[j];
            }

            // Nakonec se aktu�ln� hodnota vektoru x d�l� prvkem na diagon�le (na pozici [i][i]) pro nalezen� kone�n� hodnoty �e�en�.
            x[i] /= A[i][i];
        }

        return x;
    }
};

int main() {

    // Deklarace matice A_1 - dvourozm�rn� vektor
    vector<vector<double>> A_1 = {
        {1, 2, -3, 4, 5},
        {2, 1, 0, 3, 0},
        {0, 2, 1, 2, -1},
        {3, -1, 0, 5, 2},
        {2, 1, 2, 3, -4}
    };

    // Deklarace prav� strany matice - vektor B_1
    vector<double> B_1 = { 4, 9, 5, 3, 2 };

    // Vytvo�en� instance solveru a vol�n� funkce pro v�po�et matice.
    GaussianElimination matrixSolver;
    vector<double> solution = matrixSolver.count(A_1, B_1);

    if (!solution.empty()) {

        cout << "Reseni matice pomoci Gaussovy eliminacni metody: " << endl;

        // V�pis �e�en� matice
        int i = 1;
        for (double x : solution) {
            cout << "x" << i << " = " << x << " ";
            i++;
            cout << endl;
        }
    }

    return 0;
}
