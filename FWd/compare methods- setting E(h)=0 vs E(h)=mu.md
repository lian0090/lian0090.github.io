---
layout: default
title: compare methods setting E(h)=0 vs E(h)=mu
---


```R
library(FWd)
data(wheat)
attach(wheat.Y)
OLSh0=lmFWh0(y,VAR,ENV)
OLShmu=lmFWhmu(y,VAR,ENV)
head(OLSh0$b)
head(OLShmu$b)
```
b for OLS are the same. 
```R
> head(OLSh0$b)
               [,1]
103122  -0.01499334
1047493 -0.23156180
1058137  0.15262836
1064007  0.33197972
1066175  0.16119069
1066279  0.14964002
> 
head(OLShmu$b)
               [,1]
103122  -0.01499334
1047493 -0.23156180
1058137  0.15262836
1064007  0.33197972
1066175  0.16119069
1066279  0.14964002

```

But we should notice that the estimates of g and the interpretation of g changed
```R
> cor(OLSh0$g,OLShmu$g)
         [,1]
[1,] 0.399232
```

The effect of changing the mean of h on Gibbs method 
```R
GibbsIh0=GibbsFWh0(y=y,VAR=VAR,ENV=ENV,saveAt="GibbsIh0")
GibbsIhmu=GibbsFWhmu(y=y,VAR=VAR,ENV=ENV,saveAt="GibbsIhmu")
```
results
```R
cor(GibbsIhmu$b,GibbsIh0$b)
           Init1
Init1 -0.3296878
```
The variance estimates for var_b is greatly reduced by introducing mu into h.
```R
> GibbsIhmu$var_b
    Init1 
0.0144938 
> GibbsIh0$var_b
     Init1 
0.09865855 
``` 
Why if we center y before using GibbsFWhmu?
By centering y, we almost recovered the original solutions with GibbsFWh0.
```R
yc=y-mean(y)
GibbsI.yc.hmu=GibbsFWhmu(y=yc,VAR=VAR,ENV=ENV)
GibbsI.yc.hmu$var_b
     Init1 
0.09357356
cor(GibbsI.yc.hmu$b,GibbsIh0$b)
          Init1
Init1 0.9499459
```

## test different models's prediction accuracy

```R
yNA=y
set.seed(12345)
whichNa=seq(from=0,to=2392,by=4)+sample(1:4,size=599,replace=T)
yNA[whichNa]=NA

OLS=lmFWh0(y=yNA,VAR=VAR,ENV=ENV)
GibbsIhmu=GibbsFWhmu(y=yNA,VAR=VAR,ENV=ENV,seed=12345)
GibbsIhmuyc=GibbsFWhmu(y=scale(yNA,center=T,scale=F),VAR=VAR,ENV=ENV,seed=12345)
GibbsIh0=GibbsFWh0(y=yNA,VAR=VAR,ENV=ENV, seed=12345)
```
The results on prediction accuracy. Even if we center y, the results on prediction accuracy is still suboptimal. Change seeds will get similar results. 
```R
> cor(y[whichNa],OLS$yhat[whichNa,])
[1] 0.6218797
> cor(y[whichNa],GibbsIhmu$yhat[whichNa,])
[1] 0.7471006
 cor(y[whichNa],GibbsIhmuyc$yhat[whichNa,])
[1] 0.783637
> cor(y[whichNa],GibbsIh0$yhat[whichNa,])
[1] 0.7927549
```

Now, that's introduce another model, to avoid the confounding effect among mu and h, we set h[0]=0, and only estimate all other h. The new model is y=mu+g+h+bh+e, where h~N(0,H\sigma^2_h), and we ask h[0] to be 0. 

Check the model convergence
```R
GibbsIh10=GibbsFWh10(y=y,VAR=VAR,ENV=ENV,saveAt="GibbsIh10")
load("GibbsIh10samps.rda")
png("traceFWh10.png")
plot(samps[,c('mu','h[1]','h[2]','b[1]','b[2]','var_e')],density=F)
dev.off()
```
The var_b
```R
> GibbsIh10$var_b
    Init1 
0.0683286 
```
The trace plot for GibbsFWh10
![trace plot for GibbsFWh10](https://lian0090.github.io/FWd/traceFWh10.png)


Compare with the original full model GibbsFWh0
The trace plot for GibbsFWh0
```R
setwd("/Users/lianlian/Dropbox/github/lian0090.github.io/FWd"
png("traceFWh0.png")
plot(samps[,c('mu','h[1]','h[2]','b[1]','b[2]','var_e')],density=F)
dev.off()
```
The trace plot for GibbsFWh0
![trace plot for GibbsFWh0](https://lian0090.github.io/FWd/traceFWh0.png)


The new model's prediction accuracy, it is even better than the original model.
```R
GibbsIh10=GibbsFWh10(y=yNA,VAR=VAR,ENV=ENV, seed=12345)
cor(y[whichNa],GibbsIh10$yhat[whichNa,])
[1] 0.7968909
```

Now, check the GibbsFWh10 model on the use the genomic matrix
```R
GibbsAh0=GibbsFWh0(y=yNA,VAR=VAR,ENV=ENV,saveAt="GibbsAh0",A=wheat.G,seed=12345)
GibbsAh10=GibbsFWh10(y=yNA,VAR=VAR,ENV=ENV, saveAt="GibbsAh10",A=wheat.G,seed=12345)
```
results
```R
> cor(y[whichNa],GibbsAh0$yhat[whichNa,])
[1] 0.8055785
 cor(y[whichNa],GibbsAh10$yhat[whichNa,])
[1] 0.8075624
```

```
load("GibbsAh10samps.rda")
png("traceFWAh10.png")
plot(samps[,c('mu','h[1]','h[2]','var_e')],density=F)
dev.off()
```

The trace plot for GibbsFWAh10
![trace plot for GibbsFWAh0](https://lian0090.github.io/FWd/traceFWAh10.png)