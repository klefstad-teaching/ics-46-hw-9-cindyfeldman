#include "ladder.h"
void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << " between " << word1 << " and " <<word2 << endl;
}
bool is_adjacent(const string& word1, const string& word2)
{
    if(word1.length() != word2.length())
        return false;
    int diffCount = 0;
    for(size_t i = 0; i< word1.length(); ++i)
    {
        if(word1[i] != word2[i])
            diffCount++;
        if(diffCount > 1)return false;
    }
    return diffCount == 1; 
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int str1len = str1.length();
    int str2len = str2.length();
    if(abs(str2len-str1len) > d)
        return false;
    int ds[str1len+1][str2len+1];
    for(int i = 0; i <= str1len; ++i)
        ds[i][0] = i;
    for(int j = 0; j <= str2len; ++j)
        ds[0][j] = j;
    
    for(int i = 1; i <= str1len; ++i)
    {
        for(int j = 1; j <= str2len; ++j)
        {
            if(str1[i-1]==str2[j-1])
                ds[i][j] = ds[i-1][j-1];
            else
            {
                ds[i][j] = min(ds[i-1][j], min(ds[i][j-1], ds[i-1][j-1])) + 1;
            }
        }
    }
    return ds[str1len][str2len] <= d;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size()-1];
        for(const string& word : word_list)
        {
            if(edit_distance_within(last_word, word, 1))
            {
                if(visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    vector<string> result_ladder  = ladder;
                    result_ladder.push_back(word);
                    if(word == end_word)
                        return result_ladder;
                    ladder_queue.push(result_ladder);
                }
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name)
{
    ifstream inFile(file_name);
    string line;

    if(!inFile.is_open())cout << "Error: cant open file: " << file_name;
    while(getline(inFile, line))
    {
        word_list.insert(line);
    }
    inFile.close();
}
void print_word_ladder(const vector<string>& ladder)
{
    for(int i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i]  ;
        if(i != ladder.size() -1)
            cout << " -> ";
    }
    cout << endl;
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size()==4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size()==6);
    my_assert(generate_word_ladder("code", "data", word_list).size()==6);
    my_assert(generate_word_ladder("work", "play", word_list).size()==6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size()==8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size()==4);
}