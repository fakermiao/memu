/*
 * @Author: 苗金标
 * @Date: 2023-01-12 16:07:34
 * @LastEditors: 苗金标
 * @LastEditTime: 2023-01-12 16:18:20
 * @Description: my binary tree template
 */
#include "BinNode.h"
template <typename T>
class myBinTree
{
protected:
    /* data */
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x);
    void updateHeightAbove(BinNodePosi(T) x);
public:
    myBinTree(/* args */):_size(0),_root(NULL){};
    ~myBinTree(){if(0 < _size) remove (_root)};


    int size() const { return _size};
    bool empty() const{return (!_root)};
    BinNodePosi(T) root(){return _root};
    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x,T const& e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x,T const& e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x,myBinTree<T>* &T);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x,myBinTree<T>* &T);
    template <typename VST>
    void travLevel(VST& visit){
        if(_root) _root->travLevel(visit); 
    }
    void travPre(VST& visit){
        if(_root) _root->travPre(visit); 
    }
    void travIn(VST& visit){
        if(_root) _root->travIn(visit); 
    }
    void travPost(VST& visit){
        if(_root) _root->travPost(visit); 
    }
};
template <typename T>
BinNodePosi(T) myBinTree<T>::insertAsRoot(T const& e){
    _size = 1;
    return _root = new BinNode(e);
}

template <typename T>
BinNodePosi(T) myBinTree<T>::insertAsLC(BinNodePosi(T) x,T const& e){
    x->insertAsLc(e);
    _size++;
    updateHeightAbove(x);
    return x->lc;
}

template <typename T>
BinNodePosi(T) myBinTree<T>::insertAsRC(BinNodePosi(T) x,T const& e){
    _size++;
    x->insertAsRc(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>
BinNodePosi(T) myBinTree<T>::attachAsLC(BinNodePosi(T) x,myBinTree<T>* &S){
    _size += S->_size;
    if(x->lc = S->_root){
        x->lc->parent = x;
    }
    updateHeightAbove(x);
    S->_root = NULL;
    S-> _size = 0;
    release(S);
    S = NULL;
    return x;
}

template <typename T>
BinNodePosi(T) myBinTree<T>::attachAsRC(BinNodePosi(T) x,myBinTree<T>* &S){
    _size += S->_size;
    if(x->rc = S->_root){
        x->rc->parent = NULL;
    }
    updateHeightAbove(x);
    S->_size = 0;
    S->_root = NULL;
    release(S);
    S = NULL;
    return x;
}




















