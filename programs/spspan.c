#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define oooo mems+= 4
#define call oo \

#define verbose (argc> 2) 
#define extraverbose (argc> 3)  \

#define abort(mess) {fprintf(stderr,"Parsing error: %.*s|%s, %s!\n", \
p-argv[1],argv[1],p,mess) ;exit(-1) ;} \

#define maxn 1000 \

#define isleaf(p) ((p) <nodelist+maxn)  \

#define leafname(p) ('a'+((p) -nodelist) ) 
#define branchname(p) ('A'+((p) -root) ) 
#define nodename(p) (isleaf(p) ?leafname(p) :branchname(p) )  \

#define easy(p) o,p->typ==p->val \

#define done rchild \

/*1:*/
#line 39 "./spspan.w"

#include <stdio.h> 
/*6:*/
#line 103 "./spspan.w"

typedef struct node_struct{
int typ;
struct node_struct*lchild;
struct node_struct*rchild;
struct node_struct*rsib;
/*13:*/
#line 231 "./spspan.w"

int val;
struct node_struct*des;

/*:13*//*22:*/
#line 378 "./spspan.w"

struct node_struct*leaf;
struct node_struct*parent;

/*:22*//*25:*/
#line 466 "./spspan.w"

struct node_struct*focus;

/*:25*/
#line 109 "./spspan.w"

}node;

/*:6*/
#line 41 "./spspan.w"

/*3:*/
#line 81 "./spspan.w"

int stack[maxn];
int llink[maxn],rlink[maxn];

/*:3*//*7:*/
#line 115 "./spspan.w"

node nodelist[maxn+maxn];
node*curleaf;
node*curnode;
node*root,*topnode;

/*:7*/
#line 42 "./spspan.w"

unsigned int trees,mems;
/*9:*/
#line 141 "./spspan.w"

node*build(int stackitem,node*par)
{
register node*p,*l,*r,*lc,*rc;
register int t,j;
if(stackitem==0)return curleaf++;
t= stackitem>>8,j= stackitem&0xff;
if(t!=par->typ)p= ++curnode,p->typ= t;
else p= par;
l= build(llink[j],p),lc= l->lchild,rc= l->rchild,r= build(rlink[j],p);
if(l==p)/*11:*/
#line 160 "./spspan.w"

if(r==p)/*12:*/
#line 164 "./spspan.w"

rc->rsib= p->lchild,p->lchild= lc,p->rchild->rsib= lc;

/*:12*/
#line 161 "./spspan.w"

else p->rchild= r,rc->rsib= r,r->rsib= lc;

/*:11*/
#line 151 "./spspan.w"

else if(r==p)/*10:*/
#line 157 "./spspan.w"

r= p->lchild,p->lchild= l,l->rsib= r,p->rchild->rsib= l;

/*:10*/
#line 152 "./spspan.w"

else p->lchild= l,p->rchild= r,l->rsib= r,r->rsib= l;
return p;
}

/*:9*//*15:*/
#line 249 "./spspan.w"

void init_tree(node*p,node*par)
{
register node*q;
ooo,p->val= (par->des==p?par->val:par->typ);
if(isleaf(p))/*26:*/
#line 474 "./spspan.w"

p->leaf= p,p->parent= par;

/*:26*/
#line 254 "./spspan.w"

else{
oo,p->des= p->lchild;
for(q= p->lchild;;q= q->rsib){
call,init_tree(q,p);
if(o,q->rsib==p->lchild)break;
}
/*27:*/
#line 477 "./spspan.w"

p->leaf= p->des->leaf,p->parent= par;
o,p->focus= p;

/*:27*/
#line 261 "./spspan.w"
;
}
}

/*:15*//*16:*/
#line 279 "./spspan.w"

node*xx(char c)
{
if(c>='a')return nodelist+(c-'a');
return nodelist+maxn+(c-'@');
}

/*:16*//*17:*/
#line 286 "./spspan.w"

void printleaf(node*p)
{
printf("%c:%c rsib=%c\n",
leafname(p),p->val+'0',nodename(p->rsib));
}

void printbranch(node*p)
{
printf("%c:%c rsib=%c lchild=%c des=%c rchild=%c",
branchname(p),p->val+'0',nodename(p->rsib),
nodename(p->lchild),nodename(p->des),nodename(p->rchild));
/*28:*/
#line 481 "./spspan.w"

printf(" leaf=%c",leafname(p->leaf));
if(p->focus!=p)printf(" focus=%c",branchname(p->focus));

/*:28*/
#line 298 "./spspan.w"
;
printf("\n");
}

void printnode(node*p)
{
if(isleaf(p))printleaf(p);
else printbranch(p);
}

/*:17*//*18:*/
#line 308 "./spspan.w"

void printtree(node*p,int indent)
{
register node*q;
register int k;
for(k= 0;k<indent;k++)printf(" ");
printnode(p);
if(!isleaf(p))for(q= p->lchild;;q= q->rsib){
printtree(q,indent+1);
if(q->rsib==p->lchild)break;
}
}

/*:18*//*19:*/
#line 321 "./spspan.w"

void printedges(node*p)
{
register node*q;
if(isleaf(p)){
if(p->val)printf("%c",leafname(p));
}else for(q= p->lchild;;q= q->rsib){
printedges(q);
if(q->rsib==p->lchild)break;
}
}

/*:19*/
#line 44 "./spspan.w"

main(int argc,char*argv[])
{
register int j,k;
if(argc==1){
fprintf(stderr,"Usage: %s SPformula [[gory] details]\n",argv[0]);
exit(0);
}
/*2:*/
#line 68 "./spspan.w"

{
register char*p= argv[1];
for(j= k= 0;*p;p++)
if(*p=='-')/*4:*/
#line 89 "./spspan.w"

stack[k++]= 0;

/*:4*/
#line 72 "./spspan.w"

else if(*p=='s'||*p=='p')/*5:*/
#line 92 "./spspan.w"

{
if(k<2)abort("missing operand");
rlink[++j]= stack[--k];
llink[j]= stack[k-1];
stack[k-1]= (*p=='s'?0x100:0)+j;
}

/*:5*/
#line 73 "./spspan.w"

else abort("bad symbol");
if(k!=1)abort("disconnected graph");
/*8:*/
#line 125 "./spspan.w"

curleaf= nodelist;
topnode= curnode= nodelist+maxn;
curnode->typ= 2;
root= build(stack[0],curnode);
root->rsib= root;

/*:8*/
#line 76 "./spspan.w"
;
}

/*:2*/
#line 52 "./spspan.w"
;
/*14:*/
#line 240 "./spspan.w"

o,topnode->typ= 1;
call,init_tree(root,topnode);
trees= 1;
if(verbose)/*20:*/
#line 333 "./spspan.w"

{
if(extraverbose)printtree(root,0);
printf("The first spanning tree is ");
printedges(root);
printf(".\n");
}

/*:20*/
#line 244 "./spspan.w"
;

/*:14*/
#line 53 "./spspan.w"
;
printf(" (%u mems to get started)\n",mems);mems= 0;
/*29:*/
#line 487 "./spspan.w"

topnode->focus= topnode;
while(1){
register node*p,*q,*l,*r;
for(r= curnode;easy(r);r--);
oo,p= r->focus,r->focus= r;
if(p==topnode)break;
/*31:*/
#line 511 "./spspan.w"

oo,l= p->des,r= l->rsib;
o,k= p->val;
for(q= l;;o,q= q->des){
o,q->val= k^1;
if(isleaf(q))break;
}
if(verbose)printf(" %c%c",k?'-':'+',leafname(q));
for(q= r;;o,q= q->des){
o,q->val= k;
if(isleaf(q))break;
}
if(verbose)printf("%c%c\n",k?'+':'-',leafname(q));
o,p->des= r,trees++;
for(q= p;q->des==r;r= q,q= q->parent)q->leaf= r->leaf;

if(extraverbose){
printedges(root);
printf("; now %c->leaf=%c\n",branchname(r),leafname(r->leaf));
}

/*:31*/
#line 494 "./spspan.w"
;
if(o,p->des==p->done)/*30:*/
#line 501 "./spspan.w"

{
o,p->done= l;
for(l= p-1;easy(l);l--);
ooo,p->focus= l->focus,l->focus= l;
}

/*:30*/
#line 495 "./spspan.w"
;
}

/*:29*/
#line 55 "./spspan.w"
;
printf("Altogether %u spanning trees, %u additional mems.\n",trees,mems);
}

/*:1*/
