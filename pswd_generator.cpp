#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const char Alphanumericchar[] = "0123456789!@#$%^&*_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int str_len = sizeof(Alphanumericchar);

int main() {
    int length = 0;

    cout << "Enter the Length of the password: ";
    cin >> length;

    srand(time(0));

    if (length < 14) {
        cout << "Password length should be at least 14 characters." << endl;
    } else {
        cout << "Generated Password: ";
        for (int i = 0; i < length; i++) {
            cout << Alphanumericchar[rand() % str_len];
        }
        cout << endl;
    }

    return 0;
}
