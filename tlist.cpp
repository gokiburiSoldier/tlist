#include "tlist.h"
#include <stddef.h>
#include <stdio.h>

#ifndef __TLIST_CP
#define __TLIST_CP

#define tt template<class T>
#define tl tlist<T>

#define maketag(u, opt) if(u->right) {\
	opt##opt u->right->lazy; \
	u->right->id opt##= -1;\
}
#define pds(u, side) if(u->side) {u->side->lazy+=u->lazy; u->side->id-=u->lazy;}
#define pushdown(u) pds(u, left) pds(u, right) u->lazy=0;

tt struct tl::node_t {
	size_t id;
	T val;
	node_t *left, *right;
	signed lazy;
	int size, depth;
};

tt tl::tlist(): head(NULL), maxid(0U) {}

tt tl::~tlist() {
	destory(head);
}

tt void tl::destory(node_t *u) {
	if(u->left) destory(u->left);
	if(u->right) destory(u->right);
	delete u;
}

tt void tl::append(const T& value) {
	head=n_insert(head, maxid++, value);
}

tt void tl::remove(size_t index) {
	head=n_remove(head, index);
	--maxid;
}

tt void tl::insert(size_t index, const T& val) {
	node_t *orig=n_query(head, index), *fina;
#if 0
		size_t tar=index+orig->right->size+1;
		node_t *fa;
		if(tar < maxid) {
			fa=n_query(head, tar);
			if(fa->left != orig) fa=fa->left;
		}
		else fa=n_query(head, index-orig->left->size-1);
		/*  */
		if(fa->left == orig) fina=fa->left=n_insert(orig, index, val);
		else fina=fa->right=n_insert(orig, index, val);
		--orig->lazy;
		rotate(fina);
#endif
	head=n_insert(head, index, val);
	++maxid;
}

tt T& tl::query(size_t index) {
	if(index >= maxid) throw "666";
	return n_query(head, index)->val;
}

#define max(a, b) ((a)>(b) ? (a) : (b))
#define cr curr->right

#define dp(u) ((u) ? u->depth : 0)
tt typename tl::node_t* tl::n_insert(node_t *curr, size_t id, const T& val) {
	if(!curr) return new node_t{id, val ,NULL, NULL, 
		0, 1, 1};
	if(curr->id == id) {
		pushdown(curr)
		node_t *tmp=new node_t{id, val, curr->left, curr, 0,
			curr->size+1, curr->depth+1};
		curr->left=NULL;
		curr->size=(cr ? cr->size : 0)+1;
		curr->depth=(cr ? cr->depth : 0)+1;
		++curr->id;
		maketag(curr, -)
		return rotate(tmp);
	}
	#if 0
	if(curr->right) {
		cr->id -= curr->lazy;
		cr->lazy += curr->lazy;
	}
	curr->lazy=0;
	#endif
	pushdown(curr)
	size_t uid=curr->id;
	if(uid < id) {
		curr->right = n_insert(curr->right, id, val);
		++curr->size;
		curr->depth=max(dp(curr->left), dp(cr))+1;
		return rotate(curr);
	}
	if(uid > id) {
		curr->left = n_insert(curr->left, id, val);
		++curr->id;
		maketag(curr, -)
		++curr->size;
		curr->depth=max(dp(curr->left), dp(cr))+1;
		return rotate(curr);
	}
	return curr;
}

#define bf(u) ((u) ? (dp(u->left) - dp(u->right)) : 0)
#define sz(u) ((u) ? u->size : 0)
#define upd(u) u->depth=max(dp(u->left), dp(u->right))+1; \
			   u->size = sz(u->left)+sz(u->right)+1;

tt
typename tl::node_t* tl::__lspin(node_t* u) {
	node_t *r=u->right;
	u->right=r->left;
	r->left=u;
	upd(r)
	upd(u)
	return r;
}

tt
typename tl::node_t* tl::__rspin(node_t *u) {
	node_t *l=u->left;
	u->left=l->right;
	l->right=u;
	upd(u)
	upd(l)
	return l;
}

tt typename tl::node_t* tl::rotate(node_t *u) {
	int ubf=bf(u);
	#if 0
	if(u->right) {
		u->right->id -= u->lazy;
		u->right->lazy += u->lazy;
	}
	u->lazy=0;
	#endif
	pushdown(u);
	if(ubf >  1 && bf(u->left)  >= 0) return __rspin(u);
	if(ubf >  1 && bf(u->left)  <  0) {
		u->left = __lspin(u->left);
		return __rspin(u);
	}
	if(ubf < -1 && bf(u->right) <= 0) return __lspin(u);
	if(ubf < -1 && bf(u->right) >  0) {
		u->right=__rspin(u->right);
		return __lspin(u);
	}
	return u;
}

tt typename tl::node_t *tl::n_query(node_t *u, size_t i) {
	if(!u) return NULL;
	size_t uid=u->id;
	if(uid == i) return u;
	pushdown(u)
	if(uid >  i) return n_query(u->left, i);
	return n_query(u->right, i);
}

tt typename tl::node_t *tl::n_remove(node_t *tgt, size_t id) {
	if(!tgt) return NULL;
	pushdown(tgt)
	size_t uid=tgt->id;
	if(uid == id) {
		if(tgt->right && tgt->left) {
			tgt->val=n_query(tgt->right, id+1)->val;
			tgt->right=n_remove(tgt->right, id+1);
			maketag(tgt, +)
			upd(tgt)
			return rotate(tgt);
		}
		else {
			node_t *ret=tgt;
			if(tgt->left) ret=tgt->left;
			else ret=tgt->right;
			maketag(tgt, +)
			delete tgt;
			return ret;
		}
	}
	pushdown(tgt)
	if(uid > id) { 
		tgt->left=n_remove(tgt->left, id);
		--tgt->id;
		maketag(tgt, +)
	}
	else if(uid < id)
		tgt->right=n_remove(tgt->right, id);
	upd(tgt);
	return rotate(tgt);
}
#undef sz
#undef upd

#undef pushdown
#undef pds
#undef maketag

#undef dp
#undef bf
#undef tt
#undef cr
#undef max

#endif

