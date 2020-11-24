#define maxn 300 \

#define hprime 1009 \

#define eps 0.000001 \

#define makepoint(v,xx,yy) z.x= xx,z.y= yy,v= savepoint(z) 
#define makecircle(v,cc,rr) l.c= cc,l.r= rr,v= savecircle(l)  \

/*1:*/
#line 27 "./hyperbolic.w"

#include <stdio.h> 
#include <math.h> 
/*2:*/
#line 53 "./hyperbolic.w"

typedef struct{double x,y;}point;
typedef struct{double c,r;}circle;

/*:2*//*7:*/
#line 185 "./hyperbolic.w"

typedef struct{
int v36,v45,v90;
int e36,e45,e90;
int t36,t45,t90;
}triangle;

/*:7*/
#line 30 "./hyperbolic.w"

/*6:*/
#line 166 "./hyperbolic.w"

point hpoint[3*maxn];
int pptr;
int pleft[3*maxn],pright[3*maxn];
circle hcircle[3*maxn];
int cptr;
int cleft[3*maxn],cright[3*maxn];

/*:6*//*9:*/
#line 212 "./hyperbolic.w"

int triple[hprime];
int tripnum[hprime];
int tptr;
triangle triang[maxn+3];

/*:9*//*10:*/
#line 230 "./hyperbolic.w"

point z;
circle l;

/*:10*/
#line 31 "./hyperbolic.w"

/*3:*/
#line 65 "./hyperbolic.w"

circle common(point z,point zp)
{
circle t;
t.c= (z.x+zp.x)/2.0+((z.y+zp.y)/2.0)*((z.y-zp.y)/(z.x-zp.x));
if(fabs(t.c)<0.00001)t.c= 0.0;
t.r= sqrt((z.x-t.c)*(z.x-t.c)+z.y*z.y);
return t;
}

/*:3*//*4:*/
#line 104 "./hyperbolic.w"

point reflect(point z,circle l)
{
point t;
register double alpha;
alpha= l.r*l.r/((z.x-l.c)*(z.x-l.c)+z.y*z.y);
t.x= l.c+alpha*(z.x-l.c);
t.y= alpha*z.y;
return t;
}

/*:4*//*5:*/
#line 133 "./hyperbolic.w"

int savepoint(point z){
register int p,*q= &pleft[0];
for(p= *q;p;p= *q){
if(fabs(hpoint[p].x-z.x)<eps){
if(fabs(hpoint[p].y-z.y)<eps)goto found;
if(hpoint[p].y<z.y)q= &pleft[p];
else q= &pright[p];
}else if(hpoint[p].x<z.x)q= &pleft[p];
else q= &pright[p];
}
p= ++pptr;*q= p;
printf("z%d=(%.15g,%.15g)\n",p,z.x,z.y);
hpoint[p]= z;
found:return p;
}

int savecircle(circle l){
register int p,*q= &cleft[0];
for(p= *q;p;p= *q){
if(fabs(hcircle[p].c-l.c)<eps){
if(fabs(hcircle[p].r-l.r)<eps)goto found;
if(hcircle[p].r<l.r)q= &cleft[p];
else q= &cright[p];
}else if(hcircle[p].c<l.c)q= &cleft[p];
else q= &cright[p];
}
p= ++cptr;*q= p;
printf("l%d=(%.15g,%.15g)\n",p,l.c,l.r);
hcircle[p]= l;
found:return p;
}

/*:5*//*8:*/
#line 198 "./hyperbolic.w"

int savetriangle(int v36,int v45,int v90){
register unsigned int w= (((v36<<10)+v45)<<10)+v90;
register int h= w%hprime;
while(triple[h]){
if(triple[h]==w)goto found;
h= (h?h:hprime)-1;
}
triple[h]= w,tripnum[h]= tptr;
triang[tptr].v36= v36,triang[tptr].v45= v45,triang[tptr].v90= v90;
tptr++;
found:return tripnum[h];
}

/*:8*/
#line 32 "./hyperbolic.w"


main()
{
register int a,b,c,j,k,t;
register double phi;
/*11:*/
#line 234 "./hyperbolic.w"

phi= (1.0+sqrt(5.0))/2.0;
makepoint(a,sqrt(0.5/phi),sqrt(1.0-0.5/phi));
makepoint(b,0.0,1.0/sqrt(phi+sqrt(phi)));
makepoint(c,0.0,1.0);
/*12:*/
#line 257 "./hyperbolic.w"

makecircle(triang[0].e45,0.0,1.0);
triang[0].e36= triang[0].e45;
makecircle(triang[0].e90,hpoint[b].y,sqrt(2.0)*hpoint[b].y);

/*:12*/
#line 239 "./hyperbolic.w"
;
savetriangle(a,b,c);

printf("triangle 0 = (%d,%d,%d),",a,b,c);
printf(" edges (*,%d,%d)\n",triang[0].e45,triang[0].e90);

/*:11*/
#line 38 "./hyperbolic.w"
;
for(k= 0;tptr<maxn;k++)
/*13:*/
#line 283 "./hyperbolic.w"

{
if(hcircle[triang[k].e36].c)/*14:*/
#line 295 "./hyperbolic.w"

{
j= savepoint(reflect(hpoint[triang[k].v36],hcircle[triang[k].e36]));
t= tptr;
triang[k].t36= savetriangle(j,triang[k].v45,triang[k].v90);
if(tptr> t){
triang[t].e36= triang[k].e36;
triang[t].e45= savecircle(common(hpoint[triang[t].v36],
hpoint[triang[t].v90]));
triang[t].e90= savecircle(common(hpoint[triang[t].v36],
hpoint[triang[t].v45]));
printf("triangle %d = (z%d,z%d,z%d),",
t,triang[t].v36,triang[t].v45,triang[t].v90);
printf(" edges (%d,%d,%d)\n",triang[t].e36,triang[t].e45,triang[t].e90);
}
}

/*:14*/
#line 285 "./hyperbolic.w"
;
if(hcircle[triang[k].e45].c)/*15:*/
#line 312 "./hyperbolic.w"

{
j= savepoint(reflect(hpoint[triang[k].v45],hcircle[triang[k].e45]));
t= tptr;
triang[k].t45= savetriangle(triang[k].v36,j,triang[k].v90);
if(tptr> t){
triang[t].e45= triang[k].e45;
triang[t].e36= savecircle(common(hpoint[triang[t].v45],
hpoint[triang[t].v90]));
triang[t].e90= savecircle(common(hpoint[triang[t].v36],
hpoint[triang[t].v45]));
printf("triangle %d = (z%d,z%d,z%d),",
t,triang[t].v36,triang[t].v45,triang[t].v90);
printf(" edges (%d,%d,%d)\n",triang[t].e36,triang[t].e45,triang[t].e90);
}
}

/*:15*/
#line 286 "./hyperbolic.w"
;
if(hcircle[triang[k].e90].c)/*16:*/
#line 329 "./hyperbolic.w"

{
j= savepoint(reflect(hpoint[triang[k].v90],hcircle[triang[k].e90]));
t= tptr;
triang[k].t90= savetriangle(triang[k].v36,triang[k].v45,j);
if(tptr> t){
triang[t].e90= triang[k].e90;
triang[t].e36= savecircle(common(hpoint[triang[t].v45],
hpoint[triang[t].v90]));
triang[t].e45= savecircle(common(hpoint[triang[t].v36],
hpoint[triang[t].v90]));
printf("triangle %d = (z%d,z%d,z%d),",
t,triang[t].v36,triang[t].v45,triang[t].v90);
printf(" edges (%d,%d,%d)\n",triang[t].e36,triang[t].e45,triang[t].e90);
}
}

/*:16*/
#line 287 "./hyperbolic.w"
;
printf("Triangle %d neighbors:",k);
if(hcircle[triang[k].e36].c)printf(" t36=%d",triang[k].t36);
if(hcircle[triang[k].e45].c)printf(" t45=%d",triang[k].t45);
if(hcircle[triang[k].e90].c)printf(" t90=%d",triang[k].t90);
printf("\n");
}

/*:13*/
#line 40 "./hyperbolic.w"
;
}

/*:1*/
