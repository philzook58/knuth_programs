#define maxn 255
#define maxm 2000
#define logmemsize 27
#define memsize (1<<logmemsize) 
#define loghtsize 25
#define htsize (1<<loghtsize)  \

#define num z.I \

#define trunc(addr) ((addr) &(memsize-1) )  \

/*1:*/
#line 24 "./simpath.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "gb_graph.h"
#include "gb_save.h"
unsigned char mem[memsize];
unsigned long long tail,boundary,head;
unsigned int htable[htsize];
unsigned int htid;
int htcount;
int wrap= 1;
Vertex*vert[maxn+1];
int arcto[maxm];
int firstarc[maxn+2];
unsigned char mate[maxn+3];
int serial,newserial;
/*13:*/
#line 313 "./simpath.w"

void printstate(int j,int jj,int ll){
register int h,hh,ss,t,tt,hash;
for(t= j;t<jj;t++)
if(mate[t]&&mate[t]!=t)break;
if(t<jj)printf("0");
else if(ll<jj)printf("0");
else{
ss= ll+1-jj;
if(head+ss-tail> memsize){
fprintf(stderr,"Oops, I'm out of memory (memsize=%d, serial=%d)!\n",
memsize,serial);
fflush(stdout);
exit(-69);
}
/*14:*/
#line 335 "./simpath.w"

for(t= jj,h= trunc(head),hash= 0;t<=ll;t++,h= trunc(h+1)){
mem[h]= mate[t];
hash= hash*31415926525+mate[t];
}

/*:14*/
#line 328 "./simpath.w"
;
/*15:*/
#line 344 "./simpath.w"

for(hash= hash&(htsize-1);;hash= (hash+1)&(htsize-1)){
hh= htable[hash];
if((hh^htid)>=memsize)/*16:*/
#line 356 "./simpath.w"

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
#line 347 "./simpath.w"
;
hh= trunc(hh);
for(t= hh,h= trunc(head),tt= trunc(t+ss-1);;t= trunc(t+1),h= trunc(h+1)){
if(mem[t]!=mem[h])break;
if(t==tt)goto found;
}
}
found:

/*:15*/
#line 329 "./simpath.w"
;
h= trunc(hh-boundary)/ss;
printf("%x",newserial+h);
}
}

/*:13*/
#line 41 "./simpath.w"


main(int argc,char*argv[]){
register int i,j,jj,jm,k,km,l,ll,m,n,t,hash;
register Graph*g;
register Arc*a,*b;
register Vertex*u,*v;
Vertex*source= NULL,*target= NULL;
/*2:*/
#line 55 "./simpath.w"

if(argc!=4){
fprintf(stderr,"Usage: %s foo.gb source target\n",argv[0]);
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
if(g->m> 2*maxm){
fprintf(stderr,"Sorry, that graph has %ld edges; ",(g->m+1)/2);
fprintf(stderr,"I can't handle more than %d!\n",maxm);
exit(-3);
}
for(v= g->vertices;v<g->vertices+n;v++){
if(strcmp(argv[2],v->name)==0)source= v;
if(strcmp(argv[3],v->name)==0)target= v;
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u==v){
fprintf(stderr,"Sorry, the graph contains a loop %s--%s!\n",
v->name,v->name);
exit(-4);
}
b= (v<u?a+1:a-1);
if(b->tip!=v){
fprintf(stderr,"Sorry, the graph isn't undirected!\n");
fprintf(stderr,"(%s->%s has mate pointing to %s)\n",
v->name,u->name,b->tip->name);
exit(-5);
}
}
}
if(!source){
fprintf(stderr,"I can't find source vertex %s in the graph!\n",argv[2]);
exit(-6);
}
if(!target){
fprintf(stderr,"I can't find target vertex %s in the graph!\n",argv[3]);
exit(-7);
}

/*:2*/
#line 49 "./simpath.w"
;
/*3:*/
#line 115 "./simpath.w"

if(source==g->vertices){
for(k= 0;k<n;k++)(g->vertices+k)->num= k+1,vert[k+1]= g->vertices+k;
}else{
for(k= 0;k<n;k++)(g->vertices+k)->num= 0;
vert[1]= source,source->num= 1;
for(j= 0,k= 1;j<k;j++){
v= vert[j+1];
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u->num==0)u->num= ++k,vert[k]= u;
}
}
if(target->num==0){
fprintf(stderr,"Sorry, there's no path from %s to %s in the graph!\n",
argv[2],argv[3]);
exit(-8);
}
if(k<n){
fprintf(stderr,"The graph isn't connected (%d<%d)!\n",k,n);
fprintf(stderr,"But that's OK; I'll work with the component of %s.\n",
argv[2]);
n= k;
}
}

/*:3*/
#line 50 "./simpath.w"
;
/*4:*/
#line 152 "./simpath.w"

for(m= 0,k= 1;k<=n;k++){
firstarc[k]= m;
v= vert[k];
printf("%ld(%s)\n",v->num,v->name);
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u->num> k){
arcto[m++]= u->num;
if(a->len==1)printf(" -> %ld(%s) #%d\n",u->num,u->name,m);
else printf(" -> %ld(%s,%ld) #%d\n",u->num,u->name,a->len,m);
}
}
}
firstarc[k]= m;

/*:4*/
#line 51 "./simpath.w"
;
/*5:*/
#line 216 "./simpath.w"

/*6:*/
#line 227 "./simpath.w"

for(t= 2;t<=n;t++)mate[t]= t;
mate[target->num]= 1,mate[1]= target->num;

/*:6*/
#line 217 "./simpath.w"
;
/*7:*/
#line 231 "./simpath.w"

jj= ll= 1;
mem[0]= mate[1];
tail= 0,head= 1;
serial= 2;

/*:7*/
#line 218 "./simpath.w"
;
for(i= 0;i<m;i++){
printf("#%d:\n",i+1);
fprintf(stderr,"Beginning arc %d (serial=%d,head-tail=%lld)\n",
i+1,serial,head-tail);
fflush(stderr);
/*8:*/
#line 247 "./simpath.w"

boundary= head,htcount= 0,htid= (i+wrap)<<logmemsize;
if(htid==0){
for(hash= 0;hash<htsize;hash++)htable[hash]= 0;
wrap++,htid= 1<<logmemsize;
}
newserial= serial+((head-tail)/(ll+1-jj));
j= jj,k= arcto[i],l= ll;
while(jj<=n&&firstarc[jj+1]==i+1)jj++;
ll= (k> l?k:l);
while(tail<boundary){
printf("%x:",serial);
serial++;
/*9:*/
#line 270 "./simpath.w"

for(t= j;t<=l;t++,tail++){
mate[t]= mem[trunc(tail)];
if(mate[t]> l)mate[mate[t]]= t;
}

/*:9*/
#line 260 "./simpath.w"
;
/*11:*/
#line 290 "./simpath.w"

printstate(j,jj,ll);

/*:11*/
#line 261 "./simpath.w"
;
printf(",");
/*10:*/
#line 279 "./simpath.w"

jm= mate[j],km= mate[k];
if(jm==0||km==0)printf("0");
else if(jm==k)/*12:*/
#line 296 "./simpath.w"

{
for(t= j+1;t<=ll;t++)if(t!=k){
if(mate[t]&&mate[t]!=t)break;
}
if(t> ll)printf("1");
else printf("0");
}

/*:12*/
#line 282 "./simpath.w"

else{
mate[j]= 0,mate[k]= 0;
mate[jm]= km,mate[km]= jm;
printstate(j,jj,ll);
}
done:

/*:10*/
#line 263 "./simpath.w"
;
printf("\n");
}

/*:8*/
#line 224 "./simpath.w"
;
}

/*:5*/
#line 52 "./simpath.w"
;
}

/*:1*/
