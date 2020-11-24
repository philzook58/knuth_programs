#define bufsize 1024
#define maxpieces 100
#define maxnodes 100000
#define maxbases 1000
#define maxsuffixes 10 \

/*2:*/
#line 92 "./polyiamond-dlx.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
char buf[bufsize];
/*9:*/
#line 222 "./polyiamond-dlx.w"

typedef struct{
int list;
int size;
int xmin,xmax,ymin,ymax;
int pieceno;
}box;

/*:9*//*10:*/
#line 238 "./polyiamond-dlx.w"

typedef struct{
int xy;
int suf;
int link;
}node;

/*:10*/
#line 97 "./polyiamond-dlx.w"
;
/*8:*/
#line 211 "./polyiamond-dlx.w"

long long acc;
long long accx,accy;

/*:8*//*11:*/
#line 248 "./polyiamond-dlx.w"

node elt[maxnodes];
int curnode;
int avail;

/*:11*//*22:*/
#line 416 "./polyiamond-dlx.w"

box newbox;
char suffix[maxsuffixes+1][8]= {"\'"};
int scount= 1;
char occupied[maxsuffixes+1][64][64];
box givenbox;
int sfxpresent;

/*:22*//*23:*/
#line 438 "./polyiamond-dlx.w"

char names[maxpieces][8];
int piececount;
char mult[maxpieces][8];
char multip[8];
box base[maxbases];
int basecount;

/*:23*/
#line 98 "./polyiamond-dlx.w"
;
/*3:*/
#line 117 "./polyiamond-dlx.w"

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
#line 144 "./polyiamond-dlx.w"

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
#line 166 "./polyiamond-dlx.w"

{
register int t,y;
for(acc= 0,t= x= -1,p++;buf[p]!=']';p++){
if(buf[p]=='\n'){
fprintf(stderr,"No closing bracket in %s",
buf);
exit(-4);
}
if(buf[p]=='-')/*6:*/
#line 190 "./polyiamond-dlx.w"

{
if(x<0||buf[p+1]==']'){
fprintf(stderr,"Illegal range at position %d of %s",
p,buf);
exit(-5);
}
t= x,x= -1;
}

/*:6*/
#line 175 "./polyiamond-dlx.w"

else{
x= decode(buf[p]);
if(x<0){
fprintf(stderr,"Illegal bracketed digit at position %d of %s",
p,buf);
exit(-3);
}
if(t<0)acc|= 1LL<<x;
else/*7:*/
#line 200 "./polyiamond-dlx.w"

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
#line 184 "./polyiamond-dlx.w"
;
}
}
return p+1;
}

/*:5*/
#line 156 "./polyiamond-dlx.w"
;
}

/*:4*//*12:*/
#line 255 "./polyiamond-dlx.w"

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
#line 271 "./polyiamond-dlx.w"

void putavail(int p){
register int q;
if(p){
for(q= p;elt[q].link;q= elt[q].link);
elt[q].link= avail;
avail= p;
}
}

/*:13*//*14:*/
#line 284 "./polyiamond-dlx.w"

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
#line 309 "./polyiamond-dlx.w"

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
#line 546 "./polyiamond-dlx.w"

int equality(int b){
register int p,q;
for(p= base[b].list,q= newbox.list;p;p= elt[p].link,q= elt[q].link)
if(elt[p].xy!=elt[q].xy||elt[p].suf!=elt[q].suf)return 0;
return 1;
}

/*:30*//*37:*/
#line 686 "./polyiamond-dlx.w"

void debug(int m){
fprintf(stderr," ..debug stop %d..\n",
m);
}

/*:37*/
#line 99 "./polyiamond-dlx.w"
;
main(){
register int i,j,k,p,q,r,t,x,y,dx,dy,xy0,suf;
register long long xa,ya;
/*17:*/
#line 328 "./polyiamond-dlx.w"

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
#line 351 "./polyiamond-dlx.w"

newbox.list= newbox.size= 0;
newbox.xmin= newbox.ymin= 62;
newbox.xmax= newbox.ymax= -1;
for(;buf[p]!='\n';p++){
if(buf[p]!=' ')/*19:*/
#line 361 "./polyiamond-dlx.w"

{
p= pdecode(p),accx= acc;
p= pdecode(p),accy= acc;
/*20:*/
#line 375 "./polyiamond-dlx.w"

for(q= 0;buf[p+q]!=' '&&buf[p+q]!='\n';q++){
if(q==6){
fprintf(stderr,"Suffix too long, starting at position %d of %s",
p,buf);
exit(-11);
}
suffix[scount][q]= buf[p+q];
}
if(q){
suffix[scount][q]= 0;
p+= q;
for(i= 0;;i++)if(strcmp(suffix[i],suffix[scount])==0)break;
if(i==scount){
scount+= 2;
if(scount> maxsuffixes){
fprintf(stderr,"Overflow! Recompile me by making maxsuffixes>%d.\n",
maxsuffixes);
exit(-7);
}
if(suffix[i][0]=='\'')
strcpy(suffix[scount-1],suffix[i]),
strcpy(suffix[i],&suffix[scount-1][1]),i++;
else{
strcpy(&suffix[scount-1][1],suffix[i]),suffix[scount-1][0]= '\'';
if(strlen(suffix[scount-1])> 6){
fprintf(stderr,"Implied suffix `%s' is too long!\n",
suffix[scount-1]);
exit(-9);
}
}
}
suf= i+1;
}else suf= 0;

/*:20*/
#line 365 "./polyiamond-dlx.w"
;
if(buf[p]=='\n')p--;
for(x= 0,xa= accx;xa;x++,xa>>= 1)if(xa&1){
for(y= 0,ya= accy;ya;y++,ya>>= 1)if(ya&1)
insert(x,y,suf);
}
}

/*:19*/
#line 356 "./polyiamond-dlx.w"
;
}

/*:18*/
#line 344 "./polyiamond-dlx.w"
;
givenbox= newbox;
/*21:*/
#line 410 "./polyiamond-dlx.w"

for(p= givenbox.list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
occupied[elt[p].suf][x][y]= 1;
}

/*:21*/
#line 346 "./polyiamond-dlx.w"
;

/*:17*/
#line 103 "./polyiamond-dlx.w"
;
/*24:*/
#line 446 "./polyiamond-dlx.w"

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
#line 461 "./polyiamond-dlx.w"

/*27:*/
#line 471 "./polyiamond-dlx.w"

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
#line 505 "./polyiamond-dlx.w"

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
#line 488 "./polyiamond-dlx.w"
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
#line 462 "./polyiamond-dlx.w"
;
newbox.pieceno= k;
/*18:*/
#line 351 "./polyiamond-dlx.w"

newbox.list= newbox.size= 0;
newbox.xmin= newbox.ymin= 62;
newbox.xmax= newbox.ymax= -1;
for(;buf[p]!='\n';p++){
if(buf[p]!=' ')/*19:*/
#line 361 "./polyiamond-dlx.w"

{
p= pdecode(p),accx= acc;
p= pdecode(p),accy= acc;
/*20:*/
#line 375 "./polyiamond-dlx.w"

for(q= 0;buf[p+q]!=' '&&buf[p+q]!='\n';q++){
if(q==6){
fprintf(stderr,"Suffix too long, starting at position %d of %s",
p,buf);
exit(-11);
}
suffix[scount][q]= buf[p+q];
}
if(q){
suffix[scount][q]= 0;
p+= q;
for(i= 0;;i++)if(strcmp(suffix[i],suffix[scount])==0)break;
if(i==scount){
scount+= 2;
if(scount> maxsuffixes){
fprintf(stderr,"Overflow! Recompile me by making maxsuffixes>%d.\n",
maxsuffixes);
exit(-7);
}
if(suffix[i][0]=='\'')
strcpy(suffix[scount-1],suffix[i]),
strcpy(suffix[i],&suffix[scount-1][1]),i++;
else{
strcpy(&suffix[scount-1][1],suffix[i]),suffix[scount-1][0]= '\'';
if(strlen(suffix[scount-1])> 6){
fprintf(stderr,"Implied suffix `%s' is too long!\n",
suffix[scount-1]);
exit(-9);
}
}
}
suf= i+1;
}else suf= 0;

/*:20*/
#line 365 "./polyiamond-dlx.w"
;
if(buf[p]=='\n')p--;
for(x= 0,xa= accx;xa;x++,xa>>= 1)if(xa&1){
for(y= 0,ya= accy;ya;y++,ya>>= 1)if(ya&1)
insert(x,y,suf);
}
}

/*:19*/
#line 356 "./polyiamond-dlx.w"
;
}

/*:18*/
#line 464 "./polyiamond-dlx.w"
;
/*29:*/
#line 525 "./polyiamond-dlx.w"

xy0= (newbox.xmin<<8)+newbox.ymin;
if(xy0){
for(p= newbox.list;p;p= elt[p].link)elt[p].xy-= xy0;
newbox.xmax-= newbox.xmin,newbox.ymax-= newbox.ymin;
newbox.xmin= newbox.ymin= 0;
}

/*:29*/
#line 465 "./polyiamond-dlx.w"
;
base[basecount]= newbox;
/*31:*/
#line 558 "./polyiamond-dlx.w"

j= basecount,k= basecount+1;
while(j<k){
/*32:*/
#line 590 "./polyiamond-dlx.w"

newbox.size= newbox.list= 0;
t= newbox.ymax= base[j].xmax;newbox.xmax= 0;
newbox.xmin= newbox.ymin= 64;
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
if(elt[p].suf&1){
insert(x+y+1,t-x,elt[p].suf-1);
}else{
insert(x+y,t-x,elt[p].suf+1);
}
}
/*29:*/
#line 525 "./polyiamond-dlx.w"

xy0= (newbox.xmin<<8)+newbox.ymin;
if(xy0){
for(p= newbox.list;p;p= elt[p].link)elt[p].xy-= xy0;
newbox.xmax-= newbox.xmin,newbox.ymax-= newbox.ymin;
newbox.xmin= newbox.ymin= 0;
}

/*:29*/
#line 602 "./polyiamond-dlx.w"
;

/*:32*/
#line 561 "./polyiamond-dlx.w"
;
for(i= basecount;i<k;i++)
if(equality(i))break;
if(i<k)putavail(newbox.list);
else base[k++]= newbox;
/*33:*/
#line 615 "./polyiamond-dlx.w"

newbox.size= newbox.list= 0;
newbox.xmax= base[j].ymax,newbox.ymax= base[j].xmax;
for(p= base[j].list;p;p= elt[p].link){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
insert(y,x,elt[p].suf);
}

/*:33*/
#line 566 "./polyiamond-dlx.w"
;
for(i= basecount;i<k;i++)
if(equality(i))break;
if(i<k)putavail(newbox.list);
else base[k++]= newbox;
j++;
}
basecount= k;
if(basecount+12> maxbases){
fprintf(stderr,"Overflow! Recompile me by making maxbases bigger than %d.\n",
basecount+23);
exit(-669);
}

/*:31*/
#line 467 "./polyiamond-dlx.w"
;

/*:25*/
#line 458 "./polyiamond-dlx.w"
;
}

/*:24*/
#line 104 "./polyiamond-dlx.w"
;
/*34:*/
#line 629 "./polyiamond-dlx.w"

printf("| this file was created by polyiamond-dlx from that data\n");
for(p= givenbox.list;p;p= elt[p].link)if(elt[p].suf<2){
x= elt[p].xy>>8,y= elt[p].xy&0xff;
printf(" %c%c%s",
encode(x),encode(y),elt[p].suf?"'":"");
}
for(k= 0;k<piececount;k++){
if(mult[k][0]=='1'&&mult[k][1]=='\0')
printf(" %.8s",
names[k]);
else printf(" %s|%.8s",
mult[k],names[k]);
}
if(scount> 1){
printf(" |");
for(sfxpresent= 0,p= givenbox.list;p;p= elt[p].link)if(elt[p].suf> 1){
x= elt[p].xy>>8,y= elt[p].xy&0xff,sfxpresent++;
printf(" %c%c%s",
encode(x),encode(y),suffix[elt[p].suf-1]);
}
}
printf("\n");

/*:34*/
#line 105 "./polyiamond-dlx.w"
;
/*35:*/
#line 653 "./polyiamond-dlx.w"

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
#line 106 "./polyiamond-dlx.w"
;
/*36:*/
#line 677 "./polyiamond-dlx.w"

if(!sfxpresent)
fprintf(stderr,
"Altogether %d cells, %d pieces, %d base placements, %d nodes.\n",
givenbox.size,piececount,basecount,curnode+1);
else fprintf(stderr,
"Altogether %d+%d cells, %d pieces, %d base placements, %d nodes.\n",
givenbox.size-sfxpresent,sfxpresent,piececount,basecount,curnode+1);

/*:36*/
#line 107 "./polyiamond-dlx.w"
;
}

/*:2*/
