// Örn Óli Strange
// 25.09.18

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef unsigned int uint; // nenni ekki að skrifa alltaf unsigned int
#define rep(i,a,b) for(int i = (a); i < (b); i++) // styttri for loop

void uitoa(uint num, uint *arr) { // unsigned int í array
    rep(i,0,4) {
        arr[i] = num << i*8 >> 24;
    }
}

uint atoui(uint *arr) {
    uint output;
    output = arr[0] << 24 | arr[1] << 16 |
             arr[2] << 8 | arr[3];
    return output;
}

void addToIp(uint *arr, uint x = 1) {
    uint temp = atoui(arr);
    temp += x;
    uitoa(temp, arr);
}

string printIp(uint *ip) { // prenta ip fallega
    string output = "";
    int len;
    rep(i,0,3) output += to_string(ip[i]) + ".";
    output += to_string(ip[3]);
    len = output.length();
    rep(i,0,16 - len) output += " ";
    output += "|";
    return output;
}

int main() {
    uint ip[4], netMask, netMaskArr[4], bits, div, bitsReq, offset,
         lastOne, magicNumber, ones = 0xffffffff;
    string dashLine = "----------------+";

    cout << "Sláðu inn upphafsnet: ";
    rep(i,0,4) cin >> ip[i];
    offset = ip[3];
 
    cout << "Sláðu inn fjölda netbita í upphafsneti: ";
    cin >> bits;

    cout << "Sláðu inn fjölda neta sem skipta á upphafsnetinu í: ";
    cin >> div;

    cout << endl
         << "Ip net          |" << "Fyrsta Nothæfa  |"
         << "Síðasta nothæfa |" << "Broadcast       |"
         << "Maski           |"  << endl;
    rep(_,0,5) cout << dashLine;
    cout << endl;

    netMask = ones << 32 - (bits + (int)log2(div));
    uitoa(netMask, netMaskArr);
    magicNumber = pow(2, 32 - (bits + (int)log2(div)));

    rep(i,0,div) {
        cout << printIp(ip);
        addToIp(ip);
        cout << printIp(ip);
        addToIp(ip, magicNumber - 3);
        cout << printIp(ip);
        addToIp(ip);
        cout << printIp(ip);
        addToIp(ip);
        cout << printIp(netMaskArr) << endl;
    }
    return 0;
}
