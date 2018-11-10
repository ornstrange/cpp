#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

typedef unsigned int uint; // unsigned int er alltof langt orð
#define rep(i,a,b) for(int i = (a); i < (b); i++) // styttri for loop
#define ctoi(x) static_cast<int>(x & 0xFF) // prentar char sem int

bool ipStringToArray(string ipS, char *ip) {
    string temp = "";
    int iTemp, index = 0;
    ipS += ".";
    for (int i = 0; i < ipS.size(); i++) {
        if (ipS[i] != '.') {
            if (int(ipS[i]) > 57 || int(ipS[i]) < 48) // bara [0, 9] engir bókstafir
                return false;
            temp += ipS[i];
        } else {
            stringstream byte(temp);
            byte >> iTemp;
            if(iTemp > 255 || iTemp < 0) // tala á bilinu [0, 255]
                return false;
            ip[index] = (char)iTemp;
            temp = "";
            index++;
        }
    }
    return (index != 4) ? false : true; // rétt lengd
}

bool bitsStringToBits(string bStr, vector<int>& bits) {
    string sTemp = "";
    int iTemp;
    bStr += ",";
    for (int i = 0; i < bStr.size(); i++) {
        if (bStr[i] != ',') {
            if (int(bStr[i]) > 57 || int(bStr[i]) < 48) // bara [0, 9] engir bókstafir
                return false;
            sTemp += bStr[i];
        } else {
            stringstream byte(sTemp);
            byte >> iTemp;
            bits.push_back(iTemp);
            sTemp = "";
        }
    }
    return true;
}

void uitoa(uint submaskui, char *mask) {
    rep(i,0,4)
        mask[i] = submaskui << (i * 8) >> ((3 - i) * 8);
}

int msb(int n) {
    if (n == 0)
        return 0;

    int msb = 0;
    while (n != 0) {
        n = n / 2;
        msb++;
    }

    return msb;
}


int main() {

    string ipString, bitsString, even;
    char ip[4], mask[4];
    int netBit, split, netsHowMany, netBitHowBig;
    uint subnetMaskUi;
    bool loopBreak = false;
    vector<int> bits;

    cout << "Sláðu inn ip-töluna: ";
    cin >> ipString;
    while (!ipStringToArray(ipString, ip)) {
        cout << "Ekki alveg rétt ip-tala... reyndu aftur" << endl;
        cout << "Sláðu inn ip-töluna: ";
        cin >> ipString;
    }

    cout << "Sláðu inn netbita upphafs ip-tölu: ";
    cin >> netBit;
    while (netBit < 1 || netBit > 31) { // man ekki alveg mörkin...
        cout << "Held að þetta gangi ekki alveg upp... reyndu aftur" << endl;
        cout << "Sláðu inn netbita upphafs ip-tölu: ";
        cin >> netBit;
    }
    subnetMaskUi = (0xFFFFFFFF >> (32 - netBit)) << (32 - netBit);
    uitoa(subnetMaskUi, mask);

    cout << "Eiga öll netin að vera jafn stór (j/n): ";
    cin >> even;
    
    while (!loopBreak) {
        if (even == "j") {
            cout << "Sláðu inn fjölda neta: ";
            cin >> netsHowMany;
            cout << "Sláðu inn fjölda hosta fyrir hvert net: ";
            cin >> netBitHowBig;
            rep(i, 0, netsHowMany)
                bits.push_back(netBitHowBig);
            loopBreak = true;
        } else if (even == "n") {
            cout << "Sláðu inn fjölda hosta á hverju neti með kommu á milli: ";
            cin >> bitsString;
            bitsStringToBits(bitsString, bits);
            loopBreak = true;
        } else {
            cout << "Ég skildi þetta ekki... reyndu aftur" << endl;
            cout << "Eiga öll netin að vera jafn stór (j/n): ";
            cin >> even;
        }
    }

    rep(i,0,bits.size()) {
         
    }

    return 0;
}
