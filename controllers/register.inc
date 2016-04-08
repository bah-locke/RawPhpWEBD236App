<?php
include_once "include/util.inc";
include_once "models/Users.inc";
include_once "models/Validator.inc";

function get_index($params) {
    // @formatter:off
    renderTemplate(
        "views/register_form.inc",
        array(
            'title' => 'Register',
        )
    );
    // @formatter:on
}

function post_index($params) {
    $firstName = safeParam($_REQUEST, 'firstName', NULL);
    $lastName = safeParam($_REQUEST, 'lastName', NULL);
    $email = safeParam($_REQUEST, 'email', NULL);
    $password = safeParam($_REQUEST, 'password', NULL);
	
	$errors = new Validator();
	$errors -> required('firstName',$firstName,'First name is required');
	$errors -> required('lastName',$lastName,'Last name is required');
	$errors -> email('email',$email);
	$errors -> password('password',$password);
	$isUser = User::isValidUser($email);
	
    if (!$isUser && !$errors -> hasErrors()) {
        $_SESSION['loggedin'] = true;
		$_SESSION['fname'] = $firstName;
		$_SESSION['lname'] = $lastName;
		$_SESSION['email'] = $email;
		$_SESSION['password'] = $password;
		$user = new User('',$firstName, $lastName, $email, $password);
		$user -> addUser();
		$userInfo = User::findUserbyEmail($email);
		
		$_SESSION['userid'] = $user -> getId();

        redirectRelative("index");
    }
	// @formatter:off
		renderTemplate(
			"views/register_form.inc",
			array(
				'title' => 'Register',
				'errors' => $errors -> allErrors(),
				'firstName' => $firstName,
				'lastName' => $lastName,
				'email' => $email,
				'password' => $password
			)
		);
	// @formatter:on		
}
?>