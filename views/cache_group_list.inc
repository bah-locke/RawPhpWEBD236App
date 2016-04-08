<!DOCTYPE html>
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/webd236/lab5/static/style.css" />
    </head>
    <body>
        <div class="content">
<?php  include_once 'include/util.inc'; 
  include_once 'include/Authenticator.inc';
  include_once 'models/Users.inc';
?>
<?php  if (isLoggedIn()) : ?>
	<p>Welcome, <?php echo($_SESSION['fname']); ?> <?php echo($_SESSION['lname']); ?></p>
	<p class='loggedin'><a class="hlink" href='/webd236/lab5/logout'>Log out</a></p>
	<?php  if (Authenticator::instance()->can('admin_page')) : ?>
		<p class='loggedin'><a class="hlink" href="/webd236/lab5/admin">Admin</a></p>
	<?php  endif; ?>
	<p class='loggedin'><a class="hlink" href='/webd236/lab5/users/view/<?php echo($_SESSION['userid']); ?>'>My Profile</a></p>
	<p class='loggedin'><a class="hlink" href='/webd236/lab5/index'>Home</a></p>
<?php  else : ?>
    <p class='login'><a class="hlink" href='/webd236/lab5/login'>Log in</a></p>
    <p class='login'><a class="hlink" href='/webd236/lab5/register'>Register</a></p>
	<p class='login'><a class="hlink" href='/webd236/lab5/index'>Home</a></p>
<?php  endif; ?>
<h1><?php echo($title); ?></h1>
<form action='/webd236/lab5/group/add' method='post'>
    <label for="name">Group name:</label>
    <input type="text" id="name" name="group[name]" />
    <input type="submit" value="Add" />
</form>
<ul>
    <?php  foreach($groups as $group) : ?>
    <li><a href='/webd236/lab5/group/members/<?php echo($group->getId()); ?>'>[Members]</a> <a href='/webd236/lab5/group/permissions/<?php echo($group->getId()); ?>'>[Permissions]</a> <a href='/webd236/lab5/group/delete/<?php echo($group->getId()); ?>'>[Delete]</a> <?php echo($group->getName()); ?></li> 
    <?php  endforeach; ?> 
</ul>
        <div class="footer">
            Copyright &copy; 2015 Blake Johanning
        </div>
        </div><!-- content div -->
    </body>
</html>
