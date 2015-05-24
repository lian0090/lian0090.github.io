---
title: Jekyll
layout: default
---

#Collections
The files with the correct front matter are called documents. And these documents will have document.url that you can include into your markdown link. 

The files without the correct front matter are called static files. And theses documents will not have document.url associated with them, you need to use the relative path of those documents if you want put the link of them into the index file. For example, if there is a static file test.txt, you want to reference to it in index.md, you need `[test](../test.txt)` 
