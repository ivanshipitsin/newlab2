#ifndef BTREE_HPP
#define BTREE_HPP

template<typename Tv,typename Tk>
struct Node {
    unsigned int lf:1; // leaf check
    unsigned int ct:15; // count keys
    unsigned int cd; // count data if leaf
    struct Node<Tv, Tk> * parent;
    struct Node<Tv, TK> ** childs;
    struct Node<Tv, Tk> * prev; // if leaf
    struct Node<Tv, Tk> * next; // if leaf
    Tv ** data; // if leaf
    unsigned int * counts; // if leaf
    Tk * keys;
};

template<typename Tv,typename Tk>
class Btree{
private:
    Node<Tv,Tk> * root;
    unsigned int m; // maybe odd
public:
    Btree(unsigned int _m) : m(_m){
        root = new Node<Tv, Tk>;
        root->lf = 1;
        root->ct = 0;
        root->parent = nullptr;
        root->childs = nullptr;
        root->prev = nullptr;
        root->next = nullptr;
        root->data = nullptr;
        root->keys = nullptr;
    }
    void append(Tk key,Tv * data, unsigned int count){
        appendRec(key, data, count , root);
    }
protected:
    void appendRec(Tk key, Tv * data, unsigned int count, Node<Tv, Tk> * curr){
        if(curr->keys == nullptr){
            curr->keys = new Tk[ m ];
            curr->data = new Tv*[ m ];
            curr->keys[0] = key;
            curr->data[0] = data;
            curr->counts = new unsigned int[ m ];
            curr->counts[0] = count;
            curr->ct = 1;
            return;
        } else {
            int i = 0;
            while(i < ct && key > curr->keys[i]){ // maybe can make binary found?
                i++;
            }
            if(curr->lf){
                for(int p = ct; p > i; p--){
                    curr->keys[p] = curr->keys[p - 1];
                    curr->data[p] = curr->data[p - 1];
                }
                curr->keys[i] = key;
                curr->data[i] = 
                if(ct == m){
                    split(curr);
                }
            }else{
                appendRec(key, data, count, curr->childs[i]);
            }

        }
    }

    void split(Node<Tv, Tk> * curr){

    }
};
#endif