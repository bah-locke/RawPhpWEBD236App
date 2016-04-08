<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/Validator.inc";
include_once "models/Question.inc";
include_once "include/UploadDir.inc";

function post_add($params) {
    Authenticator::instance() -> ensure('question_edit');

    $questionsId = safeParam($_REQUEST, 'questionsId', false);
    $question = Question::findRecordById($questionsId);
    if (!$question) {
        die("No question with that ID found");
    }
    $dir = new UploadDir();
    $file = $dir -> getUpload('file');
    $file -> setQuestionsId($question -> getId());

    $validator = $file -> validate();

    if ($validator -> hasErrors()) {
        die("Problem with file upload");
    }
    $file -> insert();
    redirectRelative("question/view/{$question->getId()}");
}

function get_download($params) {
    Authenticator::instance() -> ensure('question_view');
    $fileId = safeParam($params, 0);
    $file = File::findById($fileId);
    header('Content-Description: File Transfer');
    header('Content-Type: ' . $file -> getType());
    header('Content-Disposition: attachment; filename=' . $file -> getOrigName());
    header('Content-Transfer-Encoding: binary');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . $file -> getSize());
    ob_clean();
    flush();
    readfile($file -> fullPath());
    exit ;
}

function get_view($params) {
    $fileId = safeParam($params, 0);
    $file = File::findById($fileId);
    header('Last-Modified: ' . date('r'));
    header('Accept-Ranges: bytes');
    header('Content-Length: ' . $file -> getSize());
    header('Content-Type: ' . $file -> getType());
    header('Content-Disposition: inline; filename=' . $file -> getOrigName());
    ob_clean();
    flush();
    readfile($file -> fullPath());
    exit ;
}

function get_delete($params) {
    Authenticator::instance() -> ensure('question_edit');
    $fileId = safeParam($params, 0);
    $questionsId = safeParam($params, 1);
    $file = File::findById($fileId);
    $file -> delete();
    redirectRelative("question/view/$questionsId");
}
?>