/*  3348. Smallest Divisible Digit Product II

You are given a string num which represents a positive integer, and an integer t.

A number is called zero-free if none of its digits are 0.

Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".

 

Example 1:

Input: num = "1234", t = 256

Output: "1488"

Explanation:

The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.

Example 2:

Input: num = "12355", t = 50

Output: "12355"

Explanation:

12355 is already zero-free and has the product of its digits divisible by 50, with the product of its digits equal to 150.

Example 3:

Input: num = "11111", t = 26

Output: "-1"

Explanation:

No number greater than 11111 has the product of its digits divisible by 26.

 

Constraints:

2 <= num.length <= 2 * 105
num consists only of digits in the range ['0', '9'].
num does not contain leading zeros.
1 <= t <= 1014   */

class Solution {
public:
    static const int MAXE2 = 50, MAXE3 = 35;
    int minDigits[MAXE2+1][MAXE3+1];
    int DE2[10], DE3[10], DE5[10], DE7[10];

    void buildTable(){
        const int INF = 1e9;
        for(int i=0;i<=MAXE2;i++) for(int j=0;j<=MAXE3;j++) minDigits[i][j]=INF;
        minDigits[0][0]=0;
        int opts[6][2] = {{3,0},{2,0},{1,0},{0,2},{0,1},{1,1}}; // digits 8,4,2,9,3,6
        for(int s=1;s<=MAXE2+MAXE3;s++){
            for(int i=max(0,s-MAXE3); i<=min(MAXE2,s); i++){
                int j=s-i;
                int best=INF;
                for(auto &o: opts){
                    int ni=max(0,i-o[0]), nj=max(0,j-o[1]);
                    if(minDigits[ni][nj]<INF) best=min(best,1+minDigits[ni][nj]);
                }
                minDigits[i][j]=best;
            }
        }
    }

    int md(long long i,long long j){
        int ii=(int)min<long long>(max(0LL,i),MAXE2);
        int jj=(int)min<long long>(max(0LL,j),MAXE3);
        return minDigits[ii][jj];
    }

    long long minTotal(long long r2,long long r3,long long r5,long long r7){
        r2=max(0LL,r2); r3=max(0LL,r3); r5=max(0LL,r5); r7=max(0LL,r7);
        return r5+r7+(long long)md(r2,r3);
    }

    void fillGreedy(string &res, long long len, long long r2,long long r3,long long r5,long long r7){
        for(long long pos=0; pos<len; pos++){
            long long rem = len-pos-1;
            for(int e=1;e<=9;e++){
                long long nr2=r2-DE2[e], nr3=r3-DE3[e], nr5=r5-DE5[e], nr7=r7-DE7[e];
                if(minTotal(nr2,nr3,nr5,nr7)<=rem){
                    res += char('0'+e);
                    r2=max(0LL,nr2); r3=max(0LL,nr3); r5=max(0LL,nr5); r7=max(0LL,nr7);
                    break;
                }
            }
        }
    }

    string smallestNumber(string num, long long t) {
        buildTable();
        int de[10][4] = {{},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},{0,0,1,0},
                          {1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}};
        for(int d=1; d<=9; d++){
            DE2[d]=de[d][0]; DE3[d]=de[d][1]; DE5[d]=de[d][2]; DE7[d]=de[d][3];
        }

        long long e2=0,e3=0,e5=0,e7=0, tt=t;
        while(tt%2==0){tt/=2;e2++;}
        while(tt%3==0){tt/=3;e3++;}
        while(tt%5==0){tt/=5;e5++;}
        while(tt%7==0){tt/=7;e7++;}
        if(tt!=1) return "-1";

        int n = num.size();
        vector<long long> P2(n+1,0),P3(n+1,0),P5(n+1,0),P7(n+1,0);
        int firstZero=-1;
        for(int i=0;i<n;i++){
            int d=num[i]-'0';
            P2[i+1]=P2[i]+(d? DE2[d]:0);
            P3[i+1]=P3[i]+(d? DE3[d]:0);
            P5[i+1]=P5[i]+(d? DE5[d]:0);
            P7[i+1]=P7[i]+(d? DE7[d]:0);
            if(d==0 && firstZero==-1) firstZero=i;
        }

        // Step A: num itself
        if(firstZero==-1 && P2[n]>=e2 && P3[n]>=e3 && P5[n]>=e5 && P7[n]>=e7)
            return num;

        // Step B: same length, rightmost feasible bump
        int maxIdx = (firstZero==-1)? n-1 : min(n-1, firstZero);
        for(int idx=maxIdx; idx>=0; idx--){
            int origDigit = num[idx]-'0';
            long long p2=P2[idx],p3=P3[idx],p5=P5[idx],p7=P7[idx];
            for(int d=origDigit+1; d<=9; d++){
                long long np2=p2+DE2[d], np3=p3+DE3[d], np5=p5+DE5[d], np7=p7+DE7[d];
                long long r2=e2-np2, r3=e3-np3, r5=e5-np5, r7=e7-np7;
                long long remLen = n-idx-1;
                if(minTotal(r2,r3,r5,r7) <= remLen){
                    string res = num.substr(0,idx);
                    res += char('0'+d);
                    fillGreedy(res, remLen, r2, r3, r5, r7);
                    return res;
                }
            }
        }

        // Step C: need a longer number
        long long baseMin = minTotal(e2,e3,e5,e7);
        long long L = max((long long)n+1, baseMin);
        string res;
        fillGreedy(res, L, e2, e3, e5, e7);
        return res;
    }
};
