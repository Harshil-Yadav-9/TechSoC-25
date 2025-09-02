#include <bits/stdc++.h>
using namespace std;

int charshift(char c) {
    if (isupper(c)) return c - 'A';
    if (islower(c)) return c - 'a';
    return 0;
}

string CE(const string &text, const string &keyword) {
    string result;
    int k = keyword.size();
    for (size_t i = 0; i < text.size(); i++) {
        char c = text[i];
        int shift = charshift(keyword[i % k]);

        if (isupper(c)) {
            result += char(((c - 'A' + shift) % 26) + 'A');
        } else if (islower(c)) {
            result += char(((c - 'a' + shift) % 26) + 'a');
        } else {
            result += c;
        }
    }
    return result;
}

string CD(const string &text, const string &keyword) {
    string result;
    int k = keyword.size();
    for (size_t i = 0; i < text.size(); i++) {
        char c = text[i];
        int shift = charshift(keyword[i % k]);
        if (isupper(c)) {
            result += char(((c - 'A' - shift + 26) % 26) + 'A');
        } else if (islower(c)) {
            result += char(((c - 'a' - shift + 26) % 26) + 'a');
        } else {
            result += c;
        }
    }
    return result;
}

static const string base64 =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

string base64Encode(const string &input) {
    string output;
    int val = 0, valb = -6;
    for (unsigned char c : input) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            output.push_back(base64[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) output.push_back(base64[((val << 8) >> (valb + 8)) & 0x3F]);
    while (output.size() % 4) output.push_back('=');
    return output;
}

string base64Decode(const string &input) {
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64[i]] = i;

    string output;
    int vala = 0, valb = -8;
    for (unsigned char c : input) {
        if (T[c] == -1) break;
        vala = (vala << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            output.push_back(char((vala >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return output;
}

int main() {
    string message, keyword;
    cout << "Enter message: ";
    getline(cin, message);
    cout << "Enter keyword: ";
    cin >> keyword;
    string caesarEnc = CE(message, keyword);
    string base64Enc = base64Encode(caesarEnc);
    cout << "\nEncrypted : " << base64Enc << endl;
    string base64Dec = base64Decode(base64Enc);
    string caesarDec = CD(base64Dec, keyword);
    cout << "Decrypted (Original): " << caesarDec << endl;
    return 0;
}
 