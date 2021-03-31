#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long ans;
namespace SAM{
    int trans[2000100][26],maxlen[2000100],sz[2000100],link[2000100],Nodecnt,last,barrel[2000100],rank[2000100];
    void init(void){
        Nodecnt=0;
        last=0;
        link[0]=-1;
        maxlen[0]=0;
    }
    void append(int x){
        int o = ++Nodecnt;
        maxlen[o] = maxlen[last] + 1;
        sz[o] = 1;
        int p = last;
        while(p!=-1 && (!trans[p][x]) ){
            trans[p][x] = o;
            p = link[p];
        }
        if(p == -1){
            link[o] = 0;
            last = o;
            return;
        }
        int y = trans[p][x];
        if(maxlen[p]+1 == maxlen[y]){
            link[o] = y;
        }
        else{
            int z = ++Nodecnt;
            for(int j=0;j<26;j++)
                trans[z][j] = trans[y][j];
            maxlen[z] = maxlen[p]+1; //!
            while(p!=-1 &&(trans[p][x] == y)){
                trans[p][x] = z;
                p = link[p];
            }
            link[z] = link[y];
            link[y] = z;
            link[o] = z;
        }
        last = o;
    }
    void CalcSz(void){
        int maxsz = 0;
        for(int i=1;i<=Nodecnt;i++){
            barrel[maxlen[i]]++;
            maxsz = max(maxsz,maxlen[i]);
        }
        for(int i=1;i<=maxsz;i++)
            barrel[i]+=barrel[i-1];
        for(int i=1;i<=Nodecnt;i++)
            rank[barrel[maxlen[i]]--] = i;
        for(int i=Nodecnt;i>=1;i--){
            int tmp = rank[i];
            sz[link[tmp]]+=sz[tmp];
        }
    }
    void CalcAns(void){
        for(int i=1;i<=Nodecnt;i++){
            if(sz[i]>1){
                // printf("%d %d\n",sz[i],maxlen[i]);
                ans=max(ans,1LL*sz[i]*maxlen[i]);
            }
        }
    }
};
char s[1000100];

int main(){
    ans = 0;
    scanf("%s",s+1);
    int n=strlen(s+1);
    SAM::init();
    for(int i=1;i<=n;i++){
        SAM::append(s[i]-'a');
    }
    SAM::CalcSz();
    SAM::CalcAns();
    printf("%lld\n",ans);
    return 0;
}