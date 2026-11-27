// orz
// 146. LRU Cache · LeetCode · Medium
//
// Question:
// design a data structure that follows the Least Recently Used (LRU) cache rules.
// LRUCache(int capacity) makes the cache with a positive size capacity.
// int get(int key) returns the value of key if it is in the cache, otherwise -1.
// void put(int key, int value) updates the value of key if it is there, otherwise
// adds the pair. if that makes the number of keys exceed capacity, evict the least
// recently used key. get and put must each run in O(1) average time.
// (both get and put of a key count as using it.)
// Example 1:
//   ["LRUCache","put","put","get","put","get","put","get","get","get"]
//   [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
//   -> [null,null,null,1,null,-1,null,-1,3,4]
//   (put 3 evicts key 2, put 4 evicts key 1)
// Constraints: 1 <= capacity <= 3000, 0 <= key <= 10^4, 0 <= value <= 10^5,
//              at most 2 * 10^5 calls to get and put
//
// 1. Mathematical statement
//    keep a set of at most capacity pairs (key, value), each with the time it was last used.
//    get / put of a key sets its time to now. when a new key would make the size
//    capacity + 1, remove the pair with the smallest time first.
//
// 2. Brute force
//    a vector of (key, value, time). get / put scan it to find the key, eviction scans it
//    for the smallest time. O(capacity) per call, 2 * 10^5 * 3000 = 6 * 10^8. too slow.
//
// 3. What the brute force wastes
//    two scans: one to find a key, one to find the oldest pair. the exact times are never
//    needed, only the ORDER of use, and every use moves one key to the "newest" end.
//
// 4. Key breaking point
//    keep the pairs in a list ordered by use: newest at the front, oldest at the back.
//    a use = cut the node out and put it at the front. eviction = remove the back node.
//    a doubly linked list does all of that in O(1) once we hold a pointer to the node,
//    and an unordered_map key -> node gives that pointer in O(1).
//    dummy head and dummy tail mean every real node always has a prev and a next,
//    so cutting and inserting never check for NULL.
//
// 5. Method
//    step 1 : head <-> .. <-> tail, two dummy nodes. head->next is the newest pair,
//             tail->prev the oldest. pos[key] = the node holding key.
//    step 2 : unlink(node): node->prev->next = node->next, node->next->prev = node->prev.
//    step 3 : pushfront(head, node): put node between head and head->next.
//    step 4 : get(key): key not in pos -> -1. else unlink + pushfront (it is now the newest),
//             return its value.
//    step 5 : put(key, value), key already in pos: change the value, unlink + pushfront.
//    step 6 : put(key, value), new key: if the cache is full, the oldest node is tail->prev:
//             unlink it, erase its key from pos, delete it. then make the new node,
//             pushfront it, pos[key] = node.
//
// 6. Why it works
//    every use moves its node to the front, so the list is always sorted by last use and
//    tail->prev is the least recently used key. pos always holds exactly the keys in the list.
//    every call does one map lookup and a constant number of pointer changes.
//    time O(1) average per call, space O(capacity).
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
#define fr first
#define sc second
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define mp make_pair
#define PI acos(-1)
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define pll pair<ll,ll>
using namespace std;
struct CacheNode
{
    ll key ;
    ll val ;
    CacheNode* prev ;
    CacheNode* next ;
    CacheNode(ll k , ll v)
    {
        key = k ;
        val = v ;
        prev = NULL ;
        next = NULL ;
    }
};
void unlink(CacheNode* node)
{
    // this cuts node out of the list, its neighbours now point to each other
    node->prev->next = node->next ;
    node->next->prev = node->prev ;
}
void pushfront(CacheNode* head , CacheNode* node)
{
    // this puts node right after the dummy head, so it becomes the newest
    node->prev = head ;
    node->next = head->next ;
    head->next->prev = node ;
    head->next = node ;
}
class LRUCache {
public:
    ll cap ;                                  // this stores the capacity
    CacheNode* head ;                         // this stores the dummy in front of the newest
    CacheNode* tail ;                         // this stores the dummy behind the oldest
    unordered_map < ll , CacheNode* > pos ;   // this stores key -> the node holding it

    LRUCache(int capacity) {
        // step 1 : empty list, head <-> tail
        cap = capacity ;
        head = new CacheNode(-1 , -1) ;
        tail = new CacheNode(-1 , -1) ;
        head->next = tail ;
        tail->prev = head ;
        pos.clear() ;
    }

    int get(int key) {
        // step 4 : missing -> -1, else it becomes the newest
        if(pos.find(key) == pos.end())
        {
            return -1 ;
        }
        CacheNode* node = pos[key] ;
        unlink(node) ;
        pushfront(head , node) ;
        return (int)node->val ;
    }

    void put(int key, int value) {
        // step 5 : key already there, new value, it becomes the newest
        if(pos.find(key) != pos.end())
        {
            CacheNode* node = pos[key] ;
            node->val = value ;
            unlink(node) ;
            pushfront(head , node) ;
            return ;
        }
        // step 6 : new key, evict the oldest first if the cache is full
        if((ll)pos.size() == cap)
        {
            CacheNode* oldest = tail->prev ;
            unlink(oldest) ;
            pos.erase(oldest->key) ;
            delete oldest ;
        }
        CacheNode* node = new CacheNode(key , value) ;
        pushfront(head , node) ;
        pos[key] = node ;
    }
};
