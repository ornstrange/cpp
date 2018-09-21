#include <iostream>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

int main(void) {
    int sel, num;
    string kind, out;
    
    cout << "Talnakerfisbreytir" << endl << endl;
    cout << "1 - Breyta í tvíundakerfið" << endl;
    cout << "2 - Breyta í áttundakerfið" << endl;
    cout << "3 - Breyta í sextándakerfið" << endl;
    cout << "0 - Hætta" << endl;
    cout << "---------------------------" << endl;

    cout << "Veldu aðgerð: ";
    cin >> sel;
   
    while (sel != 0) {
        if (sel == 1 || sel == 2 || sel == 3) {
            cout << endl << "Sláðu inn tugakerfistölu: ";
            cin >> num;

            cout << "Tugakerfistalan " << num << " er ";

            switch(sel) {
                case 1 :
                    kind = "tvíundakerfinu";
                    if (ceil(log2(num+1)) > 16) {
                        cout << bitset<32>(num);
                    } else if (ceil(log2(num+1)) > 8) {
                        cout << bitset<16>(num);
                    } else {
                        cout << bitset<8>(num);
                    }
                    break;
                case 2 :
                    kind = "áttundakerfinu";
                    cout << oct << num;
                    break;
                case 3 :
                    kind = "sextándakerfinu";
                    cout << hex << num;
                    break;
            }
            
            cout << " í " << kind << endl << endl;
            
            cout << "Veldu aðgerð: ";
            cin >> sel;
        } else {
            cout << endl << "Rangt val, reyndu aftur!" << endl;
            cout << "Veldu aðgerð á bilinu 0 - 3: ";
            cin >> sel;
        }
    }

    return 0;
}
