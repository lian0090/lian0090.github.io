module Jekyll

  class Blurb < Liquid::Block
    def render(context)
      # Get the current post's post object
      id = context["page"]["id"]
      posts = context.registers[:site].posts
      post = posts [posts.index {|post| post.id == id}]

      ## Put the block contents into the post's excerpt field,
      ## and also return those contents
      post.data["blurb"] = super
    end
  end

end

Liquid::Template.register_tag('blurb', Jekyll::Blurb)
