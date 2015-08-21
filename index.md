---
layout: default
title: About 
active: about
background_color: B3E5FC
---
<ul>
  {% for post in site.posts %}
    <li>
      <a href="{{ post.url }}">{{ post.title }}</a>
    </li>
  {% endfor %}
   
   {% for python in site.python %}
    <li>
      <a href="{{ python.url }}">{{ python.title }}</a>
    </li>
  {% endfor %}  

  {% for jekyll in site.jekyll %}
    <li>
      <a href="{{ jekyll.url }}">{{ jekyll.title }}</a>
    </li>
  {% endfor %}

</ul>


My name is Lian Lian. I did my PhD in University of Minnesota. Currently, I am in Michigan State Univeristy working on Statistical Genetics. 


- [R](/techmemo/R/index.md)