#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
// linked[i][j] = 'x': i번 스위치와 j번 시계가 연결되어 있다.
// linked[i][j] = '.': i번 스위치와 j번 시계가 연결되어 있지 않다.
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

// 모든 시계가 12시를 가리키고 있는지 확인한다.
bool areAligned(const vector<int>& clocks){
    int cnt = 0;
    for(int i = 0; i< CLOCKS; i++){
        if(clocks[i]==4) cnt++;
    }
    if (cnt==CLOCKS) return true;
    else return false;
}

// swt번 스위치를 누른다.
void push(vector<int>& clocks, int swt){
    for(int clock = 0; clock < CLOCKS; clock++){
        if(linked[swt][clock] == 1){
            clocks[clock] += 1;
            if(clocks[clock] == 5) clocks[clock] = 1;
        }
    }
}

// clocks: 현재 시계들의 상태
// swt: 이번에 누를 스위치의 번호
// 가 주어질 때, 남은 스위치들을 눌러서 clocks를 12시로 맞출수 있는 최소 횟수를 반환
// 만약 불가능하다면 INF 이상의 큰 수 반환
int solve(vector<int>& clocks, int swt){
    if(swt == SWITCHES) return areAligned(clocks) ? 0 : INF;
    // 이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
    int ret = INF;
    for(int cnt=0; cnt < 4; cnt++){
        ret = min(ret, cnt + solve(clocks, swt + 1));
        push(clocks, swt);
    }

    //push(clocks, swt)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 된다.
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


