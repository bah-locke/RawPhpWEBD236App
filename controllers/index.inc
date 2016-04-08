<?php
include_once "include/util.inc";
include_once "models/Question.inc";
include_once "controllers/question.inc";

function get_index($params) {
	// redirect to the questions controller get_list() function...
    get_list($params);
}

?>