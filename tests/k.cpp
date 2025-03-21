#include "../tlist.cpp"
#include <iostream>
using namespace std;

tlist<int> ls;

int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    while(n--) {
        int x; cin >> x;
        ls.append(x);
    }
    while(q--) {
        int opt, a;
        cin >> opt >> a;
        switch (opt) {
            case 1:
                cout << ls.query(a-1) << endl;
                break;
            case 2:
                ls.insert(a-1, a);
                break;
            case 3:
                ls.remove(a-1);
                break;
        }
    }
}
