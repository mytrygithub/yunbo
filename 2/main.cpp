#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "gtest/gtest.h"  

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;
using std::cin;

// head = [-2,5,-1,-10,1,-1,10,2,2,2,5,5] //示例链表 /**
 //Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//不处理 dest_sum 为 0 的情况
class Solution
{
public:
    Solution(int dest = 10):dest_sum(dest) {}

    //注意是否处理了 head == nullptr
    ListNode* removeSublists(ListNode* head) {
        ListNode tmp_head;
        tmp_head.next = head;
        ListNode* pre = &tmp_head;

        bool exist = true;
        vector<ListNode*> pres;
        vector<long> sums;

        // 为什么不能使用 =dest_sum 待分析
        auto update=[this, &tmp_head](vector<long> &sums, vector<ListNode*> &pres, ListNode* &pre) {
            pres.push_back(pre);
            pre = pre->next;
            auto n = pre->val;
            sums.push_back(n);
            //cout << "sums push:" << n << endl;
            bool ans = false;

            if (abs(n) > abs(dest_sum) || n == 0) {
                pres.clear();
                sums.clear();
                return ans;
            }

            auto const limit = sums.size();
            for (int i = 0; i < limit; i++) {
                if (i < limit-1) sums[i] *= n;

                if (sums[i] == 10) {
                    // to delete
                    auto cur = pres[i]->next;
                    auto save_head = pres[i];
                    auto cur_end = pre->next;
                    while(cur != cur_end) {
                        auto to_delete = cur;
                        cur = cur->next;
                        delete to_delete;
                    }

                    pres.clear();
                    sums.clear();

                    pre = save_head;
                    pre->next = cur_end;

                    return true;
                }
            }
            
            return ans;
        };

        while(exist) {
            exist = false;
            pre = &tmp_head;
            sums.clear();
            pres.clear();
            while(pre->next) {
                exist = exist | update(sums, pres, pre);
            }
        }

        return tmp_head.next;
    }

    ListNode* vectorToList(vector<int> &vec) {
        ListNode tmp_head;
        ListNode* cur = &tmp_head;
        for (auto const n:vec) {
            cur->next = new ListNode(n);
            cur = cur->next;
        }

        return tmp_head.next;
    }

    void listToVector(ListNode* head, vector<int>& vec) {
        auto cur = head;
        while(cur) {
            vec.push_back(cur->val);
            cur = cur->next;
        }
    }

    void printList(string const prefix, ListNode* head) {
        auto cur = head;
        cout << prefix;
        while(cur) {
            cout << " " << cur->val;
            cur = cur->next;
        }
        cout << endl;
    }

private:
    int dest_sum;
};

TEST(demo_test, check_print_func) {
    // check to list and to vec
    vector<int> tmp_vec{-2,5,-1,-10,1,-1,10,2,2,2,5,5};
    vector<int> tmp_vec_result;
    Solution tmps;
    auto tmp_list = tmps.vectorToList(tmp_vec);
    tmps.listToVector(tmp_list, tmp_vec_result);
    EXPECT_EQ(tmp_vec, tmp_vec_result);
}

// 可以定义多个测试用例  
TEST(demo_test, test1) {
    Solution s;
    vector<int> input{-2,5,-1,-10,1,-1,10,2,2,2,5,5};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{2};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, empty) {
    Solution s;
    vector<int> input{};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, have_item_greater_than_10) {
    Solution s;
    vector<int> input{-2,30,-1,-4,1,-6,10,2,100,2,5,5};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{-2,30,-1,-4,1,-6,2,100,5};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, result_empty) {
    Solution s;
    vector<int> input{-2,5,-1,-1,-1,10};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, have_0) {
    Solution s;
    vector<int> input{-2,5,-1,0,-1,10};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{0,-1};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, after_10_have_1) {
    Solution s;
    vector<int> input{-2,5,-1,0,-1,10,1};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{0,-1,1};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, after_0_is_10) {
    Solution s;
    vector<int> input{-2,5,-1,0,10,1};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{0,1};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, after_0_is_10_2) {
    Solution s;
    vector<int> input{0,10,1};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{0,1};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, after_0_is_10_3) {
    Solution s;
    vector<int> input{-1,0,10,1};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{-1,0,1};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

TEST(demo_test, after_11_is_10_1) {
    Solution s;
    vector<int> input{-1,11,10,1};
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> dest_out{-1,11,1};
    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

/*
-1 11 10 1
-1 11 1


./test --gtest_filter=-demo_test.get_*
*/
TEST(demo_test, get_input_from_stdinput) {
    Solution s;
    vector<int> input;
    vector<int> dest_out;

    string line;
    getline(cin, line);
    istringstream issinput(line);
    int n;
    while (issinput >> n) {
        input.push_back(n);
    }
    getline(cin, line);
    istringstream issoutput(line);
    while(issoutput >> n) {
        dest_out.push_back(n);
    }
    auto input_list = s.vectorToList(input);
    auto dest_list = s.removeSublists(input_list);

    vector<int> result;
    s.listToVector(dest_list, result);
    EXPECT_EQ(dest_out, result);
}

int main(int argc, char **argv) {  
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();

    return 0;
}