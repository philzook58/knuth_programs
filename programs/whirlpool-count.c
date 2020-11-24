#define maxn 8
#define maxmn 36
#define o mems++
#define oo mems+= 2
#define ooo mems+= 3 \

#define thresh 1000000000000000000 \

/*1:*/
#line 47 "./whirlpool-count.w"

#include <stdio.h> 
#include <stdlib.h> 
int m,n;
unsigned long long*count;
unsigned long long newcount[maxmn];
unsigned long long mems;
int x[maxn+1];
int ay[maxn+1];
int l[maxmn],u[maxmn];
int tpow[maxmn+1];
/*4:*/
#line 193 "./whirlpool-count.w"

int mu(int t){
register int r,a,p,tt;
for(r= t%(n+1),
tt= t;o,x[r]<tt-n;tt--,r= (r?r-1:n));
for(o,p= x[r],r= (r?r-1:n),a= 0;a<n;a++,r= (r?r-1:n))
o,p= p*(tt-a)+x[r];
return p;
}

/*:4*/
#line 58 "./whirlpool-count.w"
;
main(int argc,char*argv[]){
register int a,b,c,d,i,j,k,p,q,r,mn,t,tt,kk,bb,cc,pdel;
/*2:*/
#line 66 "./whirlpool-count.w"

if(argc!=3||sscanf(argv[1],"%d",
&m)!=1||sscanf(argv[2],"%d",
&n)!=1){
fprintf(stderr,"Usage: %s m n\n",
argv[0]);
exit(-1);
}
mn= m*n;
if(m<2||m> maxn||n<2||n> maxn||mn> maxmn){
fprintf(stderr,"Sorry, m and n should be between 2 and %d, with mn<=%d!\n",
maxn,maxmn);
exit(-2);
}
for(k= n+1;k<=mn;k++){
register unsigned long long acc= 1;
for(j= 0;j<=n;j++)acc*= k-j;
if(acc>=0x80000000){
fprintf(stderr,"Sorry, mn\\falling(n+1) must be less than 2^31!\n");
exit(-666);
}
tpow[k]= acc;
}
count= (unsigned long long*)malloc(tpow[mn]*sizeof(unsigned long long));
if(!count){
fprintf(stderr,"I couldn't allocate %d entries for the counts!\n",
tpow[mn]);
exit(-4);
}

/*:2*/
#line 61 "./whirlpool-count.w"
;
for(i= 1;i<m;i++)for(j= 0;j<n;j++)/*8:*/
#line 291 "./whirlpool-count.w"

{
t= n*i+j-1;
if(t<n){
for(p= 0;p<tpow[n+1];p++)o,count[p]= 1;
continue;
}
/*5:*/
#line 214 "./whirlpool-count.w"

x1:for(k= 0;k<=t;k++)o,l[k]= k+1;
o,l[t+1]= 0;
k= 0,kk= t%(n+1);
x2:if(k==n)/*6:*/
#line 242 "./whirlpool-count.w"

{
/*7:*/
#line 279 "./whirlpool-count.w"

for(tt= t,a= 0,r= t%(n+1);
a<n;a++,tt--,r= (r?r-1:n))
if(o,x[r]>=tt-n)break;
if(a==n)pdel= 0;
else{
for(p= pdel= 0,a= 0;a<=n;a++,r= (r?r-1:n)){
if(r!=kk)p= p*(tt+1-a)+x[r],pdel= pdel*(tt+1-a);
else p= p*(tt+1-a),pdel= pdel*(tt+1-a)+1;
}
}

/*:7*/
#line 245 "./whirlpool-count.w"
;
for(d= 0;d<=t+1;d++)o,newcount[d]= 0;
oo,b= ay[n-1],c= ay[0];
if(b<c)bb= b,cc= c;
else bb= c,cc= b;
{
register unsigned long long tmp;
for(oo,a= l[t+1],x[kk]= 0;a<=t;oo,a= l[a],x[kk]++){
if(pdel)tmp= count[p+x[kk]*pdel];
else tmp= count[mu(t-n)];
if(j==0)newcount[0]+= tmp;
else if(a<bb||a> cc){
for(d= bb+1;d<=cc;d++)oo,newcount[d]+= tmp;
}else{
for(d= 0;d<=bb;d++)oo,newcount[d]+= tmp;
for(d= cc+1;d<=t+1;d++)oo,newcount[d]+= tmp;
}
}
if(pdel){
for(d= 0;d<=t-n;d++)oo,count[p+d*pdel]= newcount[j?d:0];
for(;d<=t+1;d++)ooo,x[kk]= d,count[mu(t+1)]= newcount[j?d:0];
}else{
for(d= 0;d<=t+1;d++)ooo,x[kk]= d,count[mu(t+1)]= newcount[j?d:0];
}
}
goto x6;
}

/*:6*/
#line 218 "./whirlpool-count.w"
;
oo,p= t+1,q= l[p],x[kk]= 0;
x3:o,ay[k]= q;
x4:ooo,u[k]= p,l[p]= l[q],k++,kk= (kk?kk-1:n);
goto x2;
x5:o,p= q,q= l[p];
if(q<=t){
oo,x[kk]++;
goto x3;
}
x6:if(--k>=0){
kk= (kk==n?0:kk+1);
ooo,p= u[k],q= ay[k],l[p]= q;
goto x5;
}

/*:5*/
#line 298 "./whirlpool-count.w"
;
fprintf(stderr," done with %d,%d ..%lld, %lld mems\n",
i,j,count[0],mems);
}

/*:8*/
#line 62 "./whirlpool-count.w"
;
/*9:*/
#line 305 "./whirlpool-count.w"

for(newcount[0]= newcount[1]= newcount[2]= 0,p= tpow[mn]-1;p>=0;p--){
if(count[p]> newcount[2])newcount[2]= count[p],pdel= p;
o,newcount[0]+= count[p];
if(newcount[0]>=thresh)ooo,newcount[0]-= thresh,newcount[1]++;
}
fprintf(stderr,"(Maximum count %lld is obtained for params",
newcount[2]);
for(q= mn-n-1;q<mn;q++){
fprintf(stderr," %d",pdel%(q+1));
pdel/= q+1;
}
fprintf(stderr,")\n");
if(newcount[1]==0)
printf("Altogether %lld %dx%d whirlpool perms (%lld mems).\n",
newcount[0],m,n,mems);
else printf("Altogether %lld%018lld %dx%d whirlpool perms (%lld mems).\n",
newcount[1],newcount[0],m,n,mems);

/*:9*/
#line 63 "./whirlpool-count.w"
;
}

/*:1*/
