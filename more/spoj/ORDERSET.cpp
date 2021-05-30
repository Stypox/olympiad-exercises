#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define assert(x)

istream& in = cin;
ostream& out = cout;
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
constexpr float alpha=0.6666667;

struct Node {
   Node* par, * left=nullptr, * right=nullptr;
   int val, n=1, s;

   Node(int v, Node* p) : par{p}, val{v} {}
   ~Node() {
      if (left != nullptr) delete left;
      if (right != nullptr) delete right;
   }

   void print() {
      cout<<val<<":"<<n<<":(";
      if(left != nullptr) left->print();
      cout<<" ";
      if(right != nullptr) right->print();
      cout<<")";
   }

   bool isScapegoat() {
      int l = (left == nullptr ? 0 : left->n); // (*left).n === left->n
      int r = (right == nullptr ? 0 : right->n);
      return max(l, r) > alpha*n;
   }

   Node* insert(int x) {
      n++;
      s=max(s, n);

      Node* & side = (x<val ? left : right);
      Node* rebalancingNode = nullptr;
      if (side == nullptr) {
         side = new Node(x, this);
      } else {
         rebalancingNode = side->insert(x);
      }

      if (this->isScapegoat()) {
         rebalancingNode = this;
      }
      return rebalancingNode;
   }

   Node* find(int x) {
      if (x==val) {
         return this;
      } else if (x<val) {
         if (left == nullptr) return nullptr;
         return left->find(x);
      } else /* x>val */ {
         if(right==nullptr) return nullptr;
         return right->find(x);
      }
   }

   void erase() {
      if (n == 1) {
         if (par != nullptr) {
            if (this == par->left) par->left = nullptr;
            else par->right = nullptr;
         }

         while (par != nullptr) {
            par->n--;
            par = par->par;
         }
         delete this;

         return;
      }

      Node* dbc; // da bruciare
      if (left == nullptr) {
         dbc=right;
         while(dbc->left != nullptr) dbc = dbc->left;
      } else {
         dbc=left;
         while(dbc->right != nullptr) dbc = dbc->right;
      }

      val = dbc->val;
      dbc->erase();
   }

   Node* kth(int x) {
      if (left != nullptr) {
         if (left->n <= x) {
            x -= left->n;
         } else {
            return left->kth(x);
         }
      }
      
      if (x == 0) return this;
      assert(x > 0);
      assert(right != nullptr);
      return right->kth(x-1);
   }

   int countSmaller(int x) {
      if (val < x)
         return 1 + (left == nullptr ? 0 : left->n)
                  + (right == nullptr ? 0 : right->countSmaller(x));
      return left == nullptr ? 0 : left->countSmaller(x);
   }

   void rebalance() {
      vector<int> vals;

      function<void(Node*)> dfs = [&] (Node* e) {
         if(e->left!=nullptr) dfs(e->left);
         vals.push_back(e->val);
         if(e->right!=nullptr) dfs(e->right);
      };
      dfs(this);

      Node* other=balance(vals.begin(), vals.end());
      assert(other->n == other->n);
      this->val=other->val;
      swap(this->left, other->left);
      swap(this->right, other->right);
      delete other;
      if(left!=nullptr) left->par=this;
      if(right!=nullptr) right->par=this;
   }

private:
   template<typename I>
   static Node* balance(I start, I finish) {
      if(finish-start == 0) return nullptr;
      if(finish-start == 1) return new Node(*start, nullptr);
      I center = start + (finish - start) / 2;
      Node* res=new Node(*center, nullptr);
      res->left = balance(start, center);
      res->right = balance(center + 1, finish);
      if (res->left != nullptr) {
         res->left->par = res;//imposta il genitore dei figli
         res->n += res->left->n;
      }
      if (res->right != nullptr) {
         res->right->par = res;
         res->n += res->right->n;
      }
      res->s=res->n;
      return res;
   }
};

struct ScapegoatTree {
   Node* root=nullptr;

   ScapegoatTree() {}
   ~ScapegoatTree() {
      if (root != nullptr) delete root;
   }

   void print() {
      if (root == nullptr) {
         cout<<"( )";
      } else {
         root->print();
      }
      cout<<"\n";
   }

   void insert(int x) {
      if (root == nullptr) {
         root = new Node(x, nullptr);
      } else if (!root->find(x)) {
         Node* rebalancingNode = root->insert(x);
         if (rebalancingNode != nullptr) {
            rebalancingNode->rebalance();
         }
      }
   }

   void erase(int x) {
      if (root == nullptr) return;

      Node* found = root->find(x);
      if (found == nullptr) return;

      if (found == root && root->n == 1) root = nullptr;
      found->erase();
   }

   Node* kth(int x) {
      if (root == nullptr || x >= root->n) return nullptr;
      return root->kth(x);
   }

   int countSmaller(int x) {
      if (root == nullptr) return 0;
      return root->countSmaller(x);
   }
};

signed main() {
   ScapegoatTree t;   
   int N;
   in>>N;
   for(int n=0;n<N;++n){
      in.ignore();
      char c;
      int x;
      in>>c>>x;
      switch(c){
      case 'I':
         t.insert(x);
         break;
      case 'D':
         t.erase(x);
         break;
      case 'K': {
         Node* kth = t.kth(x-1);
         if (kth == nullptr) out << "invalid\n";
         else out << kth->val << "\n";
         break;
      }
      case 'C':
         out << t.countSmaller(x) << "\n";
         break;
      }
   }
}
