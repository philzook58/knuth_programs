#define maxm 20 \

/*3:*/
#line 39 "./graceful-count.w"

#include <stdio.h> 
#include <stdlib.h> 
int mm;
/*15:*/
#line 176 "./graceful-count.w"

int active;
int parent[maxm+1],size[maxm+1],move[maxm];
int arcs[maxm+1];
int link[2*maxm+1];
int x[maxm+1];

/*:15*//*18:*/
#line 205 "./graceful-count.w"

unsigned long long connected[maxm+2],disconnected[maxm+2];
unsigned long long totconnected,totdisconnected;

/*:18*/
#line 43 "./graceful-count.w"
;
main(int argc,char*argv[]){
register j,k,l,m;
/*4:*/
#line 55 "./graceful-count.w"

if(argc!=2||sscanf(argv[1],"%d",
&mm)!=1){
fprintf(stderr,"Usage: %s m\n",
argv[0]);
exit(-1);
}
m= mm;
if(m<2||m> maxm){
fprintf(stderr,"Sorry, m must be between 2 and %d!\n",
maxm);
exit(-2);
}

/*:4*/
#line 46 "./graceful-count.w"
;
/*7:*/
#line 103 "./graceful-count.w"

/*11:*/
#line 150 "./graceful-count.w"

for(j= 0;j<=m;j++)parent[j]= -1,size[j]= 1;
l= 0;

/*:11*/
#line 104 "./graceful-count.w"
;
for(j= m;j;j--){
x[j]= m-j;
/*8:*/
#line 110 "./graceful-count.w"

{
register int p,u,v,uu,vv;
u= x[j];
v= u+j;
/*12:*/
#line 154 "./graceful-count.w"

for(uu= u;parent[uu]>=0;uu= parent[uu]);
for(vv= v;parent[vv]>=0;vv= parent[vv]);
if(uu==vv)move[l]= -1;
else if(size[uu]<=size[vv])
parent[uu]= vv,move[l]= uu,size[vv]+= size[uu];
else parent[vv]= uu,move[l]= vv,size[uu]+= size[vv];
l++;

/*:12*/
#line 115 "./graceful-count.w"
;
p= arcs[u];
if(!p)active++;
link[j]= p,arcs[u]= j;
p= arcs[v];
if(!p)active++;
link[m+j]= p,arcs[v]= m+j;
}

/*:8*/
#line 107 "./graceful-count.w"
;
}

/*:7*/
#line 47 "./graceful-count.w"
;
while(1){
/*16:*/
#line 189 "./graceful-count.w"

for(k= parent[m];parent[k]>=0;k= parent[k]);
if(size[k]==active)connected[active]++;
else disconnected[active]++;

/*:16*/
#line 49 "./graceful-count.w"
;
/*5:*/
#line 69 "./graceful-count.w"

for(j= 1;x[j]==0;j++){
/*9:*/
#line 124 "./graceful-count.w"

{
register int p,u,v,uu,vv;
u= x[j];
v= u+j;
p= link[m+j];
arcs[v]= p;
if(!p)active--;
p= link[j];
arcs[u]= p;
if(!p)active--;
/*14:*/
#line 167 "./graceful-count.w"

l--;
uu= move[l];
if(uu>=0){
vv= parent[uu];
size[vv]-= size[uu];
parent[uu]= -1;
}

/*:14*/
#line 135 "./graceful-count.w"
;
}

/*:9*/
#line 71 "./graceful-count.w"
;
}
if(j==m-1)goto done;
/*9:*/
#line 124 "./graceful-count.w"

{
register int p,u,v,uu,vv;
u= x[j];
v= u+j;
p= link[m+j];
arcs[v]= p;
if(!p)active--;
p= link[j];
arcs[u]= p;
if(!p)active--;
/*14:*/
#line 167 "./graceful-count.w"

l--;
uu= move[l];
if(uu>=0){
vv= parent[uu];
size[vv]-= size[uu];
parent[uu]= -1;
}

/*:14*/
#line 135 "./graceful-count.w"
;
}

/*:9*/
#line 74 "./graceful-count.w"
;
x[j]--;
/*8:*/
#line 110 "./graceful-count.w"

{
register int p,u,v,uu,vv;
u= x[j];
v= u+j;
/*12:*/
#line 154 "./graceful-count.w"

for(uu= u;parent[uu]>=0;uu= parent[uu]);
for(vv= v;parent[vv]>=0;vv= parent[vv]);
if(uu==vv)move[l]= -1;
else if(size[uu]<=size[vv])
parent[uu]= vv,move[l]= uu,size[vv]+= size[uu];
else parent[vv]= uu,move[l]= vv,size[uu]+= size[vv];
l++;

/*:12*/
#line 115 "./graceful-count.w"
;
p= arcs[u];
if(!p)active++;
link[j]= p,arcs[u]= j;
p= arcs[v];
if(!p)active++;
link[m+j]= p,arcs[v]= m+j;
}

/*:8*/
#line 76 "./graceful-count.w"
;
for(j--;j;j--){
x[j]= m-j;
/*8:*/
#line 110 "./graceful-count.w"

{
register int p,u,v,uu,vv;
u= x[j];
v= u+j;
/*12:*/
#line 154 "./graceful-count.w"

for(uu= u;parent[uu]>=0;uu= parent[uu]);
for(vv= v;parent[vv]>=0;vv= parent[vv]);
if(uu==vv)move[l]= -1;
else if(size[uu]<=size[vv])
parent[uu]= vv,move[l]= uu,size[vv]+= size[uu];
else parent[vv]= uu,move[l]= vv,size[uu]+= size[vv];
l++;

/*:12*/
#line 115 "./graceful-count.w"
;
p= arcs[u];
if(!p)active++;
link[j]= p,arcs[u]= j;
p= arcs[v];
if(!p)active++;
link[m+j]= p,arcs[v]= m+j;
}

/*:8*/
#line 79 "./graceful-count.w"
;
}

/*:5*/
#line 50 "./graceful-count.w"
;
}
done:/*17:*/
#line 194 "./graceful-count.w"

printf("Counts for %d edges:\n",
m);
for(k= 2;k<=m+1;k++)if(connected[k]+disconnected[k]){
printf("on %5d vertices, %lld are connected, %lld not\n",
k,2*connected[k],2*disconnected[k]);
totconnected+= 2*connected[k],totdisconnected+= 2*disconnected[k];
}
printf("Altogether %lld connected and %lld not.\n",
totconnected,totdisconnected);

/*:17*/
#line 52 "./graceful-count.w"
;
}

/*:3*/
