%% views/header.html %% 
<h1>{{$title}}</h1>
[[ include_once 'include/util.inc';]]
	<p>
	<span style="margin-right:20px;">First Name:</span>{{$user -> getFirstName()}}<br>
	<span style="margin-right:18px;">Last Name:</span> {{$user -> getLastName()}}<br>
	<span style="margin-right:50px;">Email:</span> {{$user -> getEmail()}}<br>
	<span style="margin-right:26px;">Password:</span> 
		[[ for ($i = 0; $i < strlen($user -> getPassword()); $i++) :]]
			*
		[[ endfor; ]]
		</p>
		[[ if (Authenticator::instance() -> can('user_edit')) : ]]
		<p>
			<a href="@@users/edit/{{$user -> getId()}}@@">[Edit]</a>
			<a href="@@users/delete/{{$user -> getId()}}@@">[Del]</a>
		</p>
	[[ endif; ]]
	<h2>Questions by {{$user -> getFirstName()}} {{$user -> getLastName()}}</h2>
	[[ if (!$records) :]]
		<h4><i>This user is such a know it all! No questions were found.</i></h4>
	[[ else: ]]
		[[ foreach ($records as $record) : ]]
			<div class="content inner">
				<strong><a href="@@question/view/{{$record -> getId()}}@@">{{$record -> getTitle()}}</a></strong><br>
				Posted on: {{$record -> getPostDate()}} by <a href="@@users/view/{{$record -> getUserId()}}@@">{{$user -> getFirstName()}} {{$user -> getLastName()}}</a><br>
				[[ if ($record -> getTag() != "" || $record -> getTag() != null): ]]
				Filed under: 				
				[[ $exploded_string =  explodeNoSpace($record -> getTag()); ]]
				[[ foreach ($exploded_string as $value): ]]
					<a href="@@tag/view/{{$value}}@@" >{{$value}}<a>
				[[ endforeach; ]]<br>
				[[ endif; ]]
				<span class="inContents">{{markdown($record -> getContent())}}</span>
			</div><br>
		[[ endforeach; ]]
	[[ endif; ]]
<div class="clearboth">
	<p><a href="@@index@@"><< Back</a></p>
</div>

%% views/footer.html %% 