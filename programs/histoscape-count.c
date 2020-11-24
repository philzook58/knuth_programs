#define maxn 10
#define maxt 16
#define o mems++
#define oo mems+= 2
#define ooo mems+= 3 \

/*1:*/
#line 25 "./histoscape-count.w"

#include <stdio.h> 
#include <stdlib.h> 
int m,n,t;
char bad[maxt][maxt][maxt][maxt];
unsigned long long*count;
unsigned long long newcount[maxt];
unsigned long long mems;
int inx[maxn+1];
int tpow[maxn+2];
main(int argc,char*argv[]){
register int a,b,c,d,i,j,k,p,q,r,pp;
/*2:*/
#line 43 "./histoscape-count.w"

if(argc!=4||sscanf(argv[1],"%d",
&m)!=1||sscanf(argv[2],"%d",
&n)!=1||sscanf(argv[3],"%d",
&t)!=1){
fprintf(stderr,"Usage: %s m n t\n",
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
#line 37 "./histoscape-count.w"
;
/*3:*/
#line 70 "./histoscape-count.w"

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
#line 38 "./histoscape-count.w"
;
for(i= 1;i<m;i++)for(j= 1;j<n;j++)/*5:*/
#line 98 "./histoscape-count.w"

{
if(j==1)/*6:*/
#line 122 "./histoscape-count.w"

{
if(i==1){
for(o,p= tpow[n+1];p> 0;p--)o,count[p-1]= 1;
q= 0;
}else{
q= (q==n?0:q+1);
while(1){
for(o,a= 0,pp= p,newcount[0]= 0;a<t;a++,pp+= tpow[q])o,newcount[0]+= count[pp];
for(a= 0,pp= p;a<t;a++,pp+= tpow[q])o,count[pp]= newcount[0];
/*4:*/
#line 89 "./histoscape-count.w"

for(r= 0;r<=n;r++)if(r!=q){
ooo,inx[r]++,p+= tpow[r];
if(inx[r]<t)break;
oo,inx[r]= 0,p-= tpow[r+1];
}

/*:4*/
#line 132 "./histoscape-count.w"
;
if(p==0)break;
}
q= (q==n?0:q+1);
}
}

/*:6*/
#line 100 "./histoscape-count.w"

else q= (q==n?0:q+1);
while(1){
o,b= (q==n?inx[0]:inx[q+1]);
o,c= (q==0?inx[n]:inx[q-1]);
for(d= 0;d<t;d++)o,newcount[d]= 0;
for(o,a= 0,pp= p;a<t;a++,pp+= tpow[q]){
for(d= 0;d<t;d++)if(o,!bad[a][b][c][d])
ooo,newcount[d]+= count[pp];
}
for(o,d= 0,pp= p;d<t;d++,pp+= tpow[q])oo,count[pp]= newcount[d];
/*4:*/
#line 89 "./histoscape-count.w"

for(r= 0;r<=n;r++)if(r!=q){
ooo,inx[r]++,p+= tpow[r];
if(inx[r]<t)break;
oo,inx[r]= 0,p-= tpow[r+1];
}

/*:4*/
#line 111 "./histoscape-count.w"
;
if(p==0)break;
}
fprintf(stderr," done with %d,%d ..%lld, %lld mems\n",
i,j,count[0],mems);
}

/*:5*/
#line 39 "./histoscape-count.w"
;
/*7:*/
#line 139 "./histoscape-count.w"

for(newcount[0]= 0,p= tpow[n+1]-1;p>=0;p--)
o,newcount[0]+= count[p];
printf("Altogether %lld 3VPs (%lld mems).\n",
newcount[0],mems);

/*:7*/
#line 40 "./histoscape-count.w"
;
}

/*:1*/
