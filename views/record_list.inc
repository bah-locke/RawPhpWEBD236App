%% views/header.html %% 
<h1>{{$title}}</h1>
<h2>Recent Questions</h2>
	[[ include_once 'models/Users.inc'; ]]
	[[ include_once 'include/util.inc'; ]]
	[[ include_once 'include/Authenticator.inc'; ]]
	[[ foreach ($records as $question) : ]]
		<div class="content inner">
			<strong><a href="@@question/view/{{$question -> getId()}}@@">{{$question -> getTitle()}}</a></strong><br>
			Posted on: {{$question -> getPostDate()}} by <a href="@@users/view/{{$question -> getUserId()}}@@">[[$user = User::findUserById($question -> getUserId()); ]] {{$user -> getFirstName()}} {{$user -> getLastName()}}</a><br>
			[[ if ($question -> getTag() != "" || $question -> getTag() != NULL): ]]
				Filed under: 
				[[ $exploded_string =  explodeNoSpace($question -> getTag()); ]]
				[[ foreach ($exploded_string as $value): ]]
					<a href="@@tag/view/{{$value}}@@" >{{$value}}<a>
				[[ endforeach; ]]
				<br>
			[[ endif; ]]
			<span class="inContents">{{markdown($question -> getContent())}}</span>
		</div><br>
	[[ endforeach; ]]

	[[ if (Authenticator::instance() -> can('question_create')) : ]]	
		<div class="clearboth">
			<p><a href="@@question/add@@">Add a question</a></p>
		</div>
	[[ endif; ]]

%% views/footer.html %% 