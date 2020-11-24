#define m 6
#define q ((m*(3*m+1) ) /2) 
#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define delta 10000000000;
#define O "%"
#define mod %
#define board(i,j) brd[3*(i) +(j) ]
#define leftknown colknown[0] \

#define sanity_checking 0 \

#define testedge(i,j,ii,jj) if(board(i,j) >=0&&board(ii,jj) >=0)  \
if(t--,!placed[abs(board(i,j) -board(ii,jj) ) ])  \
fprintf(stderr,"edge from ("O"d,"O"d) to ("O"d,"O"d) not placed!\n", \
i,j,ii,jj) ; \

#define pack(row,col,val) (((col) <<12) +((row) <<8) +(val) )  \

/*1:*/
#line 37 "./back-graceful-kmp3.w"

#include <stdio.h> 
#include <stdlib.h> 
unsigned long long mems;
unsigned long long thresh= delta;
unsigned long long nodes;
unsigned long long nulls;
unsigned long long leaves;
int count;
int brd[3*m];
int rank;
int labeled[q+1];
int placed[q+1];
int colknown[3];
int move[q][1024];
int deg[q];
int x[q];
int maxl;
int vbose= 0;
/*3:*/
#line 89 "./back-graceful-kmp3.w"

void print_board(int rank){
register int i,j;
for(i= 0;i<rank;i++){
for(j= 0;j<3;j++)
if(board(i,j)>=0)fprintf(stderr,""O"3d",board(i,j));
else fprintf(stderr,"  ?");
fprintf(stderr,"\n");
}
}

/*:3*//*4:*/
#line 100 "./back-graceful-kmp3.w"

void print_placed(void){
register int k;
for(k= 1;k<=q;k++){
if(placed[k]){
if(!placed[k-1])fprintf(stderr," "O"d",k);
else if(k==q||!placed[k+1])fprintf(stderr,".."O"d",k);
}
}
fprintf(stderr,"\n");
}

/*:4*//*5:*/
#line 117 "./back-graceful-kmp3.w"

void sanity(void){
register int i,j,l,t,v;
/*6:*/
#line 125 "./back-graceful-kmp3.w"

for(i= rank;i<m;i++){
if(board(i,0)>=0)break;
if(board(i,1)>=0)break;
if(board(i,2)>=0)break;
}
if(i<m||rank> m)fprintf(stderr,"rank shouldn't be "O"d!\n",rank);

/*:6*/
#line 120 "./back-graceful-kmp3.w"
;
/*7:*/
#line 133 "./back-graceful-kmp3.w"

for(l= 0;l<=q;l++){
v= labeled[l];
if(v>=0&&board(v&0xf,v>>4)!=l)
fprintf(stderr,"labeled["O"d] not on the board!\n",l);
}
for(i= 0;i<rank;i++)for(j= 0;j<3;j++){
if(board(i,j)> q)fprintf(stderr,"board("O"d,"O"d) out of range!\n",i,j);
if(board(i,j)>=0&&labeled[board(i,j)]!=(j<<4)+i)
fprintf(stderr,"label of board("O"d,"O"d) is wrong!\n",i,j);
}

/*:7*/
#line 121 "./back-graceful-kmp3.w"
;
/*8:*/
#line 150 "./back-graceful-kmp3.w"

for(t= 0,l= 1;l<=q;l++)t+= placed[l];
for(i= 0;i<rank;i++){
testedge(i,0,i,1);
testedge(i,1,i,2);
for(j= i+1;j<rank;j++){
testedge(i,0,j,0);
testedge(i,1,j,1);
testedge(i,2,j,2);
}
}
if(t)fprintf(stderr,"placement count off by "O"d!\n",t);

/*:8*/
#line 122 "./back-graceful-kmp3.w"
;
}

/*:5*//*11:*/
#line 226 "./back-graceful-kmp3.w"

void print_progress(int level){
register int l,k,d,c,p;
register double f,fd;
fprintf(stderr," after "O"lld mems: "O"d sols,",mems,count);
for(f= 0.0,fd= 1.0,l= 0;l<level;l++){
d= deg[l],k= d-x[l];
fd*= d,f+= (k-1)/fd;
fprintf(stderr," "O"c"O"c",
k<10?'0'+k:k<36?'a'+k-10:k<62?'A'+k-36:'*',
d<10?'0'+d:d<36?'a'+d-10:d<62?'A'+d-36:'*');
}
fprintf(stderr," "O".5f\n",f+0.5/fd);
}

/*:11*//*13:*/
#line 258 "./back-graceful-kmp3.w"

void print_move(int mv){
if(!mv)
fprintf(stderr,"null");
else if(mv<0x10000)
fprintf(stderr,""O"d"O"d="O"d",(mv>>8)&0xf,(mv>>12)&0xf,mv&0xff);
else fprintf(stderr,""O"d"O"d="O"d,"O"d"O"d="O"d",
(mv>>8)&0xf,(mv>>12)&0xf,mv&0xff,(mv>>24)&0xf,(mv>>28)&0xf,(mv>>16)&0xff);
}

void print_moves(int level){
register int i;
for(i= deg[level]-1;i>=0;i--){
fprintf(stderr,""O"d:",deg[level]-i);
print_move(move[level][i]);
fprintf(stderr,"\n");
}
}

/*:13*//*14:*/
#line 277 "./back-graceful-kmp3.w"

void print_state(int levels){
register int l;
for(l= 0;l<levels;l++){
print_move(move[l][x[l]]);
fprintf(stderr," ("O"d of "O"d)\n",deg[l]-x[l],deg[l]);
}
}

/*:14*//*20:*/
#line 404 "./back-graceful-kmp3.w"

int legal_in_col(val,col){
register int i,v;
if(o,colknown[col]==m)return 0;
for(i= 0;i<rank;i++){
o,v= board(i,col);
if(v>=0&&(o,placed[abs(v-val)]))return 0;
}
return 1;
}

/*:20*/
#line 56 "./back-graceful-kmp3.w"

main(){
register int a,b,i,j,k,l,t,v,aa,bb,ii,row,col,ccol,val,mv,trouble;
fprintf(stderr,"--- Graceful labelings of K"O"d times P3 ---\n",m);
/*2:*/
#line 83 "./back-graceful-kmp3.w"

for(i= 0;i<m;i++)for(j= 0;j<3;j++)board(i,j)= -1;
rank= 0;
for(l= 0;l<=q;l++)labeled[l]= -1;
l= 0;

/*:2*/
#line 60 "./back-graceful-kmp3.w"
;
/*9:*/
#line 178 "./back-graceful-kmp3.w"

enter:nodes++;
if(mems>=thresh){
thresh+= delta;
print_progress(l);
}
if(sanity_checking)sanity();
if(l<=1)/*15:*/
#line 294 "./back-graceful-kmp3.w"

if(l==0){
o,move[0][0]= (pack(1,1,0)<<16)+pack(0,1,q);
o,move[0][1]= (pack(1,0,0)<<16)+pack(0,0,q);
o,move[0][2]= (pack(0,1,0)<<16)+pack(0,0,q);
t= 3;
goto ready;
}else if(o,x[0]!=2){
t= (m==2?1:2);
o,move[1][0]= pack(0,x[0],1);
if(m> 2)o,move[1][1]= pack(2,1-x[0],1);
goto ready;
}

/*:15*/
#line 185 "./back-graceful-kmp3.w"
;
if(l>=maxl){
maxl= l;
if(l==q)/*10:*/
#line 217 "./back-graceful-kmp3.w"

{
count++;
printf(""O"d:\n",count);
for(i= 0;i<m;i++)
printf(""O"3d"O"3d"O"3d\n",board(i,0),board(i,1),board(i,2));
goto backup;
}

/*:10*/
#line 188 "./back-graceful-kmp3.w"
;
}
if(o,placed[q-l])/*12:*/
#line 252 "./back-graceful-kmp3.w"

{
o,move[l][0]= 0,t= 1,nulls++;
goto ready;
}

/*:12*/
#line 190 "./back-graceful-kmp3.w"
;
for(t= a= 0,b= q-l;b<=q;a++,b++)
/*18:*/
#line 363 "./back-graceful-kmp3.w"

{
oo,aa= labeled[a],bb= labeled[b];
if(aa>=0){
if(bb>=0)continue;
row= aa&0xf,col= aa>>4;
/*19:*/
#line 377 "./back-graceful-kmp3.w"

switch(col){
case 0:if((o,board(row,1)<0)&&legal_in_col(b,1)&&
((o,board(row,2)<0)||(o,!placed[abs(b-board(row,2))])))
o,move[l][t++]= pack(row,1,b);
break;
case 1:if((o,board(row,0)<0)&&legal_in_col(b,0))
o,move[l][t++]= pack(row,0,b);
if((o,leftknown)&&(o,board(row,2)<0)&&legal_in_col(b,2))
o,move[l][t++]= pack(row,2,b);
break;
case 2:if((o,board(row,1)<0)&&legal_in_col(b,1)&&
((o,board(row,0)<0)||(o,!placed[abs(b-board(row,0))])))
o,move[l][t++]= pack(row,1,b);
break;
}
if(legal_in_col(b,col)){
for(i= 0;i<rank;i++)if(o,board(i,col)<0){
if(col> 0&&(o,board(i,col-1)>=0)&&
(o,placed[abs(b-board(i,col-1))]))continue;
if(col<2&&(o,board(i,col+1)>=0)&&
(o,placed[abs(b-board(i,col+1))]))continue;
o,move[l][t++]= pack(i,col,b);
}
if(rank<m)o,move[l][t++]= pack(rank,col,b);
}

/*:19*/
#line 369 "./back-graceful-kmp3.w"
;
}else if(bb>=0){
row= bb&0xf,col= bb>>4;
/*21:*/
#line 415 "./back-graceful-kmp3.w"

switch(col){
case 0:if((o,board(row,1)<0)&&legal_in_col(a,1)&&
((o,board(row,2)<0)||(o,!placed[abs(a-board(row,2))])))
o,move[l][t++]= pack(row,1,a);
break;
case 1:if((o,board(row,0)<0)&&legal_in_col(a,0))
o,move[l][t++]= pack(row,0,a);
if((o,leftknown)&&(o,board(row,2)<0)&&legal_in_col(a,2))
o,move[l][t++]= pack(row,2,a);
break;
case 2:if((o,board(row,1)<0)&&legal_in_col(a,1)&&
((o,board(row,0)<0)||(o,!placed[abs(a-board(row,0))])))
o,move[l][t++]= pack(row,1,a);
break;
}
if(legal_in_col(a,col)){
for(i= 0;i<rank;i++)if(o,board(i,col)<0){
if(col> 0&&(o,board(i,col-1)>=0)&&
(o,placed[abs(a-board(i,col-1))]))continue;
if(col<2&&(o,board(i,col+1)>=0)&&
(o,placed[abs(a-board(i,col+1))]))continue;
o,move[l][t++]= pack(i,col,a);
}
if(rank<m)o,move[l][t++]= pack(rank,col,a);
}

/*:21*/
#line 372 "./back-graceful-kmp3.w"
;
}
else/*22:*/
#line 447 "./back-graceful-kmp3.w"

for(o,ccol= (leftknown?2:1);ccol>=0;ccol--)if(legal_in_col(a,ccol)){
for(ii= 0;ii<rank;ii++)if(o,board(ii,ccol)<0){
if(ccol> 0&&(o,board(ii,ccol-1)>=0)&&
(o,placed[abs(a-board(ii,ccol-1))]))continue;
if(ccol<2&&(o,board(ii,ccol+1)>=0)&&
(o,placed[abs(a-board(ii,ccol+1))]))continue;
aa= mv= pack(ii,ccol,a);/*16:*/
#line 310 "./back-graceful-kmp3.w"

for(trouble= 0;mv;mv>>= 16){
val= mv&0xff,row= (mv>>8)&0xf,col= (mv>>12)&0xf;
o,labeled[val]= (mv>>8)&0xff;
o,board(row,col)= val;
oo,colknown[col]++;
if(col> 0){
o,v= board(row,col-1);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
if(col<2){
o,v= board(row,col+1);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
for(i= 0;i<rank;i++)if(i!=row){
o,v= board(i,col);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
if(row==rank)rank++;
}

/*:16*/
#line 454 "./back-graceful-kmp3.w"
;mv= aa;
if(!trouble)/*23:*/
#line 465 "./back-graceful-kmp3.w"

{
switch(col){
case 0:if((o,board(row,1)<0)&&legal_in_col(b,1)&&
((o,board(row,2)<0)||(o,!placed[abs(b-board(row,2))])))
o,move[l][t++]= (pack(row,1,b)<<16)+mv;
break;
case 1:if((o,board(row,0)<0)&&legal_in_col(b,0))
o,move[l][t++]= (pack(row,0,b)<<16)+mv;
if((o,leftknown)&&(o,board(row,2)<0)&&legal_in_col(b,2))
o,move[l][t++]= (pack(row,2,b)<<16)+mv;
break;
case 2:if((o,board(row,1)<0)&&legal_in_col(b,1)&&
((o,board(row,0)<0)||(o,!placed[abs(b-board(row,0))])))
o,move[l][t++]= (pack(row,1,b)<<16)+mv;
break;
}
if(legal_in_col(b,col)){
for(i= 0;i<rank;i++)if(o,board(i,col)<0){
if(col> 0&&(o,board(i,col-1)>=0)&&
(o,placed[abs(b-board(i,col-1))]))continue;
if(col<2&&(o,board(i,col+1)>=0)&&
(o,placed[abs(b-board(i,col+1))]))continue;
o,move[l][t++]= (pack(i,col,b)<<16)+mv;
}
if(rank<m)o,move[l][t++]= (pack(rank,col,b)<<16)+mv;
}
}

/*:23*/
#line 455 "./back-graceful-kmp3.w"
;
/*17:*/
#line 331 "./back-graceful-kmp3.w"

if(mv>=0x10000)mv= (mv>>16)+((mv&0xffff)<<16);
for(;mv;mv>>= 16){
val= mv&0xff,row= (mv>>8)&0xf,col= (mv>>12)&0xf;
if(row==rank-1&&(o,board(row,(col+1)mod 3)<0)&&
(o,board(row,(col+2)mod 3)<0))
rank= row;
o,labeled[val]= -1;
o,board(row,col)= -1;
oo,colknown[col]--;
if(col> 0){
o,v= board(row,col-1);
if(v>=0)o,placed[abs(val-v)]= 0;
}
if(col<2){
o,v= board(row,col+1);
if(v>=0)o,placed[abs(val-v)]= 0;
}
for(i= 0;i<rank;i++)if(i!=row){
o,v= board(i,col);
if(v>=0)o,placed[abs(val-v)]= 0;
}
}

/*:17*/
#line 456 "./back-graceful-kmp3.w"
;
}
if(rank<m){
aa= mv= pack(rank,ccol,a);/*16:*/
#line 310 "./back-graceful-kmp3.w"

for(trouble= 0;mv;mv>>= 16){
val= mv&0xff,row= (mv>>8)&0xf,col= (mv>>12)&0xf;
o,labeled[val]= (mv>>8)&0xff;
o,board(row,col)= val;
oo,colknown[col]++;
if(col> 0){
o,v= board(row,col-1);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
if(col<2){
o,v= board(row,col+1);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
for(i= 0;i<rank;i++)if(i!=row){
o,v= board(i,col);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
if(row==rank)rank++;
}

/*:16*/
#line 459 "./back-graceful-kmp3.w"
;mv= aa;
if(!trouble)/*23:*/
#line 465 "./back-graceful-kmp3.w"

{
switch(col){
case 0:if((o,board(row,1)<0)&&legal_in_col(b,1)&&
((o,board(row,2)<0)||(o,!placed[abs(b-board(row,2))])))
o,move[l][t++]= (pack(row,1,b)<<16)+mv;
break;
case 1:if((o,board(row,0)<0)&&legal_in_col(b,0))
o,move[l][t++]= (pack(row,0,b)<<16)+mv;
if((o,leftknown)&&(o,board(row,2)<0)&&legal_in_col(b,2))
o,move[l][t++]= (pack(row,2,b)<<16)+mv;
break;
case 2:if((o,board(row,1)<0)&&legal_in_col(b,1)&&
((o,board(row,0)<0)||(o,!placed[abs(b-board(row,0))])))
o,move[l][t++]= (pack(row,1,b)<<16)+mv;
break;
}
if(legal_in_col(b,col)){
for(i= 0;i<rank;i++)if(o,board(i,col)<0){
if(col> 0&&(o,board(i,col-1)>=0)&&
(o,placed[abs(b-board(i,col-1))]))continue;
if(col<2&&(o,board(i,col+1)>=0)&&
(o,placed[abs(b-board(i,col+1))]))continue;
o,move[l][t++]= (pack(i,col,b)<<16)+mv;
}
if(rank<m)o,move[l][t++]= (pack(rank,col,b)<<16)+mv;
}
}

/*:23*/
#line 460 "./back-graceful-kmp3.w"
;
/*17:*/
#line 331 "./back-graceful-kmp3.w"

if(mv>=0x10000)mv= (mv>>16)+((mv&0xffff)<<16);
for(;mv;mv>>= 16){
val= mv&0xff,row= (mv>>8)&0xf,col= (mv>>12)&0xf;
if(row==rank-1&&(o,board(row,(col+1)mod 3)<0)&&
(o,board(row,(col+2)mod 3)<0))
rank= row;
o,labeled[val]= -1;
o,board(row,col)= -1;
oo,colknown[col]--;
if(col> 0){
o,v= board(row,col-1);
if(v>=0)o,placed[abs(val-v)]= 0;
}
if(col<2){
o,v= board(row,col+1);
if(v>=0)o,placed[abs(val-v)]= 0;
}
for(i= 0;i<rank;i++)if(i!=row){
o,v= board(i,col);
if(v>=0)o,placed[abs(val-v)]= 0;
}
}

/*:17*/
#line 461 "./back-graceful-kmp3.w"
;
}
}

/*:22*/
#line 374 "./back-graceful-kmp3.w"
;
}

/*:18*/
#line 192 "./back-graceful-kmp3.w"
;
ready:deg[l]= t;
if(!t)leaves++;
tryit:if(t==0)goto backup;
advance:if(vbose){
fprintf(stderr,"L"O"d: ",l);
print_move(move[l][t-1]);
fprintf(stderr," ("O"d of "O"d)\n",deg[l]-t+1,deg[l]);
}
o,x[l]= --t;
o,mv= move[l][t];
/*16:*/
#line 310 "./back-graceful-kmp3.w"

for(trouble= 0;mv;mv>>= 16){
val= mv&0xff,row= (mv>>8)&0xf,col= (mv>>12)&0xf;
o,labeled[val]= (mv>>8)&0xff;
o,board(row,col)= val;
oo,colknown[col]++;
if(col> 0){
o,v= board(row,col-1);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
if(col<2){
o,v= board(row,col+1);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
for(i= 0;i<rank;i++)if(i!=row){
o,v= board(i,col);
if(v>=0)oo,trouble+= placed[abs(val-v)],placed[abs(val-v)]= 1;
}
if(row==rank)rank++;
}

/*:16*/
#line 203 "./back-graceful-kmp3.w"
;
if(trouble){
if(vbose)fprintf(stderr," -- was bad\n");
goto unmake;
}
l++;
goto enter;
backup:if(--l>=0){
o,t= x[l];
unmake:o,mv= move[l][t];
/*17:*/
#line 331 "./back-graceful-kmp3.w"

if(mv>=0x10000)mv= (mv>>16)+((mv&0xffff)<<16);
for(;mv;mv>>= 16){
val= mv&0xff,row= (mv>>8)&0xf,col= (mv>>12)&0xf;
if(row==rank-1&&(o,board(row,(col+1)mod 3)<0)&&
(o,board(row,(col+2)mod 3)<0))
rank= row;
o,labeled[val]= -1;
o,board(row,col)= -1;
oo,colknown[col]--;
if(col> 0){
o,v= board(row,col-1);
if(v>=0)o,placed[abs(val-v)]= 0;
}
if(col<2){
o,v= board(row,col+1);
if(v>=0)o,placed[abs(val-v)]= 0;
}
for(i= 0;i<rank;i++)if(i!=row){
o,v= board(i,col);
if(v>=0)o,placed[abs(val-v)]= 0;
}
}

/*:17*/
#line 213 "./back-graceful-kmp3.w"
;
goto tryit;
}

/*:9*/
#line 61 "./back-graceful-kmp3.w"
;
fprintf(stderr,"Altogether "O"d solution"O"s,",
count,count==1?"":"s");
fprintf(stderr," "O"lld mems, "O"lld-"O"lld nodes, "O"lld leaves;",
mems,nodes,nulls,leaves);
fprintf(stderr," max level "O"d.\n",maxl);
if(sanity_checking)fprintf(stderr,"sanity_checking was on!\n");
}

/*:1*/
