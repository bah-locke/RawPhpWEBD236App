%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
    <form action="@@register@@" method="post">
        <label for="firstName">First Name:</label>
        <input type="text" id="firstName" name="firstName" value="{{isset($firstName) ? $firstName : ''}}" />
        <label for="lastName">Last Name:</label>
        <input type="text" id="lastName" name="lastName" value="{{isset($lastName) ? $lastName : ''}}" />
        <label for="email">Email Address:</label>
        <input type="text" id="email" name="email" value="{{isset($email) ? $email : ''}}" />
        <label for="password">Password:</label>
        <input type="text" id="password" name="password" value="{{isset($password) ? $password : ''}}" /><br><br>     
		<input type="submit" value="Register" />
    </form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
