#define slack 10
#define phi 1.6180339887498948482
#define tickmax 25
#define deltamax 10
#define o ticks++
#define pausethresh 999999995 \

/*1:*/
#line 45 "./infty-queens.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
int goal;
char*a,*b,*c;
long long int maxmema,maxmemb,minmemc,maxmemc;
int ticks;
int tickhist[tickmax+1];
int deltalominint,deltalomaxint,deltahiminint,deltahimaxint;
long long deltalominfrac,deltalomaxfrac,deltahiminfrac,deltahimaxfrac;
int deltalomin[deltamax+1],deltalomax[deltamax+1],
deltahimin[deltamax+1],deltahimax[deltamax+1];
/*7:*/
#line 174 "./infty-queens.w"

int compfrac(long long x,long long y){
register int long long d= (x-y)&(y-x);
return((d&y)!=0);
}

/*:7*//*10:*/
#line 250 "./infty-queens.w"

void debug(char*m){
fprintf(stderr,"%s!\n",
m);
}
/*:10*/
#line 58 "./infty-queens.w"
;
main(int argc,char*argv[]){
register int j;
register long long k,n,q,r,s,t,nphiint,nphifrac;
/*2:*/
#line 75 "./infty-queens.w"

if(argc!=2||sscanf(argv[1],"%d",
&goal)!=1){
fprintf(stderr,"Usage: %s n\n",
argv[0]);
exit(-1);
}

/*:2*/
#line 62 "./infty-queens.w"
;
/*3:*/
#line 83 "./infty-queens.w"

maxmema= ((int)(phi*goal)+slack);
maxmemb= (maxmema+goal);
maxmemc= (maxmema-goal);
minmemc= (goal-maxmemc+2*slack);
a= (char*)calloc(maxmema,sizeof(char));
if(!a){
fprintf(stderr,"Can't allocate array a!\n");
exit(-2);
}
b= (char*)calloc(maxmemb,sizeof(char));
if(!b){
fprintf(stderr,"Can't allocate array b!\n");
exit(-2);
}
c= (char*)calloc(minmemc+maxmemc,sizeof(char));
if(!c){
fprintf(stderr,"Can't allocate array c!\n");
exit(-2);
}

/*:3*/
#line 63 "./infty-queens.w"
;
r= t= 0,s= 1;
for(n= nphiint= nphifrac= 1;n<=goal;n++){
/*4:*/
#line 108 "./infty-queens.w"

ticks= 0;
for(k= s;k<=n-r;k++){
if(k+n>=maxmemb)goto done;
if(o,b[k+n]==0){
if(k-n+minmemc<0)goto done;
if(o,c[k-n+minmemc]==0){
if(o,a[k]==0){
q= k;
o,a[k]= 1;
if(k==s)
for(s= k+1;o,a[s]==1;s++);
o,b[k+n]= 1;
o,c[k-n+minmemc]= 1;
if(k-n==-r)
for(r= n-k+1;;r++){
if(r> minmemc)goto done;
if(o,c[minmemc-r]==0)break;
}
goto got_q;
}
}
}
}
t++;
if(t>=maxmemc)goto done;
o,c[t+minmemc]= 1;
q= n+t;
if(q>=maxmema)goto done;
o,a[q]= 1;
if(q+n>=maxmemb)goto done;
o,b[q+n]= 1;
got_q:

/*:4*/
#line 66 "./infty-queens.w"
;
printf("%lld\n",
q);
/*8:*/
#line 180 "./infty-queens.w"

if(n> pausethresh)debug("watch me now");
if(ticks>=tickmax)tickhist[tickmax]++;
else tickhist[ticks]++;
if(q>=n){
if(q> nphiint){
if(q-nphiint> deltahimaxint||
(q-nphiint==deltahimaxint&&compfrac(nphifrac,deltahimaxfrac))){
deltahimaxint= q-nphiint,deltahimaxfrac= nphifrac;
fprintf(stderr,"n=%lld, deltahimax=%d,%llx\n",
n,deltahimaxint,deltahimaxfrac);
}
j= q-nphiint-1;
if(j>=deltamax)deltahimax[deltamax]++;
else deltahimax[j]++;
}else{
if(q-nphiint<deltahiminint||
(q-nphiint==deltahiminint&&compfrac(deltahiminfrac,nphifrac))){
deltahiminint= q-nphiint,deltahiminfrac= nphifrac;
fprintf(stderr,"n=%lld, deltahimin=%d,%llx\n",
n,deltahiminint,deltahiminfrac);
}
j= nphiint-q;
if(j>=deltamax)deltahimin[deltamax]++;
else deltahimin[j]++;
}
}else if(q> (nphiint-n)){
if(q-(nphiint-n)> deltalomaxint||
(q-(nphiint-n)==deltalomaxint&&compfrac(nphifrac,deltalomaxfrac))){
deltalomaxint= q-(nphiint-n),deltalomaxfrac= nphifrac;
fprintf(stderr,"n=%lld, deltalomax=%d,%llx\n",
n,deltalomaxint,deltalomaxfrac);
}
j= q-(nphiint-n)-1;
if(j>=deltamax)deltalomax[deltamax]++;
else deltalomax[j]++;
}else{
if(q-(nphiint-n)<deltalominint||
(q-(nphiint-n)==deltalominint&&compfrac(deltalominfrac,nphifrac))){
deltalominint= q-(nphiint-n),deltalominfrac= nphifrac;
fprintf(stderr,"n=%lld, deltalomin=%d,%llx\n",
n,deltalominint,deltalominfrac);
}
j= (nphiint-n)-q;
if(j>=deltamax)deltalomin[deltamax]++;
else deltalomin[j]++;
}

/*:8*/
#line 69 "./infty-queens.w"
;
/*6:*/
#line 163 "./infty-queens.w"

nphiint++;
if(nphifrac&0x3)nphiint++;
{
register long long y,z;
y= nphifrac^0xaaaaaaaaaaaaaaaa;
z= y^(y+1);
z= z|(nphifrac&(z<<1));
nphifrac^= z^((z+1)>>2);
}

/*:6*/
#line 70 "./infty-queens.w"
;
}
done:/*9:*/
#line 228 "./infty-queens.w"

fprintf(stderr,"OK, I computed %lld elements of the sequence.\n",
n-1);
fprintf(stderr,"tick histogram:");
for(j= 0;j<=tickmax;j++)fprintf(stderr," %d",
tickhist[j]);
fprintf(stderr,"\n");
fprintf(stderr,"deltalo histogram:");
for(j= deltamax;j>=0;j--)fprintf(stderr," %d",
deltalomin[j]);
fprintf(stderr," |");
for(j= 0;j<=deltamax;j++)fprintf(stderr," %d",
deltalomax[j]);
fprintf(stderr,"\n");
fprintf(stderr,"deltahi histogram:");
for(j= deltamax;j>=0;j--)fprintf(stderr," %d",
deltahimin[j]);
fprintf(stderr," |");
for(j= 0;j<=deltamax;j++)fprintf(stderr," %d",
deltahimax[j]);
fprintf(stderr,"\n");

/*:9*/
#line 72 "./infty-queens.w"
;
}

/*:1*/
