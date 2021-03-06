---
title: Output random effects estimates from SKAT. 
categories: [SKAT]
layout: post
---


Output random effects estimates from SKAT. 

$$\hat{\beta}=GZ'V^{-1}(y-X\hat\alpha)$$

G=diag(\(\tau_d\),\(\Gamma\)), Z=(\(Z_d\),W)

$V^{-1}=V_d^{-1}-V_d^{-1}WC_\Gamma W'V_d^{-1}$

 - $Z'V^{-1}(y-X\hat\alpha)=Z_d'V^{-1}(y-X\hat\alpha)+\underbrace{WV^{-1}(y-X\hat\alpha)}_{\text{calculated}}$
 

* $Z_d'V^{-1}(y-X\hat{\alpha})=Z_d'V_d^{-1}(y-X\hat\alpha)-Z_d'V_d^{-1}WC_{\Gamma} W'V_d^{-1}(y-X\hat\alpha)$
* $Z_d$ low rank
     * $Z_d'V_d^{-1}(y-X\hat\alpha)=Z_d'U_1D_{\tau}U_1'(y-X\hat\alpha)+Z_d'(y-X\hat\alpha)/\sigma^2$
     * $Z_d'V_d^{-1}W$
* $Z_d$ full rank
   * $Z_d'V_d^{-1}(y-X\hat\alpha)$ =$Z_d'UD^\# U'(y-X\hat\alpha)$
   * $Z_d'V_d^{-1}W$

