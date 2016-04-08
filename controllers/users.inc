<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/Question.inc";
include_once "models/Users.inc";
include_once "models/Validator.inc";
include_once "models/Group.inc";

// This is the question USERS CONTROLLER... 


// Handles viewing one individual user...
function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No Record selected");
    }

	$user = User::findUserById($id);
    $records = Question::findRecordsByUserId($id);
    if (!$records && !$user) {
        die("No record with id $id found.");
    }

    renderTemplate(
        "views/user_view.inc",
        array(
            'title' => 'Viewing User',
            'user' => $user,
			'records' => $records
        )
    );
}


// Handles loading record edit form view...
function get_edit($params) {
	Authenticator::instance() -> ensure('user_edit');
	
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }
    $user = User::findUserById($id);
    if (!$user) {
        die("No record found.");
    }
    renderTemplate(
        "views/user_edit.inc",
        array(
            'title' => 'Editing Profile',
            'user' => $user
        )
    );
}

// function to validate whether elements have been provided in $_POST....
function validate_present($elements) {
    $errors = '';
    foreach ($elements as $element) {
        if (!isset($_POST[$element]) || empty($_POST[$element])) {
            $errors .= "Please specify a $element<br />\n";
        }
    }
    return $errors;
}

// Handle Updating an existing record identified by id...
function post_edit($params) {
	Authenticator::instance() -> ensure('user_edit');
	
    $id = safeParam($_SESSION, 'userid', NULL);
    $fname = safeParam($_REQUEST, 'firstName', NULL);
    $lname = safeParam($_REQUEST, 'lastName', NULL);
	$email = safeParam($_REQUEST, 'email', NULL);
	$password = safeParam($_REQUEST, 'password', NULL);
	
	$errors = new Validator();
	$errors -> required('firstName',$fname,'First name is required');
	$errors -> required('lastName',$lname,'Last name is required');
	$errors -> required('email',$email,'Email is required');
	$errors -> required('password',$password,'Password is required');
	
	if(!$errors -> hasErrors()) {		
		$user = User::findUserById($id);
		$user -> setFirstName($fname);
		$user -> setLastName($lname);
		$user -> setEmail($email);
		$user -> setPassword($password);
		$user -> updateUser();
		redirectRelative("users/view/$id");
	} 
	$user = new User($id, $fname, $lname, $email, $password);
	// @formatter:off
		renderTemplate(
			"views/user_edit.inc",
			array(
				'title' => 'Editing Profile',
				'errors' => $errors -> allErrors(),
				'user' => $user
			)
		);
	// @formatter:on		
}

// Handle a request to delete a record by id...
function get_delete($params) {
	Authenticator::instance() -> ensure('user_delete');
	
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $user = User::findUserById($id);
    if (!$user) {
        die("No record found.");
    }
	$question = Question::findRecordsByUserId($user -> getId());
	Question::deleteRecordByUserId($id);
    $user -> deleteUser();
	
	if (isLoggedIn() && $user -> getEmail() == $_SESSION['email']) {
		//clear session
		$_SESSION = array();
		session_destroy();
		// send focus back to the home page...
		redirectRelative("index");
	}
}

function get_manage($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $users = User::findAllUsers();
    // @formatter:off
    renderTemplate(
        "views/user_list.inc",
        array(
            "title" => "Manage users",
            "users" => $users
        )
    );
    // @formatter:on
}

function get_groups($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No user id specified");
    }
    $user = User::findUserById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    $memberOf = Group::findByUserId($id);
    $notMemberOf = Group::findByNotUserId($id);
    renderTemplate(
        "views/user_groups.inc",
        array(
            "title" => "{$user->getFullName()}'s Groups",
            "memberOf" => $memberOf,
            "notMemberOf" => $notMemberOf,
            "user" => $user
        )
    );
}
?>