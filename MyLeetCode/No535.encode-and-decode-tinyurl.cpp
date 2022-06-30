#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    Solution(){};
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        ++id;
        db[id] = longUrl;
        return SHORT_URL_HEAD + to_string(id);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int len = shortUrl.size();
        int idIndex = len - 1;
        while (shortUrl[idIndex] != '/') {
            --idIndex;
        }
        ++idIndex;
        int id = stoi(shortUrl.substr(idIndex, len - idIndex));
        return db[id];
    }

private:
    unordered_map<int, string> db;
    int id = 1000;
    const string SHORT_URL_HEAD = "http://tinyurl.com/";
};

int main(void) {
    Solution solution;

    string longUrl1 = "https://leetcode.com/problems/design-tinyurl";
    string shortUrl1 = solution.encode(longUrl1);
    string res1 = solution.decode(shortUrl1);
    cout << "longUrl:\t" << longUrl1 << endl
         << "encode:\t\t" << shortUrl1 << endl
         << "decode:\t\t" << res1 << endl
         << "is equal:\t" << (longUrl1 == res1) << endl;

    return 0;
}
