#define maxn 10
#define maxt 16
#define o mems++
#define oo mems+= 2
#define ooo mems+= 3 \

/*1:*/
#line 20 "./histoscape-unrank.w"

#include <stdio.h> 
#include <stdlib.h> 
int m,n,t;
unsigned long long z;
char bad[maxt][maxt][maxt][maxt];
unsigned long long*count;
unsigned long long newcount[maxt];
int firstknown;
unsigned long long mems;
int inx[maxn+1];
int tpow[maxn+2];
int pos[maxn+1];
int sol[maxn*maxn];
main(int argc,char*argv[]){
register int a,b,c,d,i,j,k,p,q,r,pp,p0;
/*2:*/
#line 48 "./histoscape-unrank.w"

if(argc!=5||sscanf(argv[1],"%d",
&m)!=1||sscanf(argv[2],"%d",
&n)!=1||sscanf(argv[3],"%d",
&t)!=1||sscanf(argv[4],"%lld",
&z)!=1){
fprintf(stderr,"Usage: %s m n t z\n",
argv[0]);
exit(-1);
}
if(m<2||m> maxn||n<2||n> maxn){
fprintf(stderr,"Sorry, m and n should be between 2 and %d!\n",
maxn);
exit(-2);
}
if(t<2||t> maxt){
fprintf(stderr,"Sorry, t should be between 2 and %d!\n",
maxt);
exit(-3);
}
for(j= 1,k= 0;k<=n+1;k++)tpow[k]= j,j*= t;
count= (unsigned long long*)malloc(tpow[n+1]*sizeof(unsigned long long));
if(!count){
fprintf(stderr,"I couldn't allocate t^%d=%d entries for the counts!\n",
n+1,tpow[n+1]);
exit(-4);
}

/*:2*/
#line 36 "./histoscape-unrank.w"
;
/*3:*/
#line 76 "./histoscape-unrank.w"

for(a= 0;a<t;a++)for(b= 0;b<=a;b++)for(c= 0;c<=b;c++)for(d= 0;d<=a;d++){
if(d> b)goto nogood;
if(a> b&&c> d)goto nogood;
if(a> b&&b==d&&d> c)goto nogood;
continue;
nogood:bad[a][b][c][d]= 1;
bad[a][c][b][d]= 1;
bad[b][d][a][c]= 1;
bad[b][a][d][c]= 1;
bad[d][c][b][a]= 1;
bad[d][b][c][a]= 1;
bad[c][a][d][b]= 1;
bad[c][d][a][b]= 1;
}

/*:3*/
#line 37 "./histoscape-unrank.w"
;
firstknown= m*n;
loop:while(firstknown){
for(i= 1;i<m;i++)for(j= 1;j<n;j++)
/*7:*/
#line 149 "./histoscape-unrank.w"

{
if(j==1)/*10:*/
#line 207 "./histoscape-unrank.w"

{
if(i==1){
o,p= q= 0,newcount[0]= 1;
for(r= 0;r<=n;r++){
if(r<firstknown)ooo,pos[r]= inx[r]= 0;
else ooo,pos[r]= r,inx[r]= sol[r],p+= inx[r]*tpow[r];
}
p0= p;
while(1){
for(a= 0,pp= p;a<t;a++,pp+= tpow[q])o,count[pp]= newcount[0];
/*6:*/
#line 137 "./histoscape-unrank.w"

for(r= 0;r<=n;r++)if(r!=q&&(o,pos[r]==0)){
ooo,inx[r]++,p+= tpow[r];
if(inx[r]<t)break;
oo,inx[r]= 0,p-= tpow[r+1];
}

/*:6*/
#line 218 "./histoscape-unrank.w"
;
if(p==p0)break;
}
}else{
q= (q==n?0:q+1);
if(n*i==firstknown+n)/*11:*/
#line 238 "./histoscape-unrank.w"

{
for(o,a= 0,pp= p;a<t;a++,pp+= tpow[q]){
if(o,z<count[pp])break;
z-= count[pp];
}
if(a==t){
fprintf(stderr,"internal error, z too large at %d,0\n",
i);
exit(-6);
}
sol[--firstknown]= a;
fprintf(stderr,"cell %d,%d is %d; z reset to %lld\n",
i-2,n-1,a,z);
goto loop;
}


/*:11*/
#line 223 "./histoscape-unrank.w"
;
while(1){
for(o,a= 0,pp= p,newcount[0]= 0;a<t;a++,pp+= tpow[q])
o,newcount[0]+= count[pp];
if(n*i>=firstknown)o,count[p+sol[n*i]*tpow[q]]= newcount[0];
else for(a= 0,pp= p;a<t;a++,pp+= tpow[q])o,count[pp]= newcount[0];
/*6:*/
#line 137 "./histoscape-unrank.w"

for(r= 0;r<=n;r++)if(r!=q&&(o,pos[r]==0)){
ooo,inx[r]++,p+= tpow[r];
if(inx[r]<t)break;
oo,inx[r]= 0,p-= tpow[r+1];
}

/*:6*/
#line 229 "./histoscape-unrank.w"
;
if(p==p0)break;
}
if(i*n>=firstknown)
ooo,pos[q]= i*n,inx[q]= sol[i*n],p+= inx[q]*tpow[q],p0= p;
q= (q==n?0:q+1);
}
}

/*:10*/
#line 151 "./histoscape-unrank.w"

else q= (q==n?0:q+1);
while(1){
o,b= (q==n?inx[0]:inx[q+1]);
o,c= (q==0?inx[n]:inx[q-1]);
if(i*n+j>=firstknown)
/*8:*/
#line 175 "./histoscape-unrank.w"

{
d= sol[i*n+j];
if(i*n+j==firstknown+n)/*9:*/
#line 185 "./histoscape-unrank.w"

{
for(o,a= 0,pp= p;a<t;a++,pp+= tpow[q])if(o,!bad[a][b][c][d]){
if(o,z<count[pp])break;
z-= count[pp];
}
if(a==t){
fprintf(stderr,"internal error, z too large at %d,%d\n",
i,j);
exit(-6);
}
sol[--firstknown]= a;
fprintf(stderr,"cell %d,%d is %d; z reset to %lld\n",
firstknown/n,firstknown%n,
a,z);
goto loop;
}

/*:9*/
#line 178 "./histoscape-unrank.w"
;
for(oo,newcount[d]= 0,a= 0,pp= p;a<t;a++,pp+= tpow[q]){
if(o,!bad[a][b][c][d])ooo,newcount[d]+= count[pp];
}
o,count[p+d*tpow[q]]= newcount[d];
}

/*:8*/
#line 157 "./histoscape-unrank.w"

else{
for(d= 0;d<t;d++)o,newcount[d]= 0;
for(o,a= 0,pp= p;a<t;a++,pp+= tpow[q]){
for(d= 0;d<t;d++)if(o,!bad[a][b][c][d])
ooo,newcount[d]+= count[pp];
}
for(o,d= 0,pp= p;d<t;d++,pp+= tpow[q])oo,count[pp]= newcount[d];
}
/*6:*/
#line 137 "./histoscape-unrank.w"

for(r= 0;r<=n;r++)if(r!=q&&(o,pos[r]==0)){
ooo,inx[r]++,p+= tpow[r];
if(inx[r]<t)break;
oo,inx[r]= 0,p-= tpow[r+1];
}

/*:6*/
#line 166 "./histoscape-unrank.w"
;
if(p==p0)break;
}
if(i*n+j>=firstknown)
ooo,pos[q]= i*n+1,inx[q]= sol[i*n+j],p+= inx[q]*tpow[q],p0= p;
fprintf(stderr," done with %d,%d ..%lld, %lld mems\n",
i,j,count[0],mems);
}

/*:7*/
#line 42 "./histoscape-unrank.w"
;
/*5:*/
#line 107 "./histoscape-unrank.w"

for(k= 0;k<=n;k++){
o,pos[q]= --firstknown;
if(q==0)q= n;else q--;
}
for(p= 0;p<tpow[n+1];p++){
if(o,z<count[p])break;
z-= count[p];
}
if(p==tpow[n+1]){
fprintf(stderr,"Oops, z exceeds the total number of solutions!\n");
exit(-4);
}
for(k= 0;k<=n;k++){
sol[pos[k]]= p%t;
fprintf(stderr,"cell %d,%d is %d\n",
pos[k]/n,pos[k]%n,
sol[pos[k]]);
p/= t;
}
fprintf(stderr,"z reset to %lld\n",
z);

/*:5*/
#line 43 "./histoscape-unrank.w"
;
}
/*4:*/
#line 92 "./histoscape-unrank.w"

fprintf(stderr,"Solution completed after %lld mems:\n",
mems);
for(i= 0;i<m;i++){
for(j= 0;j<n;j++)printf(" %d",
sol[i*n+j]);
printf("\n");
}

/*:4*/
#line 45 "./histoscape-unrank.w"
;
}

/*:1*/
