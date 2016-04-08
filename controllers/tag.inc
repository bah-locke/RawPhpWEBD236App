<?php
include_once "include/util.inc";
include_once "models/Question.inc";
include_once "models/Validator.inc";

// This is the question RECORDS CONTROLLER... 

// Handles the home page... 
// Display a list of records...
function get_view($params) {
    $tag = safeParam($params, 0, false);
    if ($tag === false) {
        die("No tag selected");
    }
	
	$tag = strtolower($tag);
    $records = Question::findAllRecordsByTag($tag);
	

    renderTemplate(
        "views/tag_view.inc",
        array(
            'title' => "Questions tagged '$tag'",
            'records' => $records
        )
    );
}

?>