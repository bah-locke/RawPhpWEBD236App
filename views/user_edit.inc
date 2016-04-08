%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
    <form action="@@users/edit@@" method="post">
        <label for="firstName">First Name:</label>
        <input type="text" id="firstName" name="firstName" value="{{$user -> getFirstName()}}" />
        <label for="lastName">Last Name:</label>
        <input type="text" id="lastName" name="lastName" value="{{$user -> getLastName()}}" />
        <label for="email">Email Address:</label>
        <input type="text" id="email" name="email" value="{{$user -> getEmail()}}" />
        <label for="password">Password:</label>
        <input type="text" id="password" name="password" value="{{$user -> getPassword()}}" /><br><br>     
		<input type="submit" value="Save" />
    </form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
