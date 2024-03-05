#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    int i, j, k = 0, n, repeat_max = 0, cn = 0;
    int array1[50], mode[50], count[50] = { 0 }, c[50];

    cout << "\n inter count:\t";
    cin >> n;


    cout << "\n";

    for (i = 0; i < n; i++)
        cin >> array1[i];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {

            if (array1[i] == array1[j])
            {
                count[i]++;
                if (count[i] >= repeat_max)
                {
                    repeat_max = count[i];
                    mode[k++] = array1[i];
                }
            }
        }
    }
    cout << "\n================\n";
    for (i = 1; i < k; i++)
        cout << "\t mode[i]=" << mode[i] << "\n";
    cout << "\t\n\nrepeat array:" << repeat_max;

    return 0;