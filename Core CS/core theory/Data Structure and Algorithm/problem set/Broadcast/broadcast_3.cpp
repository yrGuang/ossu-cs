#include <cstdio>

#define DEFAULT_CAPACITY 10

template <typename T> class Vector {
protected:
	int _size; int _capacity; T* _elem;
	void expand() {
		if (_size < _capacity) return;
		if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
		T* oldElem = _elem; _elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = oldElem[i];
		delete [] oldElem;
	}
public:
	Vector (int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v) ;
	}

	~Vector() { delete [] _elem; }

	int size() { return _size; }
	int capacity() { return _capacity; }

	bool empty() { return !_size; }
	bool full() { return _size == _capacity; }

	T& operator [] (int r) const { return _elem[r]; }

	int insert (int r, T const& e) {
		expand();
		int n = _size++;
		while (n > r) _elem[n] = _elem[--n];
		_elem[r] = e;
		return r;
	}
	int insert (T const& e) { return insert(_size, e); }

	T remove (int r) {
		T e = _elem[r];
		_size--;
		while (r < _size) _elem[r] = _elem[++r];
		return e;
	}
};

#define FM 1

struct Node {
	int data;
	Node* next;
	int f;
	Node(int d = -1) : data(d), next(NULL), f(0) {}
};

int main() {
	int n, m; int u, v;
	scanf("%d%d", &n, &m);

	Vector<Node*> V(n, n, (Node*) NULL);
	int* queue = new int[m*2]; int head = 0, tail = 0;

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v); u -= 1; v -= 1;
		if (u > v) { int temp = u; u = v; v = temp; }

		if (!V[u]) V[u] = new Node(u);
		if (u == v) continue;
		if (!V[v]) V[v] = new Node(v);

		Node* p = new Node(v);
		p->next = V[u]->next; V[u]->next = p;
	}

	for (int j = 0; j < n; j++) {
		if ( !V[j] || !(V[j]->next) || V[j]->f ) continue;
		
		Node* temp = V[j]->next;
		while (temp && !V[temp->data]->f) temp = temp->next;
		if (temp) V[j]->f = - V[temp->data]->f;
		else V[j]->f = FM;

		queue[tail++] = V[j]->data;
		while (head < tail) {
			Node* p = V[queue[head++]];
			//printf("\nroot of subtree: %d(%d)\n", p->data + 1, p->f);
			int s = p->f; p = p->next;
			while (p) {
				queue[tail++] = p->data;
				//printf("%d ", p->data + 1);
				if (V[p->data]->f == s) { printf("-1\n"); return 0; }
				V[p->data]->f = -s;
				p = p->next;
			}
			//printf("head: %d, tail: %d\n", head, tail);
		}
		//printf("j: %d\n", j);
	}
	printf("1\n");
	delete [] queue; return 0;
}