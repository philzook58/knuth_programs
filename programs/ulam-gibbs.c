#define show_usage_stats 1
#define show_compression_stats 2
#define show_histograms 4
#define show_gap_stats 8
#define show_record_gaps 16
#define show_record_outliers 32
#define show_outlier_details 64
#define show_record_cutoffs 128
#define show_omitted_inliers 256
#define show_brute_winners 512
#define show_inlier_anchors 1024 \

#define o mems++
#define oo mems+= 2
#define ooo mems+= 3
#define O "%"
#define mod % \

#define alloc_quit(name,size) { \
fprintf(stderr,"Couldn't allocate the "O"s array (size "O"lld)!\n", \
name,(long long) size) ; \
exit(-666) ; \
} \

#define bar(r) (lamp-(r) ) 
#define lo_out 0
#define hi_out 1 \

#define null 0
#define danger 1 \

#define insert(head,u,r) if(!ins(head,u,r) ) { \
fprintf(stderr,"Oh oh, there's outlier overflow (size="O"d)!\n", \
outliers) ; \
goto finish_up; \
} \

#define flag 0x80000000
#define panic(m) { \
fprintf(stderr,"Oops, "O"s! (h="O"d, r="O"d, j="O"d, x="O"d)\n", \
m,h,r,j,x) ; \
return; \
} \

#define bincolors 16
#define binsize 128 \

#define dump_stats(st) fprintf(stderr, \
"n "O"lld, mean "O"g, max "O"d ("O"lld)\n", \
st.n,st.mean,st.max,st.ex) ; \

/*4:*/
#line 128 "./ulam-gibbs.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ullng;
/*9:*/
#line 216 "./ulam-gibbs.w"

typedef struct{
ullng n;
float mean;
int max;
ullng ex;
}stat;

/*:9*//*24:*/
#line 556 "./ulam-gibbs.w"

typedef struct{
ullng u;
int r;
int next;
}node;

/*:24*/
#line 135 "./ulam-gibbs.w"

/*6:*/
#line 164 "./ulam-gibbs.w"

ullng maxn;
int vbose= show_usage_stats;
uint lamp= 120500181;
uint lamq= 49315733;
ullng spacing;
ullng misses;
int biggestgap= 1;
int maxgap= 2000;
int outliers= 1000000;

int isize= 100000;
double thresh= 100;
ullng mems,last_mems;
clock_t last_clock;
ullng bytes;
int bits_per_compressed_byte= 18;
int uncompressed_bytes= 18000;
ullng window_size= 1000000;
FILE*mp_file;
char*mp_name;

/*:6*//*15:*/
#line 425 "./ulam-gibbs.w"

uchar*is_ulam,*is_um;
ullng cur_sl;
ullng cur_slot;
uint cur_code= 0;
uint code[256];
uchar*inv_code;
int code_ptr= 1;
ullng code_use[256],code_example[256];

/*:15*//*25:*/
#line 578 "./ulam-gibbs.w"

ullng*window;
int nw;
node*nmem;
int node_ptr= 2;
uint*inx[2];
uint avail;
stat ins_stats[4];

/*:25*//*35:*/
#line 802 "./ulam-gibbs.w"

stat window_stats;
ullng yes_bin[bincolors][binsize],miss_bin[bincolors][binsize];
ullng alpha;
int beta;

/*:35*//*45:*/
#line 934 "./ulam-gibbs.w"

double lampthresh;
int lowest_outlier,highest_outlier;
ullng prevu;
ullng*gapcount;
int rbound,rbarbound;
ullng ubound;
int anchorx;
int lo_r_bound,hi_r_bound;
ullng prevmisses;
ullng prevmems;
clock_t prevclock;
stat lo_out_stats,hi_out_stats;
int ulamness;

/*:45*//*57:*/
#line 1155 "./ulam-gibbs.w"

ullng acc[binsize];
int prev[binsize];
double factor;


/*:57*/
#line 136 "./ulam-gibbs.w"

/*10:*/
#line 224 "./ulam-gibbs.w"

void record_stat(stat*s,int datum,ullng u){
if(s->n==0)s->n= 1,s->mean= (float)datum,s->max= datum,s->ex= u;
else{
s->n++;
s->mean+= ((float)datum-s->mean)/((float)s->n);
if(datum> s->max)s->max= datum,s->ex= u;
}
}

/*:10*//*18:*/
#line 476 "./ulam-gibbs.w"

int ulamq(ullng x){
register int c,r,t;
register ullng q;
if(x>=cur_slot)
return(cur_code&(1<<(x-cur_slot)));
if(x<uncompressed_bytes)
return is_ulam[x];
q= x/bits_per_compressed_byte,r= x mod bits_per_compressed_byte;
o,c= is_um[q];
o,t= code[c];
return t&(1<<r);
}

/*:18*//*28:*/
#line 625 "./ulam-gibbs.w"

int ins(int head,ullng u,register int r){
register int j,x,y,z,count;
if(avail)o,z= avail,avail= nmem[avail].next;
else if(node_ptr<2+outliers)z= node_ptr++;
else return 0;
oo,nmem[z].u= u,nmem[z].r= r;
if(vbose&show_outlier_details)
fprintf(stderr," (remembering "O"soutlier "O"lld, "O"s="O"d)\n",
r> lamp/3?"near-":"",u,head==hi_out?"rbar":"r",r);
j= ((ullng)r*isize)/lamp;
o,x= inx[head][j];
for(o,y= nmem[x].next,count= 1;
y> danger&&(o,nmem[y].r<=r);
o,x= y,y= nmem[x].next)count++;
oo,nmem[x].next= z,nmem[z].next= y;
for(j++;j<=isize/2;j++,count++){
if(oo,nmem[inx[head][j]].r> r)break;
o,inx[head][j]= z;
}
record_stat(&ins_stats[head],count,u);
return 1;
}

/*:28*//*29:*/
#line 658 "./ulam-gibbs.w"

void delete(int head,ullng u,register int r){
register int j,x,y,count;
ullng uu;
j= ((ullng)r*isize)/lamp;
o,x= inx[head][j];
for(o,y= nmem[x].next,count= 1;
y> danger&&(o,nmem[y].r<=r);
o,x= y,y= nmem[x].next)count++;
o,nmem[x].next= danger;
if(y> danger){
for(x= y;o,nmem[y].next> danger;count++){
if(vbose&show_outlier_details){
r= nmem[y].r,uu= nmem[y].u;
fprintf(stderr," (forgetting "O"soutlier "O"lld, "O"s="O"d)\n",
r> lamp/3?"near-":"",uu,head==hi_out?"rbar":"r",r);
}
y= nmem[y].next;
}
o,nmem[y].next= avail,avail= x;
}
record_stat(&ins_stats[head],count,u);
}

/*:29*//*30:*/
#line 692 "./ulam-gibbs.w"

void sanity(void){
register int h,j,nextj,x,y,r,lastr;
ullng u,lastu;
for(h= lo_out;h<=hi_out;h++){
lastr= 0,lastu= 0,j= 1;
for(x= h;;x= y){
r= nmem[x].r,u= nmem[x].u,y= nmem[x].next;
if(r<lastr||(r==lastr&&u<lastu))panic("Out of order");
nextj= ((ullng)r*isize)/lamp;
for(;j<=nextj;j++)
if(!(nmem[inx[h][j]].next&flag))panic("Index bad");
nmem[x].next= y+flag;
if(y<=danger)break;
lastr= r,lastu= u;
}
for(x= h;;x= y){
y= nmem[x].next-flag;
nmem[x].next= y;
if(y<=danger)break;
}
}
}

/*:30*/
#line 137 "./ulam-gibbs.w"

main(int argc,char*argv[]){
register int i,j,k,r,rp,t,x,y,hits,count;
register ullng n,u,up;
/*5:*/
#line 153 "./ulam-gibbs.w"

if(argc==1)k= 1;
else{
k= sscanf(argv[argc-1],""O"lld",&maxn)-1;
for(j= argc-2;j;j--)switch(argv[j][0]){
/*7:*/
#line 186 "./ulam-gibbs.w"

case'v':k|= (sscanf(argv[j]+1,""O"d",&vbose)-1);break;
case'p':k|= (sscanf(argv[j]+1,""O"u",&lamp)-1);break;
case'q':k|= (sscanf(argv[j]+1,""O"u",&lamq)-1);break;
case'm':k|= (sscanf(argv[j]+1,""O"lld",&spacing)-1);break;
case'g':k|= (sscanf(argv[j]+1,""O"d",&maxgap)-1);break;
case'o':k|= (sscanf(argv[j]+1,""O"d",&outliers)-1);break;
case'i':k|= (sscanf(argv[j]+1,""O"d",&isize)-1);
isize= (isize+1)&-2;break;
case'T':k|= (sscanf(argv[j]+1,""O"lg",&thresh)-1);break;
case'b':k|= (sscanf(argv[j]+1,""O"d",&bits_per_compressed_byte)-1);break;
case'B':k|= (sscanf(argv[j]+1,""O"d",&uncompressed_bytes)-1);break;
case'w':k|= (sscanf(argv[j]+1,""O"lld",&window_size)-1);break;
case'M':mp_name= argv[j]+1,mp_file= fopen(mp_name,"w");
if(!mp_file)
fprintf(stderr,"Sorry, I can't open file `"O"s' for writing!\n",mp_name);
break;

/*:7*/
#line 158 "./ulam-gibbs.w"
;
default:k= 1;
}
}
/*8:*/
#line 204 "./ulam-gibbs.w"

if(k||uncompressed_bytes<3||
uncompressed_bytes mod bits_per_compressed_byte||
(lamp-1)/lamq!=2||window_size<3){
fprintf(stderr,
"Usage: "O"s [v<n>] [p<n>] [q<n>] [m<n>] [g<n>] [o<n>] [i<n>]",argv[0]);
fprintf(stderr," [T<f>] [b<n>] [B<n>] [w<n>] [Mfoo.mp] N\n");
exit(-1);
}

/*:8*/
#line 162 "./ulam-gibbs.w"
;

/*:5*/
#line 141 "./ulam-gibbs.w"
;
/*16:*/
#line 453 "./ulam-gibbs.w"

is_ulam= (uchar*)malloc(uncompressed_bytes*sizeof(uchar));
if(!is_ulam)alloc_quit("is_ulam",uncompressed_bytes);
bytes+= uncompressed_bytes*sizeof(uchar);
u= (14*maxn-1)/bits_per_compressed_byte+1;
is_um= (uchar*)malloc(u*sizeof(uchar));
if(!is_um)alloc_quit("is_um",u);
bytes+= u*sizeof(uchar);
inv_code= (uchar*)calloc(1<<bits_per_compressed_byte,sizeof(uchar));
if(!inv_code)alloc_quit("inv_code",1<<bits_per_compressed_byte);
bytes+= (1<<bits_per_compressed_byte)*sizeof(uchar);

bytes+= 256*sizeof(uint);
/*:16*//*22:*/
#line 533 "./ulam-gibbs.w"

window= (ullng*)malloc(window_size*sizeof(ullng));
if(!window)alloc_quit("window",window_size);
bytes+= window_size*sizeof(ullng);

/*:22*//*26:*/
#line 587 "./ulam-gibbs.w"

nmem= (node*)malloc((2+outliers)*sizeof(node));
if(!nmem)alloc_quit("nmem",outliers);
bytes+= (2+outliers)*sizeof(node);
inx[0]= (uint*)malloc((isize/2+1)*sizeof(uint));
if(!inx[0])alloc_quit("inx[0]",outliers);
inx[1]= (uint*)malloc((isize/2+1)*sizeof(uint));
if(!inx[1])alloc_quit("inx[1]",outliers);
bytes+= (isize+2)*sizeof(uint);

/*:26*//*46:*/
#line 949 "./ulam-gibbs.w"

gapcount= (ullng*)malloc((maxgap+2)*sizeof(ullng));
if(!gapcount)alloc_quit("gapcount",maxgap);
bytes+= (maxgap+2)*sizeof(ullng);

/*:46*/
#line 142 "./ulam-gibbs.w"
;
/*17:*/
#line 468 "./ulam-gibbs.w"

ooo,is_ulam[0]= 0,is_ulam[1]= is_ulam[2]= 1;
cur_slot= uncompressed_bytes,cur_sl= cur_slot/bits_per_compressed_byte;

/*:17*//*27:*/
#line 605 "./ulam-gibbs.w"

oo,nmem[lo_out].next= null,nmem[lo_out].r= 0;
oo,nmem[hi_out].next= null,nmem[hi_out].r= 0;
for(i= 0;i<=isize/2;i++)oo,inx[0][i]= lo_out,inx[1][i]= hi_out;
avail= 0;

/*:27*//*31:*/
#line 723 "./ulam-gibbs.w"

oo,window[1]= 1,window[2]= 2;
n= nw= misses= 2;
insert(lo_out,1,lamq);
insert(hi_out,2,bar(2*lamq));
if(spacing==1)printf("U1=1\n");
if(spacing==1||spacing==2)printf("U2=2\n");

/*:31*//*36:*/
#line 808 "./ulam-gibbs.w"

alpha= ((maxn-1)/bincolors)+1,beta= ((lamp-1)/binsize)+1;
yes_bin[0/alpha][lamq/beta]= 1,miss_bin[0/alpha][lamq/beta]= 1;
yes_bin[1/alpha][(2*lamq)/beta]= 1,miss_bin[1/alpha][(2*lamq)/beta]= 1;

/*:36*//*47:*/
#line 956 "./ulam-gibbs.w"

lampthresh= lamp*thresh;
lowest_outlier= lo_r_bound= hi_r_bound= lamp;
highest_outlier= 2*lamq;
gapcount[1]= 1;
prevu= 2;

/*:47*/
#line 143 "./ulam-gibbs.w"
;
for(u= 3;n<maxn;u++)
/*32:*/
#line 739 "./ulam-gibbs.w"

{
/*33:*/
#line 759 "./ulam-gibbs.w"

r= u mod lamp;
r= (lamq*(ullng)r)mod lamp;

/*:33*/
#line 741 "./ulam-gibbs.w"
;
hits= 0;
if(r<=lamp>>2||bar(r)<=lamp>>2)
/*34:*/
#line 769 "./ulam-gibbs.w"

{
x= nw;
for(o,up= window[x],count= 1;up> (u>>1);o,up= window[x]){
if(ulamq(u-up)){
if(hits){
record_stat(&window_stats,count,u);
goto not_ulam;
}
hits= 1;
}
if(++count> window_size){
fprintf(stderr,"Oh oh, there's window overflow (size="O"lld)!\n",
window_size);
goto finish_up;
}
if(x)x--;else x= window_size-1;
}
record_stat(&window_stats,count,u);
if(vbose&show_brute_winners)
fprintf(stderr," (in brute-force phase, "O"lld is an Ulam "O"s)\n",
u,hits?"number":"miss");
if(hits)goto ulam_yes;
}

/*:34*/
#line 744 "./ulam-gibbs.w"

else/*48:*/
#line 971 "./ulam-gibbs.w"

/*49:*/
#line 986 "./ulam-gibbs.w"

rbound= r>>1,ubound= (u-1)>>1;
for(o,x= nmem[lo_out].next,count= 1;;o,x= nmem[x].next,count++){
if(x<=danger)break;
oo,rp= nmem[x].r,up= nmem[x].u;
if(rp>=rbound){
if(rp> rbound||(rp+rp==r&&up> ubound))break;
}
o,up= nmem[x].u;
if(ulamq(u-up)){
if(hits){
record_stat(&lo_out_stats,count,u);
goto not_ulam;
}
hits= 1,anchorx= x;
}
}
record_stat(&lo_out_stats,count,u);
if(x==danger){
fprintf(stderr,"Sorry, the T threshold is too low!\n");
fprintf(stderr,
" (r="O"d,u="O"lld,lo_r_bound="O"d)\n",r,u,lo_r_bound);
goto finish_up;
}

/*:49*/
#line 972 "./ulam-gibbs.w"
;
/*50:*/
#line 1014 "./ulam-gibbs.w"

rbarbound= bar(r)>>1;
for(o,x= nmem[hi_out].next,count= 1;;o,x= nmem[x].next,count++){
if(x<=danger)break;
oo,rp= nmem[x].r,up= nmem[x].u;
if(rp>=rbarbound){
if(rp> rbarbound||(rp+rp==bar(r)&&up> ubound))break;
}
if(ulamq(u-up)){
if(hits){
record_stat(&hi_out_stats,count,u);
goto not_ulam;
}
hits= 1,anchorx= x;
}
}
record_stat(&hi_out_stats,count,u);
if(x==danger){
fprintf(stderr,"Sorry, the T threshold is too low!\n");
fprintf(stderr,
" (rbar="O"d,u="O"lld,hi_r_bound="O"d)\n",bar(r),u,hi_r_bound);
goto finish_up;
}

/*:50*/
#line 973 "./ulam-gibbs.w"
;
if(hits){
if(nmem[anchorx].r> lamp/3&&(vbose&show_inlier_anchors))
fprintf(stderr," (inlier anchor U"O"lld="O"lld+"O"lld)\n",
n,nmem[anchorx].u,u-nmem[anchorx].u);
goto ulam_yes;
}

/*:48*/
#line 745 "./ulam-gibbs.w"
;
ulam_miss:misses++;
miss_bin[n/alpha][r/beta]++;
not_ulam:ulamness= 0;
goto finish;
ulam_yes:yes_bin[n/alpha][r/beta]++;
/*37:*/
#line 818 "./ulam-gibbs.w"

n++,nw++;
if(nw==window_size)nw= 0;
/*23:*/
#line 540 "./ulam-gibbs.w"

o,window[nw]= u;

/*:23*/
#line 821 "./ulam-gibbs.w"
;

/*:37*//*38:*/
#line 825 "./ulam-gibbs.w"

if(r<=lamp/3)/*39:*/
#line 831 "./ulam-gibbs.w"

{
if(r<=lowest_outlier){
lowest_outlier= r;
if(vbose&show_record_outliers)
fprintf(stderr," (record low outlier r="O"d, u="O"lld)\n",r,u);
}
insert(lo_out,u,r);
}

/*:39*/
#line 826 "./ulam-gibbs.w"

else if(r<=lamp/2)/*41:*/
#line 870 "./ulam-gibbs.w"

{
register double g= lampthresh/((ullng)(3*r-lamp));
if(u>=g*g){
if(vbose&show_omitted_inliers)
fprintf(stderr," (omitting r="O"d, u="O"lld, g="O"g)\n",r,u,g*g/u);
if(r<lo_r_bound){
lo_r_bound= r;
if(vbose&show_record_cutoffs)
fprintf(stderr," (record low cutoff r="O"d, u="O"lld, g="O"g)\n",
r,u,g*g/u);
delete(lo_out,u,r);
}
}else if(r<lo_r_bound)insert(lo_out,u,r);
}

/*:41*/
#line 827 "./ulam-gibbs.w"

else if(bar(r)<=lamp/3)/*40:*/
#line 841 "./ulam-gibbs.w"

{
if(r>=highest_outlier){
highest_outlier= r;
if(vbose&show_record_outliers)
fprintf(stderr," (record high outlier r="O"d, u="O"lld\n",r,u);
}
insert(hi_out,u,bar(r));
}

/*:40*/
#line 828 "./ulam-gibbs.w"

else/*42:*/
#line 886 "./ulam-gibbs.w"

{
register double g= lampthresh/((ullng)(3*bar(r)-lamp));
if(u>=g*g){
if(vbose&show_omitted_inliers)
fprintf(stderr," (omitting rbar="O"d, u="O"lld, g="O"g)\n",
bar(r),u,g*g/u);
if(bar(r)<hi_r_bound){
hi_r_bound= bar(r);
if(vbose&show_record_cutoffs)
fprintf(stderr," (record high cutoff rbar="O"d, u="O"lld, g="O"g)\n",
bar(r),u,g*g/u);
delete(hi_out,u,bar(r));
}
}else if(bar(r)<hi_r_bound)insert(hi_out,u,bar(r));
}

/*:42*/
#line 829 "./ulam-gibbs.w"
;

/*:38*//*43:*/
#line 905 "./ulam-gibbs.w"

j= u-prevu;
if(j> maxgap)gapcount[maxgap+1]++;
else gapcount[j]++;
if(j>=biggestgap){
biggestgap= j;
if(vbose&show_record_gaps)
fprintf(stderr," (gap "O"d = U"O"lld-U"O"lld, U"O"lld="O"lld)\n",
j,n,n-1,n-1,prevu);
}
prevu= u;

/*:43*//*44:*/
#line 920 "./ulam-gibbs.w"

if(spacing&&(n mod spacing==0)){
register clock_t t= clock();
printf("U"O"lld="O"lld\n",n,u);

if(vbose&show_usage_stats)
fprintf(stderr," ("O"lld misses, "O"lld mems, "O".2f sec)\n",
misses-prevmisses,mems-prevmems,
(double)(t-prevclock)/(double)CLOCKS_PER_SEC);
prevmisses= misses,prevmems= mems,prevclock= t;
}

/*:44*/
#line 751 "./ulam-gibbs.w"
;
ulamness= 1;
finish:/*19:*/
#line 493 "./ulam-gibbs.w"

if(u<cur_slot)o,is_ulam[u]= ulamness;
else if(u==cur_slot+bits_per_compressed_byte)
/*20:*/
#line 502 "./ulam-gibbs.w"

{
o,t= inv_code[cur_code];
if(!t){
if(cur_code)/*21:*/
#line 515 "./ulam-gibbs.w"

{
if(code_ptr==256){
fprintf(stderr,"Oops, we need more than 256 codes! You must decrease b.\n");
goto finish_up;
}
o,t= inv_code[cur_code]= code_ptr;
code_example[code_ptr]= cur_slot;
o,code[code_ptr++]= cur_code;
}

/*:21*/
#line 506 "./ulam-gibbs.w"

else if(!code_example[0])code_example[0]= cur_slot;
}
o,is_um[cur_sl]= t;
code_use[t]++;
cur_sl++,cur_slot+= bits_per_compressed_byte;
cur_code= ulamness;
}

/*:20*/
#line 496 "./ulam-gibbs.w"

else if(ulamness)
cur_code+= 1<<u-cur_slot;

/*:19*/
#line 753 "./ulam-gibbs.w"
;
}

/*:32*/
#line 146 "./ulam-gibbs.w"
;
if(mp_file)/*56:*/
#line 1120 "./ulam-gibbs.w"

{
fprintf(mp_file,""O""O" created by gibbs-ulam "O"lld\n",maxn);
/*58:*/
#line 1161 "./ulam-gibbs.w"

fprintf(mp_file,"newinternal n; numeric a[];\n\n");
fprintf(mp_file,"def init =\n  draw (1,0)--("O"d,0);\n",binsize);
fprintf(mp_file,"  for j=1 upto "O"d: a[j]:=0; endfor\n",binsize);
fprintf(mp_file,"  pickup pencircle;\nenddef;\n\n");
fprintf(mp_file,"def doit(text j) text l =\n");
fprintf(mp_file,"  drawoptions(withcolor j/"O"d[green,red]);\n",bincolors);
fprintf(mp_file,"  n:=1;\n");
fprintf(mp_file,"  for t=l:\n");
fprintf(mp_file,"   if t>0: draw (n,a[n])--(n,a[n]+t); a[n]:=a[n]+t; fi\n");
fprintf(mp_file,"   n:=n+1;\n");
fprintf(mp_file,"  endfor\nenddef;\n");

/*:58*/
#line 1123 "./ulam-gibbs.w"
;
factor= (double)(binsize*binsize)/((double)9*maxn);
fprintf(mp_file,"\nbeginfig(1) init; "O""O" distribution of Ulam numbers\n");
for(j= 0;j<binsize;j++)acc[j]= 0,prev[j]= 0;
for(i= bincolors-1;i>=0;i--){
fprintf(mp_file,"doit("O"d)\n  ",i);
for(j= 0;j<binsize;j++){
acc[j]+= yes_bin[i][j];
t= (int)(factor*acc[j]+0.5);
fprintf(mp_file,""O"d"O"s",t-prev[j],
j+1==binsize?";\n":(j&0xf)==0xf?",\n  ":",");
prev[j]= t;
}
}
fprintf(mp_file,"endfig;\n\n");
fprintf(mp_file,"beginfig(0) init; "O""O" distribution of Ulam misses\n");
for(j= 0;j<binsize;j++)acc[j]= 0,prev[j]= 0;
for(i= bincolors-1;i>=0;i--){
fprintf(mp_file,"doit("O"d)\n  ",i);
for(j= 0;j<binsize;j++){
acc[j]+= miss_bin[i][j];
t= (int)(factor*acc[j]+0.5);
fprintf(mp_file,""O"d"O"s",t-prev[j],
j+1==binsize?";\n":(j&0xf)==0xf?",\n  ":",");
prev[j]= t;
}
}
fprintf(mp_file,"endfig;\n\nbye.\n");
fclose(mp_file);
fprintf(stderr,"METAPOST code written to file "O"s.\n",mp_name);
}

/*:56*/
#line 147 "./ulam-gibbs.w"
;
finish_up:/*51:*/
#line 1042 "./ulam-gibbs.w"

if(n==maxn&&!(spacing&&(n mod spacing==0)))
printf("U"O"lld="O"lld\n",n,u-1);

if(n<maxn)
fprintf(stderr,"I found "O"lld Ulam numbers and",n);
else fprintf(stderr,"I found");
fprintf(stderr," "O"lld Ulam misses < "O"lld.\n",misses,u);
if(vbose&show_gap_stats)
/*52:*/
#line 1059 "./ulam-gibbs.w"

{
fprintf(stderr,"****** Gap statistics thru U"O"lld ******\n",n);
for(j= 1;j<=maxgap;j++)if(gapcount[j])
fprintf(stderr,""O"5d:"O"14lld\n",j,gapcount[j]);
if(gapcount[maxgap+1])
fprintf(stderr,">"O"4d:"O"14lld\n",maxgap,gapcount[maxgap+1]);
}

/*:52*/
#line 1051 "./ulam-gibbs.w"
;
if(vbose&show_histograms)
/*53:*/
#line 1068 "./ulam-gibbs.w"

{
fprintf(stderr,"****** Histograms thru U"O"lld ******\n",n);
fprintf(stderr," Hits:\n");
for(j= 0;j<binsize;j++){
for(i= 0,u= 0;i<bincolors;i++)u+= yes_bin[i][j];
if(u)
fprintf(stderr,""O"4d/"O"d:"O"14lld\n",j,binsize,u);
}
fprintf(stderr," Misses:\n");
for(j= 0;j<binsize;j++){
for(i= 0,u= 0;i<bincolors;i++)u+= miss_bin[i][j];
if(u)
fprintf(stderr,""O"4d/"O"d:"O"14lld\n",j,binsize,u);
}
}

/*:53*/
#line 1053 "./ulam-gibbs.w"
;
if(vbose&show_compression_stats)
/*54:*/
#line 1085 "./ulam-gibbs.w"

{
fprintf(stderr,"****** Compression summary: ******\n");
for(j= (code_use[0]?0:1);j<code_ptr;j++){
fprintf(stderr," "O"02x ",j);
for(k= 1<<(bits_per_compressed_byte-1);k;k>>= 1)
fprintf(stderr,""O"d",code[j]&k?1:0);
fprintf(stderr,""O"14lld"O"14lld\n",code_use[j],code_example[j]);
}
}

/*:54*/
#line 1055 "./ulam-gibbs.w"
;
if(vbose&show_usage_stats)
/*55:*/
#line 1100 "./ulam-gibbs.w"

{
fprintf(stderr,"\nBrute-force loop stats: ");
dump_stats(window_stats);
fprintf(stderr,"Low-outlier insertion stats: ");
dump_stats(ins_stats[lo_out]);
fprintf(stderr,"Low-outlier loop stats: ");
dump_stats(lo_out_stats);
fprintf(stderr,"High-outlier insertion stats: ");
dump_stats(ins_stats[hi_out]);
fprintf(stderr,"High-outlier loop stats: ");
dump_stats(hi_out_stats);
fprintf(stderr,"The outlier lists used "O"d cells.\n",node_ptr-2);
fprintf(stderr,"Altogether "O"lld bytes, "O"lld mems, "O".2f sec.\n",
bytes,mems,(double)clock()/(double)CLOCKS_PER_SEC);
}

/*:55*/
#line 1057 "./ulam-gibbs.w"
;

/*:51*/
#line 148 "./ulam-gibbs.w"
;
}

/*:4*/
