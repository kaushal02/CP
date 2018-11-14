typedef complex<dbl> cpx;
void fft(vector<cpx>& a, int s = 1) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for( ; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        dbl ang = 2 * s * pi / len;
        cpx wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cpx w(1);
            for (int j = 0; j < len / 2; j++) {
                cpx u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (s == -1) {
        for (auto &ai : a) {
            ai /= n;
        }
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    vector<cpx> fa(all(a)), fb(all(b));
    
    int n = 1;
    while (n < max(a.size(), b.size())) {
        n <<= 1;
    }
    n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa), fft(fb);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, -1);
    
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = fa[i].real() + 0.5;
    }
    return res;
}