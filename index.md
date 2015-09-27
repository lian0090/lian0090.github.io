---
layout: default
title: Lian Lian 
background_color: B3E5FC
---

My name is Lian Lian. I did my PhD in University of Minnesota. Currently, I am in Michigan State Univeristy working on Statistical Genetics. 

<ul class="tag-box inline">
{% assign tags_list = site.categories %}  
{% if tags_list.first[0] == null %}
{% for tag in tags_list %} 
<li><a href="#{{ tag }}">{{ tag | capitalize }} <span>{{ site.tags[tag].size }}</span></a></li>
{% endfor %}
{% else %}
{% for tag in tags_list %} 
<li><a href="#{{ tag[0] }}">{{ tag[0] | capitalize }} <span>{{ tag[1].size }}</span></a></li>
{% endfor %}
{% endif %}
{% assign tags_list = nil %}
</ul>


{% endfor %}
