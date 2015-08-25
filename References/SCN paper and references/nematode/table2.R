library(epicalc)
zap()

dat<-read.table("nema2.csv",head=T,sep=",",stringsAsFactors=F)
attach(dat)
Siteori<-dat[,5:8]
meanSite<-apply(Siteori,1,mean)

Site<-cbind(Siteori,meanSite)
Sitemodi<-Site+0.00000001
Psite<-matrix(nrow=length(index),ncol=5)
for (i in 1:5){Psite[,i]=Site[,i]/sum(Site[,i])}
Psitemodi<-matrix(nrow=length(index),ncol=5)
for (i in 1:5){Psitemodi[,i]=Sitemodi[,i]/sum(Sitemodi[,i])}
#Shannon-Weaver index
H<-vector()
for (i in 1:5){H[i]=sum(Psitemodi[,i]*log(Psitemodi[,i]))}
H

#Simpson's dominance index
lamda<-vector()
for (i in 1:5){lamda[i]<-sum(Psite[,i]^2)}
lamda

#Jaccard's Similarity index


a=length(which(Site[,1]!=0 & Site[,2]==0))
b=length(which(Site[,1]==0 & Site[,2]!=0))
c=length(which(Site[,1]!=0 & Site[,2]!=0))
c/(a+b+c)

#Bary and Curtis Similarity index
a<-sum(Site[,1])
b<-sum(Site[,2])
w<-sum(apply(Site[,1:2],1,min))
c=2*w/(a+b)
c
#calculate MI
plant.Para<-which(Trophic.groups=="Plant parasites")
MIgroup<-cbind(C.p.value,Site)[-plant.Para,]
MI<-vector()
for(i in 1:5){MI[i]<-sum(MIgroup[,1]*MIgroup[,i+1]/sum(MIgroup[,i+1]))} 
MI


#calculate PPI
PPIgroup<-cbind(C.p.value,Site)[plant.Para,]
PPI<-vector()
for(i in 1:5){PPI[i]<-sum(PPIgroup[,1]*PPIgroup[,i+1]/sum(PPIgroup[,i+1]))} 
PPI

# calculate EI,SI,BI
ba<-list();fu<-list();ca<-list();om<-list()
for (i in 1:5) {ba[[i]]=which(Trophic.groups=="Bacterivores"&C.p.value==i)}

for (i in 1:5) {fu[[i]]=which(Trophic.groups=="Fungivor"&C.p.value==i)}

for (i in 1:5) {ca[[i]]=which(Trophic.groups=="Predator"&C.p.value==i)}

for (i in 1:5) {om[[i]]=which(Trophic.groups=="Onmivores"&C.p.value==i)}
ke<-c(0.8,3.2)
ne<-matrix(nrow=2,ncol=5)
for(i in 1:5){ne[1,i]=sum(Site[fu[[2]],i]);ne[2,i]=sum(Site[ba[[1]],i])}
kb<-c(0.8,0.8)
nb<-matrix(nrow=2,ncol=5)
for(i in 1:5){nb[1,i]=sum(Site[ba[[2]],i]);nb[2,i]=sum(Site[fu[[2]],i])}
kb*nb
e<-vector()
b<-vector()
e<-apply(ke*ne,2,sum)
b<-apply(kb*nb,2,sum)
b
EI=100*e/(e+b)
EI
e
ks<-c(0.8,3.2,5.0,rep(c(1.8,3.2,5.0),3))
ns<-matrix(nrow=12,ncol=5)
for(i in 1:5){
	ns[1,i]=sum(Site[ca[[2]],i]);
	ns[2,i]=sum(Site[om[[4]],i]);
	ns[3,i]=sum(Site[om[[5]],i]);
	ns[4,i]=sum(Site[ca[[3]],i]);
	ns[5,i]=sum(Site[ca[[4]],i]);
	ns[6,i]=sum(Site[ca[[5]],i]);
	ns[7,i]=sum(Site[fu[[3]],i]);
	ns[8,i]=sum(Site[fu[[4]],i]);
	ns[9,i]=sum(Site[fu[[5]],i]);
	ns[10,i]=sum(Site[ba[[3]],i]);
	ns[11,i]=sum(Site[ba[[4]],i])
	ns[12,i]=sum(Site[ba[[5]],i])
		
		}
s<-apply(ks*ns,2,sum)
SI<-100*s/(b+s)
BI<-100*b/(b+e+s)
BI
Fu2<-vector()
Ba1<-vector()

for(i in 1:5){Fu2[i]=sum(Site[fu[[2]],i]);Ba1[i]=sum(Site[ba[[1]],i])}
CI<-100*0.8*Fu2/(3.2*Ba1+0.8*Fu2)
CI
H;lamda;EI;SI;BI;CI;
data<-rbind(H,lamda,MI,PPI,EI,SI,BI,CI)
tmp <- function(x) {sprintf("%.02f", x)}
data2<-apply(data,1,tmp)
write.table(data2,"1.csv",sep=",",row.names=c("Site1","Site2","Site3","Site4","Meansite"),col.names=NA)