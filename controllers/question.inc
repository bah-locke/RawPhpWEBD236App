<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/Question.inc";
include_once "models/Users.inc";
include_once "models/Validator.inc";
include_once "models/File.inc";
include_once "models/Answer.inc";

// This is the question RECORDS CONTROLLER... 

// Handles the home page... 
// Display a list of records...
function get_list($params) {
    $records = Question::findAllRecords();

    renderTemplate(
        "views/record_list.inc",
        array(
            'title' => 'My Questions and Answers',
            'records' => $records
        )
    );
}

// Handles viewing one individual record...
function get_view($params) {

    $id = safeParam($params, 0, NULL);
    if (!isset($id)) {
        die("No Record selected");
    }
    
    $record = Question::findRecordByID($id);
	
    if (!$record) {
        die("No record with id $id found.");
    }
	
	$files = File::findByQuestionsId($record->getId());
	$user = User::findUserbyId($record -> getUserId());
	$answers = Answer::findAnswersByQuestionId($record -> getId());
	
    renderTemplate(
        "views/record_view.inc",
        array(
            'title' => 'Viewing Record Info',
            'question' => $record,
			'user' => $user,
			'answers' => $answers,
			'files' => $files
        )
    );
}

//Handles loading of blank adding page...
function get_add() {
	Authenticator::instance() -> ensure('question_create');
	
	renderTemplate(
		"views/record_add.inc",
		array(
			'title' => 'Add a Question'
		)
	);		
}

// Handles loading record edit form view...
function get_edit($params) {
	Authenticator::instance() -> ensure('question_edit');
	
    $id = safeParam($params, 0, NULL);
    if (!isset($id)) {
        die("No record specified");
    }
    $record = Question::findRecordById($id);
    if (!$record) {
        die("No record found.");
    }
    renderTemplate(
        "views/record_edit.inc",
        array(
            'title' => 'Editing a Question',
            'question' => $record,
			'tag' => ''
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

// Handles adding a new record with 3 fields...
function post_add($params) {
	ensureLoggedIn();	
	Authenticator::instance() -> ensure('question_create');
	
	$userid = safeParam($_SESSION, 'userid', NULL);

    $qtitle = safeParam($_REQUEST,'qtitle',NULL);
    $content = safeParam($_REQUEST,'content',NULL);
    $tag = safeParam($_REQUEST,'tag',NULL);	
	
	$errors = new Validator();
	$errors -> required('title',$qtitle,'Title is required');
	$errors -> required('content',$content,'Content is required');

	if(!$errors -> hasErrors()) {
		$question = new Question('',$userid, $qtitle, $content, $tag);
		$question -> addRecord();
		// send focus back to the home page...
		redirectRelative("index");
	}
	renderTemplate(
		"views/record_add.inc",
		array(
			'title' => 'Add a Question',
			'errors' => $errors -> allErrors(),
			'qtitle' => $qtitle,
			'content' => $content,
			'tag' => $tag
		)
	);	
}

// Handle Updating an existing record identified by id...
function post_edit($params) {
	ensureLoggedIn();
	Authenticator::instance() -> ensure('question_edit');
	
    $id = safeParam($_REQUEST, 'id', NULL);
    $qtitle = safeParam($_REQUEST, 'qtitle', NULL);
    $content = safeParam($_REQUEST, 'content', NULL);
	$tag = safeParam($_REQUEST, 'tag', NULL);
	
	$errors = new Validator();
	$errors -> required('id',$id,'Id is required');
	$errors -> required('title',$qtitle, 'Title is required');
	$errors -> required('content',$content, 'Content is required');
	
    if(!$errors -> hasErrors()) {
		$question = Question::findRecordById($id);
		
		if ($question) {
			$question -> setTitle($qtitle);
			$question -> setContent($content);
			$question -> setTag($tag);
			$question -> updateRecord();
			redirectRelative("question/view/$id");
		}
	} 
		
	$question = new Question($id,$_SESSION['userid'],$qtitle, $content, $tag);
	// @formatter:off
	renderTemplate(
		"views/record_edit.inc",
		array(
			'title' => 'Editing a Question',
			'errors' => $errors -> allErrors(),
			'question' => $question
		)
	);
	// @formatter:on		
}

// Handle a request to delete a record by id...
function get_delete($params) {
	Authenticator::instance() -> ensure('question_delete');
	
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $record = Question::findRecordByID($id);
    if (!$record) {
        die("No record found.");
    }
    $record -> deleteRecord();
	// send focus back to the home page...
    redirectRelative("index");
}

?>