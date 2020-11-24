#define maxn 90
#define maxm 2000
#define logmemsize 27
#define memsize (1<<logmemsize) 
#define loghtsize 24
#define htsize (1<<loghtsize)  \

#define invarcs y.A \

#define trunc(addr) ((addr) &(memsize-1) )  \

/*1:*/
#line 41 "./simpath-directed-cycles.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "gb_graph.h"
#include "gb_save.h"
char mem[memsize];
unsigned long long tail,boundary,head;
unsigned int htable[htsize];
unsigned int htid;
int htcount;
int wrap= 1;
Vertex*vert[maxn+1];
int f[maxn+2],ff[maxn+2];
int s,ss;
int curfront[maxn+1],nextfront[maxn+1];
int arcto[maxm];
int firstarc[maxn+2];
char mate[maxn+3];
int serial,newserial;
/*13:*/
#line 338 "./simpath-directed-cycles.w"

void printstate(int j,int jj,int i,int k){
register int h,hh,p,t,tt,hash;
for(p= 0;p<s;p++){
t= f[p];
if(nextfront[t]!=i+1&&mate[t]&&mate[t]!=t)break;
}
if(p<s)printf("0");
else if(nextfront[j]!=i+1&&mate[j]&&mate[j]!=j)printf("0");
else if(nextfront[k]!=i+1&&mate[k]&&mate[k]!=k)printf("0");
else if(ss==0)printf("%x",
newserial);
else{
if(head+ss-tail> memsize){
fprintf(stderr,"Oops, I'm out of memory: memsize=%d, serial=%d!\n",
memsize,serial);
exit(-69);
}
/*14:*/
#line 364 "./simpath-directed-cycles.w"

for(p= 0,h= trunc(head),hash= 0;p<ss;p++,h= trunc(h+1)){
t= ff[p];
mem[h]= mate[t];
hash= hash*31415926525+mate[t];
}

/*:14*/
#line 356 "./simpath-directed-cycles.w"
;
/*15:*/
#line 374 "./simpath-directed-cycles.w"

for(hash= hash&(htsize-1);;hash= (hash+1)&(htsize-1)){
hh= htable[hash];
if((hh^htid)>=memsize)/*16:*/
#line 386 "./simpath-directed-cycles.w"

{
if(++htcount> (htsize>>1)){
fprintf(stderr,"Sorry, the hash table is full (htsize=%d, serial=%d)!\n",
htsize,serial);
exit(-96);
}
hh= trunc(head);
htable[hash]= htid+hh;
head+= ss;
goto found;
}

/*:16*/
#line 377 "./simpath-directed-cycles.w"
;
hh= trunc(hh);
for(t= hh,h= trunc(head),tt= trunc(t+ss-1);;t= trunc(t+1),h= trunc(h+1)){
if(mem[t]!=mem[h])break;
if(t==tt)goto found;
}
}
found:

/*:15*/
#line 357 "./simpath-directed-cycles.w"
;
h= trunc(hh-boundary)/ss;
printf("%x",
newserial+h);
}
}

/*:13*/
#line 61 "./simpath-directed-cycles.w"


main(int argc,char*argv[]){
register int i,j,jj,jm,k,km,l,ll,m,n,p,t,hash,sign;
register Graph*g;
register Arc*a,*b;
register Vertex*u,*v;
/*2:*/
#line 73 "./simpath-directed-cycles.w"

if(argc!=2){
fprintf(stderr,"Usage: %s foo.gb\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I can't input the graph %s (panic code %ld)!\n",
argv[1],panic_code);
exit(-2);
}
n= g->n;
if(n> maxn){
fprintf(stderr,"Sorry, that graph has %d vertices; ",n);
fprintf(stderr,"I can't handle more than %d!\n",maxn);
exit(-3);
}
if(g->m> maxm){
fprintf(stderr,"Sorry, that graph has %ld arcs; ",(g->m+1)/2);
fprintf(stderr,"I can't handle more than %d!\n",maxm);
exit(-3);
}

/*:2*/
#line 68 "./simpath-directed-cycles.w"
;
/*3:*/
#line 108 "./simpath-directed-cycles.w"

/*4:*/
#line 138 "./simpath-directed-cycles.w"

for(v= g->vertices;v<g->vertices+n;v++)v->invarcs= NULL;
for(v= g->vertices;v<g->vertices+n;v++){
vert[v-g->vertices+1]= v;
for(a= v->arcs;a;a= a->next){
register Arc*b= gb_virgin_arc();
u= a->tip;
b->tip= v;
b->len= a->len;
b->next= u->invarcs;
u->invarcs= b;
}
}

/*:4*/
#line 109 "./simpath-directed-cycles.w"
;
for(m= 0,k= 1;k<=n;k++){
firstarc[k]= m;
v= vert[k];
printf("%d(%s)\n",k,v->name);
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u> v){
arcto[m++]= u-g->vertices+1;
if(a->len==1)printf(" -> %ld(%s) #%d\n",u-g->vertices+1,u->name,m);
else printf(" -> %ld(%s,%ld) #%d\n",u-g->vertices+1,u->name,a->len,m);
}
}
for(a= v->invarcs;a;a= a->next){
u= a->tip;
if(u> v){
arcto[m++]= -(u-g->vertices+1);
if(a->len==1)printf(" <- %ld(%s) #%d\n",u-g->vertices+1,u->name,m);
else printf(" <- %ld(%s,%ld) #%d\n",u-g->vertices+1,u->name,a->len,m);
}
}
}
firstarc[k]= m;

/*:3*/
#line 69 "./simpath-directed-cycles.w"
;
/*5:*/
#line 199 "./simpath-directed-cycles.w"

for(t= 1;t<=n;t++)mate[t]= t;
/*6:*/
#line 223 "./simpath-directed-cycles.w"

jj= 1,ss= 0;
while(firstarc[jj+1]==0)jj++;
tail= head= 0;
serial= 2;

/*:6*/
#line 201 "./simpath-directed-cycles.w"
;
for(i= 0;i<m;i++){
printf("#%d:\n",i+1);
fprintf(stderr,"Beginning arc %d (serial=%d,head-tail=%lld)\n",
i+1,serial,head-tail);
fflush(stderr);
/*7:*/
#line 234 "./simpath-directed-cycles.w"

if(ss==0)head++;
boundary= head,htcount= 0,htid= (i+wrap)<<logmemsize;
if(htid==0){
for(hash= 0;hash<htsize;hash++)htable[hash]= 0;
wrap++,htid= 1<<logmemsize;
}
newserial= serial+(head-tail)/(ss?ss:1);
j= jj,sign= arcto[i],k= (sign> 0?sign:-sign),s= ss;
for(p= 0;p<s;p++)f[p]= ff[p];
/*8:*/
#line 259 "./simpath-directed-cycles.w"

while(jj<=n&&firstarc[jj+1]==i+1)jj++;
for(p= ss= 0;p<s;p++){
t= f[p];
curfront[t]= i+1;
if(t>=jj){
nextfront[t]= i+1;
ff[ss++]= t;
}
}
if(j==jj&&nextfront[j]!=i+1)nextfront[j]= i+1,ff[ss++]= j;
if(k>=jj&&nextfront[k]!=i+1)nextfront[k]= i+1,ff[ss++]= k;

/*:8*/
#line 244 "./simpath-directed-cycles.w"
;
while(tail<boundary){
printf("%x:",serial);
serial++;
/*9:*/
#line 275 "./simpath-directed-cycles.w"

if(s==0)tail++;
else{
for(p= 0;p<s;p++,tail++){
t= f[p];
mate[t]= mem[trunc(tail)];
}
}
if(curfront[j]!=i+1)mate[j]= j;
if(curfront[k]!=i+1)mate[k]= k;

/*:9*/
#line 248 "./simpath-directed-cycles.w"
;
/*11:*/
#line 314 "./simpath-directed-cycles.w"

printstate(j,jj,i,k);

/*:11*/
#line 249 "./simpath-directed-cycles.w"
;
printf(",");
/*10:*/
#line 289 "./simpath-directed-cycles.w"

if(sign> 0){
jm= mate[j],km= mate[k];
if(jm==j)jm= -j;
if(jm>=0||km<=0)printf("0");
else if(jm==-k)
/*12:*/
#line 320 "./simpath-directed-cycles.w"

{
for(p= 0;p<s;p++){
t= f[p];
if(t!=j&&t!=k&&mate[t]&&mate[t]!=t)break;
}
if(p==s)printf("1");
else printf("0");
}

/*:12*/
#line 295 "./simpath-directed-cycles.w"

else{
mate[j]= 0,mate[k]= 0;
mate[-jm]= km,mate[km]= jm;
printstate(j,jj,i,k);
}
}else{
jm= mate[j],km= mate[k];
if(km==k)km= -k;
if(jm<=0||km>=0)printf("0");
else if(km==-j)
/*12:*/
#line 320 "./simpath-directed-cycles.w"

{
for(p= 0;p<s;p++){
t= f[p];
if(t!=j&&t!=k&&mate[t]&&mate[t]!=t)break;
}
if(p==s)printf("1");
else printf("0");
}

/*:12*/
#line 306 "./simpath-directed-cycles.w"

else{
mate[j]= 0,mate[k]= 0;
mate[jm]= km,mate[-km]= jm;
printstate(j,jj,i,k);
}
}

/*:10*/
#line 251 "./simpath-directed-cycles.w"
;
printf("\n");
}

/*:7*/
#line 207 "./simpath-directed-cycles.w"
;
}
printf("%x:0,0\n",
serial);

/*:5*/
#line 70 "./simpath-directed-cycles.w"
;
}

/*:1*/
