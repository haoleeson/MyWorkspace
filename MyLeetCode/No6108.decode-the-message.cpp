#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    const char SPACE_CH = ' ';
    string decodeMessage(string key, string message) {
        int lenK = key.length(), lenM = message.length();

        // 得到映射表
        char key2msg[26] = {0};
        int iterator = 0;

        for (int i = 0; i < lenK; ++i) {
            if (key[i] == SPACE_CH || iterator == 26) {
                continue;
            }

            // 未出现过
            if (key2msg[key[i] - 'a'] == 0) {
                key2msg[key[i] - 'a'] = 'a' + iterator;
                ++iterator;
            }
        }

        // 调试
        //        for (int i = 0; i < 26; ++i) {
        //            if (i < 10) {
        //                cout << " ";
        //            }
        //            cout << "  " << i + 1;
        //        }
        //        cout << endl;
        //        char ch = 'a';
        //        for (int i = 0; i < 26; ++i) {
        //            cout << "   " << (char)(ch + i);
        //        }
        //        cout << endl;
        //        for (int i = 0; i < 26; ++i) {
        //            if (key2msg[i] == 0) {
        //                cout << "    ";
        //            } else {
        //                cout << "   " << key2msg[i];
        //            }
        //        }
        //        cout << endl;

        // 编码
        string res = message;
        for (int i = 0; i < lenM; ++i) {
            if (message[i] == SPACE_CH) {
                continue;
            }

            res[i] = key2msg[message[i] - 'a'];
        }

        return res;
    }
};

int main(void) {
    Solution solution0;
    string key0 = "happy boy";
    string message0 = "happy boy";
    string res0 = solution0.decodeMessage(key0, message0);
    cout << res0 << endl;

    Solution solution1;
    string key1 = "the quick brown fox jumps over the lazy dog";
    string message1 = "vkbs bs t suepuv";
    string res1 = solution1.decodeMessage(key1, message1);
    cout << res1 << endl;

    Solution solution2;
    string key2 = "eljuxhpwnyrdgtqkviszcfmabo";
    string message2 = "zwx hnfx lqantp mnoeius ycgk vcnjrdb";
    string res2 = solution2.decodeMessage(key2, message2);
    cout << res2 << endl;

    return 0;
}
