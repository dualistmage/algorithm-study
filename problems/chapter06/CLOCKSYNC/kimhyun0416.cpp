#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
// linked[i][j] = 'x': i�� ����ġ�� j�� �ð谡 ����Ǿ� �ִ�.
// linked[i][j] = '.': i�� ����ġ�� j�� �ð谡 ����Ǿ� ���� �ʴ�.
int linked[SWITCHES][CLOCKS] = { // 0123456789012345
                        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1},
                        {1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
                        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
                        {0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1},
                        {0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0}};

// ��� �ð谡 12�ø� ����Ű�� �ִ��� Ȯ���Ѵ�.
bool areAligned(const vector<int>& clocks){
    int cnt = 0;
    for(int i = 0; i< CLOCKS; i++){
        if(clocks[i]==4) cnt++;
    }
    if (cnt==CLOCKS) return true;
    else return false;
}

// swt�� ����ġ�� ������.
void push(vector<int>& clocks, int swt){
    for(int clock = 0; clock < CLOCKS; clock++){
        if(linked[swt][clock] == 1){
            clocks[clock] += 1;
            if(clocks[clock] == 5) clocks[clock] = 1;
        }
    }
}

// clocks: ���� �ð���� ����
// swt: �̹��� ���� ����ġ�� ��ȣ
// �� �־��� ��, ���� ����ġ���� ������ clocks�� 12�÷� ����� �ִ� �ּ� Ƚ���� ��ȯ
// ���� �Ұ����ϴٸ� INF �̻��� ū �� ��ȯ
int solve(vector<int>& clocks, int swt){
    if(swt == SWITCHES) return areAligned(clocks) ? 0 : INF;
    // �� ����ġ�� 0�� ������ ������ �� �� ������ �������� ��� �õ��Ѵ�.
    int ret = INF;
    for(int cnt=0; cnt < 4; cnt++){
        ret = min(ret, cnt + solve(clocks, swt + 1));
        push(clocks, swt);
    }

    //push(clocks, swt)�� �� �� ȣ��Ǿ����� clocks�� ������ ���� ���°� �ȴ�.
    return ret;
}


int main(int argc, char* argv[])
{

    int count = 0, x = 0, y = 0;

    cin >> count;
	
    vector<int> clocks;
    clocks.resize(CLOCKS);
    while (count > 0){
        for(int i = 0; i< CLOCKS; i++){
            cin >> clocks[i];
            clocks[i] = clocks[i] /3;
            //cout << "clocks[ " << i << "]: " << clocks[i] << endl;
        }
        int answer = solve(clocks,0);
        if(answer>=INF) answer = -1;
        cout << answer << endl;
        count--;
    }

    return 0;

    /*
    for(int ln = 0; ln < y; ln++){
            cin >> block_[ln];
            vector<int> child;
            for(int i=0; i<x; i++){
                tmp = block_[ln][i];
                if(strcmp(tmp.c_str(),"#")==0) child.push_back(1);
                else child.push_back(0);
            }
            vec.push_back(child);
            child.clear();
        }
        cout << cover(vec) << endl;
        vec.clear();
        }
    */
}


