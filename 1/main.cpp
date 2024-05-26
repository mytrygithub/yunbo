#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <sstream>
#include <filesystem>
#include "gtest/gtest.h"  
  
using std::vector;
using std::lower_bound;
using std::string;
using std::unordered_map;
using std::map;
using std::set;
using std::cout;
using std::endl;
using std::cin;
using std::priority_queue;
using std::min;
using std::max;
using std::accumulate;
using std::unordered_set;
using std::pair;
using std::transform;
using std::getline;
using std::istringstream;

using namespace std::filesystem;


#include <iostream>
#include <vector>
#include <deque>
using namespace std;

//通用代码
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

// Input: 目录名称
// Output:文件列表清单

//未处理目录下有目录的情况，如果有需要如何排列等各种问题，暂时忽略这种情况
class Findupdate {
public:
    Findupdate(const string destPath, 
               const string destSuffix = ".stp"
              ):dirPath(destPath),
                suffix(destSuffix) {
        
    }

    bool checkFile(const string &fileName) {
        auto pos = fileName.end() - fileName.begin() - suffix.size();
        if (pos < 0) return false;
        return fileName.substr(pos, suffix.size()) == suffix;
    }

    void changeFileName(vector<string>& newNames) {
        path p(dirPath);
        directory_entry dir(p);
        if (!dir.exists()) {
            cout << endl << "dest path(" << dirPath << ") not exist!" << endl << endl;
            return;
        }

        directory_entry entry(p);
        if (entry.status().type() != file_type::directory) {
            cout << endl << "dirPath is not a path; path is "<< int(file_type::directory) << ", it is:" << (int)entry.status().type() << endl << endl;
            return;
            // 注意非目录能否执行到这，是否在上边检测中就返回了 dir_is_a_file 会执行到这里
        }
        directory_iterator list(p);
        auto n = 1;
        auto cur_path = p.filename(); 
        //cout << "cur path:" << p.filename() << endl;
        for (auto & it:list) {
            if (it.status().type() != file_type::regular) {
                continue;
            }
            string f = it.path().filename();
            if (checkFile(f)) {
                auto new_file = f.substr(f.begin()-f.begin(), f.end()-f.begin()-suffix.size()).append(int_to_string(n)).append(suffix);
                newNames.push_back(new_file);
                n++;

                //cout << f << " new name:" << new_file << endl;
                rename(cur_path/f, cur_path/new_file);
            }
        }
    }

private:
    string int_to_string(int n, int length = 2) {
        auto ans = to_string(n);
        if (ans.length() < length) {
            ans = string(length - ans.length(), '0') + ans;
        }
        return ans;
    } 

private:
    string dirPath;
    string suffix;
};

TEST(demo_test, only_file_in_path) {
    Findupdate F("./only_file_in_path");
    vector<string> dest_result{ "filenamea01.stp", "filenameb02.stp"};
    vector<string> result;
    F.changeFileName(result);
    EXPECT_EQ(dest_result, result);
}

TEST(demo_test, empty) {
    Findupdate F("./empty");
    vector<string> empty_path;
    vector<string> result;
    F.changeFileName(result);
    EXPECT_EQ(empty_path, result);
}

TEST(demo_test, not_exist_suffix) {
    Findupdate F("./not_exist_suffix");
    vector<string> not_exist_suffix;
    vector<string> result;
    F.changeFileName(result);
    EXPECT_EQ(not_exist_suffix, result);
}

TEST(demo_test, not_exist_dir) {
    Findupdate F("./not_exist_dir");
    vector<string> not_exist_suffix;
    vector<string> result;
    F.changeFileName(result);
    EXPECT_EQ(not_exist_suffix, result);
}

TEST(demo_test, dir_is_a_file) {
    Findupdate F("./dir_is_a_file");
    vector<string> not_exist_suffix;
    vector<string> result;
    F.changeFileName(result);
    EXPECT_EQ(not_exist_suffix, result);
}

TEST(demo_test, not_permissions) {
    Findupdate F("./not_permissions");
    vector<string> not_exist_suffix;
    vector<string> result;
    try {
        F.changeFileName(result);
    } catch(std::exception &e) {
        cout << endl << "catch exception:" << e.what() << endl << endl;
    }
    EXPECT_EQ(not_exist_suffix, result);
}

TEST(demo_test, have_dir_in_path) {
    Findupdate F("./have_dir_in_path");
    vector<string> dest_result{ "filenamea01.stp", "filenameb02.stp"};
    vector<string> result;
    F.changeFileName(result);
    EXPECT_EQ(dest_result, result);
}




int main(int argc, char **argv) {  
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();

}