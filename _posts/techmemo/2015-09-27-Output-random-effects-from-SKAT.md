---
title: Output random effects estimates from SKAT. 
categories: [techmemo,python]
tags: [techmemo,python]
layout: post
---

<!--mathJax  -->
<script type="text/x-mathjax-config">
MathJax.Hub.Config({
tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}
});
</script>
<script type="text/javascript" src="path-to-mathjax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/javascript"
src="//cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML">
</script>


Output random effects estimates from SKAT. 
$$\hat{\beta}=GZ'V^{-1}(y-X\hat\alpha)$$

G=diag($\tau_d$,$\Gamma$), Z=($Z_d$,W)

$$V^{-1}=V_d^{-1}-V_d^{-1}WC_\Gamma W'V_d^{-1}$$

 - $$Z'V^{-1}(y-X\hat\alpha)=Z_d'V^{-1}(y-X\hat\alpha)+\underbrace{WV^{-1}(y-X\hat\alpha)}_{\text{calculated}}$$
 

* $Z_d'V^{-1}(y-X\hat{\alpha})=Z_d'V_d^{-1}(y-X\hat\alpha)-Z_d'V_d^{-1}WC_{\Gamma} W'V_d^{-1}(y-X\hat\alpha)$
* $Z_d$ low rank
     * $Z_d'V_d^{-1}(y-X\hat\alpha)=Z_d'U_1D_{\tau}U_1'(y-X\hat\alpha)+Z_d'(y-X\hat\alpha)/\sigma^2$
     * $Z_d'V_d^{-1}W$
* $Z_d$ full rank
   * $Z_d'V_d^{-1}(y-X\hat\alpha)$ =$Z_d'UD^\# U'(y-X\hat\alpha)$
   * $Z_d'V_d^{-1}W$

