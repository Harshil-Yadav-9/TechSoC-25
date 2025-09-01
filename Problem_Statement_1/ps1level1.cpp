#include <iostream>
#include <string>
using namespace std;

string DM(string text, int shift, bool encode = true) {
    string result ="";
    if (!encode) {
        shift = -shift;
    }
    for (char c : text) {
        if (isupper(c)) {
            result += char(int((c - 'A' + shift + 26) % 26) + 'A');
        } 
        else if (islower(c)) {
            result += char(int((c - 'a' + shift + 26) % 26) + 'a');
        } 
        else {
            result += c;
        }
    }
    return result;
}
int main() {
    string message;
    int shift;
    cout << "Enter a message: ";
    cin >> message;
    cout << "Enter shift value: ";
    cin >> shift;
    string encoded = DM(message, shift, true);
    string decoded = DM(encoded, shift, false);
    cout << "Encoded message: " << encoded << endl;
    cout << "Decoded message: " << decoded << endl;
    return 0;
}
