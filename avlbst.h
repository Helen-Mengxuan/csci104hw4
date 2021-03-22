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
    void remove_fix(AVLNode<Key,Value>* n);
};

template<class Key, class Value>
void AVLTree<Key, Value>::left_rotate(AVLNode<Key,Value>* up, AVLNode<Key,Value>* down)
{

    /* 1. deal with the upper layer*/
    if( up->getParent() != NULL ){

        down->setParent(up->getParent());

        if( up == up->getParent()->getLeft() ){
            /*up is a left child*/
            up->getParent()->setLeft(down);
        }
        else if( up == up->getParent()->getRight() ){
            /*up is a right child*/
            up->getParent()->setRight(down);
        }   
    }
    else{
        /*there is no relevant upper level*/
        down->setParent(NULL);
    }

    /* 2. deal with the lower layer*/
    if( down->getLeft() != NULL ){
        up->setRight(down->getLeft());
        down->getRight()->setParent(up);       
    }
    else{
        /*there is no relevant lower level*/
        up->setRight(NULL);
    }

    /* 3. between rotating nodes*/
    up->setParent(down);
    down->setLeft(up);

    /*4. check NULL for children, then recalculate height*/

    if( up->getLeft() == NULL && up->getRight() == NULL ){
        /*leaf node*/  
        up->setHeight(1);
    }
    else if( up->getLeft() == NULL && up->getRight() != NULL ){
        /*right child exists*/
        up->setHeight(up->getRight()->getHeight()+1);
    }
    else if( up->getLeft() != NULL && up->getRight() == NULL ){
        /*left child exists*/
        up->setHeight(up->getLeft()->getHeight()+1);
    }
    else{
        /*both children exists*/
        int up_now = std::max(up->getLeft()->getHeight(),up->getRight()->getHeight()) + 1;
        up->setHeight(up_now);
    }

    /*left rotation, left child(g) always exist */
    if( down->getRight() == NULL ){
        /*Right NOT exists*/
        down->setHeight(down->getLeft()->getHeight()+1);
    }
    else{
         /*both children exists*/
        int down_now = std::max(down->getLeft()->getHeight(),down->getRight()->getHeight()) + 1;
        down->setHeight(down_now);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::right_rotate(AVLNode<Key,Value>* up, AVLNode<Key,Value>* down)
{

    /* 1. deal with the upper layer*/
    if( up->getParent() != NULL ){

        down->setParent(up->getParent());

        if( up == up->getParent()->getLeft() ){
            /*up is a left child*/
            up->getParent()->setLeft(down);
        }
        else if( up == up->getParent()->getRight() ){
            /*up is a right child*/
            up->getParent()->setRight(down);
        }   
    }
    else{
        /*there is no relevant upper level*/
        down->setParent(NULL);
    }


    /* 2. deal with the lower layer*/
    if( down->getRight() != NULL ){
        up->setLeft(down->getRight());
        down->getRight()->setParent(up);        
    }
    else{
        /*there is no relevant lower level*/
        up->setLeft(NULL);
    }


    /* 3. between rotating nodes*/
    up->setParent(down);
    down->setRight(up);


    /*4. check NULL for children, then recalculate height*/

    if( up->getLeft() == NULL && up->getRight() == NULL ){
        /*leaf node*/  
        up->setHeight(1);
    }
    else if( up->getLeft() == NULL && up->getRight() != NULL ){
        /*right child exists*/
        up->setHeight(up->getRight()->getHeight()+1);
    }
    else if( up->getLeft() != NULL && up->getRight() == NULL ){
        /*left child exists*/
        up->setHeight(up->getLeft()->getHeight()+1);
    }
    else{
        /*both children exists*/
        int up_now = std::max(up->getLeft()->getHeight(),up->getRight()->getHeight()) + 1;
        up->setHeight(up_now);
    }

    /*right rotation, right child(g) always exist */
    if( down->getLeft() == NULL ){
        /*Left NOT exists*/
        down->setHeight(down->getRight()->getHeight()+1);
    }
    else{
        /*both children exists*/
        int down_now = std::max(down->getLeft()->getHeight(),down->getRight()->getHeight()) + 1;
        down->setHeight(down_now);
    }
}

/*this function should call the rotation functions and finish rotation*/
template<class Key, class Value>
void AVLTree<Key, Value>::pre_rotate(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{

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
void AVLTree<Key, Value>::insert_fix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{

    /*base case, root reached*/
    if(p == NULL || p->getParent() == NULL){
        return;
    }

    AVLNode<Key,Value>* g = p->getParent();
    int gh_ori = g->getHeight();

    /*g's new height*/
    int gh_now, g_status;
    /*g is a parent so it must have a child*/
    if( g->getLeft() == NULL){
        /*g has a right child*/
        gh_now = g->getRight()->getHeight() + 1;
        g_status = 1;
    }
    else if(g->getRight() == NULL){
        /*g has a left child*/
        gh_now = g->getLeft()->getHeight() + 1;
        g_status = 0;
    }
    else if( (g->getRight() != NULL) && g->getLeft() != NULL){
        /*g has both children*/
        gh_now = std::max(g->getLeft()->getHeight(),g->getRight()->getHeight()) + 1;
        g_status = 2;
    }

    /*case 1, g's height not changed*/
    if( gh_ori == gh_now ){
        /*g's height not changed, don't worry about upper levels*/
        return;
    }

    /*check balance*/
    bool balance = false;
    if( g_status == 0){
        /*g only has a left child*/
        if( g->getLeft()->getHeight() == 1 ){
            balance = true;
        }        
    }
    else if( g_status == 1 ){
        /*g only has a right child*/
        if( g->getRight()->getHeight() == 1 ){
            balance = true;
        }
    }
    else if( g_status == 2 ){
        if( abs( g->getLeft()->getHeight() - g->getRight()->getHeight() ) <= 1 ){
            balance = true;
        }
    }
   
    /*case 2, g balanced, check upper levels*/
    if( balance == true ){
        g->setHeight(gh_now);
        insert_fix(g, p);
        return;
    }

    /*case 3, g unbalanced, fix, balance */
    if( balance == false ){
        /*determine rotation type, then rotate*/
        pre_rotate(g, p, n);
        return;
    }
}

/*insert and rotate to fix balance*/
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    /*if empty tree*/
    if(this->empty()){
        AVLNode<Key,Value>* NRoot = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
        this->root_ = NRoot;
        return;
    }
    /*if root's key = insert's key, update root's value to insert*/
    if( this->root_->getKey() == new_item.first){
        this->root_->setValue(new_item.second);
        return;
    }

    /*root_ is a Node, but point to an AVLNode*/
    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_); 

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
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key,Value>* n)
{

    /*if the node removed is the root, or root node is reached*/
    if( n == NULL){
        /*now empty tree*/
        return;
    }

    int nh_ori = n->getHeight(); 

    /*n's new height*/
    int nh_now, n_status;
    /*n is a parent so it must have a child*/
    if( n->getLeft() == NULL){
        /*n has a right child*/
        nh_now = n->getRight()->getHeight() + 1;
        n_status = 1;
    }
    else if(n->getRight() == NULL){
        /*n has a left child*/
        nh_now = n->getLeft()->getHeight() + 1;
        n_status = 0;
    }
    else if( (n->getRight() != NULL) && (n->getLeft() != NULL) ){
        /*n has both children*/
        nh_now = std::max(n->getLeft()->getHeight(),n->getRight()->getHeight()) + 1;
        n_status = 2;
    }

    /*check balance*/
    bool balance = false;

    if( n_status == 0){
        /*n only has a left child*/
        if( n->getLeft()->getHeight() == 1 ){
            balance = true;
        }        
    }
    else if( n_status == 1 ){
        /*n only has a right child*/
        if( n->getRight()->getHeight() == 1 ){
            balance = true;
        }
    }
    else if( n_status == 2 ){
        if( abs( n->getLeft()->getHeight() - n->getRight()->getHeight() ) <= 1 ){
            balance = true;
        }
    }

    /*case 1, n is unbalanced*/
    if( balance == false ){

        int c_id = 0;
        AVLNode<Key,Value>* c;

        /*find the taller of n's children*/
        if( n->getLeft()->getHeight() > n->getRight()->getHeight() ){
            /*left child has greater height*/
            c = n->getLeft();
            c_id = 1;
        }
        else{ /*then right child must has greater height*/
            c = n->getRight();
            c_id = 2;
        }

        AVLNode<Key,Value>* g;

        /*find the taller of n's grandchildren/c's chilren*/
        if( c->getLeft()->getHeight() > c->getRight()->getHeight() ){
            /*c's left child has greater height*/
            g = c->getLeft();
        }
        else if( c->getLeft()->getHeight() < c->getRight()->getHeight() ){
            /*c's left child has greater height*/
            g = c->getRight();
        }
        else{ /*need to break tie with zig-zig*/

            if( c_id == 1 ){
                /*c is n's left child, so g needs to be c's left child*/
                g = c->getLeft();
            }
            else if( c_id == 2 ){
                /*c is n's right child, so g needs to be c's right child*/
                g = c->getRight();
            }
            else if( c_id == 0 ){
                std::cerr << "n's child c has id error!" << std::endl; 
            }
        }

        /*now pointers n, c, g prepared.*/
        pre_rotate(n, c, g); //n = 10

        AVLNode<Key,Value>* p;

        /*rotation performed and all relavent heights updated*/
        /*find the highest among g,c,n and recurse to check upper levels*/
        /*n is rotated down, so higher one must be in c or g, without tie*/
        if( c->getHeight() > g->getHeight() ){
            /*after zig-zig, c higher*/
            p = c->getParent();
        }
        else if( c->getHeight() < g->getHeight() ){
            /*after zig-zag, g higher*/
            p = g->getParent();
        }

        remove_fix(p); //20
    }
    /*case 2, n's height unchanged, tree still balanced, done!*/
    else if( nh_ori == nh_now ){
        /*n's height not changed, don't worry about upper levels*/
        return;
    }
    /*case 3, n changed but still balanced*/
    else if( (nh_ori != nh_now) && (balance == true) ){
        /*update height of n*/
        n->setHeight(nh_now);
        /*keep moving up to find unbalanced node*/
        /*if all nodes above are balanced, base(root)case will trigger and return*/
        AVLNode<Key,Value>* p = n->getParent();
        remove_fix(p);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    /*find the node with key*/
    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));

    /*BST delete*/

    /*if cannot find the node or empty tree, do nothing*/
    if(temp == NULL){
        return;
    }
    
    /*now temp is a pointer to the AVLNode to be removed*/

    /* temp->getKey() == key */
    if( temp->getKey() != key ){
        std::cerr << "incorrect node but should be correct!" << std::endl;
    }

    /*if leaf node*/
    if( (temp->getRight() == NULL) && (temp->getLeft() == NULL) ){

        /*root is the only node*/
        if(temp->getParent() == NULL){
            this->root_ = NULL;
        }
        /*Left child*/
        else if(temp->getKey() < temp->getParent()->getKey()){
            temp->getParent()->setLeft(NULL);
        }
        /*Right child*/
        else if(temp->getKey() > temp->getParent()->getKey()){
            temp->getParent()->setRight(NULL);;
        }
    }
    /*if 1 child*/
    else if( (temp->getRight() == NULL) || (temp->getLeft() == NULL) ){

        /*the child is left child*/
        if( temp->getLeft() != NULL ){

        /*promote the child*/
            temp->getLeft()->setParent(temp->getParent());

            if(temp->getParent() == NULL){
                this->root_ = temp->getLeft();               
            }
            else if(temp->getKey() < temp->getParent()->getKey()){
                /*temp is a left child*/
                temp->getParent()->setLeft(temp->getLeft());
            }
            else if( temp->getKey() > temp->getParent()->getKey() ){
                /*temp is a right child*/
                temp->getParent()->setRight(temp->getLeft());
            }
        }
        /*the child is right child*/
        else if( temp->getRight() != NULL){

            temp->getRight()->setParent(temp->getParent());

            /*removing node*/
            if(temp->getParent() == NULL){
                this->root_ = temp->getRight();           
            }
            else if(temp->getKey() < temp->getParent()->getKey()){
                /*temp is a left child*/
                temp->getParent()->setLeft(temp->getRight());
            }
            else if( temp->getKey() > temp->getParent()->getKey()){
                /*temp is a right child*/
                temp->getParent()->setRight(temp->getRight());
            }
        }
    }
    /*if 2 children*/
    else if( (temp->getRight() != NULL) && (temp->getLeft() != NULL) ){

        AVLNode<Key,Value>* pre = static_cast< AVLNode<Key,Value>* >(this->predecessor(temp));

        /*predecessor is either temp's left child or always a right child of a parent*/

        this->nodeSwap(pre, temp); /*now pre is temp, both are AVLnodes*/
        //temp = 20, pre = 12

        /*always true: temp->getRight() == NULL */
        /*if predcessor is a leaf node, temp is a leaf node after swap*/
        if( (temp->getLeft() == NULL) && (temp->getRight() == NULL) ){

            if(pre->getKey() == temp->getParent()->getKey()){
                /*now pre is the parent, temp is left child*/
                temp->getParent()->setLeft(NULL);
            }
            else{
                /*pre is upper than parent, temp is right child*/
                temp->getParent()->setRight(NULL);
            }

        }    
        /*else predecessor has a child, its child must be a left child
        a right child would have been the predecessor*/
        else if( (temp->getLeft() != NULL) ){

            /*update this left child's parent pointer*/
            temp->getLeft()->setParent(temp->getParent());

            if(pre->getKey() == temp->getParent()->getKey()){
                /*pre is the parent, temp is left child*/
                temp->getParent()->setLeft(temp->getLeft());
            }    
            else{
                /*pre is upper than parent, temp is right child*/
                temp->getParent()->setRight(temp->getLeft());
            }           
        }

    }

    /*all pointers updated, preparing to delete temp*/    
    AVLNode<Key,Value>* p = temp->getParent();
    delete temp;
    remove_fix(p);
}


#endif
