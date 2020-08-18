/**
 * 
 * LEETCODE 1001 GRID ILLUMINATION:
 * SELF DEVELOPED CODE WORKS 100% FASTER, 90% MEMORY EFFICIENT
 * 
 * On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.
 * Initially, some number of lamps are on.  lamps[i] tells us the location of the i-th lamp that is on.  
 * Each lamp that is on illuminates every square on its x-axis, y-axis, and both diagonals (similar to a Queen in chess).
 * For the i-th query queries[i] = (x, y), the answer to the query is 1 if the cell (x, y) is illuminated, else 0.
 * After each query (x, y) [in the order given by queries], 
 * we turn off any lamps that are at cell (x, y) or are adjacent 8-directionally 
 * (ie., share a corner or edge with cell (x, y).)
 * Return an array of answers.  
 * Each value answer[i] should be equal to the answer of the i-th query queries[i]. 
 * 
 * 
 * Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
 * 
Output: [1,0]
Explanation: 
Before performing the first query we have both lamps [0,0] and [4,4] on.
The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
1 1 1 1 1
1 1 0 0 1
1 0 1 0 1
1 0 0 1 1
1 1 1 1 1
Then the query at [1, 1] returns 1 because the cell is lit.  
After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
1 0 0 0 1
0 1 0 0 1
0 0 1 0 1
0 0 0 1 1
1 1 1 1 1
Before performing the second query we have only the lamp [4,4] on.  Now the query at [1,0] returns 0, because the cell is no longer lit.
 * 
 * 
 * 
*/
class Solution {
public:
    
    Solution(){
        ios_base::sync_with_stdio(false);cin.tie(NULL);
    }
    //Debashish Nanda IITBHU
    
    unordered_multiset<int> hor;
    unordered_multiset<int> ver;
    unordered_multiset<int> di1;
    unordered_multiset<int> di2;
    
    int dx[9] = {0, 0, 0, 1, 1, 1,-1,-1,-1};
    int dy[9] = {0, 1,-1,-1, 0, 1,-1, 0, 1};
    
    void lampoff(int x, int y){
        auto it1 = hor.find(x);
        hor.erase(it1);

        auto it2 = ver.find(y);
        ver.erase(it2);

        auto it3 = di1.find(x-y);
        di1.erase(it3);

        auto it4 = di2.find(x+y);         
        di2.erase(it4);
    }
    
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {        
        unordered_multimap<int,int> lamp_pos;
        
        for(auto it:lamps){
            
            lamp_pos.insert({it[0],it[1]});
            
            hor.insert(it[0]);
            ver.insert(it[1]);
            di1.insert(it[0]-it[1]);
            di2.insert(it[1]+it[0]);
        }
        
        vector<int> ans;
        for(int i=0;i<queries.size();i++){
            int x = queries[i][0];
            int y = queries[i][1];
            if(
                hor.find(x)!=hor.end() ||
                ver.find(y)!=ver.end() ||
                di1.find(x-y)!=di1.end() ||
                di2.find(x+y)!=di2.end() 
            ){
                ans.push_back(1);                
            }
            else{
                ans.push_back(0);
            }        
            
            for(int i=0;i<9;i++){
                auto it = lamp_pos.find(x+dx[i]);
                
                if(it != lamp_pos.end() && it->second == y+dy[i]){
                    lamp_pos.erase(it);
                    lampoff(x+dx[i],y+dy[i]);
                }
            }
        }
        return ans;
    }
};