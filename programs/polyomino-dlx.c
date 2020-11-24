#define bufsize 1024
#define maxpieces 100
#define maxnodes 100000
#define maxbases 1000
#define maxsuffixes 10 \

/*2:*/
#line 77 "./polyomino-dlx.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
char buf[bufsize];
/*9:*/
#line 207 "./polyomino-dlx.w"

typedef struct{
int list;
int size;
int xmin,xmax,ymin,ymax;
int pieceno;
}box;

/*:9*//*10:*/
#line 223 "./polyomino-dlx.w"

typedef struct{
int xy;
int suf;
int link;
}node;

/*:10*/
#line 82 "./polyomino-dlx.w"
;
/*8:*/
#line 196 "./polyomino-dlx.w"

long long acc;
long long accx,accy;

/*:8*//*11:*/
#line 233 "./polyomino-dlx.w"

node elt[maxnodes];
int curnode;
int avail;

/*:11*//*22:*/
#line 388 "./polyomino-dlx.w"

box newbox;
char suffix[maxsuffixes+1][8];
int scount;
char occupied[maxsuffixes+1][64][64];
box givenbox;
int sfxpresent;

/*:22*//*23:*/
#line 410 "./polyomino-dlx.w"

char names[maxpieces][8];
int piececount;
char mult[maxpieces][8];
char multip[8];
box base[maxbases];
int basecount;

/*:23*/
#line 83 "./polyomino-dlx.w"
;
/*3:*/
#line 102 "./polyomino-dlx.w"

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

/*:3*//*4:*/
#line 129 "./polyomino-dlx.w"

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
}else/*5:*/
#line 151 "./polyomino-dlx.w"

{
register int t,y;
for(acc= 0,t= x= -1,p++;buf[p]!=']';p++){
if(buf[p]=='\n'){
fprintf(stderr,"No closing bracket in %s",
buf);
exit(-4);
}
if(buf[p]=='-')/*6:*/
#line 175 "./polyomino-dlx.w"

{
if(x<0||buf[p+1]==']'){
fprintf(stderr,"Illegal range at position %d of %s",
p,buf);
exit(-5);
}
t= x,x= -1;
}

/*:6*/
#line 160 "./polyomino-dlx.w"

else{
x= decode(buf[p]);
if(x<0){
fprintf(stderr,"Illegal bracketed digit at position %d of %s",
p,buf);
exit(-3);
}
if(t<0)acc|= 1LL<<x;
else/*7:*/
#line 185 "./polyomino-dlx.w"

{
if(x<t){
fprintf(stderr,"Decreasing range at position %d of %s",
p,buf);
exit(-6);
}
acc|= (1LL<<(x+1))-(1LL<<t);
t= x= -1;
}

/*:7*/
#line 169 "./polyomino-dlx.w"
;
}
}
return p+1;
}

/*:5*/
#line 141 "./polyomino-dlx.w"
;
}

/*:4*//*12:*/
#line 240 "./polyomino-dlx.w"

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

/*:12*//*13:*/
#line 256 "./polyomino-dlx.w"

void putavail(int p){
register int q;
if(p){
for(q= p;elt[q].link;q= elt[q].link);
elt[q].link= avail;
avail= p;
}
}

/*:13*//*14:*/
#line 269 "./polyomino-dlx.w"

void insert(int x,int y,int s){
register int p,q,r,xy;
xy= (x<<8)+y;
for(q= 0,p= newbox.list;p;q= p,p= elt[p].link){
if(elt[p].xy==xy){
if(elt[p].suf==s)return;
if(elt[p].suf> s)break;
}else if(elt[p].xy> xy)break;
}
r= getavail();
elt[r].xy= xy,elt[r].suf= s,elt[r].link= p;
if(q)elt[q].link= r;
else newbox.list= r;
newbox.size++;
if(x<newbox.xmin)newbox.xmin= x;
if(y<newbox.ymin)newbox.ymin= y;
if(x> newbox.xmax)newbox.xmax= x;
if(y> newbox.ymax)newbox.ymax= y;
}

/*:14*//*15:*/
#line 294 "./polyomino-dlx.w"

void printbox(box*b){
register int p,x,y;
fprintf(stderr,"Piece %d, size %d, %d..%d %d..%d:\n",
b->pieceno,b->size,b->xmin,b->xmax,
b->ymin,b->ymax);
for(p= b->list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
fprintf(stderr," %c%c%s",
encode(x),encode(y),elt[p].suf?suffix[elt[p].suf-1]:"");
}
fprintf(stderr,"\n");
}

/*:15*//*30:*/
#line 518 "./polyomino-dlx.w"

int equality(int b){
register int p,q;
for(p= base[b].list,q= newbox.list;p;p= elt[p].link,q= elt[q].link)
if(elt[p].xy!=elt[q].xy||elt[p].suf!=elt[q].suf)return 0;
return 1;
}

/*:30*/
#line 84 "./polyomino-dlx.w"
;
main(){
register int i,j,k,p,q,r,t,x,y,dx,dy,xy0,suf;
register long long xa,ya;
/*17:*/
#line 313 "./polyomino-dlx.w"

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
/*18:*/
#line 336 "./polyomino-dlx.w"

newbox.list= newbox.size= 0;
newbox.xmin= newbox.ymin= 62;
newbox.xmax= newbox.ymax= -1;
for(;buf[p]!='\n';p++){
if(buf[p]!=' ')/*19:*/
#line 346 "./polyomino-dlx.w"

{
p= pdecode(p),accx= acc;
p= pdecode(p),accy= acc;
/*20:*/
#line 358 "./polyomino-dlx.w"

for(q= 0;buf[p+q]!=' '&&buf[p+q]!='\n';q++){
if(q==6){
fprintf(stderr,"Suffix too long, starting at position %d of %s",
p,buf);
exit(-11);
}
suffix[scount+1][q]= buf[p+q];
}
if(q){
suffix[scount+1][q]= 0;
p+= q;
for(i= 0;;i++)if(strcmp(suffix[i],suffix[scount+1])==0)break;
if(i> scount){
scount++;
if(scount> maxsuffixes){
fprintf(stderr,"Overflow! Recompile me by making maxsuffixes>%d.\n",
maxsuffixes);
exit(-7);
}
}
suf= i+1;
}else suf= 0;

/*:20*/
#line 350 "./polyomino-dlx.w"
;
if(buf[p]=='\n')p--;
for(x= 0,xa= accx;xa;x++,xa>>= 1)if(xa&1){
for(y= 0,ya= accy;ya;y++,ya>>= 1)if(ya&1)
insert(x,y,suf);
}
}

/*:19*/
#line 341 "./polyomino-dlx.w"
;
}

/*:18*/
#line 329 "./polyomino-dlx.w"
;
givenbox= newbox;
/*21:*/
#line 382 "./polyomino-dlx.w"

for(p= givenbox.list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
occupied[elt[p].suf][x][y]= 1;
}

/*:21*/
#line 331 "./polyomino-dlx.w"
;

/*:17*/
#line 88 "./polyomino-dlx.w"
;
/*24:*/
#line 418 "./polyomino-dlx.w"

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
/*25:*/
#line 433 "./polyomino-dlx.w"

/*27:*/
#line 443 "./polyomino-dlx.w"

for(p= 0;buf[p]!='\n';p++)if(buf[p]=='|')break;else multip[p]= buf[p];
if(buf[p]=='|')multip[p]= '\0',p++;
else p= 0,multip[0]= '1',multip[1]= '\0';
for(q= p;buf[p]!='\n';p++){
if(buf[p]==' ')break;
if(buf[p]=='|'||buf[p]==':'){
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
/*28:*/
#line 477 "./polyomino-dlx.w"

if(p==q||p> q+8){
fprintf(stderr,"Piece name is nonexistent or too long: %s",
buf);
exit(-7);
}
for(j= q;j<p;j++)names[piececount][j-q]= buf[j];
if(p==q+2){
x= decode(names[piececount][0]);
y= decode(names[piececount][1]);
if(x>=0&&y>=0&&occupied[0][x][y]){
fprintf(stderr,"Piece name conflicts with board position: %s",
buf);
exit(-333);
}
}

/*:28*/
#line 460 "./polyomino-dlx.w"
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
if(!mult[k][0])strcpy(mult[k],multip);
else if(strcmp(mult[k],multip)){
fprintf(stderr,"Inconsistent multiplicities for piece %.8s, %s vs %s!\n",
names[k],mult[k],multip);
exit(-6);
}

/*:27*/
#line 434 "./polyomino-dlx.w"
;
newbox.pieceno= k;
/*18:*/
#line 336 "./polyomino-dlx.w"

newbox.list= newbox.size= 0;
newbox.xmin= newbox.ymin= 62;
newbox.xmax= newbox.ymax= -1;
for(;buf[p]!='\n';p++){
if(buf[p]!=' ')/*19:*/
#line 346 "./polyomino-dlx.w"

{
p= pdecode(p),accx= acc;
p= pdecode(p),accy= acc;
/*20:*/
#line 358 "./polyomino-dlx.w"

for(q= 0;buf[p+q]!=' '&&buf[p+q]!='\n';q++){
if(q==6){
fprintf(stderr,"Suffix too long, starting at position %d of %s",
p,buf);
exit(-11);
}
suffix[scount+1][q]= buf[p+q];
}
if(q){
suffix[scount+1][q]= 0;
p+= q;
for(i= 0;;i++)if(strcmp(suffix[i],suffix[scount+1])==0)break;
if(i> scount){
scount++;
if(scount> maxsuffixes){
fprintf(stderr,"Overflow! Recompile me by making maxsuffixes>%d.\n",
maxsuffixes);
exit(-7);
}
}
suf= i+1;
}else suf= 0;

/*:20*/
#line 350 "./polyomino-dlx.w"
;
if(buf[p]=='\n')p--;
for(x= 0,xa= accx;xa;x++,xa>>= 1)if(xa&1){
for(y= 0,ya= accy;ya;y++,ya>>= 1)if(ya&1)
insert(x,y,suf);
}
}

/*:19*/
#line 341 "./polyomino-dlx.w"
;
}

/*:18*/
#line 436 "./polyomino-dlx.w"
;
/*29:*/
#line 497 "./polyomino-dlx.w"

xy0= (newbox.xmin<<8)+newbox.ymin;
if(xy0){
for(p= newbox.list;p;p= elt[p].link)elt[p].xy-= xy0;
newbox.xmax-= newbox.xmin,newbox.ymax-= newbox.ymin;
newbox.xmin= newbox.ymin= 0;
}

/*:29*/
#line 437 "./polyomino-dlx.w"
;
base[basecount]= newbox;
/*31:*/
#line 528 "./polyomino-dlx.w"

j= basecount,k= basecount+1;
while(j<k){
/*32:*/
#line 553 "./polyomino-dlx.w"

newbox.size= newbox.list= 0;
newbox.xmax= base[j].ymax,t= newbox.ymax= base[j].xmax;
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
insert(y,t-x,elt[p].suf);
}

/*:32*/
#line 531 "./polyomino-dlx.w"
;
for(i= basecount;i<k;i++)
if(equality(i))break;
if(i<k)putavail(newbox.list);
else base[k++]= newbox;
/*33:*/
#line 564 "./polyomino-dlx.w"

newbox.size= newbox.list= 0;
newbox.xmax= base[j].ymax,newbox.ymax= base[j].xmax;
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
insert(y,x,elt[p].suf);
}

/*:33*/
#line 536 "./polyomino-dlx.w"
;
for(i= basecount;i<k;i++)
if(equality(i))break;
if(i<k)putavail(newbox.list);
else base[k++]= newbox;
j++;
}
basecount= k;
if(basecount+8> maxbases){
fprintf(stderr,"Overflow! Recompile me by making maxbases bigger than %d.\n",
basecount+23);
exit(-669);
}

/*:31*/
#line 439 "./polyomino-dlx.w"
;

/*:25*/
#line 430 "./polyomino-dlx.w"
;
}

/*:24*/
#line 89 "./polyomino-dlx.w"
;
/*34:*/
#line 578 "./polyomino-dlx.w"

printf("| this file was created by polyomino-dlx from that data\n");
for(p= givenbox.list;p;p= elt[p].link)if(!elt[p].suf){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
printf(" %c%c",
encode(x),encode(y));
}
for(k= 0;k<piececount;k++){
if(mult[k][0]=='1'&&mult[k][1]=='\0')
printf(" %.8s",
names[k]);
else printf(" %s|%.8s",
mult[k],names[k]);
}
if(scount){
printf(" |");
for(sfxpresent= 0,p= givenbox.list;p;p= elt[p].link)if(elt[p].suf){
x= elt[p].xy>>8,y= elt[p].xy&0xff,sfxpresent++;
printf(" %c%c%s",
encode(x),encode(y),suffix[elt[p].suf-1]);
}
}
printf("\n");

/*:34*/
#line 90 "./polyomino-dlx.w"
;
/*35:*/
#line 602 "./polyomino-dlx.w"

for(j= 0;j<basecount;j++){
for(dx= givenbox.xmin;dx<=givenbox.xmax-base[j].xmax;dx++)
for(dy= givenbox.ymin;dy<=givenbox.ymax-base[j].ymax;dy++){
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
if(!occupied[elt[p].suf][x+dx][y+dy])break;
}
if(!p){
printf("%.8s",
names[base[j].pieceno]);
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
printf(" %c%c%s",
encode(x+dx),encode(y+dy),elt[p].suf?suffix[elt[p].suf-1]:"");
}
printf("\n");
}
}
}

/*:35*/
#line 91 "./polyomino-dlx.w"
;
/*36:*/
#line 626 "./polyomino-dlx.w"

if(!sfxpresent)
fprintf(stderr,
"Altogether %d cells, %d pieces, %d base placements, %d nodes.\n",
givenbox.size,piececount,basecount,curnode+1);
else fprintf(stderr,
"Altogether %d+%d cells, %d pieces, %d base placements, %d nodes.\n",
givenbox.size-sfxpresent,sfxpresent,piececount,basecount,curnode+1);

/*:36*/
#line 92 "./polyomino-dlx.w"
;
}

/*:2*/
