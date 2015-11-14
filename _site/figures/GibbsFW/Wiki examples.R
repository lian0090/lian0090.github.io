png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/lm1.png")
plot(lm1)
dev.off()

png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/lm1_fewline.png")
plot(lm1,plotVAR=c("1081265","1101307", "1295736", "13302" , "1343502"))
dev.off()

png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/samps.png")
plot(samps)
dev.off()


png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/lm1_2_3.png")
par(mfrow=c(2,2))
plot(lm1,main="lm1")
plot(lm2,main="lm2")
plot(lm3,main="lm3")
dev.off()

png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/lm1_fewline.png")
plot(lm1,plotVAR=c("V1","V4","V5","V9"))
dev.off()

png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/samps.png")
plot(samps)
dev.off()

png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/lm1_2_3_fewline.png")
par(mfrow=c(2,2))
plot(lm1,plotVAR=c(1:5),main="lm1")
plot(lm2,plotVAR=c(1:5),main="lm2")
plot(lm3,plotVAR=names(lm1$g)[(1:5)],main="lm3")
dev.off()




png("~/Dropbox/github/lian0090.github.io/figures/GibbsFW/samps.png")
load("lm6samps.rda")
plot(samps)
dev.off()


