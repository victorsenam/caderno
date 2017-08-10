//const int N = ;
//typedef int num;

int en = 1;
int p[N], sz[N];
int C[N][2]; // {left, right} children
int pp[N];

// atualize os valores associados aos nos que podem ser calculados a partir dos filhos
inline void calc(int u) {
	sz[u] = sz[C[u][0]] + 1 + sz[C[u][1]];
}

// Puxa o filho dir de u para ficar em sua posicao e o retorna
int rotate(int u, int dir) {
	int v = C[u][dir];
	swap(pp[v], pp[u]);
	C[u][dir] = C[v][!dir];
	if(C[u][dir]) p[C[u][dir]] = u;
	C[v][!dir] = u;
	p[v] = p[u];
	if(p[v]) C[p[v]][C[p[v]][1] == u] = v;
	p[u] = v;
	calc(u);
	calc(v);
	return v;
}

// Traz o no u a raiz
void splay(int u) {
	while(p[u]) {
		int v = p[u], w = p[p[u]];
		//printf("splay %d->%d->%d\n", u, v, w);
		int du = (C[v][1] == u);
		if(!w) {
			rotate(v, du);
			assert(!p[u]);
			break;
		} else {
			int dv = (C[w][1] == v);
			if(du == dv) {
				rotate(w, dv);
				assert(C[v][du] == u);
				rotate(v, du);
			} else {
				rotate(v, du);
				assert(C[w][dv] == u);
				rotate(w, dv);
			}
		}
	}
}

// retorna o s-esimo no (0-indexed)
int find_sz(int u, int s) {
	while(sz[C[u][0]] != s) {
		if(sz[C[u][0]] < s) {
			s -= sz[C[u][0]] + 1;
			u = C[u][1];
		} else u = C[u][0];
	}
	splay(u);
	return u;
}

// chame isso 1 vez no inicio
void init() {
	en = 1;
}

// Cria um novo no
int new_node() {
	int i = en++;
	assert(i < N);
	C[i][0] = C[i][1] = p[i] = 0;
	sz[i] = 1;
	pp[i] = 0;
	return i;
}

int access(int u) {
	splay(u);
	if(int v = C[u][1]) {
		p[v] = 0;
		pp[v] = u;
		C[u][1] = 0;
	}
	calc(u);
	while(pp[u]) {
		//printf("access %d->%d\n", u, pp[u]);
		int w = pp[u];
		splay(w);
		if(int v = C[w][1]) {
			p[v] = 0;
			pp[v] = w;
		}
		C[w][1] = u;
		assert(!p[u]);
		p[u] = w;
		pp[u] = 0;
		calc(w);
		splay(u);
	}
	return u;
}

int find(int u) {
	//printf("find(%d)\n", u);
	access(u);
	while(C[u][0]) { u = C[u][0]; }
	access(u);
	//printf(">>find(%d)\n", u);
	return u;
}

void link(int u, int v) {
	//printf("link(%d, %d)\n", u, v);
	if(find(u) == find(v)) return;
	access(u); access(v);
	assert(!C[u][1]);
	C[u][1] = v;
	p[v] = u;
	pp[v] = 0;
	calc(u);
	//printf(">link(%d, %d)\n", u, v);
}

void deb(int u) {
	if(!u) return;
	printf("(");
	deb(C[u][0]);
	printf(" %d ", u);
	deb(C[u][1]);
	printf(")");
}

void cut(int u) {
	access(u); // left subtree is all its parents
	assert(C[u][0]);
	if(int v = C[u][0]) {
		p[v] = 0;
		pp[v] = 0;
	}
	C[u][0] = 0;
	calc(u);
}
