// Örn Óli Strange
// 21.09.18

#include <iostream>
#include <string>
using namespace std;

int main() {
    unsigned int ip[4];
    int bits, div;
    string dashLine = "----------------+";

    cout << "Sláðu inn upphafsnet: ";
    for (int i = 0; i < 4; i++)
        cin >> ip[i];
    
    cout << "Sláðu inn fjölda netbita í upphafsneti: ";
    cin >> bits;

    cout << "Sláðu inn fjölda neta sem skipta á upphafsnetinu í: ";
    cin >> div;

    cout << endl
         << "Ip net          |" << "Fyrsta Nothæfa  |"
         << "Síðasta nothæfa |" << "Broadcast       |"
         << "Maski           |"  << endl;
    cout << dashLine << dashLine << dashLine << dashLine << dashLine << endl;

    

    return 0;
}
