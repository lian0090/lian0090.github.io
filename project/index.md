---
layout: home
---

<div class="index-content project">
    <div class="section">
<ul class="artical-cate">
<li class="on"><a href="/"><span>blog</span></a></li>
<li style="text-align:center"><a href="/techmemo"><span>techmemo</span></a></li>
<li style="text-align:right"><a href="/project"><span>project</span></a></li>
</ul>

        <div class="cate-bar"><span id="cateBar"></span></div>

        <ul class="artical-list">
        {% for post in site.categories.project %}
            <li>
                <h2>
                    <a href="{{ post.url }}">{{ post.title }}</a>
                </h2>
                <div class="title-desc">{{ post.excerpt }}</div>
            </li>
        {% endfor %}
        </ul>
    </div>
    <div class="aside">
    </div>
</div>
