int arr[4 * ms],  seg[4 * ms], lazy[4 * ms], n;

void build(int idx = 0, int l = 0, int r = n - 1) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  lazy[idx] = 0;
  if(l == r) {
    seg[idx] = arr[l];
    return;
  }
  build(left, l, mid); build(right, mid + 1, r);
  seg[idx] = seg[left] + seg[right]; // Merge
}

void propagate(int idx, int l, int r) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  if(lazy[idx]) {
    seg[idx] += lazy[idx] * (r - l + 1); // Aplicar lazy no seg
    if(l < r) {
      lazy[2*idx+1] += lazy[idx];  // Merge de lazy
      lazy[2*idx+2] += lazy[idx];  // Merge de lazy
    }
    lazy[idx] = 0; // Limpar a lazy
  }  
}

int query(int L, int R, int idx = 0, int l = 0, int r = n - 1) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  propagate(idx, l, r);
  if(R < l || L > r) return 0; // Valor que nao atrapalhe
  if(L <= l && r <= R) return seg[idx];
  return query(L, R, left, l, mid) + query(L, R, right, mid + 1, r); // Merge
}

void update(int V, int L, int R, int idx = 0, int l = 0, int r = n -1) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  propagate(idx, l, r);
  if(l > R || r < L) return;
  if(L <= l && r <= R) {
    lazy[idx] += V; // Merge de lazy/ou so colocar
    propagate(idx, l, r);
    return;
  }
  update(V, L, R, left, l, mid); update(V, L, R, right, mid + 1, r);
  seg[idx] = seg[left] + seg[right]; // Merge
}
