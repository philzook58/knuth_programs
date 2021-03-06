#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define O "%"
#define mod % \

#define max_level 5000
#define max_cols 100000
#define max_nodes 10000000
#define bufsize (9*max_cols+3)  \

#define show_basics 1
#define show_choices 2
#define show_details 4
#define show_profile 128
#define show_full_state 256
#define show_tots 512
#define show_warnings 1024
#define show_max_deg 2048 \

#define size(x) set[(x) -1]
#define pos(x) set[(x) -2]
#define lname(x) set[(x) -4]
#define rname(x) set[(x) -3]
#define color(x) set[(x) -5] \

#define sanity_checking 0 \

#define panic(m) {fprintf(stderr,""O"s!\n"O"d: "O".99s\n",m,p,buf) ;exit(-666) ;} \

/*2:*/
#line 43 "./ssxcc.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
typedef unsigned int uint;
typedef unsigned long long ullng;
/*7:*/
#line 276 "./ssxcc.w"

typedef struct node_struct{
int itm;
int loc;
int clr;
int spr;
}node;

/*:7*//*9:*/
#line 299 "./ssxcc.w"

typedef struct{
int l,r;
}twoints;
typedef union{
char str[8];
twoints lr;
}stringbuf;
stringbuf namebuf;

/*:9*/
#line 50 "./ssxcc.w"
;
/*3:*/
#line 124 "./ssxcc.w"

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
ullng timeout= 0x1fffffffffffffff;
FILE*shape_file;
char*shape_name;
int maxdeg;

/*:3*//*8:*/
#line 284 "./ssxcc.w"

node nd[max_nodes];
int last_node;
int item[max_cols];
int second= max_cols;
int last_itm;
int set[max_nodes+4*max_cols];
int itemlength;
int setlength;
int active;

/*:8*//*25:*/
#line 618 "./ssxcc.w"

int level;
int choice[max_level];
ullng profile[max_level];

/*:25*/
#line 51 "./ssxcc.w"
;
/*10:*/
#line 309 "./ssxcc.w"

void print_item_name(int k,FILE*stream){
namebuf.lr.l= lname(k),namebuf.lr.r= rname(k);
fprintf(stream," "O".8s",namebuf.str);
}

/*:10*//*11:*/
#line 319 "./ssxcc.w"

void print_option(int p,FILE*stream){
register int k,q,x;
x= nd[p].itm;
if(p>=last_node||x<=0){
fprintf(stderr,"Illegal option "O"d!\n",p);
return;
}
for(q= p;;){
print_item_name(x,stream);
if(nd[q].clr)
fprintf(stream,":"O"c",nd[q].clr> 0?nd[q].clr:color(x));
q++;
x= nd[q].itm;
if(x<0)q+= x,x= nd[q].itm;
if(q==p)break;
}
k= nd[q].loc;
fprintf(stream," ("O"d of "O"d)\n",k-x+1,size(x));
}

void prow(int p){
print_option(p,stderr);
}

/*:11*//*12:*/
#line 346 "./ssxcc.w"

void print_itm(int c){
register int p;
if(c<4||c>=setlength||
pos(c)<0||pos(c)>=itemlength||item[pos(c)]!=c){
fprintf(stderr,"Illegal item "O"d!\n",c);
return;
}
fprintf(stderr,"Item");
print_item_name(c,stderr);
if(pos(c)<second)fprintf(stderr," ("O"d of "O"d), length "O"d:\n",
pos(c)+1,active,size(c));
else if(color(c))fprintf(stderr," (secondary "O"d:"O"c), length "O"d:\n",
pos(c)+1,color(c),size(c));
else fprintf(stderr," (secondary "O"d), length "O"d:\n",
pos(c)+1,size(c));
for(p= c;p<c+size(c);p++)prow(set[p]);
}

/*:12*//*13:*/
#line 370 "./ssxcc.w"

void sanity(void){
register int k,x,i,l,r;
for(k= 0;k<itemlength;k++){
x= item[k];
if(pos(x)!=k){
fprintf(stderr,"Bad pos field of item");
print_item_name(x,stderr);
fprintf(stderr," ("O"d,"O"d)!\n",k,x);
}
}
for(i= 0;i<last_node;i++){
l= nd[i].itm,r= nd[i].loc;
if(l<=0){
if(nd[i+r+1].itm!=-r)
fprintf(stderr,"Bad spacer in nodes "O"d, "O"d!\n",i,i+r+1);
}else{
if(l> r)fprintf(stderr,"itm>loc in node "O"d!\n",i);
else if(set[r]!=i){
fprintf(stderr,"Bad loc field for option "O"d of item",r-l+1);
print_item_name(l,stderr);
fprintf(stderr," in node "O"d!\n",i);
}
}
}
}

/*:13*//*27:*/
#line 637 "./ssxcc.w"

void cover(int c){
register int k,a,cc,s,rr,ss,nn,tt,uu,vv,nnp;
o,k= pos(c);
if(k<second){
a= active-1,active= a;
o,cc= item[a];
oo,item[a]= c,item[k]= cc;
oo,pos(cc)= k,pos(c)= a;
updates++;
}
for(o,rr= c,s= c+size(c);rr<s;rr++){
o,tt= set[rr];
/*28:*/
#line 654 "./ssxcc.w"

{
for(nn= tt+1;nn!=tt;)if(o,nd[nn].clr>=0){
o,uu= nd[nn].itm,vv= nd[nn].loc;
if(uu<0){nn+= uu;continue;}
o,ss= size(uu)-1;
o,nnp= set[uu+ss];
o,size(uu)= ss;
oo,set[uu+ss]= nn,set[vv]= nnp;
oo,nd[nn].loc= uu+ss,nd[nnp].loc= vv;
nn++;
updates++;
}else nn++;
}

/*:28*/
#line 650 "./ssxcc.w"
;
}
}

/*:27*//*29:*/
#line 674 "./ssxcc.w"

void uncover(int c){
register int k,cc,s,rr,ss,nn,tt,uu;
for(o,rr= c,s= c+size(c);rr<s;rr++){
o,tt= set[rr];
/*30:*/
#line 685 "./ssxcc.w"

{
for(nn= tt+1;nn!=tt;)if(o,nd[nn].clr>=0){
o,uu= nd[nn].itm;
if(uu<0){nn+= uu;continue;}
o,ss= size(uu)+1;
o,size(uu)= ss;
nn++;
}else nn++;
}

/*:30*/
#line 679 "./ssxcc.w"
;
}
o,k= pos(c);
if(k<second)active++;
}

/*:29*//*33:*/
#line 741 "./ssxcc.w"

void purify(int p){
register int c,x,tt,rr,s,ss,nn,uu,vv,nnp;
o,c= nd[p].itm;
o,x= nd[p].clr;
color(c)= x;
cleansings++;
for(o,rr= c,s= c+size(c);rr<s;rr++){
o,tt= set[rr];
if(o,nd[tt].clr!=x)
/*28:*/
#line 654 "./ssxcc.w"

{
for(nn= tt+1;nn!=tt;)if(o,nd[nn].clr>=0){
o,uu= nd[nn].itm,vv= nd[nn].loc;
if(uu<0){nn+= uu;continue;}
o,ss= size(uu)-1;
o,nnp= set[uu+ss];
o,size(uu)= ss;
oo,set[uu+ss]= nn,set[vv]= nnp;
oo,nd[nn].loc= uu+ss,nd[nnp].loc= vv;
nn++;
updates++;
}else nn++;
}

/*:28*/
#line 751 "./ssxcc.w"

else o,cleansings++,nd[tt].clr= -1;
}
}

/*:33*//*34:*/
#line 759 "./ssxcc.w"

void unpurify(int p){
register int c,x,tt,rr,s,ss,nn,uu;
o,c= nd[p].itm;
o,x= nd[p].clr;
color(c)= 0;
for(o,rr= c,s= c+size(c);rr<s;rr++){
o,tt= set[rr];
if(o,nd[tt].clr>=0)
/*30:*/
#line 685 "./ssxcc.w"

{
for(nn= tt+1;nn!=tt;)if(o,nd[nn].clr>=0){
o,uu= nd[nn].itm;
if(uu<0){nn+= uu;continue;}
o,ss= size(uu)+1;
o,size(uu)= ss;
nn++;
}else nn++;
}

/*:30*/
#line 768 "./ssxcc.w"

else o,nd[tt].clr= x;
}
}

/*:34*//*38:*/
#line 838 "./ssxcc.w"

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
fprintf(stderr," "O"lld solutions, "O"lld mems, and max level "O"d so far.\n",
count,mems,maxl);
}

/*:38*//*39:*/
#line 873 "./ssxcc.w"

void print_progress(void){
register int l,k,d,c,p;
register double f,fd;
fprintf(stderr," after "O"lld mems: "O"lld sols,",mems,count);
for(f= 0.0,fd= 1.0,l= 0;l<level;l++){
c= nd[choice[l]].itm,d= size(c),k= nd[choice[l]].loc-c+1;
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

/*:39*/
#line 52 "./ssxcc.w"
;
main(int argc,char*argv[]){
register int cc,i,j,k,p,pp,q,r,s,t,cur_choice,cur_node,best_itm;
/*4:*/
#line 151 "./ssxcc.w"

for(j= argc-1,k= 0;j;j--)switch(argv[j][0]){
case'v':k|= (sscanf(argv[j]+1,""O"d",&vbose)-1);break;
case'm':k|= (sscanf(argv[j]+1,""O"d",&spacing)-1);break;
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
fprintf(stderr,"Usage: "O"s [v<n>] [m<n>] [s<n>] [d<n>]"
" [c<n>] [C<n>] [l<n>] [t<n>] [T<n>] [S<bar>] < foo.dlx\n",
argv[0]);
exit(-1);
}

/*:4*/
#line 55 "./ssxcc.w"
;
/*14:*/
#line 404 "./ssxcc.w"

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
o,namebuf.lr.l= namebuf.lr.r= 0;
for(j= 0;j<8&&(o,!isspace(buf[p+j]));j++){
if(buf[p+j]==':'||buf[p+j]=='|')
panic("Illegal character in item name");
o,namebuf.str[j]= buf[p+j];
}
if(j==8&&!isspace(buf[p+j]))panic("Item name too long");
oo,lname(last_itm<<2)= namebuf.lr.l,rname(last_itm<<2)= namebuf.lr.r;
/*15:*/
#line 435 "./ssxcc.w"

for(k= last_itm-1;k;k--){
if(o,lname(k<<2)!=namebuf.lr.l)continue;
if(rname(k<<2)==namebuf.lr.r)break;
}
if(k)panic("Duplicate item name");

/*:15*/
#line 423 "./ssxcc.w"
;
last_itm++;
if(last_itm> max_cols)panic("Too many items");
for(p+= j+1;o,isspace(buf[p]);p++);
if(buf[p]=='|'){
if(second!=max_cols)panic("Item name line contains | twice");
second= last_itm;
for(p++;o,isspace(buf[p]);p++);
}
}
if(second==max_cols)second= last_itm;

/*:14*/
#line 56 "./ssxcc.w"
;
/*16:*/
#line 446 "./ssxcc.w"

while(1){
if(!fgets(buf,bufsize,stdin))break;
if(o,buf[p= strlen(buf)-1]!='\n')panic("Option line too long");
for(p= 0;o,isspace(buf[p]);p++);
if(buf[p]=='|'||!buf[p])continue;
i= last_node;
for(pp= 0;buf[p];){
o,namebuf.lr.l= namebuf.lr.r= 0;
for(j= 0;j<8&&(o,!isspace(buf[p+j]))&&buf[p+j]!=':';j++)
o,namebuf.str[j]= buf[p+j];
if(!j)panic("Empty item name");
if(j==8&&!isspace(buf[p+j])&&buf[p+j]!=':')
panic("Item name too long");
/*17:*/
#line 492 "./ssxcc.w"

for(k= (last_itm-1)<<2;k;k-= 4){
if(o,lname(k)!=namebuf.lr.l)continue;
if(rname(k)==namebuf.lr.r)break;
}
if(!k)panic("Unknown item name");
if(o,pos(k)> i)panic("Duplicate item name in this option");
last_node++;
if(last_node==max_nodes)panic("Too many nodes");
o,t= size(k);
o,nd[last_node].itm= k>>2,nd[last_node].loc= t;
if((k>>2)<second)pp= 1;
o,size(k)= t+1,pos(k)= last_node;

/*:17*/
#line 460 "./ssxcc.w"
;
if(buf[p+j]!=':')o,nd[last_node].clr= 0;
else if(k>=second){
if((o,isspace(buf[p+j+1]))||(o,!isspace(buf[p+j+2])))
panic("Color must be a single character");
o,nd[last_node].clr= (unsigned char)buf[p+j+1];
p+= 2;
}else panic("Primary item must be uncolored");
for(p+= j+1;o,isspace(buf[p]);p++);
}
if(!pp){
if(vbose&show_warnings)
fprintf(stderr,"Option ignored (no primary items): "O"s",buf);
while(last_node> i){
/*18:*/
#line 506 "./ssxcc.w"

o,k= nd[last_node].itm<<2;
oo,size(k)--,pos(k)= i-1;

/*:18*/
#line 474 "./ssxcc.w"
;
last_node--;
}
}else{
o,nd[i].loc= last_node-i;
last_node++;
if(last_node==max_nodes)panic("Too many nodes");
options++;
o,nd[last_node].itm= i+1-last_node;
nd[last_node].spr= options;
}
}
/*19:*/
#line 514 "./ssxcc.w"

itemlength= last_itm-1;
active= second= second-1;
for(k= 0,j= 4;k<itemlength;k++)
oo,item[k]= j,j+= 4+size((k+1)<<2)+(k+1>=second);
setlength= j-4-(k>=second);

/*:19*/
#line 486 "./ssxcc.w"
;
/*20:*/
#line 524 "./ssxcc.w"

for(;k;k--){
o,j= item[k-1];
oo,size(j)= size(k<<2);
o,pos(j)= k-1;
oo,rname(j)= rname(k<<2),lname(j)= lname(k<<2);
if(k>=second)o,color(j)= 0;
}

/*:20*/
#line 487 "./ssxcc.w"
;
/*21:*/
#line 533 "./ssxcc.w"

for(k= 1;k<last_node;k++){
if(o,nd[k].itm<0)continue;
o,j= item[nd[k].itm-1];
i= j+nd[k].loc;
o,nd[k].itm= j,nd[k].loc= i;
o,set[i]= k;
}

/*:21*/
#line 488 "./ssxcc.w"
;

/*:16*/
#line 57 "./ssxcc.w"
;
if(vbose&show_basics)
/*22:*/
#line 546 "./ssxcc.w"

fprintf(stderr,
"("O"lld options, "O"d+"O"d items, "O"d entries successfully read)\n",
options,second,last_itm-second-1,last_node);

/*:22*/
#line 59 "./ssxcc.w"
;
if(vbose&show_tots)
/*23:*/
#line 557 "./ssxcc.w"

{
fprintf(stderr,"Item totals:");
for(k= 0;k<itemlength;k++){
if(k==second)fprintf(stderr," |");
fprintf(stderr," "O"d",size(item[k]));
}
fprintf(stderr,"\n");
}

/*:23*/
#line 61 "./ssxcc.w"
;
imems= mems,mems= 0;
/*24:*/
#line 583 "./ssxcc.w"

level= 0;
forward:nodes++;
if(vbose&show_profile)profile[level]++;
if(sanity_checking)sanity();
/*26:*/
#line 623 "./ssxcc.w"

if(delta&&(mems>=thresh)){
thresh+= delta;
if(vbose&show_full_state)print_state();
else print_progress();
}
if(mems>=timeout){
fprintf(stderr,"TIMEOUT!\n");goto done;
}

/*:26*/
#line 588 "./ssxcc.w"
;
/*35:*/
#line 781 "./ssxcc.w"

t= max_nodes;
if((vbose&show_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap)
fprintf(stderr,"Level "O"d:",level);
for(k= 0;t&&(k<active);k++){
oo,s= size(item[k]);
if((vbose&show_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap){
print_item_name(item[k],stderr);
fprintf(stderr,"("O"d)",s);
}
if(s<t)best_itm= item[k],t= s;
}
if((vbose&show_details)&&
level<show_choices_max&&level>=maxl-show_choices_gap){
fprintf(stderr," branching on");
print_item_name(best_itm,stderr);
fprintf(stderr,"("O"d)\n",t);
}
if(t> maxdeg)maxdeg= t;
if(shape_file){
fprintf(shape_file,""O"d",t);
print_item_name(best_itm,shape_file);
fprintf(shape_file,"\n");
fflush(shape_file);
}

/*:35*/
#line 589 "./ssxcc.w"
;
if(t==0)goto donewithlevel;
cover(best_itm);
cur_choice= best_itm;
oo,cur_node= choice[level]= set[best_itm];
goto tryit;
advance:if(o,cur_choice>=best_itm+size(best_itm))goto backup;
oo,cur_node= choice[level]= set[cur_choice];
tryit:if((vbose&show_choices)&&level<show_choices_max){
fprintf(stderr,"L"O"d:",level);
print_option(cur_node,stderr);
}
/*31:*/
#line 696 "./ssxcc.w"

for(pp= cur_node+1;pp!=cur_node;){
o,cc= nd[pp].itm;
if(cc<0)pp+= cc;
else{
if(o,nd[pp].clr==0)cover(cc);
else if(nd[pp].clr> 0)purify(pp);
pp++;
}
}

/*:31*/
#line 601 "./ssxcc.w"
;
if(active==0)/*36:*/
#line 809 "./ssxcc.w"

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
/*37:*/
#line 826 "./ssxcc.w"

{
count++;
if(spacing&&(count mod spacing==0)){
printf(""O"lld:\n",count);
for(k= 0;k<=level;k++)print_option(choice[k],stdout);
fflush(stdout);
}
if(count>=maxcount)goto done;
goto recover;
}

/*:37*/
#line 823 "./ssxcc.w"
;
}

/*:36*/
#line 602 "./ssxcc.w"
;
if(++level> maxl){
if(level>=max_level){
fprintf(stderr,"Too many levels!\n");
exit(-4);
}
maxl= level;
}
goto forward;
backup:uncover(best_itm);
donewithlevel:if(level==0)goto done;
level--;
oo,cur_node= choice[level],best_itm= nd[cur_node].itm,cur_choice= nd[cur_node].loc;
recover:/*32:*/
#line 715 "./ssxcc.w"

for(pp= cur_node-1;pp!=cur_node;){
o,cc= nd[pp].itm;
if(cc<=0)pp+= nd[pp].loc;
else{
if(o,nd[pp].clr==0)uncover(cc);
else if(nd[pp].clr> 0)unpurify(pp);
pp--;
}
}

/*:32*/
#line 615 "./ssxcc.w"
;
cur_choice++;goto advance;

/*:24*/
#line 63 "./ssxcc.w"
;
done:if(sanity_checking)sanity();
if(vbose&show_tots)
/*23:*/
#line 557 "./ssxcc.w"

{
fprintf(stderr,"Item totals:");
for(k= 0;k<itemlength;k++){
if(k==second)fprintf(stderr," |");
fprintf(stderr," "O"d",size(item[k]));
}
fprintf(stderr,"\n");
}

/*:23*/
#line 66 "./ssxcc.w"
;
if(vbose&show_profile)/*40:*/
#line 892 "./ssxcc.w"

{
fprintf(stderr,"Profile:\n");
for(level= 0;level<=maxl;level++)
fprintf(stderr,""O"3d: "O"lld\n",
level,profile[level]);
}

/*:40*/
#line 67 "./ssxcc.w"
;
if(vbose&show_max_deg)
fprintf(stderr,"The maximum branching degree was "O"d.\n",maxdeg);
if(vbose&show_basics){
fprintf(stderr,"Altogether "O"llu solution"O"s, "O"llu+"O"llu mems,",
count,count==1?"":"s",imems,mems);
bytes= (itemlength+setlength)*sizeof(int)+last_node*sizeof(node)
+maxl*sizeof(int);
fprintf(stderr," "O"llu updates, "O"llu cleansings,",
updates,cleansings);
fprintf(stderr," "O"llu bytes, "O"llu nodes.\n",
bytes,nodes);
}
/*5:*/
#line 175 "./ssxcc.w"

if(shape_file)fclose(shape_file);

/*:5*/
#line 80 "./ssxcc.w"
;
}

/*:2*/
