#include <bits/stdc++.h>
#define __ ios_base::sync_with_stdio(0);cin.tie(0);

#define FI first
#define SE second
#define MP make_pair
#define PB push_back

using namespace std;

const int MAXN = 100004;

class SuffixArray{
    public:
    const int static MAXN = 100004;
    
    char s[MAXN];
    int n, sa[MAXN], temsa[MAXN], lcp[MAXN], pos[MAXN], ct[MAXN], srank[MAXN], SIZE;
    pair<int, int> key[MAXN];
    // sort by 2nd key, then by 1st key
    // 1st key = srank
    
    void reads(){
        scanf("%s", s+1);
        n = strlen(s+1);    
    }
    
    void buildSA(){
        for (int i=1; i<=n; i++) key[i] = MP(s[i], 0);
        SIZE = max(300, n);
        
        for (int L=1; L<=n*2; L*=2){
            for (int i=0; i<=SIZE; i++) ct[i] = 0;
            for (int i=1; i<=n; i++) ct[key[i].SE]++;
            for (int i=1; i<=SIZE; i++) ct[i]+=ct[i-1];
            
            for (int i=n; i>0; i--){
                int k = key[i].SE;
                temsa[ct[k]--] = i;
            }            
            
            for (int i=0; i<=SIZE; i++) ct[i] = 0;
            for (int i=1; i<=n; i++) ct[key[i].FI]++;
            for (int i=1; i<=SIZE; i++) ct[i]+=ct[i-1];
            
            for (int i=n; i>0; i--){
                int k = key[temsa[i]].FI;
                sa[ct[k]--] = temsa[i];
            }            
            
            srank[sa[1]] = 1;
            for (int i=2; i<=n; i++){
                srank[sa[i]] = srank[sa[i-1]];
                if (key[sa[i]]!=key[sa[i-1]]) srank[sa[i]]++;
            }            
            
            for (int i=1; i<=n; i++){
                key[i].FI = srank[i];
                if (i+L<=n) key[i].SE = srank[i+L];
                else
                    key[i].SE = 0;
            }
        }    
    }
    
    void buildLCP(){
        int Phi[MAXN], PLCP[MAXN];
        Phi[sa[1]] = -1;
        for (int i = 1; i<=n; i++) Phi[sa[i]] = sa[i-1];
        for (int i=1, L=0; i<=n; i++){
            if (Phi[i] == -1){
                PLCP[i] = 0;
                continue;
            }
            
            while (s[i+L] == s[Phi[i] + L]) L++;
            PLCP[i] = L;
            L = max(L-1, 0);
        }
        
        for (int i=1; i<=n; i++) lcp[i] = PLCP[sa[i]];    
    }
};

int main(){ __
    SuffixArray sf;
    char s1[MAXN], s2[MAXN], s3[MAXN];
    scanf("%s%s%s", s1, s2, s3);
}
