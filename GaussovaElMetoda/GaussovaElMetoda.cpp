#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class GaussianElimination {
public:

    vector<double> count(vector<vector<double>>& A, vector<double>& b) { //funkce pøíjímá adresy matice a vektoru

        int n = A.size();

        // Rozšíøení matice A o pravou stranu - což je vektor b
        for (int i = 0; i < n; ++i) {
            A[i].push_back(b[i]);
        }

        //po tomto kroku matice vypadá takto:
        /*
           { 1, 2,-3, 4, 5 | 4 }
           { 2, 1, 0, 3, 0 | 9 }
           { 0, 2, 1, 2,-1 | 5 }
           { 3,-1, 0, 5, 2 | 3 }
           { 2, 1, 2, 3,-4 | 2 }
        */

        // Provádìní pøímé eliminace
        // postupnì se pøevede matice A na horní trojúhelníkovou formu.

        for (int i = 0; i < n - 1; i++) {

            // Procházíme øádky nad diagonálou (nad hlavní diagonálou matice).
            for (int j = i + 1; j < n; j++) {

                // Spoèítáme faktor, kterým budeme následující øádek upravovat,
                // aby nulový prvek pod diagonálou.
                double factor = A[j][i] / A[i][i];

                // Procházíme všechny sloupce od aktuálního i.
                for (int k = i; k <= n; k++) {

                    // Aktualizujeme hodnoty v matici A až po sloupec (n),
                    // aby eliminovali prvky pod diagonálou.
                    A[j][k] -= factor * A[i][k];

                }
            }
        }


        // Kontrola, zda neexistují žádná øešení nebo nekoneèná øešení
        for (int i = 0; i < n; i++) {
            // Zde se kontroluje, zda hlavní diagonála matice obsahuje velmi malé hodnoty (témìø nulové).

            if (abs(A[i][i]) < 0.00001 && abs(A[i][n]) > 0.00001) {
                // Jestli je diagonální prvek skoro nulový, ale pravá strana není nulová, tak pøíklad nemá žádné øešení.
                cout << "Reseni neexistuje." << endl;
                return vector<double>();
            }
            else if (abs(A[i][i]) < 0.00001 && abs(A[i][n]) < 0.00001) {
                // Jestli je diagonální prvek skoro nulový a pravá strana je taky témìø nulová, tak má pøíklad nekoneènì mnoho øešení (singulární matice).
                cout << "Existuje nekonecne mnoho reseni." << endl;
                return vector<double>();
            }
        }

        // Zpìtná substituce
        // Vytvoøení vektoru x pro uložení øešení. Vektor má stejnou délku jako poèet neznámých (n).

        vector<double> x(n);

        // Zde probìhne zpìtná substituce pro øešení lineárních rovnic.
        for (int i = n - 1; i >= 0; i--) {
            // Øádek i - zaèíná od prvního a jde dolù -> (kromì posledního)

            // Nastavení poèáteèní hodnoty vektoru x na odpovídající pravou stranu rovnice (prvek v matici A na pozici [i][n]).
            x[i] = A[i][n];

            // Nyní je tøeba projít všechny øádky pod øádkem i
            for (int j = i + 1; j < n; j++) {

                // V tomto cyklu se prochází prvky nad hlavní diagonálou (v horní èásti matice),
                // a tyto hodnoty se odèítají od aktuálního prvku na pozici [i][j] násobeného odpovídajícím prvkem vektoru x.
                x[i] -= A[i][j] * x[j];
            }

            // Nakonec se aktuální hodnota vektoru x dìlí prvkem na diagonále (na pozici [i][i]) pro nalezení koneèné hodnoty øešení.
            x[i] /= A[i][i];
        }

        return x;
    }
};

int main() {

    // Deklarace matice A_1 - dvourozmìrný vektor
    vector<vector<double>> A_1 = {
        {1, 2, -3, 4, 5},
        {2, 1, 0, 3, 0},
        {0, 2, 1, 2, -1},
        {3, -1, 0, 5, 2},
        {2, 1, 2, 3, -4}
    };

    // Deklarace pravé strany matice - vektor B_1
    vector<double> B_1 = { 4, 9, 5, 3, 2 };

    // Vytvoøení instance solveru a volání funkce pro výpoèet matice.
    GaussianElimination matrixSolver;
    vector<double> solution = matrixSolver.count(A_1, B_1);

    if (!solution.empty()) {

        cout << "Reseni matice pomoci Gaussovy eliminacni metody: " << endl;

        // Výpis øešení matice
        int i = 1;
        for (double x : solution) {
            cout << "x" << i << " = " << x << " ";
            i++;
            cout << endl;
        }
    }

    return 0;
}
