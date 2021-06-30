#include<bits/stdc++.h>

using namespace std;

vector<int> get_z(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
        if (r <= i){
            l = r = i;
            while (r < n && s[r] == s[r-l]) r++;
            z[i] = r-i;
        }
        else{
            if (z[i-l] < (r - i))
                z[i] = z[i-l];
            else{
                l = i;
                while (r < n && s[r] == s[r-l]) r++;
                z[i] = r-i;
            }
        }
    return z;
}

int main(){
    string s; cin >> s;
    auto z = get_z(s);
    for (auto x: z)
        cout << x << " ";
    cout << "\n";
    return 0;
}
