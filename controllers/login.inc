<?php
include_once "include/util.inc";
include_once "models/Users.inc";
include_once "models/Validator.inc";

function get_index($params) {
    // @formatter:off
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter:on
}

function post_index($params) {
    $email = safeParam($_REQUEST, 'email', null);
    $password = safeParam($_REQUEST, 'password', null);
	$errors = new Validator();
	$errors -> required('email',$email,'Email is required');
	$errors -> required('password',$password,'Password is required');
	
    if (User::isValidUser($email) && !$errors -> hasErrors()) {
		$userInfo = User::findUserByEmail($email);
        $_SESSION['loggedin'] = true;
		$_SESSION['userid'] = $userInfo -> getId();
		$_SESSION['fname'] = $userInfo -> getFirstName();
		$_SESSION['lname'] = $userInfo -> getLastName();
		$_SESSION['email'] = $userInfo -> getEmail();
		$_SESSION['password'] = $userInfo -> getPassword();
		
		if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
		
        redirectRelative("index");
    }
	if (!User::isValidUser($email)){
		$errors -> addError('isValid','User not found');
	}
	// @formatter:off
	renderTemplate(
		"views/login_form.inc",
		array(
			'title' => 'Login',
			'errors' => $errors -> allErrors(),
			'email' => $email,
			'password' => $password
		)
	);
	// @formatter:on
}
?>