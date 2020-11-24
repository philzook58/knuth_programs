#define bufsize 1024
#define maxpieces 100
#define maxnodes 10000
#define maxbases 1000 \

/*1:*/
#line 57 "./polycube-dlx.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
char buf[bufsize];
/*8:*/
#line 187 "./polycube-dlx.w"

typedef struct{
int list;
int size;
int xmin,xmax,ymin,ymax,zmin,zmax;
int pieceno;
}box;

/*:8*//*9:*/
#line 203 "./polycube-dlx.w"

typedef struct{
int xyz;
int link;
}node;

/*:9*/
#line 62 "./polycube-dlx.w"
;
/*7:*/
#line 176 "./polycube-dlx.w"

long long acc;
long long accx,accy,accz;

/*:7*//*10:*/
#line 212 "./polycube-dlx.w"

node elt[maxnodes];
int curnode;
int avail;

/*:10*//*20:*/
#line 352 "./polycube-dlx.w"

box newbox;
char occupied[64][64][64];
box givenbox;

/*:20*//*21:*/
#line 371 "./polycube-dlx.w"

char names[maxpieces][8];
int piececount;
int mult[maxpieces];
box base[maxbases];
int basecount;

/*:21*/
#line 63 "./polycube-dlx.w"
;
/*2:*/
#line 82 "./polycube-dlx.w"

int decode(char c){
if(c<='9'){
if(c>='0')return c-'0';
}else if(c>='a'){
if(c<='z')return c+10-'a';
}else if(c>='A'&&c<='Z')return c+36-'A';
if(c!='\n')return-1;
fprintf(stderr,"Incomplete input line: %s",
buf);
exit(-888);
}

char encode(int x){
if(x<0)return'-';
if(x<10)return'0'+x;
if(x<36)return'a'-10+x;
if(x<62)return'A'-36+x;
return'?';
}

/*:2*//*3:*/
#line 109 "./polycube-dlx.w"

int pdecode(register int p){
register int x;
if(buf[p]!='['){
x= decode(buf[p]);
if(x>=0){
acc= 1LL<<x;
return p+1;
}
fprintf(stderr,"Illegal digit at position %d of %s",
p,buf);
exit(-2);
}else/*4:*/
#line 131 "./polycube-dlx.w"

{
register int t,y;
for(acc= 0,t= x= -1,p++;buf[p]!=']';p++){
if(buf[p]=='\n'){
fprintf(stderr,"No closing bracket in %s",
buf);
exit(-4);
}
if(buf[p]=='-')/*5:*/
#line 155 "./polycube-dlx.w"

{
if(x<0||buf[p+1]==']'){
fprintf(stderr,"Illegal range at position %d of %s",
p,buf);
exit(-5);
}
t= x,x= -1;
}

/*:5*/
#line 140 "./polycube-dlx.w"

else{
x= decode(buf[p]);
if(x<0){
fprintf(stderr,"Illegal bracketed digit at position %d of %s",
p,buf);
exit(-3);
}
if(t<0)acc|= 1LL<<x;
else/*6:*/
#line 165 "./polycube-dlx.w"

{
if(x<t){
fprintf(stderr,"Decreasing range at position %d of %s",
p,buf);
exit(-6);
}
acc|= (1LL<<(x+1))-(1LL<<t);
t= x= -1;
}

/*:6*/
#line 149 "./polycube-dlx.w"
;
}
}
return p+1;
}

/*:4*/
#line 121 "./polycube-dlx.w"
;
}

/*:3*//*11:*/
#line 219 "./polycube-dlx.w"

int getavail(void){
register int p= avail;
if(p){
avail= elt[avail].link;
return p;
}
p= ++curnode;
if(p<maxnodes)return p;
fprintf(stderr,"Overflow! Recompile me by making maxnodes bigger than %d.\n",
maxnodes);
exit(-666);
}

/*:11*//*12:*/
#line 235 "./polycube-dlx.w"

void putavail(int p){
register int q;
if(p){
for(q= p;elt[q].link;q= elt[q].link);
elt[q].link= avail;
avail= p;
}
}

/*:12*//*13:*/
#line 248 "./polycube-dlx.w"

void insert(int x,int y,int z){
register int p,q,r,xyz;
xyz= (x<<16)+(y<<8)+z;
for(q= 0,p= newbox.list;p;q= p,p= elt[p].link){
if(elt[p].xyz==xyz)return;
if(elt[p].xyz> xyz)break;
}
r= getavail();
elt[r].xyz= xyz,elt[r].link= p;
if(q)elt[q].link= r;
else newbox.list= r;
newbox.size++;
if(x<newbox.xmin)newbox.xmin= x;
if(y<newbox.ymin)newbox.ymin= y;
if(z<newbox.zmin)newbox.zmin= z;
if(x> newbox.xmax)newbox.xmax= x;
if(y> newbox.ymax)newbox.ymax= y;
if(z> newbox.zmax)newbox.zmax= z;
}

/*:13*//*14:*/
#line 273 "./polycube-dlx.w"

void printbox(box*b){
register int p,x,y,z;
fprintf(stderr,"Piece %d, size %d, %d..%d %d..%d %d..%d:\n",
b->pieceno,b->size,b->xmin,b->xmax,
b->ymin,b->ymax,b->zmin,b->zmax);
for(p= b->list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
fprintf(stderr," %c%c%c",
encode(x),encode(y),encode(z));
}
fprintf(stderr,"\n");
}

/*:14*//*27:*/
#line 483 "./polycube-dlx.w"

int equality(int b){
register int p,q;
for(p= base[b].list,q= newbox.list;p;p= elt[p].link,q= elt[q].link)
if(elt[p].xyz!=elt[q].xyz)return 0;
return 1;
}

/*:27*/
#line 64 "./polycube-dlx.w"
;
main(){
register int i,j,k,p,q,r,t,x,y,z,dx,dy,dz,xyz0;
register long long xa,ya,za;
/*16:*/
#line 292 "./polycube-dlx.w"

while(1){
if(!fgets(buf,bufsize,stdin)){
fprintf(stderr,"Input file ended before the box specification!\n");
exit(-9);
}
if(buf[strlen(buf)-1]!='\n'){
fprintf(stderr,"Overflow! Recompile me by making bufsize bigger than %d.\n",
bufsize);
exit(-667);
}
printf("| %s",
buf);
if(buf[0]!='|')break;
}
p= 0;
/*17:*/
#line 315 "./polycube-dlx.w"

newbox.list= newbox.size= 0;
newbox.xmin= newbox.ymin= newbox.zmin= 62;
newbox.xmax= newbox.ymax= newbox.zmax= -1;
for(;buf[p]!='\n';p++){
if(buf[p]!=' ')/*18:*/
#line 325 "./polycube-dlx.w"

{
p= pdecode(p),accx= acc;
p= pdecode(p),accy= acc;
p= pdecode(p),accz= acc;
if(buf[p]!=' '){
if(buf[p]=='\n')p--;
else{
fprintf(stderr,"Missing space at position %d of %s",
p,buf);
exit(-11);
}
}
for(x= 0,xa= accx;xa;x++,xa>>= 1)if(xa&1){
for(y= 0,ya= accy;ya;y++,ya>>= 1)if(ya&1){
for(z= 0,za= accz;za;z++,za>>= 1)if(za&1)
insert(x,y,z);
}
}
}

/*:18*/
#line 320 "./polycube-dlx.w"
;
}

/*:17*/
#line 308 "./polycube-dlx.w"
;
givenbox= newbox;
/*19:*/
#line 346 "./polycube-dlx.w"

for(p= givenbox.list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
occupied[x][y][z]= 1;
}

/*:19*/
#line 310 "./polycube-dlx.w"
;

/*:16*/
#line 68 "./polycube-dlx.w"
;
/*22:*/
#line 378 "./polycube-dlx.w"

while(1){
if(!fgets(buf,bufsize,stdin))break;
if(buf[strlen(buf)-1]!='\n'){
fprintf(stderr,
"Overflow! Recompile me by making bufsize bigger than %d.\n",
bufsize);
exit(-777);
}
printf("| %s",
buf);
if(buf[0]=='|')continue;
/*23:*/
#line 393 "./polycube-dlx.w"

/*24:*/
#line 401 "./polycube-dlx.w"

if(buf[1]!='*')i= 1,p= q= 0;
else{
i= decode(buf[0]),p= q= 2;
if(i<0){
fprintf(stderr,"Unknown multiplicity: %s",
buf);
exit(-4);
}
}
for(;buf[p]!='\n';p++){
if(buf[p]==' ')break;
if(buf[p]=='|'||buf[p]==':'||buf[p]=='*'){
fprintf(stderr,"Illegal character in piece name: %s",
buf);
exit(-8);
}
}
if(buf[p]=='\n'){
fprintf(stderr,"(Empty %s is being ignored)\n",
p==0?"line":"piece");
continue;
}
/*25:*/
#line 441 "./polycube-dlx.w"

if(p==q||p> q+8){
fprintf(stderr,"Piece name is nonexistent or too long: %s",
buf);
exit(-7);
}
for(j= q;j<p;j++)names[piececount][j-q]= buf[j];
if(p==q+3){
x= decode(names[piececount][0]);
y= decode(names[piececount][1]);
z= decode(names[piececount][2]);
if(x>=0&&y>=0&&z>=0&&occupied[x][y][z]){
fprintf(stderr,"Piece name conflicts with board position: %s",
buf);
exit(-333);
}
}

/*:25*/
#line 424 "./polycube-dlx.w"
;
for(k= 0;;k++)if(strncmp(names[k],names[piececount],8)==0)break;
if(k==piececount){
if(++piececount> maxpieces){
fprintf(stderr,
"Overflow! Recompile me by making maxpieces bigger than %d.\n",
maxpieces);
exit(-668);
}
}
if(!mult[k])mult[k]= i;
else if(mult[k]!=i){
fprintf(stderr,"Inconsistent multiplicities for piece %.8s, %d vs %d!\n",
names[k],mult[k],i);
exit(-6);
}

/*:24*/
#line 394 "./polycube-dlx.w"
;
newbox.pieceno= k;
/*17:*/
#line 315 "./polycube-dlx.w"

newbox.list= newbox.size= 0;
newbox.xmin= newbox.ymin= newbox.zmin= 62;
newbox.xmax= newbox.ymax= newbox.zmax= -1;
for(;buf[p]!='\n';p++){
if(buf[p]!=' ')/*18:*/
#line 325 "./polycube-dlx.w"

{
p= pdecode(p),accx= acc;
p= pdecode(p),accy= acc;
p= pdecode(p),accz= acc;
if(buf[p]!=' '){
if(buf[p]=='\n')p--;
else{
fprintf(stderr,"Missing space at position %d of %s",
p,buf);
exit(-11);
}
}
for(x= 0,xa= accx;xa;x++,xa>>= 1)if(xa&1){
for(y= 0,ya= accy;ya;y++,ya>>= 1)if(ya&1){
for(z= 0,za= accz;za;z++,za>>= 1)if(za&1)
insert(x,y,z);
}
}
}

/*:18*/
#line 320 "./polycube-dlx.w"
;
}

/*:17*/
#line 396 "./polycube-dlx.w"
;
/*26:*/
#line 462 "./polycube-dlx.w"

xyz0= (newbox.xmin<<16)+(newbox.ymin<<8)+newbox.zmin;
if(xyz0){
for(p= newbox.list;p;p= elt[p].link)elt[p].xyz-= xyz0;
newbox.xmax-= newbox.xmin,newbox.ymax-= newbox.ymin,newbox.zmax-= newbox.zmin;
newbox.xmin= newbox.ymin= newbox.zmin= 0;
}

/*:26*/
#line 397 "./polycube-dlx.w"
;
base[basecount]= newbox;
/*28:*/
#line 493 "./polycube-dlx.w"

j= basecount,k= basecount+1;
while(j<k){
/*29:*/
#line 518 "./polycube-dlx.w"

newbox.size= newbox.list= 0;
newbox.xmax= base[j].ymax,t= newbox.ymax= base[j].xmax,newbox.zmax= base[j].zmax;
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
insert(y,t-x,z);
}

/*:29*/
#line 496 "./polycube-dlx.w"
;
for(i= basecount;i<k;i++)
if(equality(i))break;
if(i<k)putavail(newbox.list);
else base[k++]= newbox;
/*30:*/
#line 529 "./polycube-dlx.w"

newbox.size= newbox.list= 0;
newbox.xmax= base[j].ymax,newbox.ymax= base[j].zmax,newbox.zmax= base[j].xmax;
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
insert(y,z,x);
}

/*:30*/
#line 501 "./polycube-dlx.w"
;
for(i= basecount;i<k;i++)
if(equality(i))break;
if(i<k)putavail(newbox.list);
else base[k++]= newbox;
j++;
}
basecount= k;
if(basecount+24> maxbases){
fprintf(stderr,"Overflow! Recompile me by making maxbases bigger than %d.\n",
basecount+23);
exit(-669);
}

/*:28*/
#line 399 "./polycube-dlx.w"
;

/*:23*/
#line 390 "./polycube-dlx.w"
;
}

/*:22*/
#line 69 "./polycube-dlx.w"
;
/*31:*/
#line 543 "./polycube-dlx.w"

printf("| this file was created by polycube-dlx from that data\n");
for(p= givenbox.list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
printf(" %c%c%c",
encode(x),encode(y),encode(z));
}
for(k= 0;k<piececount;k++){
if(mult[k]==1)
printf(" %.8s",
names[k]);
else printf(" %c*%.8s",
encode(mult[k]),names[k]);
}
printf("\n");

/*:31*/
#line 70 "./polycube-dlx.w"
;
/*32:*/
#line 559 "./polycube-dlx.w"

for(j= 0;j<basecount;j++){
for(dx= givenbox.xmin;dx<=givenbox.xmax-base[j].xmax;dx++)
for(dy= givenbox.ymin;dy<=givenbox.ymax-base[j].ymax;dy++)
for(dz= givenbox.zmin;dz<=givenbox.zmax-base[j].zmax;dz++){
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
if(!occupied[x+dx][y+dy][z+dz])break;
}
if(!p){
printf("%.8s",
names[base[j].pieceno]);
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xyz>>16,y= (elt[p].xyz>>8)&0xff,z= elt[p].xyz&0xff;
printf(" %c%c%c",
encode(x+dx),encode(y+dy),encode(z+dz));
}
printf("\n");
}
}
}

/*:32*/
#line 71 "./polycube-dlx.w"
;
/*33:*/
#line 584 "./polycube-dlx.w"

fprintf(stderr,
"Altogether %d cells, %d pieces, %d base placements, %d nodes.\n",
givenbox.size,piececount,basecount,curnode+1);
/*:33*/
#line 72 "./polycube-dlx.w"
;
}

/*:1*/
