#include <iostream>
#include <set>
#include <vector>
using namespace std;

template<class T>
using tlist=set<pair<unsigned int, T>>;

vector<int> arr;

int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> q;
    arr.resize(n+q, 0);
    for(int i=1;i<=n;i++) {
        cin >> arr[i];
    }
    while(q--) {
        int opt, a;
        cin >> opt >> a;
        switch (opt) {
            case 1:
                cout << arr[a] << endl;
                break;
            case 2:
                arr.insert(arr.begin()+a, a);
                break;
            case 3:
                arr.erase(arr.begin()+a);
                break;
        }
    }
}
