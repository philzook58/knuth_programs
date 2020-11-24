#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define O "%"
#define mod % \

#define max_level 5000
#define max_cols 100000
#define max_nodes 10000000
#define max_inx 200000
#define max_cache 2000000000 \

#define loghashsize 30
#define hashsize (1<<loghashsize) 
#define bufsize (9*max_cols+3)  \

#define show_basics 1
#define show_choices 2
#define show_details 4
#define show_hits 8
#define show_secondary_details 16
#define show_profile 128
#define show_full_state 256
#define show_tots 512
#define show_warnings 1024 \

#define len itm
#define aux color \

#define root 0 \

#define sanity_checking 0 \

#define panic(m) {fprintf(stderr,""O"s!\n"O"d: "O".99s\n",m,p,buf) ;exit(-666) ;} \

#define overflow(p,pname) {fprintf(stderr, \
"Overflow in cache memory ("O"s="O"d)!\n",pname,p) ;exit(-667) ;} \

#define signbit 0x8000000000000000 \

#define hashmask ((1<<loghashsize) -1)  \

/*2:*/
#line 64 "./dlx6.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include "gb_flip.h"
typedef unsigned int uint;
typedef unsigned long long ullng;
/*6:*/
#line 276 "./dlx6.w"

typedef struct node_struct{
int up,down;
int itm;
int color;
}node;

/*:6*//*7:*/
#line 298 "./dlx6.w"

typedef struct itm_struct{
char name[8];
int prev,next;
int sig,offset;
}item;

/*:7*//*23:*/
#line 557 "./dlx6.w"

typedef struct inx_struct{
int hash;
short code;
char shift;
char orig;
}inx;

/*:23*//*24:*/
#line 568 "./dlx6.w"

typedef struct hash_struct{
int sig;
int zddref;
}hashentry;

/*:24*/
#line 72 "./dlx6.w"
;
/*3:*/
#line 160 "./dlx6.w"

int random_seed= 0;
int randomizing;
int vbose= show_basics+show_warnings;
int spacing;
int show_choices_max= 1000000;
int show_choices_gap= 1000000;

int show_levels_max= 1000000;
int maxl= 0;
char buf[bufsize];
ullng count;
ullng options;
ullng imems,mems;
ullng updates;
ullng cleansings;
ullng bytes;
ullng nodes;
ullng thresh= 10000000000;
ullng delta= 10000000000;
ullng maxcount= 0xffffffffffffffff;
ullng maxzdd= 0xffffffffffffffff;
ullng timeout= 0x1fffffffffffffff;
FILE*shape_file;
char*shape_name;

/*:3*//*8:*/
#line 305 "./dlx6.w"

node nd[max_nodes];
int last_node;
item cl[max_cols+2];
int second= max_cols;
int last_itm;

/*:8*//*25:*/
#line 579 "./dlx6.w"

inx siginx[max_inx];
int sigptr;
int sigsiz;
hashentry*hash;
int hashcount;
ullng*cache;
unsigned int cacheptr;
unsigned int oldcacheptr;
unsigned int zddnodes= 2;
unsigned int memos;
unsigned int goodmemos;
ullng hits;
char usedcolor[256],colormap[256];

/*:25*//*37:*/
#line 841 "./dlx6.w"

int level;
int choice[max_level];
int savez[max_level];
ullng profile[max_level];
ullng entrycount[max_level];
int hashloc[max_level];

/*:37*/
#line 73 "./dlx6.w"
;
/*10:*/
#line 322 "./dlx6.w"

void print_option(int p,FILE*stream){
register int k,q,cc;
if(p<last_itm||p>=last_node||nd[p].itm<=0){
fprintf(stderr,"Illegal option "O"d!\n",p);
return;
}
for(q= p,cc= nd[q].itm;;){
fprintf(stream," "O".8s",cl[cc].name);
if(nd[q].color)
fprintf(stream,":"O"c",nd[q].color> 0?siginx[cl[cc].sig+nd[q].color].orig:
siginx[cl[cc].sig+nd[cc].color].orig);
q++;
cc= nd[q].itm;
if(cc<=0)q= nd[q].up,cc= nd[q].itm;
if(q==p)break;
}
for(q= nd[nd[p].itm].down,k= 1;q!=p;k++){
if(q==nd[p].itm){
fprintf(stream," (?)\n");return;
}else q= nd[q].down;
}
fprintf(stream," ("O"d of "O"d)\n",k,nd[nd[p].itm].len);
}

void prow(int p){
print_option(p,stderr);
}

/*:10*//*11:*/
#line 353 "./dlx6.w"

void print_itm(int c){
register int p;
if(c<root||c>=last_itm){
fprintf(stderr,"Illegal item "O"d!\n",c);
return;
}
if(c<second)
fprintf(stderr,"Item "O".8s, length "O"d, neighbors "O".8s and "O".8s:\n",
cl[c].name,nd[c].len,cl[cl[c].prev].name,cl[cl[c].next].name);
else fprintf(stderr,"Item "O".8s, length "O"d:\n",cl[c].name,nd[c].len);
for(p= nd[c].down;p>=last_itm;p= nd[p].down)prow(p);
}

/*:11*//*12:*/
#line 372 "./dlx6.w"

void sanity(void){
register int k,p,q,pp,qq,t;
for(q= root,p= cl[q].next;;q= p,p= cl[p].next){
if(cl[p].prev!=q)fprintf(stderr,"Bad prev field at itm "O".8s!\n",
cl[p].name);
if(p==root)break;
/*13:*/
#line 383 "./dlx6.w"

for(qq= p,pp= nd[qq].down,k= 0;;qq= pp,pp= nd[pp].down,k++){
if(nd[pp].up!=qq)fprintf(stderr,"Bad up field at node "O"d!\n",pp);
if(pp==p)break;
if(nd[pp].itm!=p)fprintf(stderr,"Bad itm field at node "O"d!\n",pp);
}
if(nd[p].len!=k)fprintf(stderr,"Bad len field in item "O".8s!\n",
cl[p].name);

/*:13*/
#line 379 "./dlx6.w"
;
}
}

/*:12*//*39:*/
#line 874 "./dlx6.w"

void cover(int c){
register int cc,l,r,rr,nn,uu,dd,t;
o,l= cl[c].prev,r= cl[c].next;
oo,cl[l].next= r,cl[r].prev= l;
updates++;
for(o,rr= nd[c].down;rr>=last_itm;o,rr= nd[rr].down)
for(nn= rr+1;nn!=rr;){
o,cc= nd[nn].itm;
if(cc<=0){
o,nn= nd[nn].up;continue;
}
if(nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
oo,nd[uu].down= dd,nd[dd].up= uu;
}
updates++;
o,t= nd[cc].len-1;
o,nd[cc].len= t;
if(t==0&&cc>=second){
o,l= cl[cc].prev,r= cl[cc].next;
oo,cl[l].next= r,cl[r].prev= l;
}
nn++;
}
}

/*:39*//*40:*/
#line 904 "./dlx6.w"

void uncover(int c){
register int cc,l,r,rr,nn,uu,dd,t;
for(o,rr= nd[c].up;rr>=last_itm;o,rr= nd[rr].up)
for(nn= rr-1;nn!=rr;){
o,cc= nd[nn].itm;
if(cc<=0){
o,nn= nd[nn].down;continue;
}
if(nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
oo,nd[uu].down= nd[dd].up= nn;
}
o,t= nd[cc].len+1;
o,nd[cc].len= t;
if(t==1&&cc>=second){
o,l= cl[cc].prev,r= cl[cc].next;
oo,cl[l].next= cl[r].prev= cc;
}
nn--;
}
o,l= cl[c].prev,r= cl[c].next;
oo,cl[l].next= cl[r].prev= c;
}

/*:40*//*43:*/
#line 977 "./dlx6.w"

void purify(int p){
register int cc,rr,nn,uu,dd,t,x,tt;
o,cc= nd[p].itm,x= nd[p].color;
o,nd[cc].color= x;
o,tt= nd[cc].len;
cleansings++;
for(o,rr= nd[cc].down;rr>=last_itm;o,rr= nd[rr].down){
if(rr==p)fprintf(stderr,"confusion!\n");
if(o,nd[rr].color!=x){
tt--;
for(nn= rr+1;nn!=rr;){
o,cc= nd[nn].itm;
if(cc<=0){
o,nn= nd[nn].up;continue;
}
if(nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
oo,nd[uu].down= dd,nd[dd].up= uu;
}
updates++;
o,t= nd[cc].len-1;
o,nd[cc].len= t;
if(t==0&&cc>=second){
register int l,r;
o,l= cl[cc].prev,r= cl[cc].next;
oo,cl[l].next= r,cl[r].prev= l;
}
nn++;
}
}else cleansings++,o,nd[rr].color= -1;
}
if(tt> 0)o,cc= nd[p].itm,nd[cc].len= tt;
else{
register int l,r;
o,cc= nd[p].itm,nd[cc].len= -1;
o,l= cl[cc].prev,r= cl[cc].next;
oo,cl[l].next= r,cl[r].prev= l;
}
}

/*:43*//*44:*/
#line 1021 "./dlx6.w"

void unpurify(int p){
register int cc,rr,nn,uu,dd,t,x,tt;
oo,cc= nd[p].itm,x= nd[p].color,nd[cc].color= 0;
o,tt= nd[cc].len;
if(tt<0){
register int l,r;
tt= 0;
o,l= cl[cc].prev,r= cl[cc].next;
oo,cl[l].next= cl[r].prev= cc;
}
for(o,rr= nd[cc].up;rr>=last_itm;o,rr= nd[rr].up){
if(rr==p)fprintf(stderr,"confusion!\n");
if(o,nd[rr].color<0)o,nd[rr].color= x;
else{
tt++;
for(nn= rr-1;nn!=rr;){
o,cc= nd[nn].itm;
if(cc<=0){
o,nn= nd[nn].down;continue;
}
if(nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
oo,nd[uu].down= nd[dd].up= nn;
}
o,t= nd[cc].len+1;
o,nd[cc].len= t;
if(t==1&&cc>=second){
register int l,r;
o,l= cl[cc].prev,r= cl[cc].next;
oo,cl[l].next= cl[r].prev= cc;
}
nn--;
}
}
}
o,cc= nd[p].itm,nd[cc].len= tt;
}

/*:44*//*48:*/
#line 1133 "./dlx6.w"

void print_state(void){
register int l;
fprintf(stderr,"Current state (level "O"d):\n",level);
for(l= 0;l<level;l++){
print_option(choice[l],stderr);
if(l>=show_levels_max){
fprintf(stderr," ...\n");
break;
}
}
fprintf(stderr," "O"lld solutions, "O"lld hits, "O"lld mems,",
count,hits,mems);
fprintf(stderr," and max level "O"d so far.\n",maxl);
}

/*:48*//*49:*/
#line 1169 "./dlx6.w"

void print_progress(void){
register int l,k,d,c,p;
register double f,fd;
fprintf(stderr," after "O"lld mems: "O"lld sols, "O"lld hits,",mems,count,hits);
for(f= 0.0,fd= 1.0,l= 0;l<level;l++){
c= nd[choice[l]].itm,d= nd[c].len;
for(k= 1,p= nd[c].down;p!=choice[l];k++,p= nd[p].down);
fd*= d,f+= (k-1)/fd;
fprintf(stderr," "O"c"O"c",
k<10?'0'+k:k<36?'a'+k-10:k<62?'A'+k-36:'*',
d<10?'0'+d:d<36?'a'+d-10:d<62?'A'+d-36:'*');
if(l>=show_levels_max){
fprintf(stderr,"...");
break;
}
}
fprintf(stderr," "O".5f\n",f+0.5/fd);
}

/*:49*/
#line 74 "./dlx6.w"
;
main(int argc,char*argv[]){
register int cc,i,j,k,p,pp,q,r,t,cur_node,best_itm,znode,zsol,optionno,hit;
/*4:*/
#line 189 "./dlx6.w"

for(j= argc-1,k= 0;j;j--)switch(argv[j][0]){
case'v':k|= (sscanf(argv[j]+1,""O"d",&vbose)-1);break;
case'm':k|= (sscanf(argv[j]+1,""O"d",&spacing)-1);break;
case's':k|= (sscanf(argv[j]+1,""O"d",&random_seed)-1),randomizing= 1;break;
case'd':k|= (sscanf(argv[j]+1,""O"lld",&delta)-1),thresh= delta;break;
case'c':k|= (sscanf(argv[j]+1,""O"d",&show_choices_max)-1);break;
case'C':k|= (sscanf(argv[j]+1,""O"d",&show_levels_max)-1);break;
case'l':k|= (sscanf(argv[j]+1,""O"d",&show_choices_gap)-1);break;
case't':k|= (sscanf(argv[j]+1,""O"lld",&maxcount)-1);break;
case'T':k|= (sscanf(argv[j]+1,""O"lld",&timeout)-1);break;
case'Z':k|= (sscanf(argv[j]+1,""O"lld",&maxzdd)-1);break;
case'S':shape_name= argv[j]+1,shape_file= fopen(shape_name,"w");
if(!shape_file)
fprintf(stderr,"Sorry, I can't open file `"O"s' for writing!\n",
shape_name);
break;
default:k= 1;
}
if(k){
fprintf(stderr,"Usage: "O"s [v<n>] [m<n>] [s<n>] [d<n>]"
" [c<n>] [C<n>] [l<n>] [t<n>] [T<n>] [S<bar>] [Z<n] < foo.dlx\n",
argv[0]);
exit(-1);
}
if(randomizing)gb_init_rand(random_seed);
else gb_init_rand(0);

/*:4*/
#line 77 "./dlx6.w"
;
/*14:*/
#line 397 "./dlx6.w"

if(max_nodes<=2*max_cols){
fprintf(stderr,"Recompile me: max_nodes must exceed twice max_cols!\n");
exit(-999);
}
while(1){
if(!fgets(buf,bufsize,stdin))break;
if(o,buf[p= strlen(buf)-1]!='\n')panic("Input line way too long");
for(p= 0;o,isspace(buf[p]);p++);
if(buf[p]=='|'||!buf[p])continue;
last_itm= 1;
break;
}
if(!last_itm)panic("No items");
for(;o,buf[p];){
for(j= 0;j<8&&(o,!isspace(buf[p+j]));j++){
if(buf[p+j]==':'||buf[p+j]=='|')
panic("Illegal character in item name");
o,cl[last_itm].name[j]= buf[p+j];
}
if(j==8&&!isspace(buf[p+j]))panic("Item name too long");
/*15:*/
#line 435 "./dlx6.w"

for(k= 1;o,strncmp(cl[k].name,cl[last_itm].name,8);k++);
if(k<last_itm)panic("Duplicate item name");

/*:15*/
#line 418 "./dlx6.w"
;
/*16:*/
#line 439 "./dlx6.w"

if(last_itm> max_cols)panic("Too many items");
oo,cl[last_itm-1].next= last_itm,cl[last_itm].prev= last_itm-1;

o,nd[last_itm].up= nd[last_itm].down= last_itm;
last_itm++;

/*:16*/
#line 419 "./dlx6.w"
;
for(p+= j+1;o,isspace(buf[p]);p++);
if(buf[p]=='|'){
if(second!=max_cols)panic("Item name line contains | twice");
second= last_itm;
for(p++;o,isspace(buf[p]);p++);
}
}
if(second==max_cols)second= last_itm;
oo,cl[last_itm].prev= last_itm-1,cl[last_itm-1].next= last_itm;
oo,cl[second].prev= last_itm,cl[last_itm].next= second;

oo,cl[root].prev= second-1,cl[second-1].next= root;
last_node= last_itm;


/*:14*/
#line 78 "./dlx6.w"
;
/*17:*/
#line 449 "./dlx6.w"

while(1){
if(!fgets(buf,bufsize,stdin))break;
if(o,buf[p= strlen(buf)-1]!='\n')panic("Option line too long");
for(p= 0;o,isspace(buf[p]);p++);
if(buf[p]=='|'||!buf[p])continue;
i= last_node;
for(pp= 0;buf[p];){
for(j= 0;j<8&&(o,!isspace(buf[p+j]))&&buf[p+j]!=':';j++)
o,cl[last_itm].name[j]= buf[p+j];
if(!j)panic("Empty item name");
if(j==8&&!isspace(buf[p+j])&&buf[p+j]!=':')
panic("Item name too long");
if(j<8)o,cl[last_itm].name[j]= '\0';
/*18:*/
#line 490 "./dlx6.w"

for(k= 0;o,strncmp(cl[k].name,cl[last_itm].name,8);k++);
if(k==last_itm)panic("Unknown item name");
if(o,nd[k].aux>=i)panic("Duplicate item name in this option");
last_node++;
if(last_node==max_nodes)panic("Too many nodes");
o,nd[last_node].itm= k;
if(k<second)pp= 1;
o,t= nd[k].len+1;
/*19:*/
#line 512 "./dlx6.w"

o,nd[k].len= t;
nd[k].aux= last_node;
if(!randomizing){
o,r= nd[k].up;
ooo,nd[r].down= nd[k].up= last_node,nd[last_node].up= r,nd[last_node].down= k;
}else{
mems+= 4,t= gb_unif_rand(t);
for(o,r= k;t;o,r= nd[r].down,t--);
ooo,q= nd[r].up,nd[q].down= nd[r].up= last_node;
o,nd[last_node].up= q,nd[last_node].down= r;
}

/*:19*/
#line 499 "./dlx6.w"
;

/*:18*/
#line 463 "./dlx6.w"
;
if(buf[p+j]!=':')o,nd[last_node].color= 0;
else if(k>=second){
if((o,isspace(buf[p+j+1]))||(o,!isspace(buf[p+j+2])))
panic("Color must be a single character");
o,nd[last_node].color= (unsigned char)buf[p+j+1];
p+= 2;
}else panic("Primary item must be uncolored");
for(p+= j+1;o,isspace(buf[p]);p++);
}
if(!pp){
if(vbose&show_warnings)
fprintf(stderr,"Option ignored (no primary items): "O"s",buf);
while(last_node> i){
/*20:*/
#line 525 "./dlx6.w"

o,k= nd[last_node].itm;
oo,nd[k].len--,nd[k].aux= i-1;
o,q= nd[last_node].up,r= nd[last_node].down;
oo,nd[q].down= r,nd[r].up= q;

/*:20*/
#line 477 "./dlx6.w"
;
last_node--;
}
}else{
o,nd[i].down= last_node;
last_node++;
if(last_node==max_nodes)panic("Too many nodes");
options++;
o,nd[last_node].up= i+1;
o,nd[last_node].itm= -options;
}
}

/*:17*/
#line 79 "./dlx6.w"
;
/*27:*/
#line 616 "./dlx6.w"

hash= (hashentry*)malloc(hashsize*sizeof(hashentry));
if(!hash){
fprintf(stderr,"Couldn't allocate the hash table (hashsize="O"d)!\n",
hashsize);
exit(-68);
}
cache= (ullng*)malloc(max_cache*sizeof(ullng));
if(!cache){
fprintf(stderr,"Couldn't allocate the cache memory (max_cache="O"d)!\n",
max_cache);
exit(-69);
}
q= 1,r= 0;
for(k= last_itm-1;k;k--)
if(k<second)/*28:*/
#line 635 "./dlx6.w"

{
if(r==63)q++,r= 0;
o,siginx[sigptr].shift= r,siginx[sigptr].code= 1;
mems+= 4,siginx[sigptr].hash= gb_next_rand();
o,cl[k].sig= sigptr++,cl[k].offset= q;
if(sigptr>=max_inx)overflow(max_inx,"max_inx");
r++;
}

/*:28*/
#line 631 "./dlx6.w"

else/*29:*/
#line 645 "./dlx6.w"

{
if(o,nd[k].down==k){
register l,r;
o,l= cl[k].prev,r= cl[k].next;
oo,cl[l].next= r,cl[r].prev= l;
continue;
}
o,nd[k].color= 0;
cc= 1;
for(p= nd[k].down;p> k;o,p= nd[p].down){
o,i= nd[p].color;
if(i){
o,t= usedcolor[i];
if(!t)oo,colormap[cc]= i,usedcolor[i]= cc++;
o,nd[p].color= usedcolor[i];
}
}
for(t= 1;cc>=(1<<t);t++);

if(sigptr+t>=max_inx)overflow(max_inx,"max_inx");
if(r+t>=63)q++,r= 0;
for(i= 0;i<cc;i++){
o,siginx[sigptr+i].shift= r,siginx[sigptr+i].code= 1+i;
oo,siginx[sigptr+i].orig= colormap[i],usedcolor[colormap[i]]= 0;
mems+= 4,siginx[sigptr+i].hash= gb_next_rand();
o,cl[k].sig= sigptr,cl[k].offset= q;
}
sigptr+= cc,r+= t;
}

/*:29*/
#line 632 "./dlx6.w"
;
sigsiz= q+1;

/*:27*/
#line 80 "./dlx6.w"
;
if(vbose&show_basics)
/*21:*/
#line 531 "./dlx6.w"

fprintf(stderr,
"("O"lld options, "O"d+"O"d items, "O"d entries successfully read)\n",
options,second-1,last_itm-second,last_node-last_itm);

/*:21*/
#line 82 "./dlx6.w"
;
if(vbose&show_tots)
/*22:*/
#line 540 "./dlx6.w"

{
fprintf(stderr,"Item totals:");
for(k= 1;k<last_itm;k++){
if(k==second)fprintf(stderr," |");
fprintf(stderr," "O"d",nd[k].len);
}
fprintf(stderr,"\n");
}

/*:22*/
#line 84 "./dlx6.w"
;
imems= mems,mems= 0;
/*36:*/
#line 801 "./dlx6.w"

level= 0;
forward:nodes++;
if(vbose&show_profile)profile[level]++;
if(sanity_checking)sanity();
/*38:*/
#line 849 "./dlx6.w"

if(delta&&(mems>=thresh)){
thresh+= delta;
if(vbose&show_full_state)print_state();
else print_progress();
}
if(mems>=timeout){
fprintf(stderr,"TIMEOUT!\n");timeout= 0;
}

/*:38*/
#line 806 "./dlx6.w"
;
/*30:*/
#line 678 "./dlx6.w"

{
register ullng sigacc;
register unsigned int sighash;
register int off,sig,offset;
if(cacheptr+sigsiz>=max_cache)overflow(max_cache,"max_cache");
sighash= 0,off= 1,sigacc= 0;
for(o,k= cl[last_itm].prev;k!=last_itm;o,k= cl[k].prev)
/*32:*/
#line 704 "./dlx6.w"

{
if(o,nd[k].len==0)continue;
o,sig= cl[k].sig,offset= cl[k].offset;
while(off<offset){
o,cache[cacheptr+off]= sigacc|signbit;
off++,sigacc= 0;
}
o,sig+= nd[k].color;
o,sighash+= siginx[sig].hash;
sigacc+= ((long long)siginx[sig].code)<<siginx[sig].shift;
}

/*:32*/
#line 686 "./dlx6.w"
;
for(o,k= cl[root].prev;k!=root;o,k= cl[k].prev)
/*31:*/
#line 693 "./dlx6.w"

{
o,sig= cl[k].sig,offset= cl[k].offset;
while(off<offset){
o,cache[cacheptr+off]= sigacc|signbit;
off++,sigacc= 0;
}
o,sighash+= siginx[sig].hash;
sigacc+= 1LL<<siginx[sig].shift;
}

/*:31*/
#line 688 "./dlx6.w"
;
o,cache[cacheptr+off]= sigacc;
/*33:*/
#line 725 "./dlx6.w"

{
register int h,hh,s,l;
hh= (sighash>>(loghashsize-1))|1;
for(h= sighash&hashmask;;h= (h+hh)&hashmask){
o,s= hash[h].sig;
if(!s)break;
for(l= 0;;l++){
if(oo,cache[s+l]!=cache[cacheptr+1+l])break;
if(cache[s+l]&signbit)continue;
goto cache_hit;
}
}
if(++hashcount>=hashsize)overflow(hashsize,"hashsize");
o,hash[h].sig= cacheptr+1;
oldcacheptr= cacheptr,cacheptr+= q+1;
memos++;
o,hashloc[level]= h;
hit= 0;
goto cache_miss;
cache_hit:hit= 1+h;
cache_miss:;
}

/*:33*/
#line 690 "./dlx6.w"
;
}

/*:30*/
#line 807 "./dlx6.w"
;
if(hit)/*35:*/
#line 766 "./dlx6.w"

{
register ullng c;
o,znode= hash[hit-1].zddref;
if(vbose&show_hits)fprintf(stderr,
"Hit[%x] (zdd="O"x, sols="O"lld)\n",
hash[hit-1].sig-1,znode,cache[hash[hit-1].sig-1]);
if(znode){
o,c= cache[hash[hit-1].sig-1];
count+= c;
if(count>=maxcount)timeout= 0;
if(count<c)
fprintf(stderr,"(the solution count has overflowed!)\n");
}
hits++;
goto backdown;
}

/*:35*/
#line 808 "./dlx6.w"
;
o,entrycount[level]= count;
znode= 0;
/*45:*/
#line 1065 "./dlx6.w"

t= max_nodes;
if((vbose&show_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap){
fprintf(stderr,"Level "O"d:",level);
if(vbose&show_hits)fprintf(stderr,"["O"x]",oldcacheptr);
}
for(o,k= cl[root].next;t&&k!=root;o,k= cl[k].next){
if((vbose&show_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap)
fprintf(stderr," "O".8s("O"d)",cl[k].name,nd[k].len);
if(o,nd[k].len<=t){
if(nd[k].len<t)best_itm= k,t= nd[k].len,p= 1;
else{
p++;
if(randomizing&&(mems+= 4,!gb_unif_rand(p)))best_itm= k;
}
}
}
if((vbose&show_secondary_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap){
fprintf(stderr,";");
for(k= cl[last_itm].next;k!=last_itm;k= cl[k].next)
fprintf(stderr," "O".8s("O"d)",cl[k].name,nd[k].len);
}
if((vbose&show_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap)
fprintf(stderr," branching on "O".8s("O"d)\n",cl[best_itm].name,t);
if(shape_file){
fprintf(shape_file,""O"d "O".8s\n",t,cl[best_itm].name);
fflush(shape_file);
}

/*:45*/
#line 811 "./dlx6.w"
;
cover(best_itm);
oo,cur_node= choice[level]= nd[best_itm].down;
advance:if(cur_node==best_itm)goto backup;
if((vbose&show_choices)&&level<show_choices_max){
fprintf(stderr,"L"O"d:",level);
print_option(cur_node,stderr);
}
/*41:*/
#line 936 "./dlx6.w"

for(pp= cur_node+1;pp!=cur_node;){
o,cc= nd[pp].itm;
if(cc<=0)o,pp= nd[pp].up;
else{
if(cc<second||(o,nd[cc].len)){
if(!nd[pp].color)cover(cc);
else if(nd[pp].color> 0)purify(pp);
}
pp++;
}
}

/*:41*/
#line 819 "./dlx6.w"
;
if(o,cl[root].next==root)/*46:*/
#line 1098 "./dlx6.w"

{
nodes++;
hits++;
if(vbose&show_hits)fprintf(stderr,"Solution\n");
if(level+1> maxl){
if(level+1>=max_level){
fprintf(stderr,"Too many levels!\n");
exit(-5);
}
maxl= level+1;
}
if(vbose&show_profile)profile[level+1]++;
if(shape_file){
fprintf(shape_file,"sol\n");fflush(shape_file);
}
zsol= 1;
count++;
if(count>=maxcount)timeout= 0;
goto recover;
}

/*:46*/
#line 820 "./dlx6.w"
;
o,savez[level]= znode;
if(++level> maxl){
if(level>=max_level){
fprintf(stderr,"Too many levels!\n");
exit(-4);
}
maxl= level;
}
goto forward;
backup:uncover(best_itm);
if(znode)/*34:*/
#line 754 "./dlx6.w"

{
register int h;
o,h= hashloc[level];
o,hash[h].zddref= znode;
goodmemos++;
ooo,cache[hash[h].sig-1]= count-entrycount[level];
}

/*:34*/
#line 831 "./dlx6.w"
;
backdown:if(level==0)goto done;
level--;
oo,cur_node= choice[level],best_itm= nd[cur_node].itm;
o,zsol= znode,znode= savez[level];
recover:/*42:*/
#line 956 "./dlx6.w"

for(pp= cur_node-1;pp!=cur_node;){
o,cc= nd[pp].itm;
if(cc<=0)o,optionno= 1-cc,pp= nd[pp].down;
else{
if(cc<second||(o,nd[cc].len)){
if(!nd[pp].color)uncover(cc);
else if(nd[pp].color> 0)unpurify(pp);
}
pp--;
}
}

/*:42*/
#line 836 "./dlx6.w"
;
if(zsol)/*47:*/
#line 1120 "./dlx6.w"

{
if(spacing)
printf(""O"x: (~"O"d?"O"x:"O"x)\n",
zddnodes,optionno,znode,zsol);
znode= zddnodes++;
if(!zddnodes){
fprintf(stderr,"Too many ZDD nodes (4294967296)!\n");
exit(-232);
}
if(zddnodes> maxzdd)timeout= 0;
}

/*:47*/
#line 837 "./dlx6.w"
;
if(timeout==0)goto backup;
oo,cur_node= choice[level]= nd[cur_node].down;goto advance;

/*:36*/
#line 86 "./dlx6.w"
;
done:if(sanity_checking)sanity();
if(spacing)
printf(""O"x: (~0?0:"O"x)\n",zddnodes,znode);
if(vbose&show_tots)
/*22:*/
#line 540 "./dlx6.w"

{
fprintf(stderr,"Item totals:");
for(k= 1;k<last_itm;k++){
if(k==second)fprintf(stderr," |");
fprintf(stderr," "O"d",nd[k].len);
}
fprintf(stderr,"\n");
}

/*:22*/
#line 91 "./dlx6.w"
;
if(vbose&show_profile)/*50:*/
#line 1189 "./dlx6.w"

{
fprintf(stderr,"Profile:\n");
for(level= 0;level<=maxl;level++)
fprintf(stderr,""O"3d: "O"lld\n",
level,profile[level]);
}

/*:50*/
#line 92 "./dlx6.w"
;
if(vbose&show_basics){
fprintf(stderr,"Altogether "O"llu solution"O"s, "O"llu+"O"llu mems,",
count,count==1?"":"s",imems,mems);
bytes= last_itm*sizeof(item)+last_node*sizeof(node)+maxl*sizeof(int);
bytes+= sigptr*sizeof(inx)+cacheptr*sizeof(ullng);
bytes+= (2*hashcount> hashsize?hashsize:2*hashcount)*sizeof(hashentry);
fprintf(stderr," "O"llu updates, "O"llu cleansings,",
updates,cleansings);
fprintf(stderr," "O"llu bytes, "O"llu search nodes,",
bytes,nodes);
fprintf(stderr," "O"u ZDD node"O"s, "O"u+"O"u signatures, "O"llu hits.\n",
zddnodes==2?1:zddnodes,zddnodes==2?"":"s",memos-goodmemos,goodmemos+1,hits);

}
/*5:*/
#line 217 "./dlx6.w"

if(shape_file)fclose(shape_file);

/*:5*/
#line 107 "./dlx6.w"
;
}

/*:2*/
