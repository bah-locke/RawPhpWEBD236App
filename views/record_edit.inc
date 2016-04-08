%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
    <form action="@@question/edit@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$question -> getId()}}" />
        <label for="title">Title:</label>
        <input type="text" id="title" name="qtitle" value="{{$question -> getTitle()}}" />
        <label for="content">Content:</label>
        <textarea type="text" id="content" name="content" rows="15" cols="69">{{$question -> getContent()}}</textarea>
		<label for="tag">Tag:</label>
		<input type="text" id="tag" name="tag" value="{{$question -> getTag()}}" />
		<br>
		<br>
        <input type="submit" value="Save" />
    </form>
</div>
<div class="clearboth">
    <p><a href="@@index@@"><< Back</a></p>
</div>
%% views/footer.html %%
