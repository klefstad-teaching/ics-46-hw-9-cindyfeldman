#include "ladder.h"
void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << " between " << word1 << " and " <<word2 << endl;
}
bool is_adjacent(const string& word1, const string& word2)
{
    int diffCount = 0;
    if(word1 == word2)
        return true;
    if(abs((int)(word1.length() - word2.length()))>1)
        return false;
    if(word1.length() == word2.length())
    {
        for(size_t i = 0; i< word1.length(); ++i)
        {
            if(word1[i] != word2[i])
                diffCount++;
            if(diffCount > 1)return false;
        }
        return diffCount == 1; 
    }
    if(word1.length() > word2.length())
        return is_adjacent(word2, word1);
    for(size_t i = 0; i< word2.length(); ++i)
    {
        if(word1[i] != word2[i])
            return word1.substr(i) == word2.substr(i+1);
    }
    return false;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int str1len = str1.length();
    int str2len = str2.length();
    if(abs(str2len-str1len) > d)
        return false;
    vector<vector<int>> dist(str1len+1, vector<int>(str2len+1));
    for(int i = 0; i <= str1len; ++i)
        dist[i][0] = i;
    for(int j = 0; j <= str2len; ++j)
        dist[0][j] = j;
    
    for(int i = 1; i <= str1len; ++i)
    {
        for(int j = 1; j <= str2len; ++j)
        {
            if(str1[i-1]==str2[j-1])
                dist[i][j] = dist[i-1][j-1];
            else
            {
                dist[i][j] = min(dist[i-1][j], min(dist[i][j-1], dist[i-1][j-1])) + 1;
            }
        }
    }
    return dist[str1len][str2len] <= d;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word)
        return {};
    if(word_list.find(end_word) == word_list.end())
        return {};

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
            if(is_adjacent(last_word, word))
            {
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
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
    if(ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    else{
        cout << "Word ladder found: ";
        for(int i = 0; i < ladder.size(); ++i)
            cout << ladder[i] << " ";
        cout << endl;
    }
    
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    if(word_list.empty()){
        cout << "Error: word list empty"<<endl;
        return;
    }
    my_assert(generate_word_ladder("cat", "dog", word_list).size()==4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size()==6);
    my_assert(generate_word_ladder("code", "data", word_list).size()==6);
    my_assert(generate_word_ladder("work", "play", word_list).size()==6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size()==8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size()==4);
}