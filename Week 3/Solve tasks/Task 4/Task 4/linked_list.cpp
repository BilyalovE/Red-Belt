#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

    ~LinkedList(){
        while(head != nullptr){
            PopFront();
        }
    }

    void PushFront(const T& value){
        Node* ptr_node = new Node;
        ptr_node->next = head;
        head = ptr_node;
        ptr_node->value = value;
    }
    
    void InsertAfter(Node* node, const T& value){
        if(node == nullptr){
            PushFront(value);
        }
        else{
            Node* ptr_node = new Node;
            ptr_node->value = value;
            const auto temp = node->next;
            node->next = ptr_node;
            ptr_node->next = temp;
        }
    }
    
    void RemoveAfter(Node* node){
        if(node == nullptr){
            PopFront();
        }
        else if (node->next == nullptr){
            return;
        }
        else{
            auto del_node = node->next;
            auto after_del_node = del_node->next;
            node->next = after_del_node;
            delete del_node;
        }
    }
    
    void PopFront(){
        if(head == nullptr){
            return;
        }
        else{
            auto next_head = head->next;
            delete head;
            head = next_head;
        }
    }

    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
    LinkedList<int> list;

    list.PushFront(1);
    ASSERT_EQUAL(list.GetHead()->value, 1);
    list.PushFront(2);
    ASSERT_EQUAL(list.GetHead()->value, 2);
    list.PushFront(3);
    ASSERT_EQUAL(list.GetHead()->value, 3);

    const vector<int> expected = {3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
    LinkedList<string> list;

    list.PushFront("a");
    auto head = list.GetHead();
    //ASSERT(head);
    ASSERT_EQUAL(head->value, "a");
    
//    list.InsertAfter(nullptr, "b");
//    const vector<string> expected1 = {"b", "a"};
//    ASSERT_EQUAL(ToVector(list), expected1);

    list.InsertAfter(head, "b");
    const vector<string> expected2 = {"a", "b"};
    ASSERT_EQUAL(ToVector(list), expected2);

    list.InsertAfter(head, "c");
    const vector<string> expected3 = {"a", "c", "b"};
    ASSERT_EQUAL(ToVector(list), expected3);
}

void TestRemoveAfter() {
    
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }

    const vector<int> expected = {5, 4, 3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);
    
//    list.RemoveAfter(nullptr); // удаляем после nullptr
//    const vector<int> expected1 = {4, 3, 2, 1};
//    ASSERT_EQUAL(ToVector(list), expected1);
    
    auto next_to_head = list.GetHead()->next;
    list.RemoveAfter(next_to_head); // удаляем 3
    list.RemoveAfter(next_to_head); // удаляем 2

    const vector<int> expected2 = {5, 4, 1};
    ASSERT_EQUAL(ToVector(list), expected2);
//    list.RemoveAfter(next_to_head); // удаляем 1
//    const vector<int> expected3 = {5, 4};
//    ASSERT_EQUAL(ToVector(list), expected3);
//    list.RemoveAfter(next_to_head); // node->next == nullptr
 

    while (list.GetHead()->next) {
        list.RemoveAfter(list.GetHead());
    }
    ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }
    for (int i = 1; i <= 5; ++i) {
        list.PopFront();
    }
    ASSERT(list.GetHead() == nullptr);
    
    LinkedList<int> list2;
    list2.PopFront();
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestPushFront);
    RUN_TEST(tr, TestInsertAfter);
    RUN_TEST(tr, TestPopFront);
    RUN_TEST(tr, TestRemoveAfter);
  return 0;
}
