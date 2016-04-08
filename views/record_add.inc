%% views/header.html %% 
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
	<form action="@@question/add@@" method="post">
		<label for="qtitle">Title:</label>
		<input type="text" id="title" name="qtitle" value="{{isset($qtitle) ? $qtitle : ''}}"/><br />
		<label for="content">Content:</label>
		<textarea type="text" id="content" name="content" rows="15" cols="69">{{isset($content) ? $content : ''}}</textarea><br />	
		<label for="tag">Tag:</label>
		<input type="text" id="tag" name="tag" value="{{isset($tag) ? $tag : ''}}"/><br />	<br />
		<input type="submit" value="Add New Record" />
	</form>
</div>
%% views/footer.html %% 