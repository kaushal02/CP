template<class T> void in(T&p) {
	p=0;char neg=0,ch=0;
	while(ch<0x30 or ch>0x39) {if(ch=='-')neg=1; ch=getchar();}
	while(0x30<=ch and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
	if(neg)p=-p;
}
template<class T> void out(T n) {
	char d[20],i=0;
	if(n<0){putchar('-'); n=-n;}
	do{d[i++]=(n%10)|0x30; n/=10;} while(n);
	while(i) putchar(d[--i]);
	putchar('\n');
}
