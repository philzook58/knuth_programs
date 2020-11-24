#define maxn 16
#define maxd 16
#define bufsize 80
#define pack(i,j) ((((i) +1) <<8) +(j) +1) 
#define unpack(ij) icoord= ((ij) >>8) -1,jcoord= ((ij) &0xff) -1
#define board(i,j) brd[pack(i,j) ]
#define panic(message) {fprintf(stderr,"%s: %s",message,buf) ;exit(-1) ;} \

/*1:*/
#line 33 "./filomino-dlx.w"

#include <stdio.h> 
#include <stdlib.h> 
char buf[bufsize];
int brd[pack(maxn,maxn)];
int dmax;
/*18:*/
#line 270 "./filomino-dlx.w"

int forcing;
int dir[5]= {0,-(1<<8),-1,1,1<<8};
int tag[pack(maxn,maxn)];
int vv[maxd],aa[maxd],ii[maxd],stack[maxd];
int curstamp;
int stamp[pack(maxn,maxn)];
int mm,nn;

/*:18*/
#line 39 "./filomino-dlx.w"
;
/*19:*/
#line 279 "./filomino-dlx.w"

void debug(char*message){
fprintf(stderr,"%s!\n",
message);
}

/*:19*//*20:*/
#line 287 "./filomino-dlx.w"

void showtags(void){
register int i,j;
for(i= 0;i<mm;i++)for(j= 0;j<nn;j++)if(tag[pack(i,j)])
printf("%x%x:%d\n",
i,j,tag[pack(i,j)]);
}

/*:20*//*21:*/
#line 295 "./filomino-dlx.w"

void checktags(void){
register int i,j,q;
for(i= 0;i<mm;i++)for(j= 0;j<nn;j++)if(tag[pack(i,j)]){
if(pack(i,j)==vv[0])continue;
for(q= 1;q<=4;q++)if(pack(i,j)==vv[0]+dir[q])break;
if(q<=4)continue;
debug("bad tag");
}
}

/*:21*/
#line 40 "./filomino-dlx.w"
;
main(){
register int a,d,i,j,k,l,m,n,p,q,s,t,u,v,di,dj,icoord,jcoord;
/*2:*/
#line 48 "./filomino-dlx.w"

printf("| filomino-dlx:\n");
for(i= n= t= 0;i<=maxn;i++){
if(!fgets(buf,bufsize,stdin))break;
printf("| %s",
buf);
for(j= k= 0;;j++,k++){
if(buf[k]=='\n')break;
if(buf[k]=='.')continue;
if(buf[k]>='1'&&buf[k]<='9')
board(i,j)= buf[k]-'0',t++;
else if(buf[k]>='a'&&buf[k]<='f')
board(i,j)= buf[k]-'a'+10,t++;
else panic("illegal entry");
if(board(i,j)> dmax)dmax= board(i,j);
}
if(j> n)n= j;
}
if(i> maxn)panic("too many rows");
m= i;
for(i= 0;i<m;i++)board(i,-1)= board(i,n)= -1;
for(j= 0;j<n;j++)board(-1,j)= board(m,j)= -1;
fprintf(stderr,"OK, I've read %d clues <= %d, for a %dx%d board.\n",
t,dmax,m,n);
mm= m,nn= n;

/*:2*/
#line 43 "./filomino-dlx.w"
;
/*3:*/
#line 83 "./filomino-dlx.w"

for(i= 0;i<m;i++)for(j= 0;j<n;j++)printf("%x%x ",
i,j);
printf("|");
for(i= 0;i<m;i++)for(j= 1;j<n;j++)for(d= 1;d<=dmax;d++)printf(" h%x%x%x",
d,i,j);
for(i= 1;i<m;i++)for(j= 0;j<n;j++)for(d= 1;d<=dmax;d++)printf(" v%x%x%x",
d,i,j);
printf("\n");

/*:3*/
#line 44 "./filomino-dlx.w"
;
for(d= 1;d<=dmax;d++)/*4:*/
#line 93 "./filomino-dlx.w"

{
for(di= 0;di<m;di++)for(dj= 0;dj<n;dj++)
/*5:*/
#line 118 "./filomino-dlx.w"

{
u= pack(di,dj);
if(!board(di,dj)){
for(q= 1;q<=4;q++)if(brd[u+dir[q]]==d)break;
if(q<=4)continue;
forcing= 0;
}else if(board(di,dj)!=d)continue;
else forcing= 1;
/*6:*/
#line 137 "./filomino-dlx.w"

r1:
for(i= 0;i<m;i++)for(j= 0;j<n;j++)tag[pack(i,j)]= 0;
v= vv[0]= u,tag[v]= 1;
i= ii[0]= 0,a= aa[0]= 0,l= 1;

/*:6*/
#line 127 "./filomino-dlx.w"
;
/*7:*/
#line 147 "./filomino-dlx.w"

r2:
if(forcing)/*8:*/
#line 164 "./filomino-dlx.w"

for(stack[0]= u,s= 1;s;){
u= stack[--s];
for(q= 1;q<=4;q++){
t= u+dir[q];
if(brd[t]!=d)continue;
if(tag[t])continue;
if(t<vv[0])goto r7;
if(l==d)goto r7;
aa[l]= 0,vv[l++]= t,tag[t]= 1,stack[s++]= t;
}
}

/*:8*/
#line 150 "./filomino-dlx.w"
;
if(l==d){
/*9:*/
#line 179 "./filomino-dlx.w"

{
curstamp++;
for(p= 0;p<d;p++){
unpack(vv[p]);
printf(" %x%x",
icoord,jcoord);
stamp[vv[p]]= curstamp;
}
for(p= 0;p<d;p++){
unpack(vv[p]);
for(q= 1;q<=4;q++)
if(stamp[vv[p]+dir[q]]!=curstamp){
switch(q){
case 1:if(icoord)printf(" v%x%x%x",
d,icoord,jcoord);break;
case 2:if(jcoord)printf(" h%x%x%x",
d,icoord,jcoord);break;
case 3:if(jcoord<n-1)printf(" h%x%x%x",
d,icoord,jcoord+1);break;
case 4:if(icoord<m-1)printf(" v%x%x%x",
d,icoord+1,jcoord);break;
}
}
}
printf("\n");
}

/*:9*/
#line 152 "./filomino-dlx.w"
;
/*10:*/
#line 207 "./filomino-dlx.w"

for(l--;aa[l]==0;l--){
if(l==0)goto done;
tag[vv[l]]= 0;
}

/*:10*/
#line 153 "./filomino-dlx.w"
;
}

/*:7*/
#line 128 "./filomino-dlx.w"
;
/*11:*/
#line 213 "./filomino-dlx.w"

r3:
a++;

/*:11*/
#line 129 "./filomino-dlx.w"
;
/*12:*/
#line 217 "./filomino-dlx.w"

r4:
if(a!=5)goto r5;
if(i==l-1)goto r6;
v= vv[++i],a= 1;

/*:12*/
#line 130 "./filomino-dlx.w"
;
/*13:*/
#line 223 "./filomino-dlx.w"

r5:
u= v+dir[a];
if(brd[u])goto r3;
tag[u]++;
if(tag[u]> 1)goto r3;
if(!forcing)
/*14:*/
#line 235 "./filomino-dlx.w"

{
if(u<vv[0])goto r3;
if(brd[u])goto r3;
for(q= 1;q<=4;q++)if(brd[u+dir[q]]==d)goto r3;
}

/*:14*/
#line 231 "./filomino-dlx.w"
;
ii[l]= i,aa[l]= a,vv[l]= u,l++;
goto r2;

/*:13*/
#line 131 "./filomino-dlx.w"
;
/*15:*/
#line 242 "./filomino-dlx.w"

r6:
/*16:*/
#line 255 "./filomino-dlx.w"

for(l--;aa[l]==0;l--){
if(l==0)goto done;
t= vv[l];
for(q= 1;q<=4;q++)
if(brd[t+dir[q]]==0)tag[t+dir[q]]--;
tag[t]= 0;
}

/*:16*/
#line 244 "./filomino-dlx.w"
;
for(i= ii[l],k= i+1;k<=l;k++){
t= vv[k];
for(q= 1;q<=4;q++)
if(brd[t+dir[q]]==0)tag[t+dir[q]]--;
}
for(a= aa[l]+1,v= vv[i];a<=4;a++)
if(brd[v+dir[a]]==0)tag[v+dir[a]]--;
a= aa[l];
goto r3;

/*:15*/
#line 132 "./filomino-dlx.w"
;
/*17:*/
#line 264 "./filomino-dlx.w"

r7:
/*10:*/
#line 207 "./filomino-dlx.w"

for(l--;aa[l]==0;l--){
if(l==0)goto done;
tag[vv[l]]= 0;
}

/*:10*/
#line 266 "./filomino-dlx.w"
;
i= ii[l],v= vv[i],a= aa[l];
goto r3;

/*:17*/
#line 133 "./filomino-dlx.w"
;
done:checktags();
}

/*:5*/
#line 96 "./filomino-dlx.w"
;
}

/*:4*/
#line 45 "./filomino-dlx.w"
;
}

/*:1*/
