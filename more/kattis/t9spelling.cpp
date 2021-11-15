#include <bits/stdc++.h>
using namespace std;

//          a b c d e f g h i j k l m n o p q r s t u v w x y z
int nums[] {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
int cont[] {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};

int main(){
	int T;
	cin>>T;
	cin.ignore();
	int prev=0;
	for(int t=0;t<T;++t){
		cout<<"Case #"<<t+1<<": ";
		while(1){
			char c;
			c=getchar();
			if(cin.eof() || c=='\r' || c=='\n'){
				break;
			}

			if(c==' '){
				if (prev==0){
					cout<<" ";
				}
				prev=0;
				cout<<0;
				continue;
			}
			int num=nums[c-'a'];
			if(num==prev){
				cout<<" ";
			}
			prev=num;

			for(int i=0;i<cont[c-'a'];++i){
				cout<<num;
			}
		}
		cout<<"\n";
	}
}