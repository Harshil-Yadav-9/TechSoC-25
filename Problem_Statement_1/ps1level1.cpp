#include <bits/stdc++.h>
using namespace std;

vector<double> ef = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

string cs(const string &text, int shift) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base - shift + 26) % 26 + base);
        } else {
            result += c;
        }
    }
    return result;
}

double st(const string &text) {
    vector<int> count(26, 0);
    int total = 0;

    for (char c : text) {
        if (isalpha(c)) {
            count[toupper(c) - 'A']++;
            total++;
        }
    }

    if (total == 0) return 1e9;

    double chisq = 0.0;
    for (int i = 0; i < 26; i++) {
        double observed = count[i];
        double expected = ef[i] * total / 100.0;
        chisq += ((observed - expected) * (observed - expected)) / (expected + 1e-6);
    }
    return chisq;
}

string autodecode(const string &cipher) {
    double bestscore = 1e18;
    string bestdecryption = "";
    int bestshift = 0;

    for (int shift = 1; shift < 26; shift++) {
        string decoded = cs(cipher, shift);
        double score = st(decoded);

        if (score < bestscore) {
            bestscore = score;
            bestdecryption = decoded;
            bestshift = shift;
        }
    }

    cout << "Best shift found: " << bestshift << endl;
    return bestdecryption;
}

int main() {
    string cipher;
    cout << "Enter the encoded message: ";
    getline(cin, cipher);

    string decoded = autodecode(cipher);
    cout << "Decoded message: " << decoded << endl;

    return 0;
}
