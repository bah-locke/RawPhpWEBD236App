%% views/header.html %%
<h1>{{$question -> getTitle()}}</h1>
%% views/errors.html %%
[[ include_once 'include/util.inc'; ]]
[[ include_once 'models/Users.inc'; ]]
<div class='display'>
	Filed under: 
	[[ $exploded_string =  explodeNoSpace($question -> getTag()); ]]
	[[ foreach ($exploded_string as $value): ]]
		<a href="@@tag/view/{{$value}}@@" >{{$value}}<a>
	[[ endforeach; ]]
    <div class='value'>{{markdown($question -> getContent())}}</div>
</div>
<div class='display'>
    [[ if ($files) : ]]
    <label>Attachments:</label>
    <div class='value'>&nbsp;
        <ul>
        [[ foreach ($files as $file) : ]]
        <li><a href="@@file/download/{{$file->getId()}}@@">[download]</a> <a href="@@file/delete/{{$file->getId()}}/{{$question->getId()}}@@">[delete]</a> <a href="@@file/view/{{$file->getId()}}@@">[view]</a> {{ $file->getOrigName() }}</li>
        [[ endforeach; ]]
        </ul>
    </div>
    [[ endif; ]]
</div>
<div>
	[[ include_once 'include/util.inc'; ]]
	[[ if (isLoggedIn() && $user -> getId() == $_SESSION['userid']) : ]]
		<p>
			[[ if (Authenticator::instance() -> can('question_edit')) : ]]
				<a href="@@question/edit/{{$question -> getId()}}@@">[Edit]</a>
			[[endif;]]
			[[ if (Authenticator::instance() -> can('question_delete')) : ]]
				<a href="@@question/delete/{{$question -> getId()}}@@">[Del]</a>
			[[endif;]]
			[[ if (Authenticator::instance() -> can('question_edit')) : ]]
				<div class='inputs'>
					<form action="@@file/add@@" method="post" enctype="multipart/form-data">
						<input type="hidden" id="questionsId" name="questionsId" value="{{$question->getId()}}" />
						<label for="file">Add a file:</label>
						<input type="file" id="file" name="file" /><br />
						<input type="submit" value="Upload" />
					</form>
				</div>
			[[ endif; ]]
			[[ if (Authenticator::instance() -> can('answer_create')) : ]]
				<form action="@@answer/add@@" method="post">
					<input type="hidden" id-"questionId" name="questionId" value="{{$question -> getId()}}">
					<label for="answerText">Add an Answer:</label>
					<textarea type="text" id="answerText" name="answerText" rows="10" cols="65">{{isset($answerText) ? $answerText : ''}}</textarea><br /><br/>	
					<input type="submit" value="Add New Answer" /><br /><br/>
				</form><br><br>
			[[ endif; ]]
			<h2>Answers:</h2>
			[[ if ($answers):]]
				[[ foreach ($answers as $answer): ]]
					<div class="content inner">
						Posted on: {{$answer -> getAnswerDate()}} by <a href="@@users/view/{{$answer -> getUserId()}}@@">[[$user = User::findUserById($answer -> getUserId()); ]] {{$user -> getFirstName()}} {{$user -> getLastName()}}</a><br>
						<span class="inContents">{{markdown($answer -> getAnswerText())}}</span>
						[[ if (Authenticator::instance() -> can('answer_delete')) : ]]
							<a href="@@answer/delete/{{$answer -> getId()}}@@">[Delete]</a>
						[[ endif; ]]
					</div><br>
				[[ endforeach; ]]
			[[ endif; ]]
		</p>
	[[ elseif (isLoggedIn()): ]]
		[[ if (Authenticator::instance() -> can('answer_create')) : ]]
			<form action="@@answer/add@@" method="post">
				<input type="hidden" id-"questionId" name="questionId" value="{{$question -> getId()}}">
				<label for="answerText">Add an Answer:</label>
				<textarea type="text" id="answerText" name="answerText" rows="15" cols="69">{{isset($answerText) ? $answerText : ''}}</textarea><br /><br/>	
				<input type="submit" value="Add New Answer" /><br /><br/>	
			</form><br><br>
		[[ endif; ]]
		<h2>Answers:</h2>
		[[ if ($answers):]]
			[[ foreach ($answers as $answer): ]]
				<div class="content inner">
					Posted on: {{$answer -> getAnswerDate()}} by <a href="@@users/view/{{$answer -> getUserId()}}@@">[[$user = User::findUserById($answer -> getUserId()); ]] {{$user -> getFirstName()}} {{$user -> getLastName()}}</a><br>
					<span class="inContents">{{markdown($answer -> getAnswerText())}}</span>
					[[ if (Authenticator::instance() -> can('answer_delete')) : ]]
						<a href="@@answer/delete/{{$answer -> getId()}}@@">[Delete]</a>
					[[ endif; ]]
				</div><br>
			[[ endforeach; ]]
		[[ endif; ]]
	[[ else: ]]
		[[ if ($answers):]]
		<h2>Answers:</h2>
			[[ foreach ($answers as $answer): ]]
				<div class="content inner">
					Posted on: {{$answer -> getAnswerDate()}} by <a href="@@users/view/{{$answer -> getUserId()}}@@">[[$user = User::findUserById($answer -> getUserId()); ]] {{$user -> getFirstName()}} {{$user -> getLastName()}}</a><br>
					<span class="inContents">{{markdown($answer -> getAnswerText())}}</span>
				</div><br>
			[[ endforeach; ]]
		[[ endif; ]]
	[[ endif; ]]
</div>
<div class="clearboth">
    <p><a href="@@index@@"><< Back</a></p>
</div>
%% views/footer.html %%
