template <typename T>
struct List {
    T n;
    List *l, *r;
    List() {n = T(); l = r = NULL;}
    List(T n_ = T(), List *l_ = NULL, List *r_ = NULL) { n = n_; l = l_; r = r_;}
    inline bool isend() { return l == NULL or r == NULL;}
    inline bool isalone() { return l == NULL and r == NULL;}
    inline void next(T _n) {
        List *newList = new List(_n, this, this->r);
        if(this->r) this->r->l = newList;
        this->r = newList;
    }
    inline void next(List *newList) {
        newList->l = this;
        this->r = newList;
    }
    inline void prev(T _n) {
        List *newList = new List(_n, this->l, this);
        if(this->l) this->l->r = newList;
        this->l = newList;
    }
    inline void prev(List *newList) {
        newList->r = this;
        this->l = newList;
    }
    inline void print() {
        List *temp = this;
        if(temp->l != NULL) cerr << "-> ";
        while(temp != NULL) {
            cerr << temp->n << " -> ";
            temp = temp->r;
        }
        cerr << "end\n";
    }
};