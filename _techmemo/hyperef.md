---
layout: default
title: Hyperef url
---
#Hyperef url
	
**colors**, **line break**

### Hyperref Colors
```
\documentclass{article} 
\usepackage[colorlinks = true,         
    linkcolor = red,             
   citecolor = red,            
\begin{document} 
Here is \href{http://www.google.com}{Google} and \href{http://www.yahoo.com}{Yahoo!}. 
\end{document}
```


Caution! if you do not add commas in-between the option items, it will not report error but the color will not work (always be black)! 



### How to break long url in an item

```latex
\usepackage[hyphenbreaks]{breaker}
```



