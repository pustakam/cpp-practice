#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* prev;
   Node* next;
   int key;
   int value;

   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

ostream& operator<<(ostream& os, Node* node)
{
    os << "{";
    if (node == nullptr) {
        os << "null";
    } else {
        os << "prev=";
        if (node->prev == nullptr)
            os << "null";
        else
            os << reinterpret_cast<int*>(node->prev);
        os << ", key=" << node->key; 
        os << ", address=" << reinterpret_cast<int*>(node); 
        os << ", next=";
        if (node->next == nullptr)
            os << "null";
        else
            os << reinterpret_cast<int*>(node->next);
    }
    os << "} ";
    return os;
}

class LRUCache : public Cache {
public:
    LRUCache(int capacity)
    {
        assert(capacity >= 1 && capacity <= 1000);
        mp = {};
        cp = capacity;
        tail = nullptr;
        head = nullptr;
    }
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = delete;
    LRUCache& operator=(LRUCache&&) = delete;
    virtual ~LRUCache() {
        while (head != nullptr) {
            auto n = head;
            head = head->next;
            delete n;
        }
    }

    void set(int k, int v) override
    {
        assert(k >= 1 && k <= 20);
        assert(v >= 1 && v <= 2000);
    
        if (mp.size() < cp) {
            if (head == nullptr) {
                Node* new_node = new Node{nullptr, nullptr, k, v};
                tail = head = new_node;
                mp[new_node->key] = new_node;
            } else {
                Node* new_node = new Node{nullptr, head, k, v};
                head->prev = new_node;
                head = new_node;
                mp[new_node->key] = new_node;
            }
        } else {
            assert(tail != nullptr && head != nullptr);
            if (head == tail) {
                Node* new_node = new Node{nullptr, nullptr, k, v};
                mp.erase(tail->key);
                delete tail;
                head = tail = new_node;
                mp[new_node->key] = new_node;
            } else {
                auto new_tail = tail->prev;
                new_tail->next = nullptr;

                mp.erase(tail->key);
                delete tail;
                tail = new_tail;

                Node* new_node = new Node{nullptr, head, k, v};
                head->prev = new_node;
                head = new_node;
                mp[new_node->key] = new_node;
            }
        }
    }

    int get(int k) override
    {
        if (mp.find(k) == mp.end())
            return -1;
        
        auto found_node = mp[k];
        if (head == found_node) {
            //Nothing to do
        } else if (tail == found_node) {
            tail->prev->next = nullptr;
            tail = tail->prev;

            found_node->next = head;
            found_node->prev = nullptr;

            head->prev = found_node;
            head = found_node;
        } else {
            found_node->prev->next = found_node->next;
            found_node->next->prev = found_node->prev;

            found_node->next = head;
            found_node->prev = nullptr;

            head->prev = found_node;
            head = found_node;
        }

        return found_node->value;
    }

    void print(){
        Node* p = head;
        while(p != nullptr) {
            cout << p;
            p = p->next;
        }
        cout << endl;
    }
};

int testme() {
    LRUCache cache(4);

    cache.set(4, 2);
    cache.print();

    cache.set(2, 7);
    cache.print();

    cout << "get 2: " << cache.get(2) << endl;
    cache.print();

    cache.set(1, 8);
    cache.print();

    cache.set(5, 9);
    cache.print();

    cache.set(6, 15);
    cache.print();

    cout << "get 4: " << cache.get(4) << endl;
    cache.print();

    cout << "get 5: " << cache.get(5) << endl;
    cache.print();

/*
8 4
set 4 2
set 2 7
get 2
set 1 8
set 5 9
set 6 15
get 4
get 5
*/

    /*
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
   */
}


