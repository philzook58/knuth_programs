#define del 100000000LL
#define kmax 10000 \

/*2:*/
#line 61 "./prime-sieve.w"

#include <stdio.h> 
#include <stdlib.h> 
FILE*infile,*outfile;
unsigned int prime[kmax];
unsigned int start[kmax];
unsigned long long sieve[2+del/128];
unsigned long long s0;
int tt;
unsigned long long st;
unsigned long long lastprime;
int bestgap= 256;
unsigned long long sv[11];
int rem[11];
char nu[0x10000];

main(int argc,char*argv[])
{
register j,k;
unsigned long long x,y,z,s,ss;
int d,ii,kk;
/*17:*/
#line 307 "./prime-sieve.w"

for(j= 0;j<=16;j++)nu[((1<<j)-1)]= j;

/*:17*/
#line 82 "./prime-sieve.w"
;
/*3:*/
#line 89 "./prime-sieve.w"

if(argc!=5||sscanf(argv[1],"%llu",&s0)!=1||
sscanf(argv[2],"%d",&tt)!=1){
fprintf(stderr,"Usage: %s s[0] t inputfile outputfile\n",argv[0]);
exit(-1);
}
infile= fopen(argv[3],"rb");
if(!infile){
fprintf(stderr,"I can't open %s for binary input!\n",argv[3]);
exit(-2);
}
outfile= fopen(argv[4],"w");
if(!outfile){
fprintf(stderr,"I can't open %s for text output!\n",argv[4]);
exit(-3);
}
st= s0+tt*del;
if(del%128){
fprintf(stderr,"Oops: The sieve size %d isn't a multiple of 128!\n",del);
exit(-4);
}
if(s0&1){
fprintf(stderr,"The starting point %llu isn't even!\n",s0);
exit(-5);
}
if(s0*s0<del){
fprintf(stderr,"The starting point %llu is less than sqrt(%llu)!\n",s0,del);
exit(-6);
}
/*4:*/
#line 121 "./prime-sieve.w"

for(k= 0;;k++){
if(k>=kmax){
fprintf(stderr,"Oops: Please recompile me with kmax>%d!\n",kmax);
exit(-7);
}
if(fread(&prime[k],sizeof(unsigned int),1,infile)!=1){
fprintf(stderr,"The input file ended prematurely (%d^2<%llu)!\n",
k?prime[k-1]:0,st);
exit(-8);
}
if(k==0&&prime[0]!=2){
fprintf(stderr,"The input file begins with %d, not 2!\n",prime[0]);
exit(-9);
}else if(k> 0&&prime[k]<=prime[k-1]){
fprintf(stderr,"The input file has consecutive entries %d,%d!\n",
prime[k-1],prime[k]);
exit(-10);
}
if(((unsigned long long)prime[k])*prime[k]> st)break;
}
printf("%d primes successfully loaded from %s\n",k,argv[3]);

/*:4*/
#line 118 "./prime-sieve.w"
;
printf("Sieving between s[0]=%llu and s[t]=%llu:\n",s0,st);

/*:3*/
#line 83 "./prime-sieve.w"
;
/*7:*/
#line 177 "./prime-sieve.w"

/*5:*/
#line 157 "./prime-sieve.w"

for(k= 1;((unsigned long long)prime[k])*prime[k]<s0;k++){
j= s0%prime[k];
if(j&1)start[k]= prime[k]-((j+1)>>1);
else start[k]= (prime[k]-j-1)>>1;
}
kk= k;
/*6:*/
#line 170 "./prime-sieve.w"

for(k= 1;prime[k]<32&&k<kk;k++){
for(x= 0,y= 1LL<<start[k];x!=y;x= y,y|= y<<prime[k]);
sv[k]= x,rem[k]= 64%prime[k];
}
d= k;

/*:6*/
#line 164 "./prime-sieve.w"
;

/*:5*/
#line 178 "./prime-sieve.w"
;
ss= s0;
sieve[1+del/128]= -1;

/*:7*/
#line 84 "./prime-sieve.w"
;
for(ii= 0;ii<tt;ii++)/*8:*/
#line 182 "./prime-sieve.w"

{
s= ss,ss= s+del;
printf("Beginning segment %llu\n",s);
/*9:*/
#line 192 "./prime-sieve.w"

for(j= 0;j<del/128;j++){
for(z= 0,k= 1;k<d;k++){
z|= sv[k];
sv[k]= (sv[k]<<(prime[k]-rem[k]))|(sv[k]>>rem[k]);
}
sieve[j]= z;
}

/*:9*/
#line 186 "./prime-sieve.w"
;
/*10:*/
#line 206 "./prime-sieve.w"

for(k= d;k<kk;k++){
for(j= start[k];j<del/2;j+= prime[k])sieve[j>>6]|= 1LL<<(j&0x3f);
start[k]= j-del/2;
}

/*:10*/
#line 187 "./prime-sieve.w"
;
/*11:*/
#line 212 "./prime-sieve.w"

while(((unsigned long long)prime[k])*prime[k]<ss){
for(j= (((unsigned long long)prime[k])*prime[k]-s-1)>>1;j<del/2;j+= prime[k])
sieve[j>>6]|= 1LL<<(j&0x3f);
start[k]= j-del/2;
k++;
}
kk= k;

/*:11*/
#line 188 "./prime-sieve.w"
;
/*12:*/
#line 235 "./prime-sieve.w"

j= 0;
/*13:*/
#line 261 "./prime-sieve.w"

if(lastprime<=s-128||sieve[j]==-1){
for(;sieve[j]==-1;j++);
if(j==del/128)goto donewithseg;
y= ~sieve[j];
y= y&-y;
/*16:*/
#line 300 "./prime-sieve.w"

y--;
y= nu[y&0xffff]+nu[(y>>16)&0xffff]+nu[(y>>32)&0xffff]+nu[(y>>48)&0xffff];

/*:16*/
#line 267 "./prime-sieve.w"
;
x= s+(j<<7)+y+y+1;
if(lastprime)/*18:*/
#line 310 "./prime-sieve.w"

{
if(x-lastprime>=bestgap){
bestgap= x-lastprime;
fprintf(outfile,"%llu is followed by a gap of length %d\n",
lastprime,bestgap);
fflush(outfile);
}
}

/*:18*/
#line 269 "./prime-sieve.w"

else{
k= x-s0;
fprintf(outfile,"The first prime is %llu = s[0]+%d\n",x,k);
fflush(outfile);
}
}

/*:13*/
#line 237 "./prime-sieve.w"
;
while(1){
for(j++;sieve[j]!=-1;j++);
if(j<del/128){
k= j-1;
for(j++;sieve[j]==-1;j++);
if(j==del/128)break;
/*14:*/
#line 281 "./prime-sieve.w"

if(((j-k)<<7)+126>=bestgap){
y= ~sieve[j];
y= y&-y;
/*16:*/
#line 300 "./prime-sieve.w"

y--;
y= nu[y&0xffff]+nu[(y>>16)&0xffff]+nu[(y>>32)&0xffff]+nu[(y>>48)&0xffff];

/*:16*/
#line 285 "./prime-sieve.w"
;
x= s+(j<<7)+y+y+1;
/*15:*/
#line 291 "./prime-sieve.w"

for(y= ~sieve[k],z= y&(y-1);z;y= z,z= y&(y-1));
/*16:*/
#line 300 "./prime-sieve.w"

y--;
y= nu[y&0xffff]+nu[(y>>16)&0xffff]+nu[(y>>32)&0xffff]+nu[(y>>48)&0xffff];

/*:16*/
#line 293 "./prime-sieve.w"
;
lastprime= s+(k<<7)+y+y+1;

/*:15*/
#line 287 "./prime-sieve.w"
;
/*18:*/
#line 310 "./prime-sieve.w"

{
if(x-lastprime>=bestgap){
bestgap= x-lastprime;
fprintf(outfile,"%llu is followed by a gap of length %d\n",
lastprime,bestgap);
fflush(outfile);
}
}

/*:18*/
#line 288 "./prime-sieve.w"
;
}

/*:14*/
#line 244 "./prime-sieve.w"
;
}else{
k= del/128-1;break;
}
}
/*15:*/
#line 291 "./prime-sieve.w"

for(y= ~sieve[k],z= y&(y-1);z;y= z,z= y&(y-1));
/*16:*/
#line 300 "./prime-sieve.w"

y--;
y= nu[y&0xffff]+nu[(y>>16)&0xffff]+nu[(y>>32)&0xffff]+nu[(y>>48)&0xffff];

/*:16*/
#line 293 "./prime-sieve.w"
;
lastprime= s+(k<<7)+y+y+1;

/*:15*/
#line 249 "./prime-sieve.w"
;
donewithseg:

/*:12*/
#line 189 "./prime-sieve.w"
;
}

/*:8*/
#line 85 "./prime-sieve.w"
;
/*19:*/
#line 320 "./prime-sieve.w"

if(lastprime){
k= st-lastprime;
fprintf(outfile,"The final prime is %llu = s[t]-%d.\n",lastprime,k);
}else fprintf(outfile,"No prime numbers exist between s[0] and s[t].\n");

/*:19*/
#line 86 "./prime-sieve.w"
;
}

/*:2*/
