#ifndef __TLIST
#define __TLIST 1

template<class T>
class tlist {
	public:
		typedef unsigned int size_t;
	private:
		struct node_t;
		node_t *head;
		size_t maxid;
	private:
		node_t *__lspin(node_t*);
		node_t *__rspin(node_t*);
		void destory(node_t*);
		node_t* n_insert(node_t*, size_t, const T&);
		node_t *rotate(node_t*);
		node_t *n_remove(node_t*, size_t);
		node_t *n_query(node_t*, size_t);
	public:
		tlist();
		~tlist();
		void append(const T&);
		void remove(size_t);
		T& query(size_t);
		void insert(size_t, const T&);
};

#endif

