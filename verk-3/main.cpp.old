// Örn Óli Strange
// 25.09.18

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

typedef unsigned int uint; // nenni ekki að skrifa alltaf unsigned int
#define rep(i,a,b) for(int i = (a); i < (b); i++) // styttri for loop

void uitoa(uint num, uint *arr) { // unsigned int í array
    rep(i,0,4) arr[i] = num << i*8 >> 24;
}

uint atoui(uint *arr) {
    uint output;
    output = arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3];
    return output;
}

void addToIp(uint *arr, uint x = 1) {
    uint temp = atoui(arr) + x;
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

uint * stouia(string input) { // string to unsigned int array
    static uint outArr[4];
    return outArr;
}

void splitIp(string input, uint *ip) {
    sscanf(input, "%hu.%hu.%hu.%hu", &ip[0], &ip[1], &ip[2], &ip[3]);
}


int main() {
    uint ip[4], netMask, netMaskArr[4], bits, div, bitsReq, offset,
         lastOne, magicNumber, ones = 0xffffffff;
    vector<int> hosts;
    string dashLine = "----------------+", ipRaw;

    cout << "Sláðu inn upphafsnet: ";
    cin >> ipRaw;
    ip = splitIp(ipRaw, ip);
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
    uint addAlg[4] = {1, magicNumber - 3, 1, 1};

    rep(i,0,div) {
        rep(j, 0, 4) {
            cout << printIp(ip);
            addToIp(ip, addAlg[j]);
        }
        cout << printIp(netMaskArr) << endl;
    }
    return 0;
}
