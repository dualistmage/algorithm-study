#include <iostream>
#include <string>

using namespace std;

int calculateEnd(const string& tree, int start);
void reverse(string& tree, int start, int end);
void swap(string& tree, int start, int half, int end);


int main(int argc, char* argv[])
{
    int count = 0;
    string compStr;

    cin >> count;
    while (count > 0)
    {
        cin >> compStr;
        reverse(compStr, 0, static_cast<int>(compStr.length()));
        cout << compStr << endl;
        count--;
    }

    return 0;
}

int calculateEnd(const string& tree, int start)
{
    int cur = start;
    int end = start;
    while( cur <= end )
    {
        if( tree[cur] == 'x' )
            end += 4;
        cur++;
    }
    return cur;
}

void reverse(string& tree, int start, int end)
{
    if( start >= end - 1 )
        return;
    int firstEnd, secondEnd, thirdEnd, fourthEnd;
    firstEnd  = calculateEnd(tree, start);
    if( firstEnd == end )
    {
        reverse(tree, start + 1, end);
        return;
    }
    secondEnd = calculateEnd(tree, firstEnd);
    thirdEnd  = calculateEnd(tree, secondEnd);
    fourthEnd = calculateEnd(tree, thirdEnd);
    reverse( tree, start,     firstEnd);
    reverse( tree, firstEnd, secondEnd);
    reverse( tree, secondEnd, thirdEnd);
    reverse( tree, thirdEnd, fourthEnd);
    swap(tree, start, secondEnd, fourthEnd);
}

void swap(string& tree, int start, int half, int end)
{
    string tmpTree = tree;
    tmpTree.replace(start, end - half, tree, half, end - half);
    tmpTree.replace(start + end - half, half - start, tree, start, half - start);
    tree.swap( tmpTree );
}
