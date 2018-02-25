while(l<r) {
	//minimum ok..			|	//maximum ok..
	mid=l+r>>1;				|	mid=l+r+1>>1;
	if(ok(mid)) r=mid;		|	if(ok(mid)) l=mid;
	else l=mid+1;			|	else r=mid-1;
}
while(l<r) {
	if(f((l+l+r)/3) < f((l+r+r)/3)) l=(l+l+r)/3;
	else r=(l+r+r)/3;
}
