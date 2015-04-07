#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;

// 주어진 칸을 덮을 수 있는 네 가지 방법
// 블록을 구성하는 세 칸의 상대적 위치(dy,dx)의 목록
const int coverType[4][3][2] ={
	{ {0,0}, {1,0}, {0,1} },
	{ {0,0}, {0,1}, {1,1} },
	{ {0,0}, {1,0}, {1,1} },
	{ {0,0}, {1,0}, {1,-1} } };
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1 };
const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1 };

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// board의 (y, x)를 type번 방법으로 덥거나, 덥었던 블록을 없앤다.
// delta = 1 이면 덮고, -1 이면 덮었던 블록을 없앤다.
// 만약 블록이 제대로 덮이지 않은 경우(게임판 밖으로 나가, 겹치, 검은 칸을 덮을 때) false 반환
bool setShape(vector<vector<int> >& board, int y, int x, int type, int delta){
	bool ok = true;
	for(int i = 0; i < 3; ++i){
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if(ny < 0  || ny >= board.size() || // 나가
			nx < 0 || nx >= board[0].size())
			ok = false;
		else if((board[ny][nx] += delta) > 1) // 겹치
			ok = false;
	}

	return ok;
}
bool chkWhite(vector<vector<int> >& board,int y,int x){
	int cnt = 0;
	for(int i = 0; i < 8; i++){
		const int ny = y + dy[i];
		const int nx = x + dx[i];
		if(ny < 0  || ny >= board.size() || // 나가
			nx < 0 || nx >= board[0].size()) continue;
		else if(board[ny][nx]==0)
			cnt++;
		if(cnt>2) {
			return false;
		}
	}
	return true; //white가 2개보다 적은 경우(불가능한 경우)
}

// 가능한 경우를 구하는 함수
bool isPossiblePattern(vector<vector<int> >& board, int _y){
	for(int i = _y; i < board.size(); i++){
		for(int j = 0; j < board[i].size(); j++){
			if(board[i][j] == 0){
				if (chkWhite(board,i,j)) {
					//cout << "chkWhite(true) pattern[" << i << "," << j << "]"<< endl;
					return false;
				}
			}
		}
	}
	//cout << "possible phase!! " << endl;
	return true;
}
// board의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환한다.
// board[i][j] = 1 이미 덮인 칸 혹은 검은 칸
// board[i][j] = 0 아직 덮이지 않은 칸
int cover(vector<vector<int> >& board) {
	// 아직 채우지 못한 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
	int y = -1, x = -1;
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board[i].size(); j++){
			if(board[i][j] == 0){
				y = i;
				x = j;
				break;
			}
		}
		if(y != -1) break;
	}
	// 기저 사례: 모든 칸을 채웠으면 1을 반환
	if(y == -1) return 1;
	//if(!isPossiblePattern(board, y)) return 0;

	int ret = 0;
	for(int type = 0; type < 4; type++){
		// 만약 board[y][x]를 type 형태로 덮을 수 있으면 재귀 호출
		if(setShape(board, y, x, type, 1))
			ret += cover(board);
		// 덮었던 블록을 치운다.
		setShape(board, y, x, type, -1);
	}
	return ret;
}

int loadMap(string name){
	ifstream fvt;
	fvt.open(name);

	const char* DELIM = " ";
	int token = -1, x = -1, y = -1;
	vector<vector<int> > vec;

	while (true){
		string buf;
		if (fvt.eof()) break;
		getline(fvt, buf);
		//std::cout << buf << endl;

		char* str = new char[buf.size() + 1];
		const char* p = buf.c_str();
		int i = 0;
		while (i < buf.size()){
			str[i] = p[i];
			i++;
		}
		char* ptr = 0x00;
		string tmp = strtok_s(str, DELIM, &ptr); 
		
		if(token<0) {
			token = atoi(tmp.c_str());
			cout << "load success(token):" << token << endl;
		}
		else{
			if(y<0){
				y = atoi(tmp.c_str());
				tmp = strtok_s(0x00, DELIM, &ptr);
				x = atoi(tmp.c_str());
				cout << "load success(x,y): (" << x << "," << y << ")" << endl;
				vec.clear();
				token--;
			}else if(y==0){
			}else{
				vector<int> child;
				for(int i=0; i<x; i++){
					tmp = str[i];
					if(strcmp(tmp.c_str(),"#")==0) child.push_back(1);
					else child.push_back(0);
				}
				vec.push_back(child);
				child.clear();
				y--;
				if(y==0){
					cout << cover(vec) << endl;
					y--;
				}
			}
		}

	}
	return 0;

}


int main(int argc, char* argv[])
{
	/*
	clock_t start_time, end_time;
	start_time = clock(); // Start-time

	loadMap("BoardCover.txt");

	end_time = clock(); // End-time
	printf("Time:%f\n " ,((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	*/

	int count = 0, x = 0, y = 0;
	char block_[20][20];
	string tmp;
	vector<vector<int> > vec;

	cin >> count;
	
	while (count > 0){
		cin >> y >> x;
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
		/*
		cout << "start print!! vector" << endl;
		for(int ty = 0; ty < vec.size(); ty++){
			for(int tx = 0; tx < x; tx++){
				cout << vec[ty][tx] << "," ;
			}
			cout << endl;
		}*/
		vec.clear();
		count--;
	}

	return 0;

}


