<?php
include_once "include/util.inc";
include_once "models/Users.inc";

function get_index($params) {
    $_SESSION = array();
    session_destroy();
    redirectRelative("index");
}
?>