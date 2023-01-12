/*
 * @Author: 苗金标
 * @Date: 2023-01-11 14:35:48
 * @LastEditors: 苗金标
 * @LastEditTime: 2023-01-12 16:17:01
 * @Description: 二叉树模板类
 * 保护变量：规模_size，根节点_root，
 * 保护类型方法：updateHeight更新节点高度，updateHeightAbove更新
 * 共有类型方法：size()获取树的规模，empty()判断二叉树是否为空（bool），获取根节点root()，
 *              insertAsRoot(e)插入根节点
 * ....................
 */

#include "BinNode.h"
template <typename T> class BinTree
{
protected:
    int _size; //规模
    BinNodePosi(T) _root; //根节点
    virtual int updataHeight(BinNodePosi(T) x); //更新节点x的高度
    void updataHeightAbove(BinNodePosi(T) x);

public:
    BinTree(/* args */):_size(0),_root(NULL){};
    ~BinTree(){if(0 < _size) remove (_root)};
    int size() const {return _size;}
    bool empty() const {return !_root;}
    BinNodePosi(T) root() const {return _root;}
    BinNodePosi(T) insertAsRoot (T const& e); //插入根节点
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e作为x的左孩子（原无）插入
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e作为x的右孩子（原无）插入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x,BinTree<T>* &T); //T作为x左子树接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x,BinTree<T>* &T); //T作为右孩子接入
    int remove(BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T>* secede (BinNodePosi(T) x); //将子树x从当前树中摘除，并将其转化为一棵独立子树
    template <typename VST>
    void travLevel (VST& visit) {if(_root) _root->travLevel(visit);} //层次遍历
    template <typename VST>
    void tracPre (VST& visit) {if(_root) _root->travPre(visit);} //先序遍历
    template <typename VST>
    void tracIn (VST& visit) {if(_root) _root->travIn(visit);} //中序遍历
    template <typename VST>
    void tracPost (VST& visit) {if(_root) _root->travPost(visit);} //后序遍历
    bool operator== (BinTree<T> const& t)
    {return _root && t._root && (_root == t._root);}
};
template <typename T> int BinTree<T>::updataHeight(BinNodePosi(T) x){
    return x->height = 1 + max( stature(x->lc),stature(x->rc));
}
template <typename T> void BinTree<T>::updataHeightAbove(BinNodePosi(T) x){
    while (x)
    {
        updataHeight(x);
        x = x->parent;
    }    
}
template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e){
    _size = 1;
    return _root = new BinNode<T>(e);
}
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x,T const& e)
{
    _size++;
    x->insertAsRc(e);
    updataHeightAbove(x);
    return x->rc;
}
template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,T const& e){
    _size++;
    x->insertAsLc(e);
    updataHeightAbove(x);
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x,BinTree<T>* &S){
    if(x->rc = S->_root){
        x->rc->parent = x;
    }
    _size += S->_size;
    updataHeightAbove(x);
    S->_root = NUll;
    S->size = 0;
    release(S);
    S = NULL;
    return x;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x,BinTree<T>* &S){
    if(x->lc = S->_root){
        x->lc->parent = x;
    }
    _size += S->_size;
    updataHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}
template <typename T>
static int removeAt(BinNodePosi(T) x){
    if(!x) return 0;
    int n = removeAt(x->lc) + removeAt(x->rc) + 1;
    release(x->data);
    release(x);
    return n;
}
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x){
    FromParentTo (*x) = NULL;
    updataHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}
template <typename T>
BinTree<T>* BinTree<T>::secede (BinNodePosi(T) x){
    FromParentTo (*x) = NULL;
    updataHeightAbove(x->parent);
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}






















