#define file_given (argc==2)  \

#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define oooo mems+= 4
#define rfactor 4.0
#define zfactor 1.0 \

#define addr_(p) ((addr) (size_t) (p) )  \

#define logpagesize 12
#define memsize (1<<29)  \

#define pagesize (1<<logpagesize) 
#define pagemask (pagesize-1) 
#define pageints (pagesize/sizeof(int) ) 
#define node_(a) ((node*) (size_t) (a) ) 
#define page_(a) ((page*) (size_t) (a) )  \

#define topofmem ((page*) &mem[memsize])  \

#define logmaxhashsize 21
#define slotsperpage (pagesize/sizeof(addr) ) 
#define maxhashpages (((1<<logmaxhashsize) +slotsperpage-1) /slotsperpage)  \

#define logvarsize 10
#define varsize (1<<logvarsize) 
#define varpart(x) ((x) >>(32-logvarsize) ) 
#define initnewnode(p,v,l,h) oo,p->lo= addr_(l) ,p->hi= addr_(h) ,p->xref= 0, \
oooo,p->index= ((v) <<(32-logvarsize) ) +(gb_next_rand() >>(logvarsize-1) )  \

#define topofvars &varhead[totvars] \

#define tautology node_(varhead[0].taut)  \

#define hashcode(l,h) ((addr*) (size_t) (oo,((l) ->index<<3) ^((h) ->index<<2) ) ) 
#define hashedcode(p) hashcode(node_(p->lo) ,node_(p->hi) ) 
#define addr__(x) (*((addr*) (size_t) (x) ) ) 
#define fetchnode(v,k) node_(addr__(v->base[(k) >>logpagesize]+((k) &pagemask) ) ) 
#define storenode(v,k,p) o,addr__(v->base[(k) >>logpagesize]+((k) &pagemask) ) = addr_(p)  \

#define storenulls(k) *(long long*) (size_t) (k) = 0LL; \

#define timerinterval 1024
#define deadfraction 8 \

#define maxmask ((1<<logmaxhashsize) *sizeof(addr) -1)  \
 \

#define memo_(a) ((memo*) (size_t) (a) )  \

#define logmaxcachepages 15
#define maxcachepages (1<<logmaxcachepages) 
#define cacheslotsperpage (pagesize/sizeof(memo) ) 
#define maxbinop 15 \

#define id(a) (((size_t) (a) -(size_t) mem) /sizeof(node) )  \

#define cachehash(f,g,h)  \
((f) ->index<<4) ^(((h) ?(g) ->index:addr_(g) ) <<5) ^(addr_(h) <<6) 
#define thememo(s) memo_(cachepage[((s) &cachemask) >>logpagesize]+((s) &pagemask) )  \

#define extsize 10000 \

#define thevar(p) (&varhead[varpart((p) ->index) ]) 
#define print_node(p)  \
printf("%x: (~%d?%x:%x)",id(p) ,thevar(p) ->name,id((p) ->lo) ,id((p) ->hi) )  \

#define includesanity 1 \

#define ghost(p) node_((size_t) (p) -(size_t) mem+(size_t) smem)  \

#define complain(complaint)  \
{printf("! %s in node ",complaint) ; \
print_node(p) ;printf("\n") ;}
#define legit(p) (((size_t) (p) &(sizeof(node) -1) ) ==0&&(p) <nodeptr&& \
(p) >=botsink&&ghost(p) ->xref!=-1) 
#define superlegit(p) (((size_t) (p) &(sizeof(node) -1) ) ==0&&(p) <nodeptr&& \
(p) > topsink&&ghost(p) ->xref!=-1)  \

#define badpage(p) ((p) <pageptr||(p) >=topofmem)  \

#define deref(p) if(o,(p) ->xref==0) recursively_kill(p) ;else o,(p) ->xref-- \

#define debugging 1 \

#define bufsize 100 \

#define getk for(k= 0;isdigit(*c) ;c++) k= 10*k+*c-'0'
#define reporterror {printf("Sorry; `%c' confuses me %s%s", \
*(c-1) ,infile?"in this command: ":"in that command.",infile?buf:"\n") ; \
goto nextcommand;} \

#define passblanks for(;*c==' ';c++)  \

#define getkf  \
getk;if(k>=extsize) {printf("f%d is out of range.\n",k) ;continue;}
#define getkv  \
getk;if(k>=totvars) {printf("x%d is out of range.\n",k) ;continue;} \

#define checknull(p) if(!p) {printf("f%d is null!\n",k) ;continue;} \
 \

/*3:*/
#line 102 "./bdd15.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include "gb_flip.h" 
#define verbose Verbose 
/*11:*/
#line 228 "./bdd15.w"

typedef unsigned int addr;

/*:11*//*12:*/
#line 261 "./bdd15.w"

typedef struct node_struct{
addr lo,hi;
int xref;
unsigned int index;
}node;
typedef struct page_struct{
addr dat[pageints];
}page;

/*:12*//*20:*/
#line 414 "./bdd15.w"

typedef struct var_struct{
addr proj;
addr taut;
addr elt;
int free;
int mask;
addr base[maxhashpages];
int name;
int aux;
struct var_struct*up,*down;
}var;

/*:20*//*40:*/
#line 869 "./bdd15.w"

typedef struct memo_struct{
addr f;
addr g;
addr h;
addr r;
}memo;

/*:40*/
#line 108 "./bdd15.w"

/*5:*/
#line 131 "./bdd15.w"

FILE*infile;
int verbose= -1;

/*:5*//*9:*/
#line 183 "./bdd15.w"

unsigned long long mems,rmems,zmems;

/*:9*//*14:*/
#line 293 "./bdd15.w"

char mem[memsize];
node*nodeptr;
page*pageptr;
node*nodeavail;
page*pageavail;
node*botsink,*topsink;
int totalnodes;
int deadnodes;
int leasesonlife= 1;

/*:14*//*22:*/
#line 453 "./bdd15.w"

var varhead[varsize];
var*tvar= &varhead[varsize];
int varmap[varsize];
int totvars;

/*:22*//*31:*/
#line 644 "./bdd15.w"

unsigned long long timer;

/*:31*//*41:*/
#line 891 "./bdd15.w"

addr cachepage[maxcachepages];
int cachepages;
int cacheinserts;
int threshold;
int cachemask;

/*:41*//*43:*/
#line 925 "./bdd15.w"

char*binopname[]= 
{"+","&",">","!","<","*","^","|","\"","/","%","_",":","$",";",","};
char*ternopname1[]= 
{"?",".","&","!","@","#","$","%","*","<","-","+","|","/","\\","~"};
char*ternopname2[]= 
{":",".","&",":","@","#","$","%","*","<","-","+","|","/","\\","~"};

/*:43*//*52:*/
#line 1128 "./bdd15.w"

node*f[extsize];

/*:52*//*60:*/
#line 1295 "./bdd15.w"

#if includesanity
char smem[memsize];
#endif

/*:60*//*110:*/
#line 2525 "./bdd15.w"

char buf[bufsize];

/*:110*//*130:*/
#line 2834 "./bdd15.w"

int totalvars;
var*firstvar;
int oldleases;

/*:130*//*134:*/
#line 2970 "./bdd15.w"

addr savebase[maxhashpages];

/*:134*//*152:*/
#line 3277 "./bdd15.w"

double trigger;
int toobig= memsize;

/*:152*//*155:*/
#line 3315 "./bdd15.w"

int last_ditch;

/*:155*//*158:*/
#line 3341 "./bdd15.w"

FILE*outfile;
int outcount;

/*:158*/
#line 109 "./bdd15.w"

/*26:*/
#line 532 "./bdd15.w"

node*unique_find(var*v,node*l,node*h);
node*symfunc(node*p,var*v,int k);

/*:26*//*28:*/
#line 601 "./bdd15.w"

void recursively_revive(node*p);
void recursively_kill(node*p);
void collect_garbage(int level);

/*:28*//*106:*/
#line 2447 "./bdd15.w"

void attempt_repairs(void);

/*:106*/
#line 110 "./bdd15.w"

/*8:*/
#line 166 "./bdd15.w"

void show_stats(void){
printf("stats: %d/%d nodes, %d dead, %d pages,",
totalnodes,nodeptr-botsink,deadnodes,topofmem-pageptr);
printf(" %llu mems, %llu rmems, %llu zmems, %.4g\n",
mems,rmems,zmems,mems+rfactor*rmems+zfactor*zmems);
}

/*:8*//*15:*/
#line 312 "./bdd15.w"

node*reserve_node(void){
register node*r= nodeavail;
if(r)o,nodeavail= node_(nodeavail->xref);
else{
r= nodeptr;
if(r<(node*)pageptr)nodeptr++;
else{
leasesonlife--;
fprintf(stderr,"NULL node forced (%d pages, %d nodes, %d dead)\n",
topofmem-pageptr,nodeptr-botsink,deadnodes);
fprintf(stderr,"(I will try %d more times)\n",leasesonlife);
if(leasesonlife==0){
show_stats();exit(-98);
}
return NULL;
}
}
totalnodes++;
return r;
}

/*:15*//*16:*/
#line 337 "./bdd15.w"

void free_node(register node*p){
o,p->xref= addr_(nodeavail);
nodeavail= p;
totalnodes--;
}

/*:16*//*17:*/
#line 347 "./bdd15.w"

page*reserve_page(void){
register page*r= pageavail;
if(r)o,pageavail= page_(pageavail->dat[0]);
else{
r= pageptr-1;
if((node*)r>=nodeptr)pageptr= r;
else{
leasesonlife--;
fprintf(stderr,"NULL page forced (%d pages, %d nodes, %d dead)\n",
topofmem-pageptr,nodeptr-botsink,deadnodes);
fprintf(stderr,"(I will try %d more times)\n",leasesonlife);
if(leasesonlife==0){
show_stats();exit(-97);
}
return NULL;
}
}
return r;
}

void free_page(register page*p){
o,p->dat[0]= addr_(pageavail);
pageavail= p;
}

/*:17*//*23:*/
#line 462 "./bdd15.w"

void createvars(int v){
register node*p,*q,*r;
register var*hv= &varhead[v];
register int j,k;
if(!totvars)/*24:*/
#line 477 "./bdd15.w"

{
if(v+1>=varsize){
printf("Sorry, x%d is as high as I can go!\n",varsize-2);
exit(-4);
}
totvars= v+1;
o,oooo,botsink->index= (totvars<<(32-logvarsize))+
(gb_next_rand()>>(logvarsize-1));
o,oooo,topsink->index= (totvars<<(32-logvarsize))+
(gb_next_rand()>>(logvarsize-1));
for(k= 0;k<=v;k++){
o,varhead[k].base[0]= addr_(reserve_page());

/*29:*/
#line 611 "./bdd15.w"

o,varhead[k].free= 2,varhead[k].mask= 7;
storenulls(varhead[k].base[0]);
zmems++;

/*:29*/
#line 491 "./bdd15.w"
;
}
o,(topofvars)->taut= addr_(topsink);
for(p= topsink,k= v;k>=0;p= r,k--){
r= unique_find(&varhead[k],p,p);
oo,p->xref+= 2;
varhead[k].taut= addr_(r);
p= unique_find(&varhead[k],botsink,topsink);
oooo,botsink->xref++,topsink->xref++;
o,varhead[k].elt= addr_(p);
if(verbose&2)printf(" %x=t%d, %x=e%d\n",id(r),k,id(p),k);
if(k!=0)oo,r->xref--;
oo,varhead[k].name= k,varmap[k]= k;
}
leasesonlife= 10;
}

/*:24*/
#line 467 "./bdd15.w"
;
}

/*:23*//*25:*/
#line 516 "./bdd15.w"

node*projection(int v){
register node*p,*q,*r;
register var*hv= &varhead[v];
register int j,k;
if(!hv->proj){
hv->proj= addr_(symfunc(node_(hv->elt),varhead,1));
if(verbose&2)printf(" %x=x%d\n",id(hv->proj),v);
}
return o,node_(hv->proj);
}

/*:25*//*27:*/
#line 576 "./bdd15.w"

node*unique_find(var*v,node*l,node*h){
register int j,k,mask,free;
register addr*hash;
register node*p,*r;
if(h==botsink){
return oo,h->xref--,l;
}
restart:o,mask= v->mask,free= v->free;
for(hash= hashcode(l,h);;hash++){
k= addr_(hash)&mask;
oo,p= fetchnode(v,k);
if(!p)goto newnode;
if(node_(p->lo)==l&&node_(p->hi)==h)break;
}
if(o,p->xref<0){
deadnodes--,o,p->xref= 0;
return p;
}
oooo,l->xref--,h->xref--;
return o,p->xref++,p;
newnode:/*30:*/
#line 636 "./bdd15.w"

if((++timer%timerinterval)==0){
if(deadnodes> totalnodes/deadfraction){
collect_garbage(0);
goto restart;
}
}

/*:30*/
#line 597 "./bdd15.w"
;
/*32:*/
#line 649 "./bdd15.w"

p= reserve_node();
if(!p)goto cramped;
if(--free<=mask>>4){
free_node(p);
/*33:*/
#line 667 "./bdd15.w"

{
register int newmask= mask+mask+1,kk= newmask>>logpagesize;
if(verbose&256)
printf("doubling the hash table for level %d(x%d) (%d slots)\n",
v-varhead,v->name,(newmask+1)/sizeof(addr));
if(kk)/*34:*/
#line 688 "./bdd15.w"

{
if(newmask> maxmask){
if(verbose&(2+256+512))
printf("profile limit reached for level %d(x%d)\n",v-varhead,v->name);
goto cramped;
}
for(k= (mask>>logpagesize)+1;k<=kk;k++){
o,v->base[k]= addr_(reserve_page());
if(!v->base[k]){
for(k--;k> mask>>logpagesize;k--){
o,free_page(page_(v->base[k]));
}
goto cramped;
}
for(j= v->base[k];j<v->base[k]+pagesize;j+= sizeof(long long))
storenulls(j);
zmems+= pagesize/sizeof(long long);
}
}

/*:34*/
#line 673 "./bdd15.w"

else{
for(k= v->base[0]+mask+1;k<v->base[0]+newmask;k+= sizeof(long long))
storenulls(k);
zmems+= (newmask-mask)/sizeof(long long);
}
/*35:*/
#line 722 "./bdd15.w"

for(k= 0;k<newmask;k+= sizeof(addr)){
oo,r= fetchnode(v,k);
if(r){
storenode(v,k,NULL);
for(o,hash= hashedcode(r);;hash++){
j= addr_(hash)&newmask;
oo,p= fetchnode(v,j);
if(!p)break;
}
storenode(v,j,r);
}else if(k> mask)break;
}

/*:35*/
#line 679 "./bdd15.w"
;
v->mask= newmask;
v->free= free+1+(newmask-mask)/sizeof(addr);
goto restart;
}

/*:33*/
#line 654 "./bdd15.w"
;
}
storenode(v,k,p);o,v->free= free;
initnewnode(p,v-varhead,l,h);
return p;
cramped:
deref(l);
deref(h);
return NULL;

/*:32*/
#line 598 "./bdd15.w"
;
}

/*:27*//*36:*/
#line 741 "./bdd15.w"

void table_purge(var*v){
register int free,i,j,jj,k,kk,mask,newmask,oldtotal;
register node*p,*r;
register addr*hash;
o,mask= v->mask,free= v->free;
oldtotal= totalnodes;
for(k= 0;k<mask;k+= sizeof(addr)){
oo,p= fetchnode(v,k);
if(p&&p->xref<0){
free_node(p);
/*37:*/
#line 767 "./bdd15.w"

do{
for(kk= k,j= k+sizeof(addr),k= 0;;j+= sizeof(addr)){
jj= j&mask;
oo,p= fetchnode(v,jj);
if(!p)break;
if(p->xref>=0){
o,i= addr_(hashedcode(p))&mask;
if((i<=kk)+(jj<i)+(kk<jj)> 1)storenode(v,kk,p),kk= jj;
}else if(!k)
k= j,free_node(p);
}
storenode(v,kk,NULL);
}while(k);
k= j;

/*:37*/
#line 752 "./bdd15.w"
;
}
}
deadnodes-= oldtotal-totalnodes,free+= oldtotal-totalnodes;
/*38:*/
#line 785 "./bdd15.w"

k= (mask>>2)+1-free;
for(newmask= mask;(newmask>>5)>=k;newmask>>= 1);
if(newmask!=mask){
if(verbose&256)
printf("downsizing the hash table for level %d(x%d) (%d slots)\n",
v-varhead,v->name,(newmask+1)/sizeof(addr));
free-= (mask-newmask)>>2;
/*39:*/
#line 805 "./bdd15.w"

for(k= newmask+1;k<mask;k+= sizeof(addr)){
oo,r= fetchnode(v,k);
if(r){
for(o,hash= hashedcode(r);;hash++){
j= addr_(hash)&newmask;
oo,p= fetchnode(v,j);
if(!p)break;
}
storenode(v,j,r);
}
}

/*:39*/
#line 793 "./bdd15.w"
;
for(k= mask>>logpagesize;k> newmask>>logpagesize;k--)
o,free_page(page_(v->base[k]));
v->mask= newmask;
}

/*:38*/
#line 756 "./bdd15.w"
;
o,v->free= free;
}

/*:36*//*42:*/
#line 905 "./bdd15.w"

void print_memo(memo*m){
printf("%x",id(m->f));
if(m->h<=maxbinop)printf("%s%x",binopname[m->h],id(m->g));
else printf("%s%x%s%x",
ternopname1[m->h&0xf],id(m->g),ternopname2[m->h&0xf],id(m->h));
printf("=%x\n",id(m->r));
}

void print_cache(void){
register int k;
register memo*m;
for(k= 0;k<cachepages;k++)
for(m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
if(m->r)print_memo(m);
}

/*:42*//*44:*/
#line 940 "./bdd15.w"

int choose_cache_size(int items){
register int k,slots;
k= 1,slots= cacheslotsperpage;
while(4*slots<totalnodes-deadnodes&&k<maxcachepages)k<<= 1,slots<<= 1;
while(slots<4*items&&k<maxcachepages)k<<= 1,slots<<= 1;
return k;
}

void cache_init(void){
register int k;
register memo*m;
cachepages= choose_cache_size(0);
if(verbose&(8+16+32+512))
printf("initializing the cache (%d page%s)\n",
cachepages,cachepages==1?"":"s");
for(k= 0;k<cachepages;k++){
o,cachepage[k]= addr_(reserve_page());
if(!cachepage[k]){
fprintf(stderr,"(trouble allocating cache pages!)\n");
for(k--;(k+1)&k;k--)o,free_page(page_(cachepage[k]));
cachepages= k+1;
break;
}
for(m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
m->r= 0;
zmems+= cacheslotsperpage;
}
cachemask= (cachepages<<logpagesize)-1;
cacheinserts= 0;
threshold= 1+(cachepages*cacheslotsperpage)/2;
}

/*:44*//*46:*/
#line 990 "./bdd15.w"

node*cache_lookup(node*f,node*g,node*h){
register node*r;
register memo*m;
register addr slot= cachehash(f,g,h);
o,m= thememo(slot);
o,r= node_(m->r);
if(!r)return NULL;
if(o,node_(m->f)==f&&node_(m->g)==g&&node_(m->h)==h){
if(verbose&8){
printf("hit %x: ",(slot&cachemask)/sizeof(memo));
print_memo(m);
}
if(o,r->xref<0){
recursively_revive(r);
return r;
}
return o,r->xref++,r;
}
return NULL;
}

/*:46*//*47:*/
#line 1015 "./bdd15.w"

void cache_insert(node*f,node*g,node*h,node*r){
register memo*m,*mm;
register int k;
register int slot= cachehash(f,g,h);
if(h)oo;else o;
if(++cacheinserts>=threshold)/*48:*/
#line 1034 "./bdd15.w"

if(cachepages<maxcachepages){
if(verbose&(8+16+32+512))
printf("doubling the cache (%d pages)\n",cachepages<<1);
for(k= cachepages;k<cachepages+cachepages;k++){
o,cachepage[k]= addr_(reserve_page());
if(!cachepage[k]){
fprintf(stderr,"(trouble doubling cache pages!)\n");
for(k--;k>=cachepages;k--)o,free_page(page_(cachepage[k]));
goto done;
}
for(m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
m->r= 0;
zmems+= cacheslotsperpage;
}
cachepages<<= 1;
cachemask+= cachemask+1;
threshold= 1+(cachepages*cacheslotsperpage)/2;
/*49:*/
#line 1056 "./bdd15.w"

for(k= cachepages>>1;k<cachepages;k++){
for(o,m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
if(o,m->r){
if(m->h)oo;else o;
oo,mm= thememo(cachehash(node_(m->f),node_(m->g),node_(m->h)));
if(m!=mm){
oo,*mm= *m;
o,m->r= 0;
}
}
}

/*:49*/
#line 1052 "./bdd15.w"
;
}
done:

/*:48*/
#line 1021 "./bdd15.w"
;
o,m= thememo(slot);
if((verbose&16)&&m->r){
printf("lose %x: ",(slot&cachemask)/sizeof(memo));
print_memo(m);
}
oo,m->f= addr_(f),m->g= addr_(g),m->h= addr_(h),m->r= addr_(r);
if(verbose&32){
printf("set %x: ",(slot&cachemask)/sizeof(memo));
print_memo(m);
}
}

/*:47*//*50:*/
#line 1072 "./bdd15.w"

void cache_purge(void){
register int k,items,newcachepages;
register memo*m,*mm;
for(k= items= 0;k<cachepages;k++){
for(m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
if(o,m->r){
if((o,node_(m->r)->xref<0)||(oo,node_(m->f)->xref<0))goto purge;
if(o,node_(m->g)->xref<0)goto purge;
if(m->h> maxbinop&&(o,node_(m->h&-0x10)->xref<0))goto purge;
items++;continue;
purge:o,m->r= 0;
}
}
if(verbose&(8+16+32+512))
printf("purging the cache (%d items left)\n",items);
/*51:*/
#line 1092 "./bdd15.w"

newcachepages= choose_cache_size(items);
if(newcachepages<cachepages){
if(verbose&(8+16+32+512))
printf("downsizing the cache (%d page%s)\n",
newcachepages,newcachepages==1?"":"s");
cachemask= (newcachepages<<logpagesize)-1;
for(k= newcachepages;k<cachepages;k++){
for(o,m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
if(o,m->r){
if(m->h)oo;else o;
oo,mm= thememo(cachehash(node_(m->f),node_(m->g),node_(m->h)));
if(m!=mm){
oo,*mm= *m;
}
}
free_page(page_(cachepage[k]));
}
cachepages= newcachepages;
threshold= 1+(cachepages*cacheslotsperpage)/2;
}

/*:51*/
#line 1088 "./bdd15.w"
;
cacheinserts= items;
}

/*:50*//*53:*/
#line 1135 "./bdd15.w"

void mark(node*p){
rmems++;
restart:if(o,p->xref>=0){
o,p->xref^= 0x80000000;
ooo,mark(node_(p->lo));
o,p= node_(p->hi);
goto restart;
}
}

/*:53*//*54:*/
#line 1149 "./bdd15.w"

void unmark(node*p){
rmems++;
restart:if(o,p->xref<0){
o,p->xref^= 0x80000000;
ooo,unmark(node_(p->lo));
o,p= node_(p->hi);
goto restart;
}
}

/*:54*//*55:*/
#line 1169 "./bdd15.w"

void print_base(int marked){
register int j,k;
register node*p;
register var*v;
for(v= varhead;v<topofvars;v++){
for(k= 0;k<v->mask;k+= sizeof(addr)){
p= fetchnode(v,k);
if(p&&(!marked||(p->xref+1)<0)){
print_node(p);
if(marked||p->xref==0)printf("\n");
else printf(" (%d)\n",p->xref);
}
}
if(!marked){
printf("t%d=%x\ne%d=%x\n",v->name,id(v->taut),v->name,id(v->elt));
if(v->proj)printf("x%d=%x\n",v->name,id(v->proj));
}
}
if(!marked){
for(j= 0;j<extsize;j++)if(f[j])
printf("f%d=%x\n",j,id(f[j]));
}
}

/*:55*//*56:*/
#line 1196 "./bdd15.w"

void print_function(node*p){
unsigned long long savemems= mems,savermems= rmems;

if(p==botsink||p==topsink)printf("%d\n",p-botsink);
else if(p){
mark(p);
print_base(1);
unmark(p);
}
mems= savemems,rmems= savermems;
}

/*:56*//*57:*/
#line 1209 "./bdd15.w"

void print_profile(node*p){
unsigned long long savemems= mems,savermems= rmems;
register int j,k,tot,bot= 0;
register var*v;
if(!p)printf(" 0\n");
else if(p<=topsink)printf(" 1\n");
else{
tot= 0;
mark(p);
for(v= varhead;v<topofvars;v++){
/*58:*/
#line 1228 "./bdd15.w"

for(j= k= 0;k<v->mask;k+= sizeof(addr)){
register node*q= fetchnode(v,k);
if(q&&(q->xref+1)<0){
j++;
if(node_(q->lo)==botsink)bot= 1;
}
}
printf(" %d",j);
tot+= j;

/*:58*/
#line 1220 "./bdd15.w"
;
}
unmark(p);
printf(" %d (total %d)\n",bot+1,tot+bot+1);
}
mems= savemems,rmems= savermems;
}

/*:57*//*59:*/
#line 1262 "./bdd15.w"

#if includesanity
unsigned int sanitycount;
void sanity_check(void){
register node*p,*q;
register int j,k,count,extra;
register var*v;
unsigned long long savemems= mems;
sanitycount++;
/*61:*/
#line 1308 "./bdd15.w"

for(p= botsink;p<nodeptr;p++)ghost(p)->xref= 0,ghost(p)->index= -1;
/*65:*/
#line 1364 "./bdd15.w"

extra= nodeptr-botsink;
for(p= nodeavail;p;p= node_(p->xref)){
if(!superlegit(p))
printf("! illegal node %x in the list of free nodes\n",id(p));
else extra--,ghost(p)->xref= -1;
}

/*:65*/
#line 1310 "./bdd15.w"
;
/*66:*/
#line 1372 "./bdd15.w"

ghost(botsink)->index= ghost(topsink)->index= 0;
for(v= varhead;v<topofvars;v++){
if(v->proj){
if(!superlegit(node_(v->proj)))
printf("! illegal projection function for level %d\n",v-varhead);
else ghost(v->proj)->index++;
}
if(!superlegit(node_(v->taut)))
printf("! illegal tautology function for level %d\n",v-varhead);
if(!superlegit(node_(v->elt)))
printf("! illegal projection function for level %d\n",v-varhead);
else ghost(v->elt)->index++;
}
if(totvars)
ghost(varhead[0].taut)->index++;
for(j= 0;j<extsize;j++)if(f[j]){
if(f[j]> topsink&&!superlegit(f[j]))
printf("! illegal external pointer f%d\n",j);
else ghost(f[j])->index++;
}

/*:66*/
#line 1311 "./bdd15.w"
;
for(count= 2,p= topsink+1;p<nodeptr;p++)if(ghost(p)->xref!=-1){
count++;
if(!legit(node_(p->lo))||!legit(node_(p->hi)))
complain("bad pointer")
else if(node_(thevar(p)->elt)==NULL)
complain("bad var")
else if(node_(p->hi)==botsink)
complain("hi=bot")
else{
/*64:*/
#line 1347 "./bdd15.w"

{
register addr*hash;
register var*v= thevar(p);
j= v->mask;
for(hash= hashcode(node_(p->lo),node_(p->hi));;hash++){
k= addr_(hash)&j;
q= fetchnode(v,k);
if(!q)break;
if(q->lo==p->lo&&q->hi==p->hi)break;
}
if(q!=p)
complain("unfindable (lo,hi)");
addr__((size_t)(v->base[k>>logpagesize]+(k&pagemask))
-(size_t)mem+(size_t)smem)= sanitycount;
}

/*:64*/
#line 1321 "./bdd15.w"
;
if(node_(p->lo)> topsink&&thevar(p)>=thevar(node_(p->lo)))
complain("bad lo rank");
if(node_(p->hi)> topsink&&thevar(p)>=thevar(node_(p->hi)))
complain("bad hi rank");
if(p->xref>=0){
q= ghost(p);
q->lo= ghost(p->lo)->xref,ghost(p->lo)->xref= addr_(&(p->lo));
q->hi= ghost(p->hi)->xref,ghost(p->hi)->xref= addr_(&(p->hi));
}
}
}
if(count!=totalnodes)
printf("! totalnodes should be %d, not %d\n",count,totalnodes);
if(extra!=totalnodes)
printf("! %d nodes have leaked\n",extra-totalnodes);

/*:61*/
#line 1271 "./bdd15.w"
;
/*67:*/
#line 1394 "./bdd15.w"

for(p= botsink,count= 0;p<nodeptr;p++){
q= ghost(p);
if(q->xref==-1)continue;
for(k= q->index,q= node_(q->xref);q;q= node_(addr__(ghost(q))))k++;
if(p->xref!=k)
printf("! %x->xref should be %d, not %d\n",id(p),k,p->xref);
if(k<0)count++;
}
if(count!=deadnodes)
printf("! deadnodes should be %d, not %d\n",count,deadnodes);

/*:67*/
#line 1272 "./bdd15.w"
;
/*69:*/
#line 1426 "./bdd15.w"

extra= topofmem-pageptr;
for(v= varhead;v<topofvars;v++){
for(k= 0;k<=v->mask>>logpagesize;k++)
if(badpage(page_(v->base[k])))
printf("! bad page base %x in unique table for level %d\n",
id(v->base[k]),v-varhead);
extra-= 1+(v->mask>>logpagesize);
for(k= count= 0;k<v->mask;k+= sizeof(addr)){
p= fetchnode(v,k);
if(!p)count++;
else{
if(addr__((size_t)(v->base[k>>logpagesize]+(k&pagemask))
-(size_t)mem+(size_t)smem)!=sanitycount)
printf("! extra node %x in unique table for level %d\n",id(p),v-varhead);
if(!superlegit(p))
printf("! illegal node %x in unique table for level %d\n",id(p),v-varhead);
else if(varpart(p->index)!=v-varhead)
complain("wrong var");
}
}
if(count!=v->free)
printf("! unique table %d has %d free slots, not %d\n",
v-varhead,count,v->free);
}

/*:69*/
#line 1273 "./bdd15.w"
;
/*70:*/
#line 1455 "./bdd15.w"

{
register memo*m;
extra-= 1+(cachemask>>logpagesize);
for(k= 0;k<cachepages;k++){
if(badpage(page_(cachepage[k])))
printf("! bad page base %x in the cache\n",id(cachepage[k]));
for(m= memo_(cachepage[k]);m<memo_(cachepage[k])+cacheslotsperpage;m++)
if(m->r){
if(!legit(node_(m->r)))goto nogood;
if(!legit(node_(m->f)))goto nogood;
if(!legit(node_(m->g)))goto nogood;
if(m->h> maxbinop&&!legit(node_(m->h&-0x10)))goto nogood;
}
continue;
nogood:printf("! bad node in cache entry ");print_memo(m);
}
}

/*:70*/
#line 1274 "./bdd15.w"
;
/*71:*/
#line 1477 "./bdd15.w"

{
register page*p= pageavail;
while(p&&extra> 0){
if(badpage(p))
printf("! bad free page %x\n",id(p));
p= page_(p->dat[0]),extra--;
}
if(extra> 0)
printf("! %d pages have leaked\n",extra);
else if(p)
printf("! the free pages form a loop\n");
}

/*:71*/
#line 1275 "./bdd15.w"
;
mems= savemems;
}
#endif

/*:59*//*68:*/
#line 1409 "./bdd15.w"

#if includesanity
void who_points_to(node*p){
register addr q;
for(q= addr_(ghost(p)->xref);q;q= addr__(ghost(q))){
print_node(node_(q&-sizeof(node)));
printf("\n");
}
}
#endif

/*:68*//*72:*/
#line 1495 "./bdd15.w"

void recursively_revive(node*p){
register node*q;
rmems++;
restart:if(verbose&4)printf("reviving %x\n",id(p));
o,p->xref= 0;
deadnodes--;
q= node_(p->lo);
if(o,q->xref<0)oooo,recursively_revive(q);
else o,q->xref++;
p= node_(p->hi);
if(o,p->xref<0)goto restart;
else o,p->xref++;
}

/*:72*//*73:*/
#line 1515 "./bdd15.w"

void recursively_kill(node*p){
register node*q;
rmems++;
restart:if(verbose&4)printf("burying %x\n",id(p));
o,p->xref= -1;
deadnodes++;
q= node_(p->lo);
if(o,q->xref==0)oooo,recursively_kill(q);
else o,q->xref--;
p= node_(p->hi);
if(o,p->xref==0)goto restart;
else o,p->xref--;
}

/*:73*//*74:*/
#line 1550 "./bdd15.w"

node*and_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1;
oo,vf= thevar(f),vg= thevar(g);
while(vf!=vg){
if(vf<vg){
if(g==botsink)return oo,g->xref++,g;
oo,f= node_(f->lo),vf= thevar(f);
}
else if(f==botsink)return oo,f->xref++,f;
else oo,g= node_(g->lo),vg= thevar(g);
}
if(f==g)return oo,f->xref++,f;
if(f> g)r= f,f= g,g= r;
if(o,f==node_(vf->taut))return oo,g->xref++,g;
if(g==node_(vf->taut))return oo,f->xref++,f;
r= cache_lookup(f,g,node_(1));

if(r)return r;
/*75:*/
#line 1579 "./bdd15.w"

rmems++;
oo,r0= and_rec(node_(f->lo),node_(g->lo));
if(!r0)return NULL;
r1= and_rec(node_(f->hi),node_(g->hi));
if(!r1){
deref(r0);
return NULL;
}
r= unique_find(vf,r0,r1);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x&%x (level %d)\n",id(r),id(f),id(g),vf-varhead);
cache_insert(f,g,node_(1),r);
}
return r;

/*:75*/
#line 1570 "./bdd15.w"
;
}

/*:74*//*76:*/
#line 1599 "./bdd15.w"

node*or_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1;
if(f==g)return oo,f->xref++,f;
if(f> g)r= f,f= g,g= r;
if(f==botsink)return oo,g->xref++,g;
oo,r= cache_lookup(f,g,node_(7));
if(r)return r;
/*77:*/
#line 1611 "./bdd15.w"

rmems++;
vf= thevar(f);
vg= thevar(g);
if(vf<vg){
v= vf;
if(o,f==node_(vf->taut))return oo,f->xref++,f;
o,r0= or_rec(node_(f->lo),g);
if(!r0)return NULL;
r1= node_(f->hi),oo,r1->xref++;
}else{
v= vg;
if(o,g==node_(vg->taut))return oo,g->xref++,g;
if(vg<vf){
o,r0= or_rec(f,node_(g->lo));
if(!r0)return NULL;
r1= node_(g->hi),oo,r1->xref++;
}else{
oo,r0= or_rec(node_(f->lo),node_(g->lo));
if(!r0)return NULL;
r1= or_rec(node_(f->hi),node_(g->hi));
if(!r1){
deref(r0);
return NULL;
}
}
}
r= unique_find(v,r0,r1);
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x|%x (level %d)\n",id(r),id(f),id(g),v-varhead);
cache_insert(f,g,node_(7),r);
}
return r;

/*:77*/
#line 1608 "./bdd15.w"
;
}

/*:76*//*78:*/
#line 1648 "./bdd15.w"

node*xor_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1;
if(f==g)return oo,botsink->xref++,botsink;
if(f> g)r= f,f= g,g= r;
if(f==botsink)return oo,g->xref++,g;
oo,r= cache_lookup(f,g,node_(6));
if(r)return r;
/*79:*/
#line 1660 "./bdd15.w"

rmems++;
vf= thevar(f);
vg= thevar(g);
if(vf<vg){
v= vf;
o,r0= xor_rec(node_(f->lo),g);
if(!r0)return NULL;
r1= node_(f->hi),oo,r1->xref++;
}else{
v= vg;
if(vg<vf){
o,r0= xor_rec(f,node_(g->lo));
if(!r0)return NULL;
r1= node_(g->hi),oo,r1->xref++;
}else{
oo,r0= xor_rec(node_(f->lo),node_(g->lo));
if(!r0)return NULL;
r1= xor_rec(node_(f->hi),node_(g->hi));
if(!r1){
deref(r0);
return NULL;
}
}
}
r= unique_find(v,r0,r1);
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x^%x (level %d)\n",id(r),id(f),id(g),v-varhead);
cache_insert(f,g,node_(6),r);
}
return r;

/*:79*/
#line 1657 "./bdd15.w"
;
}

/*:78*//*80:*/
#line 1697 "./bdd15.w"

node*but_not_rec(node*f,node*g){
var*vf,*vg;
node*r,*r0,*r1;
if(f==g||f==botsink)
return oo,botsink->xref++,botsink;
if(g==botsink)return oo,f->xref++,f;
oo,vf= thevar(f),vg= thevar(g);
while(vg<vf){
oo,g= node_(g->lo),vg= thevar(g);
if(f==g)return oo,botsink->xref++,botsink;
if(g==botsink)return oo,f->xref++,f;
}
r= cache_lookup(f,g,node_(2));
if(r)return r;
/*81:*/
#line 1715 "./bdd15.w"

rmems++;
if(vf<vg){
o,r0= but_not_rec(node_(f->lo),g);
if(!r0)return NULL;
r1= node_(f->hi),oo,r1->xref++;
}else{
oo,r0= but_not_rec(node_(f->lo),node_(g->lo));
if(!r0)return NULL;
r1= but_not_rec(node_(f->hi),node_(g->hi));
if(!r1){
deref(r0);
return NULL;
}
}
r= unique_find(vf,r0,r1);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x>%x (level %d)\n",id(r),id(f),id(g),vf-varhead);
cache_insert(f,g,node_(2),r);
}
return r;

/*:81*/
#line 1712 "./bdd15.w"
;
}

/*:80*//*82:*/
#line 1749 "./bdd15.w"

node*prod_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1,*r01,*r10;
if(f> g)r= f,f= g,g= r;
if(f<=topsink){
if(f==botsink)return oo,f->xref++,f;
else return oo,g->xref++,g;
}
o,v= vf= thevar(f);
o,vg= thevar(g);
if(vf> vg)r= f,f= g,g= r,v= vg;
r= cache_lookup(f,g,node_(5));
if(r)return r;
/*83:*/
#line 1780 "./bdd15.w"

rmems++;
if(vf!=vg){
o,r0= prod_rec(node_(f->lo),g);
if(!r0)return NULL;
r1= prod_rec(node_(f->hi),g);
if(!r1){
deref(r0);
return NULL;
}
}else{
o,r10= or_rec(node_(g->lo),node_(g->hi));
if(!r10)return NULL;
o,r= prod_rec(node_(f->hi),r10);
deref(r10);
if(!r)return NULL;
r01= prod_rec(node_(f->lo),node_(g->hi));
if(!r01){
deref(r);return NULL;
}
r1= or_rec(r,r01);
deref(r);deref(r01);
if(!r1)return NULL;
r0= prod_rec(node_(f->lo),node_(g->lo));
if(!r0){
deref(r1);return NULL;
}
}
r= unique_find(v,r0,r1);
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x*%x (level %d)\n",id(r),id(f),id(g),v-varhead);
cache_insert(f,g,node_(5),r);
}
return r;

/*:83*/
#line 1763 "./bdd15.w"
;
}

/*:82*//*84:*/
#line 1826 "./bdd15.w"

node*disprod_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1,*r01;
if(f> g)r= f,f= g,g= r;
if(f<=topsink){
if(f==botsink)return oo,f->xref++,f;
else return oo,g->xref++,g;
}
o,v= vf= thevar(f);
o,vg= thevar(g);
if(vf> vg)r= f,f= g,g= r,v= vg;
r= cache_lookup(f,g,node_(0));
if(r)return r;
/*85:*/
#line 1843 "./bdd15.w"

rmems++;
if(vf!=vg){
o,r0= disprod_rec(node_(f->lo),g);
if(!r0)return NULL;
r1= disprod_rec(node_(f->hi),g);
if(!r1){
deref(r0);
return NULL;
}
}else{
o,r= disprod_rec(node_(f->hi),node_(g->lo));
if(!r)return NULL;
r01= disprod_rec(node_(f->lo),node_(g->hi));
if(!r01){
deref(r);return NULL;
}
r1= or_rec(r,r01);
deref(r);deref(r01);
if(!r1)return NULL;
r0= disprod_rec(node_(f->lo),node_(g->lo));
if(!r0){
deref(r1);return NULL;
}
}
r= unique_find(v,r0,r1);
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x+%x (level %d)\n",id(r),id(f),id(g),v-varhead);
cache_insert(f,g,node_(0),r);
}
return r;

/*:85*/
#line 1840 "./bdd15.w"
;
}

/*:84*//*86:*/
#line 1885 "./bdd15.w"

node*coprod_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1,*r01,*r10;
if(f> g)r= f,f= g,g= r;
if(f<=topsink)return oo,f->xref++,f;

oo,r= cache_lookup(f,g,node_(8));
if(r)return r;
/*87:*/
#line 1897 "./bdd15.w"

rmems++;
v= vf= thevar(f),vg= thevar(g);
if(vf!=vg){
if(vf> vg)r= f,f= g,g= r;
o,r0= or_rec(node_(f->lo),node_(f->hi));
if(!r0)return NULL;
r= coprod_rec(r0,g);
deref(r0);
}else{
o,r10= or_rec(node_(f->lo),node_(f->hi));
if(!r10)return NULL;
o,r= coprod_rec(r10,node_(g->lo));
deref(r10);
if(!r)return NULL;
r01= coprod_rec(node_(f->lo),node_(g->hi));
if(!r01){
deref(r);return NULL;
}
r0= or_rec(r,r01);
deref(r);deref(r01);
if(!r0)return NULL;
r1= coprod_rec(node_(f->hi),node_(g->hi));
if(!r1){
deref(r1);return NULL;
}
r= unique_find(v,r0,r1);
}
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x_%x (level %d)\n",id(r),id(f),id(g),v-varhead);
cache_insert(f,g,node_(8),r);
}
return r;

/*:87*/
#line 1894 "./bdd15.w"
;
}

/*:86*//*88:*/
#line 1939 "./bdd15.w"

node*delta_rec(node*f,node*g){
var*v,*vf,*vg;
node*r,*r0,*r1,*r00,*r01,*r10,*r11;
if(f> g)r= f,f= g,g= r;
if(f<=topsink){
if(f==botsink)return oo,f->xref++,f;
else return oo,g->xref++,g;
}
o,v= vf= thevar(f);
o,vg= thevar(g);
if(vf> vg)r= f,f= g,g= r,v= vg;
r= cache_lookup(f,g,node_(11));
if(r)return r;
/*89:*/
#line 1956 "./bdd15.w"

rmems++;
if(vf!=vg){
o,r0= delta_rec(node_(f->lo),g);
if(!r0)return NULL;
r1= delta_rec(node_(f->hi),g);
if(!r1){
deref(r0);
return NULL;
}
}else{
oo,r01= delta_rec(node_(f->lo),node_(g->hi));
if(!r01)return NULL;
r10= delta_rec(node_(f->hi),node_(g->lo));
if(!r10){
deref(r01);return NULL;
}
r1= or_rec(r01,r10);
deref(r01);deref(r10);
if(!r1)return NULL;
r11= delta_rec(node_(f->hi),node_(g->hi));
if(!r11){
deref(r1);return NULL;
}
r00= delta_rec(node_(f->lo),node_(g->lo));
if(!r00){
deref(r1);deref(r11);return NULL;
}
r0= or_rec(r00,r11);
deref(r00);deref(r11);
if(!r0){
deref(r1);return NULL;
}
}
r= unique_find(v,r0,r1);
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x#%x (level %d)\n",id(r),id(f),id(g),v-varhead);
cache_insert(f,g,node_(11),r);
}
return r;

/*:89*/
#line 1953 "./bdd15.w"
;
}

/*:88*//*90:*/
#line 2013 "./bdd15.w"

node*ezrem_rec(node*f,var*vg){
var*vf;
node*r,*r0,*r1;
o,vf= thevar(f);
if(vf==vg){
r= node_(f->lo);
return oo,r->xref++,r;
}
if(vf> vg)return oo,f->xref++,f;
o,r= cache_lookup(f,node_(vg->elt),node_(10));
if(r)return r;
/*91:*/
#line 2028 "./bdd15.w"

rmems++;
o,r0= ezrem_rec(node_(f->lo),vg);
if(!r0)return NULL;
r1= ezrem_rec(node_(f->hi),vg);
if(!r1){
deref(r0);return NULL;
}
r= unique_find(vf,r0,r1);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x%%%x (level %d)\n",id(r),id(f),id(vg->elt),vf-varhead);
cache_insert(f,node_(vg->elt),node_(10),r);
}
return r;

/*:91*/
#line 2025 "./bdd15.w"
;
}

/*:90*//*92:*/
#line 2044 "./bdd15.w"

node*ezquot_rec(node*f,var*vg){
var*vf;
node*r,*r0,*r1;
o,vf= thevar(f);
if(vf==vg){
r= node_(f->hi);
return oo,r->xref++,r;
}
if(vf> vg)return oo,botsink->xref++,botsink;
o,r= cache_lookup(f,node_(vg->elt),node_(9));
if(r)return r;
/*93:*/
#line 2059 "./bdd15.w"

rmems++;
o,r0= ezquot_rec(node_(f->lo),vg);
if(!r0)return NULL;
r1= ezquot_rec(node_(f->hi),vg);
if(!r1){
deref(r0);return NULL;
}
r= unique_find(vf,r0,r1);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x%%%x (level %d)\n",id(r),id(f),id(vg->elt),vf-varhead);
cache_insert(f,node_(vg->elt),node_(9),r);
}
return r;

/*:93*/
#line 2056 "./bdd15.w"
;
}

/*:92*//*94:*/
#line 2079 "./bdd15.w"

node*quot_rec(node*f,node*g){
node*r,*r0,*r1,*f0,*f1;
var*vf,*vg;
if(g<=topsink){
if(g==topsink)return oo,f->xref++,f;
return oo,tautology->xref++,tautology;
}
if(f<=topsink)return oo,botsink->xref++,botsink;
if(f==g)return oo,topsink->xref++,topsink;
if(o,node_(g->lo)==botsink&&node_(g->hi)==topsink)
return o,ezquot_rec(f,thevar(g));
r= cache_lookup(f,g,node_(9));
if(r)return r;
/*95:*/
#line 2096 "./bdd15.w"

rmems++;
o,vg= thevar(g);
f1= ezquot_rec(f,vg);
if(!f1)return NULL;
r= quot_rec(f1,node_(g->hi));
deref(f1);
if(!r)return NULL;
if(r!=botsink&&node_(g->lo)!=botsink){
r1= r;
f0= ezrem_rec(f,vg);
if(!f0)return NULL;
r0= quot_rec(f0,node_(g->lo));
deref(f0);
if(!r0){
deref(r1);return NULL;
}
r= and_rec(r1,r0);
deref(r1);deref(r0);
}
if(r){
if((verbose&128)&&(vg<tvar))
printf("   %x=%x/%x (level %d)\n",id(r),id(f),id(g),vg-varhead);
cache_insert(f,g,node_(9),r);
}
return r;

/*:95*/
#line 2093 "./bdd15.w"
;
}

/*:94*//*96:*/
#line 2126 "./bdd15.w"

node*rem_rec(node*f,node*g){
node*r,*r1;
var*vf;
if(g<=topsink){
if(g==botsink)return oo,f->xref++,f;
return oo,botsink->xref++,botsink;
}
if(o,node_(g->lo)==botsink&&node_(g->hi)==topsink)
return o,ezrem_rec(f,thevar(g));
r= cache_lookup(f,g,node_(10));
if(r)return r;
r= quot_rec(f,g);
if(!r)return NULL;
r1= prod_rec(r,g);
deref(r);
if(!r1)return NULL;
r= but_not_rec(f,r1);
deref(r1);
if(r){
vf= thevar(f);
if((verbose&128)&&(vf<tvar))
printf("   %x=%x%%%x (level %d)\n",id(r),id(f),id(g),vf-varhead);
cache_insert(f,g,node_(10),r);
}
return r;
}

/*:96*//*97:*/
#line 2166 "./bdd15.w"

node*mux_rec(node*f,node*g,node*h){
var*v,*vf,*vg,*vh;
node*r,*r0,*r1;
if(f==botsink)return oo,h->xref++,h;
if(g==botsink)return but_not_rec(h,f);
if(h==botsink||f==h)return and_rec(f,g);

if(f==g)return or_rec(f,h);
if(g==h)return oo,g->xref++,g;
ooo,vf= thevar(f),vg= thevar(g),vh= thevar(h);
gloop:while(vg<vf&&vg<vh){
oo,g= node_(g->lo),vg= thevar(g);
if(g==botsink)return but_not_rec(h,f);
if(f==g)return or_rec(f,h);
if(g==h)return oo,g->xref++,g;
}
while(vf<vg&&vf<vh){
oo,f= node_(f->lo),vf= thevar(f);
if(f==botsink)return oo,h->xref++,h;
if(f==h)return and_rec(f,g);
if(f==g)return or_rec(f,h);
}
if(vg<vf&&vg<vh)goto gloop;
if(vf<vg)v= vf;else v= vg;
if(vh<v)v= vh;
if(f==node_(v->taut))return oo,g->xref++,g;
if(g==node_(v->taut))return or_rec(f,h);
r= cache_lookup(f,g,h);
if(r)return r;
/*98:*/
#line 2199 "./bdd15.w"

rmems++;
if(v<vf){
o,r0= mux_rec(f,(vg==v?o,node_(g->lo):g),node_(h->lo));
if(!r0)return NULL;
r1= node_(h->hi),oo,r1->xref++;
}
else{
o,r0= mux_rec(node_(f->lo),(vg==v?o,node_(g->lo):g),
(vh==v?o,node_(h->lo):h));
if(!r0)return NULL;
o,r1= mux_rec(node_(f->hi),(vg==v?o,node_(g->hi):botsink),
(vh==v?o,node_(h->hi):botsink));
if(!r1){
deref(r0);
return NULL;
}
}
r= unique_find(v,r0,r1);
if(r){
if((verbose&128)&&(v<tvar))
printf("   %x=%x?%x:%x (level %d)\n",id(r),id(f),id(g),id(h),v-varhead);
cache_insert(f,g,h,r);
}
return r;

/*:98*/
#line 2196 "./bdd15.w"
;
}

/*:97*//*99:*/
#line 2228 "./bdd15.w"

node*med_rec(node*f,node*g,node*h){
var*v,*vf,*vg,*vh;
node*r,*r0,*r1;
ooo,vf= thevar(f),vg= thevar(g),vh= thevar(h);
gloop:if(vg<vf||(vg==vf&&g<f))v= vg,vg= vf,vf= v,r= f,f= g,g= r;
if(vh<vg||(vh==vg&&h<g))v= vh,vh= vg,vg= v,r= g,g= h,h= r;
if(vg<vf||(vg==vf&&g<f))v= vg,vg= vf,vf= v,r= f,f= g,g= r;
if(h==botsink)return and_rec(f,g);
if(f==g)return oo,f->xref++,f;
if(g==h)return oo,g->xref++,g;
if(vf<vg){
do{
oo,f= node_(f->lo),vf= thevar(f);
}while(vf<vg);
goto gloop;
}
r= cache_lookup(f,g,node_(addr_(h)+1));
if(r)return r;
/*100:*/
#line 2250 "./bdd15.w"

rmems++;
oo,r0= med_rec(node_(f->lo),node_(g->lo),
(vh==vf?o,node_(h->lo):h));
if(!r0)return NULL;
if(vf<vh)r1= and_rec(node_(f->hi),node_(g->hi));
else r1= med_rec(node_(f->hi),node_(g->hi),node_(h->hi));
if(!r1){
deref(r0);
return NULL;
}
r= unique_find(vf,r0,r1);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x.%x.%x (level %d)\n",id(r),id(f),id(g),id(h),vf-varhead);
cache_insert(f,g,node_(addr_(h)+1),r);
}
return r;

/*:100*/
#line 2247 "./bdd15.w"
;
}

/*:99*//*101:*/
#line 2271 "./bdd15.w"

node*and_and_rec(node*f,node*g,node*h){
var*v,*vf,*vg,*vh;
node*r,*r0,*r1;
ooo,vf= thevar(f),vg= thevar(g),vh= thevar(h);
restart:while(vf!=vg){
if(vf<vg){
if(g==botsink)return oo,g->xref++,g;
oo,f= node_(f->lo),vf= thevar(f);
}else if(f==botsink)return oo,f->xref++,f;
else oo,g= node_(g->lo),vg= thevar(g);
}
if(f==g)return and_rec(g,h);
while(vf!=vh){
if(vf<vh){
if(h==botsink)return oo,h->xref++,h;
oooo,f= node_(f->lo),vf= thevar(f),g= node_(g->lo),vg= thevar(g);
goto restart;
}
else oo,h= node_(h->lo),vh= thevar(h);
}
if(f> g){
if(g> h)r= f,f= h,h= r;
else if(f> h)r= f,f= g,g= h,h= r;
else r= f,f= g,g= r;
}else if(g> h){
if(f> h)r= f,f= h,h= g,g= r;
else r= g,g= h,h= r;
}
if(f==g)return and_rec(g,h);
if(g==h)return and_rec(f,g);
if(o,f==node_(vf->taut))return and_rec(g,h);

if(g==node_(vf->taut))return and_rec(f,h);
if(h==node_(vf->taut))return and_rec(f,g);
r= cache_lookup(f,g,node_(addr_(h)+2));
if(r)return r;
/*102:*/
#line 2311 "./bdd15.w"

rmems++;
ooo,r0= and_and_rec(node_(f->lo),node_(g->lo),node_(h->lo));
if(!r0)return NULL;
r1= and_and_rec(node_(f->hi),node_(g->hi),node_(h->hi));
if(!r1){
deref(r0);
return NULL;
}
r= unique_find(vf,r0,r1);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x&%x&%x (level %d)\n",id(r),id(f),id(g),id(h),vf-varhead);
cache_insert(f,g,node_(addr_(h)+2),r);
}
return r;

/*:102*/
#line 2308 "./bdd15.w"
;
}

/*:101*//*103:*/
#line 2346 "./bdd15.w"

node*symfunc(node*p,var*v,int k){
register var*vp;
register node*q,*r;
o,vp= thevar(p);
while(vp<v)oo,p= node_(p->lo),vp= thevar(p);
if(vp==topofvars){
if(k> 0)return oo,botsink->xref++,botsink;
else return oo,node_(v->taut)->xref++,node_(v->taut);
}
oooo,r= cache_lookup(p,node_(v->taut),node_(varhead[k].taut+4));
if(r)return r;
rmems++;
o,q= symfunc(node_(p->lo),vp+1,k);
if(!q)return NULL;
if(k> 0){
r= symfunc(node_(p->lo),vp+1,k-1);
if(!r){
deref(q);
return NULL;
}
q= unique_find(vp,q,r);
if(!q)return NULL;
}
while(vp> v){
vp--;
oo,q->xref++;
q= unique_find(vp,q,q);
if(!q)return NULL;
}
if((verbose&128)&&(v<tvar))
printf("   %x=%x@%x@%x (level %d)\n",id(q),id(p),id(v->taut),
id(varhead[k].taut),v-varhead);
cache_insert(p,node_(v->taut),node_(varhead[k].taut+4),q);
return q;
}

/*:103*//*104:*/
#line 2391 "./bdd15.w"

node*zdd_build(node*f,node*g,node*h){
var*vf;
node*r;
if(f<=topsink)return oo,f->xref++,f;
o,vf= thevar(f);
while((o,thevar(g))<=vf)g= node_(g->lo);
while((o,thevar(h))<=vf)h= node_(h->lo);
oooo,g->xref++,h->xref++;
r= unique_find(vf,g,h);
if(r){
if((verbose&128)&&(vf<tvar))
printf("   %x=%x!%x:%x (level %d)\n",id(r),id(f),id(g),id(h),vf-varhead);
}
return r;
}

/*:104*//*105:*/
#line 2413 "./bdd15.w"

node*binary_top(int curop,node*f,node*g){
node*r;
unsigned long long oldmems= mems,oldrmems= rmems,oldzmems= zmems;
if(verbose&2)
printf("beginning to compute %x %s %x:\n",
id(f),binopname[curop],id(g));
cacheinserts= 0;
while(1){
switch(curop){
case 0:r= disprod_rec(f,g);break;
case 1:r= and_rec(f,g);break;
case 2:r= but_not_rec(f,g);break;
case 4:r= but_not_rec(g,f);break;
case 5:r= prod_rec(f,g);break;
case 6:r= xor_rec(f,g);break;
case 7:r= or_rec(f,g);break;
case 8:r= coprod_rec(f,g);break;
case 9:r= quot_rec(f,g);break;
case 10:r= rem_rec(f,g);break;
case 11:r= delta_rec(f,g);break;
default:fprintf(stderr,"This can't happen!\n");exit(-69);
}
if(r)break;
attempt_repairs();
}
if(verbose&(1+2))
printf(" %x=%x%s%x (%llu mems, %llu rmems, %llu zmems, %.4g)\n",
id(r),id(f),binopname[curop],id(g),
mems-oldmems,rmems-oldrmems,zmems-oldzmems,
mems-oldmems+rfactor*(rmems-oldrmems)+zfactor*(zmems-oldzmems));
return r;
}

/*:105*//*107:*/
#line 2450 "./bdd15.w"

node*ternary_top(int curop,node*f,node*g,node*h){
node*r;
unsigned long long oldmems= mems,oldrmems= rmems,oldzmems= zmems;
if(verbose&2)
printf("beginning to compute %x %s %x %s %x:\n",
id(f),ternopname1[curop-16],id(g),ternopname2[curop-16],id(h));
cacheinserts= 0;
while(1){
switch(curop){
case 16:r= mux_rec(f,g,h);break;
case 17:r= med_rec(f,g,h);break;
case 18:r= and_and_rec(f,g,h);break;
case 19:r= zdd_build(f,g,h);break;
default:fprintf(stderr,"This can't happen!\n");exit(-69);
}
if(r)break;
attempt_repairs();
}
if(verbose&(1+2))
printf(" %x=%x%s%x%s%x (%llu mems, %llu rmems, %llu zmems, %.4g)\n",
id(r),id(f),ternopname1[curop-16],id(g),ternopname2[curop-16],
id(h),mems-oldmems,rmems-oldrmems,zmems-oldzmems,
mems-oldmems+rfactor*(rmems-oldrmems)+zfactor*(zmems-oldzmems));
return r;
}

node*symfunc_top(node*p,int k){
node*r;
unsigned long long oldmems= mems,oldrmems= rmems,oldzmems= zmems;
if(verbose&2)
printf("beginning to compute %x S %d:\n",
id(p),k);
cacheinserts= 0;
while(1){
r= symfunc(p,varhead,k);
if(r)break;
attempt_repairs();
}
if(verbose&(1+2))
printf(" %x=%xS%d (%llu mems, %llu rmems, %llu zmems, %.4g)\n",
id(r),id(p),k,mems-oldmems,rmems-oldrmems,zmems-oldzmems,
mems-oldmems+rfactor*(rmems-oldrmems)+zfactor*(zmems-oldzmems));
return r;
}


/*:107*//*120:*/
#line 2678 "./bdd15.w"

node*getconst(int k){
k-= '0';
if(k<0||k> 2)return NULL;
if(totvars==0){
printf("(Hey, I don't know the number of variables yet.)\n");
return NULL;
}
if(k==0)return botsink;
if(k==2)return topsink;
return tautology;
}

/*:120*//*129:*/
#line 2813 "./bdd15.w"

void reorder_init(void){
var*v,*vup;
collect_garbage(1);
totalvars= 0;
for(v= varhead,vup= NULL;v<topofvars;v++){
v->aux= ++totalvars;
v->up= vup;
if(vup)vup->down= v;else firstvar= v;
vup= v;
}
if(vup)vup->down= NULL;else firstvar= NULL;
oldleases= leasesonlife;
leasesonlife= 1;
}

void reorder_fin(void){
cache_init();
leasesonlife= oldleases;
}

/*:129*//*135:*/
#line 2978 "./bdd15.w"

void new_unique(var*v,int m){
register int f,j,k;
for(f= 6;(m<<2)> f;f<<= 1);
f= f&(-f);
o,v->free= f,v->mask= (f<<2)-1;
for(k= 0;k<=v->mask>>logpagesize;k++){
o,v->base[k]= addr_(reserve_page());
if(k){
for(j= v->base[k];j<v->base[k]+pagesize;j+= sizeof(long long))
storenulls(j);
zmems+= pagesize/sizeof(long long);
}
}
f= v->mask&pagemask;
for(j= v->base[0];j<v->base[0]+f;j+= sizeof(long long))storenulls(j);
zmems+= (f+1)/sizeof(long long);
}

/*:135*//*136:*/
#line 3003 "./bdd15.w"

void insert_node(var*v,node*q){
register int j,k,mask,free;
register addr*hash;
register node*l,*h,*p,*r;
o,l= node_(q->lo),h= node_(q->hi);
restart:o,mask= v->mask,free= v->free;
for(hash= hashcode(l,h);;hash++){
k= addr_(hash)&mask;
oo,r= fetchnode(v,k);
if(!r)break;
}
if(--free<=mask>>4)
/*33:*/
#line 667 "./bdd15.w"

{
register int newmask= mask+mask+1,kk= newmask>>logpagesize;
if(verbose&256)
printf("doubling the hash table for level %d(x%d) (%d slots)\n",
v-varhead,v->name,(newmask+1)/sizeof(addr));
if(kk)/*34:*/
#line 688 "./bdd15.w"

{
if(newmask> maxmask){
if(verbose&(2+256+512))
printf("profile limit reached for level %d(x%d)\n",v-varhead,v->name);
goto cramped;
}
for(k= (mask>>logpagesize)+1;k<=kk;k++){
o,v->base[k]= addr_(reserve_page());
if(!v->base[k]){
for(k--;k> mask>>logpagesize;k--){
o,free_page(page_(v->base[k]));
}
goto cramped;
}
for(j= v->base[k];j<v->base[k]+pagesize;j+= sizeof(long long))
storenulls(j);
zmems+= pagesize/sizeof(long long);
}
}

/*:34*/
#line 673 "./bdd15.w"

else{
for(k= v->base[0]+mask+1;k<v->base[0]+newmask;k+= sizeof(long long))
storenulls(k);
zmems+= (newmask-mask)/sizeof(long long);
}
/*35:*/
#line 722 "./bdd15.w"

for(k= 0;k<newmask;k+= sizeof(addr)){
oo,r= fetchnode(v,k);
if(r){
storenode(v,k,NULL);
for(o,hash= hashedcode(r);;hash++){
j= addr_(hash)&newmask;
oo,p= fetchnode(v,j);
if(!p)break;
}
storenode(v,j,r);
}else if(k> mask)break;
}

/*:35*/
#line 679 "./bdd15.w"
;
v->mask= newmask;
v->free= free+1+(newmask-mask)/sizeof(addr);
goto restart;
}

/*:33*/
#line 3016 "./bdd15.w"
;
storenode(v,k,q);o,v->free= free;
return;
cramped:printf("Uh oh: insert_node hasn't enough memory to continue!\n");
show_stats();
exit(-96);
}

/*:136*//*139:*/
#line 3058 "./bdd15.w"

node*swap_find(var*v,node*l,node*h){
register int j,k,mask,free;
register addr*hash;
register node*p,*r;
if(h==botsink){
return oo,l->xref++,l;
}
restart:o,mask= v->mask,free= v->free;
for(hash= hashcode(l,h);;hash++){
k= addr_(hash)&mask;
oo,p= fetchnode(v,k);
if(!p)goto newnode;
if(node_(p->lo)==l&&node_(p->hi)==h)break;
}
return o,p->xref++,p;
newnode:/*140:*/
#line 3077 "./bdd15.w"

if(--free<=mask>>4)/*33:*/
#line 667 "./bdd15.w"

{
register int newmask= mask+mask+1,kk= newmask>>logpagesize;
if(verbose&256)
printf("doubling the hash table for level %d(x%d) (%d slots)\n",
v-varhead,v->name,(newmask+1)/sizeof(addr));
if(kk)/*34:*/
#line 688 "./bdd15.w"

{
if(newmask> maxmask){
if(verbose&(2+256+512))
printf("profile limit reached for level %d(x%d)\n",v-varhead,v->name);
goto cramped;
}
for(k= (mask>>logpagesize)+1;k<=kk;k++){
o,v->base[k]= addr_(reserve_page());
if(!v->base[k]){
for(k--;k> mask>>logpagesize;k--){
o,free_page(page_(v->base[k]));
}
goto cramped;
}
for(j= v->base[k];j<v->base[k]+pagesize;j+= sizeof(long long))
storenulls(j);
zmems+= pagesize/sizeof(long long);
}
}

/*:34*/
#line 673 "./bdd15.w"

else{
for(k= v->base[0]+mask+1;k<v->base[0]+newmask;k+= sizeof(long long))
storenulls(k);
zmems+= (newmask-mask)/sizeof(long long);
}
/*35:*/
#line 722 "./bdd15.w"

for(k= 0;k<newmask;k+= sizeof(addr)){
oo,r= fetchnode(v,k);
if(r){
storenode(v,k,NULL);
for(o,hash= hashedcode(r);;hash++){
j= addr_(hash)&newmask;
oo,p= fetchnode(v,j);
if(!p)break;
}
storenode(v,j,r);
}else if(k> mask)break;
}

/*:35*/
#line 679 "./bdd15.w"
;
v->mask= newmask;
v->free= free+1+(newmask-mask)/sizeof(addr);
goto restart;
}

/*:33*/
#line 3078 "./bdd15.w"
;
p= reserve_node();
storenode(v,k,p);o,v->free= free;
initnewnode(p,v-varhead,l,h);
oooo,l->xref++,h->xref++;
return p;
cramped:printf("Uh oh: swap_find hasn't enough memory to continue!\n");
show_stats();
exit(-95);

/*:140*/
#line 3074 "./bdd15.w"
;
}

/*:139*//*143:*/
#line 3121 "./bdd15.w"

/*131:*/
#line 2884 "./bdd15.w"

void swap(var*u,var*v){
register int j,k,solptr,tangptr,umask,vmask,del;
register int hcount= 0,rcount= 0,scount= 0,tcount= 0,icount= totalnodes;
register node*f,*g,*h,*gg,*hh,*p,*pl,*ph,*q,*ql,*qh,
*firsthidden,*lasthidden;
register var*vg,*vh;
unsigned long long omems= mems,ozmems= zmems;
oo,umask= u->mask,vmask= v->mask;
del= ((u-varhead)^(v-varhead))<<(32-logvarsize);
/*132:*/
#line 2912 "./bdd15.w"

solptr= j= 0;tangptr= k= umask+1;
while(1){
for(;j<k;j+= sizeof(addr)){
oo,p= fetchnode(u,j);
if(p==0)continue;
o,pl= node_(p->lo),ph= node_(p->hi);
if((o,thevar(pl)==v)||(o,thevar(ph)==v)){
oooo,pl->xref--,ph->xref--;
break;
}
storenode(u,solptr,p);
solptr+= sizeof(addr),scount++;
}
if(j>=k)break;
for(k-= sizeof(addr);j<k;k-= sizeof(addr)){
oo,q= fetchnode(u,k);
if(q==0)continue;
o,ql= node_(q->lo),qh= node_(q->hi);
if((o,thevar(ql)==v)||(o,thevar(qh)==v))
oooo,ql->xref--,qh->xref--;
else break;
tangptr-= sizeof(addr),tcount++;
storenode(u,tangptr,q);
}
tangptr-= sizeof(addr),tcount++;
storenode(u,tangptr,p);
if(j>=k)break;
storenode(u,solptr,q);
solptr+= sizeof(addr),scount++;
j+= sizeof(addr);
}

/*:132*/
#line 2894 "./bdd15.w"
;
/*133:*/
#line 2952 "./bdd15.w"

for(k= 0;k<=umask>>logpagesize;k++)oo,savebase[k]= u->base[k];
new_unique(u,tcount+1);
for(k= rcount= hcount= 0;k<vmask;k+= sizeof(addr)){
oo,p= fetchnode(v,k);
if(p==0)continue;
if(o,p->xref<0){
if(hcount==0)firsthidden= lasthidden= p,hcount= 1;
else o,hcount++,p->xref= addr_(lasthidden),lasthidden= p;
oo,node_(p->lo)->xref--;
oo,node_(p->hi)->xref--;
}else{
rcount++;
oo,p->index^= del;
insert_node(u,p);
}
}

/*:133*/
#line 2895 "./bdd15.w"
;
if(verbose&2048)printf(
"swapping %d(x%d)<->%d(x%d): solitary %d, tangled %d, remote %d, hidden %d\n",
u-varhead,u->name,v-varhead,v->name,scount,tcount,rcount,hcount);
/*137:*/
#line 3024 "./bdd15.w"

for(k= 0;k<=vmask>>logpagesize;k++)o,free_page(page_(v->base[k]));
new_unique(v,scount);
for(k= 0;k<solptr;k+= sizeof(addr)){
o,p= node_(addr__(savebase[k>>logpagesize]+(k&pagemask)));
oo,p->index^= del;
insert_node(v,p);
}

/*:137*/
#line 2899 "./bdd15.w"
;
/*138:*/
#line 3042 "./bdd15.w"

for(k= tangptr;k<umask;k+= sizeof(addr)){
o,f= node_(addr__(savebase[k>>logpagesize]+(k&pagemask)));
o,g= node_(f->lo),h= node_(f->hi);
oo,vg= thevar(g),vh= thevar(h);

gg= swap_find(v,vg> v?g:(o,node_(g->lo)),vh> v?h:(o,node_(h->lo)));
hh= swap_find(v,vg> v?botsink:node_(g->hi),vh> v?botsink:node_(h->hi));
o,f->lo= addr_(gg),f->hi= addr_(hh);
insert_node(u,f);
}

/*:138*/
#line 2900 "./bdd15.w"
;
/*141:*/
#line 3088 "./bdd15.w"

for(k= 0;k<=umask>>logpagesize;k++)o,free_page(page_(savebase[k]));
if(hcount){
o,firsthidden->xref= addr_(nodeavail);
nodeavail= lasthidden;
totalnodes-= hcount;
}

/*:141*/
#line 2901 "./bdd15.w"
;
if(verbose&2048)
printf(" newbies %d, change %d, mems (%llu,0,%llu)\n",
totalnodes-icount+hcount,totalnodes-icount,mems-omems,zmems-ozmems);
/*142:*/
#line 3108 "./bdd15.w"

oo,j= u->name,k= v->name;
oooo,u->name= k,v->name= j,varmap[j]= v-varhead,varmap[k]= u-varhead;
oo,j= u->aux,k= v->aux;
if(j*k<0)oo,u->aux= -j,v->aux= -k;
o,j= u->proj,k= u->elt;
oo,u->proj= v->proj,u->elt= v->elt;
o,v->proj= j,v->elt= k;
o,v->taut= addr_(node_(u->taut)->lo);

/*:142*/
#line 2905 "./bdd15.w"
;
}

/*:131*/
#line 3122 "./bdd15.w"


/*:143*//*146:*/
#line 3155 "./bdd15.w"

void sift(var*v){
register int pass,bestscore,origscore,swaps;
var*u= v;
double worstratio,saferatio;
unsigned long long oldmems= mems,oldrmems= rmems,oldzmems= zmems;
bestscore= origscore= totalnodes;
worstratio= saferatio= 1.0;
swaps= pass= 0;
if(o,totalvars-v->aux<v->aux)goto siftdown;
siftup:/*147:*/
#line 3180 "./bdd15.w"

while(o,u->up){
swaps++,swap(u->up,u);
u= u->up;
if(bestscore> totalnodes){
bestscore= totalnodes;
if(saferatio<worstratio)saferatio= worstratio;
worstratio= 1.0;
}else if(totalnodes> worstratio*bestscore)
worstratio= (double)totalnodes/bestscore;
}
if(pass==0){
while(u!=v){
o,swaps++,swap(u,u->down);
u= u->down;
}
pass= 1,worstratio= 1.0;
goto siftdown;
}
while(totalnodes!=bestscore){
swaps++,swap(u,u->down);
u= u->down;
}
goto wrapup;

/*:147*/
#line 3165 "./bdd15.w"
;
siftdown:/*148:*/
#line 3205 "./bdd15.w"

while(o,u->down){
swaps++,swap(u,u->down);
u= u->down;
if(bestscore> totalnodes){
bestscore= totalnodes;
if(saferatio<worstratio)saferatio= worstratio;
worstratio= 1.0;
}else if(totalnodes> worstratio*bestscore)
worstratio= (double)totalnodes/bestscore;
}
if(pass==0){
while(u!=v){
o,swaps++,swap(u->up,u);
u= u->up;
}
pass= 1,worstratio= 1.0;
goto siftup;
}
while(totalnodes!=bestscore){
o,swaps++,swap(u->up,u);
u= u->up;
}
goto wrapup;

/*:148*/
#line 3166 "./bdd15.w"
;
wrapup:if(verbose&4096)printf(
"sift x%d (%d->%d), %d saved, %.3f safe, %d swaps, (%llu,0,%llu) mems\n",
u->name,v-varhead,u-varhead,origscore-bestscore,saferatio,swaps,
mems-oldmems,zmems-oldzmems);
oo,u->aux= -u->aux;
}

/*:146*//*149:*/
#line 3241 "./bdd15.w"

void siftall(void){
register var*v;
reorder_init();
for(v= firstvar;v;){
if(o,v->aux<0){
v= v->down;
continue;
}
sift(v);
}
reorder_fin();
}

/*:149*//*153:*/
#line 3292 "./bdd15.w"

void collect_garbage(int level){
register int k;
var*v;
node*p;
last_ditch= 0;
if(!level)cache_purge();
else{
if(verbose&512)printf("clearing the cache\n");
for(k= 0;k<cachepages;k++)free_page(page_(cachepage[k]));
cachepages= 0;
}
if(verbose&512)printf("collecting garbage (%d/%d)\n",deadnodes,totalnodes);
for(v= varhead;v<topofvars;v++)table_purge(v);
}

/*:153*//*156:*/
#line 3318 "./bdd15.w"

void attempt_repairs(void){
register int j,k;
if(last_ditch){
printf("sorry --- there's not enough memory; we have to quit!\n");
/*7:*/
#line 160 "./bdd15.w"

printf("Job stats:\n");
printf("  %llu mems plus %llu rmems plus %llu zmems (%.4g)\n",
mems,rmems,zmems,mems+rfactor*rmems+zfactor*zmems);
/*18:*/
#line 373 "./bdd15.w"

j= nodeptr-(node*)mem;k= topofmem-pageptr;
printf("  %llu bytes of memory (%d nodes, %d pages)\n",
((long long)j)*sizeof(node)+((long long)k)*sizeof(page),j,k);

/*:18*/
#line 164 "./bdd15.w"
;

/*:7*/
#line 3323 "./bdd15.w"
;
exit(-99);
}
if(verbose&512)printf("(making a last ditch attempt for space)\n");
collect_garbage(1);
cache_init();
last_ditch= 1;
}

/*:156*//*159:*/
#line 3345 "./bdd15.w"

void math_print(node*p){
var*v;
int k,s;
node*q,*r;
if(!p)return;
outcount++;
sprintf(buf,"/tmp/bdd15-out%d.m",outcount);
outfile= fopen(buf,"w");
if(!outfile){
fprintf(stderr,"I can't open file %s for writing!\n",buf);
exit(-71);
}
fprintf(outfile,"g0=0\ng1=1\n");
if(p> topsink){
mark(p);
for(s= 0,v= topofvars-1;v>=varhead;v--)
/*160:*/
#line 3369 "./bdd15.w"

{
for(k= 0;k<v->mask;k+= sizeof(addr)){
q= fetchnode(v,k);
if(q&&(q->xref+1)<0){
/*161:*/
#line 3379 "./bdd15.w"

fprintf(outfile,"g%x=Expand[",id(q));
r= node_(q->lo);
fprintf(outfile,"g%x+z*",id(r));
r= node_(q->hi);
fprintf(outfile,"g%x]\n",id(r));

/*:161*/
#line 3374 "./bdd15.w"
;
}
}
}

/*:160*/
#line 3362 "./bdd15.w"
;
unmark(p);
}
fprintf(outfile,"g%x\n",id(p));
fclose(outfile);
}

/*:159*/
#line 111 "./bdd15.w"


main(int argc,char*argv[])
{
/*19:*/
#line 378 "./bdd15.w"

register int j,k;

/*:19*//*113:*/
#line 2591 "./bdd15.w"

char*c,*cc;
node*p,*q,*r;
var*v;
int lhs;
int curop;

/*:113*/
#line 115 "./bdd15.w"
;
/*4:*/
#line 125 "./bdd15.w"

if(argc> 2||(file_given&&!(infile= fopen(argv[1],"r")))){
fprintf(stderr,"Usage: %s [commandfile]\n",argv[0]);
exit(-1);
}

/*:4*/
#line 116 "./bdd15.w"
;
/*6:*/
#line 135 "./bdd15.w"

gb_init_rand(0);

/*:6*//*10:*/
#line 186 "./bdd15.w"

if(sizeof(long long)!=8){
fprintf(stderr,"Sorry, I assume that sizeof(long long) is 8!\n");
exit(-2);
}

/*:10*//*13:*/
#line 283 "./bdd15.w"

botsink= (node*)mem;
topsink= botsink+1;
o,botsink->lo= botsink->hi= addr_(botsink);
o,topsink->lo= topsink->hi= addr_(topsink);
oo,botsink->xref= topsink->xref= 0;
totalnodes= 2;
nodeptr= topsink+1;
pageptr= topofmem;

/*:13*//*45:*/
#line 973 "./bdd15.w"

cache_init();

/*:45*//*63:*/
#line 1341 "./bdd15.w"

if(sizeof(node)!=16){
fprintf(stderr,"Sorry, I assume that sizeof(node) is 16!\n");
exit(-3);
}

/*:63*/
#line 117 "./bdd15.w"
;
while(1)/*108:*/
#line 2503 "./bdd15.w"

{
/*109:*/
#line 2515 "./bdd15.w"

#if debugging&includesanity
if(verbose&8192)sanity_check();
#endif
if(totalnodes>=toobig)/*151:*/
#line 3267 "./bdd15.w"

{
if(verbose&(4096+8192))
printf("autosifting (totalnodes=%d, trigger=%.2f, toobig=%d)\n",
totalnodes,trigger,toobig);
siftall();
if(trigger*totalnodes>=memsize)toobig= memsize;
else toobig= trigger*totalnodes;
}

/*:151*/
#line 2519 "./bdd15.w"
;
if(verbose&1024)show_stats();

/*:109*/
#line 2505 "./bdd15.w"
;
/*111:*/
#line 2528 "./bdd15.w"

if(infile){
if(!fgets(buf,bufsize,infile)){
if(file_given)goto alldone;

fclose(infile);
infile= NULL;
continue;
}
if(verbose&64)printf("> %s",buf);
}else while(1){
printf("> ");fflush(stdout);
if(fgets(buf,bufsize,stdin))break;
freopen("/dev/tty","r",stdin);
}

/*:111*/
#line 2506 "./bdd15.w"
;
/*112:*/
#line 2561 "./bdd15.w"

rescan:for(c= buf;*c==' ';c++);
switch(*c++){
case'\n':if(!infile)printf("(Type `quit' to exit the program.)\n");
case'#':continue;
case'!':printf(buf+1);continue;
case'b':/*144:*/
#line 3124 "./bdd15.w"

if(totalvars){
reorder_init();
for(v= firstvar->down;v;){
if(oo,v->name> v->up->name)v= v->down;
else{
swap(v->up,v);
if(v->up->up)v= v->up;
else v= v->down;
}
}
reorder_fin();
}

/*:144*/
#line 2567 "./bdd15.w"
;continue;
case'C':print_cache();continue;
case'f':/*118:*/
#line 2648 "./bdd15.w"

getkf;lhs= k;
passblanks;
if(*c++!='=')reporterror;
/*119:*/
#line 2662 "./bdd15.w"

passblanks;
switch(*c++){
case'e':getkv;p= node_(varhead[varmap[k]].elt);break;
case'x':getkv;p= projection(varmap[k]);break;
case'f':getkf;p= f[k];checknull(p);break;
case'c':p= getconst(*c++);if(!p)reporterror;break;
case'~':p= tautology;curop= 2;goto second;

case'.':/*126:*/
#line 2764 "./bdd15.w"

if(o,f[lhs]){
deref(f[lhs]);
o,f[lhs]= NULL;
}

/*:126*/
#line 2671 "./bdd15.w"
;continue;
default:reporterror;
}

/*:119*/
#line 2652 "./bdd15.w"
;
/*121:*/
#line 2696 "./bdd15.w"

passblanks;
switch(*c++){
case'+':curop= 0;break;
case'&':curop= 1;break;
case'>':curop= 2;break;
case'<':curop= 4;break;
case'*':curop= 5;break;
case'^':curop= 6;break;
case'|':curop= 7;break;
case'"':curop= 8;break;
case'/':curop= 9;break;
case'%':curop= 10;break;
case'_':curop= 11;break;
case'?':curop= 16;break;
case'.':curop= 17;break;
case'!':curop= 19;break;
case'\n':curop= 7,q= p,c--;goto fourth;
case'S':getk;r= symfunc_top(p,k);goto assignit;
default:reporterror;
}

/*:121*/
#line 2653 "./bdd15.w"
;
second:/*122:*/
#line 2718 "./bdd15.w"

passblanks;
switch(*c++){
case'e':getkv;q= node_(varhead[varmap[k]].elt);break;
case'x':getkv;q= projection(varmap[k]);break;
case'f':getkf;q= f[k];checknull(q);break;
case'c':q= getconst(*c++);if(!q)reporterror;break;
default:reporterror;
}

/*:122*/
#line 2654 "./bdd15.w"
;
third:/*123:*/
#line 2728 "./bdd15.w"


passblanks;
if(curop==1&&*c=='&')curop= 18;
if(curop<=maxbinop)r= NULL;
else{
if(*c++!=ternopname2[curop-16][0])reporterror;
passblanks;
switch(*c++){
case'e':getkv;r= node_(varhead[varmap[k]].elt);break;
case'x':getkv;r= projection(varmap[k]);break;
case'f':getkf;r= f[k];checknull(r);break;
case'c':r= getconst(*c++);if(!r)reporterror;break;
default:reporterror;
}
}

/*:123*/
#line 2655 "./bdd15.w"
;
fourth:/*124:*/
#line 2747 "./bdd15.w"

passblanks;
if(*c!='\n'&&*c!='#'){
reportjunk:c++;
reporterror;
}
if(curop<=maxbinop)r= binary_top(curop,p,q);
else r= ternary_top(curop,p,q,r);

/*:124*/
#line 2656 "./bdd15.w"
;
assignit:/*125:*/
#line 2760 "./bdd15.w"

if(o,f[lhs])deref(f[lhs]);
o,f[lhs]= r;

/*:125*/
#line 2657 "./bdd15.w"
;

/*:118*/
#line 2569 "./bdd15.w"
;continue;
case'i':/*114:*/
#line 2604 "./bdd15.w"

if(infile)
printf("Sorry --- you can't include one file inside of another.\n");
else{
for(;isgraph(*c);c++);
passblanks;
for(cc= c;isgraph(*c);c++);
*c= '\0';
if(!(infile= fopen(cc,"r")))
printf("Sorry --- I couldn't open file `%s'!\n",cc);
}

/*:114*/
#line 2570 "./bdd15.w"
;continue;
case'l':getk;leasesonlife= k;continue;
case'm':/*157:*/
#line 3336 "./bdd15.w"

getkf;
math_print(f[k]);
fprintf(stderr,"(generating function for f%d written to %s)\n",k,buf);

/*:157*/
#line 2572 "./bdd15.w"
;continue;
case'o':/*116:*/
#line 2635 "./bdd15.w"

getkf;
sprintf(buf,"/tmp/f%d.zdd",k);
freopen(buf,"w",stdout);
print_function(f[k]);
freopen("/dev/tty","w",stdout);

/*:116*/
#line 2573 "./bdd15.w"
;continue;
case'O':/*117:*/
#line 2642 "./bdd15.w"

for(v= varhead;v<topofvars;v++)printf(" x%d",v->name);
printf("\n");

/*:117*/
#line 2574 "./bdd15.w"
;continue;
case'p':/*115:*/
#line 2624 "./bdd15.w"

if(*c=='p'){
c++;getkf;
printf("p%d:",k);
print_profile(f[k]);
}else{
getkf;
printf("f%d=",k);
print_function(f[k]);
}

/*:115*/
#line 2575 "./bdd15.w"
;continue;
case'P':print_base(0);continue;
case'q':goto alldone;
case'r':/*150:*/
#line 3261 "./bdd15.w"

getk;
trigger= k/100.0;
if(trigger*totalnodes>=memsize)toobig= memsize;
else toobig= trigger*totalnodes;

/*:150*/
#line 2578 "./bdd15.w"
;continue;
case's':/*128:*/
#line 2792 "./bdd15.w"

getkv;v= &varhead[varmap[k]];
reorder_init();
if(v->up)swap(v->up,v);
reorder_fin();

/*:128*/
#line 2579 "./bdd15.w"
;continue;
case'S':if(isdigit(*c))/*145:*/
#line 3142 "./bdd15.w"

{
getkv;v= &varhead[varmap[k]];
reorder_init();
sift(v);
reorder_fin();
}

/*:145*/
#line 2580 "./bdd15.w"

else siftall();continue;
case't':/*127:*/
#line 2774 "./bdd15.w"

getkv;
tvar= &varhead[k+1];

/*:127*/
#line 2582 "./bdd15.w"
;continue;
case'v':getk;verbose= k;continue;
case'V':verbose= -1;continue;
case'x':if(!totvars){getk;createvars(k);}else reporterror;continue;
case'$':show_stats();continue;
default:reporterror;
}
nextcommand:continue;

/*:112*/
#line 2507 "./bdd15.w"
;
}

/*:108*/
#line 118 "./bdd15.w"
;
alldone:/*7:*/
#line 160 "./bdd15.w"

printf("Job stats:\n");
printf("  %llu mems plus %llu rmems plus %llu zmems (%.4g)\n",
mems,rmems,zmems,mems+rfactor*rmems+zfactor*zmems);
/*18:*/
#line 373 "./bdd15.w"

j= nodeptr-(node*)mem;k= topofmem-pageptr;
printf("  %llu bytes of memory (%d nodes, %d pages)\n",
((long long)j)*sizeof(node)+((long long)k)*sizeof(page),j,k);

/*:18*/
#line 164 "./bdd15.w"
;

/*:7*/
#line 119 "./bdd15.w"
;
exit(0);
}

/*:3*/
