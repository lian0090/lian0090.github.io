---
layout: default
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



## [R]('_techmemo/R/index.md')