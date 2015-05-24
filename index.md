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


# Hello World
# Hello World




Proin eleifend libero accumsan felis luctus nec consectetur purus commodo. Phasellus sodales est nec massa imperdiet commodo. Maecenas risus nulla, placerat vel vestibulum vel, dapibus quis libero.

Donec libero libero, bibendum non condimentum ac, ullamcorper at sapien. Du
is feugiat urna vel justo cursus facilisis. Vivamus ligula dui, convallis a
 varius vitae, facilisis eget magna.

