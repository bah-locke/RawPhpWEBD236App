<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/Question.inc";
include_once "models/Users.inc";
include_once "models/Answer.inc";
include_once "models/Validator.inc";

// This is the question Answers CONTROLLER... 

// Handles adding a new record with 3 fields...
function post_add($params) {
	ensureLoggedIn();	
	Authenticator::instance() -> ensure('answer_create');
	
	$userid = safeParam($_SESSION, 'userid', NULL);
	$questionId = safeParam($_REQUEST, 'questionId', NULL);
    $answerText = safeParam($_REQUEST,'answerText',NULL);
	
	$record = Question::findRecordByID($questionId);
    if (!$record) {
        die("No record with id $id found.");
    }
	$user = User::findUserbyId($record -> getUserId());
	$answers = Answer::findAnswersByQuestionId($record -> getId());
	
	$errors = new Validator();
	$errors -> required('answer',$answerText,'Answer is required');

	if(!$errors -> hasErrors()) {
		$answer = new Answer('',$userid, $questionId, $answerText);
		$answer -> addAnswer();
		// send focus back to the home page...
		redirectRelative("question/view/".$record -> getId());
	}
	renderTemplate(
		"views/record_view.inc",
		array(
			'title' => 'Add a Answer',
			'errors' => $errors -> allErrors(),
			'answerText' => $answerText,
			'user' => $user,
			'question' => $record,
			'answers' => $answers
		)
	);	
}

// Handle a request to delete a record by id...
function get_delete($params) {
	Authenticator::instance() -> ensure('answer_delete');
	
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $answer = Answer::findAnswerByID($id);
	$record = Question::findRecordByID($answer -> getQuestionId());
    if (!$answer) {
        die("No record found.");
    }
    $answer -> deleteAnswer();
	// send focus back to the home page...
    redirectRelative("question/view/".$record -> getId());
}

?>