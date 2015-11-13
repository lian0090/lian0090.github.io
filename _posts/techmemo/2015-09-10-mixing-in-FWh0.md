---
title: mixing in FWh0
categories: [techmemo,python]
tags: [techmemo,python]
layout: post
---

```R
bh=NULL
colnamesbh=NULL
for(i in 1:2){
for(j in 1:2){
bh=cbind(bh,samps[[1]][,paste('b[',i,']',sep="")]*samps[[1]][,paste('h[',j,']',sep="")])
colnamesbh=c(colnamesbh,paste("b",i,"h",j,sep=""));
}
}
colnames(bh)=colnamesbh
bh=mcmc.list(as.mcmc(bh))
plot(bh,density=F)

```





![trace of b1h1](https://dl.dropboxusercontent.com/u/13898422/FWd/mixing%20on%20bh%20and%20yhat%20from%20GibbsFWh0/tracebh.pdf)
 

 