#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insert_fix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void pre_rotate(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void left_rotate(AVLNode<Key,Value>* up, AVLNode<Key,Value>* down);
    void right_rotate(AVLNode<Key,Value>* up, AVLNode<Key,Value>* down);

};


template<class Key, class Value>
void left_rotate(AVLNode<Key,Value>* up, AVLNode<Key,Value>* down){

    /*deal with the upper layer*/
    down->setParent(up->getParent());

    if( up == up->getParent()->getLeft() ){
        /*up is a left child*/
        up->getParent()->setLeft(p);
    }
    else if( up == up->getParent()->getRight() ){
        /*up is a right child*/
        up->getParent()->setRight(p);
    }

    /*deal with the lower layer*/
    up->setLeft(p->getRight());

    

    

}



/*this function should call the rotation functions and finish rotation*/
template<class Key, class Value>
void AVLTree<Key, Value>::pre_rotate(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){

    if( (g->getLeft() == p) && (p->getLeft() == n)){
        /*left zig-zig needs right rotation*/
        right_rotate(g, p);
        return;
    }
    if( (g->getRight() == p) && (p->getRight() == n)){
        /*right zig-zig needs left rotation*/
        left_rotate(g, p);
        return;
    }
    if( (g->getLeft() == p) && (p->getRight() == n)){
        /*p_left zig-zag needs left then right rotation*/
        left_rotate(p, n);
        right_rotate(g, n);
        return;
    }
    if( (g->getRight() == p) && (p->getLeft() == n)){
        /*p_right zig-zag needs right then left rotation*/
        right_rotate(p, n);
        left_rotate(g, n);
        return;
    }   
}

/*this function should make an unbalanced tree balanced again*/
template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){

    /*base case, root reached*/
    if(p == NULL || p->getParent() == NULL){
        return;
    }

    AVLNode<Key,Value>* g = p->getParent();
    int gh_ori = g->getHeight();
    int gh_now = std::max(g->getLeft()->getHeight(),g->getRight()->getHeight()) + 1;

    /*case 1, g's height no change*/
    if( gh_ori == gh_now ){
        /*g's height not changed, don't worry about upper levels*/
        return;
    }
    /*case 2, g balanced, check upper levels*/
    if( abs( g->getLeft()->getHeight() - g->getRight()->getHeight() ) <= 1 ){
        g->setHeight(gh_now);
        insert_fix(g, p);
        return;
    }
    /*case 3, g unbalanced, fix, balance */
    if( abs( g->getLeft()->getHeight() - g->getRight()->getHeight() ) > 1 ){
        /*determine rotation type, then rotate*/
        pre_rotate(g, p, n);
        return;
    }
}9

/*insert and rotate to fix balance*/
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    /*if empty tree*/
    if(this->empty()){
        AVLNode<Key,Value>* NRoot = new AVLNode<Key,Value>(new_item.first, new_item.second, temp);
        this->root_ = NRoot;
        return;
    }
    /*if root's key = insert's key, update root's value to insert*/
    if( this->root_->getKey() == new_item.first){
        this->root_->setValue(new_item.second);
        return;
    }

    /*root_ is a Node, but point to an AVLNode*/
    AVLNode<Key,Value>* temp = static_cast<AVLNode<K,V>*>(this->root_); 

    while(true){
        if( new_item.first < temp->getKey() ){ 
            if(temp->getLeft() == NULL){
                /*target node reached, insert new left node*/
                AVLNode<Key,Value>* node_l = new AVLNode<Key,Value>(new_item.first, new_item.second, temp);
                temp->setLeft(node_l);
                /*insert finished, temp is the parent of the new node*/

                /*check parent*/
                if(temp->getHeight() == 2){
                    /*this parent already has antoher node. still balanced, no change*/
                    return;
                }
                else if(temp->getHeight() == 1){
                    temp->setHeight(2);
                    /*fix balance*/
                    insert_fix(temp, node_l);
                    return;
                }
            }   
            temp = temp->getLeft();
            continue; 
        }
        else if(new_item.first > temp->getKey()){ 
            if(temp->getRight() == NULL){
                /*target node reached, insert new left node*/
                AVLNode<Key,Value>* node_r = new AVLNode<Key,Value>(new_item.first, new_item.second, temp);
                temp->setRight(node_r);
                /*insert finished, temp is the parent of the new node*/

                /*check parent*/
                if(temp->getHeight() == 2){
                    /*this parent already has antoher node. still balanced, no change*/
                    return;
                }
                else if(temp->getHeight() == 1){
                    temp->setHeight(2);
                    /*fix balance*/
                    insert_fix(temp, node_r);
                    return;
                }
                return;
             }
             temp = temp->getRight();
             continue;
        }
        else{
            /*new_item.first == temp->getKey() */
            temp->setValue(new_item.second);
            break;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
