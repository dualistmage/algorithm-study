#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int count = 0;
    string compStr();

	cin >> count;
	while (count > 0)
	{
        getline(cin, compStr);
        cout << compStr << endl;
		count--;
	}

    return 0;
}
