#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define O "%"
#define mod % \

#define max_level 5000
#define max_cols 100000
#define max_nodes 10000000
#define bufsize (9*max_cols+3) 
#define sortbufsize 32 \

#define show_basics 1
#define show_choices 2
#define show_details 4
#define show_taxes 8
#define show_opt_costs 16
#define show_profile 128
#define show_full_state 256
#define show_tots 512
#define show_warnings 1024
#define maxk 15000 \

#define len itm
#define aux color
#define tax cost \

#define root 0 \

#define sanity_checking 0 \

#define panic(m) {fprintf(stderr,""O"s!\n"O"d: "O".99s\n",m,p,buf) ;exit(-666) ;} \

#define infcost ((ullng) -1)  \

#define explaining ((vbose&show_details) && \
level<show_choices_max&&level>=maxl-show_choices_gap)  \

/*2:*/
#line 84 "./dlx5.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
typedef unsigned int uint;
typedef unsigned long long ullng;
/*11:*/
#line 348 "./dlx5.w"

typedef struct node_struct{
int up,down;
int itm;
int color;
ullng cost;
}node;

/*:11*//*12:*/
#line 369 "./dlx5.w"

typedef struct itm_struct{
char name[8];
int prev,next;
}item;

/*:12*/
#line 91 "./dlx5.w"
;
/*6:*/
#line 192 "./dlx5.w"

int vbose= show_basics+show_opt_costs+show_warnings;
int spacing;
int show_choices_max= 1000000;
int show_choices_gap= 1000000;

int show_levels_max= 1000000;
int maxl= 0;
char buf[bufsize];
ullng sortbuf[sortbufsize];
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
ullng timeout= 0x1fffffffffffffff;
FILE*shape_file;
char*shape_name;
int kthresh= 1;
int lenthresh= 10;
int zgiven;
char Zchars[8];
int ppgiven;

/*:6*//*13:*/
#line 375 "./dlx5.w"

node*nd;
int last_node;
item cl[max_cols+2];
int second= max_cols;
int last_itm;
ullng totaltax;

/*:13*//*41:*/
#line 842 "./dlx5.w"

int level;
int choice[max_level];
ullng profile[max_level];
ullng partcost[max_level];
ullng coverthresh0[max_level],coverthresh[max_level];
ullng bestcost[maxk+1];
ullng cutoffcost;
ullng cumcost[7];
int solutionsize;

/*:41*/
#line 92 "./dlx5.w"
;
/*15:*/
#line 394 "./dlx5.w"

void print_option(int p,FILE*stream,ullng thresh){
register int c,j,k,q;
register ullng s;
c= nd[p].itm;
if(p<last_itm||p>=last_node||c<=0){
fprintf(stderr,"Illegal option "O"d!\n",p);
return;
}
for(q= p,s= 0;;){
fprintf(stream," "O".8s",cl[nd[q].itm].name);
if(nd[q].color)
fprintf(stream,":"O"c",nd[q].color> 0?nd[q].color:nd[nd[q].itm].color);
s+= nd[nd[q].itm].tax;
q++;
if(nd[q].itm<=0)q= nd[q].up;
if(q==p)break;
}
for(q= nd[c].down,k= 1;q!=p;k++){
if(q==c){
fprintf(stream," (?)");goto finish;
}else q= nd[q].down;
}
for(q= nd[c].down,j= 0;q>=last_itm;q= nd[q].down,j++)
if(nd[q].cost>=thresh)break;
fprintf(stream," ("O"d of "O"d)",k,j);
finish:if(s+nd[p].cost)fprintf(stream," $"O"llu ["O"llu]\n",
s+nd[p].cost,nd[p].cost);
else fprintf(stream,"\n");
}

void prow(int p){
print_option(p,stderr,infcost);
}

/*:15*//*16:*/
#line 431 "./dlx5.w"

void print_itm(int c){
register int p;
if(c<root||c>=last_itm){
fprintf(stderr,"Illegal item "O"d!\n",c);
return;
}
if(c<second)
fprintf(stderr,"Item "O".8s, neighbors "O".8s and "O".8s:\n",
cl[c].name,cl[cl[c].prev].name,cl[cl[c].next].name);
else fprintf(stderr,"Item "O".8s:\n",cl[c].name);
for(p= nd[c].down;p>=last_itm;p= nd[p].down)prow(p);
}

/*:16*//*17:*/
#line 450 "./dlx5.w"

void sanity(void){
register int k,p,q,pp,qq,t;
for(q= root,p= cl[q].next;;q= p,p= cl[p].next){
if(cl[p].prev!=q)
fprintf(stderr,"Bad prev field at itm "O".8s!\n",cl[p].name);
if(p==root)break;
/*18:*/
#line 461 "./dlx5.w"

for(qq= p,pp= nd[qq].down,k= 0;;qq= pp,pp= nd[pp].down,k++){
if(nd[pp].up!=qq)
fprintf(stderr,"Bad up field at node "O"d!\n",pp);
if(pp==p)break;
if(nd[pp].itm!=p)
fprintf(stderr,"Bad itm field at node "O"d!\n",pp);
if(qq> p&&nd[pp].cost<nd[qq].cost)
fprintf(stderr,"Costs out of order at node "O"d!\n",pp);
}
if(p<second&&nd[p].len!=k)fprintf(stderr,"Bad len field in item "O".8s!\n",
cl[p].name);

/*:18*/
#line 457 "./dlx5.w"
;
}
}

/*:17*//*43:*/
#line 878 "./dlx5.w"

void cover(int c,ullng thresh){
register int cc,l,r,rr,nn,uu,dd,t;
o,l= cl[c].prev,r= cl[c].next;
oo,cl[l].next= r,cl[r].prev= l;
updates++;
for(o,rr= nd[c].down;rr>=last_itm;o,rr= nd[rr].down){
if(o,nd[rr].cost>=thresh)break;
for(nn= rr+1;nn!=rr;){
if(o,nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
cc= nd[nn].itm;
if(cc<=0){
nn= uu;continue;
}
oo,nd[uu].down= dd,nd[dd].up= uu;
updates++;
if(cc<second)oo,nd[cc].len--;
}
nn++;
}
}
}

/*:43*//*44:*/
#line 917 "./dlx5.w"

void uncover(int c,ullng thresh){
register int cc,l,r,rr,nn,uu,dd,t;
for(o,rr= nd[c].down;rr>=last_itm;o,rr= nd[rr].down){
if(o,nd[rr].cost>=thresh)break;
for(nn= rr+1;nn!=rr;){
if(o,nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
cc= nd[nn].itm;
if(cc<=0){
nn= uu;continue;
}
oo,nd[uu].down= nd[dd].up= nn;
if(cc<second)oo,nd[cc].len++;
}
nn++;
}
}
o,l= cl[c].prev,r= cl[c].next;
oo,cl[l].next= cl[r].prev= c;
}

/*:44*//*47:*/
#line 971 "./dlx5.w"

void purify(int p,ullng thresh){
register int cc,rr,nn,uu,dd,t,x;
o,cc= nd[p].itm,x= nd[p].color;
nd[cc].color= x;
cleansings++;
for(o,rr= nd[cc].down;rr>=last_itm;o,rr= nd[rr].down){
if(o,nd[rr].cost>=thresh)break;
if(o,nd[rr].color!=x){
for(nn= rr+1;nn!=rr;){
if(o,nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
cc= nd[nn].itm;
if(cc<=0){
nn= uu;continue;
}
oo,nd[uu].down= dd,nd[dd].up= uu;
updates++;
if(cc<second)oo,nd[cc].len--;
}
nn++;
}
}else if(rr!=p)cleansings++,o,nd[rr].color= -1;
}
}

/*:47*//*48:*/
#line 1000 "./dlx5.w"

void unpurify(int p,ullng thresh){
register int cc,rr,nn,uu,dd,t,x;
o,cc= nd[p].itm,x= nd[p].color;
for(o,rr= nd[cc].down;rr>=last_itm;o,rr= nd[rr].down){
if(o,nd[rr].cost>=thresh)break;
if(o,nd[rr].color<0)o,nd[rr].color= x;
else if(rr!=p){
for(nn= rr+1;nn!=rr;){
if(o,nd[nn].color>=0){
o,uu= nd[nn].up,dd= nd[nn].down;
cc= nd[nn].itm;
if(cc<=0){
nn= uu;continue;
}
oo,nd[uu].down= nd[dd].up= nn;
if(cc<second)oo,nd[cc].len++;
}
nn++;
}
}
}
}

/*:48*//*59:*/
#line 1261 "./dlx5.w"

void print_state(void){
register int l;
fprintf(stderr,"Current state (level "O"d):\n",level);
for(l= 0;l<level;l++){
print_option(choice[l],stderr,cutoffcost-partcost[l]);
if(l>=show_levels_max){
fprintf(stderr," ...\n");
break;
}
}
if(cutoffcost<infcost)
fprintf(stderr,
" "O"lld solutions, $"O"llu, "O"lld mems, and max level "O"d so far.\n",
count,cutoffcost+totaltax,mems,maxl);
else fprintf(stderr,
" "O"lld solutions, "O"lld mems, and max level "O"d so far.\n",
count,mems,maxl);
}

/*:59*//*60:*/
#line 1301 "./dlx5.w"

void print_progress(void){
register int l,k,d,c,p;
register double f,fd;
if(cutoffcost<infcost)
fprintf(stderr," after "O"lld mems: "O"lld sols, $"O"llu,",
mems,count,cutoffcost+totaltax);
else fprintf(stderr," after "O"lld mems: "O"lld sols,",
mems,count);
for(f= 0.0,fd= 1.0,l= 0;l<level;l++){
c= nd[choice[l]].itm;
for(k= 1,p= nd[c].down;p!=choice[l];k++,p= nd[p].down);
for(d= k-1;p>=last_itm;p= nd[p].down,d++)
if(nd[p].cost>=cutoffcost-partcost[l])break;
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

/*:60*//*62:*/
#line 1335 "./dlx5.w"

int confusioncount;
void confusion(char*id){
if(confusioncount++==0)
fprintf(stderr,"This can't happen (%s)!\n",id);
}

/*:62*/
#line 93 "./dlx5.w"
;
main(int argc,char*argv[]){
register int cc,i,j,k,p,pp,q,r,s,t,cur_node,best_itm;
register ullng tmpcost,curcost,mincost,nextcost;
/*7:*/
#line 224 "./dlx5.w"

for(j= argc-1,k= 0;j;j--)switch(argv[j][0]){
case'v':k|= (sscanf(argv[j]+1,""O"d",&vbose)-1);break;
case'm':k|= (sscanf(argv[j]+1,""O"d",&spacing)-1);break;
case'k':k|= (sscanf(argv[j]+1,""O"d",&kthresh)-1);
if(kthresh<1||kthresh> maxk){
fprintf(stderr,"Sorry, parameter k must be between 1 and "O"d!\n",
maxk);
exit(-1);
}
break;
case'Z':if(strlen(argv[j])> 8){
fprintf(stderr,
"Sorry, parameter Z must specify at most 7 prefix characters!\n");
k|= 1;
}else sprintf(Zchars,"%s",argv[j]+1);
break;
case'z':k|= (sscanf(argv[j]+1,""O"d",&zgiven)-1);break;
case'h':k|= (sscanf(argv[j]+1,""O"d",&lenthresh)-1);break;
case'd':k|= (sscanf(argv[j]+1,""O"lld",&delta)-1),thresh= delta;break;
case'c':k|= (sscanf(argv[j]+1,""O"d",&show_choices_max)-1);break;
case'C':k|= (sscanf(argv[j]+1,""O"d",&show_levels_max)-1);break;
case'l':k|= (sscanf(argv[j]+1,""O"d",&show_choices_gap)-1);break;
case't':k|= (sscanf(argv[j]+1,""O"lld",&maxcount)-1);break;
case'T':k|= (sscanf(argv[j]+1,""O"lld",&timeout)-1);break;
case'S':shape_name= argv[j]+1,shape_file= fopen(shape_name,"w");
if(!shape_file)
fprintf(stderr,"Sorry, I can't open file `"O"s' for writing!\n",
shape_name);
break;
default:k= 1;
}
if(k){
fprintf(stderr,"Usage: "O"s [v<n>] [m<n>] [k<n>] [Z<ABC>] [z<n>] [h<n>]"
" [d<n>] [c<n>] [C<n>] [l<n>] [t<n>] [T<n>] [S<bar>] < foo.dlx\n",
argv[0]);
exit(-1);
}

/*:7*/
#line 97 "./dlx5.w"
;
/*3:*/
#line 104 "./dlx5.w"

/*19:*/
#line 479 "./dlx5.w"

nd= (node*)calloc(max_nodes,sizeof(node));
if(!nd){
fprintf(stderr,"I couldn't allocate space for "O"d nodes!\n",max_nodes);
exit(-666);
}
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
/*20:*/
#line 522 "./dlx5.w"

for(k= 1;o,strncmp(cl[k].name,cl[last_itm].name,8);k++);
if(k<last_itm)panic("Duplicate item name");

/*:20*/
#line 505 "./dlx5.w"
;
/*21:*/
#line 526 "./dlx5.w"

if(last_itm> max_cols)panic("Too many items");
oo,cl[last_itm-1].next= last_itm,cl[last_itm].prev= last_itm-1;

o,nd[last_itm].up= nd[last_itm].down= last_itm;
last_itm++;

/*:21*/
#line 506 "./dlx5.w"
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


/*:19*/
#line 105 "./dlx5.w"
;
/*22:*/
#line 536 "./dlx5.w"

/*28:*/
#line 635 "./dlx5.w"

if(o,Zchars[0]){
for(r= 1;Zchars[r];r++);
ppgiven= (1<<r)-1+(zgiven<<8);
}else ppgiven= zgiven<<8;

/*:28*/
#line 537 "./dlx5.w"
;
while(1){
if(!fgets(buf,bufsize,stdin))break;
if(o,buf[p= strlen(buf)-1]!='\n')panic("Option line too long");
for(p= 0;o,isspace(buf[p]);p++);
if(buf[p]=='|'||!buf[p])continue;
i= last_node;
tmpcost= 0;
for(pp= 0;buf[p];){
for(j= 0;j<8&&(o,!isspace(buf[p+j]))&&buf[p+j]!=':';j++)
o,cl[last_itm].name[j]= buf[p+j];
if(!j)panic("Empty item name");
if(j==8&&!isspace(buf[p+j])&&buf[p+j]!=':')
panic("Item name too long");
if(j<8)o,cl[last_itm].name[j]= '\0';
/*25:*/
#line 600 "./dlx5.w"

for(k= 0;o,strncmp(cl[k].name,cl[last_itm].name,8);k++);
if(k==last_itm)panic("Unknown item name");
if(o,nd[k].aux>=i)panic("Duplicate item name in this option");
last_node++;
if(last_node==max_nodes)panic("Too many nodes");
o,nd[last_node].itm= k;
if(k<second)/*30:*/
#line 652 "./dlx5.w"

{
for(r= 0;Zchars[r];r++)
if(Zchars[r]==cl[last_itm].name[0])break;
if(Zchars[r]){
if(pp&(1<<r))
fprintf(stderr,"Option has two "O"c items: "O"s",Zchars[r],buf);
else pp+= 1<<r;
}else pp+= 1<<8;
}

/*:30*/
#line 607 "./dlx5.w"
;
o,t= nd[k].len+1;
/*26:*/
#line 617 "./dlx5.w"

o,nd[k].len= t;
nd[k].aux= last_node;
o,r= nd[k].up;
oo,nd[k].up= last_node,nd[last_node].up= r;

/*:26*/
#line 609 "./dlx5.w"
;

/*:25*/
#line 552 "./dlx5.w"
;
if(buf[p+j]!=':')o,nd[last_node].color= 0;
else if(k>=second){
if((o,isspace(buf[p+j+1]))||(o,!isspace(buf[p+j+2])))
panic("Color must be a single character");
o,nd[last_node].color= buf[p+j+1];
p+= 2;
}else panic("Primary item must be uncolored");
/*23:*/
#line 581 "./dlx5.w"

while(1){
register ullng d;
for(p+= j+1;o,isspace(buf[p]);p++);
if(buf[p]!='|')break;
if(buf[p+1]<'0'||buf[p+1]> '9')
panic("Option cost should be a decimal number");
for(j= 1,d= 0;o,!isspace(buf[p+j]);j++){
if(buf[p+j]<'0'||buf[p+j]> '9')
panic("Illegal digit in option cost");
d= 10*d+buf[p+j]-'0';
}
tmpcost+= d;
}

/*:23*/
#line 560 "./dlx5.w"
;
}
if(!pp){
if(vbose&show_warnings)
fprintf(stderr,"Option ignored (no primary items): "O"s",buf);
while(last_node> i){
/*27:*/
#line 623 "./dlx5.w"

o,k= nd[last_node].itm;
oo,nd[k].len--,nd[k].aux= i-1;
oo,nd[k].up= nd[last_node].up;

/*:27*/
#line 566 "./dlx5.w"
;
last_node--;
}
}else{
/*29:*/
#line 641 "./dlx5.w"

if(ppgiven){
if(zgiven&&((pp>>8)!=zgiven))
fprintf(stderr,"Option has "O"d non-Z primary items, not "O"d: "O"s",
pp>>8,zgiven,buf);
if((pp^ppgiven)&0xff){
for(r= 0;Zchars[r];r++)if((pp&(1<<r))==0)
fprintf(stderr,"Option lacks a "O"c item: "O"s",Zchars[r],buf);
}
}

/*:29*/
#line 570 "./dlx5.w"
;
/*24:*/
#line 596 "./dlx5.w"

for(j= i+1;j<=last_node;j++)
o,nd[j].cost= tmpcost;

/*:24*/
#line 571 "./dlx5.w"
;
o,nd[i].down= last_node;
last_node++;
if(last_node==max_nodes)panic("Too many nodes");
options++;
o,nd[last_node].up= i+1;
o,nd[last_node].itm= -options;
}
}

/*:22*/
#line 106 "./dlx5.w"
;
/*31:*/
#line 673 "./dlx5.w"

for(k= 1;k<second;k++){
register ullng minc;
for(p= nd[k].up,minc= infcost;p> k&&minc;o,p= nd[p].up)
if(o,nd[p].cost<minc)minc= nd[p].cost;
if(minc){
if(vbose&show_taxes)
fprintf(stderr," "O".8s tax=$"O"llu\n",cl[k].name,minc);
totaltax+= minc;
for(p= nd[k].up;p> k;o,p= nd[p].up){
for(q= p+1;;){
o,cc= nd[q].itm;
if(cc<=0)o,q= nd[q].up;
else{
oo,nd[q].cost-= minc;
if(q==p)break;
q++;
}
}
}
nd[k].tax= minc;
}
}
if(totaltax&&(vbose&show_taxes))
fprintf(stderr," (total tax is $"O"llu)\n",totaltax);

/*:31*/
#line 107 "./dlx5.w"
;
/*32:*/
#line 702 "./dlx5.w"

for(k= 1;k<last_itm;k++){
l1:o,p= nd[k].up,q= nd[p].up;
for(o,t= root;q> k;o,p= q,q= nd[p].up)
if(o,nd[p].cost<nd[q].cost)nd[t].up= -q,t= p;
if(t!=root)/*34:*/
#line 721 "./dlx5.w"

{
oo,nd[t].up= nd[p].up= 0;
l2:while(o,nd[root].up){
oo,s= k,t= root,p= nd[s].up,q= -nd[root].up;
l3:if(o,nd[p].cost<nd[q].cost)goto l6;
l4:/*35:*/
#line 735 "./dlx5.w"

o,nd[s].up= (nd[s].up<=0?-p:p);
o,s= p,p= nd[p].up;
if(p> 0)goto l3;
l5:o,nd[s].up= q,s= t;
for(;q> 0;o,q= nd[q].up)t= q;
goto l8;

/*:35*/
#line 727 "./dlx5.w"
;
l6:/*36:*/
#line 743 "./dlx5.w"

o,nd[s].up= (nd[s].up<=0?-q:q);
o,s= q,q= nd[q].up;
if(q> 0)goto l3;
l7:o,nd[s].up= p,s= t;
for(;p> 0;o,p= nd[p].up)t= p;
goto l8;

/*:36*/
#line 728 "./dlx5.w"
;
l8:p= -p,q= -q;
if(q)goto l3;
oo,nd[s].up= -p,nd[t].up= 0;
}
}

/*:34*/
#line 707 "./dlx5.w"
;
/*33:*/
#line 711 "./dlx5.w"

for(o,p= k,q= nd[p].up;q> k;o,p= q,q= nd[p].up)o,nd[q].down= p;
oo,nd[p].up= k,nd[k].down= p;

/*:33*/
#line 708 "./dlx5.w"
;
}

/*:32*/
#line 108 "./dlx5.w"
;
if(vbose&show_basics)
/*37:*/
#line 751 "./dlx5.w"

fprintf(stderr,
"("O"lld options, "O"d+"O"d items, "O"d entries successfully read)\n",
options,second-1,last_itm-second,last_node-last_itm);

/*:37*/
#line 110 "./dlx5.w"
;
if(vbose&show_tots)
/*38:*/
#line 760 "./dlx5.w"

{
fprintf(stderr,"Item totals:");
for(k= 1;k<last_itm;k++){
if(k==second)fprintf(stderr," |");
fprintf(stderr," "O"d",nd[k].len);
}
fprintf(stderr,"\n");
}

/*:38*/
#line 112 "./dlx5.w"
;
imems= mems,mems= 0;

/*:3*/
#line 98 "./dlx5.w"
;
/*39:*/
#line 787 "./dlx5.w"

/*40:*/
#line 827 "./dlx5.w"

if(zgiven){
for(r= 0;Zchars[r];r++);
if((second-1)mod(zgiven+r)){
fprintf(stderr,
"There are "O"d primary items, but z="O"d and Z="O"s!\n",
second-1,zgiven,Zchars);
goto done;
}
}
level= 0;
for(k= 0;k<kthresh;k++)o,bestcost[k]= infcost;
cutoffcost= infcost;
curcost= 0;

/*:40*/
#line 788 "./dlx5.w"
;
forward:nodes++;
if(vbose&show_profile)profile[level]++;
if(sanity_checking)sanity();
/*42:*/
#line 853 "./dlx5.w"

if(delta&&(mems>=thresh)){
thresh+= delta;
if(vbose&show_full_state)print_state();
else print_progress();
}
if(mems>=timeout){
fprintf(stderr,"TIMEOUT!\n");goto done;
}

/*:42*/
#line 792 "./dlx5.w"
;
/*49:*/
#line 1027 "./dlx5.w"

if(ppgiven&&cutoffcost!=infcost){
if(zgiven> 1){
if(second-level*zgiven<=sortbufsize+1)pp= zgiven;
else if(ppgiven&0xff)pp= 0;
else pp= -1;
}else pp= zgiven;
if(pp>=0)/*50:*/
#line 1037 "./dlx5.w"

{
register ullng newcost,oldcost,acccost;
acccost= curcost;
for(r= 0;Zchars[r];r++)o,cumcost[r]= curcost;
for(o,k= cl[root].next,t= 0;k!=root;o,k= cl[k].next){
o,p= nd[k].down;
if(p<last_itm){
if(explaining)fprintf(stderr,
"(Level "O"d, "O".8s's list is empty)\n",level,cl[k].name);
goto backdown;
}
oo,cc= cl[k].name[0],tmpcost= nd[p].cost;
for(r= 0;Zchars[r];r++)if(Zchars[r]==cc)break;
if(Zchars[r])/*51:*/
#line 1056 "./dlx5.w"

{
if(o,cumcost[r]+tmpcost>=cutoffcost){
if(explaining)fprintf(stderr,
"(Level "O"d, "O".8s's cost overflowed)\n",level,cl[k].name);
goto backdown;
}
o,cumcost[r]+= tmpcost;
}

/*:51*/
#line 1051 "./dlx5.w"

else if(pp)/*52:*/
#line 1077 "./dlx5.w"

{
if(pp==1){
if(acccost+tmpcost>=cutoffcost){
if(explaining)fprintf(stderr,
"(Level "O"d, "O".8s's cost overflowed)\n",level,cl[k].name);
goto backdown;
}
acccost+= tmpcost;
}else{

for(p= t,oldcost= 0;p;p--,oldcost= newcost){
o,newcost= sortbuf[sortbufsize-p];
if(tmpcost<=newcost)break;
if((p mod pp)==0){
acccost+= newcost-oldcost;
if(acccost>=cutoffcost){
if(explaining)fprintf(stderr,
"(Level "O"d, "O".8s's cost overflowed)\n",level,cl[k].name);
goto backdown;
}
}
o,sortbuf[sortbufsize-p-1]= newcost;
}
if((p mod pp)==0){
acccost+= tmpcost-oldcost;
if(acccost>=cutoffcost){
if(explaining)
fprintf(stderr,"("O".8s's cost caused overflow)\n",cl[k].name);
goto backdown;
}
}
o,sortbuf[sortbufsize-p-1]= tmpcost;
t++;
}
}

/*:52*/
#line 1052 "./dlx5.w"
;
}
}

/*:50*/
#line 1034 "./dlx5.w"

}

/*:49*/
#line 793 "./dlx5.w"
;
/*53:*/
#line 1138 "./dlx5.w"

t= max_nodes,tmpcost= 0;
if(explaining)fprintf(stderr,"Level "O"d:",level);
for(o,k= cl[root].next;k!=root;o,k= cl[k].next){
o,p= nd[k].down;
if(p==k){
if(explaining)fprintf(stderr," "O".8s(0)",cl[k].name);
t= 0,best_itm= k;
break;
}
o,mincost= nd[p].cost;
if(mincost>=cutoffcost-curcost){
if(explaining)fprintf(stderr," "O".8s(0$"O"llu)",
cl[k].name,mincost);
t= 0,best_itm= k;
break;
}
/*54:*/
#line 1169 "./dlx5.w"

for(o,s= 1,p= nd[p].down;;o,p= nd[p].down,s++){
if(p<last_itm||(o,nd[p].cost>=cutoffcost-curcost)){
if(explaining)fprintf(stderr,
" "O".8s("O"d$"O"llu)",cl[k].name,s,mincost);
break;
}
if(s==t){
if(explaining)fprintf(stderr,
" "O".8s(>"O"d)",cl[k].name,t);
goto no_change;
}
if(s>=lenthresh){
o,s= nd[k].len;
if(explaining)fprintf(stderr,
" "O".8s("O"d?$"O"llu)",cl[k].name,s,mincost);
break;
}
}
if(s<t||(s==t&&mincost> tmpcost))
t= s,best_itm= k,tmpcost= mincost;
no_change:

/*:54*/
#line 1155 "./dlx5.w"
;
}
if(explaining)
fprintf(stderr," branching on "O".8s("O"d)\n",cl[best_itm].name,t);
if(shape_file){
fprintf(shape_file,""O"d "O".8s\n",t,cl[best_itm].name);
fflush(shape_file);
}
if(t==0)goto backdown;

/*:53*/
#line 794 "./dlx5.w"
;
o,partcost[level]= curcost;
oo,cur_node= choice[level]= nd[best_itm].down;
o,nextcost= curcost+nd[cur_node].cost;
o,coverthresh0[level]= cutoffcost-nextcost;
cover(best_itm,coverthresh0[level]);
advance:if((vbose&show_choices)&&level<show_choices_max){
fprintf(stderr,"L"O"d:",level);
print_option(cur_node,stderr,cutoffcost-curcost);
}
/*45:*/
#line 939 "./dlx5.w"

o,coverthresh[level]= cutoffcost-nextcost;
for(pp= cur_node+1;pp!=cur_node;){
o,cc= nd[pp].itm;
if(cc<=0)o,pp= nd[pp].up;
else{
if(!nd[pp].color)cover(cc,coverthresh[level]);
else if(nd[pp].color> 0)purify(pp,coverthresh[level]);
pp++;
}
}

/*:45*/
#line 804 "./dlx5.w"
;
if(o,cl[root].next==root)/*55:*/
#line 1192 "./dlx5.w"

{
nodes++;
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
/*56:*/
#line 1218 "./dlx5.w"

{
register int h,hh;
tmpcost= cutoffcost;
for(h= 0,hh= 2;hh<=kthresh;hh= h+h+2){
if(oo,bestcost[hh]> bestcost[hh-1]){
if(nextcost<bestcost[hh])o,bestcost[h]= bestcost[hh],h= hh;
else break;
}else if(nextcost<bestcost[hh-1])o,bestcost[h]= bestcost[hh-1],h= hh-1;
else break;
}
o,bestcost[h]= nextcost;
o,cutoffcost= bestcost[0];
}

/*:56*/
#line 1206 "./dlx5.w"
;
/*58:*/
#line 1249 "./dlx5.w"

{
count++;
if(spacing&&(count mod spacing==0)){
printf(""O"lld: (total cost $"O"llu)\n",count,totaltax+nextcost);
for(k= 0;k<=level;k++)print_option(choice[k],stdout,tmpcost-partcost[k]);
fflush(stdout);
}
if(count>=maxcount)goto done;
goto recover;
}

/*:58*/
#line 1207 "./dlx5.w"
;
}

/*:55*/
#line 805 "./dlx5.w"
;
if(++level> maxl){
if(level>=max_level){
fprintf(stderr,"Too many levels!\n");
exit(-4);
}
maxl= level;
}
curcost= nextcost;
goto forward;
backup:o,uncover(best_itm,coverthresh0[level]);
backdown:if(level==0)goto done;
level--;
oo,cur_node= choice[level],best_itm= nd[cur_node].itm;
o,curcost= partcost[level];
recover:/*46:*/
#line 954 "./dlx5.w"

o;
for(pp= cur_node-1;pp!=cur_node;){
o,cc= nd[pp].itm;
if(cc<=0)o,pp= nd[pp].down;
else{
if(!nd[pp].color)uncover(cc,coverthresh[level]);
else if(nd[pp].color> 0)unpurify(pp,coverthresh[level]);
pp--;
}
}

/*:46*/
#line 820 "./dlx5.w"
;
oo,cur_node= choice[level]= nd[cur_node].down;
if(cur_node==best_itm)goto backup;
o,nextcost= curcost+nd[cur_node].cost;
if(nextcost>=cutoffcost)goto backup;
goto advance;

/*:39*/
#line 99 "./dlx5.w"
;
done:if(sanity_checking)sanity();
/*4:*/
#line 115 "./dlx5.w"

if(vbose&show_tots)
/*38:*/
#line 760 "./dlx5.w"

{
fprintf(stderr,"Item totals:");
for(k= 1;k<last_itm;k++){
if(k==second)fprintf(stderr," |");
fprintf(stderr," "O"d",nd[k].len);
}
fprintf(stderr,"\n");
}

/*:38*/
#line 117 "./dlx5.w"
;
if(vbose&show_profile)/*61:*/
#line 1327 "./dlx5.w"

{
fprintf(stderr,"Profile:\n");
for(level= 0;level<=maxl;level++)
fprintf(stderr,""O"3d: "O"lld\n",
level,profile[level]);
}

/*:61*/
#line 118 "./dlx5.w"
;
if(vbose&show_basics){
fprintf(stderr,"Altogether "O"llu solution"O"s, "O"llu+"O"llu mems,",
count,count==1?"":"s",imems,mems);
bytes= last_itm*sizeof(item)+last_node*sizeof(node)+maxl*sizeof(int);
fprintf(stderr," "O"llu updates, "O"llu cleansings,",
updates,cleansings);
fprintf(stderr," "O"llu bytes, "O"llu nodes.\n",
bytes,nodes);
}
if((vbose&show_opt_costs)&&count)/*9:*/
#line 266 "./dlx5.w"

{
fprintf(stderr,"The optimum cost"O"s",kthresh==1?" is":"s are:\n");
/*57:*/
#line 1233 "./dlx5.w"

for(p= kthresh;p> 2;p--){
register int h,hh;
nextcost= bestcost[p-1],bestcost[p-1]= 0,bestcost[p]= bestcost[0];
for(h= 0,hh= 2;hh<p;hh= h+h+2){
if(bestcost[hh]> bestcost[hh-1]){
if(nextcost<bestcost[hh])bestcost[h]= bestcost[hh],h= hh;
else break;
}else if(nextcost<bestcost[hh-1])bestcost[h]= bestcost[hh-1],h= hh-1;
else break;
}
bestcost[h]= nextcost;
}
bestcost[p]= bestcost[0];


/*:57*/
#line 269 "./dlx5.w"
;
for(k= 1,tmpcost= infcost;k<=kthresh&&bestcost[k]<infcost;k++){
if(tmpcost==totaltax+bestcost[k])r++;
else{
/*10:*/
#line 280 "./dlx5.w"

if(tmpcost!=infcost){
if(r)fprintf(stderr," $"O"llu (repeated "O"d times)\n",tmpcost,r+1);
else fprintf(stderr," $"O"llu\n",tmpcost);
}

/*:10*/
#line 273 "./dlx5.w"
;
tmpcost= totaltax+bestcost[k],r= 0;
}
}
/*10:*/
#line 280 "./dlx5.w"

if(tmpcost!=infcost){
if(r)fprintf(stderr," $"O"llu (repeated "O"d times)\n",tmpcost,r+1);
else fprintf(stderr," $"O"llu\n",tmpcost);
}

/*:10*/
#line 277 "./dlx5.w"
;
}

/*:9*/
#line 128 "./dlx5.w"
;
/*8:*/
#line 263 "./dlx5.w"

if(shape_file)fclose(shape_file);

/*:8*/
#line 129 "./dlx5.w"
;

/*:4*/
#line 101 "./dlx5.w"
;
}

/*:2*/
