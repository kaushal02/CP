/*
https://www.interviewbit.com/problems/pretty-json/

O(Linear)
*/
vector<string> Solution::prettyJSON(string A) {
    int i = 0, N = A.size();
    vector<string> B;
    string Indent = "";
    while (i < N) {
        if (iswspace(A[i])) i++;
        else if (A[i] == '[' or A[i] == '{') {
            B.push_back(Indent + A[i++]);
            Indent += '\t';
        }
        else if (A[i] == ']' or A[i] == '}') {
            Indent.pop_back();
            B.push_back(Indent + A[i++]);
        }
        else {
            string t = "";
            while (A[i] != ',' and A[i] != '[' and A[i] != '{' and A[i] != ']' and A[i] != '}') {
                t += A[i++];
            }
            if (A[i] == ',') {
                t += A[i++];
            }
            if (t == ",") B.back() += t;
            else B.push_back(Indent + t);
        }
    }
    return B;
}
