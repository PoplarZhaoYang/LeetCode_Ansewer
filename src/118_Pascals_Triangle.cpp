class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > ret;
        vector<int> temp;
        if (numRows > 0) temp.push_back(1), ret.push_back(temp);
        for (int i = 1; i < numRows; i++) {
            vector<int> temps;
            for (int j = 0; j < ret[i - 1].size() + 1; j++) {
                if (j == 0 || j == ret[i - 1].size()) temps.push_back(1);
                else temps.push_back(ret[i - 1][j - 1] + ret[i - 1][j]);
            }
            ret.push_back(temps);
        }
        return ret;
    }
};
