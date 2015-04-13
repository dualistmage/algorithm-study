#include <iostream>

using namespace std;


class ClockSync {
public:
	static const int TWELVE_OCLOCK = 0;
	static const int CLOCK_SIZE = 16;
	static const int SWITCH_SIZE = 10;
	static const int MAX_CLICK_COUNT = 4;
	static const int SWITCHS[SWITCH_SIZE][CLOCK_SIZE];
	static const int MAX_RESULT = 987654321;

public: // methods
	int getCountOfSwitchClick(int switchNo);
	bool isClockDone();
	void clickSwitch(int switchNo);

public: // fields
	int clocks_[CLOCK_SIZE];
};

int main(int argc, char* argv[])
{
	int count = 0;
	ClockSync clockSync;
	int tmpClock;

	cin >> count;
	while (count > 0)
	{
		for (int i = 0; i < ClockSync::CLOCK_SIZE; ++i)
		{
			cin >> tmpClock;
			clockSync.clocks_[i] = (tmpClock % 12) / 3;
		}
		int result = clockSync.getCountOfSwitchClick(0);
		if (result == ClockSync::MAX_RESULT)
			result = -1;
		cout << result << endl;
		count--;
	}
}

const int ClockSync::SWITCHS[ClockSync::SWITCH_SIZE][ClockSync::CLOCK_SIZE] = {
	// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 0
	{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0 }, // 1 
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 }, // 2
	{ 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, // 3
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0 }, // 4
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, // 5
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, // 6
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 }, // 7
	{ 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 8
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 }, // 9
};

int ClockSync::getCountOfSwitchClick(int switchNo)
{
	if (isClockDone())
		return 0;
	if (switchNo == SWITCH_SIZE)
		return MAX_RESULT;

	int minCount = MAX_RESULT;
	int prevCount;

	for (int switchClickTime = 0; switchClickTime < MAX_CLICK_COUNT; ++switchClickTime)
	{
		prevCount = getCountOfSwitchClick(switchNo + 1);
		if (minCount > prevCount + switchClickTime)
			minCount = prevCount + switchClickTime;
		clickSwitch(switchNo);
	}
	return minCount;
}

bool ClockSync::isClockDone()
{
	for (int i = 0; i < CLOCK_SIZE; ++i)
	{
		if (clocks_[i] != TWELVE_OCLOCK)
			return false;
	}
	return true;
}

void ClockSync::clickSwitch(int switchNo)
{
	for (int i = 0; i < CLOCK_SIZE; ++i)
		clocks_[i] = (clocks_[i] + SWITCHS[switchNo][i]) % MAX_CLICK_COUNT;
}


