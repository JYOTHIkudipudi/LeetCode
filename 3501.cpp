/*  3501. Maximize Active Section with Trade II
You are given a binary string s of length n, where:

'1' represents an active section.
'0' represents an inactive section.
You can perform at most one trade to maximize the number of active sections in s. In a trade, you:

Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
Additionally, you are given a 2D array queries, where queries[i] = [li, ri] represents a substring s[li...ri].

For each query, determine the maximum possible number of active sections in s after making the optimal trade on the substring s[li...ri].

Return an array answer, where answer[i] is the result for queries[i].

Note

For each query, treat s[li...ri] as if it is augmented with a '1' at both ends, forming t = '1' + s[li...ri] + '1'. The augmented '1's do not contribute to the final count.
The queries are independent of each other.
 

Example 1:

Input: s = "01", queries = [[0,1]]

Output: [1]

Explanation:

Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.

Example 2:

Input: s = "0100", queries = [[0,3],[0,2],[1,3],[2,3]]

Output: [4,3,1,1]

Explanation:

Query [0, 3] → Substring "0100" → Augmented to "101001"
Choose "0100", convert "0100" → "0000" → "1111".
The final string without augmentation is "1111". The maximum number of active sections is 4.

Query [0, 2] → Substring "010" → Augmented to "10101"
Choose "010", convert "010" → "000" → "111".
The final string without augmentation is "1110". The maximum number of active sections is 3.

Query [1, 3] → Substring "100" → Augmented to "11001"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.

Query [2, 3] → Substring "00" → Augmented to "1001"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.

Example 3:

Input: s = "1000100", queries = [[1,5],[0,6],[0,4]]

Output: [6,7,2]

Explanation:

Query [1, 5] → Substring "00010" → Augmented to "1000101"
Choose "00010", convert "00010" → "00000" → "11111".
The final string without augmentation is "1111110". The maximum number of active sections is 6.

Query [0, 6] → Substring "1000100" → Augmented to "110001001"
Choose "000100", convert "000100" → "000000" → "111111".
The final string without augmentation is "1111111". The maximum number of active sections is 7.

Query [0, 4] → Substring "10001" → Augmented to "1100011"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 2.

Example 4:

Input: s = "01010", queries = [[0,3],[1,4],[1,3]]

Output: [4,4,2]

Explanation:

Query [0, 3] → Substring "0101" → Augmented to "101011"
Choose "010", convert "010" → "000" → "111".
The final string without augmentation is "11110". The maximum number of active sections is 4.

Query [1, 4] → Substring "1010" → Augmented to "110101"
Choose "010", convert "010" → "000" → "111".
The final string without augmentation is "01111". The maximum number of active sections is 4.

Query [1, 3] → Substring "101" → Augmented to "11011"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 2.

 

Constraints:

1 <= n == s.length <= 105
1 <= queries.length <= 105
s[i] is either '0' or '1'.
queries[i] = [li, ri]
0 <= li <= ri < n  *?   */

class Solution {
public:

    struct Group {
        int start;
        int length;
    };


    class SparseTable {
    public:

        vector<vector<int>> st;
        vector<int> lg;

        SparseTable(vector<int>& a) {

            int n = a.size();

            lg.assign(n + 1, 0);

            for(int i = 2; i <= n; i++)
                lg[i] = lg[i/2] + 1;


            st.assign(lg[n] + 1, vector<int>(n));

            st[0] = a;


            for(int j = 1; (1<<j) <= n; j++) {

                for(int i = 0; i + (1<<j) <= n; i++) {

                    st[j][i] = max(
                        st[j-1][i],
                        st[j-1][i+(1<<(j-1))]
                    );
                }
            }
        }


        int query(int l,int r){

            if(l > r)
                return 0;

            int j = lg[r-l+1];

            return max(
                st[j][l],
                st[j][r-(1<<j)+1]
            );
        }
    };



    pair<vector<Group>, vector<int>> getZeroGroups(string &s){

        vector<Group> groups;
        vector<int> index(s.size(),-1);


        for(int i=0;i<s.size();i++){

            if(s[i]=='0'){

                if(i>0 && s[i-1]=='0')
                    groups.back().length++;

                else
                    groups.push_back({i,1});
            }

            index[i]=groups.size()-1;
        }


        return {groups,index};
    }



    vector<int> getAdjacentGroupLengthSums(vector<Group>& groups){

        vector<int> ans;


        for(int i=0;i+1<groups.size();i++){

            ans.push_back(
                groups[i].length +
                groups[i+1].length
            );
        }


        return ans;
    }



    pair<int,int> mapToAdjacentGroupIndices(
        int l,int r){

        return {l,r-1};
    }



    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries) {


        int ones = 0;

        for(char c:s)
            ones += c=='1';



        auto [zeroGroups, zeroIndex] =
            getZeroGroups(s);



        if(zeroGroups.empty())
            return vector<int>(queries.size(),ones);



        vector<int> values =
            getAdjacentGroupLengthSums(zeroGroups);



        SparseTable st(values);



        vector<int> ans;



        for(auto &q:queries){

            int l=q[0];
            int r=q[1];


            int left =
                zeroIndex[l]==-1 ? -1 :
                zeroGroups[zeroIndex[l]].length -
                (l-zeroGroups[zeroIndex[l]].start);



            int right =
                zeroIndex[r]==-1 ? -1 :
                (r-zeroGroups[zeroIndex[r]].start+1);



            int best=ones;



            int leftGroup = zeroIndex[l];
            int rightGroup = zeroIndex[r];



            auto [a,b] =
                mapToAdjacentGroupIndices(
                    leftGroup+1,
                    (s[r]=='1'
                     ? rightGroup
                     : rightGroup-1)
                );



            if(s[l]=='0' &&
               s[r]=='0' &&
               leftGroup+1==rightGroup){

                best=max(
                    best,
                    ones+left+right
                );
            }


            else if(a<=b){

                best=max(
                    best,
                    ones+st.query(a,b)
                );
            }



            // left boundary zero group
            if(s[l]=='0' &&
               leftGroup+1<=
               (s[r]=='1'?rightGroup:rightGroup-1)){


                best=max(
                    best,
                    ones+
                    left+
                    zeroGroups[leftGroup+1].length
                );
            }



            // right boundary zero group
            if(s[r]=='0' &&
               leftGroup<rightGroup-1){


                best=max(
                    best,
                    ones+
                    right+
                    zeroGroups[rightGroup-1].length
                );
            }


            ans.push_back(best);
        }


        return ans;
    }
};
