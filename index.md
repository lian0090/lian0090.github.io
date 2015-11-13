---
layout: home
---

<div class="index-content background">
<div class="section">


        <ul class="artical-cate">
            <li style="text-align:center"><a href="/techmemo"><span>Techmemo</span></a></li>
            <li style="text-align:center"><a href="/project"><span>Project</span></a></li>
            <li style="text-align:center"><a href="/collection"><span>Collection</span></a></li>
        </ul>

        <div class="cate-bar"><span id="cateBar"></span></div>

        <ul class="artical-list">
        {% for post in site.categories.techmemo %}
            <li>
                <h2><a href="{{ post.url }}">{{ post.title }}</a></h2>
                <div class="title-desc">{{ post.excerpt}}</div>
            </li>
        {% endfor %}
        </ul>
    </div>
    <div class="aside">
    </div>
</div>
