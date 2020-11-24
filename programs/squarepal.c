#define maxn 180 \

#define m32 0xffffffff \

#define comp(x) ((1LL<<(t+2) ) -(x) )  \

/*1:*/
#line 27 "./squarepal.w"

#include <stdio.h> 
#include <stdlib.h> 
int n;
unsigned long long y[maxn/2],r[maxn/2];
unsigned long long q[maxn/4],qq[maxn/4];
unsigned long long pretrial[2],trial[3],acc[6];
main(int argc,char*argv[]){
register unsigned long long prod,sqrtxl,a,bit;
register int j,k,t,p,jj,kk;
/*2:*/
#line 44 "./squarepal.w"

if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",
argv[0]);
exit(-1);
}
if(n<15||n> maxn){
fprintf(stderr,"Sorry: n should be between 15 and %d.\n",
maxn);
exit(-2);
}

/*:2*/
#line 37 "./squarepal.w"
;
printf("Binary palindromic squares with %d bits:\n",n);
/*12:*/
#line 223 "./squarepal.w"

t= (n-11)/4;
/*4:*/
#line 121 "./squarepal.w"

for(j= 1;j<=t;j++)q[j]= qq[j]= 1;

/*:4*/
#line 225 "./squarepal.w"
;
/*6:*/
#line 153 "./squarepal.w"

if(n&1){
y[(n-3)/2]= 2,r[(n-3)/2]= 0;
for(j= (n-5)/2;j>=t+2;j--)y[j]= 2*y[j+1],r[j]= 0;
}else{
y[n/2-1]= 1,r[n/2-1]= 1;
for(j= n/2-2;j>=t+2;j--){
y[j]= 2*y[j+1],r[j]= 4*r[j+1];
if(r[j]> 2*y[j])r[j]-= 2*y[j]+1,y[j]++;
}
}

/*:6*/
#line 226 "./squarepal.w"
;

/*:12*/
#line 39 "./squarepal.w"
;
for(a= 0;a<1LL<<t;a++)
/*13:*/
#line 230 "./squarepal.w"

{
sqrtxl= y[t+2];
for(p= t,bit= 1;a&bit;p--,bit<<= 1);
/*7:*/
#line 165 "./squarepal.w"

j= (n-3-p)/2;
if((n+p)&1)r[j]+= 1;
else r[j]= 4*r[j+1]+2,y[j]= 2*y[j+1];
if(r[j]> 2*y[j])r[j]-= 2*y[j]+1,y[j]++;
for(j--;j>=t+2;j--){
y[j]= 2*y[j+1],r[j]= 4*r[j+1];
if(r[j]> 2*y[j])r[j]-= 2*y[j]+1,y[j]++;
}

/*:7*/
#line 234 "./squarepal.w"
;
if(y[t+2]>=sqrtxl+4)
fprintf(stderr,"Something's wrong in case %llx!\n",
a);
for(;sqrtxl<=y[t+2];sqrtxl++){
/*9:*/
#line 205 "./squarepal.w"

if(t+2<32)pretrial[0]= (sqrtxl<<(t+2))&m32,
pretrial[1]= (sqrtxl>>(30-t))&m32;
else pretrial[0]= 0,pretrial[1]= (sqrtxl<<(t-30))&m32;
trial[2]= sqrtxl>>(62-t);

/*:9*/
#line 239 "./squarepal.w"
;
/*10:*/
#line 211 "./squarepal.w"

if(t+2<=32)trial[0]= pretrial[0]+q[t],trial[1]= pretrial[1];
else trial[0]= q[t]&m32,trial[1]= pretrial[1]+(q[t]>>32);

/*:10*/
#line 240 "./squarepal.w"
;
/*14:*/
#line 248 "./squarepal.w"

/*8:*/
#line 182 "./squarepal.w"

for(j= 0;j<3;j++){
prod= trial[j]*trial[0];
if(j)prod+= acc[j];
acc[j]= prod&m32;
prod>>= 32;
prod+= trial[j]*trial[1];
if(j)prod+= acc[j+1];
acc[j+1]= prod&m32;
prod>>= 32;
prod+= trial[j]*trial[2];
if(j)prod+= acc[j+2];
acc[j+2]= prod&m32;
acc[j+3]= prod>>32;
}

/*:8*/
#line 249 "./squarepal.w"
;
for(j= 0,k= n-1;j<k;j++,k--){
jj= ((acc[j>>5]&(1<<(j&0x1f)))!=0);
kk= ((acc[k>>5]&(1<<(k&0x1f)))!=0);
if(jj!=kk)break;
}
if(j>=k)
printf("%08llx%08llx%08llx^2=%08llx%08llx%08llx%08llx%08llx%08llx\n",
trial[2],trial[1],trial[0],
acc[5],acc[4],acc[3],acc[2],acc[1],acc[0]);

/*:14*/
#line 241 "./squarepal.w"
;
/*11:*/
#line 217 "./squarepal.w"

if(t+2<=32)trial[0]= pretrial[0]+comp(q[t]),trial[1]= pretrial[1];
else trial[0]= comp(q[t])&m32,trial[1]= pretrial[1]+(comp(q[t])>>32);

/*:11*/
#line 242 "./squarepal.w"
;
/*14:*/
#line 248 "./squarepal.w"

/*8:*/
#line 182 "./squarepal.w"

for(j= 0;j<3;j++){
prod= trial[j]*trial[0];
if(j)prod+= acc[j];
acc[j]= prod&m32;
prod>>= 32;
prod+= trial[j]*trial[1];
if(j)prod+= acc[j+1];
acc[j+1]= prod&m32;
prod>>= 32;
prod+= trial[j]*trial[2];
if(j)prod+= acc[j+2];
acc[j+2]= prod&m32;
acc[j+3]= prod>>32;
}

/*:8*/
#line 249 "./squarepal.w"
;
for(j= 0,k= n-1;j<k;j++,k--){
jj= ((acc[j>>5]&(1<<(j&0x1f)))!=0);
kk= ((acc[k>>5]&(1<<(k&0x1f)))!=0);
if(jj!=kk)break;
}
if(j>=k)
printf("%08llx%08llx%08llx^2=%08llx%08llx%08llx%08llx%08llx%08llx\n",
trial[2],trial[1],trial[0],
acc[5],acc[4],acc[3],acc[2],acc[1],acc[0]);

/*:14*/
#line 243 "./squarepal.w"
;
}
/*5:*/
#line 124 "./squarepal.w"

q[p]^= 1LL<<(p+1);
qq[p]= q[p]*q[p];
for(j= p+1;j<=t;j++){
if(qq[j-1]&(1LL<<(j+2)))q[j]= q[j-1]^(1LL<<(j+1));
else q[j]= q[j-1];
qq[j]= q[j]*q[j];
}

/*:5*/
#line 245 "./squarepal.w"

}

/*:13*/
#line 41 "./squarepal.w"
;
}

/*:1*/
